// Hexic HD PC - updating the program files ("Hexic HD.exe --update").
//
// Opened by the game's Settings > Updates > Check for Updates once the player
// chose Update (the game closes itself first); shown in the setup window's
// update mode (setup_window.cpp). Ported from Perfect Dark XBLA PC Recomp's
// launcher update.cpp.
//
// It asks GitHub for the latest release (src/hexic_update.h), downloads its ZIP
// into resources\.update, checks the SHA-256 GitHub gives for it, unpacks it
// (CRC checked, unsafe names refused), checks it is a Hexic HD release and
// replaces the program files: Hexic HD.exe, README.txt, licenses\ and
// resources\runtime\ (not runtime\logs). resources\assets (the imported game
// data) and resources\userdata (saves, high scores, settings, caches) are never
// touched.
//
// The replacement is two steps per file, so a failure can be undone: every new
// file is first written beside its target as <name>.update-new; then each
// target becomes <name>.update-old and the new file takes its name. Any error
// in the second step renames everything back. The old files are deleted
// afterwards; one still in use (this launcher's own exe) is deleted at the next
// start, where an update cut off half-way is also put back
// (RecoverInterruptedUpdate).
#include "launcher.h"

#include <algorithm>

#include "../../src/hexic_update.h"

namespace hexic {
namespace {

const wchar_t kNewSuffix[] = L".update-new";
const wchar_t kOldSuffix[] = L".update-old";

// ---------------------------------------------------------------- ZIP --
uint32_t Crc32(const unsigned char* data, size_t size) {
  static uint32_t table[256];
  static bool ready = false;
  if (!ready) {
    for (uint32_t i = 0; i < 256; ++i) {
      uint32_t c = i;
      for (int k = 0; k < 8; ++k) c = c & 1 ? 0xEDB88320u ^ (c >> 1) : c >> 1;
      table[i] = c;
    }
    ready = true;
  }
  uint32_t c = 0xFFFFFFFFu;
  for (size_t i = 0; i < size; ++i) c = table[(c ^ data[i]) & 0xFF] ^ (c >> 8);
  return c ^ 0xFFFFFFFFu;
}

uint16_t Le16(const unsigned char* p) { return uint16_t(p[0] | p[1] << 8); }
uint32_t Le32(const unsigned char* p) { return uint32_t(p[0] | p[1] << 8 | p[2] << 16) | uint32_t(p[3]) << 24; }

bool ReadFileAll(const fs::path& path, std::vector<unsigned char>& out) {
  HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
  if (file == INVALID_HANDLE_VALUE) return false;
  LARGE_INTEGER size{};
  bool ok = GetFileSizeEx(file, &size) && size.QuadPart < (1ll << 31);
  if (ok) {
    out.resize(size_t(size.QuadPart));
    DWORD got = 0;
    ok = ReadFile(file, out.data(), DWORD(out.size()), &got, nullptr) && got == out.size();
  }
  CloseHandle(file);
  return ok;
}

bool WriteFileAll(const fs::path& path, const unsigned char* data, size_t size) {
  std::error_code ec;
  fs::create_directories(path.parent_path(), ec);
  HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) return false;
  DWORD written = 0;
  const bool ok = WriteFile(file, data, DWORD(size), &written, nullptr) && written == size;
  CloseHandle(file);
  return ok;
}

// Unpacks a ZIP (stored or deflated entries) under `dest`. Names that would
// leave `dest` are refused.
bool ExtractZip(const fs::path& zip, const fs::path& dest, std::wstring* error) {
  std::vector<unsigned char> data;
  if (!ReadFileAll(zip, data) || data.size() < 22) return *error = L"the download could not be read", false;
  size_t eocd = std::string::npos;
  for (size_t i = data.size() - 22;; --i) {
    if (Le32(&data[i]) == 0x06054B50) {
      eocd = i;
      break;
    }
    if (i == 0 || data.size() - i > 65557) break;
  }
  if (eocd == std::string::npos) return *error = L"the download is not a ZIP", false;
  const uint16_t count = Le16(&data[eocd + 10]);
  size_t at = Le32(&data[eocd + 16]);
  std::vector<uint8_t> file;
  for (uint16_t n = 0; n < count; ++n) {
    if (at + 46 > data.size() || Le32(&data[at]) != 0x02014B50) return *error = L"the ZIP is damaged", false;
    const uint16_t method = Le16(&data[at + 10]);
    const uint32_t crc = Le32(&data[at + 16]);
    const uint32_t packed = Le32(&data[at + 20]), unpacked = Le32(&data[at + 24]);
    const uint16_t name_len = Le16(&data[at + 28]), extra_len = Le16(&data[at + 30]), note_len = Le16(&data[at + 32]);
    const uint32_t local = Le32(&data[at + 42]);
    if (at + 46 + name_len > data.size()) return *error = L"the ZIP is damaged", false;
    std::string name(reinterpret_cast<const char*>(&data[at + 46]), name_len);
    at += 46 + name_len + extra_len + note_len;
    std::replace(name.begin(), name.end(), '\\', '/');
    if (name.empty() || name[0] == '/' || name.find(':') != std::string::npos ||
        ("/" + name + "/").find("/../") != std::string::npos || ("/" + name + "/").find("/./") != std::string::npos)
      return *error = L"the ZIP holds an unsafe name (" + Widen(name) + L")", false;
    const fs::path out = dest / fs::path(Widen(name)).make_preferred();
    if (name.back() == '/') {
      std::error_code ec;
      fs::create_directories(out, ec);
      continue;
    }
    if (size_t(local) + 30 > data.size() || Le32(&data[local]) != 0x04034B50) return *error = L"the ZIP is damaged", false;
    const size_t start = size_t(local) + 30 + Le16(&data[local + 26]) + Le16(&data[local + 28]);
    if (start + packed > data.size()) return *error = L"the ZIP is damaged", false;
    if (method == 0) {
      if (packed != unpacked) return *error = L"the ZIP is damaged", false;
      file.assign(data.begin() + start, data.begin() + start + packed);
    } else if (method == 8) {
      if (!InflateRaw(&data[start], packed, unpacked, &file) || file.size() != unpacked)
        return *error = L"the ZIP is damaged", false;
    } else {
      return *error = L"the ZIP uses an unknown compression", false;
    }
    if (Crc32(file.data(), file.size()) != crc) return *error = L"the ZIP is damaged (checksum)", false;
    if (!WriteFileAll(out, file.data(), file.size())) return *error = L"could not unpack " + out.filename().wstring(), false;
  }
  return true;
}

// ------------------------------------------------------------- install --
fs::path WithSuffix(const fs::path& path, const wchar_t* suffix) { return fs::path(path.wstring() + suffix); }

bool EndsWith(const std::wstring& s, const wchar_t* tail) {
  const size_t n = wcslen(tail);
  return s.size() >= n && _wcsicmp(s.c_str() + s.size() - n, tail) == 0;
}

// The program files of an unpacked release (relative paths): everything but
// resources\ other than resources\runtime, and never runtime\logs.
std::vector<fs::path> ProgramFiles(const fs::path& release) {
  std::vector<fs::path> files;
  std::error_code ec;
  for (fs::recursive_directory_iterator it(release, ec), end; it != end; it.increment(ec)) {
    if (ec) break;
    if (!it->is_regular_file(ec)) continue;
    const fs::path rel = fs::relative(it->path(), release, ec);
    auto part = rel.begin();
    if (part == rel.end()) continue;
    if (_wcsicmp(part->c_str(), L"resources") == 0) {
      ++part;
      if (part == rel.end() || _wcsicmp(part->c_str(), L"runtime") != 0) continue;
      ++part;
      if (part != rel.end() && _wcsicmp(part->c_str(), L"logs") == 0) continue;
    }
    files.push_back(rel);
  }
  return files;
}

bool Install(const Paths& p, const fs::path& release, std::wstring* error) {
  const std::vector<fs::path> files = ProgramFiles(release);
  if (files.empty()) return *error = L"the release is empty", false;
  // 1. Every new file beside its target.
  std::vector<fs::path> staged;
  auto unstage = [&] {
    std::error_code ec;
    for (const fs::path& f : staged) fs::remove(f, ec);
  };
  for (const fs::path& rel : files) {
    const fs::path target = p.root / rel;
    std::error_code ec;
    fs::create_directories(target.parent_path(), ec);
    const fs::path fresh = WithSuffix(target, kNewSuffix);
    if (!CopyFileW((release / rel).c_str(), fresh.c_str(), FALSE)) {
      unstage();
      return *error = L"could not write " + rel.wstring() + L" (is the folder read-only?); nothing was changed", false;
    }
    staged.push_back(fresh);
  }
  // 2. Swap them in; undo everything on a failure.
  struct Done {
    fs::path target;
    bool had_old;
  };
  std::vector<Done> done;
  for (const fs::path& rel : files) {
    const fs::path target = p.root / rel, old = WithSuffix(target, kOldSuffix), fresh = WithSuffix(target, kNewSuffix);
    const bool had_old = GetFileAttributesW(target.c_str()) != INVALID_FILE_ATTRIBUTES;
    bool ok = !had_old || MoveFileExW(target.c_str(), old.c_str(), MOVEFILE_REPLACE_EXISTING);
    if (ok && !MoveFileExW(fresh.c_str(), target.c_str(), 0)) {
      if (had_old) MoveFileExW(old.c_str(), target.c_str(), 0);
      ok = false;
    }
    if (!ok) {
      Log(L"Update: could not replace " + rel.wstring() + L" (error " + std::to_wstring(GetLastError()) +
          L"); putting back " + std::to_wstring(done.size()) + L" file(s)");
      for (auto it = done.rbegin(); it != done.rend(); ++it) {
        DeleteFileW(it->target.c_str());
        if (it->had_old) MoveFileExW(WithSuffix(it->target, kOldSuffix).c_str(), it->target.c_str(), 0);
      }
      unstage();
      return *error = L"could not replace " + rel.wstring() + L" (is a file in use?); nothing was changed", false;
    }
    done.push_back({target, had_old});
  }
  // 3. The old files go (this exe's own copy stays until the next start).
  for (const Done& d : done)
    if (d.had_old) DeleteFileW(WithSuffix(d.target, kOldSuffix).c_str());
  Log(L"Update: replaced " + std::to_wstring(done.size()) + L" program file(s)");
  return true;
}

// The release folder inside an unpacked ZIP: "Hexic HD PC" (what Make-Release
// writes), or the top folder itself, or its only subfolder holding Hexic HD.exe.
fs::path FindReleaseRoot(const fs::path& unpacked) {
  auto is_release = [](const fs::path& root) {
    return GetFileAttributesW((root / L"Hexic HD.exe").c_str()) != INVALID_FILE_ATTRIBUTES &&
           GetFileAttributesW((root / L"resources" / L"runtime" / L"hexic_hd.exe").c_str()) != INVALID_FILE_ATTRIBUTES;
  };
  if (is_release(unpacked / L"Hexic HD PC")) return unpacked / L"Hexic HD PC";
  if (is_release(unpacked)) return unpacked;
  std::error_code ec;
  for (fs::directory_iterator it(unpacked, ec), end; it != end; it.increment(ec)) {
    if (!ec && it->is_directory(ec) && is_release(it->path())) return it->path();
  }
  return {};
}

}  // namespace

