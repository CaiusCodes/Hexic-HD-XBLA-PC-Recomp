// Hexic HD PC - launcher: paths, install state, package
// detection and import, settings and extras. No window code here (setup_window.cpp).
#include "launcher.h"

#include <bcrypt.h>
#include <shlobj.h>
#include <tlhelp32.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <memory>
#include <set>

#include "resource.h"
#include "stfs.h"

namespace hexic {

const char* const kMarkerName = ".hexic-import-ok";

namespace {

// The port is a static recompilation of one specific build of the game
// program: its code is compiled into the game exe and the package supplies
// the data that build expects. Only a package carrying that exact build works.
constexpr uint32_t kTitleId = 0x584107D1;
constexpr uint32_t kContentType = 0x000D0000;  // Xbox LIVE Arcade title
constexpr const char* kXexSha256 = "EE18728AB4C4B45CC6D55F7917ABBB20B5D700C9410EAD400E2F687D51EFEEE0";
const wchar_t* const kRequiredGameFiles[] = {L"default.xex", L"g.xml", L"arcadeinfo.xml"};
const wchar_t* const kRuntimeFiles[] = {L"hexic_hd.exe", L"rexruntime.dll", L"rexgpu-xenos.dll",
                                        L"msvcp140.dll", L"vcruntime140.dll", L"vcruntime140_1.dll"};
const wchar_t* const kShortcutName = L"Hexic HD.lnk";
const wchar_t* const kShortcutDescription = L"Hexic HD (XBLA PC port)";

// Folder searches stay small: a few levels below the starting folder and a
// bounded number of entries, so a dropped drive root cannot stall setup.
constexpr int kSearchDepth = 6;
constexpr int kSearchEntryLimit = 20000;
constexpr int kHeaderCheckLimit = 400;

fs::path g_log_dir;

bool FileExists(const fs::path& path) {
  const DWORD attributes = GetFileAttributesW(path.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

bool DirExists(const fs::path& path) {
  const DWORD attributes = GetFileAttributesW(path.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

uint64_t FileSize(const fs::path& path) {
  WIN32_FILE_ATTRIBUTE_DATA data = {};
  if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &data)) return 0;
  return (uint64_t(data.nFileSizeHigh) << 32) | data.nFileSizeLow;
}

uint32_t BE32(const uint8_t* p) {
  return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3];
}

// --------------------------------------------------------------- SHA-256 --
class Sha256 {
 public:
  Sha256() {
    if (BCryptOpenAlgorithmProvider(&algorithm_, BCRYPT_SHA256_ALGORITHM, nullptr, 0) == 0)
      BCryptCreateHash(algorithm_, &hash_, nullptr, 0, nullptr, 0, 0);
  }
  ~Sha256() {
    if (hash_) BCryptDestroyHash(hash_);
    if (algorithm_) BCryptCloseAlgorithmProvider(algorithm_, 0);
  }
  void Add(const uint8_t* data, size_t size) {
    if (hash_) BCryptHashData(hash_, const_cast<PUCHAR>(data), static_cast<ULONG>(size), 0);
  }
  std::string Hex() {
    uint8_t digest[32] = {};
    if (!hash_ || BCryptFinishHash(hash_, digest, sizeof(digest), 0) != 0) return {};
    char text[65] = {};
    for (int i = 0; i < 32; ++i) snprintf(text + i * 2, 3, "%02X", digest[i]);
    return text;
  }

 private:
  BCRYPT_ALG_HANDLE algorithm_ = nullptr;
  BCRYPT_HASH_HANDLE hash_ = nullptr;
};

// The version a default.xex reports in its execution info header (0x00040006):
// e.g. "2.0.1884.0". Empty if the header is missing or the bytes are too short.
// Only used to tell a player which build they have; the SHA-256 decides.
constexpr const wchar_t* kXexVersion = L"2.0.1884.0";

std::wstring XexVersion(const std::vector<uint8_t>& x) {
  if (x.size() < 0x18 || memcmp(x.data(), "XEX2", 4) != 0) return {};
  const uint32_t count = BE32(&x[0x14]);
  for (uint32_t i = 0; i < count && i < 64; ++i) {
    const size_t at = 0x18 + size_t(i) * 8;
    if (at + 8 > x.size()) return {};
    if (BE32(&x[at]) != 0x00040006) continue;
    const size_t info = BE32(&x[at + 4]);
    if (info + 8 > x.size()) return {};
    const uint32_t v = BE32(&x[info + 4]);
    wchar_t text[48];
    swprintf(text, 48, L"%u.%u.%u.%u", v >> 28, (v >> 24) & 0xF, (v >> 8) & 0xFFFF, v & 0xFF);
    return text;
  }
  return {};
}

std::vector<uint8_t> ReadPrefix(const fs::path& path, size_t size) {
  std::vector<uint8_t> data(size);
  HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
  if (file == INVALID_HANDLE_VALUE) return {};
  DWORD got = 0;
  if (!ReadFile(file, data.data(), static_cast<DWORD>(size), &got, nullptr)) got = 0;
  CloseHandle(file);
  data.resize(got);
  return data;
}

// What a player is told when their game program is not the build this port
// was made from.
std::wstring WrongBuildMessage(const std::wstring& found, const wchar_t* where) {
  // Kept to two lines of the setup window's status text.
  if (found == kXexVersion)
    return std::wstring(where) + L" holds a modified or damaged copy of Hexic HD " + found +
           L". Copy it from your Xbox 360 again. Nothing was changed.";
  std::wstring text = std::wstring(where) + L" holds ";
  text += found.empty() ? L"a different build of Hexic HD" : L"Hexic HD version " + found;
  return text + L", but this port needs " + kXexVersion + L" (the Xbox Live Arcade release). Nothing was changed.";
}

std::string HashFile(const fs::path& path) {
  HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                            FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
  if (file == INVALID_HANDLE_VALUE) return {};
  Sha256 sha;
  std::vector<uint8_t> buffer(1 << 20);
  DWORD got = 0;
  while (ReadFile(file, buffer.data(), static_cast<DWORD>(buffer.size()), &got, nullptr) && got > 0)
    sha.Add(buffer.data(), got);
  CloseHandle(file);
  return sha.Hex();
}

// ------------------------------------------------------- embedded files --
std::string LoadText(int id) {
  HRSRC found = FindResourceW(nullptr, MAKEINTRESOURCEW(id), MAKEINTRESOURCEW(10));  // RT_RCDATA
  if (!found) return {};
  HGLOBAL loaded = LoadResource(nullptr, found);
  const char* data = loaded ? static_cast<const char*>(LockResource(loaded)) : nullptr;
  return data ? std::string(data, SizeofResource(nullptr, found)) : std::string();
}

std::vector<std::string> SplitLines(const std::string& text) {
  std::vector<std::string> lines;
  size_t start = 0;
  while (start < text.size()) {
    size_t end = text.find('\n', start);
    if (end == std::string::npos) end = text.size();
    std::string line = text.substr(start, end - start);
    if (!line.empty() && line.back() == '\r') line.pop_back();
    lines.push_back(line);
    start = end + 1;
  }
  return lines;
}

bool ReadAll(const fs::path& path, std::string* out) {
  HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                            OPEN_EXISTING, 0, nullptr);
  if (file == INVALID_HANDLE_VALUE) return false;
  const uint64_t size = FileSize(path);
  out->resize(static_cast<size_t>(size));
  DWORD got = 0;
  const bool ok = size == 0 || (ReadFile(file, out->data(), static_cast<DWORD>(size), &got, nullptr) && got == size);
  CloseHandle(file);
  return ok;
}

// Written to a temporary file first, then moved over the target, so a
// failure never leaves a half-written file behind.
bool WriteAll(const fs::path& path, const std::string& data) {
  const fs::path temp = path.wstring() + L".tmp";
  HANDLE file = CreateFileW(temp.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) return false;
  DWORD written = 0;
  const bool ok = data.empty() ||
                  (WriteFile(file, data.data(), static_cast<DWORD>(data.size()), &written, nullptr) &&
                   written == data.size());
  CloseHandle(file);
  if (!ok || !MoveFileExW(temp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
    DeleteFileW(temp.c_str());
    return false;
  }
  return true;
}

// --------------------------------------------------------- folder search --
struct Search {
  int entries = 0;
  int headers = 0;
};

void FindPackages(const fs::path& folder, int depth, Search& search, std::vector<Source>& out) {
  if (depth > kSearchDepth) return;
  std::error_code ec;
  fs::directory_iterator it(folder, fs::directory_options::skip_permission_denied, ec);
  std::vector<fs::path> subfolders;
  for (; !ec && it != fs::directory_iterator(); it.increment(ec)) {
    if (++search.entries > kSearchEntryLimit) return;
    const fs::directory_entry& entry = *it;
    std::error_code type_ec;
    if (entry.is_symlink(type_ec)) continue;  // never follow links out of the folder
    if (entry.is_directory(type_ec)) {
      subfolders.push_back(entry.path());
    } else if (entry.is_regular_file(type_ec) && search.headers < kHeaderCheckLimit) {
      const uint64_t size = entry.file_size(type_ec);
      if (size < 0xC000) continue;
      ++search.headers;
      std::wstring why;
      uint64_t bytes = 0;
      if (CheckPackageHeader(entry.path(), &why, &bytes)) out.push_back({SourceKind::Package, entry.path(), bytes});
    }
  }
  for (const fs::path& sub : subfolders) FindPackages(sub, depth + 1, search, out);
}

void AddUnique(std::vector<Source>& list, const Source& source) {
  for (const Source& s : list) {
    if (s.kind == source.kind && SameFile(s.path, source.path)) return;
  }
  list.push_back(source);
}

uint64_t FolderBytes(const fs::path& folder) {
  uint64_t total = 0;
  std::error_code ec;
  for (fs::recursive_directory_iterator it(folder, fs::directory_options::skip_permission_denied, ec), end;
       !ec && it != end; it.increment(ec)) {
    std::error_code type_ec;
    if (it->is_regular_file(type_ec)) total += it->file_size(type_ec);
  }
  return total;
}

// ------------------------------------------------------------------ copy --
// Copies one file in 1 MB pieces so a cancel is noticed quickly.
bool CopyOne(const fs::path& from, const fs::path& to, const std::atomic<bool>* cancel,
             const std::function<void(uint64_t)>& progress) {
  HANDLE in = CreateFileW(from.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                          FILE_FLAG_SEQUENTIAL_SCAN, nullptr);
  if (in == INVALID_HANDLE_VALUE) return false;
  HANDLE out = CreateFileW(to.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (out == INVALID_HANDLE_VALUE) {
    CloseHandle(in);
    return false;
  }
  std::vector<uint8_t> buffer(1 << 20);
  bool ok = true;
  DWORD got = 0;
  while (ok && ReadFile(in, buffer.data(), static_cast<DWORD>(buffer.size()), &got, nullptr) && got > 0) {
    DWORD written = 0;
    ok = WriteFile(out, buffer.data(), got, &written, nullptr) && written == got;
    if (progress) progress(got);
    if (cancel && cancel->load()) ok = false;
  }
  CloseHandle(in);
  CloseHandle(out);
  if (!ok) DeleteFileW(to.c_str());
  return ok;
}

// A previous install's saves and settings, copied into resources\userdata
// only when this folder has none yet (cache folders are left behind).
std::wstring MigrateUserData(const Paths& p, const fs::path& from) {
  std::error_code ec;
  fs::create_directories(p.userdata, ec);
  bool have_saves = false;
  for (fs::directory_iterator it(p.userdata, ec), end; !ec && it != end; it.increment(ec)) {
    if (_wcsicmp(it->path().filename().c_str(), L"cache") != 0 &&
        _wcsicmp(it->path().filename().c_str(), L"hexic_hd.toml") != 0)
      have_saves = true;
  }
  int copied = 0;
  const fs::path saves = UserDataIn(from);  // that install's chosen saves folder, if it had one
  if (!have_saves && DirExists(saves)) {
    for (fs::recursive_directory_iterator it(saves, fs::directory_options::skip_permission_denied, ec), end;
         !ec && it != end; it.increment(ec)) {
      const fs::path relative = it->path().lexically_relative(saves);
      if (!relative.empty() && _wcsicmp(relative.begin()->c_str(), L"cache") == 0) {
        if (it->is_directory()) it.disable_recursion_pending();
        continue;
      }
      const fs::path target = p.userdata / relative;
      std::error_code item_ec;
      if (it->is_directory(item_ec)) {
        fs::create_directories(target, item_ec);
      } else if (it->is_regular_file(item_ec) && !FileExists(target)) {
        fs::create_directories(target.parent_path(), item_ec);
        if (CopyOne(it->path(), target, nullptr, nullptr)) ++copied;
      }
    }
  }
  bool settings = false;
  if (!FileExists(p.config)) {
    for (const fs::path& old : {from / L"hexic_hd.toml", saves / L"hexic_hd.toml"}) {
      if (FileExists(old) && CopyOne(old, p.config, nullptr, nullptr)) {
        settings = true;
        break;
      }
    }
  }
  Log(L"Carried over from " + from.wstring() + L": " + std::to_wstring(copied) + L" save files" +
      (settings ? L" and hexic_hd.toml" : L""));
  if (copied == 0 && !settings) return L"";
  if (copied > 0 && settings) return L"Your saves and settings were carried over from your previous install.";
  return copied > 0 ? L"Your saves were carried over from your previous install."
                    : L"Your settings were carried over from your previous install.";
}

std::wstring Stats(int files, int total_files, uint64_t done, uint64_t total) {
  return std::to_wstring(files) + L" of " + std::to_wstring(total_files) + L" files  ·  " +
         FormatMB(done) + L" of " + FormatMB(total);
}

}  // namespace

// ================================================================ paths ==
namespace {
// The folder named in <resources>\userdata-location.txt; empty when there is none.
fs::path ReadUserDataPointer(const fs::path& resources) {
  HANDLE file = CreateFileW((resources / L"userdata-location.txt").c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                            OPEN_EXISTING, 0, nullptr);
  if (file == INVALID_HANDLE_VALUE) return {};
  char buffer[4096] = {};
  DWORD got = 0;
  ReadFile(file, buffer, sizeof(buffer) - 1, &got, nullptr);
  CloseHandle(file);
  std::string line(buffer, got);
  if (line.size() >= 3 && static_cast<unsigned char>(line[0]) == 0xEF) line.erase(0, 3);  // BOM
  const size_t end = line.find_first_of("\r\n");
  if (end != std::string::npos) line.resize(end);
  while (!line.empty() && line.back() == ' ') line.pop_back();
  return line.empty() ? fs::path() : fs::path(Widen(line));
}

bool IsInside(const fs::path& path, const fs::path& folder) {
  const std::wstring a = fs::weakly_canonical(path).wstring() + L"\\";
  const std::wstring b = fs::weakly_canonical(folder).wstring() + L"\\";
  return a.size() >= b.size() && _wcsnicmp(a.c_str(), b.c_str(), b.size()) == 0;
}
}  // namespace

fs::path UserDataIn(const fs::path& resources) {
  const fs::path custom = ReadUserDataPointer(resources);
  return custom.empty() ? resources / L"userdata" : custom;
}

bool SetUserDataLocation(Paths& p, const fs::path& folder, std::wstring* message) {
  const fs::path target = folder.empty() ? p.resources / L"userdata" : fs::path(folder).make_preferred();
  if (!folder.empty()) {
    if (!target.is_absolute()) return *message = L"Choose a full folder path for your saves.", false;
    if (IsInside(target, p.runtime) || IsInside(target, p.assets) || IsInside(p.resources, target) ||
        IsInside(target, p.resources / L".update") || IsInside(target, p.resources / L".import"))
      return *message = L"That folder holds the game itself. Choose a folder of its own for your saves.", false;
  }
  std::error_code ec;
  fs::create_directories(target, ec);
  const fs::path probe = target / L".hexic-write-test";
  HANDLE file = CreateFileW(probe.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, nullptr);
  if (file == INVALID_HANDLE_VALUE)
    return *message = L"Hexic HD can't write to " + target.wstring() + L". Choose a folder you can save files in.", false;
  CloseHandle(file);
  DeleteFileW(probe.c_str());

  // Copy what is there now (not the caches, which rebuild themselves).
  int copied = 0;
  if (!SameFile(target, p.userdata) && DirExists(p.userdata)) {
    for (fs::recursive_directory_iterator it(p.userdata, fs::directory_options::skip_permission_denied, ec), end;
         !ec && it != end; it.increment(ec)) {
      const fs::path relative = it->path().lexically_relative(p.userdata);
      if (!relative.empty() && _wcsicmp(relative.begin()->c_str(), L"cache") == 0) {
        if (it->is_directory()) it.disable_recursion_pending();
        continue;
      }
      const fs::path to = target / relative;
      std::error_code item_ec;
      if (it->is_directory(item_ec)) {
        fs::create_directories(to, item_ec);
      } else if (it->is_regular_file(item_ec) && !FileExists(to)) {
        fs::create_directories(to.parent_path(), item_ec);
        if (CopyOne(it->path(), to, nullptr, nullptr)) ++copied;
      }
    }
  }
  if (folder.empty()) {
    DeleteFileW(p.userdata_pointer.c_str());
  } else {
    const std::string line = Narrow(target.wstring()) + "\r\n";
    HANDLE out = CreateFileW(p.userdata_pointer.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    const bool ok = out != INVALID_HANDLE_VALUE && WriteFile(out, line.data(), DWORD(line.size()), &written, nullptr) &&
                    written == line.size();
    if (out != INVALID_HANDLE_VALUE) CloseHandle(out);
    if (!ok) return *message = L"Could not record the saves folder in resources (is the folder read-only?).", false;
  }
  const fs::path from = p.userdata;
  p.userdata = target;
  p.custom_userdata = !folder.empty();
  p.config = p.userdata / L"hexic_hd.toml";
  Log(L"Saves and settings folder: " + target.wstring() + L" (" + std::to_wstring(copied) + L" files copied from " +
      from.wstring() + L")");
  *message = copied ? L"Your saves and settings were copied to " + target.wstring() +
                          L". The old copy in " + from.wstring() + L" was left as it was."
                    : L"Saves and settings will be kept in " + target.wstring() + L".";
  return true;
}

Paths MakePaths() {
  std::vector<wchar_t> buffer(32768);
  const DWORD length = GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
  Paths p;
  p.launcher = fs::path(std::wstring(buffer.data(), length));
  p.root = p.launcher.parent_path();
  p.resources = p.root / L"resources";
  p.runtime = p.resources / L"runtime";
  p.game_exe = p.runtime / L"hexic_hd.exe";
  p.assets = p.resources / L"assets";
  p.userdata_pointer = p.resources / L"userdata-location.txt";
  p.userdata = UserDataIn(p.resources);
  p.custom_userdata = !ReadUserDataPointer(p.resources).empty();
  p.config = p.userdata / L"hexic_hd.toml";
  p.logs = p.runtime / L"logs";
  p.staging = p.resources / L".import";
  p.previous = p.resources / L".assets-previous";
  return p;
}

// ================================================================== log ==
void LogTo(const fs::path& logs_dir) { g_log_dir = logs_dir; }

void Log(const std::wstring& line) {
  if (g_log_dir.empty()) return;
  std::error_code ec;
  fs::create_directories(g_log_dir, ec);
  const fs::path file = g_log_dir / L"setup.log";
  if (FileSize(file) > (1u << 20)) MoveFileExW(file.c_str(), (g_log_dir / L"setup.old.log").c_str(), MOVEFILE_REPLACE_EXISTING);
  SYSTEMTIME now;
  GetLocalTime(&now);
  char stamp[64];
  snprintf(stamp, sizeof(stamp), "%04d-%02d-%02d %02d:%02d:%02d  ", now.wYear, now.wMonth, now.wDay, now.wHour,
           now.wMinute, now.wSecond);
  const std::string text = stamp + Narrow(line) + "\r\n";
  HANDLE handle = CreateFileW(file.c_str(), FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL, nullptr);
  if (handle == INVALID_HANDLE_VALUE) return;
  DWORD written = 0;
  WriteFile(handle, text.data(), static_cast<DWORD>(text.size()), &written, nullptr);
  CloseHandle(handle);
}

// ================================================================ state ==
bool IsInstalled(const Paths& p, std::wstring* missing) {
  for (const wchar_t* name : kRuntimeFiles) {
    if (!FileExists(p.runtime / name)) {
      *missing = L"resources\\runtime\\" + std::wstring(name);
      return false;
    }
  }
  if (!FileExists(p.assets / kMarkerName)) {
    *missing = L"resources\\assets (no finished import)";
    return false;
  }
  for (const wchar_t* name : kRequiredGameFiles) {
    if (!FileExists(p.assets / name)) {
      *missing = L"resources\\assets\\" + std::wstring(name);
      return false;
    }
  }
  return true;
}

void RecoverInterruptedSwap(const Paths& p) {
  if (!DirExists(p.previous)) return;
  if (!FileExists(p.assets / kMarkerName) && FileExists(p.previous / kMarkerName)) {
    std::error_code ec;
    if (DirExists(p.assets)) fs::remove_all(p.assets, ec);
    if (MoveFileExW(p.previous.c_str(), p.assets.c_str(), 0)) Log(L"Restored resources\\assets from an interrupted import.");
    return;
  }
  if (FileExists(p.assets / kMarkerName)) {
    std::error_code ec;
    fs::remove_all(p.previous, ec);
  }
}

bool GameRunning(const Paths& p) {
  HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (snapshot == INVALID_HANDLE_VALUE) return false;
  PROCESSENTRY32W entry = {sizeof(entry)};
  bool running = false;
  for (BOOL more = Process32FirstW(snapshot, &entry); more && !running; more = Process32NextW(snapshot, &entry)) {
    if (_wcsicmp(entry.szExeFile, L"hexic_hd.exe") != 0) continue;
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, entry.th32ProcessID);
    if (!process) continue;
    wchar_t image[32768];
    DWORD size = 32768;
    if (QueryFullProcessImageNameW(process, 0, image, &size) && _wcsicmp(image, p.game_exe.c_str()) == 0)
      running = true;
    CloseHandle(process);
  }
  CloseHandle(snapshot);
  return running;
}

// ============================================================== sources ==
std::wstring Describe(const Source& s) {
  if (s.kind == SourceKind::PreviousInstall) return L"Previous install: " + s.path.wstring();
  return s.path.wstring();
}

bool CheckPackageHeader(const fs::path& file, std::wstring* why, uint64_t* bytes) {
  HANDLE handle = CreateFileW(file.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, nullptr);
  if (handle == INVALID_HANDLE_VALUE) {
    *why = L"The selected file could not be opened.";
    return false;
  }
  uint8_t header[0x1000] = {};
  DWORD got = 0;
  LARGE_INTEGER size = {};
  const bool read = GetFileSizeEx(handle, &size) && ReadFile(handle, header, sizeof(header), &got, nullptr);
  CloseHandle(handle);
  *bytes = static_cast<uint64_t>(size.QuadPart);
  if (!read || got < sizeof(header) || size.QuadPart < 0xC000) {
    *why = L"This file is too small to be an Xbox 360 package.";
    return false;
  }
  if (memcmp(header, "LIVE", 4) != 0 && memcmp(header, "PIRS", 4) != 0 && memcmp(header, "CON ", 4) != 0) {
    *why = L"This is not an Xbox 360 package. Choose the Hexic HD package file itself.";
    return false;
  }
  const uint32_t title = BE32(header + 0x360);
  if (title != kTitleId) {
    wchar_t text[160];
    swprintf(text, 160, L"This package is for a different game (title ID %08X). Hexic HD is 584107D1.", title);
    *why = text;
    return false;
  }
  if (BE32(header + 0x344) != kContentType) {
    *why = L"This Hexic HD package is not the game itself (it may be a title update, save or theme).";
    return false;
  }
  return true;
}

bool CheckPreviousInstall(const fs::path& folder, fs::path* game_dir, uint64_t* bytes) {
  // A previous release folder, its Game folder (0.4.41 to 0.9.x), or another
  // copy of this release (its resources folder).
  for (const fs::path& dir : {folder, folder / L"Game", folder / L"resources"}) {
    if (!FileExists(dir / L"assets" / L"default.xex")) continue;
    bool complete = true;
    for (const wchar_t* name : kRequiredGameFiles) complete = complete && FileExists(dir / L"assets" / name);
    if (!complete) continue;
    *game_dir = dir;
    *bytes = 0;
    return true;
  }
  return false;
}

std::vector<Source> SourcesIn(const fs::path& chosen, std::wstring* why) {
  std::vector<Source> found;
  std::error_code ec;
  const fs::path path = fs::absolute(chosen, ec);
  if (FileExists(path)) {
    uint64_t bytes = 0;
    if (CheckPackageHeader(path, why, &bytes)) found.push_back({SourceKind::Package, path, bytes});
    return found;
  }
  if (!DirExists(path)) {
    *why = L"The selected file or folder could not be found.";
    return found;
  }
  fs::path game_dir;
  uint64_t bytes = 0;
  if (CheckPreviousInstall(path, &game_dir, &bytes)) {
    if (SameFile(game_dir, MakePaths().resources)) {
      *why = L"That is this copy's own game data. Choose your Xbox 360 package instead.";
      return found;
    }
    found.push_back({SourceKind::PreviousInstall, game_dir, FolderBytes(game_dir / L"assets")});
    return found;
  }
  Search search;
  std::vector<Source> packages;
  FindPackages(path, 0, search, packages);
  for (const Source& s : packages) AddUnique(found, s);
  if (found.empty()) *why = L"No Hexic HD package was found in that folder.";
  return found;
}

std::vector<Source> DetectSources(const Paths& p) {
  std::vector<Source> found;
  Search search;
  std::error_code ec;
  // The launcher's own folder: its files, then every folder beside the
  // launcher ("Game Package" and the like) a few levels deep.
  std::vector<fs::path> folders;
  for (fs::directory_iterator it(p.root, fs::directory_options::skip_permission_denied, ec), end; !ec && it != end;
       it.increment(ec)) {
    std::error_code type_ec;
    if (it->is_symlink(type_ec)) continue;
    const std::wstring name = it->path().filename().wstring();
    if (it->is_directory(type_ec)) {
      if (_wcsicmp(name.c_str(), L"resources") == 0 || _wcsicmp(name.c_str(), L"licenses") == 0) continue;
      if (_wcsicmp(name.c_str(), L"Game Package") == 0)
        folders.insert(folders.begin(), it->path());
      else
        folders.push_back(it->path());
    } else if (it->is_regular_file(type_ec) && it->file_size(type_ec) >= 0xC000) {
      std::wstring why;
      uint64_t bytes = 0;
      if (CheckPackageHeader(it->path(), &why, &bytes)) AddUnique(found, {SourceKind::Package, it->path(), bytes});
    }
  }
  for (const fs::path& folder : folders) {
    fs::path game_dir;
    uint64_t bytes = 0;
    if (CheckPreviousInstall(folder, &game_dir, &bytes)) {
      AddUnique(found, {SourceKind::PreviousInstall, game_dir, 0});
      continue;  // an install's own files are not searched for packages
    }
    std::vector<Source> packages;
    FindPackages(folder, 1, search, packages);
    for (const Source& s : packages) AddUnique(found, s);
  }
  // Previous releases in sibling folders (extracted next to this one).
  const fs::path previous = FindPreviousInstall(p);
  if (!previous.empty()) AddUnique(found, {SourceKind::PreviousInstall, previous, 0});
  for (Source& s : found) {
    if (s.kind == SourceKind::PreviousInstall && s.bytes == 0) s.bytes = FolderBytes(s.path / L"assets");
  }
  return found;
}

fs::path FindPreviousInstall(const Paths& p) {
  fs::path game_dir;
  uint64_t bytes = 0;
  if (CheckPreviousInstall(p.root / L"Game", &game_dir, &bytes)) return game_dir;
  // The earliest portable builds kept the game data in the folder itself.
  if (FileExists(p.root / L"assets" / L"default.xex") && CheckPreviousInstall(p.root, &game_dir, &bytes) &&
      !SameFile(game_dir, p.resources))
    return game_dir;
  const fs::path parent = p.root.parent_path();
  if (parent.empty() || parent == p.root) return {};
  // This release extracted inside an old release folder (beside its Setup and Game).
  if (FileExists(parent / L"Install Hexic HD.exe") && CheckPreviousInstall(parent / L"Game", &game_dir, &bytes))
    return game_dir;
  if (FileExists(parent / L"Hexic HD.exe") && FileExists(parent / L"assets" / L"default.xex") &&
      CheckPreviousInstall(parent, &game_dir, &bytes) && !SameFile(game_dir, parent / L"resources"))
    return game_dir;
  std::error_code ec;
  int checked = 0;
  for (fs::directory_iterator it(parent, fs::directory_options::skip_permission_denied, ec), end;
       !ec && it != end && checked < 200; it.increment(ec), ++checked) {
    std::error_code type_ec;
    if (!it->is_directory(type_ec) || it->is_symlink(type_ec) || SameFile(it->path(), p.root)) continue;
    // Only release folders: an old one has Setup beside Game, a new one this launcher.
    const bool old_release = FileExists(it->path() / L"Install Hexic HD.exe");
    const bool new_release = FileExists(it->path() / L"Hexic HD.exe");
    if (!old_release && !new_release) continue;
    for (const fs::path& dir : {it->path() / L"Game", it->path() / L"resources", it->path()}) {
      if (FileExists(dir / L"assets" / L"default.xex") && CheckPreviousInstall(dir, &game_dir, &bytes)) return game_dir;
    }
  }
  return {};
}

// =============================================================== import ==
ImportResult Import(const Paths& p, const Source& source, const fs::path& saves_from,
                    const std::atomic<bool>& cancel, const Report& report) {
  ImportResult result;
  auto step = [&](int percent, const wchar_t* phase, const std::wstring& detail) {
    if (report) report(percent, phase, detail);
  };
  auto fail = [&](const std::wstring& message) {
    result.message = message;
    Log(L"FAILED: " + message);
    return result;
  };
  Log(std::wstring(L"Import ") + kVersion + L" from " + Describe(source));

  for (const wchar_t* name : kRuntimeFiles) {
    if (!FileExists(p.runtime / name))
      return fail(L"This download is incomplete (resources\\runtime\\" + std::wstring(name) +
                  L" is missing). Extract the whole ZIP again.");
  }
  if (GameRunning(p)) return fail(L"Hexic HD is running from this folder. Close the game, then try again.");
  RecoverInterruptedSwap(p);

  std::error_code ec;
  fs::remove_all(p.staging, ec);
  fs::create_directories(p.staging, ec);
  if (ec) return fail(L"Could not create resources\\.import. Make sure this folder is writable (not inside Program Files).");

  // Anything that stops before the swap leaves only the staging folder, removed here.
  struct Cleanup {
    const fs::path& staging;
    bool keep = false;
    ~Cleanup() {
      if (!keep) {
        std::error_code ignored;
        fs::remove_all(staging, ignored);
      }
    }
  } cleanup{p.staging};

  auto cancelled = [&]() {
    result.cancelled = true;
    result.message = L"Import cancelled. Nothing was changed.";
    Log(L"Cancelled.");
    return result;
  };

  // 1. Is this the build the port was compiled from? Checked before anything is unpacked.
  step(1, L"CHECKING YOUR PACKAGE", L"Checking the game build" + std::wstring(L"…"));
  std::unique_ptr<stfs::Package> package;
  uint64_t total = 0;
  int total_files = 0;
  std::vector<fs::path> previous_files;
  const fs::path previous_assets = source.path / L"assets";
  if (source.kind == SourceKind::Package) {
    std::wstring why;
    uint64_t bytes = 0;
    if (!CheckPackageHeader(source.path, &why, &bytes)) return fail(why);
    package = std::make_unique<stfs::Package>();
    if (!package->Open(source.path.wstring(), &why)) return fail(why);
    for (const wchar_t* name : kRequiredGameFiles) {
      if (!package->Find(name))
        return fail(L"This package does not contain " + std::wstring(name) + L". It may be damaged or incomplete.");
    }
    Sha256 sha;
    std::vector<uint8_t> head;  // the first 64 KB, for the version in its header
    if (!package->Read(*package->Find(L"default.xex"),
                       [&](const uint8_t* d, size_t n) {
                         sha.Add(d, n);
                         if (head.size() < 0x10000) head.insert(head.end(), d, d + (std::min)(n, 0x10000 - head.size()));
                         return true;
                       },
                       &why))
      return fail(why);
    const std::string hash = sha.Hex();
    const std::wstring version = XexVersion(head);
    Log(L"default.xex SHA-256 " + Widen(hash) + L", version " + (version.empty() ? L"unknown" : version));
    if (hash != kXexSha256) return fail(WrongBuildMessage(version, L"This package"));
    total = package->total_file_bytes();
    for (const stfs::Entry& e : package->entries()) total_files += e.directory ? 0 : 1;
  } else {
    for (const wchar_t* name : kRequiredGameFiles) {
      if (!FileExists(previous_assets / name))
        return fail(L"The previous install is missing " + std::wstring(name) + L". Choose your Xbox 360 package instead.");
    }
    const std::string hash = HashFile(previous_assets / L"default.xex");
    const std::wstring version = XexVersion(ReadPrefix(previous_assets / L"default.xex", 0x10000));
    Log(L"previous default.xex SHA-256 " + Widen(hash) + L", version " + (version.empty() ? L"unknown" : version));
    if (hash != kXexSha256) return fail(WrongBuildMessage(version, L"The previous install"));
    for (fs::recursive_directory_iterator it(previous_assets, fs::directory_options::skip_permission_denied, ec), end;
         !ec && it != end; it.increment(ec)) {
      std::error_code type_ec;
      if (it->is_regular_file(type_ec) && it->path().filename() != kMarkerName) {
        previous_files.push_back(it->path());
        total += it->file_size(type_ec);
      }
    }
    total_files = static_cast<int>(previous_files.size());
  }
  if (cancel.load()) return cancelled();

  ULARGE_INTEGER free_bytes = {};
  if (GetDiskFreeSpaceExW(p.resources.c_str(), &free_bytes, nullptr, nullptr) &&
      free_bytes.QuadPart < total + (64ull << 20))
    return fail(L"There is not enough free disk space here. The game data needs about " + FormatMB(total) +
                L"; " + FormatMB(free_bytes.QuadPart) + L" is free.");

  // 2. Unpack (or copy) into the staging folder.
  uint64_t done = 0;
  int files = 0;
  uint64_t last_report = 0;
  auto progress = [&](uint64_t add) {
    done += add;
    if (done - last_report >= (4u << 20) || done == total) {
      last_report = done;
      const int percent = 5 + static_cast<int>(80.0 * (total ? double(done) / double(total) : 1.0));
      step(percent, L"IMPORTING YOUR GAME DATA", Stats(files, total_files, done, total));
    }
  };
  step(5, L"IMPORTING YOUR GAME DATA", Stats(0, total_files, 0, total));
  if (package) {
    std::vector<uint8_t> buffer;
    buffer.reserve(1 << 20);
    for (const stfs::Entry& entry : package->entries()) {
      const fs::path target = p.staging / entry.path;
      if (entry.directory) {
        fs::create_directories(target, ec);
        continue;
      }
      fs::create_directories(target.parent_path(), ec);
      HANDLE out = CreateFileW(target.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
      if (out == INVALID_HANDLE_VALUE) return fail(L"Could not write " + target.wstring() + L".");
      bool write_ok = true;
      auto flush = [&]() {
        DWORD written = 0;
        write_ok = write_ok && (buffer.empty() ||
                                (WriteFile(out, buffer.data(), static_cast<DWORD>(buffer.size()), &written, nullptr) &&
                                 written == buffer.size()));
        buffer.clear();
      };
      std::wstring why;
      const bool read_ok = package->Read(
          entry,
          [&](const uint8_t* data, size_t size) {
            buffer.insert(buffer.end(), data, data + size);
            if (buffer.size() >= (1u << 20)) flush();
            progress(size);
            return write_ok && !cancel.load();
          },
          &why);
      flush();
      CloseHandle(out);
      if (cancel.load()) return cancelled();
      if (!read_ok) return fail(why.empty() ? L"Could not unpack " + entry.path + L"." : why);
      if (!write_ok) return fail(L"Could not write " + target.wstring() + L". Is the disk full?");
      ++files;
    }
    package.reset();  // the package is closed before anything else happens
  } else {
    for (const fs::path& file : previous_files) {
      const fs::path target = p.staging / file.lexically_relative(previous_assets);
      fs::create_directories(target.parent_path(), ec);
      if (!CopyOne(file, target, &cancel, progress)) {
        if (cancel.load()) return cancelled();
        return fail(L"Could not copy " + file.wstring() + L".");
      }
      ++files;
    }
  }
  if (cancel.load()) return cancelled();

  // 3. The unpacked copy must still be the right build.
  step(88, L"CHECKING THE GAME DATA", L"Verifying the imported files" + std::wstring(L"…"));
  for (const wchar_t* name : kRequiredGameFiles) {
    if (!FileExists(p.staging / name)) return fail(L"After importing, " + std::wstring(name) + L" is missing.");
  }
  if (HashFile(p.staging / L"default.xex") != kXexSha256)
    return fail(L"The imported default.xex does not match the package. The disk may be failing; try again.");

  // 4. PC wording in the menus. A failure only leaves the Xbox wording.
  step(92, L"PREPARING THE MENUS", L"Settings, High Scores and Quit Hexic");
  for (const std::wstring& line : PatchPcMenus(p.staging)) Log(line);

  // 5. The marker goes in last, so only a complete copy is ever "installed".
  const std::string marker = "version = " + Narrow(kVersion) + "\nsource = " + Narrow(Describe(source)) +
                             "\ndefault_xex_sha256 = " + kXexSha256 + "\n";
  if (!WriteAll(p.staging / kMarkerName, marker)) return fail(L"Could not write to resources\\.import.");
  if (cancel.load()) return cancelled();

  // 6. Swap the folders. From here on cancelling is no longer offered.
  step(96, L"MOVING THE GAME DATA INTO PLACE", L"");
  fs::remove_all(p.previous, ec);
  if (DirExists(p.assets) && !MoveFileExW(p.assets.c_str(), p.previous.c_str(), 0))
    return fail(L"The old game data in resources\\assets could not be replaced. Close anything using it and try again.");
  if (!MoveFileExW(p.staging.c_str(), p.assets.c_str(), 0)) {
    if (DirExists(p.previous)) MoveFileExW(p.previous.c_str(), p.assets.c_str(), 0);
    return fail(L"The imported game data could not be moved into resources\\assets.");
  }
  cleanup.keep = true;
  fs::remove_all(p.previous, ec);

  // 7. Saves and settings.
  fs::create_directories(p.userdata, ec);
  if (!saves_from.empty()) result.migrated = MigrateUserData(p, saves_from);
  EnsureSettings(p);

  step(100, L"READY FOR DUTY", L"");
  Log(L"Import finished.");
  result.ok = true;
  return result;
}

// ============================================================= settings ==
bool ReadConfig(const Paths& p, const std::string& key, std::string* value) {
  std::string text;
  if (!ReadAll(p.config, &text)) return false;
  for (const std::string& line : SplitLines(text)) {
    size_t i = line.find_first_not_of(" \t");
    if (i == std::string::npos || line.compare(i, key.size(), key) != 0) continue;
    size_t j = line.find_first_not_of(" \t", i + key.size());
    if (j == std::string::npos || line[j] != '=') continue;
    std::string v = line.substr(j + 1);
    v.erase(0, v.find_first_not_of(" \t"));
    while (!v.empty() && (v.back() == ' ' || v.back() == '\t')) v.pop_back();
    if (v.size() >= 2 && v.front() == '"' && v.back() == '"') v = v.substr(1, v.size() - 2);
    *value = v;
    return true;
  }
  return false;
}

bool WriteConfig(const Paths& p, const std::string& key, const std::string& value) {
  std::string text;
  ReadAll(p.config, &text);
  std::vector<std::string> lines = SplitLines(text);
  bool found = false;
  for (std::string& line : lines) {
    size_t i = line.find_first_not_of(" \t");
    if (i == std::string::npos || line.compare(i, key.size(), key) != 0) continue;
    size_t j = line.find_first_not_of(" \t", i + key.size());
    if (j == std::string::npos || line[j] != '=') continue;
    line = key + " = " + value;
    found = true;
  }
  if (!found) lines.push_back(key + " = " + value);
  std::string out;
  for (const std::string& line : lines) out += line + "\n";
  std::error_code ec;
  fs::create_directories(p.config.parent_path(), ec);
  return WriteAll(p.config, out);
}

// ------------------------------------------------------------- language --
namespace {
struct LanguageDef {
  const char* code;
  const wchar_t* name;
};
// Same order and names as the game's (src/hexic_language.h).
constexpr LanguageDef kLanguageDefs[] = {
    {"auto", L"Auto"},        {"en", L"English"},          {"de", L"Deutsch"},  {"es", L"Español"},
    {"fr", L"Français"}, {"it", L"Italiano"},         {"pt", L"Português"}, {"ja", L"Japanese"},
    {"ko", L"Korean"},        {"zh", L"Chinese"},
};
}  // namespace

int LanguageCount() { return static_cast<int>(sizeof(kLanguageDefs) / sizeof(kLanguageDefs[0])); }
const char* LanguageCode(int index) { return kLanguageDefs[index].code; }
const wchar_t* LanguageName(int index) { return kLanguageDefs[index].name; }

int LanguageIndex(const std::string& code) {
  for (int i = 0; i < LanguageCount(); ++i) {
    if (_stricmp(code.c_str(), kLanguageDefs[i].code) == 0) return i;
  }
  return -1;
}

int AutoLanguageIndex() {
  switch (PRIMARYLANGID(GetUserDefaultUILanguage())) {
    case LANG_GERMAN: return LanguageIndex("de");
    case LANG_SPANISH: return LanguageIndex("es");
    case LANG_FRENCH: return LanguageIndex("fr");
    case LANG_ITALIAN: return LanguageIndex("it");
    case LANG_PORTUGUESE: return LanguageIndex("pt");
    case LANG_JAPANESE: return LanguageIndex("ja");
    case LANG_KOREAN: return LanguageIndex("ko");
    case LANG_CHINESE: return LanguageIndex("zh");
    default: return LanguageIndex("en");
  }
}

int CurrentLanguage(const Paths& p) {
  std::string value;
  if (!ReadConfig(p, "hexic_language", &value)) return 0;
  const int index = LanguageIndex(value);
  return index < 0 ? 0 : index;
}

bool SetLanguage(const Paths& p, int index) {
  if (index < 0 || index >= LanguageCount()) return false;
  Log(L"Language: " + Widen(LanguageCode(index)));
  return WriteConfig(p, "hexic_language", std::string("\"") + LanguageCode(index) + "\"");
}

void EnsureSettings(const Paths& p) {
  std::error_code ec;
  fs::create_directories(p.userdata, ec);
  if (!FileExists(p.config)) {
    std::string defaults = LoadText(IDR_DEFAULT_CONFIG);
    if (!defaults.empty() && WriteAll(p.config, defaults)) Log(L"Wrote the default hexic_hd.toml.");
  }
}

// =============================================================== extras ==
namespace {

fs::path ShortcutPath(const fs::path& folder) {
  if (!folder.empty()) return folder / kShortcutName;
  PWSTR desktop = nullptr;
  fs::path path;
  if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &desktop))) path = fs::path(desktop) / kShortcutName;
  CoTaskMemFree(desktop);
  return path;
}

// Reads a shortcut's target and description. False if it cannot be read.
bool ReadShortcut(const fs::path& link, std::wstring* target, std::wstring* description) {
  IShellLinkW* shell_link = nullptr;
  if (FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shell_link)))) return false;
  IPersistFile* file = nullptr;
  bool ok = false;
  if (SUCCEEDED(shell_link->QueryInterface(IID_PPV_ARGS(&file)))) {
    if (SUCCEEDED(file->Load(link.c_str(), STGM_READ))) {
      wchar_t buffer[MAX_PATH * 4] = {};
      // SLGP_RAWPATH: the stored path, without resolving (and searching for) a moved target.
      if (SUCCEEDED(shell_link->GetPath(buffer, MAX_PATH * 4, nullptr, SLGP_RAWPATH))) *target = buffer;
      buffer[0] = 0;
      shell_link->GetDescription(buffer, MAX_PATH * 4);
      *description = buffer;
      ok = true;
    }
    file->Release();
  }
  shell_link->Release();
  return ok;
}

