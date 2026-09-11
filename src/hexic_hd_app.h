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
#include <memory>
#include <string_view>
#include <string>

#include <imgui.h>

#include <rex/cvar.h>
#include <rex/kernel/xam/ui_hooks.h>
#include <rex/logging.h>
#include <rex/rex_app.h>
#include <rex/system/kernel_state.h>
#include <rex/ui/imgui_dialog.h>
#include <rex/ui/imgui_drawer.h>
#include <rex/ui/window.h>
#include <rex/ui/window_sdl.h>

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

}  // namespace hexic_ui

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
  explicit HexicSettingsDialog(rex::ui::ImGuiDrawer* imgui_drawer, HexicHdApp* app)
      : rex::ui::ImGuiDialog(imgui_drawer), app_(app) {
    // The panel polls raw keyboard/controller state directly so it works
    // without a mouse; the guest's own input drivers poll that same raw
    // state at the same time and are still fully live behind this "modal"
    // popup. mnk_mode in particular maps common keys (Escape -> Start,
    // etc.) that the guest's main menu acts on immediately, up to and
    // including exiting the game. Suspend it for the panel's lifetime.
    mnk_mode_was_enabled_ = rex::cvar::GetFlagByName("mnk_mode") == "true";
    if (mnk_mode_was_enabled_) {
      rex::cvar::SetFlagByName("mnk_mode", "false");
    }
  }

  void OnDraw(ImGuiIO& io) override;

 protected:
  void OnClose() override;

 private:
  enum Row : int {
    kRowFullscreen = 0,
    kRowResolution,
    kRowVSync,
    kRowShowFps,
    kRowDone,
    kRowCount,
  };

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
              const char* label, const char* value, bool has_value);

  HexicHdApp* app_;
  bool has_opened_shown_ = false;
  int selected_row_ = kRowFullscreen;

  // Edge-detection state for keyboard and controller polling.
  bool key_was_down_[6] = {};
  WORD pad_buttons_prev_ = 0;
  bool pad_was_connected_ = false;
  bool mnk_mode_was_enabled_ = false;
  // The first PollInput() call only seeds key_was_down_/pad_buttons_prev_
  // and reports no edges: the button that opened this dialog (e.g. A on the
  // main menu) is often still physically held on that first polled frame,
  // and without priming it would read as a fresh edge here too.
  bool input_primed_ = false;
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
      if (imgui_drawer_ && !settings_dialog_open_ && !in_cooldown) {
        settings_dialog_open_ = true;
        imgui_drawer_->AddDialog(new HexicSettingsDialog(imgui_drawer_, this));
      }
    });

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

  void OnSettingsDialogClosed() {
    settings_dialog_open_ = false;
    last_dialog_closed_time_ = std::chrono::steady_clock::now();
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
  // void OnPostSetup() override {}
  // std::unique_ptr<rex::ui::ImGuiDialog> CreateAchievementsOverlay() override;
  // std::unique_ptr<rex::ui::AchievementNotificationDialog>
  // CreateAchievementNotificationDialog() override;
  // void OnShutdown() override {}

 private:
  inline static HexicHdApp* current_instance_ = nullptr;
  rex::ui::ImGuiDrawer* imgui_drawer_ = nullptr;
  bool settings_dialog_open_ = false;
  std::chrono::steady_clock::time_point last_dialog_closed_time_{};
};

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
  // Only Done responds to A/Enter; every other row's value only changes via
  // Left/Right, so a confirm press can't accidentally change a setting.
  if (row == kRowDone) {
    ImGui::CloseCurrentPopup();
    Close();
  }
}

