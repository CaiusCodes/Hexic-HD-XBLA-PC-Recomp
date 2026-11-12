#pragma once
// Mouse in Hexic. In the menus hover highlights a button, left click selects
// it (A), right click goes back (B). In a game the board cursor follows the
// pointer; left click rotates clockwise there (A), right click counter-
// clockwise (X).
//
// The menus and the board are drawn by the game's small built-in Flash player
// and driven by its ActionScript, which moves the highlight / cursor one step
// per D-pad press. This reads the player's display list to find the buttons
// and the cursor and where they are, then drives the game's own navigation.
// To be quick it alternates D-pad and left-stick presses (the game reads them
// separately, so each is a fresh press): one step every frame, fired as a
// burst toward the goal, then checked and corrected.
//
// Player structures (found 2026-11-06):
//  - a button highlights with gotoAndStop("over") and unhighlights with "up";
//    sub_92074078(clip, label) is that jump (hooked in main.cpp, NoteLabel).
//    The screen clip (no parent) gets the screen labels: Splash, Menu,
//    Options, DifficultySelection, Pause, GameOver ..., and "Active" /
//    "Level_n" while a game is played;
//  - movie clip: +76 a, +80 b, +84 tx (int twips), +88 d, +92 c, +96 ty,
//    +136 _visible (byte), +144/+148 timeline children and +172/+176
//    attached children (attachMovie; the board), each a list of entry
//    pointers whose first word is the object, +196 parent, +200 definition;
//  - sprite definition: first word = a little way into itself (+0x40,
//    +0x80, ...); +4 frames (pointers), a frame's +4/+8 its place records;
//    +24 frame-label map header (std::map: node +0 left, +4 parent, +8 right,
//    +12 label string object);
//  - place record: +4 definition, +8 a, +12 b, +16 tx, +20 d, +24 c, +28 ty;
//  - shape (vtable 0x9203A788) and text (0x92003F20) definitions: bounds as
//    four int16 twips at +4 (xmin, xmax, ymin, ymax);
//  - string object: [refcount][length][text];
//  - the board cursor is a sprite with the frames Normal, Flower, PearlUp and
//    PearlDown; a step moves it 32 or 65 px left / right, 28 px up / down
//    with a 16 px sideways zigzag.
// The stage is 1280 x 720, drawn letterboxed into the window.

#include <windows.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <deque>
#include <unordered_map>
#include <vector>

#include <rex/logging.h>
#include <rex/system/xmemory.h>

