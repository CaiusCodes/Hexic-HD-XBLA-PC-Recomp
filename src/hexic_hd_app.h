// hexic_hd - ReXGlue Recompiled Project
//
// Customize your app by overriding virtual hooks from rex::ReXApp.

#pragma once

// Before <xinput.h>: it #defines XINPUT_DEVTYPE_GAMEPAD, a name the SDK's
// input headers declare as an enum value.
#include <rex/input/input_system.h>

#include <windows.h>
#include <xinput.h>

#include <atomic>
#include <cfloat>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <memory>
#include <mutex>
#include <string_view>
#include <thread>
#include <string>
#include <vector>

#include <imgui.h>

#include <rex/cvar.h>
#include <rex/kernel/xam/netplay.h>
#include <rex/kernel/xam/ui_hooks.h>
#include <rex/logging.h>
#include <rex/rex_app.h>
#include <rex/system/kernel_state.h>
#include <rex/system/xam/user_profile.h>
#include <rex/ui/imgui_dialog.h>
#include <rex/ui/imgui_drawer.h>
#include <rex/ui/keybinds.h>
#include <rex/ui/presenter.h>
#include <rex/ui/window.h>
#include <rex/ui/window_sdl.h>

#include "hexic_input.h"
#include "hexic_input_mode.h"
#include "hexic_mouse.h"
#include "hexic_player_names.h"
#include "hexic_system_info.h"
#include "hexic_title.h"
#include "hexic_update.h"
#include "hexic_version.h"  // HEXIC_VERSION, generated from VERSION (CMakeLists.txt)

// Which set of Hexic keyboard defaults this config has received (main.cpp).
REXCVAR_DECLARE(int32_t, hexic_controls_version);

class HexicHdApp;

// Where the game keeps its data. In a release the game program lives in
// <release>\resources\runtime and its data beside that folder (resources\assets,
// resources\userdata with hexic_hd.toml); the launcher in the release root starts
// it. Dev builds, and the earlier portable builds (Game\hexic_hd.exe), keep
// everything beside the exe (assets, userdata, hexic_hd.toml).
namespace hexic_paths {
inline std::filesystem::path ExeFolder() {
  wchar_t exe_path[32768] = {};
  const DWORD length = GetModuleFileNameW(nullptr, exe_path, 32768);
  return std::filesystem::path(std::wstring(exe_path, length)).parent_path();
}
inline bool InRuntimeFolder() {
  std::wstring name = ExeFolder().filename().wstring();
  for (wchar_t& c : name) c = static_cast<wchar_t>(towlower(c));
  return name == L"runtime";
}
inline std::filesystem::path DataRoot() {
  const auto exe = ExeFolder();
  return InRuntimeFolder() ? exe.parent_path() : exe;
}
// Saves, high scores, settings and caches: resources\userdata, unless the
// player chose another folder in setup. Then resources\userdata-location.txt
// holds that folder (one line, UTF-8); the launcher writes it, and an update
// never touches it (only the program files are replaced).
inline std::filesystem::path CustomUserDataRoot() {
  if (!InRuntimeFolder()) return {};
  std::ifstream in(DataRoot() / "userdata-location.txt", std::ios::binary);
  std::string line;
  if (!in || !std::getline(in, line)) return {};
  if (line.size() >= 3 && static_cast<unsigned char>(line[0]) == 0xEF) line.erase(0, 3);  // BOM
  while (!line.empty() && (line.back() == '\r' || line.back() == ' ')) line.pop_back();
  if (line.empty()) return {};
  return std::filesystem::path(std::u8string(line.begin(), line.end()));
}
inline std::filesystem::path UserDataRoot() {
  const auto custom = CustomUserDataRoot();
  return custom.empty() ? DataRoot() / "userdata" : custom;
}
inline std::filesystem::path ConfigPath() {
  return InRuntimeFolder() ? UserDataRoot() / "hexic_hd.toml" : ExeFolder() / "hexic_hd.toml";
}
}  // namespace hexic_paths

// Fonts loaded from the game's own asset files (see HexicHdApp::
// OnConfigureFonts), so the panel reads with the game's actual typography
// instead of ImGui's small debug-overlay bitmap font. Null if the source
// file wasn't found (e.g. dialog somehow opened pre-install); callers must
// tolerate that and fall back to the default font.
struct HexicFonts {
  inline static ImFont* heading = nullptr;
  inline static ImFont* body = nullptr;
};

// Drawing helpers and palette for a Hexic HD-styled ImGui panel: black field,
// faint hexagon clusters, a dark-navy-to-purple metallic card, and a cyan
// accent line, echoing the game's own title/options screens.
namespace hexic_ui {

constexpr ImU32 kCardTop = IM_COL32(0x20, 0x1A, 0x38, 255);
constexpr ImU32 kCardBottom = IM_COL32(0x46, 0x44, 0x74, 255);
constexpr ImU32 kCardBorder = IM_COL32(0x8A, 0x7E, 0xD8, 255);
constexpr ImU32 kAccentCyan = IM_COL32(0x3F, 0xD0, 0xE8, 255);
constexpr ImU32 kHexLine = IM_COL32(120, 130, 210, 55);
constexpr ImU32 kRowIdle = IM_COL32(0x22, 0x1C, 0x3E, 190);
constexpr ImU32 kRowIdleBorder = IM_COL32(0x5A, 0x50, 0x92, 160);
constexpr ImU32 kRowSelectedTop = IM_COL32(0x3E, 0xC6, 0x3A, 255);
constexpr ImU32 kRowSelectedBottom = IM_COL32(0x1F, 0x7A, 0x1C, 255);
constexpr ImU32 kRowSelectedBorder = IM_COL32(0xA8, 0xF0, 0x7A, 255);
constexpr ImU32 kTextNormal = IM_COL32(0xE6, 0xEA, 0xF7, 255);
constexpr ImU32 kTextDim = IM_COL32(0xAF, 0xB6, 0xD6, 255);
constexpr ImU32 kTextSelected = IM_COL32(0xFF, 0xFF, 0xFF, 255);
constexpr ImU32 kChevron = IM_COL32(0x3F, 0xD0, 0xE8, 255);
constexpr ImU32 kChevronDim = IM_COL32(0x6C, 0x74, 0x9A, 255);

// Glossy-pill palette, sampled from Hexic's own menu buttons: purple when
// idle, lime-green when selected, each with a light bevel rim. Text on both
// is white with a dark drop shadow, matching the game.
constexpr ImU32 kPillPurpleBase = IM_COL32(0x5A, 0x20, 0xA4, 255);
constexpr ImU32 kPillPurpleRim = IM_COL32(0xC6, 0xA6, 0xF2, 220);
constexpr ImU32 kPillGreenBase = IM_COL32(0x4C, 0xB0, 0x20, 255);
constexpr ImU32 kPillGreenRim = IM_COL32(0xCC, 0xF6, 0x8C, 235);
constexpr ImU32 kTextShadow = IM_COL32(0x0E, 0x06, 0x1E, 200);

// A glossy rounded button matching Hexic's own menu items: a rounded base, a
// bright gloss over the top half, a shaded lower half for depth, a light
// bevel rim, and (when selected) a soft green outer glow. ImGui can't fill a
// rounded rect with a vertical gradient, so the gloss and shade are layered
// rounded rects over a flat base instead - which keeps the corners rounded.
inline void DrawGamePill(ImDrawList* draw_list, ImVec2 lo, ImVec2 hi, bool selected) {
  const float rounding = 10.0f;
  const float height = hi.y - lo.y;
  if (selected) {
    for (int i = 3; i >= 1; --i) {
      float grow = i * 3.0f;
      draw_list->AddRect(ImVec2(lo.x - grow, lo.y - grow), ImVec2(hi.x + grow, hi.y + grow),
                         IM_COL32(0x8A, 0xF0, 0x40, 24 + (3 - i) * 20), rounding + grow, 0, 2.2f);
    }
  }
  draw_list->AddRectFilled(lo, hi, selected ? kPillGreenBase : kPillPurpleBase, rounding);
  draw_list->AddRectFilled(lo, ImVec2(hi.x, lo.y + height * 0.5f),
                           IM_COL32(0xFF, 0xFF, 0xFF, selected ? 80 : 58), rounding,
                           ImDrawFlags_RoundCornersTop);
  draw_list->AddRectFilled(ImVec2(lo.x, hi.y - height * 0.42f), hi,
                           IM_COL32(0x00, 0x00, 0x00, selected ? 42 : 62), rounding,
                           ImDrawFlags_RoundCornersBottom);
  draw_list->AddRect(lo, hi, selected ? kPillGreenRim : kPillPurpleRim, rounding, 0, 1.6f);
  draw_list->AddLine(ImVec2(lo.x + rounding, lo.y + 1.5f), ImVec2(hi.x - rounding, lo.y + 1.5f),
                     IM_COL32(0xFF, 0xFF, 0xFF, 90), 1.0f);
}

// Text with a 1px dark drop shadow, so labels stay legible over the glossy
// pill in both colours (matching the game's own button lettering).
inline void DrawPillText(ImDrawList* draw_list, ImFont* font, float size, ImVec2 pos, ImU32 color,
                         const char* text) {
  draw_list->AddText(font, size, ImVec2(pos.x, pos.y + 1.5f), kTextShadow, text);
  draw_list->AddText(font, size, pos, color, text);
}

inline void DrawHexagon(ImDrawList* draw_list, ImVec2 center, float radius, ImU32 color) {
  ImVec2 points[6];
  for (int i = 0; i < 6; ++i) {
    float angle = (3.14159265f / 180.0f) * (60.0f * i - 30.0f);
    points[i] = ImVec2(center.x + radius * cosf(angle), center.y + radius * sinf(angle));
  }
  draw_list->AddPolyline(points, 6, color, ImDrawFlags_Closed, 1.4f);
}

inline void DrawHexCluster(ImDrawList* draw_list, ImVec2 origin, int cols, int rows,
                           float radius) {
  float step_x = radius * 1.75f;
  float step_y = radius * 1.52f;
  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      float offset = (row % 2 == 0) ? 0.0f : step_x / 2.0f;
      ImVec2 center(origin.x + offset + col * step_x, origin.y + row * step_y);
      DrawHexagon(draw_list, center, radius, kHexLine);
    }
  }
}

// A left/right chevron, drawn as a filled triangle (matching the arrow
// buttons flanking spinner rows in the game's own Options screen).
inline void DrawChevron(ImDrawList* draw_list, ImVec2 center, float size, bool pointing_right,
                        ImU32 color) {
  ImVec2 a, b, c;
  if (pointing_right) {
    a = ImVec2(center.x - size * 0.5f, center.y - size);
    b = ImVec2(center.x - size * 0.5f, center.y + size);
    c = ImVec2(center.x + size * 0.6f, center.y);
  } else {
    a = ImVec2(center.x + size * 0.5f, center.y - size);
    b = ImVec2(center.x + size * 0.5f, center.y + size);
    c = ImVec2(center.x - size * 0.6f, center.y);
  }
  draw_list->AddTriangleFilled(a, b, c, color);
}

// The panel every Hexic PC dialog sits on: a deep violet metallic card with a
// soft outer glow and honeycomb corners, a shadowed heading and the cyan
// accent line under it. Returns the y of that line, where content starts.
inline float DrawHexicCard(ImDrawList* draw_list, ImVec2 window_pos, ImVec2 window_end,
                           float side_margin, const char* heading) {
  ImVec2 card_min(window_pos.x + 8, window_pos.y + 6);
  ImVec2 card_max(window_end.x - 8, window_end.y - 6);
  for (int i = 4; i >= 1; --i) {
    float grow = i * 2.5f;
    draw_list->AddRect(ImVec2(card_min.x - grow, card_min.y - grow),
                       ImVec2(card_max.x + grow, card_max.y + grow),
                       IM_COL32(0x7A, 0x4C, 0xFF, 18 + (4 - i) * 14), 18.0f + grow, 0, 2.0f);
  }
  draw_list->AddRectFilled(card_min, card_max, IM_COL32(0x17, 0x12, 0x2C, 252), 16.0f);
  draw_list->AddRectFilled(card_min,
                           ImVec2(card_max.x, card_min.y + (card_max.y - card_min.y) * 0.5f),
                           IM_COL32(0x33, 0x28, 0x58, 90), 16.0f, ImDrawFlags_RoundCornersTop);
  draw_list->PushClipRect(card_min, card_max, true);
  DrawHexCluster(draw_list, ImVec2(card_min.x - 4, card_min.y - 4), 4, 5, 20.0f);
  DrawHexCluster(draw_list, ImVec2(card_max.x - 80, card_min.y - 4), 4, 5, 20.0f);
  draw_list->PopClipRect();
  draw_list->AddRect(card_min, card_max, kCardBorder, 16.0f, 0, 2.0f);

  ImFont* heading_font = HexicFonts::heading ? HexicFonts::heading : ImGui::GetFont();
  float heading_size = HexicFonts::heading ? 27.0f : ImGui::GetFontSize() * 1.3f;
  ImVec2 heading_pos(window_pos.x + side_margin, window_pos.y + 20.0f);
  draw_list->AddText(heading_font, heading_size, ImVec2(heading_pos.x, heading_pos.y + 1.5f),
                     kTextShadow, heading);
  draw_list->AddText(heading_font, heading_size, heading_pos, kTextSelected, heading);
  float accent_y = window_pos.y + 20.0f + heading_size + 8.0f;
  draw_list->AddLine(ImVec2(window_pos.x + side_margin, accent_y),
                     ImVec2(window_end.x - side_margin, accent_y), kAccentCyan, 2.0f);
  return accent_y;
}

}  // namespace hexic_ui

