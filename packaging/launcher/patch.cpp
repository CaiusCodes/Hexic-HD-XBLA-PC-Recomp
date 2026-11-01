// Hexic HD PC - launcher: the PC wording and the High Scores screen.
//
// A native port of the earlier Patch-PcMenuText.ps1 (kept in packaging\legacy-setup),
// run on the unpacked assets while they are still in the staging folder:
//
//   g.xml  (plain UTF-8 text)
//     Achievements -> Settings, Xbox Dashboard -> Quit Hexic,
//     Leaderboards -> High Scores, and the wording around them.
//   HexicDeluxe.swf  (the game's Flash movie)
//     The High Scores screen lists this PC's scores only, so it opens on Overall
//     and the Sort Mode (X) button goes. Six in-place byte edits to the
//     decompressed movie, each checked against the original bytes first; the
//     movie is only rewritten when all of them match.
//
// A file that is not the expected build is left exactly as it was, and patching
// twice changes nothing, so a failure here only leaves the Xbox wording.
#include "launcher.h"

#include <cstring>

namespace hexic {
namespace {

bool ReadBytes(const fs::path& path, std::string* out) {
  HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) return false;
  LARGE_INTEGER size = {};
  bool ok = GetFileSizeEx(file, &size) && size.QuadPart >= 0 && size.QuadPart < (1ll << 30);
  if (ok) {
    out->resize(static_cast<size_t>(size.QuadPart));
    DWORD got = 0;
    ok = size.QuadPart == 0 ||
         (ReadFile(file, out->data(), static_cast<DWORD>(out->size()), &got, nullptr) && got == out->size());
  }
  CloseHandle(file);
  return ok;
}

// Written beside the target first and moved over it, so a failure never leaves
// a half-written file.
bool WriteBytes(const fs::path& path, const std::string& data) {
  const fs::path temp = path.wstring() + L".tmp";
  HANDLE file = CreateFileW(temp.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) return false;
  DWORD written = 0;
  const bool ok = data.empty() || (WriteFile(file, data.data(), static_cast<DWORD>(data.size()), &written, nullptr) &&
                                   written == data.size());
  CloseHandle(file);
  if (!ok || !MoveFileExW(temp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
    DeleteFileW(temp.c_str());
    return false;
  }
  return true;
}

bool FileExists(const fs::path& path) {
  const DWORD attributes = GetFileAttributesW(path.c_str());
  return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

// Replaces every occurrence; false when there was none.
bool ReplaceAll(std::string* text, const std::string& from, const std::string& to) {
  bool found = false;
  for (size_t at = text->find(from); at != std::string::npos; at = text->find(from, at + to.size())) {
    text->replace(at, from.size(), to);
    found = true;
  }
  return found;
}

uint8_t HexNibble(char c) { return static_cast<uint8_t>(c <= '9' ? c - '0' : (c | 0x20) - 'a' + 10); }

std::vector<uint8_t> FromHex(const char* hex) {
  std::vector<uint8_t> bytes;
  for (size_t i = 0; hex[i] && hex[i + 1]; i += 2) bytes.push_back(static_cast<uint8_t>((HexNibble(hex[i]) << 4) | HexNibble(hex[i + 1])));
  return bytes;
}

bool BytesAt(const std::vector<uint8_t>& data, size_t offset, const std::vector<uint8_t>& expected) {
  return offset + expected.size() <= data.size() && memcmp(data.data() + offset, expected.data(), expected.size()) == 0;
}

uint32_t LE32(const uint8_t* p) { return p[0] | (uint32_t(p[1]) << 8) | (uint32_t(p[2]) << 16) | (uint32_t(p[3]) << 24); }

std::wstring PatchGxml(const fs::path& assets) {
  const fs::path path = assets / L"g.xml";
  std::string text;
  if (!ReadBytes(path, &text)) return L"menus: g.xml not found; PC menu text skipped.";
  struct Replacement {
    const char* from;
    const char* to;
  };
  static const Replacement kReplacements[] = {
      {">Achievements</text>", ">Settings</text>"},
      {"Show off the awards you've earned.", "Change display, audio and performance settings."},
      {">Xbox Dashboard</text>", ">Quit Hexic</text>"},
      {"Quit Hexic, and return to the Xbox Dashboard.", "Quit Hexic, and return to the desktop."},
      // Leaderboards -> High Scores: the screen lists this PC's scores only.
      {">Leaderboards</text>", ">High Scores</text>"},
      {"View high scores on Xbox Live.", "View your best scores for each mode."},
      {"Congratulations! You have a new high score on the Xbox Live leaderboards!!",
       "Congratulations! You have a new high score!"},
      {"-->Sort Mode</text>", "--></text>"},
      {"No scores have been posted to this leaderboard.", "No high scores yet for this mode."},
      {"-->Signed In:</text>", "-->Player:</text>"},
  };
  bool changed = false;
  for (const Replacement& r : kReplacements) changed = ReplaceAll(&text, r.from, r.to) || changed;
  if (!changed) return L"menus: PC menu text already applied (or source text changed); nothing to do.";
  // g.xml ships without a BOM and the bytes are written back as they were.
  if (!WriteBytes(path, text)) return L"menus: could not write g.xml.";
  return L"menus: Relabeled the menus for PC: Settings, High Scores, Quit Hexic.";
}

std::wstring PatchSwf(const fs::path& assets) {
  const fs::path path = assets / L"HexicDeluxe.swf";
  if (!FileExists(path)) return L"menus: HexicDeluxe.swf not found; High Scores screen left unchanged.";
  std::string raw_text;
  if (!ReadBytes(path, &raw_text) || raw_text.size() < 16) return L"menus: HexicDeluxe.swf could not be read; High Scores screen left unchanged.";
  const uint8_t* raw = reinterpret_cast<const uint8_t*>(raw_text.data());

  std::vector<uint8_t> body;
  if (memcmp(raw, "CWS", 3) == 0) {
    // zlib stream after the 8-byte header.
    if (!Inflate(raw + 8, raw_text.size() - 8, &body)) body.clear();
  } else if (memcmp(raw, "FWS", 3) == 0) {
    body.assign(raw + 8, raw + raw_text.size());
  }
  // The header's length field should cover the 8-byte header too, but this
  // movie's equals the body alone; accept either, and keep it as it was.
  const uint32_t declared = LE32(raw + 4);
  if (body.empty() || (declared != body.size() && declared != body.size() + 8))
    return L"menus: HexicDeluxe.swf is not the expected movie; High Scores screen left unchanged.";

  // Offsets count from the start of the body, after the 8-byte SWF header.
  //   SortOrder starts as SO_Overall instead of SO_Friends (constant index)
  //   the first title shown is Overall instead of Friends (constant index)
  //   ChangeSortOrder, bound to X, jumps straight to its end
  //   the X button icon's three pieces are placed at zero scale
  struct Edit {
    size_t offset;
    const char* from;
    const char* to;
  };
  static const Edit kEdits[] = {
      {0x2583CA, "0F", "47"},
      {0x258590, "27", "29"},
      {0x258A05, "960400082B", "9902006F00"},
      {0x25AC4D, "C92BBB4B290F74362858", "C8000000000F74362858"},
      {0x25AC5E, "C5E842F4DF3DB080A440", "C4000000003DB080A440"},
      {0x25AC6F, "C92BBB4B290F74362858", "C8000000000F74362858"},
  };
  constexpr size_t kEditCount = sizeof(kEdits) / sizeof(kEdits[0]);
  size_t original = 0, patched = 0;
  for (const Edit& e : kEdits) {
    original += BytesAt(body, e.offset, FromHex(e.from)) ? 1 : 0;
    patched += BytesAt(body, e.offset, FromHex(e.to)) ? 1 : 0;
  }
  if (patched == kEditCount) return L"menus: High Scores screen already patched; nothing to do.";
  if (original != kEditCount) return L"menus: HexicDeluxe.swf differs from the expected build; High Scores screen left unchanged.";
  for (const Edit& e : kEdits) {
    const std::vector<uint8_t> to = FromHex(e.to);
    memcpy(body.data() + e.offset, to.data(), to.size());
  }
  // Written back uncompressed ("FWS") with the original version and length field.
  std::string movie("FWS", 3);
  movie.append(raw_text, 3, 5);
  movie.append(reinterpret_cast<const char*>(body.data()), body.size());
  if (!WriteBytes(path, movie)) return L"menus: could not write HexicDeluxe.swf.";
  return L"menus: High Scores screen: opens on Overall, Sort Mode removed.";
}

}  // namespace

std::vector<std::wstring> PatchPcMenus(const fs::path& assets) {
  return {PatchGxml(assets), PatchSwf(assets)};
}

}  // namespace hexic