namespace hexic_mouse {

// Set by the gotoAndStop hook: the clip that last jumped to "over".
inline std::atomic<uint32_t> g_highlighted{0};

// Test pointer (hexic_test_input_file: HOVER=x,y / CLICK=x,y / RCLICK, stage
// pixels). While set, it stands in for the real mouse, without focus.
inline std::atomic<bool> g_test_pointer{false};
inline std::atomic<float> g_test_x{0}, g_test_y{0};
inline std::atomic<int> g_test_clicks{0}, g_test_right_clicks{0};

// The screen clip (no parent) and whether its state is play: "Level_n" while
// a level's card shows, then "Active" (the board and side panel only).
inline std::atomic<uint32_t> g_root{0};
inline std::atomic<bool> g_play{false};
inline std::atomic<bool> g_active{false};

// Screens whose pad icons get keycaps (HexicKeycapOverlay), by the screen
// clip's label.
enum Screen : int {
  kScreenOther,
  kScreenActive,       // play: X / A icons and the Start icon by "Pause"
  kScreenBack,         // "Back (B)" at the panel's foot (difficulty, tutorial list)
  kScreenHowTo,        // tutorial page: "(A) Next Page" and "Menu (B)"
  kScreenLeaderboard,  // High Scores: "Back (B)" bottom right
  kScreenTitle,        // the title screen ("Press any key"): the version, bottom left
};
inline std::atomic<int> g_screen{kScreenOther};
// The main menu shows (not a game, its pause menu or a level card): updating,
// which closes the game, is offered only then.
inline std::atomic<bool> g_on_main_menu{false};

// The screen as drawn, for the keycaps. A label set during a game frame shows
// from the next frame's picture, and that picture reaches the window a frame
// or two later still (the GPU thread swaps it in). Following g_screen, the
// caps came and went 1-3 frames before the picture changed, showing the pad
// icons on the way into and out of every screen. So each game frame's screen
// is kept by frame number (the present routine, game thread), and the overlay
// looks up the frame the GPU has swapped in (GraphicsSystem::guest_frame_count,
// which counts the same presents).
// The two counts don't start together: while the game loads, presents run
// ahead of swaps (22-32 apart afterwards in testing). So the offset is
// measured at each present: presents so far minus frames swapped in, at its
// smallest (the GPU has caught up) over the last 32 presents. A short window
// matters: with a 2 s one the gap's value from loading (0) stayed in use for
// the first seconds of the menus, putting the keycaps ~0.4 s behind the
// picture (pad icons showed on the first screens opened quickly after start).
inline constexpr uint64_t kScreenRing = 64;
inline std::atomic<int> g_frame_screens[kScreenRing] = {};  // kScreenOther == 0
inline std::atomic<uint64_t> g_presents{0};
inline std::atomic<uint64_t (*)()> g_swap_counter{nullptr};  // set by the app
inline std::atomic<int64_t> g_swap_offset{-1};               // -1: not known yet
inline constexpr int kGapWindow = 32;
inline int64_t g_recent_gaps[kGapWindow] = {};  // game thread
inline int g_recent_gap_count = 0;
inline void NotePresent() {
  const uint64_t frame = g_presents.load(std::memory_order_relaxed) + 1;
  if (auto* counter = g_swap_counter.load(std::memory_order_acquire)) {
    const int64_t gap = int64_t(frame - 1) - int64_t(counter());
    if (gap >= 0) {
      g_recent_gaps[g_recent_gap_count % kGapWindow] = gap;
      ++g_recent_gap_count;
      int64_t offset = INT64_MAX;
      for (int i = 0; i < std::min(g_recent_gap_count, kGapWindow); ++i) {
        offset = std::min(offset, g_recent_gaps[i]);
      }
      g_swap_offset.store(offset, std::memory_order_relaxed);
    }
  }
  g_frame_screens[frame % kScreenRing].store(g_screen.load(std::memory_order_relaxed),
                                             std::memory_order_relaxed);
  g_presents.store(frame, std::memory_order_release);
}
// The screen in the picture on show, given the frames swapped in so far. Burst
// screenshots (pause / resume, menus in and out) put it two frames behind the
// frame that set the label: one for the label to take effect, one more before
// the picture reaches the window.
inline int ScreenOnShow(uint64_t swapped) {
  constexpr uint64_t kLag = 2;
  const uint64_t presents = g_presents.load(std::memory_order_acquire);
  const int64_t offset = g_swap_offset.load(std::memory_order_relaxed);
  uint64_t shown = offset >= 0 ? swapped + uint64_t(offset) : presents;
  if (shown > presents || presents - shown > kScreenRing - 8) shown = presents;
  if (shown <= kLag) return g_screen.load(std::memory_order_relaxed);
  return g_frame_screens[(shown - kLag) % kScreenRing].load(std::memory_order_relaxed);
}

inline int ScreenFromLabel(const char* label, size_t length) {
  auto is = [&](const char* s) {
    return length == std::strlen(s) && std::memcmp(label, s, length) == 0;
  };
  if (is("Active")) return kScreenActive;
  // "Back (B)" at the panel's foot: difficulty, the tutorial list, the resume
  // prompt ("Confirm": Resume Game / New Game) and Game Options > Controls.
  if (is("DifficultySelection") || is("Tutorial") || is("Confirm") || is("Controls")) {
    return kScreenBack;
  }
  if (is("Leaderboard")) return kScreenLeaderboard;
  if (is("Splash")) return kScreenTitle;
  if (length > 6 && std::memcmp(label + length - 6, "_howto", 6) == 0) return kScreenHowTo;
  return kScreenOther;
}

// High Scores: the tab on show (0 Marathon, 1 Timed, 2 Survival); its clip
// goes to the mode's label. Left / Right change tabs.
inline std::atomic<int> g_leaderboard_tab{0};

inline void NoteLabel(uint32_t clip, uint32_t parent, const char* label, size_t length) {
  if (length == 4 && std::memcmp(label, "over", 4) == 0) {
    g_highlighted.store(clip, std::memory_order_relaxed);
  }
  if (parent != 0) {
    static const char* const kTabs[] = {"Marathon", "Timed", "Survival"};
    for (int i = 0; i < 3; ++i) {
      if (length == std::strlen(kTabs[i]) && std::memcmp(label, kTabs[i], length) == 0) {
        g_leaderboard_tab.store(i, std::memory_order_relaxed);
      }
    }
  }
  if (parent == 0) {
    g_root.store(clip, std::memory_order_relaxed);
    const bool active = length == 6 && std::memcmp(label, "Active", 6) == 0;
    const bool play = active || (length > 6 && std::memcmp(label, "Level_", 6) == 0);
    g_play.store(play, std::memory_order_relaxed);
    g_active.store(active, std::memory_order_relaxed);
    g_screen.store(ScreenFromLabel(label, length), std::memory_order_relaxed);
    g_on_main_menu.store(length == 4 && std::memcmp(label, "Menu", 4) == 0, std::memory_order_relaxed);
  }
}

// X_INPUT_GAMEPAD_* bits used here.
constexpr uint16_t kUp = 0x0001, kDown = 0x0002, kLeft = 0x0004, kRight = 0x0008,
                   kA = 0x1000, kB = 0x2000, kX = 0x4000;

class MenuMouse {
 public:
  void SetWindow(HWND window) { window_ = window; }
  void SetTrace(bool trace) { trace_ = trace; }

  // Called on every pad poll (game thread): adds buttons / left stick.
  // suspended: a PC dialog (Settings, name entry, controls) has the mouse, or
  // just closed. Nothing reaches the game then, but the pointer and button
  // states stay current, so a click made in the dialog (or the one that
  // closed it) isn't taken as a new click on the menu behind afterwards.
  void Poll(rex::memory::Memory* memory, uint16_t& buttons, int16_t& lx, int16_t& ly,
            bool suspended = false) {
    const auto now = std::chrono::steady_clock::now();
    ++poll_index_;
    if (suspended) {
      Reset();
      if (window_) ReadPointer(g_test_pointer.load());
      return;
    }
    if (trace_) {
      // How often the game reads the pad (sets how fast steps can go).
      ++polls_;
      const auto gap = now - last_poll_;
      if (last_poll_ != std::chrono::steady_clock::time_point{}) {
        min_gap_ = std::min(min_gap_, gap);
        max_gap_ = std::max(max_gap_, gap);
      }
      last_poll_ = now;
      if (now - poll_count_start_ >= std::chrono::seconds(5)) {
        using ms = std::chrono::duration<double, std::milli>;
        REXLOG_INFO("[mouse] {} pad polls in 5 s, gaps {:.1f}-{:.1f} ms", polls_,
                    ms(min_gap_).count(), ms(max_gap_).count());
        polls_ = 0;
        min_gap_ = std::chrono::hours(1);
        max_gap_ = {};
        poll_count_start_ = now;
      }
    }
    Tick(now);
    Apply(buttons, lx, ly);
    const bool test = g_test_pointer.load();
    if (!memory || (!test && (!window_ || GetForegroundWindow() != window_))) {
      Reset();
      return;
    }
    memory_ = memory;
    base_ = memory->virtual_membase();
    readable_pages_.clear();

    if (!ReadPointer(test)) return;

    if (g_play.load(std::memory_order_relaxed)) {
      menu_goal_ = 0;
      PlayPoll(now);
    } else {
      board_active_ = false;
      cursor_ = 0;
      MenuPoll(now);
    }
    Tick(now);
    Apply(buttons, lx, ly);
  }

