// hexic_hd - ReXGlue Recompiled Project
//
// Customize your app by overriding virtual hooks from rex::ReXApp.

#pragma once

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
#include <algorithm>
#include <memory>
#include <string_view>
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
#include <rex/ui/window.h>
#include <rex/ui/window_sdl.h>

// Which set of Hexic keyboard defaults this config has received (main.cpp).
REXCVAR_DECLARE(int32_t, hexic_controls_version);

class HexicHdApp;

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
      {"A", "Rotate clockwise, select", "keybind_a", "Space,Return"},
      {"B", "Back", "keybind_b", "Backspace"},
      {"X", "Rotate counter-clockwise", "keybind_x", "Q"},
      {"Y", "", "keybind_y", "E"},
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

// Bumped whenever the defaults above change, so existing configs pick them up.
constexpr int32_t kDefaultsVersion = 1;
constexpr size_t kMaxKeysPerBinding = 2;

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

}  // namespace hexic_controls

// A native, controller-first PC settings panel, shown in place of Hexic
// HD's own (Xbox-only) Achievements viewer: the main menu's "Achievements"
// button now opens this instead of the unavailable Xbox system UI. Reuses
// the same CVars as the F4 debug overlay, so both stay in sync.
//
// Navigation is a fixed-order row list (matching the game's own Options
// screen), driven directly by XInput and the keyboard rather than ImGui's
// mouse-oriented widgets: Up/Down moves the selection, Left/Right/A cycles
// a row's value, B (or Escape) always closes.
class HexicSettingsDialog : public rex::ui::ImGuiDialog {
 public:
  // `select_row` lets a sub-dialog return with its own row still highlighted.
  HexicSettingsDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app, int select_row = 0);

  void OnDraw(ImGuiIO& io) override;

  enum Row : int {
    kRowPlayerName = 0,
    kRowFullscreen,
    kRowResolution,
    kRowVSync,
    kRowShowFps,
    kRowControls,
    kRowDone,
    kRowCount,
  };

 protected:
  void OnClose() override;

 private:

  struct InputEdges {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool confirm = false;
    bool back = false;
  };

  InputEdges PollInput();
  void MoveSelection(int delta);
  void CycleRow(int row, int delta);
  void ActivateRow(int row);
  void DrawRow(ImDrawList* draw_list, ImVec2 pos, ImVec2 size, int row, bool selected,
              const char* label, const char* value, bool has_value, bool show_chevrons = true);

  HexicHdApp* app_;
  bool has_opened_shown_ = false;
  int selected_row_ = kRowPlayerName;

  // Edge-detection state for keyboard and controller polling.
  bool key_was_down_[6] = {};
  WORD pad_buttons_prev_ = 0;
  bool pad_was_connected_ = false;
  // The first PollInput() call only seeds key_was_down_/pad_buttons_prev_
  // and reports no edges: the button that opened this dialog (e.g. A on the
  // main menu) is often still physically held on that first polled frame,
  // and without priming it would read as a fresh edge here too.
  bool input_primed_ = false;
};