// Keyboard controls. Every Xbox 360 controller input can be bound to up to
// two keys or mouse buttons; the bindings are the SDK's keybind_* settings in
// hexic_hd.toml. The SDK's defaults suit a shooter, so Hexic applies its own
// once (hexic_controls_version) and "Reset" restores these.
namespace hexic_controls {

struct Binding {
  const char* button;  // the controller input
  const char* action;  // what it does in Hexic, or "" where the game doesn't use it
  const char* cvar;
  const char* defaults;
};

inline const std::vector<Binding>& Bindings() {
  static const std::vector<Binding> kBindings = {
      {"A", "Rotate clockwise, select", "keybind_a", "E,Space,Return"},
      {"B", "Back", "keybind_b", "Backspace"},
      {"X", "Rotate counter-clockwise", "keybind_x", "Q"},
      {"Y", "", "keybind_y", ""},
      {"Left Trigger", "Rotate", "keybind_left_trigger", "Z"},
      {"Right Trigger", "Rotate", "keybind_right_trigger", "X"},
      {"Left Bumper", "", "keybind_left_shoulder", "1"},
      {"Right Bumper", "", "keybind_right_shoulder", "3"},
      {"Start", "Pause", "keybind_start", "Escape"},
      {"Back", "", "keybind_back", "Tab"},
      {"D-pad Up", "Move", "keybind_dpad_up", "Up"},
      {"D-pad Down", "Move", "keybind_dpad_down", "Down"},
      {"D-pad Left", "Move", "keybind_dpad_left", "Left"},
      {"D-pad Right", "Move", "keybind_dpad_right", "Right"},
      {"Left Stick Up", "Move", "keybind_lstick_up", "W"},
      {"Left Stick Down", "Move", "keybind_lstick_down", "S"},
      {"Left Stick Left", "Move", "keybind_lstick_left", "A"},
      {"Left Stick Right", "Move", "keybind_lstick_right", "D"},
      {"Left Stick Click", "", "keybind_lstick_press", "C"},
      {"Right Stick Up", "", "keybind_rstick_up", "I"},
      {"Right Stick Down", "", "keybind_rstick_down", "K"},
      {"Right Stick Left", "", "keybind_rstick_left", "J"},
      {"Right Stick Right", "", "keybind_rstick_right", "L"},
      {"Right Stick Click", "", "keybind_rstick_press", "V"},
  };
  return kBindings;
}

// Bumped whenever the defaults above change, so existing configs pick them up
// (version 2: E rotates clockwise like Space, Y has no key; see Upgrade).
constexpr int32_t kDefaultsVersion = 2;
constexpr size_t kMaxKeysPerBinding = 3;

inline std::vector<std::string> SplitKeys(const std::string& value) {
  std::vector<std::string> keys;
  size_t start = 0;
  while (start <= value.size()) {
    const size_t comma = value.find(',', start);
    std::string key =
        value.substr(start, comma == std::string::npos ? std::string::npos : comma - start);
    while (!key.empty() && key.front() == ' ') key.erase(0, 1);
    while (!key.empty() && key.back() == ' ') key.pop_back();
    if (!key.empty()) keys.push_back(key);
    if (comma == std::string::npos) break;
    start = comma + 1;
  }
  return keys;
}

inline std::string JoinKeys(const std::vector<std::string>& keys) {
  std::string value;
  for (const auto& key : keys) {
    if (!value.empty()) value += ",";
    value += key;
  }
  return value;
}

inline std::vector<std::string> KeysOf(size_t index) {
  return SplitKeys(rex::cvar::GetFlagByName(Bindings()[index].cvar));
}

// The config names ("LMB", "Return", "LBracket") read poorly in a menu.
inline std::string KeyDisplayName(const std::string& key) {
  static const std::pair<const char*, const char*> kNames[] = {
      {"LMB", "Left Mouse"},     {"RMB", "Right Mouse"},     {"MMB", "Middle Mouse"},
      {"Control", "Ctrl"},       {"Escape", "Esc"},          {"Return", "Enter"},
      {"PageUp", "Page Up"},     {"PageDown", "Page Down"},  {"CapsLock", "Caps Lock"},
      {"LBracket", "["},         {"RBracket", "]"},          {"Semicolon", ";"},
      {"Quote", "'"},            {"Comma", ","},             {"Period", "."},
      {"Slash", "/"},            {"Backslash", "\\"},        {"Backtick", "`"},
      {"Minus", "-"},            {"Plus", "="},
  };
  for (const auto& [raw, nice] : kNames) {
    if (key == raw) return nice;
  }
  return key;
}

inline std::string FormatKeys(const std::vector<std::string>& keys) {
  if (keys.empty()) return "Not bound";
  std::string text;
  for (const auto& key : keys) {
    if (!text.empty()) text += "  /  ";
    text += KeyDisplayName(key);
  }
  return text;
}

// Gives binding `index` exactly `keys`, taking them off every other binding.
// A binding left with no key receives this one's previous keys, so a clash is
// a swap and nothing that had a key ends up unbound.
inline void SetKeys(size_t index, const std::vector<std::string>& keys) {
  const auto& bindings = Bindings();
  std::vector<std::string> spare;
  for (const auto& key : KeysOf(index)) {
    if (std::find(keys.begin(), keys.end(), key) == keys.end()) spare.push_back(key);
  }
  for (size_t j = 0; j < bindings.size(); ++j) {
    if (j == index) continue;
    auto others = KeysOf(j);
    const size_t before = others.size();
    others.erase(std::remove_if(others.begin(), others.end(),
                                [&](const std::string& key) {
                                  return std::find(keys.begin(), keys.end(), key) != keys.end();
                                }),
                 others.end());
    if (others.size() == before) continue;
    if (others.empty()) {
      others = spare;
      spare.clear();
    }
    rex::cvar::SetFlagByName(bindings[j].cvar, JoinKeys(others));
    REXLOG_INFO("[controls] {} -> {}", bindings[j].button, JoinKeys(others));
  }
  rex::cvar::SetFlagByName(bindings[index].cvar, JoinKeys(keys));
  REXLOG_INFO("[controls] {} -> {}", bindings[index].button, JoinKeys(keys));
}

inline void ResetAll() {
  for (const auto& binding : Bindings()) {
    rex::cvar::SetFlagByName(binding.cvar, binding.defaults);
  }
  REXLOG_INFO("[controls] all keys reset to the Hexic defaults");
}

// The guide button has no keyboard binding in Hexic: clear the SDK's.
inline void ApplyDefaults() {
  ResetAll();
  rex::cvar::SetFlagByName("keybind_guide", "");
}

// Brings a config made with older defaults up to date without undoing the
// player's own changes: version 1 -> 2 moves E from Y to A (E and Q are
// rotate clockwise / counterclockwise), only if E is still where 1 put it.
inline void Upgrade(int32_t from_version) {
  if (from_version < 1) {
    ApplyDefaults();
    return;
  }
  if (from_version < 2 && rex::cvar::GetFlagByName("keybind_y") == "E") {
    rex::cvar::SetFlagByName("keybind_y", "");
    auto keys = SplitKeys(rex::cvar::GetFlagByName("keybind_a"));
    if (std::find(keys.begin(), keys.end(), "E") == keys.end() && keys.size() < kMaxKeysPerBinding) {
      keys.insert(keys.begin(), "E");
      rex::cvar::SetFlagByName("keybind_a", JoinKeys(keys));
    }
    REXLOG_INFO("[controls] E now rotates clockwise (A): {}", rex::cvar::GetFlagByName("keybind_a"));
  }
}

}  // namespace hexic_controls

// Menu input for the Hexic dialogs: arrow keys / D-pad / left stick to move,
// Enter / A to confirm, Esc / B to go back, Tab / Y for a second action and
// Backspace / X to reset or erase. Keys and the pad are read directly (the
// game's own keyboard mapping is off while a dialog is open). Presses are
// edges; Up and Down, and optionally Reset, repeat while held. The first poll,
// and the first poll after Reprime(), only records what is already held, so
// the press that opened a dialog can't also act inside it.
class HexicMenuInput {
 public:
  enum Action : int {
    kUp, kDown, kLeft, kRight, kConfirm, kBack, kAlt, kReset,
    kPrevPage, kNextPage,  // Q / E, Page Up / Page Down, LB / RB
    kCount
  };

  explicit HexicMenuInput(bool repeat_reset = false) : repeat_reset_(repeat_reset) {}

  void Poll(bool focused) {
    bool held[kCount] = {};
    if (focused) {
      auto key = [](int vk) { return (GetAsyncKeyState(vk) & 0x8000) != 0; };
      held[kUp] = key(VK_UP);
      held[kDown] = key(VK_DOWN);
      held[kLeft] = key(VK_LEFT);
      held[kRight] = key(VK_RIGHT);
      held[kConfirm] = key(VK_RETURN);
      held[kBack] = key(VK_ESCAPE);
      held[kAlt] = key(VK_TAB);
      held[kReset] = key(VK_BACK) || key(VK_DELETE);
      held[kPrevPage] = key('Q') || key(VK_PRIOR);
      held[kNextPage] = key('E') || key(VK_NEXT);
      // The game gets no input while a dialog is open, so the dialog itself
      // tells the button prompts which device is in use (hexic_input_mode.h).
      for (int i = 0; i < kCount; ++i) {
        if (held[i]) hexic_input_mode::NoteKeyboardMouse();
      }
      XINPUT_STATE state{};
      if (XInputGetState(0, &state) == ERROR_SUCCESS) {
        const WORD b = state.Gamepad.wButtons;
        constexpr SHORT kStick = 16000;
        if (b != 0 || std::abs(state.Gamepad.sThumbLX) > kStick ||
            std::abs(state.Gamepad.sThumbLY) > kStick) {
          hexic_input_mode::SetMode(hexic_input_mode::kController, "controller used in a dialog");
        }
        held[kUp] |= (b & XINPUT_GAMEPAD_DPAD_UP) || state.Gamepad.sThumbLY > kStick;
        held[kDown] |= (b & XINPUT_GAMEPAD_DPAD_DOWN) || state.Gamepad.sThumbLY < -kStick;
        held[kLeft] |= (b & XINPUT_GAMEPAD_DPAD_LEFT) || state.Gamepad.sThumbLX < -kStick;
        held[kRight] |= (b & XINPUT_GAMEPAD_DPAD_RIGHT) || state.Gamepad.sThumbLX > kStick;
        held[kConfirm] |= (b & XINPUT_GAMEPAD_A) != 0;
        held[kBack] |= (b & XINPUT_GAMEPAD_B) != 0;
        held[kAlt] |= (b & XINPUT_GAMEPAD_Y) != 0;
        held[kReset] |= (b & XINPUT_GAMEPAD_X) != 0;
        held[kPrevPage] |= (b & XINPUT_GAMEPAD_LEFT_SHOULDER) != 0;
        held[kNextPage] |= (b & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
      }
    }
    const auto now = std::chrono::steady_clock::now();
    for (int i = 0; i < kCount; ++i) {
      pressed_[i] = primed_ && held[i] && !was_held_[i];
      const bool repeats = i == kUp || i == kDown || (i == kReset && repeat_reset_);
      if (pressed_[i]) {
        repeat_at_[i] = now + std::chrono::milliseconds(400);
      } else if (primed_ && repeats && held[i] && was_held_[i] && now >= repeat_at_[i]) {
        pressed_[i] = true;
        repeat_at_[i] = now + std::chrono::milliseconds(i == kReset ? 45 : 90);
      }
      was_held_[i] = held[i];
    }
    primed_ = true;
  }

  bool Pressed(Action action) const { return pressed_[action]; }
  void Reprime() { primed_ = false; }

 private:
  bool repeat_reset_;
  bool primed_ = false;
  bool was_held_[kCount] = {};
  bool pressed_[kCount] = {};
  std::chrono::steady_clock::time_point repeat_at_[kCount] = {};
};

// Settings > Controls: every controller input with the keys bound to it, drawn
// inside the Settings panel (in its style) rather than as a dialog of its own.
// Keyboard / pad: Up / Down choose, Enter / A change the key, Tab / Y add one,
// Backspace / X reset that input. Mouse: hover chooses, click a row to change
// its key, Add / Reset on the chosen row, the wheel scrolls. The last row
// resets every key. While waiting for a key, Esc, B or a click cancels.
class HexicControlsPanel {
 public:
  bool Capturing() const { return capture_ != kCaptureIdle; }
  // After input.Poll (not capturing): the list's keys. While capturing: the
  // capture, which reads the keyboard directly (input is re-primed after).
  void Update(bool focused, HexicMenuInput& input);
  // The list in [lo, hi], with the mouse (click: a left click this frame).
  void Draw(ImDrawList* dl, ImFont* font, ImVec2 lo, ImVec2 hi, ImVec2 mouse, bool mouse_moved,
            bool click, float wheel);
  std::string Help() const;

 private:
  enum Capture : int { kCaptureIdle, kCaptureWaitRelease, kCaptureListen, kCaptureFinish };

  int RowCount() const { return int(hexic_controls::Bindings().size()) + 1; }
  int ResetAllRow() const { return int(hexic_controls::Bindings().size()); }

  void Activate(int row, bool append);
  void ResetRow(int row);
  void ResetAllKeys();
  void TickCapture(bool focused, HexicMenuInput& input);
  void FinishCapture(const std::string& notice);
  void Notice(int row, const std::string& text, int seconds);

  int selected_ = 0;
  int scroll_top_ = 0;
  int visible_rows_ = 8;

  Capture capture_ = kCaptureIdle;
  int capture_row_ = -1;
  bool capture_append_ = false;
  std::chrono::steady_clock::time_point capture_deadline_{};
  int notice_row_ = -1;
  std::string notice_;
  std::chrono::steady_clock::time_point notice_until_{};
};

// The PC settings panel, shown in place of Hexic HD's own (Xbox-only)
// Achievements viewer. Categories down the side (Display, Graphics, Player,
// Controls); the chosen category's settings on the right, every choice shown
// with the current one filled in. Reuses the same CVars as the F4 overlay.
//
// Controller: LB / RB category, D-pad up / down setting, left / right choice,
// A opens (Player name, Keyboard controls), B closes. Keyboard: Q / E (or
// Page Up / Down), arrows, Enter, Esc. Mouse: click a category or a choice;
// right click closes.
class HexicSettingsDialog : public rex::ui::ImGuiDialog {
 public:
  // Every setting, by category. kRowPlayerName and kRowControls are the
  // pages a sub-dialog returns to.
  enum Item : int {
    kItemDisplayMode,
    kItemResolution,
    kItemVSync,
    kItemShowFps,
    kItemRenderScale,
    kItemAntiAliasing,
    kItemUpscaling,
    kItemRenderer,
    kRowPlayerName,
    kRowControls,
    kRowUpdates,
    kItemCount,
  };

  // `select_item` lets a sub-dialog return with its own setting selected.
  HexicSettingsDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app,
                      int select_item = kItemDisplayMode);

  void OnDraw(ImGuiIO& io) override;

 protected:
  void OnClose() override;

 private:
  enum Category : int { kDisplay, kGraphics, kPlayer, kControls, kUpdates, kCategoryCount };

  static Category CategoryOf(int item);
  static int FirstItem(Category category);
  static int ItemCount(Category category);

  // The choices of a setting with fixed options, and which is current; an
  // empty list means the item opens a page instead (Player name, Controls).
  static std::vector<const char*> Options(int item);
  static int Current(int item);
  static void Choose(int item, int option);
  static const char* Label(int item);
  static std::string Help(int item);

  void SelectCategory(Category category);
  void Activate(int item);

  HexicHdApp* app_;
  HexicMenuInput input_;
  HexicControlsPanel controls_;
  bool has_opened_shown_ = false;
  Category category_ = kDisplay;
  int item_ = kItemDisplayMode;
  ImVec2 last_mouse_{-1.0f, -1.0f};
};