 private:
  struct Matrix {
    float a, b, c, d, tx, ty;  // x' = a x + c y + tx, y' = b x + d y + ty (pixels)
  };
  struct Button {
    uint32_t clip;
    float x0, y0, x1, y1;  // stage pixels
    float cy() const { return (y0 + y1) * 0.5f; }
    float cx() const { return (x0 + x1) * 0.5f; }
  };
  struct DefInfo {
    bool button = false;
    bool cursor = false;
    bool has_bounds = false;
    float x0 = 0, y0 = 0, x1 = 0, y1 = 0;  // frame 1 bounds, twips
  };

  // --- pointer -----------------------------------------------------------

  // Reads the pointer into sx_ / sy_ (stage pixels), moved_, and the click
  // edges. False when there is no usable pointer.
  bool ReadPointer(bool test) {
    if (test) {
      sx_ = g_test_x.load();
      sy_ = g_test_y.load();
      inside_ = true;
      moved_ = sx_ != last_test_x_ || sy_ != last_test_y_;
      last_test_x_ = sx_;
      last_test_y_ = sy_;
      left_pressed_ = g_test_clicks.load() > 0 && g_test_clicks.fetch_sub(1) > 0;
      right_pressed_ = g_test_right_clicks.load() > 0 && g_test_right_clicks.fetch_sub(1) > 0;
      return true;
    }
    POINT cursor;
    RECT client;
    if (!GetCursorPos(&cursor) || !ScreenToClient(window_, &cursor) ||
        !GetClientRect(window_, &client) || client.right <= 0 || client.bottom <= 0) {
      return false;
    }
    inside_ = cursor.x >= 0 && cursor.y >= 0 && cursor.x < client.right && cursor.y < client.bottom;
    // Window -> stage: the 1280 x 720 picture, letterboxed.
    const float scale = std::min(client.right / 1280.0f, client.bottom / 720.0f);
    sx_ = (cursor.x - (client.right - 1280.0f * scale) * 0.5f) / scale;
    sy_ = (cursor.y - (client.bottom - 720.0f * scale) * 0.5f) / scale;
    moved_ = cursor.x != last_cursor_.x || cursor.y != last_cursor_.y;
    last_cursor_ = cursor;
    const bool swapped = GetSystemMetrics(SM_SWAPBUTTON) != 0;
    const bool left = (GetAsyncKeyState(swapped ? VK_RBUTTON : VK_LBUTTON) & 0x8000) != 0;
    const bool right = (GetAsyncKeyState(swapped ? VK_LBUTTON : VK_RBUTTON) & 0x8000) != 0;
    left_pressed_ = left && !left_was_down_ && inside_;
    right_pressed_ = right && !right_was_down_ && inside_;
    left_was_down_ = left;
    right_was_down_ = right;
    return true;
  }

  // --- menus ---------------------------------------------------------------

  void MenuPoll(std::chrono::steady_clock::time_point now) {
    // High Scores tabs (stage pixels; not clips with an "over" frame): a
    // click moves Left / Right as many tabs as it takes.
    if (g_screen.load(std::memory_order_relaxed) == kScreenLeaderboard && left_pressed_ &&
        sy_ >= 55.0f && sy_ < 112.0f && sx_ >= 228.0f && sx_ < 760.0f) {
      const int clicked = sx_ < 400.0f ? 0 : sx_ < 565.0f ? 1 : 2;
      const int shown = g_leaderboard_tab.load(std::memory_order_relaxed);
      Clear();
      for (int i = shown; i < clicked; ++i) Enqueue(kRight);
      for (int i = shown; i > clicked; --i) Enqueue(kLeft);
      return;
    }
    const uint32_t highlighted = g_highlighted.load(std::memory_order_relaxed);
    buttons_.clear();
    uint32_t root = g_root.load(std::memory_order_relaxed);
    if (root && Readable(root, 256)) {
      visited_ = 0;
      found_cursor_ = 0;
      Collect(root, Identity(), 0);
    }
    uint64_t list_hash = buttons_.size();
    for (const Button& b : buttons_) list_hash = list_hash * 1000003u + b.clip;
    if (trace_ && list_hash != logged_hash_) {
      logged_hash_ = list_hash;
      for (const Button& b : buttons_) {
        REXLOG_INFO("[mouse] button {:08X} at ({:.0f},{:.0f})-({:.0f},{:.0f})", b.clip, b.x0,
                    b.y0, b.x1, b.y1);
      }
    }
    const Button* hovered = nullptr;
    if (inside_) {
      for (const Button& b : buttons_) {
        if (sx_ >= b.x0 && sx_ < b.x1 && sy_ >= b.y0 && sy_ < b.y1) hovered = &b;
      }
    }
    if (right_pressed_) {
      Clear();
      Enqueue(kB);
      return;
    }
    if (left_pressed_) {
      if (hovered) {
        menu_goal_ = hovered->clip;
        menu_click_ = true;
        replans_ = 0;
      } else if (buttons_.size() <= 1) {
        // A screen with one action (Continue, Game Over, a tutorial card):
        // clicking anywhere does it.
        Clear();
        Enqueue(kA);
        return;
      }
    } else if (moved_ && hovered && hovered->clip != menu_goal_) {
      menu_goal_ = hovered->clip;
      menu_click_ = false;
      replans_ = 0;
    }
    if (!menu_goal_ || Busy(now)) return;

    const Button* goal = Find(menu_goal_);
    const Button* current = Find(highlighted);
    if (!goal) {
      menu_goal_ = 0;
      return;
    }
    // A row of arrows (Game Options: Pattern, SFX, Music) is highlighted as a
    // whole (both arrows go to "over"); Left / Right on the row is what its
    // arrows do, by which side of the row the clicked one is on.
    int row_left = 0, row_right = 0;
    for (const Button& b : buttons_) {
      if (b.clip == goal->clip || !SameRow(b, *goal)) continue;
      (b.cx() < goal->cx() ? row_left : row_right)++;
    }
    const bool arrow = row_left + row_right > 0;
    const bool on_row = menu_goal_ == highlighted || (current && SameRow(*goal, *current));
    if (on_row) {
      if (menu_click_) Enqueue(arrow ? (row_right > 0 ? kLeft : kRight) : kA);
      menu_goal_ = 0;
      return;
    }
    if (!current) {
      menu_goal_ = 0;
      return;
    }
    if (++replans_ > 4) {
      menu_goal_ = 0;
      return;
    }
    // How many rows away: the menus are vertical lists, one step per row.
    std::vector<float> rows;
    for (const Button& b : buttons_) {
      bool known = false;
      for (float y : rows) known |= std::abs(y - b.cy()) < (b.y1 - b.y0) * 0.5f;
      if (!known) rows.push_back(b.cy());
    }
    int steps = 0;
    const float lo = std::min(goal->cy(), current->cy()), hi = std::max(goal->cy(), current->cy());
    for (float y : rows) {
      if (y > lo + 1.0f && y <= hi + (goal->y1 - goal->y0) * 0.5f) ++steps;
    }
    steps = std::clamp(steps, 1, 16);
    const uint16_t direction = goal->cy() < current->cy() ? kUp : kDown;
    for (int i = 0; i < steps; ++i) Enqueue(direction);
  }