// Menu input for the Hexic dialogs: arrow keys / D-pad / left stick to move,
// Enter / A to confirm, Esc / B to go back, Tab / Y for a second action and
// Backspace / X to reset or erase. Keys and the pad are read directly (the
// game's own keyboard mapping is off while a dialog is open). Presses are
// edges; Up and Down, and optionally Reset, repeat while held. The first poll,
// and the first poll after Reprime(), only records what is already held, so
// the press that opened a dialog can't also act inside it.
class HexicMenuInput {
 public:
  enum Action : int { kUp, kDown, kLeft, kRight, kConfirm, kBack, kAlt, kReset, kCount };

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
      XINPUT_STATE state{};
      if (XInputGetState(0, &state) == ERROR_SUCCESS) {
        const WORD b = state.Gamepad.wButtons;
        constexpr SHORT kStick = 16000;
        held[kUp] |= (b & XINPUT_GAMEPAD_DPAD_UP) || state.Gamepad.sThumbLY > kStick;
        held[kDown] |= (b & XINPUT_GAMEPAD_DPAD_DOWN) || state.Gamepad.sThumbLY < -kStick;
        held[kLeft] |= (b & XINPUT_GAMEPAD_DPAD_LEFT) || state.Gamepad.sThumbLX < -kStick;
        held[kRight] |= (b & XINPUT_GAMEPAD_DPAD_RIGHT) || state.Gamepad.sThumbLX > kStick;
        held[kConfirm] |= (b & XINPUT_GAMEPAD_A) != 0;
        held[kBack] |= (b & XINPUT_GAMEPAD_B) != 0;
        held[kAlt] |= (b & XINPUT_GAMEPAD_Y) != 0;
        held[kReset] |= (b & XINPUT_GAMEPAD_X) != 0;
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

// PC Settings > Player Name: the name Hexic shows as your gamertag (High
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

// PC Settings > Keyboard Controls: every controller input with the keys bound
// to it. Enter changes a key, Tab adds a second one, Backspace resets that
// input, plus Reset All and Done rows at the end.
class HexicControlsDialog : public rex::ui::ImGuiDialog {
 public:
  HexicControlsDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app);

  void OnDraw(ImGuiIO& io) override;

 protected:
  void OnClose() override;

 private:
  enum Capture : int { kCaptureIdle, kCaptureWaitRelease, kCaptureListen, kCaptureFinish };

  int RowCount() const { return int(hexic_controls::Bindings().size()) + 2; }
  int ResetAllRow() const { return int(hexic_controls::Bindings().size()); }
  int DoneRow() const { return ResetAllRow() + 1; }

  void Activate(int row, bool append);
  void ResetRow(int row);
  void TickCapture();
  void FinishCapture(const std::string& notice);

  HexicHdApp* app_;
  HexicMenuInput input_;
  bool has_opened_shown_ = false;
  int selected_ = 0;
  int scroll_top_ = 0;

  Capture capture_ = kCaptureIdle;
  int capture_row_ = -1;
  bool capture_append_ = false;
  std::chrono::steady_clock::time_point capture_deadline_{};
  int notice_row_ = -1;
  std::string notice_;
  std::chrono::steady_clock::time_point notice_until_{};
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

  // Keep the game fully portable: assets, saves and cache all live beside
  // the executable rather than under the user's profile, so the installed
  // folder can be moved or backed up as a single unit. Installation itself
  // (STFS extraction into assets\) is handled by the external graphical
  // installer, not by this app.
  void OnConfigurePaths(rex::PathConfig& paths) override {
    wchar_t exe_path[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, exe_path, MAX_PATH);
    const auto app_directory = std::filesystem::path(exe_path).parent_path();

    const auto assets_path = app_directory / "assets";
    if (!std::filesystem::is_directory(assets_path)) {
      // Preempt the SDK's generic "--game_data_root does not exist" message
      // (written for a CLI flag the player never typed) with one that tells
      // them what to actually do.
      MessageBoxW(nullptr,
                  L"No Hexic HD game files found.\n\n"
                  L"Open \"Install Hexic HD.exe\" (beside the Game folder) "
                  L"and select your Xbox 360 Hexic HD package, then play again.",
                  L"Hexic HD", MB_OK | MB_ICONERROR);
      ExitProcess(1);
    }

    paths.game_data_root = assets_path;

    const auto user_data_path = app_directory / "userdata";
    paths.user_data_root = user_data_path;
    paths.cache_root = user_data_path / "cache";
  }

  std::string GetWindowTitle() const override { return "Hexic HD PC"; }

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
    wchar_t exe_path[MAX_PATH] = {};
    GetModuleFileNameW(nullptr, exe_path, MAX_PATH);
    const auto app_directory = std::filesystem::path(exe_path).parent_path();
    const auto font_path = app_directory / "assets" / "convectionui.ttf";
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
        OpenSettings(HexicSettingsDialog::kRowPlayerName);
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
    rex::cvar::SetFlagByName("mnk_mode", "true");
    rex::cvar::SetFlagByName("mnk_mouse", "false");
    rex::cvar::SetFlagByName("mnk_dpad_to_stick", "false");
    if (REXCVAR_GET(hexic_controls_version) < hexic_controls::kDefaultsVersion) {
      hexic_controls::ApplyDefaults();
      REXCVAR_SET(hexic_controls_version, hexic_controls::kDefaultsVersion);
      SavePcSettings();
      REXLOG_INFO("[controls] applied Hexic keyboard defaults (version {})",
                  hexic_controls::kDefaultsVersion);
    }
  }

  // --- the PC dialogs --------------------------------------------------------
  // While any of them is open the game must not act on the keys used in it, so
  // the keyboard mapping is off from the first dialog opening until the last
  // one closes. A dialog handing over to another opens the next one before
  // closing itself, so the count never drops to zero in between.
  void BeginModal() {
    if (modal_depth_++ == 0) rex::cvar::SetFlagByName("mnk_mode", "false");
  }

  void EndModal() {
    if (modal_depth_ > 0 && --modal_depth_ == 0) {
      rex::cvar::SetFlagByName("mnk_mode", "true");
      last_dialog_closed_time_ = std::chrono::steady_clock::now();
    }
  }