bool WriteShortcut(const Paths& p, const fs::path& link) {
  IShellLinkW* shell_link = nullptr;
  if (FAILED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&shell_link)))) return false;
  shell_link->SetPath(p.launcher.c_str());
  shell_link->SetWorkingDirectory(p.root.c_str());
  shell_link->SetIconLocation(p.launcher.c_str(), 0);
  shell_link->SetDescription(kShortcutDescription);
  IPersistFile* file = nullptr;
  bool ok = false;
  if (SUCCEEDED(shell_link->QueryInterface(IID_PPV_ARGS(&file)))) {
    ok = SUCCEEDED(file->Save(link.c_str(), TRUE));
    file->Release();
  }
  shell_link->Release();
  return ok;
}

bool OurShortcut(const Paths& p, const fs::path& link) {
  std::wstring target, description;
  return FileExists(link) && ReadShortcut(link, &target, &description) &&
         _wcsicmp(target.c_str(), p.launcher.c_str()) == 0;
}

}  // namespace

Extras CurrentExtras(const Paths& p, const fs::path& shortcut_folder) {
  Extras e;
  std::string value;
  // fullscreen is off unless hexic_hd.toml says so (the game drops the key
  // when it is switched back off, so a missing key means windowed).
  e.fullscreen = ReadConfig(p, "fullscreen", &value) && value == "true";
  e.shortcut = OurShortcut(p, ShortcutPath(shortcut_folder));
  return e;
}