  // --- the board -------------------------------------------------------------

  void PlayPoll(std::chrono::steady_clock::time_point now) {
    // Find the cursor once per game (re-found if its clip goes away).
    if (!cursor_ || !Readable(cursor_, 208) || U32(cursor_ + 200) != cursor_def_) {
      cursor_ = 0;
      const uint32_t root = g_root.load(std::memory_order_relaxed);
      if (root && Readable(root, 256) && now >= next_cursor_search_) {
        next_cursor_search_ = now + std::chrono::milliseconds(250);
        visited_ = 0;
        found_cursor_ = 0;
        buttons_.clear();
        Collect(root, Identity(), 0);
        cursor_ = found_cursor_;
        cursor_def_ = found_cursor_def_;
        lattice_known_ = false;  // a new board: learn its corners again
        have_last_cursor_ = false;
        if (trace_ && cursor_) REXLOG_INFO("[mouse] board cursor clip {:08X}", cursor_);
      }
    }
    float cx, cy;
    if (!cursor_ || !WorldOrigin(cursor_, &cx, &cy)) {
      // No cursor on screen (a tutorial card, the level-up banner): clicks
      // are its A / B.
      if (left_pressed_ || right_pressed_) {
        Clear();
        Enqueue(left_pressed_ ? kA : kB);
      }
      return;
    }
    LearnLattice(cx, cy);
    if (lattice_known_) {
      LatticePoll(now, cx, cy);
      return;
    }
    // Until one move has shown where the grid's corners are: step greedily.
    if (left_pressed_ || right_pressed_) {
      board_click_ = left_pressed_ ? kA : kX;
      StartBoardGoal();
    } else if (moved_ && inside_) {
      if (board_active_) {
        // Already on the way: small moves only adjust the target (a restart
        // would forget which axis is blocked and re-plan from mid-route).
        if (std::hypot(sx_ - goal_x_, sy_ - goal_y_) < 12.0f) {
          goal_x_ = sx_;
          goal_y_ = sy_;
        } else {
          StartBoardGoal();
        }
      } else {
        // Hysteresis: the cursor's spots are a lattice (28 px rows, 32 px
        // columns), and near the border between two of them a restart on every
        // pixel of movement flips between them. Move only once the pointer is
        // clearly nearer another spot than the one the cursor is on.
        const float ex = (sx_ - cx) / 24.0f, ey = (sy_ - cy) / 20.0f;
        if (ex * ex + ey * ey > 1.0f) StartBoardGoal();
      }
    }
    if (!board_active_ || Busy(now)) return;

    const float dx = goal_x_ - cx, dy = goal_y_ - cy;
    if (trace_) {
      REXLOG_INFO("[mouse] cursor ({:.1f},{:.1f}) goal ({:.1f},{:.1f})", cx, cy, goal_x_, goal_y_);
    }
    // Progress is judged per axis: an Up / Down step zigzags 16 px sideways,
    // so the straight-line distance can grow while the vertical gap shrinks.
    // An axis that stops getting closer has reached the board's edge; the
    // other one still goes on.
    if (last_axis_gap_ < 1e9f) {
      const float gap = last_vertical_ ? std::abs(dy) : std::abs(dx);
      if (gap >= last_axis_gap_ - 0.5f) {
        (last_vertical_ ? vertical_blocked_ : horizontal_blocked_) = true;
        // A step that overshot (left / right can jump two columns) and left
        // it further away: one step back to the nearer spot, and stop there.
        if (gap > last_axis_gap_ + 0.5f) {
          Enqueue(last_vertical_ ? (dy < 0 ? kUp : kDown) : (dx < 0 ? kLeft : kRight));
          board_active_ = false;
          if (board_click_) Enqueue(board_click_);
          board_click_ = 0;
          return;
        }
      }
    }
    const bool want_vertical = std::abs(dy) >= 14.5f && !vertical_blocked_;
    const bool want_horizontal = std::abs(dx) >= 16.5f && !horizontal_blocked_;
    if ((!want_vertical && !want_horizontal) || ++replans_ > 10) {
      board_active_ = false;
      if (board_click_) Enqueue(board_click_);
      board_click_ = 0;
      return;
    }
    last_vertical_ = want_vertical;
    last_axis_gap_ = last_vertical_ ? std::abs(dy) : std::abs(dx);
    // A burst of the steps that axis needs, then a check.
    if (last_vertical_) {
      const int steps = std::clamp(int(std::lround(std::abs(dy) / 27.9f)), 1, 12);
      for (int i = 0; i < steps; ++i) Enqueue(dy < 0 ? kUp : kDown);
    } else {
      const int steps = std::clamp(int(std::lround(std::abs(dx) / 32.3f)), 1, 12);
      // Left / right can jump two columns, so go one short and let the
      // check finish it.
      for (int i = 0; i < std::max(1, steps - 1); ++i) Enqueue(dx < 0 ? kLeft : kRight);
    }
  }

