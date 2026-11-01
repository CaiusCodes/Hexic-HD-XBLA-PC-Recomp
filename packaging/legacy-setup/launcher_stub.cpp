// Hexic HD PC - play launcher ("Hexic HD.exe")
//
// Setup copies this beside itself once the game is installed. It starts
// Game\hexic_hd.exe with Game as the working directory, passing any arguments
// through, so the player never has to open the Game folder. If the game is not
// installed yet it offers to run Setup instead. Built by
// packaging/Build-Stubs.ps1.

#include <windows.h>
#include <shellapi.h>

#include <string>

static std::wstring ExeDirectory() {
  wchar_t path[MAX_PATH];
  DWORD length = GetModuleFileNameW(nullptr, path, MAX_PATH);
  if (length == 0 || length == MAX_PATH) {
    return L".";
  }
  std::wstring full(path, length);
  size_t slash = full.find_last_of(L"\\/");
  return slash == std::wstring::npos ? L"." : full.substr(0, slash);
}

static bool Exists(const std::wstring& path) {
  return GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR args, int) {
  const std::wstring dir = ExeDirectory();
  const std::wstring game_dir = dir + L"\\Game";
  const std::wstring game_exe = game_dir + L"\\hexic_hd.exe";

  if (!Exists(game_exe) || !Exists(game_dir + L"\\assets\\default.xex")) {
    const std::wstring setup = dir + L"\\Install Hexic HD.exe";
    if (MessageBoxW(nullptr,
                    L"Hexic HD is not installed in this folder yet.\n\n"
                    L"Run Setup now and select your Xbox 360 Hexic HD package?",
                    L"Hexic HD", MB_YESNO | MB_ICONINFORMATION) == IDYES &&
        Exists(setup)) {
      ShellExecuteW(nullptr, L"open", setup.c_str(), nullptr, dir.c_str(), SW_SHOWNORMAL);
    }
    return 1;
  }

  std::wstring command = L"\"" + game_exe + L"\"";
  if (args && *args) {
    command += L" ";
    command += args;
  }

  STARTUPINFOW startup = {};
  startup.cb = sizeof(startup);
  PROCESS_INFORMATION process = {};
  if (!CreateProcessW(game_exe.c_str(), command.data(), nullptr, nullptr, FALSE, 0, nullptr,
                      game_dir.c_str(), &startup, &process)) {
    MessageBoxW(nullptr, L"Hexic HD could not be started.", L"Hexic HD", MB_OK | MB_ICONERROR);
    return 1;
  }
  CloseHandle(process.hProcess);
  CloseHandle(process.hThread);
  return 0;
}