void RecoverInterruptedUpdate(const Paths& p) {
  std::error_code ec;
  const fs::path work = p.resources / L".update";
  std::vector<fs::path> leftovers;
  auto scan = [&](const fs::path& folder, bool recursive) {
    std::error_code e;
    if (recursive) {
      for (fs::recursive_directory_iterator it(folder, e), end; it != end; it.increment(e)) {
        if (e) break;
        const std::wstring name = it->path().wstring();
        if (EndsWith(name, kOldSuffix) || EndsWith(name, kNewSuffix)) leftovers.push_back(it->path());
      }
    } else {
      for (fs::directory_iterator it(folder, e), end; it != end; it.increment(e)) {
        if (e) break;
        const std::wstring name = it->path().wstring();
        if (EndsWith(name, kOldSuffix) || EndsWith(name, kNewSuffix)) leftovers.push_back(it->path());
      }
    }
  };
  scan(p.root, false);
  scan(p.root / L"licenses", true);
  scan(p.runtime, true);
  const bool work_left = GetFileAttributesW(work.c_str()) != INVALID_FILE_ATTRIBUTES;
  if (leftovers.empty() && !work_left) return;
  LogTo(p.logs);
  for (const fs::path& f : leftovers) {
    const std::wstring name = f.wstring();
    if (EndsWith(name, kNewSuffix)) {
      DeleteFileW(f.c_str());
      continue;
    }
    const fs::path base = name.substr(0, name.size() - wcslen(kOldSuffix));
    if (GetFileAttributesW(base.c_str()) == INVALID_FILE_ATTRIBUTES) {
      if (MoveFileExW(f.c_str(), base.c_str(), 0)) Log(L"Update: put back " + base.filename().wstring() + L" (an update was cut off).");
    } else {
      DeleteFileW(f.c_str());
    }
  }
  if (work_left) fs::remove_all(work, ec);
}