  // --- the board as a lattice --------------------------------------------------
  // The cursor sits on the corners of the hex grid (hex side kSide, rows kRow
  // apart). Along a row the corners come in pairs (the ends of a hexagon's
  // flat top / bottom edge), kSide apart, pairs 2 * kSide apart; each row is
  // shifted 1.5 * kSide from the next. Numbering the corners of row k by n
  // (even n = a pair's left end, odd = its right end), each press is one fixed
  // step: Right (0, +1), Left (0, -1), Down (+1, -1), Up (-1, +1). So the
  // corner nearest the pointer is reached by an exact burst, computed once.

  static constexpr float kSide = 32.3f, kRow = 27.9f, kPeriod = 3 * kSide;
  struct Corner {
    int k = 0, n = 0;
    bool operator==(const Corner& o) const { return k == o.k && n == o.n; }
  };

  // Learns where the corners are from one recognised move of the cursor:
  // along a pair (kSide), across a hexagon (2 kSide), or up / down a slanted
  // edge (left end: x - kSide / 2, right end: x + kSide / 2).
  void LearnLattice(float cx, float cy) {
    if (lattice_known_ && !ToCorner(cx, cy, nullptr)) lattice_known_ = false;
    if (!lattice_known_ && have_last_cursor_) {
      const float ddx = cx - last_cx_, ddy = cy - last_cy_;
      auto close_to = [](float v, float want) { return std::abs(v - want) < 3.0f; };
      bool learned = true;
      if (std::abs(ddy) < 3.0f && close_to(std::abs(ddx), kSide)) {
        lattice_x_ = std::min(cx, last_cx_);
        lattice_y_ = cy;
      } else if (std::abs(ddy) < 3.0f && close_to(std::abs(ddx), 2 * kSide)) {
        lattice_x_ = std::min(cx, last_cx_) - kSide;
        lattice_y_ = cy;
      } else if (close_to(std::abs(ddy), kRow) && close_to(std::abs(ddx), kSide * 0.5f)) {
        lattice_x_ = ddx > 0 ? last_cx_ - kSide : last_cx_;
        lattice_y_ = last_cy_;
      } else {
        learned = false;
      }
      if (learned) {
        lattice_known_ = true;
        // Re-plan from scratch as a lattice move, but only when the mouse was
        // taking the cursor somewhere (or has a click pending). The move that
        // taught the grid is usually the player's own, on a controller or the
        // keys: on a new board, or after the cursor sat on a silver star (the
        // middle of a hexagon, off the grid). Re-aiming at a pointer resting
        // somewhere then dragged the cursor away from them (GitHub issue #1).
        lattice_fresh_ = board_active_ || board_click_ != 0;
        board_active_ = false;
        blocked_valid_ = false;
        if (trace_) REXLOG_INFO("[mouse] board corners from ({:.1f},{:.1f})", lattice_x_, lattice_y_);
      }
    }
    last_cx_ = cx;
    last_cy_ = cy;
    have_last_cursor_ = true;
  }

  void CornerXY(const Corner& c, float* x, float* y) const {
    const int pair = c.n >= 0 ? c.n / 2 : -((1 - c.n) / 2);  // floor(n / 2)
    *x = lattice_x_ + 1.5f * kSide * c.k + kPeriod * pair + ((c.n & 1) ? kSide : 0.0f);
    *y = lattice_y_ + kRow * c.k;
  }
  bool ToCorner(float x, float y, Corner* out) const {
    Corner c;
    c.k = int(std::lround((y - lattice_y_) / kRow));
    if (std::abs(lattice_y_ + kRow * c.k - y) > 4.0f) return false;
    const float rel = x - lattice_x_ - 1.5f * kSide * c.k;
    const int pair = int(std::floor((rel + 5.0f) / kPeriod));
    const float u = rel - kPeriod * pair;
    if (std::abs(u) < 5.0f) {
      c.n = 2 * pair;
    } else if (std::abs(u - kSide) < 5.0f) {
      c.n = 2 * pair + 1;
    } else {
      return false;
    }
    if (out) *out = c;
    return true;
  }
  Corner Nearest(float x, float y) const {
    Corner best;
    float best_d = 1e30f;
    const int k0 = int(std::lround((y - lattice_y_) / kRow));
    for (int k = k0 - 1; k <= k0 + 1; ++k) {
      const float rel = x - lattice_x_ - 1.5f * kSide * k;
      const int pair0 = int(std::floor(rel / kPeriod));
      for (int pair = pair0 - 1; pair <= pair0 + 1; ++pair) {
        for (int end = 0; end < 2; ++end) {
          const Corner c{k, 2 * pair + end};
          const float d = PointerDistance(c);
          if (d < best_d) {
            best_d = d;
            best = c;
          }
        }
      }
    }
    return best;
  }
  float PointerDistance(const Corner& c) const {
    float x, y;
    CornerXY(c, &x, &y);
    return std::hypot(x - sx_, y - sy_);
  }