// Settings > Player Name: the name Hexic shows as your gamertag (High
// Scores, the new-high-score screen). Typed characters come from ImGui's
// input queue; empty means the Windows user name, as before.
class HexicNameEntryDialog : public rex::ui::ImGuiDialog {
 public:
  HexicNameEntryDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app);

  void OnDraw(ImGuiIO& io) override;

 protected:
  void OnClose() override;

 private:
  static constexpr size_t kMaxName = 15;  // an Xbox gamertag

  HexicHdApp* app_;
  HexicMenuInput input_{true};
  std::string text_;
  bool has_opened_shown_ = false;
  std::chrono::steady_clock::time_point opened_at_{};
};

// What Check for Updates found (HexicHdApp::StartUpdateCheck). Outside the
// app class: a nested type with default member initializers can't be used in
// the class's own static members.
enum class HexicUpdateState { kIdle, kChecking, kUpToDate, kAvailable, kFailed, kNoLauncher };
struct HexicUpdateStatus {
  HexicUpdateState state = HexicUpdateState::kIdle;
  std::string latest, error;
  uint64_t size = 0;
};

// Settings > Updates > Check for Updates: a small box (the PC dialogs' card)
// while a worker asks GitHub for the latest release (HexicHdApp::
// StartUpdateCheck, src/hexic_update.h), then its answer: up to date, could not
// check (with the reason), not in a release folder, or "Version X is available.
// You have Y." with Update / Cancel. Update starts the launcher's update
// ("Hexic HD.exe --update") and closes the game, from the main menu only.
// Nothing is checked unless the player opens this.
// Keys: Left / Right (or Up / Down) choose, Enter / A press, Esc / B close;
// mouse: hover chooses, click presses, right click closes.
class HexicUpdateDialog : public rex::ui::ImGuiDialog {
 public:
  HexicUpdateDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app);
  void OnDraw(ImGuiIO& io) override;

 protected:
  void OnClose() override;

 private:
  HexicHdApp* app_;
  HexicMenuInput input_;
  bool has_opened_shown_ = false;
  bool updating_ = false;  // Update pressed: the game is closing
  int selected_ = 0;
  ImVec2 last_mouse_{-1.0f, -1.0f};
  std::chrono::steady_clock::time_point opened_at_{};
};


// Invisible dialog that exists only for its per-frame OnDraw() hook
// (ImGuiDrawer only calls OnDraw() for dialogs in its list): it retries
// HexicHdApp::TrySetSignedInToLive() until the kernel is up, then closes.
class HexicSignInHook : public rex::ui::ImGuiDialog {
 public:
  explicit HexicSignInHook(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app)
      : rex::ui::ImGuiDialog(imgui_drawer), app_(app) {}

  void OnDraw(ImGuiIO& io) override;

 private:
  HexicHdApp* app_;
};

// Keycaps over the game's own pad icons when no controller is connected: in
// play the side panel's X (rotate counter-clockwise) and A (rotate clockwise)
// icons and the Start icon by "Pause"; in menus the B icon by "Back" / "Menu"
// and the A icon by "Next Page". The icons are vector shapes inside panels,
// not clips of their own, so their stage positions (1280 x 720) are fixed
// here per screen (hexic_mouse::g_screen, from the screen clip's label).
// Each cap shows the first key bound to that button.
class HexicKeycapOverlay : public rex::ui::ImGuiDialog {
 public:
  // swapped_frames: the game frames the GPU has swapped in so far.
  HexicKeycapOverlay(rex::ui::ImGuiDrawer* imgui_drawer,
                     std::function<uint64_t()> swapped_frames, bool trace)
      : rex::ui::ImGuiDialog(imgui_drawer),
        swapped_frames_(std::move(swapped_frames)),
        trace_(trace) {}

  // Passive: drawn with the game's frames, which repaint anyway.
  bool WantsContinuousRedraw() const override { return false; }

  void OnDraw(ImGuiIO& io) override {
    const auto now = std::chrono::steady_clock::now();
    // The screen in the picture on show, not as just set (hexic_mouse::NotePresent).
    const uint64_t swapped = swapped_frames_ ? swapped_frames_() : 0;
    const int screen = hexic_mouse::ScreenOnShow(swapped);
    if (trace_ && now >= next_trace_) {
      next_trace_ = now + std::chrono::seconds(5);
      REXLOG_INFO("[keycaps] game presents {}, frames swapped in {}, offset {}",
                  hexic_mouse::g_presents.load(), swapped, hexic_mouse::g_swap_offset.load());
    }
    if (screen == hexic_mouse::kScreenTitle) {
      DrawVersion(io);
      return;
    }
    // The game's own pad icons while a controller is the device in use
    // (hexic_input_mode.h: the last one used, following plugging in / out).
    if (screen == hexic_mouse::kScreenOther || hexic_input_mode::UsingController()) return;
    // The keys bound to each button (re-read once a second, after rebinding).
    if (now >= next_key_check_) {
      next_key_check_ = now + std::chrono::seconds(1);
      keys_[kKeyX] = FirstKey("keybind_x", "Q");
      keys_[kKeyA] = FirstKey("keybind_a", "E");
      keys_[kKeyStart] = FirstKey("keybind_start", "Esc");
      keys_[kKeyB] = FirstKey("keybind_b", "Bksp");
    }

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 pos = viewport ? viewport->Pos : ImVec2(0, 0);
    const ImVec2 size = viewport ? viewport->Size : io.DisplaySize;
    if (size.x <= 0 || size.y <= 0) return;
    const float scale = std::min(size.x / 1280.0f, size.y / 720.0f);
    const float ox = pos.x + (size.x - 1280.0f * scale) * 0.5f;
    const float oy = pos.y + (size.y - 720.0f * scale) * 0.5f;

    struct Cap {
      float x, y;  // stage pixels, icon centre
      int key;
      int grow;    // a wide cap grows: -1 left, 0 both ways, 1 right (away from the text)
    };
    static constexpr Cap kPlay[] = {
        {994, 481, kKeyX, 0}, {1015, 527, kKeyA, 0}, {983, 612, kKeyStart, 0}};
    static constexpr Cap kBack[] = {{862, 641, kKeyB, 1}};
    static constexpr Cap kHowTo[] = {{418, 641, kKeyA, -1}, {862, 641, kKeyB, 1}};
    static constexpr Cap kLeaderboard[] = {{1030, 618, kKeyB, 0}};
    const Cap* caps = nullptr;
    size_t count = 0;
    switch (screen) {
      case hexic_mouse::kScreenActive: caps = kPlay; count = std::size(kPlay); break;
      case hexic_mouse::kScreenBack: caps = kBack; count = std::size(kBack); break;
      case hexic_mouse::kScreenHowTo: caps = kHowTo; count = std::size(kHowTo); break;
      case hexic_mouse::kScreenLeaderboard:
        caps = kLeaderboard;
        count = std::size(kLeaderboard);
        break;
      default: return;
    }
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    ImFont* font = HexicFonts::body ? HexicFonts::body : ImGui::GetFont();
    for (size_t i = 0; i < count; ++i) {
      const Cap& cap = caps[i];
      const std::string& label = keys_[cap.key];
      // The pad icons are ~37 px across with their outline; cover them fully.
      const float h = 44.0f * scale;
      const float base_size = 22.0f * scale * (label.size() > 1 ? 0.8f : 1.0f);
      const ImVec2 text = font->CalcTextSizeA(base_size, FLT_MAX, 0, label.c_str());
      const float w = std::max(h, text.x + 14.0f * scale);
      const float cy = oy + cap.y * scale;
      const float cx = ox + cap.x * scale + cap.grow * (w - h) * 0.5f;
      const ImVec2 a(cx - w * 0.5f, cy - h * 0.5f), b(cx + w * 0.5f, cy + h * 0.5f);
      const float r = 6.0f * scale;
      // Key body: a darker base with a lighter top face, like a keycap.
      dl->AddRectFilled(ImVec2(a.x, a.y + 2 * scale), ImVec2(b.x, b.y + 2 * scale),
                        IM_COL32(20, 24, 34, 235), r);
      dl->AddRectFilled(a, b, IM_COL32(236, 240, 246, 255), r);
      dl->AddRectFilledMultiColor(ImVec2(a.x + 3 * scale, a.y + 3 * scale),
                                  ImVec2(b.x - 3 * scale, cy), IM_COL32(255, 255, 255, 120),
                                  IM_COL32(255, 255, 255, 120), IM_COL32(255, 255, 255, 0),
                                  IM_COL32(255, 255, 255, 0));
      dl->AddRect(a, b, IM_COL32(70, 80, 100, 255), r, 0, 1.5f * scale);
      dl->AddText(font, base_size, ImVec2(cx - text.x * 0.5f, cy - text.y * 0.5f),
                  IM_COL32(30, 36, 48, 255), label.c_str());
    }
  }

 private:
  // The title screen: the port's version, faint, in the stage's bottom-left
  // corner (dark background there, clear of the bezel).
  static void DrawVersion(ImGuiIO& io) {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    const ImVec2 pos = viewport ? viewport->Pos : ImVec2(0, 0);
    const ImVec2 size = viewport ? viewport->Size : io.DisplaySize;
    if (size.x <= 0 || size.y <= 0) return;
    const float scale = std::min(size.x / 1280.0f, size.y / 720.0f);
    const float ox = pos.x + (size.x - 1280.0f * scale) * 0.5f;
    const float oy = pos.y + (size.y - 720.0f * scale) * 0.5f;
    ImFont* font = HexicFonts::body ? HexicFonts::body : ImGui::GetFont();
    const float font_size = 17.0f * scale;
    const std::string text = std::string("v") + HEXIC_VERSION;
    const ImVec2 extent = font->CalcTextSizeA(font_size, FLT_MAX, 0, text.c_str());
    ImGui::GetBackgroundDrawList()->AddText(font, font_size,
                                            ImVec2(ox + 18.0f * scale, oy + (720.0f - 16.0f) * scale - extent.y),
                                            IM_COL32(0xDC, 0xD8, 0xF2, 90), text.c_str());
  }

  // First key of a binding, as printed on a key.
  static std::string FirstKey(const char* cvar, const char* fallback) {
    std::string keys = rex::cvar::GetFlagByName(cvar);
    std::string key = keys.substr(0, keys.find(','));
    while (!key.empty() && key.front() == ' ') key.erase(key.begin());
    while (!key.empty() && key.back() == ' ') key.pop_back();
    if (key.empty()) return fallback;
    if (key == "Escape") return "Esc";
    if (key == "Return") return "Enter";
    if (key == "Space") return "Space";
    if (key == "Backspace") return "Bksp";
    return key;
  }

  enum { kKeyX, kKeyA, kKeyStart, kKeyB, kKeyCount };
  std::function<uint64_t()> swapped_frames_;
  bool trace_ = false;
  std::chrono::steady_clock::time_point next_trace_{};
  std::chrono::steady_clock::time_point next_key_check_{};
  std::string keys_[kKeyCount] = {"Q", "E", "Esc", "Bksp"};
};

class HexicHdApp : public rex::ReXApp {
 public:
  using rex::ReXApp::ReXApp;

  static std::unique_ptr<rex::ui::WindowedApp> Create(
      rex::ui::WindowedAppContext& ctx) {
    auto app = std::unique_ptr<HexicHdApp>(new HexicHdApp(ctx, "hexic_hd",
        PPCImageConfig));
    current_instance_ = app.get();
    return app;
  }

  // Keep the game fully portable: assets, saves and cache all live in the
  // release folder rather than under the user's profile, so it can be moved or
  // backed up as a single unit (see hexic_paths). Importing the game data (STFS
  // extraction into assets\) is handled by the launcher in the release root, not
  // by this app.
  void OnConfigurePaths(rex::PathConfig& paths) override {
    const auto data_root = hexic_paths::DataRoot();

    const auto assets_path = data_root / "assets";
    if (!std::filesystem::is_directory(assets_path)) {
      // Preempt the SDK's generic "--game_data_root does not exist" message
      // (written for a CLI flag the player never typed) with one that tells
      // them what to actually do.
      MessageBoxW(nullptr,
                  hexic_paths::InRuntimeFolder()
                      ? L"Hexic HD's game data has not been imported yet.\n\n"
                        L"Open \"Hexic HD.exe\" in the main Hexic HD folder and select "
                        L"your Xbox 360 Hexic HD package."
                      : L"No Hexic HD game files found.\n\n"
                        L"Open \"Install Hexic HD.exe\" (beside the Game folder) "
                        L"and select your Xbox 360 Hexic HD package, then play again.",
                  L"Hexic HD", MB_OK | MB_ICONERROR);
      ExitProcess(1);
    }

    paths.game_data_root = assets_path;

    const auto custom = hexic_paths::CustomUserDataRoot();
    std::error_code ec;
    if (!custom.empty() && !std::filesystem::is_directory(custom, ec)) {
      // A chosen saves folder that is gone (a drive not connected, say): never
      // start with empty saves in its place.
      const std::wstring text = L"Hexic HD can't find your saves and settings folder:\n\n" +
                                custom.wstring() +
                                L"\n\nConnect the drive it is on, or open \"Hexic HD.exe\" with "
                                L"--setup to choose another folder.";
      MessageBoxW(nullptr, text.c_str(), L"Hexic HD", MB_OK | MB_ICONERROR);
      ExitProcess(1);
    }
    const auto user_data_path = hexic_paths::UserDataRoot();
    paths.user_data_root = user_data_path;
    paths.cache_root = user_data_path / "cache";
    paths.config_path = hexic_paths::ConfigPath();
  }

  std::string GetWindowTitle() const override { return "Hexic HD"; }

  // Game frames the GPU has swapped in (for the keycaps' frame timing).
  static uint64_t SwappedFrames() {
    HexicHdApp* app = current_instance_;
    auto* graphics = app && app->runtime() ? app->runtime()->graphics_system() : nullptr;
    return graphics ? graphics->guest_frame_count() : 0;
  }

  // window() is a protected ReXApp accessor; the settings dialog isn't part
  // of this class hierarchy so it needs a public way to check focus before
  // trusting GetAsyncKeyState/XInput, which both read system-wide input
  // state rather than state scoped to this window.
  bool HasWindowFocus() const { return window() && window()->HasFocus(); }