  void OpenSettings(int select_row) {
    if (imgui_drawer_) {
      imgui_drawer_->AddDialog(new HexicSettingsDialog(imgui_drawer_, this, select_row));
    }
  }

  void OpenNameEntry() {
    if (imgui_drawer_) imgui_drawer_->AddDialog(new HexicNameEntryDialog(imgui_drawer_, this));
  }

  void OpenControls() {
    if (imgui_drawer_) imgui_drawer_->AddDialog(new HexicControlsDialog(imgui_drawer_, this));
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

  void SetPlayerName(const std::string& name) {
    rex::cvar::SetFlagByName("net_player_name", name);
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

  static void SavePcSettings() {
    HexicHdApp* app = current_instance_;
    if (!app || app->config_path().empty()) {
      return;
    }
    // Use the exact same config file as the F4 settings overlay.
    rex::cvar::SaveConfig(app->config_path());
  }

  static void SetPcResolution(int32_t width, int32_t height, int32_t scale) {
    HexicHdApp* app = current_instance_;
    if (!app) {
      return;
    }

    bool changed = false;
    changed |= rex::cvar::SetFlagByName("video_mode_width", std::to_string(width));
    changed |= rex::cvar::SetFlagByName("video_mode_height", std::to_string(height));
    bool scale_changed = rex::cvar::SetFlagByName("resolution_scale", std::to_string(scale));
    changed |= scale_changed;

    if (changed) {
      SavePcSettings();
    }

    // Rebuild scale-dependent graphics resources immediately.
    if (scale_changed && app->runtime() && app->runtime()->graphics_system()) {
      app->runtime()->graphics_system()->ReinitializeContext();
    }

    // Apply the output/window resolution immediately.
    app->app_context().CallInUIThreadDeferred([app, width, height]() {
      if (app->window()) {
        auto* sdl_window = static_cast<rex::ui::WindowSDL*>(app->window());
        sdl_window->SetLogicalSize(width, height);
      }
    });
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
  rex::ui::ImGuiDrawer* imgui_drawer_ = nullptr;
  int modal_depth_ = 0;
  std::chrono::steady_clock::time_point last_dialog_closed_time_{};
};

inline HexicSettingsDialog::HexicSettingsDialog(rex::ui::ImGuiDrawer* imgui_drawer,
                                                HexicHdApp* app, int select_row)
    : rex::ui::ImGuiDialog(imgui_drawer), app_(app), selected_row_(select_row) {
  app_->BeginModal();
}

inline HexicSettingsDialog::InputEdges HexicSettingsDialog::PollInput() {
  InputEdges edges;

  // GetAsyncKeyState and XInput both read system-wide input state, not
  // state scoped to this window. Without gating on focus, keys typed (or a
  // controller used) in another application while the game is merely
  // running in the background would still drive this dialog.
  if (!app_ || !app_->HasWindowFocus()) {
    return edges;
  }

  // Keyboard: Up/Down/Left/Right/Enter/Escape, edge-triggered.
  int vks[6] = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_RETURN, VK_ESCAPE};
  bool now_down[6];
  for (int i = 0; i < 6; ++i) {
    now_down[i] = (GetAsyncKeyState(vks[i]) & 0x8000) != 0;
  }

  XINPUT_STATE state{};
  bool pad_connected = XInputGetState(0, &state) == ERROR_SUCCESS;

  if (!input_primed_) {
    // Seed the "previous state" from whatever's currently held (typically
    // the same A/Enter press that opened this dialog) without reporting it
    // as an edge.
    for (int i = 0; i < 6; ++i) {
      key_was_down_[i] = now_down[i];
    }
    if (pad_connected) {
      pad_was_connected_ = true;
      pad_buttons_prev_ = state.Gamepad.wButtons;
    }
    input_primed_ = true;
    return edges;
  }

  edges.up = now_down[0] && !key_was_down_[0];
  edges.down = now_down[1] && !key_was_down_[1];
  edges.left = now_down[2] && !key_was_down_[2];
  edges.right = now_down[3] && !key_was_down_[3];
  edges.confirm = now_down[4] && !key_was_down_[4];
  edges.back = now_down[5] && !key_was_down_[5];
  for (int i = 0; i < 6; ++i) {
    key_was_down_[i] = now_down[i];
  }

  // Controller: XInput D-pad + A (confirm) + B (back), edge-triggered.
  if (pad_connected) {
    pad_was_connected_ = true;
    WORD buttons = state.Gamepad.wButtons;
    WORD pressed = buttons & ~pad_buttons_prev_;
    if (pressed & XINPUT_GAMEPAD_DPAD_UP) edges.up = true;
    if (pressed & XINPUT_GAMEPAD_DPAD_DOWN) edges.down = true;
    if (pressed & XINPUT_GAMEPAD_DPAD_LEFT) edges.left = true;
    if (pressed & XINPUT_GAMEPAD_DPAD_RIGHT) edges.right = true;
    if (pressed & XINPUT_GAMEPAD_A) edges.confirm = true;
    if (pressed & XINPUT_GAMEPAD_B) edges.back = true;
    pad_buttons_prev_ = buttons;
  } else if (pad_was_connected_) {
    pad_buttons_prev_ = 0;
  }

  return edges;
}

inline void HexicSettingsDialog::MoveSelection(int delta) {
  selected_row_ = (selected_row_ + delta + kRowCount) % kRowCount;
}

inline void HexicSettingsDialog::CycleRow(int row, int delta) {
  switch (row) {
    case kRowFullscreen:
      HexicHdApp::SetPcFullscreen(!HexicHdApp::GetPcFullscreen());
      break;
    case kRowResolution: {
      static const int32_t kW[] = {1280, 1920, 2560, 3840};
      static const int32_t kH[] = {720, 1080, 1440, 2160};
      static const int32_t kScale[] = {1, 2, 2, 3};
      int index = HexicHdApp::GetPcResolutionIndex();
      index = (index + delta + 4) % 4;
      HexicHdApp::SetPcResolution(kW[index], kH[index], kScale[index]);
      break;
    }
    case kRowVSync:
      HexicHdApp::SetPcVSync(!HexicHdApp::GetPcVSync());
      break;
    case kRowShowFps:
      HexicHdApp::SetPcShowFps(!HexicHdApp::GetPcShowFps());
      break;
    default:
      break;
  }
}

inline void HexicSettingsDialog::ActivateRow(int row) {
  // A/Enter opens Player Name and Keyboard Controls and closes on Done; every
  // other row's value only changes via Left/Right, so a confirm press can't
  // accidentally change a setting. A sub-dialog opens before this one
  // closes, so the game's keyboard mapping stays off across the hand-over.
  if (row == kRowPlayerName) {
    app_->OpenNameEntry();
  } else if (row == kRowControls) {
    app_->OpenControls();
  } else if (row != kRowDone) {
    return;
  }
  ImGui::CloseCurrentPopup();
  Close();
}

inline void HexicSettingsDialog::DrawRow(ImDrawList* draw_list, ImVec2 pos, ImVec2 size, int row,
                                         bool selected, const char* label, const char* value,
                                         bool has_value, bool show_chevrons) {
  using namespace hexic_ui;

  ImVec2 row_max(pos.x + size.x, pos.y + size.y);
  DrawGamePill(draw_list, pos, row_max, selected);

  ImFont* body_font = HexicFonts::body ? HexicFonts::body : ImGui::GetFont();
  float label_size = body_font == HexicFonts::body ? 19.0f : ImGui::GetFontSize();
  ImVec2 label_pos(pos.x + 22.0f, pos.y + (size.y - label_size) * 0.5f);
  DrawPillText(draw_list, body_font, label_size, label_pos, kTextSelected, label);

  if (has_value && !show_chevrons) {
    // Rows that open a page (Player Name, Keyboard Controls): the value sits
    // at the right edge, with no arrows implying Left/Right changes it.
    ImVec2 value_text_size = body_font->CalcTextSizeA(label_size, FLT_MAX, 0, value);
    ImVec2 value_pos(row_max.x - 22.0f - value_text_size.x, pos.y + (size.y - label_size) * 0.5f);
    DrawPillText(draw_list, body_font, label_size, value_pos, IM_COL32(0xF0, 0xF0, 0xFA, 255),
                 value);
  } else if (has_value) {
    float chevron_inset = 34.0f;
    // White arrows read cleanly on both the purple and green pills; the game
    // uses the same bright arrows flanking its own value controls.
    ImU32 chevron_color = IM_COL32(0xFF, 0xFF, 0xFF, selected ? 255 : 210);
    DrawChevron(draw_list, ImVec2(row_max.x - size.x * 0.42f, pos.y + size.y * 0.5f), 7.0f, false,
               chevron_color);
    DrawChevron(draw_list, ImVec2(row_max.x - chevron_inset, pos.y + size.y * 0.5f), 7.0f, true,
               chevron_color);

    // Center the value text between the two chevrons.
    ImVec2 value_text_size = body_font->CalcTextSizeA(label_size, FLT_MAX, 0, value);
    float center_x = row_max.x - (size.x * 0.42f + chevron_inset) * 0.5f;
    ImVec2 value_pos(center_x - value_text_size.x * 0.5f, pos.y + (size.y - label_size) * 0.5f);
    DrawPillText(draw_list, body_font, label_size, value_pos, IM_COL32(0xF0, 0xF0, 0xFA, 255),
                 value);
  }
}

inline void HexicSettingsDialog::OnDraw(ImGuiIO& io) {
  if (!has_opened_shown_) {
    ImGui::OpenPopup("##HexicPcSettings");
    has_opened_shown_ = true;
  }

  using namespace hexic_ui;

  InputEdges input = PollInput();
  if (input.up) MoveSelection(-1);
  if (input.down) MoveSelection(1);
  if (input.left) CycleRow(selected_row_, -1);
  if (input.right) CycleRow(selected_row_, 1);
  if (input.confirm) ActivateRow(selected_row_);

  // Recompute every frame (ImGuiCond_Always) rather than only on first
  // appearance, so the panel stays centered even if the resolution row
  // changes the display size while this dialog is still open.
  ImGuiViewport* viewport = ImGui::GetMainViewport();
  ImVec2 viewport_center =
      viewport ? ImVec2(viewport->WorkPos.x + viewport->WorkSize.x * 0.5f,
                        viewport->WorkPos.y + viewport->WorkSize.y * 0.5f)
               : ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
  ImGui::SetNextWindowPos(viewport_center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));

  constexpr float kWindowWidth = 480.0f;
  ImGui::SetNextWindowSize(ImVec2(kWindowWidth, 0), ImGuiCond_Always);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 18.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  // Transparent window: only the drawn card and its glow show over the game,
  // so the panel reads as a floating menu rather than a black box.
  ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));

  bool still_open =
      ImGui::BeginPopupModal("##HexicPcSettings", nullptr,
                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
  if (still_open) {
    if (input.back) {
      ImGui::CloseCurrentPopup();
      Close();
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    ImVec2 window_pos = ImGui::GetWindowPos();

    constexpr int kRows = kRowCount;
    constexpr float kRowHeight = 46.0f;
    constexpr float kRowSpacing = 10.0f;
    constexpr float kSideMargin = 26.0f;
    constexpr float kTopContent = 78.0f;
    constexpr float kBottomMargin = 22.0f;
    float content_height =
        kTopContent + kRows * kRowHeight + (kRows - 1) * kRowSpacing + kBottomMargin;
    ImVec2 window_size(kWindowWidth, content_height);
    ImVec2 window_end(window_pos.x + window_size.x, window_pos.y + window_size.y);

    ImGui::Dummy(window_size);

    DrawHexicCard(draw_list, window_pos, window_end, kSideMargin, "PC SETTINGS");

    static const char* kRowLabels[kRowCount] = {
        "Player Name",
        "Display Mode",
        "Resolution",
        "VSync",
        "Show FPS",
        "Keyboard Controls",
        "Done",
    };
    static const char* kResolutionValues[4] = {
        "1280 x 720",
        "1920 x 1080",
        "2560 x 1440",
        "3840 x 2160",
    };

    float row_y = window_pos.y + kTopContent;
    for (int row = 0; row < kRows; ++row) {
      ImVec2 row_pos(window_pos.x + kSideMargin, row_y);
      ImVec2 row_size(window_size.x - kSideMargin * 2.0f, kRowHeight);
      bool selected = (row == selected_row_);

      const char* value = nullptr;
      bool has_value = true;
      std::string value_storage;
      const bool opens_page = row == kRowPlayerName || row == kRowControls;
      switch (row) {
        case kRowPlayerName:
          value_storage = HexicHdApp::PlayerName();
          value = value_storage.c_str();
          break;
        case kRowControls:
          value = "Customize";
          break;
        case kRowFullscreen:
          value = HexicHdApp::GetPcFullscreen() ? "Fullscreen" : "Windowed";
          break;
        case kRowResolution:
          value = kResolutionValues[HexicHdApp::GetPcResolutionIndex()];
          break;
        case kRowVSync:
          value = HexicHdApp::GetPcVSync() ? "On" : "Off";
          break;
        case kRowShowFps:
          value = HexicHdApp::GetPcShowFps() ? "On" : "Off";
          break;
        default:
          has_value = false;
          value = "";
          break;
      }

      // Done reads as a full-width action row, not a value spinner - a glossy
      // pill with its label centred, matching the game's own menu buttons.
      bool is_action_row = (row == kRowDone);
      if (is_action_row) {
        ImVec2 row_max(row_pos.x + row_size.x, row_pos.y + row_size.y);
        DrawGamePill(draw_list, row_pos, row_max, selected);
        ImFont* body_font = HexicFonts::body ? HexicFonts::body : ImGui::GetFont();
        float font_size = HexicFonts::body ? 19.0f : ImGui::GetFontSize();
        ImVec2 text_size = body_font->CalcTextSizeA(font_size, FLT_MAX, 0, kRowLabels[row]);
        ImVec2 text_pos(row_pos.x + (row_size.x - text_size.x) * 0.5f,
                        row_pos.y + (row_size.y - font_size) * 0.5f);
        DrawPillText(draw_list, body_font, font_size, text_pos, kTextSelected, kRowLabels[row]);
      } else {
        DrawRow(draw_list, row_pos, row_size, row, selected, kRowLabels[row], value, has_value,
                !opens_page);
      }

      // Mouse fallback. Done is a single full-width activation button.
      // Every other row only changes value via
      // the drawn left/right chevrons (matching Left/Right being the only
      // way to change a value); clicking anywhere else on the row just
      // selects it, same as clicking any other non-actionable row.
      ImGui::PushID(row);
      if (is_action_row || opens_page) {
        ImGui::SetCursorScreenPos(row_pos);
        if (ImGui::InvisibleButton("row", row_size)) {
          selected_row_ = row;
          ActivateRow(row);
        }
      } else if (has_value) {
        float row_right = row_pos.x + row_size.x;
        float chevron_left_x = row_right - row_size.x * 0.42f;
        float chevron_right_x = row_right - 34.0f;
        constexpr float kChevronHitHalfWidth = 20.0f;
        float band1_end = chevron_left_x - kChevronHitHalfWidth;
        float band2_end = chevron_left_x + kChevronHitHalfWidth;
        float band3_end = chevron_right_x - kChevronHitHalfWidth;
        float band4_end = chevron_right_x + kChevronHitHalfWidth;

        auto place_band = [&](const char* id, float x0, float x1b) {
          if (x1b <= x0) return false;
          ImGui::SetCursorScreenPos(ImVec2(x0, row_pos.y));
          return ImGui::InvisibleButton(id, ImVec2(x1b - x0, row_size.y));
        };

        if (place_band("b1", row_pos.x, band1_end)) selected_row_ = row;
        if (place_band("b2", band1_end, band2_end)) {
          selected_row_ = row;
          CycleRow(row, -1);
        }
        if (place_band("b3", band2_end, band3_end)) selected_row_ = row;
        if (place_band("b4", band3_end, band4_end)) {
          selected_row_ = row;
          CycleRow(row, 1);
        }
        if (place_band("b5", band4_end, row_right)) selected_row_ = row;
      } else {
        ImGui::SetCursorScreenPos(row_pos);
        if (ImGui::InvisibleButton("row", row_size)) {
          selected_row_ = row;
        }
      }
      ImGui::PopID();

      row_y += kRowHeight + kRowSpacing;
    }

    ImGui::EndPopup();
  }

  ImGui::PopStyleColor(1);
  ImGui::PopStyleVar(3);

  if (!still_open) {
    // Popup was dismissed some other way; close the dialog.
    Close();
  }
}

inline void HexicSettingsDialog::OnClose() {
  if (app_) app_->EndModal();
}

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
      const std::string placeholder =
          "Windows user name (" + rex::kernel::xam::netplay::ConfiguredPlayerName("") + ")";
      draw_list->AddText(BodyFont(), BodySize(), text_pos, IM_COL32(0x9A, 0x94, 0xB8, 200),
                         placeholder.c_str());
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

// --- Keyboard Controls ---------------------------------------------------

inline HexicControlsDialog::HexicControlsDialog(rex::ui::ImGuiDrawer* imgui_drawer,
                                                HexicHdApp* app)
    : rex::ui::ImGuiDialog(imgui_drawer), app_(app) {
  app_->BeginModal();
}

inline void HexicControlsDialog::OnClose() { app_->EndModal(); }

inline void HexicControlsDialog::Activate(int row, bool append) {
  capture_row_ = row;
  capture_append_ = append;
  capture_deadline_ = std::chrono::steady_clock::now() + std::chrono::seconds(10);
  notice_row_ = -1;
  capture_ = kCaptureWaitRelease;
  REXLOG_INFO("[controls] {}: waiting for a key ({})",
              hexic_controls::Bindings()[row].button, append ? "add" : "change");
}

inline void HexicControlsDialog::ResetRow(int row) {
  const auto& binding = hexic_controls::Bindings()[row];
  hexic_controls::SetKeys(row, hexic_controls::SplitKeys(binding.defaults));
  HexicHdApp::SavePcSettings();
  notice_row_ = row;
  notice_ = "Reset to default";
  notice_until_ = std::chrono::steady_clock::now() + std::chrono::seconds(2);
}

inline void HexicControlsDialog::FinishCapture(const std::string& notice) {
  if (!notice.empty()) {
    notice_row_ = capture_row_;
    notice_ = notice;
    notice_until_ = std::chrono::steady_clock::now() + std::chrono::seconds(3);
  }
  capture_deadline_ = std::chrono::steady_clock::now() + std::chrono::seconds(3);
  capture_ = kCaptureFinish;
}

// Waits for everything to be released (the key that started the capture is
// still down), takes the next key or mouse button, then waits for that to be
// released too before handing input back to the menu.
inline void HexicControlsDialog::TickCapture() {
  const auto now = std::chrono::steady_clock::now();
  const bool expired = now > capture_deadline_;
  const bool focused = app_->HasWindowFocus();
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
    if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000) ||
        (pad_connected && (pad.Gamepad.wButtons & XINPUT_GAMEPAD_B))) {
      FinishCapture("");
      return;
    }
    std::string key;
    for (int vk = 1; key.empty() && vk < 255; ++vk) {
      // Esc cancels and F4 opens the runtime overlay, so neither can be
      // bound; the generic Shift/Ctrl/Alt codes are used, not left/right.
      const bool excluded = vk == VK_ESCAPE || vk == VK_F4 || vk == VK_LWIN || vk == VK_RWIN ||
                            vk == VK_APPS || (vk >= VK_LSHIFT && vk <= VK_RMENU);
      if (excluded || !(GetAsyncKeyState(vk) & 0x8000)) continue;
      key = vk == VK_RETURN ? "Return"
                            : rex::ui::VirtualKeyToString(static_cast<rex::ui::VirtualKey>(vk));
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
    input_.Reprime();
  }
}