  void FinishBoard() {
    if (trace_ && board_active_) {
      REXLOG_INFO("[mouse] board target reached in {} polls", poll_index_ - target_poll_);
    }
    board_active_ = false;
    if (board_click_) Enqueue(board_click_);
    board_click_ = 0;
  }

  void LatticePoll(std::chrono::steady_clock::time_point now, float cx, float cy) {
    Corner here;
    if (!ToCorner(cx, cy, &here)) return;
    const bool click = left_pressed_ || right_pressed_;
    if (click) board_click_ = left_pressed_ ? kA : kX;
    if ((moved_ && inside_) || click || lattice_fresh_) {
      lattice_fresh_ = false;
      // Hysteresis: keep the corner being headed for (or sat on) unless
      // another is clearly nearer the pointer, so a pointer resting on the
      // border between two corners doesn't flip between them.
      const Corner best = Nearest(sx_, sy_);
      if (blocked_valid_ && !(best == blocked_)) blocked_valid_ = false;
      const Corner keep = board_active_ ? target_ : here;
      if (!(best == keep) && !blocked_valid_ &&
          PointerDistance(best) + 6.0f < PointerDistance(keep)) {
        target_ = best;
        replans_ = 0;
        target_poll_ = poll_index_;
        if (board_active_ && Busy(now)) {
          // Mid-move: re-plan the rest at once from where the presses already
          // sent will leave the cursor, rather than finishing the old route.
          DropQueuedMoves();
          PlanBoard(predicted_, cx, cy);
          return;
        }
        board_active_ = true;
      }
      if (board_click_ && !board_active_) FinishBoard();
    }
    if (!board_active_ || Busy(now)) return;
    predicted_ = here;
    if (here == target_) {
      FinishBoard();
      return;
    }
    // A plan that left the cursor where it was: the target is off the
    // board's playable corners. Stay, and don't try it again.
    if ((replans_ > 0 && here == plan_start_) || replans_ >= 3) {
      blocked_ = target_;
      blocked_valid_ = true;
      FinishBoard();
      return;
    }
    ++replans_;
    plan_start_ = here;
    PlanBoard(here, cx, cy);
  }

  // Queues the presses from corner `from` to target_.
  void PlanBoard(const Corner& from, float cx, float cy) {
    const int dk = target_.k - from.k;           // Down (+1, -1) / Up (-1, +1) presses
    const int dh = (target_.n - from.n) + dk;    // Right (0, +1) / Left (0, -1) presses
    const int v = std::abs(dk), h = std::abs(dh);
    if (trace_) {
      REXLOG_INFO("[mouse] cursor ({:.1f},{:.1f}) corner {},{} -> {},{}: {} vertical, {} horizontal",
                  cx, cy, from.k, from.n, target_.k, target_.n, dk, dh);
    }
    // Interleaved, so the route keeps near the straight line (inside the board).
    int done_v = 0, done_h = 0;
    while (done_v < v || done_h < h) {
      if (done_h >= h || (done_v < v && done_v * h <= done_h * v)) {
        Enqueue(dk > 0 ? kDown : kUp);
        ++done_v;
      } else {
        Enqueue(dh > 0 ? kRight : kLeft);
        ++done_h;
      }
    }
  }

  void StartBoardGoal() {
    goal_x_ = sx_;
    goal_y_ = sy_;
    board_active_ = true;
    replans_ = 0;
    last_vertical_ = true;
    last_axis_gap_ = 1e9f;
    vertical_blocked_ = horizontal_blocked_ = false;
  }

  // --- pulses ----------------------------------------------------------------
  // Counted in pad polls: the game reads the pad once a frame (60 a second,
  // 14-19 ms apart), so a pulse timed in milliseconds was often held over two
  // reads, wasting a frame. A direction lasts one poll, alternating between
  // the D-pad and the left stick so each is a fresh press; a button lasts two.
  // After the queue empties, one more poll lets the game's move show.

  static bool IsDirection(uint16_t action) { return action <= kRight; }

  void Enqueue(uint16_t action) { queue_.push_back(action); }
  // Drops the queued (not yet sent) moves, keeping any button press.
  void DropQueuedMoves() {
    queue_.erase(std::remove_if(queue_.begin(), queue_.end(), IsDirection), queue_.end());
  }
  void Clear() {
    queue_.clear();
    menu_goal_ = 0;
    board_active_ = false;
    board_click_ = 0;
  }
  void Reset() {
    Clear();
    current_ = 0;
  }
  bool Busy(std::chrono::steady_clock::time_point) const {
    return !queue_.empty() || poll_index_ < slot_end_ || poll_index_ < settle_end_;
  }

  void Tick(std::chrono::steady_clock::time_point) {
    if (poll_index_ < slot_end_) return;
    current_ = 0;
    if (queue_.empty()) return;
    current_ = queue_.front();
    queue_.pop_front();
    if (IsDirection(current_)) {
      use_stick_ = !use_stick_;
      slot_end_ = poll_index_ + 1;
      // Where the board cursor will be once this press lands.
      if (current_ == kRight) predicted_.n += 1;
      if (current_ == kLeft) predicted_.n -= 1;
      if (current_ == kDown) predicted_.k += 1, predicted_.n -= 1;
      if (current_ == kUp) predicted_.k -= 1, predicted_.n += 1;
    } else {
      use_stick_ = false;
      slot_end_ = poll_index_ + 2;
    }
    if (queue_.empty()) settle_end_ = slot_end_ + 1;
  }