inline void HexicSettingsDialog::DrawRow(ImDrawList* draw_list, ImVec2 pos, ImVec2 size, int row,
                                         bool selected, const char* label, const char* value,
                                         bool has_value) {
  using namespace hexic_ui;

  ImVec2 row_max(pos.x + size.x, pos.y + size.y);
  DrawGamePill(draw_list, pos, row_max, selected);

  ImFont* body_font = HexicFonts::body ? HexicFonts::body : ImGui::GetFont();
  float label_size = body_font == HexicFonts::body ? 19.0f : ImGui::GetFontSize();
  ImVec2 label_pos(pos.x + 22.0f, pos.y + (size.y - label_size) * 0.5f);
  DrawPillText(draw_list, body_font, label_size, label_pos, kTextSelected, label);

  if (has_value) {
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

    // Deep violet metallic card with a soft outer glow, echoing the title
    // screen's panel, so it sits over the menu like one of the game's own.
    ImVec2 card_min(window_pos.x + 8, window_pos.y + 6);
    ImVec2 card_max(window_end.x - 8, window_end.y - 6);
    for (int i = 4; i >= 1; --i) {
      float grow = i * 2.5f;
      draw_list->AddRect(ImVec2(card_min.x - grow, card_min.y - grow),
                         ImVec2(card_max.x + grow, card_max.y + grow),
                         IM_COL32(0x7A, 0x4C, 0xFF, 18 + (4 - i) * 14), 18.0f + grow, 0, 2.0f);
    }
    draw_list->AddRectFilled(card_min, card_max, IM_COL32(0x17, 0x12, 0x2C, 252), 16.0f);
    // A faint sheen over the top half and the honeycomb corners, then the rim.
    draw_list->AddRectFilled(card_min, ImVec2(card_max.x, card_min.y + (card_max.y - card_min.y) * 0.5f),
                             IM_COL32(0x33, 0x28, 0x58, 90), 16.0f, ImDrawFlags_RoundCornersTop);
    draw_list->PushClipRect(card_min, card_max, true);
    DrawHexCluster(draw_list, ImVec2(card_min.x - 4, card_min.y - 4), 4, 5, 20.0f);
    DrawHexCluster(draw_list, ImVec2(card_max.x - 80, card_min.y - 4), 4, 5, 20.0f);
    draw_list->PopClipRect();
    draw_list->AddRect(card_min, card_max, kCardBorder, 16.0f, 0, 2.0f);

    ImFont* heading_font = HexicFonts::heading ? HexicFonts::heading : ImGui::GetFont();
    float heading_size = HexicFonts::heading ? 27.0f : ImGui::GetFontSize() * 1.3f;
    ImVec2 heading_pos(window_pos.x + kSideMargin, window_pos.y + 20.0f);
    draw_list->AddText(heading_font, heading_size, ImVec2(heading_pos.x, heading_pos.y + 1.5f),
                       kTextShadow, "PC SETTINGS");
    draw_list->AddText(heading_font, heading_size, heading_pos, kTextSelected, "PC SETTINGS");

    float accent_y = window_pos.y + 20.0f + heading_size + 8.0f;
    draw_list->AddLine(ImVec2(window_pos.x + kSideMargin, accent_y),
                       ImVec2(window_end.x - kSideMargin, accent_y), kAccentCyan, 2.0f);

    static const char* kRowLabels[kRowCount] = {
        "Display Mode",
        "Resolution",
        "VSync",
        "Show FPS",
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
      switch (row) {
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
        DrawRow(draw_list, row_pos, row_size, row, selected, kRowLabels[row], value, has_value);
      }

      // Mouse fallback. Done is a single full-width activation button.
      // Every other row only changes value via
      // the drawn left/right chevrons (matching Left/Right being the only
      // way to change a value); clicking anywhere else on the row just
      // selects it, same as clicking any other non-actionable row.
      ImGui::PushID(row);
      if (is_action_row) {
        ImGui::SetCursorScreenPos(row_pos);
        if (ImGui::InvisibleButton("row", row_size)) {
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
  if (mnk_mode_was_enabled_) {
    rex::cvar::SetFlagByName("mnk_mode", "true");
  }
  if (app_) {
    app_->OnSettingsDialogClosed();
  }
}

inline void HexicSignInHook::OnDraw(ImGuiIO& /*io*/) {
  if (app_ && app_->TrySetSignedInToLive()) {
    Close();
  }
}