  // Load the game's own UI font (assets\convectionui.ttf) at PC settings
  // panel sizes, so the panel reads with Hexic HD's actual typography
  // instead of ImGui's tiny debug-overlay bitmap font. Runs before the
  // font atlas is built, so this is the supported place to add fonts (no
  // runtime atlas/texture rebuild required).
  void OnConfigureFonts(ImFontAtlas* atlas) override {
    const auto font_path = hexic_paths::DataRoot() / "assets" / "convectionui.ttf";
    if (!std::filesystem::exists(font_path)) {
      return;
    }

    std::string font_path_utf8 = font_path.string();
    ImFontConfig config;
    config.OversampleH = 3;
    config.OversampleV = 3;
    config.PixelSnapH = false;

    HexicFonts::body = atlas->AddFontFromFileTTF(font_path_utf8.c_str(), 19.0f, &config);
    HexicFonts::heading = atlas->AddFontFromFileTTF(font_path_utf8.c_str(), 27.0f, &config);
  }

  // Register the PC settings dialog in place of the stubbed Xbox
  // Achievements viewer once the ImGui drawer exists.
  void OnCreateDialogs(rex::ui::ImGuiDrawer* drawer) override {
    imgui_drawer_ = drawer;
    imgui_drawer_->AddDialog(new HexicSignInHook(imgui_drawer_, this));
    hexic_mouse::g_swap_counter.store(&HexicHdApp::SwappedFrames, std::memory_order_release);
    imgui_drawer_->AddDialog(new HexicKeycapOverlay(
        imgui_drawer_, &HexicHdApp::SwappedFrames,
        rex::cvar::GetFlagByName("hexic_menu_trace") == "true"));
    rex::kernel::xam::SetShowAchievementsUICallback([this]() {
      // The guest can call XamShowAchievementsUI more than once per press
      // (e.g. while input is held/repeating); only one settings dialog
      // should ever be open at a time.
      //
      // The SDK's input system also synthesizes a fresh "button down" edge
      // for whatever's currently held on a real controller the instant
      // guest input reactivates (see sdl_input_driver.cpp: "force buttons
      // to unpressed [while inactive]... send DOWN events when is_active()
      // goes high again"). Since this dialog blocks guest input while open,
      // closing it can immediately re-synthesize the very A press that's
      // still resting on the pad, instantly reopening it. A short cooldown
      // after close absorbs that stray edge without needing the SDK's
      // general reactivation behavior to change.
      auto now = std::chrono::steady_clock::now();
      bool in_cooldown = now - last_dialog_closed_time_ < std::chrono::milliseconds(400);
      if (modal_depth_ == 0 && !in_cooldown) {
        OpenSettings(HexicSettingsDialog::kItemDisplayMode);
      }
    });

  }

  // Keyboard play is always on and works alongside a controller (the SDK
  // merges the two). Hexic has no mouse aiming, so the cursor stays free, and
  // its menus read the D-pad and the stick separately, so a D-pad key must not
  // also push the stick (that moved two rows per press). The Hexic key
  // defaults are applied once per config; after that the player's own
  // bindings are kept.
  void OnPostSetup() override {
    // The game always runs at 60 fps. Parts of Hexic move once per frame, so
    // with V-Sync off the 1000 Hz guest vblank (~220 fps) sped them up; with
    // a fixed vblank V-Sync only decides whether frames may tear.
    rex::cvar::SetFlagByName("fixed_guest_vblank", "true");
    startup_renderer_ = GetPcRenderer();
    ApplyWindowIcons();
    hexic_system_info::Log();
    rex::cvar::SetFlagByName("mnk_mode", "true");
    rex::cvar::SetFlagByName("mnk_mouse", "false");
    rex::cvar::SetFlagByName("mnk_dpad_to_stick", "false");
    // The title prompt suits the input present now, plus later PC wording;
    // the game reads g.xml after this, as it starts.
    auto* input_system =
        runtime() ? static_cast<rex::input::InputSystem*>(runtime()->input_system()) : nullptr;
    const bool controller_at_start = hexic_title::ControllerConnected() ||
                                     (input_system && input_system->AnyControllerConnected());
    hexic_title::ApplyMenuText(hexic_paths::DataRoot() / "assets", controller_at_start);
    // Button prompts follow the device in use (hexic_input_mode.h).
    hexic_input_mode::g_mode.store(controller_at_start ? hexic_input_mode::kController
                                                       : hexic_input_mode::kKeyboardMouse);
    if (input_system) {
      input_system->SetControllerActivityCallback(&hexic_input_mode::NoteController);
    }
    // Extra pad input on every poll the game makes: test presses, and any key
    // or click as A on the title screen (hexic_input.h, hexic_title.h).
    // Test input SETTING=name,value (hexic_input.h): a Settings change, on the
    // UI thread like the dialog's.
    hexic_input::TestPresses::g_setting_hook = [this](std::string name, std::string value) {
      // The update box: SETTING=open_updates,1 opens it as Settings would;
      // SETTING=dialog,down|up|press|back drives it (its keys are real input).
      if (name == "dialog") {
        if (value == "down") ++test_dialog_moves_;
        if (value == "up") --test_dialog_moves_;
        if (value == "press") test_dialog_press_ = true;
        if (value == "back") test_dialog_back_ = true;
        return;
      }
      app_context().CallInUIThread([this, name, value]() {
        if (name == "open_updates") OpenUpdateDialog();
        if (name == "open_settings") OpenSettings(std::atoi(value.c_str()));  // the row to select
        const int number = std::atoi(value.c_str());
        if (name == "render_scale") SetPcRenderScale(number);
        if (name == "fsr") SetPcFsr(number != 0);
        if (name == "aa") SetPcAntiAliasing(number);
        if (name == "vsync") SetPcVSync(number != 0);
        if (name == "show_fps") SetPcShowFps(number != 0);
      });
    };
    menu_mouse_.SetWindow(game_window_);
    if (window()) window()->AddInputListener(&title_input_, 0);
    menu_mouse_.SetTrace(rex::cvar::GetFlagByName("hexic_menu_trace") == "true");
    if (runtime() && runtime()->input_system()) {
      static_cast<rex::input::InputSystem*>(runtime()->input_system())
          ->SetPadFilterCallback([this](uint16_t& buttons, int16_t& lx, int16_t& ly) {
            const bool title = OnTitleScreen();
            buttons |= test_presses_.Poll() | any_key_starts_.Poll(title);
            if (!title) {
              menu_mouse_.Poll(runtime() ? runtime()->memory() : nullptr, buttons, lx, ly,
                               MouseBelongsToDialog());
            }
          });
    }
    // No saved name (a new install, or one left empty): pick one from the list
    // rather than showing the Windows account name, and keep it.
    if (SavedPlayerName().empty()) {
      rex::cvar::SetFlagByName("net_player_name", hexic_player_names::Random());
      SavePcSettings();
      REXLOG_INFO("[name] assigned the player name \"{}\"", SavedPlayerName());
    }
    if (REXCVAR_GET(hexic_controls_version) < hexic_controls::kDefaultsVersion) {
      hexic_controls::Upgrade(REXCVAR_GET(hexic_controls_version));
      REXCVAR_SET(hexic_controls_version, hexic_controls::kDefaultsVersion);
      SavePcSettings();
      REXLOG_INFO("[controls] keyboard defaults now version {}", hexic_controls::kDefaultsVersion);
    }
  }

  // The game window's key and mouse input: on the title screen any key or
  // mouse button counts (hexic_title.h), and any of it (or a real mouse move)
  // switches the button prompts to the keyboard and mouse (hexic_input_mode.h).
  // Alt and the Windows keys come with switching windows, so they don't count.
  class TitleInputListener : public rex::ui::WindowInputListener {
   public:
    explicit TitleInputListener(hexic_title::AnyKeyStarts* target) : target_(target) {}
    void OnKeyDown(rex::ui::KeyEvent& e) override {
      using rex::ui::VirtualKey;
      const VirtualKey key = e.virtual_key();
      if (key != VirtualKey::kMenu && key != VirtualKey::kLMenu && key != VirtualKey::kRMenu &&
          key != VirtualKey::kLWin && key != VirtualKey::kRWin && e.repeat_count() == 0) {
        target_->NotePress();
        hexic_input_mode::NoteKeyboardMouse();
      }
    }
    void OnMouseDown(rex::ui::MouseEvent&) override {
      target_->NotePress();
      hexic_input_mode::NoteKeyboardMouse();
    }
    void OnMouseMove(rex::ui::MouseEvent& e) override { moves_.Note(e.x(), e.y()); }
    void OnMouseWheel(rex::ui::MouseEvent&) override { hexic_input_mode::NoteKeyboardMouse(); }

   private:
    hexic_title::AnyKeyStarts* target_;
    hexic_input_mode::MouseMoves moves_;
  };

  // --- the PC dialogs --------------------------------------------------------
  // While any of them is open the game must not act on the keys used in it, so
  // the keyboard mapping is off from the first dialog opening until the last
  // one closes. A dialog handing over to another opens the next one before
  // closing itself, so the count never drops to zero in between.
  void BeginModal() {
    if (modal_depth_++ == 0) rex::cvar::SetFlagByName("mnk_mode", "false");
    modal_open_.store(true, std::memory_order_release);
  }

  void EndModal() {
    if (modal_depth_ > 0 && --modal_depth_ == 0) {
      rex::cvar::SetFlagByName("mnk_mode", "true");
      last_dialog_closed_time_ = std::chrono::steady_clock::now();
      modal_closed_at_.store(last_dialog_closed_time_.time_since_epoch().count(),
                             std::memory_order_relaxed);
      modal_open_.store(false, std::memory_order_release);
    }
  }

  // Game thread: whether the game's menus must leave the mouse alone - a PC
  // dialog is open, or closed under 150 ms ago (the click that closed it can
  // still be down at the next pad poll).
  bool MouseBelongsToDialog() const {
    if (modal_open_.load(std::memory_order_acquire)) return true;
    const auto closed = std::chrono::steady_clock::time_point(
        std::chrono::steady_clock::duration(modal_closed_at_.load(std::memory_order_relaxed)));
    return std::chrono::steady_clock::now() - closed < std::chrono::milliseconds(150);
  }

  void OpenSettings(int select_row) {
    if (imgui_drawer_) {
      imgui_drawer_->AddDialog(new HexicSettingsDialog(imgui_drawer_, this, select_row));
    }
  }

  void OpenNameEntry() {
    if (imgui_drawer_) imgui_drawer_->AddDialog(new HexicNameEntryDialog(imgui_drawer_, this));
  }


  // ---- Settings > Updates > Check for Updates ------------------------------
  // Only when the player asks (ported from Perfect Dark's): the box asks
  // GitHub for the latest release on a worker thread. Update starts the
  // launcher with --update and closes the game, from the main menu only; the
  // launcher downloads, verifies and installs the release, then starts the
  // game again.
  using UpdateState = HexicUpdateState;
  using UpdateStatus = HexicUpdateStatus;
  static inline std::mutex update_mutex_;
  static inline UpdateStatus update_status_;
  static inline uint64_t update_check_id_ = 0;  // a newer check makes an older answer stale
  // Test input SETTING=dialog,down|press|back (hexic_input.h) drives the box.
  static inline std::atomic<int> test_dialog_moves_{0};
  static inline std::atomic<bool> test_dialog_press_{false}, test_dialog_back_{false};

  static UpdateStatus CurrentUpdateStatus() {
    std::lock_guard<std::mutex> lock(update_mutex_);
    return update_status_;
  }

  // The release folder's launcher (root\Hexic HD.exe, two folders above
  // resources\runtime\hexic_hd.exe); empty outside the release layout.
  static std::filesystem::path LauncherPath() {
    wchar_t exe[32768] = {};
    GetModuleFileNameW(nullptr, exe, 32768);
    const std::filesystem::path runtime = std::filesystem::path(exe).parent_path();
    if (_wcsicmp(runtime.filename().c_str(), L"runtime") != 0) return {};
    const std::filesystem::path launcher = runtime.parent_path().parent_path() / L"Hexic HD.exe";
    std::error_code ec;
    return std::filesystem::exists(launcher, ec) ? launcher : std::filesystem::path();
  }

  static void StartUpdateCheck() {
    uint64_t id = 0;
    {
      std::lock_guard<std::mutex> lock(update_mutex_);
      update_status_ = UpdateStatus{};
      update_status_.state = LauncherPath().empty() ? UpdateState::kNoLauncher : UpdateState::kChecking;
      if (update_status_.state != UpdateState::kChecking) return;
      id = ++update_check_id_;
    }
    std::thread([id] {
      hexic_update::Release release;
      std::string error;
      const std::wstring agent = L"Hexic-HD-PC/" + hexic_update::Widen(HEXIC_VERSION);
      bool ok = hexic_update::LatestRelease(release, agent, error);
      const bool newer = ok && hexic_update::CompareVersions(release.version, HEXIC_VERSION) > 0;
      if (newer && !release.asset_error.empty()) {  // newer, but its download can't be used
        ok = false;
        error = release.asset_error;
      }
      std::lock_guard<std::mutex> lock(update_mutex_);
      if (id != update_check_id_ || update_status_.state != UpdateState::kChecking) return;  // closed meanwhile
      update_status_.latest = release.version;
      update_status_.size = release.zip_size;
      update_status_.error = error;
      update_status_.state = !ok ? UpdateState::kFailed : newer ? UpdateState::kAvailable : UpdateState::kUpToDate;
      REXLOG_INFO("[update] latest release {} (this copy {}): {}", ok ? release.version : "?", HEXIC_VERSION,
                  ok ? (update_status_.state == UpdateState::kAvailable ? "newer" : "not newer") : error);
    }).detach();
  }

  // Updating closes the game, so only from the main menu (not mid-game, its
  // pause menu or a level card).
  static bool UpdateIsSafe() { return hexic_mouse::g_on_main_menu.load(std::memory_order_relaxed); }

  // Starts the launcher's update window and closes the game (the window's
  // close button path, which exits in a fraction of a second; a watchdog ends
  // the process if that ever stalls, so the launcher is never left waiting).
  bool StartUpdater() {
    const std::filesystem::path launcher = LauncherPath();
    if (launcher.empty()) return false;
    std::wstring command = L"\"" + launcher.wstring() + L"\" --update";
    STARTUPINFOW startup = {sizeof(startup)};
    PROCESS_INFORMATION process = {};
    if (!CreateProcessW(launcher.c_str(), command.data(), nullptr, nullptr, FALSE, 0, nullptr,
                        launcher.parent_path().c_str(), &startup, &process)) {
      REXLOG_ERROR("[update] could not start the launcher (error {})", GetLastError());
      return false;
    }
    AllowSetForegroundWindow(process.dwProcessId);
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    REXLOG_INFO("[update] started the launcher's update; closing the game");
    std::thread([] {
      Sleep(10000);
      REXLOG_WARN("[update] the game did not close in 10 s; ending it");
      TerminateProcess(GetCurrentProcess(), 0);
    }).detach();
    if (game_window_) PostMessageW(game_window_, WM_CLOSE, 0, 0);
    return true;
  }