  void Apply(uint16_t& buttons, int16_t& lx, int16_t& ly) const {
    if (!current_) return;
    if (IsDirection(current_) && use_stick_) {
      if (current_ == kUp) ly = 32767;
      if (current_ == kDown) ly = -32767;
      if (current_ == kLeft) lx = -32767;
      if (current_ == kRight) lx = 32767;
    } else {
      buttons |= current_;
    }
  }

  // --- guest reads -----------------------------------------------------------

  bool Readable(uint32_t address, uint32_t length) {
    if (address < 0x40000000u || address >= 0xC0000000u) return false;
    for (uint32_t page = address >> 12; page <= (address + length - 1) >> 12; ++page) {
      auto it = readable_pages_.find(page);
      if (it == readable_pages_.end()) {
        bool ok = false;
        if (auto* heap = memory_->LookupHeap(page << 12)) {
          uint32_t protect = 0;
          ok = heap->QueryProtect(page << 12, &protect) &&
               (protect & rex::memory::kMemoryProtectRead);
        }
        it = readable_pages_.emplace(page, ok).first;
      }
      if (!it->second) return false;
    }
    return true;
  }
  uint32_t U32(uint32_t address) {
    if (!Readable(address, 4)) return 0;
    const uint8_t* p = base_ + address;
    return uint32_t(p[0]) << 24 | uint32_t(p[1]) << 16 | uint32_t(p[2]) << 8 | p[3];
  }
  float F32(uint32_t address) {
    const uint32_t bits = U32(address);
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
  }
  int16_t S16(uint32_t address) {
    if (!Readable(address, 2)) return 0;
    const uint8_t* p = base_ + address;
    return int16_t(uint16_t(p[0]) << 8 | p[1]);
  }

  static Matrix Identity() { return {1, 0, 0, 1, 0, 0}; }
  static Matrix Multiply(const Matrix& p, const Matrix& l) {  // p after l
    return {p.a * l.a + p.c * l.b, p.b * l.a + p.d * l.b, p.a * l.c + p.c * l.d,
            p.b * l.c + p.d * l.d, p.a * l.tx + p.c * l.ty + p.tx,
            p.b * l.tx + p.d * l.ty + p.ty};
  }
  // Matrix at `at` in the clip / place record layout (a, b, tx, d, c, ty).
  Matrix ReadMatrix(uint32_t at) {
    return {F32(at), F32(at + 4), F32(at + 16), F32(at + 12),
            int32_t(U32(at + 8)) / 20.0f, int32_t(U32(at + 20)) / 20.0f};
  }

  // A smaller button level with a bigger one, e.g. an arrow on its row.
  static bool SameRow(const Button& a, const Button& b) {
    const float dy = std::abs(a.cy() - b.cy());
    const float half = std::max(a.y1 - a.y0, b.y1 - b.y0) * 0.5f;
    return dy < half;
  }
  const Button* Find(uint32_t clip) const {
    for (const Button& b : buttons_) {
      if (b.clip == clip) return &b;
    }
    return nullptr;
  }

  // A sprite definition's first word points a little way into itself (its
  // inline storage: +0x40, +0x80, ...), and +4 / +8 bound its frame list.
  bool IsSpriteDef(uint32_t def) {
    if (!def || !Readable(def, 32)) return false;
    const uint32_t inline_at = U32(def);
    const uint32_t frames = U32(def + 4), frames_end = U32(def + 8);
    return inline_at > def && inline_at - def <= 0x200 && (inline_at & 3) == 0 && frames &&
           frames_end >= frames && frames_end - frames <= 4 * 1024;
  }

  // Whether a sprite definition has a frame label (its label map, a std::map).
  bool HasLabel(uint32_t def, const char* label) {
    const uint32_t length = uint32_t(std::strlen(label));
    const uint32_t header = U32(def + 24);
    if (!header) return false;
    uint32_t stack[64];
    int top = 0;
    stack[top++] = U32(header + 4);  // the root node
    for (int visited = 0; top > 0 && visited < 64; ++visited) {
      const uint32_t node = stack[--top];
      if (!node || node == header || !Readable(node, 16)) continue;
      const uint32_t key = U32(node + 12);
      if (key && Readable(key, 8 + length) && U32(key + 4) == length &&
          std::memcmp(base_ + key + 8, label, length) == 0) {
        return true;
      }
      if (top < 62) {
        stack[top++] = U32(node + 0);
        stack[top++] = U32(node + 8);
      }
    }
    return false;
  }

  // Frame-1 bounds of a definition, in its own twips.
  bool Bounds(uint32_t def, int depth, float* x0, float* y0, float* x1, float* y1) {
    const uint32_t vtable = U32(def);
    if (vtable == 0x9203A788u || vtable == 0x92003F20u) {
      *x0 = S16(def + 4);
      *x1 = S16(def + 6);
      *y0 = S16(def + 8);
      *y1 = S16(def + 10);
      return *x1 > *x0 && *y1 > *y0;
    }
    if (depth > 4 || !IsSpriteDef(def)) return false;
    const uint32_t frame = U32(U32(def + 4));
    if (!frame) return false;
    const uint32_t begin = U32(frame + 4), end = U32(frame + 8);
    if (!begin || end < begin || end - begin > 4 * 256) return false;
    bool any = false;
    for (uint32_t slot = begin; slot < end; slot += 4) {
      const uint32_t record = U32(slot);
      if (!record || !Readable(record, 32)) continue;
      float cx0, cy0, cx1, cy1;
      if (!Bounds(U32(record + 4), depth + 1, &cx0, &cy0, &cx1, &cy1)) continue;
      Matrix m = ReadMatrix(record + 8);
      m.tx *= 20.0f;  // keep twips here
      m.ty *= 20.0f;
      const float xs[2] = {cx0, cx1}, ys[2] = {cy0, cy1};
      for (float x : xs) {
        for (float y : ys) {
          const float tx = m.a * x + m.c * y + m.tx, ty = m.b * x + m.d * y + m.ty;
          if (!any) {
            *x0 = *x1 = tx;
            *y0 = *y1 = ty;
            any = true;
          } else {
            *x0 = std::min(*x0, tx);
            *x1 = std::max(*x1, tx);
            *y0 = std::min(*y0, ty);
            *y1 = std::max(*y1, ty);
          }
        }
      }
    }
    return any;
  }

