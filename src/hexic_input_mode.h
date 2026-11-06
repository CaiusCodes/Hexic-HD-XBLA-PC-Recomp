#pragma once

// Which input the player is using, for the button prompts (the keycap overlay
// and the Settings hints): the keyboard and mouse, or a controller. The last
// one used wins, so both can be used on the fly; plugging a controller in
// switches to it, and unplugging the last one switches back to the keyboard.
//
// Controller side: InputSystem::SetControllerActivityCallback (SDK), called on
// every pad poll the game makes with what the controller drivers (SDL, which
// covers Xbox, PlayStation and other pads, or XInput) saw for that user.
// Keyboard / mouse side: the game window's own key and mouse events
// (InputModeListener in hexic_hd_app.h), so only input aimed at the game
// counts.

#include <atomic>
#include <cstdint>
#include <cstdlib>

#include <rex/logging.h>

namespace hexic_input_mode {

enum Mode : int { kKeyboardMouse = 0, kController = 1 };

inline std::atomic<int> g_mode{kKeyboardMouse};
inline std::atomic<uint32_t> g_connected_users{0};  // a bit per user with a controller

inline bool UsingController() { return g_mode.load(std::memory_order_relaxed) == kController; }

inline void SetMode(Mode mode, const char* why) {
  if (g_mode.exchange(mode, std::memory_order_relaxed) != mode) {
    REXLOG_INFO("[input] prompts for the {} ({})",
                mode == kController ? "controller" : "keyboard and mouse", why);
  }
}

// Game thread: one pad poll's controller report for `user`.
inline void NoteController(uint32_t user, bool connected, bool active) {
  if (user < 32) {
    const uint32_t bit = 1u << user;
    const uint32_t before = g_connected_users.load(std::memory_order_relaxed);
    const uint32_t after = connected ? (before | bit) : (before & ~bit);
    if (after != before) {
      g_connected_users.store(after, std::memory_order_relaxed);
      if (!before && after) SetMode(kController, "controller connected");
      if (before && !after) SetMode(kKeyboardMouse, "controller disconnected");
    }
  }
  if (active) SetMode(kController, "controller used");
}

// UI thread: a key or a mouse button went down in the game window.
inline void NoteKeyboardMouse() { SetMode(kKeyboardMouse, "keyboard or mouse used"); }

// UI thread: the mouse moved in the game window. Only a deliberate move counts
// (8 px from where it last rested), not a nudge of the desk.
class MouseMoves {
 public:
  void Note(int32_t x, int32_t y) {
    if (!anchored_) {
      anchored_ = true;
      ax_ = x;
      ay_ = y;
      return;
    }
    if (std::abs(x - ax_) + std::abs(y - ay_) >= 8) {
      ax_ = x;
      ay_ = y;
      NoteKeyboardMouse();
    }
  }

 private:
  bool anchored_ = false;
  int32_t ax_ = 0, ay_ = 0;
};

}  // namespace hexic_input_mode
