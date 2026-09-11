// Hexic HD PC - Setup launcher ("Install Hexic HD.exe")
//
// A small GUI-subsystem executable, so starting Setup never flashes a console.
// It runs resources\installer\Install-HexicHD.ps1 through a hidden Windows
// PowerShell host, forwards its own command line (used for automated testing),
// and returns the script's exit code. Built by packaging/Build-Stubs.ps1.

#include <windows.h>

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

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR args, int) {
  const std::wstring dir = ExeDirectory();
  const std::wstring script = dir + L"\\resources\\installer\\Install-HexicHD.ps1";

  if (GetFileAttributesW(script.c_str()) == INVALID_FILE_ATTRIBUTES) {
    MessageBoxW(nullptr,
                (L"Setup files are missing:\n" + script +
                 L"\n\nExtract the complete download again and keep the resources folder "
                 L"beside Setup.")
                    .c_str(),
                L"Hexic HD Setup", MB_OK | MB_ICONERROR);
    return 1;
  }

  // Full path, so a stray powershell.exe elsewhere on PATH is never picked up.
  wchar_t system_dir[MAX_PATH];
  GetSystemDirectoryW(system_dir, MAX_PATH);
  const std::wstring powershell =
      std::wstring(system_dir) + L"\\WindowsPowerShell\\v1.0\\powershell.exe";

  std::wstring command = L"\"" + powershell +
                         L"\" -NoProfile -STA -ExecutionPolicy Bypass -File \"" + script + L"\"";
  if (args && *args) {
    command += L" ";
    command += args;
  }

  STARTUPINFOW startup = {};
  startup.cb = sizeof(startup);
  PROCESS_INFORMATION process = {};

  // CREATE_NO_WINDOW hides PowerShell's console; the script draws its own window.
  if (!CreateProcessW(powershell.c_str(), command.data(), nullptr, nullptr, FALSE,
                      CREATE_NO_WINDOW, nullptr, dir.c_str(), &startup, &process)) {
    MessageBoxW(nullptr, L"Setup could not start Windows PowerShell.", L"Hexic HD Setup",
                MB_OK | MB_ICONERROR);
    return 1;
  }

  WaitForSingleObject(process.hProcess, INFINITE);
  DWORD exit_code = 1;
  GetExitCodeProcess(process.hProcess, &exit_code);
  CloseHandle(process.hProcess);
  CloseHandle(process.hThread);
  return static_cast<int>(exit_code);
}