  const DefInfo& Info(uint32_t def) {
    auto it = defs_.find(def);
    if (it != defs_.end()) return it->second;
    DefInfo info;
    if (IsSpriteDef(def)) {
      if (HasLabel(def, "over")) {
        info.button = true;
        info.has_bounds = Bounds(def, 0, &info.x0, &info.y0, &info.x1, &info.y1);
      }
      info.cursor = HasLabel(def, "PearlUp") && HasLabel(def, "Flower");
    }
    return defs_.emplace(def, info).first->second;
  }

  void Collect(uint32_t clip, const Matrix& parent, int depth) {
    if (depth > 8 || ++visited_ > 3000 || !Readable(clip, 208)) return;
    if (!(base_[clip + 136])) return;  // _visible false: nothing under it shows
    const Matrix world = Multiply(parent, ReadMatrix(clip + 76));
    const uint32_t def = U32(clip + 200);
    const DefInfo& info = Info(def);
    if (info.cursor && !found_cursor_) {
      found_cursor_ = clip;
      found_cursor_def_ = def;
    }
    if (info.button && info.has_bounds) {
      const float xs[2] = {info.x0 / 20.0f, info.x1 / 20.0f};
      const float ys[2] = {info.y0 / 20.0f, info.y1 / 20.0f};
      Button b{clip, 1e9f, 1e9f, -1e9f, -1e9f};
      for (float x : xs) {
        for (float y : ys) {
          const float tx = world.a * x + world.c * y + world.tx;
          const float ty = world.b * x + world.d * y + world.ty;
          b.x0 = std::min(b.x0, tx);
          b.x1 = std::max(b.x1, tx);
          b.y0 = std::min(b.y0, ty);
          b.y1 = std::max(b.y1, ty);
        }
      }
      buttons_.push_back(b);
      return;  // a button's own children are its pieces
    }
    for (uint32_t list : {144u, 172u}) {
      const uint32_t begin = U32(clip + list), end = U32(clip + list + 4);
      if (!begin || end < begin || end - begin > 4 * 4096) continue;
      for (uint32_t slot = begin; slot < end; slot += 4) {
        const uint32_t entry = U32(slot);
        if (!entry) continue;
        const uint32_t child = U32(entry);
        // Movie clips only: their parent is this clip.
        if (child && Readable(child, 208) && U32(child + 196) == clip) {
          Collect(child, world, depth + 1);
        }
      }
    }
  }

  // A clip's position on the stage: its matrices up through its parents.
  bool WorldOrigin(uint32_t clip, float* x, float* y) {
    uint32_t chain[16];
    int n = 0;
    for (uint32_t c = clip; c && n < 16; c = U32(c + 196)) {
      if (!Readable(c, 208)) return false;
      chain[n++] = c;
    }
    Matrix world = Identity();
    for (int i = n - 1; i >= 0; --i) world = Multiply(world, ReadMatrix(chain[i] + 76));
    *x = world.tx;
    *y = world.ty;
    return true;
  }

  HWND window_ = nullptr;
  bool trace_ = false;
  rex::memory::Memory* memory_ = nullptr;
  uint8_t* base_ = nullptr;
  std::unordered_map<uint32_t, bool> readable_pages_;
  std::unordered_map<uint32_t, DefInfo> defs_;
  std::vector<Button> buttons_;
  int visited_ = 0;
  uint64_t logged_hash_ = 0;

  // Pointer.
  float sx_ = 0, sy_ = 0;
  bool inside_ = false, moved_ = false, left_pressed_ = false, right_pressed_ = false;
  POINT last_cursor_{-1, -1};
  float last_test_x_ = -1, last_test_y_ = -1;
  bool left_was_down_ = false, right_was_down_ = false;

  // Menus.
  uint32_t menu_goal_ = 0;
  bool menu_click_ = false;
  int replans_ = 0;

  // Board.
  uint32_t found_cursor_ = 0, found_cursor_def_ = 0;  // set by Collect
  uint32_t cursor_ = 0, cursor_def_ = 0;              // cached board cursor
  std::chrono::steady_clock::time_point next_cursor_search_{};
  bool board_active_ = false;
  uint16_t board_click_ = 0;
  // Trace: pad poll rate.
  int polls_ = 0;
  std::chrono::steady_clock::time_point last_poll_{}, poll_count_start_{};
  std::chrono::steady_clock::duration min_gap_ = std::chrono::hours(1), max_gap_{};
  // The board's corners (see LatticePoll).
  bool lattice_known_ = false, lattice_fresh_ = false;
  float lattice_x_ = 0, lattice_y_ = 0;  // a pair's left end
  bool have_last_cursor_ = false;
  float last_cx_ = 0, last_cy_ = 0;
  Corner target_, plan_start_, blocked_;
  Corner predicted_;  // where the presses sent so far leave the cursor
  uint64_t target_poll_ = 0;  // trace: when the current target was set
  bool blocked_valid_ = false;
  float goal_x_ = 0, goal_y_ = 0;
  bool last_vertical_ = true;
  float last_axis_gap_ = 1e9f;
  bool vertical_blocked_ = false, horizontal_blocked_ = false;

  // Pulses.
  std::deque<uint16_t> queue_;
  uint16_t current_ = 0;
  bool use_stick_ = false;
  uint64_t poll_index_ = 0, slot_end_ = 0, settle_end_ = 0;  // in pad polls
};

}  // namespace hexic_mouse