  void OpenUpdateDialog() {
    if (!imgui_drawer_) return;
    StartUpdateCheck();
    imgui_drawer_->AddDialog(new HexicUpdateDialog(imgui_drawer_, this));
  }
  void OnUpdateDialogClosed() {
    std::lock_guard<std::mutex> lock(update_mutex_);
    update_status_.state = UpdateState::kIdle;
  }

  // The name Hexic shows: the saved player name, else the Windows user name
  // (the SDK's netplay::PlayerName rule, which XamUserGetName follows).
  static std::string PlayerName() {
    std::string profile_name = "Player";
    if (auto* kernel_state = REX_KERNEL_STATE()) {
      if (const auto& profile = kernel_state->user_profile()) profile_name = profile->name();
    }
    return rex::kernel::xam::netplay::ConfiguredPlayerName(profile_name);
  }

  static std::string SavedPlayerName() { return rex::cvar::GetFlagByName("net_player_name"); }

  // An empty name draws a new one from the list.
  void SetPlayerName(const std::string& name) {
    rex::cvar::SetFlagByName("net_player_name",
                             name.empty() ? hexic_player_names::Random() : name);
    SavePcSettings();
    REXLOG_INFO("[name] player name is now \"{}\"", PlayerName());
    RefreshGameGamertag();
  }

  // Hexic reads the gamertag only when a profile signs in. The path from the
  // sign-in notification to the name, all verified before anything is
  // touched:
  //  - the profile manager at 0x9226FC18 holds a callback (+132) and its
  //    context (+136), set by sub_92053FE8;
  //  - the callback, thunk 0x92053558, calls the context's vtable+20,
  //    sub_9204E188, which calls vtable+36 of the game object stored at
  //    0x9226FC14;
  //  - that is sub_92052B40, which re-reads the name and updates the
  //    "Player:" label only when the game object's signed-out flag (+16) is
  //    set.
  // So set that flag and send XN_SYS_SIGNINCHANGED, and the game takes the
  // new name as if the player had just signed in.
  void RefreshGameGamertag() {
    constexpr uint32_t kProfileManager = 0x9226FC18;
    constexpr uint32_t kGameObjectSlot = 0x9226FC14;
    constexpr uint32_t kSignInThunk = 0x92053558;
    constexpr uint32_t kForwarder = 0x9204E188;
    constexpr uint32_t kSignInMethod = 0x92052B40;
    auto* kernel_state = REX_KERNEL_STATE();
    auto* memory = runtime() ? runtime()->memory() : nullptr;
    if (!kernel_state || !memory) return;
    // Reads a guest word, or 0 if the address isn't mapped guest memory.
    auto read_u32 = [memory](uint32_t address) -> uint32_t {
      if (!address || !memory->LookupHeap(address)) return 0;
      return rex::memory::load_and_swap<uint32_t>(memory->TranslateVirtual<uint8_t*>(address));
    };
    auto virtual_method = [&](uint32_t object, uint32_t offset) -> uint32_t {
      const uint32_t vtable = read_u32(object);
      return vtable ? read_u32(vtable + offset) : 0;
    };
    const uint32_t callback = read_u32(kProfileManager + 132);
    const uint32_t context = read_u32(kProfileManager + 136);
    const uint32_t forwarder = context ? virtual_method(context, 20) : 0;
    const uint32_t game_object = read_u32(kGameObjectSlot);
    const uint32_t method = game_object ? virtual_method(game_object, 36) : 0;
    if (callback != kSignInThunk || forwarder != kForwarder || method != kSignInMethod) {
      REXLOG_WARN("[name] sign-in path not as expected ({:08X}, {:08X}, {:08X}); the new "
                  "name shows after a restart",
                  callback, forwarder, method);
      return;
    }
    memory->TranslateVirtual<uint8_t*>(game_object)[16] = 1;
    kernel_state->BroadcastNotification(0x0000000A, 0x1);  // XN_SYS_SIGNINCHANGED
  }

  // Hexic's Leaderboards screen (Scaleform/Flash) checks a "_SignedInToLive"
  // flag and shows its own "please sign in" page while it's false, before
  // asking for any stats. Reporting the profile as signed in to Xbox LIVE lets
  // it ask; the SDK then answers from its local leaderboards, which the
  // game's own end-of-run stats writes fill (Marathon, Timed and Survival).
  // kernel_state()/user_profile() don't exist yet in OnCreateDialogs, so
  // HexicSignInHook retries this every frame until it succeeds.
  bool TrySetSignedInToLive() {
    auto* kernel_state = REX_KERNEL_STATE();
    auto* profile = kernel_state ? kernel_state->user_profile() : nullptr;
    if (!profile) return false;
    profile->set_signin_state(2);
    return true;
  }

  // SDL gives the window class only the large icon (LoadIcon), so Windows
  // shrinks the 32 px flower for the title bar. Hand the game window both
  // sizes from the exe's icon (src/hexic_hd.rc) at its DPI, so the title bar
  // gets the icon's own small image (the three-gem cluster at 16 and 24 px).
  static void ApplyWindowIcons() {
    EnumWindows(
        [](HWND hwnd, LPARAM) -> BOOL {
          DWORD pid = 0;
          GetWindowThreadProcessId(hwnd, &pid);
          if (pid != GetCurrentProcessId() || !IsWindowVisible(hwnd)) return TRUE;
          game_window_ = hwnd;
          const UINT dpi = GetDpiForWindow(hwnd) ? GetDpiForWindow(hwnd) : 96;
          HINSTANCE module = GetModuleHandleW(nullptr);
          auto load = [&](int metric) {
            const int size = GetSystemMetricsForDpi(metric, dpi);
            return reinterpret_cast<HICON>(
                LoadImageW(module, MAKEINTRESOURCEW(1), IMAGE_ICON, size, size, LR_DEFAULTCOLOR));
          };
          // Icons loaded this way live until the process ends, as the window does.
          // ("small" is a macro in the Windows headers, hence these names.)
          if (HICON icon_big = load(SM_CXICON)) {
            SendMessageW(hwnd, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(icon_big));
          }
          if (HICON icon_small = load(SM_CXSMICON)) {
            SendMessageW(hwnd, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(icon_small));
          }
          return TRUE;
        },
        0);
  }

  // The "Press A to continue" title screen is showing (see hexic_title.h).
  bool OnTitleScreen() {
    auto* memory = runtime() ? runtime()->memory() : nullptr;
    if (!memory || !memory->LookupHeap(hexic_title::kActivePadSlot)) return false;
    return rex::memory::load_and_swap<uint32_t>(memory->TranslateVirtual<uint8_t*>(
               hexic_title::kActivePadSlot)) == hexic_title::kNoActivePad;
  }

  static void SavePcSettings() {
    HexicHdApp* app = current_instance_;
    if (!app || app->config_path().empty()) {
      return;
    }
    // Use the exact same config file as the F4 settings overlay.
    rex::cvar::SaveConfig(app->config_path());
  }

  // Resolution is the output (window) size only; Render Scale is separate.
  static void SetPcResolution(int32_t width, int32_t height) {
    HexicHdApp* app = current_instance_;
    if (!app) {
      return;
    }

    bool changed = false;
    changed |= rex::cvar::SetFlagByName("video_mode_width", std::to_string(width));
    changed |= rex::cvar::SetFlagByName("video_mode_height", std::to_string(height));

    if (changed) {
      SavePcSettings();
    }

    // Apply the output/window resolution immediately.
    app->app_context().CallInUIThreadDeferred([app, width, height]() {
      if (app->window()) {
        auto* sdl_window = static_cast<rex::ui::WindowSDL*>(app->window());
        sdl_window->SetLogicalSize(width, height);
      }
    });
  }

  // Render Scale: how many times the game's own 1280 x 720 picture is
  // rendered in each direction (1x, 2x or 3x), independent of the output
  // resolution. More is sharper and costs the graphics card more.
  static int32_t GetPcRenderScale() {
    const int32_t scale = std::atoi(rex::cvar::GetFlagByName("resolution_scale").c_str());
    return scale >= 1 && scale <= 3 ? scale : 1;
  }

  static void SetPcRenderScale(int32_t scale) {
    HexicHdApp* app = current_instance_;
    if (!app || scale < 1 || scale > 3) {
      return;
    }
    if (!rex::cvar::SetFlagByName("resolution_scale", std::to_string(scale))) {
      return;
    }
    SavePcSettings();
    // Rebuild scale-dependent graphics resources immediately.
    if (app->runtime() && app->runtime()->graphics_system()) {
      app->runtime()->graphics_system()->ReinitializeContext();
    }
  }

  static int32_t GetPcResolutionIndex() {
    std::string width = rex::cvar::GetFlagByName("video_mode_width");
    std::string height = rex::cvar::GetFlagByName("video_mode_height");

    if (width == "1280" && height == "720") return 0;
    if (width == "1920" && height == "1080") return 1;
    if (width == "2560" && height == "1440") return 2;
    if (width == "3840" && height == "2160") return 3;
    return 1;
  }

  // Renderer: 0 Auto (Direct3D 12 on NVIDIA, Vulkan on other GPUs), 1 Direct3D
  // 12, 2 Vulkan. The SDK reads the "gpu" cvar once at start, so a change
  // applies on the next restart.
  static int GetPcRenderer() {
    const std::string value = rex::cvar::GetFlagByName("gpu");
    return value == "d3d12" ? 1 : value == "vulkan" ? 2 : 0;
  }

  static void SetPcRenderer(int renderer) {
    static const char* kValues[3] = {"auto", "d3d12", "vulkan"};
    if (renderer >= 0 && renderer < 3 && rex::cvar::SetFlagByName("gpu", kValues[renderer])) {
      SavePcSettings();
    }
  }

  static bool PcRendererPendingRestart() { return GetPcRenderer() != startup_renderer_; }

  // Anti-Aliasing: 0 Off, 1 FXAA, 2 FXAA Extreme (swap_post_effect, a filter on
  // the finished picture). The SDK re-reads it every vblank, so it applies live.
  static int GetPcAntiAliasing() {
    const std::string value = rex::cvar::GetFlagByName("swap_post_effect");
    return value == "fxaa" ? 1 : value == "fxaa_extreme" ? 2 : 0;
  }

  static void SetPcAntiAliasing(int mode) {
    static const char* kValues[3] = {"none", "fxaa", "fxaa_extreme"};
    if (mode >= 0 && mode < 3 && rex::cvar::SetFlagByName("swap_post_effect", kValues[mode])) {
      SavePcSettings();
    }
  }

  // Upscaling: off (bilinear) or AMD FSR 1, which scales the game's picture up
  // to the window with sharper edges when the window is larger than the render
  // size. present_effect is read by the presenter, so it is reloaded here.
  static bool GetPcFsr() { return rex::cvar::GetFlagByName("present_effect") == "fsr"; }

  static void SetPcFsr(bool enabled) {
    HexicHdApp* app = current_instance_;
    if (!app || !rex::cvar::SetFlagByName("present_effect", enabled ? "fsr" : "bilinear")) {
      return;
    }
    SavePcSettings();
    app->app_context().CallInUIThreadDeferred([app]() {
      auto* graphics = app->runtime() ? app->runtime()->graphics_system() : nullptr;
      if (graphics && graphics->presenter()) {
        graphics->presenter()->ReloadGuestOutputPaintConfigFromCVarsFromUIThread();
      }
    });
  }

  static bool GetPcVSync() {
    std::string value = rex::cvar::GetFlagByName("vsync");
    return value == "true" || value == "1";
  }

  static void SetPcVSync(bool enabled) {
    if (rex::cvar::SetFlagByName("vsync", enabled ? "true" : "false")) {
      SavePcSettings();
    }
  }

  static bool GetPcShowFps() {
    std::string value = rex::cvar::GetFlagByName("show_fps");
    return value == "true" || value == "1";
  }

  static void SetPcShowFps(bool enabled) {
    if (rex::cvar::SetFlagByName("show_fps", enabled ? "true" : "false")) {
      SavePcSettings();
    }
  }

  static bool GetPcFullscreen() {
    std::string value = rex::cvar::GetFlagByName("fullscreen");
    return value == "true" || value == "1";
  }

  static void SetPcFullscreen(bool fullscreen) {
    HexicHdApp* app = current_instance_;
    if (!app) {
      return;
    }

    if (rex::cvar::SetFlagByName("fullscreen", fullscreen ? "true" : "false")) {
      SavePcSettings();
    }

    // Window state changes belong on the UI thread.
    app->app_context().CallInUIThreadDeferred([app, fullscreen]() {
      if (app->window()) {
        app->window()->SetFullscreen(fullscreen);
      }
    });
  }

  // Override virtual hooks for customization:
  // void OnPostInitLogging() override {}
  // void OnPreSetup(rex::RuntimeConfig& config) override {}
  // void OnLoadXexImage(std::string& xex_image) override {}
  // void OnPostLoadXexImage() override {}
  // std::unique_ptr<rex::ui::ImGuiDialog> CreateAchievementsOverlay() override;
  // std::unique_ptr<rex::ui::AchievementNotificationDialog>
  // CreateAchievementNotificationDialog() override;
  // void OnShutdown() override {}

 private:
  inline static HexicHdApp* current_instance_ = nullptr;
  inline static int startup_renderer_ = 0;  // GetPcRenderer() when the game started
  hexic_input::TestPresses test_presses_;
  hexic_title::AnyKeyStarts any_key_starts_;
  TitleInputListener title_input_{&any_key_starts_};
  hexic_mouse::MenuMouse menu_mouse_;
  inline static HWND game_window_ = nullptr;  // found by ApplyWindowIcons
  rex::ui::ImGuiDrawer* imgui_drawer_ = nullptr;
  int modal_depth_ = 0;
  std::chrono::steady_clock::time_point last_dialog_closed_time_{};
  // The same, for the game thread (pad filter).
  std::atomic<bool> modal_open_{false};
  std::atomic<int64_t> modal_closed_at_{0};  // steady_clock ticks
};


namespace hexic_ui {

// Centers the next dialog window and makes its background transparent, so
// only the drawn card shows. Pair with PopDialogStyle().
inline void PushDialogStyle(ImGuiIO& io, float width) {
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImVec2 center = viewport ? ImVec2(viewport->WorkPos.x + viewport->WorkSize.x * 0.5f,
                                    viewport->WorkPos.y + viewport->WorkSize.y * 0.5f)
                           : ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
  ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
  ImGui::SetNextWindowSize(ImVec2(width, 0), ImGuiCond_Always);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 18.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));
}

inline void PopDialogStyle() {
  ImGui::PopStyleColor(1);
  ImGui::PopStyleVar(3);
}

