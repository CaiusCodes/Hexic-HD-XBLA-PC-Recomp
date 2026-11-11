// Hexic HD PC - launcher entry point.
//
//   Hexic HD.exe                      start the game; shows setup first when the
//                                     game data has not been imported (or a
//                                     needed file is missing)
//   Hexic HD.exe --setup              open the setup window
//   Hexic HD.exe --update             download and install the latest release
//                                     (the game's Settings > Updates starts this
//                                     and closes itself), then start the game
//                                     (update.cpp; HEXIC_UPDATE_API points it at
//                                     another releases URL, for testing)
//
// For automated tests (no window):
//   --setup --unattended [--package <file or folder>] [--extras fullscreen,shortcut]
//           [--shortcut-folder <dir>] [--saves-folder <dir>] [--language <code>]
//   (--saves-folder: saves and settings in that folder instead of resources\userdata;
//    --language: auto, en, de, es, fr, it, pt, ja, ko or zh, the game's text)
//   Exit code 0 imported, 1 failed, 2 several packages found (pass --package), 3 none found.
//
// Any other arguments are passed on to the game.
//
// A GUI-subsystem program, so starting it never flashes a console.
#include "launcher.h"

#include <objbase.h>
#include <shellapi.h>

#define HEXIC_WIDEN2(x) L##x
#define HEXIC_WIDEN(x) HEXIC_WIDEN2(x)
#define HEXIC_STRINGIZE2(x) #x
#define HEXIC_STRINGIZE(x) HEXIC_STRINGIZE2(x)

namespace hexic {
const wchar_t* const kVersion = HEXIC_WIDEN(HEXIC_STRINGIZE(HEXIC_VERSION));
}