inline void HexicControlsDialog::OnDraw(ImGuiIO& io) {
  using namespace hexic_ui;
  using hexic_controls::Bindings;
  const auto now = std::chrono::steady_clock::now();
  if (!has_opened_shown_) {
    ImGui::OpenPopup("##HexicControls");
    has_opened_shown_ = true;
  }

  const bool capturing = capture_ != kCaptureIdle;
  if (capturing) {
    TickCapture();
  } else {
    input_.Poll(app_->HasWindowFocus());
  }

  constexpr float kWindowWidth = 660.0f;
  constexpr int kVisibleRows = 9;
  constexpr float kRowHeight = 38.0f;
  constexpr float kRowSpacing = 7.0f;
  constexpr float kSideMargin = 26.0f;
  const int row_count = RowCount();

  PushDialogStyle(io, kWindowWidth);
  const bool still_open =
      ImGui::BeginPopupModal("##HexicControls", nullptr,
                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
  if (still_open) {
    bool close = false;
    int activate = -1;  // a row to act on as if confirmed
    if (!capturing) {
      if (input_.Pressed(HexicMenuInput::kUp)) selected_ = (selected_ + row_count - 1) % row_count;
      if (input_.Pressed(HexicMenuInput::kDown)) selected_ = (selected_ + 1) % row_count;
      if (input_.Pressed(HexicMenuInput::kConfirm)) activate = selected_;
      if (input_.Pressed(HexicMenuInput::kAlt) && selected_ < ResetAllRow()) {
        Activate(selected_, true);
      }
      if (input_.Pressed(HexicMenuInput::kReset) && selected_ < ResetAllRow()) ResetRow(selected_);
      if (input_.Pressed(HexicMenuInput::kBack)) close = true;
    }

    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 window_pos = ImGui::GetWindowPos();
    const float list_height = kVisibleRows * kRowHeight + (kVisibleRows - 1) * kRowSpacing;
    const ImVec2 window_size(kWindowWidth, 55.0f + 44.0f + list_height + 64.0f);
    const ImVec2 window_end(window_pos.x + window_size.x, window_pos.y + window_size.y);
    ImGui::Dummy(window_size);

    const float accent_y =
        DrawHexicCard(draw_list, window_pos, window_end, kSideMargin, "KEYBOARD CONTROLS");
    DrawHint(draw_list, window_pos.x, window_end.x, accent_y + 10.0f,
             "Keys for each controller input. A controller works alongside them.");

    // Mouse wheel scrolls; the selection is otherwise kept in view.
    if (ImGui::IsWindowHovered() && io.MouseWheel != 0.0f && !capturing) {
      scroll_top_ -= io.MouseWheel > 0 ? 1 : -1;
    } else {
      if (selected_ < scroll_top_) scroll_top_ = selected_;
      if (selected_ >= scroll_top_ + kVisibleRows) scroll_top_ = selected_ - kVisibleRows + 1;
    }
    scroll_top_ = std::clamp(scroll_top_, 0, row_count - kVisibleRows);

    const float list_top = accent_y + 44.0f;
    const float row_left = window_pos.x + kSideMargin;
    const float row_right = window_end.x - kSideMargin;
    for (int i = 0; i < kVisibleRows; ++i) {
      const int row = scroll_top_ + i;
      const ImVec2 pos(row_left, list_top + i * (kRowHeight + kRowSpacing));
      const ImVec2 max(row_right, pos.y + kRowHeight);
      const bool selected = row == selected_;
      DrawGamePill(draw_list, pos, max, selected);
      const float text_y = pos.y + (kRowHeight - BodySize()) * 0.5f;
      const bool noticed = row == notice_row_ && now < notice_until_;

      if (row >= ResetAllRow()) {
        const char* label = row == DoneRow() ? "Done" : "Reset All to Defaults";
        if (noticed) label = notice_.c_str();
        ImVec2 size = BodyFont()->CalcTextSizeA(BodySize(), FLT_MAX, 0, label);
        DrawPillText(draw_list, BodyFont(), BodySize(),
                     ImVec2(pos.x + (max.x - pos.x - size.x) * 0.5f, text_y),
                     kTextSelected, label);
      } else {
        const auto& binding = Bindings()[row];
        std::string value;
        if (capture_row_ == row && (capture_ == kCaptureWaitRelease || capture_ == kCaptureListen)) {
          value = "Press a key...  (Esc cancels)";
        } else if (noticed) {
          value = notice_;
        } else {
          value = hexic_controls::FormatKeys(hexic_controls::KeysOf(row));
        }
        const float value_width =
            BodyFont()->CalcTextSizeA(BodySize(), FLT_MAX, 0, value.c_str()).x;
        const float value_x = max.x - 20.0f - value_width;
        DrawPillText(draw_list, BodyFont(), BodySize(), ImVec2(pos.x + 20.0f, text_y),
                     kTextSelected, binding.button);
        if (binding.action[0]) {
          draw_list->PushClipRect(ImVec2(pos.x + 178.0f, pos.y), ImVec2(value_x - 12.0f, max.y),
                                  true);
          draw_list->AddText(BodyFont(), BodySize(), ImVec2(pos.x + 178.0f, text_y),
                             IM_COL32(0xE4, 0xDC, 0xF8, 170), binding.action);
          draw_list->PopClipRect();
        }
        const ImU32 value_color = (capture_row_ == row || noticed)
                                      ? IM_COL32(0xFF, 0xE8, 0x7A, 255)
                                      : IM_COL32(0xF0, 0xF0, 0xFA, 255);
        DrawPillText(draw_list, BodyFont(), BodySize(), ImVec2(value_x, text_y), value_color,
                     value.c_str());
      }

      // Mouse: clicking a row selects it and acts on it.
      ImGui::PushID(row);
      ImGui::SetCursorScreenPos(pos);
      if (ImGui::InvisibleButton("row", ImVec2(max.x - pos.x, kRowHeight)) && !capturing) {
        selected_ = row;
        activate = row;
      }
      ImGui::PopID();
    }

    // Scroll position, as a thin bar beside the list.
    const float track_x = window_end.x - 16.0f;
    const float thumb_h = list_height * float(kVisibleRows) / float(row_count);
    const float thumb_y =
        list_top + (list_height - thumb_h) * float(scroll_top_) / float(row_count - kVisibleRows);
    draw_list->AddRectFilled(ImVec2(track_x, list_top), ImVec2(track_x + 4.0f, list_top + list_height),
                             IM_COL32(0x5A, 0x50, 0x92, 90), 2.0f);
    draw_list->AddRectFilled(ImVec2(track_x, thumb_y), ImVec2(track_x + 4.0f, thumb_y + thumb_h),
                             kAccentCyan, 2.0f);

    const float footer_y = list_top + list_height + 16.0f;
    DrawHint(draw_list, window_pos.x, window_end.x, footer_y,
             "Enter/A  Change     Tab/Y  Add a key     Backspace/X  Reset     Esc/B  Back");

    if (activate >= 0) {
      if (activate < ResetAllRow()) {
        Activate(activate, false);
      } else if (activate == ResetAllRow()) {
        hexic_controls::ResetAll();
        HexicHdApp::SavePcSettings();
        notice_row_ = activate;
        notice_ = "All keys reset to defaults";
        notice_until_ = now + std::chrono::seconds(2);
      } else {
        close = true;
      }
    }
    if (close) {
      app_->OpenSettings(HexicSettingsDialog::kRowControls);
      ImGui::CloseCurrentPopup();
      Close();
    }
    ImGui::EndPopup();
  }
  PopDialogStyle();
  if (!still_open) Close();
}

inline void HexicSignInHook::OnDraw(ImGuiIO& /*io*/) {
  if (app_ && app_->TrySetSignedInToLive()) {
    Close();
  }
}