inline ImFont* BodyFont() { return HexicFonts::body ? HexicFonts::body : ImGui::GetFont(); }
inline float BodySize() { return HexicFonts::body ? 19.0f : ImGui::GetFontSize(); }

// A line of dim help text, centered between x0 and x1.
inline void DrawHint(ImDrawList* draw_list, float x0, float x1, float y, const char* text) {
  ImVec2 size = BodyFont()->CalcTextSizeA(BodySize(), FLT_MAX, 0, text);
  draw_list->AddText(BodyFont(), BodySize(), ImVec2(x0 + (x1 - x0 - size.x) * 0.5f, y), kTextDim,
                     text);
}

}  // namespace hexic_ui

// --- Settings -------------------------------------------------------------

namespace hexic_settings_ui {
// Clean, flat palette: a dark panel over the dimmed game, Hexic's green for
// the current choice and the selection marker.
constexpr ImU32 kDim = IM_COL32(0x05, 0x04, 0x0E, 150);
constexpr ImU32 kPanel = IM_COL32(0x10, 0x0C, 0x26, 242);
constexpr ImU32 kSidebar = IM_COL32(0x0A, 0x07, 0x19, 255);
constexpr ImU32 kInk = IM_COL32(0xF4, 0xF2, 0xFF, 255);
constexpr ImU32 kSoft = IM_COL32(0xDC, 0xD8, 0xF2, 255);
constexpr ImU32 kMuted = IM_COL32(0x9C, 0x97, 0xC4, 255);
constexpr ImU32 kFaint = IM_COL32(0x6E, 0x68, 0xA0, 255);
constexpr ImU32 kGreen = IM_COL32(0x7D, 0xE3, 0x6A, 255);
constexpr ImU32 kOnGreen = IM_COL32(0x0C, 0x2A, 0x06, 255);
constexpr ImU32 kHover = IM_COL32(0xFF, 0xFF, 0xFF, 14);
constexpr ImU32 kOutline = IM_COL32(0xFF, 0xFF, 0xFF, 44);
constexpr ImU32 kOutlineFocus = IM_COL32(0xFF, 0xFF, 0xFF, 110);

constexpr float kWidth = 780.0f;
constexpr float kHeight = 440.0f;
constexpr float kSidebarWidth = 220.0f;
constexpr float kRowHeight = 50.0f;
constexpr float kRowPitch = 58.0f;

inline ImFont* Font() { return HexicFonts::body ? HexicFonts::body : ImGui::GetFont(); }
inline ImFont* TitleFont() { return HexicFonts::heading ? HexicFonts::heading : Font(); }

inline void Text(ImDrawList* dl, ImFont* font, float size, ImVec2 pos, ImU32 color, const char* text) {
  dl->AddText(font, size, pos, color, text);
}
inline float Width(ImFont* font, float size, const char* text) {
  return font->CalcTextSizeA(size, FLT_MAX, 0, text).x;
}
inline bool Inside(ImVec2 p, ImVec2 lo, ImVec2 hi) {
  return p.x >= lo.x && p.x < hi.x && p.y >= lo.y && p.y < hi.y;
}
}  // namespace hexic_settings_ui

inline HexicSettingsDialog::HexicSettingsDialog(rex::ui::ImGuiDrawer* imgui_drawer,
                                                HexicHdApp* app, int select_item)
    : rex::ui::ImGuiDialog(imgui_drawer), app_(app) {
  item_ = (select_item >= 0 && select_item < kItemCount) ? select_item : kItemDisplayMode;
  category_ = CategoryOf(item_);
  app_->BeginModal();
}

inline void HexicSettingsDialog::OnClose() {
  if (app_) app_->EndModal();
}

inline HexicSettingsDialog::Category HexicSettingsDialog::CategoryOf(int item) {
  if (item <= kItemShowFps) return kDisplay;
  if (item <= kItemRenderer) return kGraphics;
  if (item == kRowUpdates) return kUpdates;
  return item == kRowPlayerName ? kPlayer : kControls;
}

inline int HexicSettingsDialog::FirstItem(Category category) {
  static const int kFirst[kCategoryCount] = {kItemDisplayMode, kItemRenderScale, kRowPlayerName,
                                             kRowControls, kRowUpdates};
  return kFirst[category];
}

inline int HexicSettingsDialog::ItemCount(Category category) {
  static const int kCount[kCategoryCount] = {4, 4, 1, 1, 1};
  return kCount[category];
}

inline std::vector<const char*> HexicSettingsDialog::Options(int item) {
  switch (item) {
    case kItemDisplayMode: return {"Windowed", "Fullscreen"};
    case kItemResolution: return {"1280 x 720", "1920 x 1080", "2560 x 1440", "3840 x 2160"};
    case kItemVSync: return {"Off", "On"};
    case kItemShowFps: return {"Off", "On"};
    case kItemRenderScale: return {"1x", "2x", "3x"};
    case kItemAntiAliasing: return {"Off", "FXAA", "Extreme"};
    case kItemUpscaling: return {"Off", "FSR"};
    case kItemRenderer: return {"Auto", "D3D12", "Vulkan"};
    default: return {};
  }
}

inline int HexicSettingsDialog::Current(int item) {
  switch (item) {
    case kItemDisplayMode: return HexicHdApp::GetPcFullscreen() ? 1 : 0;
    case kItemResolution: return HexicHdApp::GetPcResolutionIndex();
    case kItemVSync: return HexicHdApp::GetPcVSync() ? 1 : 0;
    case kItemShowFps: return HexicHdApp::GetPcShowFps() ? 1 : 0;
    case kItemRenderScale: return HexicHdApp::GetPcRenderScale() - 1;
    case kItemAntiAliasing: return HexicHdApp::GetPcAntiAliasing();
    case kItemUpscaling: return HexicHdApp::GetPcFsr() ? 1 : 0;
    case kItemRenderer: return HexicHdApp::GetPcRenderer();
    default: return 0;
  }
}

inline void HexicSettingsDialog::Choose(int item, int option) {
  if (option == Current(item)) return;
  switch (item) {
    case kItemDisplayMode: HexicHdApp::SetPcFullscreen(option == 1); break;
    case kItemResolution: {
      static const int32_t kW[] = {1280, 1920, 2560, 3840};
      static const int32_t kH[] = {720, 1080, 1440, 2160};
      HexicHdApp::SetPcResolution(kW[option], kH[option]);
      break;
    }
    case kItemVSync: HexicHdApp::SetPcVSync(option == 1); break;
    case kItemShowFps: HexicHdApp::SetPcShowFps(option == 1); break;
    case kItemRenderScale: HexicHdApp::SetPcRenderScale(option + 1); break;
    case kItemAntiAliasing: HexicHdApp::SetPcAntiAliasing(option); break;
    case kItemUpscaling: HexicHdApp::SetPcFsr(option == 1); break;
    case kItemRenderer: HexicHdApp::SetPcRenderer(option); break;
    default: break;
  }
}

inline const char* HexicSettingsDialog::Label(int item) {
  static const char* kLabels[kItemCount] = {
      "Display mode",  "Window size", "VSync",    "Show FPS",    "Render scale",
      "Anti-aliasing", "Upscaling",  "Renderer", "Player name", "Keyboard controls",
      "Check for Updates",
  };
  return kLabels[item];
}

inline std::string HexicSettingsDialog::Help(int item) {
  switch (item) {
    case kItemDisplayMode: return "Play in a window or fill the screen";
    case kItemResolution:
      return HexicHdApp::GetPcFullscreen() ? "Used when windowed. Fullscreen fills the display"
                                           : "The size of the game window";
    case kItemVSync:
      return "Always 60 fps. On: no tearing" +
             std::string(HexicHdApp::GetPcRenderer() == 2 ? " (Vulkan: applies after a restart)" : "");
    case kItemShowFps: return "Frame rate in the top corner";
    case kItemRenderScale: return "Draws the game at 2 or 3 times the detail. Sharper, more work";
    case kItemAntiAliasing: return "Smooths edges on the finished picture";
    case kItemUpscaling: return "Sharper picture when the window is bigger than 1280 x 720";
    case kItemRenderer:
      return HexicHdApp::PcRendererPendingRestart()
                 ? "Applies the next time you start the game"
                 : "Auto: Direct3D 12 on NVIDIA, Vulkan on AMD and Intel";
    case kRowPlayerName: return "Shown on High Scores";
    case kRowControls: return "Change the key for every controller button";
    case kRowUpdates: return "Asks GitHub for a newer version. Nothing is checked unless you ask";
    default: return "";
  }
}

inline void HexicSettingsDialog::SelectCategory(Category category) {
  category_ = category;
  item_ = FirstItem(category);
}

// Player name and Keyboard controls open their own page; this panel closes
// after the page opens, so the game's keyboard mapping stays off in between.
inline void HexicSettingsDialog::Activate(int item) {
  if (item == kRowPlayerName) {
    app_->OpenNameEntry();
  } else if (item == kRowUpdates) {
    app_->OpenUpdateDialog();
  } else {
    return;
  }
  ImGui::CloseCurrentPopup();
  Close();
}

inline void HexicSettingsDialog::OnDraw(ImGuiIO& io) {
  using namespace hexic_settings_ui;
  if (!has_opened_shown_) {
    ImGui::OpenPopup("##HexicSettings");
    has_opened_shown_ = true;
  }

  // Keyboard and controller. While the Controls list waits for a key, that
  // key is all that is read (Esc / B cancel it rather than closing Settings).
  const bool window_focused = app_ && app_->HasWindowFocus();
  const bool capturing = controls_.Capturing();
  bool close = false;
  bool confirm = false;
  if (capturing) {
    controls_.Update(window_focused, input_);
  } else {
    input_.Poll(window_focused);
    const int first = FirstItem(category_);
    const int count = ItemCount(category_);
    if (input_.Pressed(HexicMenuInput::kPrevPage))
      SelectCategory(Category((category_ + kCategoryCount - 1) % kCategoryCount));
    if (input_.Pressed(HexicMenuInput::kNextPage))
      SelectCategory(Category((category_ + 1) % kCategoryCount));
    if (category_ == kControls) {
      controls_.Update(window_focused, input_);
    } else {
      if (input_.Pressed(HexicMenuInput::kUp)) item_ = first + (item_ - first + count - 1) % count;
      if (input_.Pressed(HexicMenuInput::kDown)) item_ = first + (item_ - first + 1) % count;
      const auto options = Options(item_);
      if (!options.empty()) {
        const int n = int(options.size());
        if (input_.Pressed(HexicMenuInput::kLeft)) Choose(item_, (Current(item_) + n - 1) % n);
        if (input_.Pressed(HexicMenuInput::kRight)) Choose(item_, (Current(item_) + 1) % n);
      }
      confirm = input_.Pressed(HexicMenuInput::kConfirm);
    }
    if (input_.Pressed(HexicMenuInput::kBack)) close = true;
  }

  ImGuiViewport* viewport = ImGui::GetMainViewport();
  const ImVec2 view_pos = viewport ? viewport->Pos : ImVec2(0, 0);
  const ImVec2 view_size = viewport ? viewport->Size : io.DisplaySize;
  // Dim the game behind the panel.
  ImGui::GetBackgroundDrawList()->AddRectFilled(
      view_pos, ImVec2(view_pos.x + view_size.x, view_pos.y + view_size.y), kDim);

  ImGui::SetNextWindowPos(ImVec2(view_pos.x + view_size.x * 0.5f, view_pos.y + view_size.y * 0.5f),
                          ImGuiCond_Always, ImVec2(0.5f, 0.5f));
  ImGui::SetNextWindowSize(ImVec2(kWidth, kHeight), ImGuiCond_Always);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));
  ImGui::PushStyleColor(ImGuiCol_ModalWindowDimBg, IM_COL32(0, 0, 0, 0));
  const bool open = ImGui::BeginPopupModal(
      "##HexicSettings", nullptr,
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
          ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings);
  if (open) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 o = ImGui::GetWindowPos();
    const ImVec2 end(o.x + kWidth, o.y + kHeight);
    ImGui::Dummy(ImVec2(kWidth, kHeight));

    // Mouse: hovering selects (only when the mouse moves, so it never fights
    // the keys), left click chooses, right click closes.
    const ImVec2 mouse = io.MousePos;
    const bool mouse_moved = mouse.x != last_mouse_.x || mouse.y != last_mouse_.y;
    last_mouse_ = mouse;
    // (A click while the Controls list waits for a key only cancels that.)
    const bool click = ImGui::IsMouseClicked(ImGuiMouseButton_Left) && !capturing;
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right) && !capturing) close = true;

    // Panel and sidebar.
    dl->AddRectFilled(o, end, kPanel, 14.0f);
    dl->AddRectFilled(o, ImVec2(o.x + kSidebarWidth, end.y), kSidebar, 14.0f,
                      ImDrawFlags_RoundCornersLeft);

    ImFont* font = Font();
    Text(dl, TitleFont(), 27.0f, ImVec2(o.x + 28.0f, o.y + 26.0f), kInk, "Settings");
    static const char* kCategoryNames[kCategoryCount] = {"Display", "Graphics", "Player",
                                                         "Controls", "Updates"};
    for (int c = 0; c < kCategoryCount; ++c) {
      const ImVec2 lo(o.x + 14.0f, o.y + 86.0f + c * 44.0f);
      const ImVec2 hi(o.x + kSidebarWidth - 14.0f, lo.y + 36.0f);
      const bool hovered = Inside(mouse, lo, hi);
      if (hovered && click) SelectCategory(Category(c));
      const bool on = c == category_;
      if (on || hovered) dl->AddRectFilled(lo, hi, on ? IM_COL32(0xFF, 0xFF, 0xFF, 18) : kHover, 6.0f);
      if (on) dl->AddRectFilled(ImVec2(lo.x, lo.y + 9.0f), ImVec2(lo.x + 3.0f, hi.y - 9.0f), kGreen);
      Text(dl, font, 19.0f, ImVec2(lo.x + 16.0f, lo.y + 8.0f), on ? kInk : kMuted,
           kCategoryNames[c]);
    }

    // The chosen category's settings (Controls: the key list).
    const float content_x = o.x + kSidebarWidth + 24.0f;
    const float right_x = end.x - 28.0f;
    if (category_ == kControls) {
      controls_.Draw(dl, font, ImVec2(content_x - 12.0f, o.y + 30.0f), ImVec2(right_x + 12.0f, end.y - 96.0f),
                     mouse, mouse_moved, click, io.MouseWheel);
    }
    for (int i = 0; category_ != kControls && i < ItemCount(category_); ++i) {
      const int item = FirstItem(category_) + i;
      const ImVec2 lo(content_x - 12.0f, o.y + 40.0f + i * kRowPitch);
      const ImVec2 hi(right_x + 12.0f, lo.y + kRowHeight);
      const bool row_hovered = Inside(mouse, lo, hi);
      if (row_hovered && mouse_moved) item_ = item;
      const bool focused = item == item_;
      if (focused) {
        dl->AddRectFilled(lo, hi, IM_COL32(0xFF, 0xFF, 0xFF, 10), 8.0f);
        dl->AddRectFilled(ImVec2(lo.x, lo.y + 13.0f), ImVec2(lo.x + 3.0f, hi.y - 13.0f), kGreen);
      }
      const float text_y = lo.y + (kRowHeight - 19.0f) * 0.5f;
      Text(dl, font, 19.0f, ImVec2(content_x + 8.0f, text_y), focused ? kInk : kSoft, Label(item));

      const auto choices = Options(item);
      if (choices.empty()) {
        // A page: its current value, and a chevron.
        std::string value = item == kRowPlayerName ? HexicHdApp::PlayerName()
                            : item == kRowUpdates  ? std::string("v") + HEXIC_VERSION
                                                   : std::string("Customize");
        value += "   >";
        Text(dl, font, 19.0f, ImVec2(right_x - Width(font, 19.0f, value.c_str()), text_y),
             focused ? kInk : kMuted, value.c_str());
        if (row_hovered && click) Activate(item);
        continue;
      }
      // Every choice as a segment, right-aligned; the current one filled.
      const int n = int(choices.size());
      // Wide enough for the longest choice ("3840 x 2160").
      float seg_w = n >= 4 ? 72.0f : 86.0f;
      for (const char* choice : choices) seg_w = std::max(seg_w, Width(font, 17.0f, choice) + 22.0f);
      const float seg_h = 32.0f;
      const int current = Current(item);
      for (int k = 0; k < n; ++k) {
        const ImVec2 slo(right_x - (n - k) * seg_w + 6.0f, lo.y + (kRowHeight - seg_h) * 0.5f);
        const ImVec2 shi(slo.x + seg_w - 6.0f, slo.y + seg_h);
        const bool seg_hovered = Inside(mouse, slo, shi);
        if (seg_hovered && click) {
          item_ = item;
          Choose(item, k);
        }
        const float tw = Width(font, 17.0f, choices[k]);
        const ImVec2 tpos(slo.x + (seg_w - 6.0f - tw) * 0.5f, slo.y + (seg_h - 17.0f) * 0.5f);
        if (k == Current(item)) {
          dl->AddRectFilled(slo, shi, kGreen, 6.0f);
          Text(dl, font, 17.0f, tpos, kOnGreen, choices[k]);
        } else {
          if (seg_hovered) dl->AddRectFilled(slo, shi, kHover, 6.0f);
          dl->AddRect(slo, shi, focused ? kOutlineFocus : kOutline, 6.0f, 0, 1.0f);
          Text(dl, font, 17.0f, tpos, focused ? kSoft : kMuted, choices[k]);
        }
      }
      (void)current;
    }

    // What the selected setting does, and the controls.
    const std::string help = category_ == kControls ? controls_.Help() : Help(item_);
    Text(dl, font, 16.0f, ImVec2(content_x + 8.0f, end.y - 82.0f), kMuted, help.c_str());
    // Hints for the device in use (hexic_input_mode.h).
    const bool pad = hexic_input_mode::UsingController();
    const char* hints =
        category_ == kControls
            ? (pad ? "LB / RB  Category    A  Change    Y  Add    X  Reset    B  Back"
                   : "Q / E  Category    Enter  Change    Tab  Add    Backspace  Reset    Esc  Back")
            : (pad ? "LB / RB  Category      D-pad  Change      A  Open      B  Back"
                   : "Q / E  Category      Arrows  Change      Enter  Open      Esc  Back");
    Text(dl, font, 15.0f, ImVec2(content_x + 8.0f, end.y - 46.0f), kFaint, hints);

    if (confirm) Activate(item_);
    if (close) {
      ImGui::CloseCurrentPopup();
      Close();
    }
    ImGui::EndPopup();
  }
  ImGui::PopStyleColor(2);
  ImGui::PopStyleVar(3);
  if (!open) Close();
}