std::wstring ApplyExtras(const Paths& p, const Extras& want, const Extras& was, const fs::path& shortcut_folder,
                         const std::function<bool(const fs::path&)>& ask_replace) {
  std::wstring note;
  EnsureSettings(p);
  // Only the one key per extra is written; every other setting stays as it is.
  if (want.fullscreen != was.fullscreen) {
    WriteConfig(p, "fullscreen", want.fullscreen ? "true" : "false");
    Log(std::wstring(L"Extra fullscreen: ") + (want.fullscreen ? L"on" : L"off"));
  }
  if (want.shortcut != was.shortcut) {
    const fs::path link = ShortcutPath(shortcut_folder);
    if (link.empty()) {
      note = L"The desktop folder could not be found, so no shortcut was made.";
    } else if (want.shortcut) {
      bool write = true;
      if (FileExists(link) && !OurShortcut(p, link)) write = ask_replace && ask_replace(link);
      if (!write) {
        note = L"A different Hexic HD shortcut is already on your desktop, so it was left as it is.";
        Log(L"Desktop shortcut: kept the existing one at " + link.wstring());
      } else if (!WriteShortcut(p, link)) {
        note = L"The desktop shortcut could not be created.";
      } else {
        Log(L"Desktop shortcut: " + link.wstring());
      }
    } else if (OurShortcut(p, link)) {
      DeleteFileW(link.c_str());
      Log(L"Desktop shortcut removed.");
    }
  }
  return note;
}

