#pragma once
// Extra controller input for Hexic, added to every poll of the game's pad
// through the SDK's button filter (Hexic reads input only via
// XamInputGetState, so this reaches every screen):
//  - test presses read from a text file (hexic_test_input_file, test builds
//    only; empty = off). It drives the game without focus and never sends
//    keystrokes to Windows. Each new line is one press: A B X Y START BACK UP
//    DOWN LEFT RIGHT LB RB, or WAIT. Lines are read once, so appending more
//    lines drives the game step by step.

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <deque>
#include <functional>
#include <mutex>
#include <string>

#include <rex/cvar.h>
#include <rex/logging.h>

#include "hexic_mouse.h"

REXCVAR_DEFINE_STRING(hexic_test_input_file, "", "Hexic",
                      "Test-only: text file of pad presses to play back (empty = off)");

namespace hexic_input {

// X_INPUT_GAMEPAD_* bits.
constexpr uint16_t kDpadUp = 0x0001, kDpadDown = 0x0002, kDpadLeft = 0x0004, kDpadRight = 0x0008,
                   kStart = 0x0010, kBack = 0x0020, kLeftShoulder = 0x0100,
                   kRightShoulder = 0x0200, kA = 0x1000, kB = 0x2000, kX = 0x4000, kY = 0x8000;

class TestPresses {
 public:
  // Buttons the current test press holds down (0 between presses).
  uint16_t Poll() {
    std::lock_guard lock(mutex_);
    const auto now = std::chrono::steady_clock::now();
    ReadNewLines(now);
    if (holding_ && now >= phase_end_) {
      holding_ = false;
      phase_end_ = now + kGap;
    }
    if (!holding_ && now >= phase_end_ && !queue_.empty()) {
      current_ = queue_.front();
      queue_.pop_front();
      holding_ = true;
      phase_end_ = now + kHold;
      REXLOG_INFO("[test input] press {:04X}", current_);
    }
    return holding_ ? current_ : 0;
  }

 private:
  // Long enough for a game that samples once a frame to see it once.
  static constexpr auto kHold = std::chrono::milliseconds(120);
  static constexpr auto kGap = std::chrono::milliseconds(150);

  static uint16_t ParseWord(const std::string& word) {
    if (word == "A") return kA;
    if (word == "B") return kB;
    if (word == "X") return kX;
    if (word == "Y") return kY;
    if (word == "START") return kStart;
    if (word == "BACK") return kBack;
    if (word == "UP") return kDpadUp;
    if (word == "DOWN") return kDpadDown;
    if (word == "LEFT") return kDpadLeft;
    if (word == "RIGHT") return kDpadRight;
    if (word == "LB") return kLeftShoulder;
    if (word == "RB") return kRightShoulder;
    return 0;  // WAIT, or anything else: an empty press
  }

  // Test pointer for the menu mouse (stage pixels): HOVER=x,y moves it,
  // CLICK=x,y moves it and left-clicks, RCLICK right-clicks. Applied at once.
  static bool PointerWord(const std::string& word) {
    float x = 0, y = 0;
    const bool hover = word.rfind("HOVER=", 0) == 0;
    const bool click = word.rfind("CLICK=", 0) == 0;
    if ((hover || click) && std::sscanf(word.c_str() + 6, "%f,%f", &x, &y) == 2) {
      hexic_mouse::g_test_x = x;
      hexic_mouse::g_test_y = y;
      hexic_mouse::g_test_pointer = true;
      if (click) ++hexic_mouse::g_test_clicks;
      REXLOG_INFO("[test input] pointer {} ({:.0f},{:.0f})", click ? "click" : "hover", x, y);
      return true;
    }
    if (word == "RCLICK") {
      hexic_mouse::g_test_pointer = true;
      ++hexic_mouse::g_test_right_clicks;
      REXLOG_INFO("[test input] pointer right click");
      return true;
    }
    // SETTING=name,value: change a Settings row as its dialog would (the
    // dialog reads the real keyboard, so tests can't drive it). Applied on the
    // UI thread by the app (g_setting_hook).
    if (word.rfind("SETTING=", 0) == 0) {
      const size_t comma = word.find(',');
      if (comma != std::string::npos && g_setting_hook) {
        REXLOG_INFO("[test input] setting {}", word.substr(8));
        g_setting_hook(word.substr(8, comma - 8), word.substr(comma + 1));
      }
      return true;
    }
    return false;
  }

 public:
  inline static std::function<void(std::string name, std::string value)> g_setting_hook;

 private:

  void ReadNewLines(std::chrono::steady_clock::time_point now) {
    if (now - last_read_ < std::chrono::milliseconds(100)) return;
    last_read_ = now;
    const std::string path = rex::cvar::GetFlagByName("hexic_test_input_file");
    if (path.empty()) return;
    FILE* file = std::fopen(path.c_str(), "rb");
    if (!file) return;
    std::fseek(file, 0, SEEK_END);
    const long size = std::ftell(file);
    if (size > 0 && static_cast<uint64_t>(size) > read_pos_) {
      std::string text(static_cast<size_t>(size - read_pos_), '\0');
      std::fseek(file, static_cast<long>(read_pos_), SEEK_SET);
      text.resize(std::fread(text.data(), 1, text.size(), file));
      const size_t last_newline = text.rfind('\n');  // only whole lines
      if (last_newline != std::string::npos) {
        text.resize(last_newline + 1);
        read_pos_ += text.size();
        size_t start = 0;
        while (start < text.size()) {
          const size_t end = text.find('\n', start);
          std::string word = text.substr(start, end - start);
          start = end + 1;
          while (!word.empty() && (word.back() == '\r' || word.back() == ' ')) word.pop_back();
          if (PointerWord(word)) continue;
          if (!word.empty()) queue_.push_back(ParseWord(word));
        }
      }
    }
    std::fclose(file);
  }

  std::mutex mutex_;
  std::deque<uint16_t> queue_;
  uint16_t current_ = 0;
  bool holding_ = false;
  std::chrono::steady_clock::time_point phase_end_{};
  std::chrono::steady_clock::time_point last_read_{};
  uint64_t read_pos_ = 0;
};

}  // namespace hexic_input