// --- Player Name ---------------------------------------------------------

inline HexicNameEntryDialog::HexicNameEntryDialog(rex::ui::ImGuiDrawer* imgui_drawer,
                                                  HexicHdApp* app)
    : rex::ui::ImGuiDialog(imgui_drawer), app_(app), text_(HexicHdApp::SavedPlayerName()) {
  if (text_.size() > kMaxName) text_.resize(kMaxName);
  app_->BeginModal();
}

inline void HexicNameEntryDialog::OnDraw(ImGuiIO& io) {
  using namespace hexic_ui;
  const auto now = std::chrono::steady_clock::now();
  if (!has_opened_shown_) {
    ImGui::OpenPopup("##HexicPlayerName");
    has_opened_shown_ = true;
    opened_at_ = now;
  }

  const bool focused = app_->HasWindowFocus();
  input_.Poll(focused);
  // The Enter or A that opened this box can arrive as a typed character a
  // frame later; ignore characters briefly so it doesn't land in the name.
  if (focused && now - opened_at_ >= std::chrono::milliseconds(250)) {
    for (int i = 0; i < io.InputQueueCharacters.Size; ++i) {
      const ImWchar c = io.InputQueueCharacters[i];
      if (c >= 0x20 && c < 0x7F && text_.size() < kMaxName) {
        text_.push_back(static_cast<char>(c));
      }
    }
  }
  if (input_.Pressed(HexicMenuInput::kReset) && !text_.empty()) text_.pop_back();

  constexpr float kWindowWidth = 500.0f;
  PushDialogStyle(io, kWindowWidth);
  const bool still_open =
      ImGui::BeginPopupModal("##HexicPlayerName", nullptr,
                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
  if (still_open) {
    const bool save = input_.Pressed(HexicMenuInput::kConfirm);
    const bool cancel = input_.Pressed(HexicMenuInput::kBack);

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 window_pos = ImGui::GetWindowPos();
    constexpr float kSideMargin = 26.0f;
    const ImVec2 window_size(kWindowWidth, 236.0f);
    const ImVec2 window_end(window_pos.x + window_size.x, window_pos.y + window_size.y);
    ImGui::Dummy(window_size);

    const float accent_y =
        DrawHexicCard(draw_list, window_pos, window_end, kSideMargin, "PLAYER NAME");

    // The name field: a dark well with a lit rim and a blinking caret.
    const ImVec2 box_min(window_pos.x + kSideMargin, accent_y + 20.0f);
    const ImVec2 box_max(window_end.x - kSideMargin, box_min.y + 50.0f);
    draw_list->AddRectFilled(box_min, box_max, IM_COL32(0x0B, 0x08, 0x1C, 255), 10.0f);
    draw_list->AddRect(box_min, box_max, kPillGreenRim, 10.0f, 0, 2.0f);
    const ImVec2 text_pos(box_min.x + 16.0f, box_min.y + (50.0f - BodySize()) * 0.5f);
    float caret_x = text_pos.x;
    if (text_.empty()) {
      draw_list->AddText(BodyFont(), BodySize(), text_pos, IM_COL32(0x9A, 0x94, 0xB8, 200),
                         "Leave empty for a random name");
    } else {
      DrawPillText(draw_list, BodyFont(), BodySize(), text_pos, kTextSelected, text_.c_str());
      caret_x += BodyFont()->CalcTextSizeA(BodySize(), FLT_MAX, 0, text_.c_str()).x + 2.0f;
    }
    const auto blink = std::chrono::duration_cast<std::chrono::milliseconds>(now - opened_at_);
    if ((blink.count() / 500) % 2 == 0) {
      draw_list->AddLine(ImVec2(caret_x, text_pos.y), ImVec2(caret_x, text_pos.y + BodySize()),
                         kAccentCyan, 2.0f);
    }

    DrawHint(draw_list, window_pos.x, window_end.x, box_max.y + 16.0f,
             "Shown on High Scores. Up to 15 characters.");
    DrawHint(draw_list, window_pos.x, window_end.x, box_max.y + 42.0f,
             "Enter  Save        Esc  Cancel        Backspace  Delete");

    if (save || cancel) {
      if (save) {
        std::string name = text_;
        while (!name.empty() && name.front() == ' ') name.erase(0, 1);
        while (!name.empty() && name.back() == ' ') name.pop_back();
        app_->SetPlayerName(name);
      }
      app_->OpenSettings(HexicSettingsDialog::kRowPlayerName);
      ImGui::CloseCurrentPopup();
      Close();
    }
    ImGui::EndPopup();
  }
  PopDialogStyle();
  if (!still_open) Close();
}

inline void HexicNameEntryDialog::OnClose() { app_->EndModal(); }

// --- Check for Updates --------------------------------------------------------

inline HexicUpdateDialog::HexicUpdateDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app)
    : rex::ui::ImGuiDialog(imgui_drawer), app_(app) {
  app_->BeginModal();
}

inline void HexicUpdateDialog::OnClose() {
  app_->OnUpdateDialogClosed();
  app_->EndModal();
}