void RepairShortcut(const Paths& p, const fs::path& shortcut_folder) {
  const fs::path link = ShortcutPath(shortcut_folder);
  std::wstring target, description;
  if (link.empty() || !FileExists(link) || !ReadShortcut(link, &target, &description)) return;
  // Ours (by its description), aimed at a Hexic HD.exe that is no longer there:
  // the folder was moved, so point it here.
  if (description != kShortcutDescription || FileExists(target)) return;
  if (_wcsicmp(fs::path(target).filename().c_str(), L"Hexic HD.exe") != 0) return;
  if (WriteShortcut(p, link)) Log(L"Desktop shortcut updated for the moved folder.");
}

// ================================================================= game ==
bool LaunchGame(const Paths& p, const std::wstring& args, std::wstring* error) {
  std::wstring command = Quote(p.game_exe.wstring());
  if (!args.empty()) command += L" " + args;
  STARTUPINFOW startup = {sizeof(startup)};
  PROCESS_INFORMATION process = {};
  if (!CreateProcessW(p.game_exe.c_str(), command.data(), nullptr, nullptr, FALSE, 0, nullptr, p.runtime.c_str(),
                      &startup, &process)) {
    *error = L"Hexic HD could not be started (error " + std::to_wstring(GetLastError()) + L").";
    return false;
  }
  // Let the game take the foreground from the launcher.
  AllowSetForegroundWindow(process.dwProcessId);
  CloseHandle(process.hThread);
  CloseHandle(process.hProcess);
  return true;
}