namespace {

using namespace hexic;

int RunUnattended(Paths& p, const SetupOptions& options, const std::wstring& extras, const fs::path& saves_folder,
                  const std::string& language) {
  Log(L"Unattended setup");
  std::vector<Source> found;
  std::wstring why;
  if (!options.package.empty()) {
    found = SourcesIn(options.package, &why);
  } else {
    found = DetectSources(p);
    why = L"no package found";
  }
  if (found.size() != 1) {
    Log(L"Unattended: " + (found.empty() ? why : std::to_wstring(found.size()) + L" candidates, pass --package"));
    return found.empty() ? 3 : 2;
  }
  std::atomic<bool> cancel{false};
  const fs::path saves_from = found[0].kind == SourceKind::PreviousInstall ? found[0].path : FindPreviousInstall(p);
  ImportResult result = Import(p, found[0], saves_from, cancel, nullptr);
  if (!result.ok) return 1;
  Extras want;
  want.fullscreen = extras.find(L"fullscreen") != std::wstring::npos;
  want.shortcut = extras.find(L"shortcut") != std::wstring::npos;
  // As on a first setup: unticked extras change nothing; never replace a shortcut that is not ours.
  const std::wstring note = ApplyExtras(p, want, Extras{}, options.shortcut_folder, nullptr);
  if (!note.empty()) Log(L"Unattended: " + note);
  if (!saves_folder.empty()) {
    std::wstring message;
    const bool ok = SetUserDataLocation(p, saves_folder, &message);
    Log(L"Unattended: " + message);
    if (!ok) return 1;
  }
  if (!language.empty()) {
    const int index = LanguageIndex(language);
    if (index < 0 || !SetLanguage(p, index)) {
      Log(L"Unattended: unknown language " + Widen(language));
      return 1;
    }
  }
  return 0;
}

}  // namespace

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int) {
  int argc = 0;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  bool setup = false, unattended = false, update = false;
  std::wstring extras;
  fs::path saves_folder;
  std::string language;
  SetupOptions options;
  for (int i = 1; i < argc; ++i) {
    const std::wstring arg = argv[i];
    if (arg == L"--setup") {
      setup = true;
    } else if (arg == L"--update") {
      update = true;
    } else if (arg == L"--unattended") {
      unattended = true;
    } else if (arg == L"--package" && i + 1 < argc) {
      options.package = argv[++i];
    } else if (arg == L"--extras" && i + 1 < argc) {
      extras = argv[++i];
    } else if (arg == L"--saves-folder" && i + 1 < argc) {
      saves_folder = argv[++i];
    } else if (arg == L"--language" && i + 1 < argc) {
      for (const wchar_t ch : std::wstring(argv[++i])) language += static_cast<char>(ch < 128 ? ch : '?');
    } else if (arg == L"--shortcut-folder" && i + 1 < argc) {
      options.shortcut_folder = argv[++i];
    } else {
      options.game_args += (options.game_args.empty() ? L"" : L" ") + Quote(arg);
    }
  }
  if (argv) LocalFree(argv);

  Paths p = MakePaths();
  CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

  // A cut-off import is put right (or tidied up) before anything looks at the
  // folders. This is one directory check when nothing was cut off.
  LogTo(p.logs);
  RecoverInterruptedSwap(p);
  // The same for an update cut off half-way (and the previous launcher's exe,
  // left behind by an update because it was running).
  RecoverInterruptedUpdate(p);

  // The normal case: everything is in place, so start the game at once.
  std::wstring missing;
  const bool installed = IsInstalled(p, &missing);
  if (installed && !setup && !update && options.package.empty()) {
    // A saves folder chosen in setup that is gone (a drive not connected):
    // never start the game with empty saves in its place.
    if (p.custom_userdata && GetFileAttributesW(p.userdata.c_str()) == INVALID_FILE_ATTRIBUTES) {
      LogTo(p.logs);
      Log(L"The saves folder is missing: " + p.userdata.wstring());
      const std::wstring text = L"Hexic HD can't find your saves and settings folder:\n\n" + p.userdata.wstring() +
                                L"\n\nConnect the drive it is on and try again, or press OK to open setup "
                                L"and choose another folder.";
      if (MessageBoxW(nullptr, text.c_str(), L"Hexic HD", MB_OKCANCEL | MB_ICONWARNING) != IDOK) {
        CoUninitialize();
        return 1;
      }
      setup = true;
    }
  }
  if (installed && !setup && !update && options.package.empty()) {
    if (GetFileAttributesW(p.config.c_str()) == INVALID_FILE_ATTRIBUTES) {
      LogTo(p.logs);
      EnsureSettings(p);
    }
    RepairShortcut(p, options.shortcut_folder);
    std::wstring error;
    int code = 0;
    if (!LaunchGame(p, options.game_args, &error)) {
      LogTo(p.logs);
      Log(L"FAILED to start the game: " + error);
      MessageBoxW(nullptr, error.c_str(), L"Hexic HD", MB_OK | MB_ICONERROR);
      code = 1;
    }
    CoUninitialize();
    return code;
  }

  // Setup. One window per folder: a second launch brings the first to the front.
  std::wstring mutex_name = L"Local\\HexicHDSetup-";
  for (wchar_t c : p.root.wstring()) mutex_name += (c == L'\\' || c == L':') ? L'_' : static_cast<wchar_t>(towlower(c));
  if (mutex_name.size() > 250) mutex_name.resize(250);
  HANDLE mutex = CreateMutexW(nullptr, TRUE, mutex_name.c_str());
  if (mutex && GetLastError() == ERROR_ALREADY_EXISTS) {
    if (HWND other = FindWindowW(L"HexicHDSetup", nullptr)) {
      ShowWindow(other, SW_RESTORE);
      SetForegroundWindow(other);
    }
    CloseHandle(mutex);
    CoUninitialize();
    return 0;
  }

  LogTo(p.logs);
  options.forced = installed;
  options.update = update && installed;  // an incomplete install needs setup first
  options.reason = options.update ? L"--update" : installed ? L"--setup" : L"missing " + missing;
  const int code = unattended ? RunUnattended(p, options, extras, saves_folder, language) : RunSetupWindow(instance, p, options);
  if (mutex) {
    ReleaseMutex(mutex);
    CloseHandle(mutex);
  }
  CoUninitialize();
  return code;
}