inline void HexicUpdateDialog::OnDraw(ImGuiIO& io) {
  using namespace hexic_ui;
  using State = HexicHdApp::UpdateState;
  const auto now = std::chrono::steady_clock::now();
  if (!has_opened_shown_) {
    ImGui::OpenPopup("##HexicUpdate");
    has_opened_shown_ = true;
    opened_at_ = now;
  }

  // The answer so far, and the buttons that go with it.
  const HexicHdApp::UpdateStatus status = HexicHdApp::CurrentUpdateStatus();
  const bool safe = HexicHdApp::UpdateIsSafe();
  const std::string current = HEXIC_VERSION;
  std::string line1, line2;
  std::vector<const char*> buttons;
  bool offer = false;
  switch (status.state) {
    case State::kIdle:
    case State::kChecking: {
      const int dots = int(std::chrono::duration_cast<std::chrono::milliseconds>(now - opened_at_).count() / 400 % 4);
      line1 = "Asking GitHub for the latest release" + std::string(size_t(dots), '.');
      buttons = {"Cancel"};
      break;
    }
    case State::kUpToDate:
      line1 = "Hexic HD is up to date (v" + current + ").";
      buttons = {"OK"};
      break;
    case State::kFailed:
      line1 = "Could not check for updates: " + status.error + ".";
      line2 = "Check your internet connection and try again later.";
      buttons = {"OK"};
      break;
    case State::kNoLauncher:
      line1 = "Updates work in the release folder, where Hexic HD.exe sits beside the resources folder.";
      buttons = {"OK"};
      break;
    case State::kAvailable:
      line1 = "Version " + status.latest + " is available. You have " + current + ".";
      if (updating_) {
        line2 = "Closing the game for the update...";
      } else if (!safe) {
        line2 = "Updating closes the game. Quit to the main menu first, then try again.";
        buttons = {"OK"};
      } else {
        char size[32] = "";
        if (status.size) std::snprintf(size, sizeof(size), " (%.0f MB)", status.size / 1048576.0);
        line2 = std::string("The game closes, the update downloads") + size +
                " and installs, then the game starts again. Your saves and settings are kept.";
        buttons = {"Update", "Cancel"};
        offer = true;
      }
      break;
  }
  const int count = int(buttons.size());
  if (selected_ >= count) selected_ = 0;

  // Keyboard and controller (and the test hooks).
  input_.Poll(app_ && app_->HasWindowFocus());
  int moves = HexicHdApp::test_dialog_moves_.exchange(0);
  if (input_.Pressed(HexicMenuInput::kRight) || input_.Pressed(HexicMenuInput::kDown)) ++moves;
  if (input_.Pressed(HexicMenuInput::kLeft) || input_.Pressed(HexicMenuInput::kUp)) --moves;
  if (count > 0) selected_ = ((selected_ + moves) % count + count) % count;
  int press = -1;
  if (input_.Pressed(HexicMenuInput::kConfirm) || HexicHdApp::test_dialog_press_.exchange(false)) press = selected_;
  bool back = input_.Pressed(HexicMenuInput::kBack) || HexicHdApp::test_dialog_back_.exchange(false);

  constexpr float kWindowWidth = 600.0f, kSideMargin = 28.0f;
  constexpr float kButtonWidth = 190.0f, kButtonHeight = 50.0f, kButtonGap = 18.0f;
  const float wrap = kWindowWidth - kSideMargin * 2.0f;
  ImFont* font = BodyFont();
  const float size = BodySize();
  const float h1 = font->CalcTextSizeA(size, FLT_MAX, wrap, line1.c_str()).y;
  const float h2 = line2.empty() ? 0.0f : font->CalcTextSizeA(size, FLT_MAX, wrap, line2.c_str()).y;
  const float heading_block = 20.0f + 27.0f + 8.0f;  // DrawHexicCard: heading, then the accent line
  const float text_top = heading_block + 22.0f;
  const float buttons_top = text_top + h1 + (h2 > 0 ? 10.0f + h2 : 0.0f) + 26.0f;
  const float hint_top = buttons_top + (count ? kButtonHeight + 22.0f : 0.0f);
  const float window_height = hint_top + size + 24.0f;

  PushDialogStyle(io, kWindowWidth);
  const bool still_open = ImGui::BeginPopupModal("##HexicUpdate", nullptr,
                                                 ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
  if (still_open) {
    ImDrawList* dl = ImGui::GetWindowDrawList();
    const ImVec2 o = ImGui::GetWindowPos();
    const ImVec2 end(o.x + kWindowWidth, o.y + window_height);
    ImGui::Dummy(ImVec2(kWindowWidth, window_height));
    DrawHexicCard(dl, o, end, kSideMargin, "CHECK FOR UPDATES");
    dl->AddText(font, size, ImVec2(o.x + kSideMargin, o.y + text_top), kTextNormal, line1.c_str(), nullptr, wrap);
    if (h2 > 0) {
      dl->AddText(font, size, ImVec2(o.x + kSideMargin, o.y + text_top + h1 + 10.0f), kTextDim, line2.c_str(),
                  nullptr, wrap);
    }

    // The buttons, centred: hover chooses, click presses, right click closes.
    const ImVec2 mouse = io.MousePos;
    const bool mouse_moved = mouse.x != last_mouse_.x || mouse.y != last_mouse_.y;
    last_mouse_ = mouse;
    const float row_width = count * kButtonWidth + (count - 1) * kButtonGap;
    float x = o.x + (kWindowWidth - row_width) * 0.5f;
    for (int i = 0; i < count; ++i, x += kButtonWidth + kButtonGap) {
      const ImVec2 lo(x, o.y + buttons_top), hi(x + kButtonWidth, o.y + buttons_top + kButtonHeight);
      const bool hovered = mouse.x >= lo.x && mouse.x < hi.x && mouse.y >= lo.y && mouse.y < hi.y;
      if (hovered && mouse_moved) selected_ = i;
      if (hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) press = i;
      DrawGamePill(dl, lo, hi, i == selected_);
      const ImVec2 text = font->CalcTextSizeA(size, FLT_MAX, 0, buttons[i]);
      DrawPillText(dl, font, size, ImVec2(lo.x + (kButtonWidth - text.x) * 0.5f, lo.y + (kButtonHeight - text.y) * 0.5f),
                   kTextSelected, buttons[i]);
    }
    if (ImGui::IsMouseClicked(ImGuiMouseButton_Right)) back = true;

    // Hints for the device in use (no pad glyphs on keyboard and mouse).
    if (count) {
      DrawHint(dl, o.x, end.x, o.y + hint_top,
               hexic_input_mode::UsingController() ? "A  Select        B  Back"
                                                   : "Enter / Click  Select        Esc / Right click  Back");
    }

    // A press, or Back (which is Cancel / OK). Nothing while the game closes.
    if (!updating_ && (press >= 0 || back)) {
      const bool update = offer && press == 0 && !back;
      if (update && HexicHdApp::UpdateIsSafe() && app_->StartUpdater()) {
        updating_ = true;
      } else {
        app_->OpenSettings(HexicSettingsDialog::kRowUpdates);
        ImGui::CloseCurrentPopup();
        Close();
      }
    }
    ImGui::EndPopup();
  }
  PopDialogStyle();
  if (!still_open) Close();
}

// --- Settings > Controls --------------------------------------------------

inline void HexicControlsPanel::Notice(int row, const std::string& text, int seconds) {
  notice_row_ = row;
  notice_ = text;
  notice_until_ = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
}

inline void HexicControlsPanel::Activate(int row, bool append) {
  capture_row_ = row;
  capture_append_ = append;
  capture_deadline_ = std::chrono::steady_clock::now() + std::chrono::seconds(10);
  notice_row_ = -1;
  capture_ = kCaptureWaitRelease;
  REXLOG_INFO("[controls] {}: waiting for a key ({})", hexic_controls::Bindings()[row].button,
              append ? "add" : "change");
}

inline void HexicControlsPanel::ResetRow(int row) {
  const auto& binding = hexic_controls::Bindings()[row];
  hexic_controls::SetKeys(row, hexic_controls::SplitKeys(binding.defaults));
  HexicHdApp::SavePcSettings();
  Notice(row, "Reset to default", 2);
}

inline void HexicControlsPanel::ResetAllKeys() {
  hexic_controls::ResetAll();
  HexicHdApp::SavePcSettings();
  Notice(ResetAllRow(), "All keys reset to defaults", 2);
}

inline void HexicControlsPanel::FinishCapture(const std::string& notice) {
  if (!notice.empty()) Notice(capture_row_, notice, 3);
  capture_deadline_ = std::chrono::steady_clock::now() + std::chrono::seconds(3);
  capture_ = kCaptureFinish;
}

// Waits for everything to be released (the key or click that started the
// capture is still down), takes the next key, then waits for that to be
// released too before handing input back to the menu. Mouse buttons are not
// bound (the mouse plays the game itself); a click cancels, as Esc and B do.
inline void HexicControlsPanel::TickCapture(bool focused, HexicMenuInput& input) {
  const auto now = std::chrono::steady_clock::now();
  const bool expired = now > capture_deadline_;
  XINPUT_STATE pad{};
  const bool pad_connected = XInputGetState(0, &pad) == ERROR_SUCCESS;
  auto any_input_down = [&]() {
    for (int vk = 1; vk < 255; ++vk) {
      if (GetAsyncKeyState(vk) & 0x8000) return true;
    }
    return pad_connected && (pad.Gamepad.wButtons != 0 || pad.Gamepad.bLeftTrigger > 30 ||
                             pad.Gamepad.bRightTrigger > 30);
  };

  if (capture_ == kCaptureWaitRelease) {
    if (!any_input_down()) {
      capture_ = kCaptureListen;
    } else if (expired) {
      FinishCapture("");
    }
    return;
  }

  if (capture_ == kCaptureListen) {
    if (expired) {
      FinishCapture("No key pressed");
      return;
    }
    if (!focused) return;
    const bool click = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000) ||
                       (GetAsyncKeyState(VK_MBUTTON) & 0x8000);
    if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) || click ||
        (pad_connected && (pad.Gamepad.wButtons & XINPUT_GAMEPAD_B))) {
      FinishCapture("");
      return;
    }
    std::string key;
    for (int vk = 1; key.empty() && vk < 255; ++vk) {
      // Esc cancels and F4 opens the runtime overlay, so neither can be
      // bound; the generic Shift/Ctrl/Alt codes are used, not left/right;
      // mouse buttons are the pointer's.
      const bool excluded = vk == VK_LBUTTON || vk == VK_RBUTTON || vk == VK_MBUTTON || vk == VK_ESCAPE ||
                            vk == VK_F4 || vk == VK_LWIN || vk == VK_RWIN || vk == VK_APPS ||
                            (vk >= VK_LSHIFT && vk <= VK_RMENU);
      if (excluded || !(GetAsyncKeyState(vk) & 0x8000)) continue;
      key = vk == VK_RETURN ? "Return" : rex::ui::VirtualKeyToString(static_cast<rex::ui::VirtualKey>(vk));
    }
    if (key.empty()) return;

    const auto& bindings = hexic_controls::Bindings();
    std::vector<std::string> keys;
    if (capture_append_) {
      // Adding a key that is another input's only key would leave that input
      // unbound, so refuse and say which one has it. Changing a key swaps.
      for (size_t j = 0; j < bindings.size(); ++j) {
        if (int(j) == capture_row_) continue;
        const auto others = hexic_controls::KeysOf(j);
        if (others.size() == 1 && others[0] == key) {
          FinishCapture(std::string("Only key for ") + bindings[j].button);
          return;
        }
      }
      keys = hexic_controls::KeysOf(capture_row_);
      if (std::find(keys.begin(), keys.end(), key) == keys.end()) {
        if (keys.size() >= hexic_controls::kMaxKeysPerBinding) keys.resize(1);
        keys.push_back(key);
      }
    } else {
      keys = {key};
    }
    hexic_controls::SetKeys(capture_row_, keys);
    HexicHdApp::SavePcSettings();
    FinishCapture("");
    return;
  }

  // kCaptureFinish
  if (!any_input_down() || expired) {
    capture_ = kCaptureIdle;
    capture_row_ = -1;
    input.Reprime();
  }
}

inline void HexicControlsPanel::Update(bool focused, HexicMenuInput& input) {
  if (Capturing()) {
    TickCapture(focused, input);
    return;
  }
  const int rows = RowCount();
  if (input.Pressed(HexicMenuInput::kUp)) selected_ = (selected_ + rows - 1) % rows;
  if (input.Pressed(HexicMenuInput::kDown)) selected_ = (selected_ + 1) % rows;
  if (input.Pressed(HexicMenuInput::kConfirm)) {
    if (selected_ == ResetAllRow()) ResetAllKeys();
    else Activate(selected_, false);
  }
  if (selected_ < ResetAllRow()) {
    if (input.Pressed(HexicMenuInput::kAlt)) Activate(selected_, true);
    if (input.Pressed(HexicMenuInput::kReset)) ResetRow(selected_);
  }
}

inline std::string HexicControlsPanel::Help() const {
  if (selected_ >= ResetAllRow()) return "Every input back to Hexic's own keys";
  const auto& binding = hexic_controls::Bindings()[selected_];
  return std::string(binding.button) + ": " + (binding.action[0] ? binding.action : "not used by Hexic") +
         ". Click a row to change its key";
}

inline void HexicControlsPanel::Draw(ImDrawList* dl, ImFont* font, ImVec2 lo, ImVec2 hi, ImVec2 mouse,
                                     bool mouse_moved, bool click, float wheel) {
  using namespace hexic_settings_ui;
  const auto now = std::chrono::steady_clock::now();
  constexpr float kListRowHeight = 34.0f, kListRowPitch = 38.0f, kTextSize = 17.0f;
  const int rows = RowCount();
  visible_rows_ = std::max(1, int((hi.y - lo.y + (kListRowPitch - kListRowHeight)) / kListRowPitch));
  const bool capturing = Capturing();

  // The wheel scrolls; otherwise the chosen row is kept in view.
  if (!capturing && wheel != 0.0f && Inside(mouse, lo, hi)) {
    scroll_top_ -= wheel > 0 ? 1 : -1;
  } else {
    if (selected_ < scroll_top_) scroll_top_ = selected_;
    if (selected_ >= scroll_top_ + visible_rows_) scroll_top_ = selected_ - visible_rows_ + 1;
  }
  scroll_top_ = std::clamp(scroll_top_, 0, std::max(0, rows - visible_rows_));

  const float right = hi.x - 14.0f;  // room for the scroll bar
  for (int i = 0; i < visible_rows_ && scroll_top_ + i < rows; ++i) {
    const int row = scroll_top_ + i;
    const ImVec2 rlo(lo.x, lo.y + i * kListRowPitch);
    const ImVec2 rhi(right, rlo.y + kListRowHeight);
    const bool hovered = Inside(mouse, rlo, rhi);
    if (hovered && mouse_moved && !capturing) selected_ = row;
    const bool focused = row == selected_;
    if (focused) {
      dl->AddRectFilled(rlo, rhi, IM_COL32(0xFF, 0xFF, 0xFF, 10), 7.0f);
      dl->AddRectFilled(ImVec2(rlo.x, rlo.y + 9.0f), ImVec2(rlo.x + 3.0f, rhi.y - 9.0f), kGreen);
    }
    const float text_y = rlo.y + (kListRowHeight - kTextSize) * 0.5f;
    const bool noticed = row == notice_row_ && now < notice_until_;
    const ImU32 yellow = IM_COL32(0xFF, 0xE8, 0x7A, 255);

    // Small outlined buttons, right to left, for the chosen row (and the
    // reset-all row): click them; they also say which key does the same.
    float x = rhi.x - 8.0f;
    auto small_button = [&](const char* label) {
      const float w = Width(font, 15.0f, label) + 20.0f;
      const ImVec2 blo(x - w, rlo.y + 5.0f), bhi(x, rhi.y - 5.0f);
      const bool over = Inside(mouse, blo, bhi);
      if (over) dl->AddRectFilled(blo, bhi, kHover, 5.0f);
      dl->AddRect(blo, bhi, over ? kOutlineFocus : kOutline, 5.0f, 0, 1.0f);
      Text(dl, font, 15.0f, ImVec2(blo.x + 10.0f, blo.y + (bhi.y - blo.y - 15.0f) * 0.5f), over ? kInk : kSoft,
           label);
      x -= w + 6.0f;
      return over && click && !capturing;
    };

    if (row == ResetAllRow()) {
      Text(dl, font, kTextSize, ImVec2(rlo.x + 12.0f, text_y), focused ? kInk : kSoft,
           noticed ? notice_.c_str() : "Reset all keys to defaults");
      // Only its button resets (a stray click on the row should not).
      if (small_button("Reset all")) {
        selected_ = row;
        ResetAllKeys();
      }
      continue;
    }

    const auto& binding = hexic_controls::Bindings()[row];
    Text(dl, font, kTextSize, ImVec2(rlo.x + 12.0f, text_y), focused ? kInk : kSoft, binding.button);
    bool handled = false;
    if (focused && !capturing) {
      if (small_button("Reset")) {
        ResetRow(row);
        handled = true;
      }
      if (small_button("+ Add")) {
        Activate(row, true);
        handled = true;
      }
    }
    // The keys, as chips (or the capture prompt / a notice).
    if (capture_row_ == row && (capture_ == kCaptureWaitRelease || capture_ == kCaptureListen)) {
      const char* prompt = capture_append_ ? "Press a key to add  (Esc cancels)" : "Press a key  (Esc cancels)";
      Text(dl, font, 15.0f, ImVec2(x - Width(font, 15.0f, prompt), rlo.y + (kListRowHeight - 15.0f) * 0.5f), yellow,
           prompt);
    } else if (noticed) {
      Text(dl, font, 15.0f, ImVec2(x - Width(font, 15.0f, notice_.c_str()), rlo.y + (kListRowHeight - 15.0f) * 0.5f),
           yellow, notice_.c_str());
    } else {
      const auto keys = hexic_controls::KeysOf(row);
      if (keys.empty()) {
        Text(dl, font, 15.0f, ImVec2(x - Width(font, 15.0f, "Not bound"), rlo.y + (kListRowHeight - 15.0f) * 0.5f),
             kFaint, "Not bound");
      }
      for (auto it = keys.rbegin(); it != keys.rend(); ++it) {
        const std::string name = hexic_controls::KeyDisplayName(*it);
        const float w = std::max(30.0f, Width(font, 15.0f, name.c_str()) + 16.0f);
        const ImVec2 clo(x - w, rlo.y + 5.0f), chi(x, rhi.y - 5.0f);
        dl->AddRectFilled(clo, chi, IM_COL32(0xFF, 0xFF, 0xFF, focused ? 30 : 18), 5.0f);  // a keycap
        dl->AddRect(clo, chi, focused ? kOutlineFocus : kOutline, 5.0f, 0, 1.0f);
        Text(dl, font, 15.0f, ImVec2(clo.x + (w - Width(font, 15.0f, name.c_str())) * 0.5f, clo.y + (chi.y - clo.y - 15.0f) * 0.5f),
             focused ? kInk : kSoft, name.c_str());
        x -= w + 6.0f;
      }
    }
    // A click anywhere else on the row changes its key.
    if (hovered && click && !capturing && !handled) {
      selected_ = row;
      Activate(row, false);
    }
  }

  // Scroll position, as a thin bar beside the list.
  if (rows > visible_rows_) {
    const float list_h = visible_rows_ * kListRowPitch - (kListRowPitch - kListRowHeight);
    const float thumb_h = list_h * float(visible_rows_) / float(rows);
    const float thumb_y = lo.y + (list_h - thumb_h) * float(scroll_top_) / float(rows - visible_rows_);
    dl->AddRectFilled(ImVec2(hi.x - 4.0f, lo.y), ImVec2(hi.x, lo.y + list_h), IM_COL32(0xFF, 0xFF, 0xFF, 18), 2.0f);
    dl->AddRectFilled(ImVec2(hi.x - 4.0f, thumb_y), ImVec2(hi.x, thumb_y + thumb_h), kGreen, 2.0f);
  }
}

inline void HexicSignInHook::OnDraw(ImGuiIO& /*io*/) {
  if (app_ && app_->TrySetSignedInToLive()) {
    Close();
  }
}
