#pragma once
// The "Press A to continue" title screen on PC:
//  - its prompt says "Press any key to continue." when no controller is
//    connected as the game starts (the text is line 803 of the imported g.xml,
//    which the game reads once, at start);
//  - while it is showing, any key or a left click in the window counts as A.
//
// The title screen is how the Xbox game learns which controller is playing:
// the active pad slot at 0x9226FCA4 reads -1 (0xFFFFFFFF) from boot until A is
// pressed there, then the pad's index (checked 2026-11-06: -1 for the whole
// title screen including its loading, 0 the moment A reached the game).

#include <windows.h>
#include <xinput.h>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include <rex/logging.h>

namespace hexic_title {

constexpr uint32_t kActivePadSlot = 0x9226FCA4;
constexpr uint32_t kNoActivePad = 0xFFFFFFFF;

inline bool ControllerConnected() {
  for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i) {
    XINPUT_STATE state = {};
    if (XInputGetState(i, &state) == ERROR_SUCCESS) return true;
  }
  return false;
}

// Rewrites menu text in <assets>\g.xml as the game starts (it reads the file
// once, at start): the title prompt to suit the input present now, and PC
// wording added after the launcher's import-time relabels, so installs
// imported earlier get it too. Every change is a no-op once applied.
inline void ApplyMenuText(const std::filesystem::path& assets, bool controller) {
  struct Replacement {
    const char* from;
    const char* to;
  };
  const Replacement kPrompt = controller
      ? Replacement{">Press any key to continue.<", ">Press A to continue.<"}
      : Replacement{">Press A to continue.<", ">Press any key to continue.<"};
  static const Replacement kWording[] = {
      // The game's own Options screen, so it doesn't read like Settings.
      {">Options</text>", ">Game Options</text>"},
      {"Change your settings, and see who made this game.",
       "Change the sound and piece pattern, and see who made this game."},
      {"Go to the Options menu,", "Go to the Game Options menu,"},
      {"Change display, audio and performance settings.",
       "Change display, graphics and keyboard settings."},
  };
  // Pad wording and its keyboard and mouse form, swapped to suit the input
  // present at start (the tutorial cards and the save error messages).
  static const Replacement kPadText[] = {
      {"Press A to rotate the group clockwise, or press X to rotate it counterclockwise. "
       "Or, pull either trigger to rotate the pieces.",
       "Press E or left click to rotate the group clockwise, or press Q or right click to "
       "rotate it counterclockwise."},
      {"Please press A to continue", "Please press Enter to continue"},
  };
  // Offline there is no Guide button or LIVE to sign in to.
  static const Replacement kOffline[] = {
      {"Press the Xbox Guide Button to sign in to Xbox Live to post your score!!",
       "Your score goes on the High Scores list."},
  };
  const auto path = assets / "g.xml";
  std::ifstream in(path, std::ios::binary);
  if (!in) return;
  std::stringstream buffer;
  buffer << in.rdbuf();
  in.close();
  std::string text = buffer.str();
  bool changed = false;
  auto replace = [&](const Replacement& r) {
    for (size_t at = text.find(r.from); at != std::string::npos; at = text.find(r.from, at)) {
      text.replace(at, std::strlen(r.from), r.to);
      at += std::strlen(r.to);
      changed = true;
    }
  };
  replace(kPrompt);
  for (const Replacement& r : kWording) replace(r);
  for (const Replacement& r : kOffline) replace(r);
  for (const Replacement& r : kPadText) {
    replace(controller ? Replacement{r.to, r.from} : r);
  }
  if (!changed) return;
  std::ofstream out(path, std::ios::binary | std::ios::trunc);
  out.write(text.data(), static_cast<std::streamsize>(text.size()));
  REXLOG_INFO("[title] menu text updated; prompt: {}",
              controller ? "Press A to continue." : "Press any key to continue.");
}

// Any key, or a mouse click in the game window, while the title screen shows
// becomes one A press. Presses come from the window's own key and mouse events
// (HexicHdApp::OnKeyDown / OnMouseDown, UI thread), so only input aimed at the
// game counts, and clicks on the title bar don't.
class AnyKeyStarts {
 public:
  // UI thread: a key (not Alt / Windows, which come with switching windows)
  // or a mouse button went down in the game window.
  void NotePress() { pending_.fetch_add(1, std::memory_order_relaxed); }

  // Called on every pad poll (game thread). on_title: the title screen shows.
  uint16_t Poll(bool on_title) {
    const auto now = std::chrono::steady_clock::now();
    const int pending = pending_.exchange(0, std::memory_order_relaxed);
    if (on_title && pending > 0) hold_until_ = now + std::chrono::milliseconds(120);
    return on_title && now < hold_until_ ? 0x1000 /* A */ : 0;
  }

 private:
  std::atomic<int> pending_{0};
  std::chrono::steady_clock::time_point hold_until_{};
};

}  // namespace hexic_title