// ================================================================ utils ==
std::wstring FormatMB(uint64_t bytes) {
  std::wstring digits = std::to_wstring((bytes + (1u << 19)) >> 20);
  for (int i = static_cast<int>(digits.size()) - 3; i > 0; i -= 3) digits.insert(i, L",");
  return digits + L" MB";
}

std::wstring Quote(const std::wstring& s) {
  std::wstring out = L"\"";
  size_t slashes = 0;
  for (wchar_t c : s) {
    if (c == L'\\') {
      ++slashes;
      continue;
    }
    out.append(c == L'"' ? slashes * 2 + 1 : slashes, L'\\');
    slashes = 0;
    out += c;
  }
  out.append(slashes * 2, L'\\');
  return out + L"\"";
}

std::wstring Widen(const std::string& s) {
  if (s.empty()) return {};
  const int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), nullptr, 0);
  std::wstring out(n, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), out.data(), n);
  return out;
}

std::string Narrow(const std::wstring& s) {
  if (s.empty()) return {};
  const int n = WideCharToMultiByte(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), nullptr, 0, nullptr, nullptr);
  std::string out(n, '\0');
  WideCharToMultiByte(CP_UTF8, 0, s.data(), static_cast<int>(s.size()), out.data(), n, nullptr, nullptr);
  return out;
}

bool SameFile(const fs::path& a, const fs::path& b) {
  std::error_code ec;
  if (fs::equivalent(a, b, ec)) return true;
  return _wcsicmp(fs::absolute(a, ec).lexically_normal().c_str(), fs::absolute(b, ec).lexically_normal().c_str()) == 0;
}

}  // namespace hexic