UpdateOutcome RunUpdate(const Paths& p, const std::atomic<bool>& cancel, const Report& report) {
  UpdateOutcome outcome;
  auto say = [&](int percent, const std::wstring& phase, const std::wstring& detail = L"") {
    if (report) report(percent, phase, detail);
  };
  auto fail = [&](const std::wstring& why) {
    Log(L"Update FAILED: " + why);
    outcome.kind = cancel ? UpdateOutcome::kCancelled : UpdateOutcome::kFailed;
    outcome.message = why;
    return outcome;
  };
  // The game closes itself before opening this; give it a moment.
  say(0, L"WAITING FOR THE GAME TO CLOSE");
  for (int i = 0; i < 100 && GameRunning(p); ++i) {
    if (cancel) return outcome.kind = UpdateOutcome::kCancelled, outcome;
    Sleep(200);
  }
  if (GameRunning(p)) return fail(L"Hexic HD is still running from this folder. Close it, then try again.");

  say(0, L"CHECKING GITHUB FOR THE LATEST RELEASE");
  const std::wstring agent = std::wstring(L"Hexic-HD-PC-Launcher/") + kVersion;
  hexic_update::Release release;
  std::string error;
  if (!hexic_update::LatestRelease(release, agent, error)) return fail(L"Could not check for updates: " + Widen(error) + L".");
  outcome.version = Widen(release.version);
  Log(L"Update: latest release v" + outcome.version + L", this copy v" + kVersion);
  if (hexic_update::CompareVersions(release.version, Narrow(kVersion)) <= 0) {
    outcome.kind = UpdateOutcome::kUpToDate;
    return outcome;
  }
  if (!release.asset_error.empty()) return fail(L"Could not update: " + Widen(release.asset_error) + L". Nothing was changed.");
  if (cancel) return outcome.kind = UpdateOutcome::kCancelled, outcome;

  const fs::path work = p.resources / L".update";
  std::error_code ec;
  fs::remove_all(work, ec);
  fs::create_directories(work, ec);
  const fs::path zip = work / Widen(release.zip_name);
  HANDLE file = CreateFileW(zip.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) return fail(L"Could not save the download in resources\\.update (is the folder read-only?).");
  say(0, L"DOWNLOADING", release.zip_size ? L"0 / " + FormatMB(release.zip_size) : L"");
  DWORD last_report = 0;
  const bool got = hexic_update::HttpGet(
      Widen(release.zip_url), agent, nullptr, file,
      [&](uint64_t done, uint64_t total) {
        if (!total) total = release.zip_size;
        if (GetTickCount() - last_report > 100) {
          last_report = GetTickCount();
          say(total ? int(done * 100 / total) : 0, L"DOWNLOADING",
              FormatMB(done) + (total ? L" / " + FormatMB(total) : std::wstring()));
        }
        return !cancel.load();
      },
      error);
  CloseHandle(file);
  if (!got) {
    fs::remove_all(work, ec);
    return fail(L"The download did not finish: " + Widen(error) + L". Nothing was changed.");
  }
  say(100, L"CHECKING THE DOWNLOAD");
  const std::string sha = hexic_update::FileSha256(zip.wstring());
  if (sha != release.sha256) {
    fs::remove_all(work, ec);
    Log(L"Update: SHA-256 " + Widen(sha) + L", expected " + Widen(release.sha256));
    return fail(L"The download did not match the release's checksum, so it was not used. Nothing was changed.");
  }
  Log(L"Update: downloaded " + zip.filename().wstring() + L", SHA-256 verified.");
  if (cancel) {
    fs::remove_all(work, ec);
    return outcome.kind = UpdateOutcome::kCancelled, outcome;
  }
  say(100, L"UNPACKING");
  std::wstring why;
  const fs::path unpacked = work / L"new";
  if (!ExtractZip(zip, unpacked, &why)) {
    fs::remove_all(work, ec);
    return fail(L"The download could not be unpacked: " + why + L". Nothing was changed.");
  }
  const fs::path release_root = FindReleaseRoot(unpacked);
  if (release_root.empty()) {
    fs::remove_all(work, ec);
    return fail(L"The download is not a Hexic HD release. Nothing was changed.");
  }
  say(100, L"INSTALLING");
  if (!Install(p, release_root, &why)) {
    fs::remove_all(work, ec);
    return fail(L"The update could not be installed: " + why + L".");
  }
  fs::remove_all(work, ec);
  Log(L"Update: installed v" + outcome.version + L".");
  outcome.kind = UpdateOutcome::kUpdated;
  return outcome;
}

}  // namespace hexic
