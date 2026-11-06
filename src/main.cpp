// hexic_hd - ReXGlue Recompiled Project

#include "generated/default/hexic_hd_init.h"

#include "hexic_hd_app.h"

#include <rex/diag_timing.h>

REXCVAR_DEFINE_INT32(hexic_controls_version, 0, "Hexic",
                     "Keyboard defaults already applied to this config (0 = none yet)");

// Menu research (test only): log every gotoAndStop/gotoAndPlay with a frame
// label in the menus' Flash player. sub_92074078(clip, label) looks the label
// up in the clip's label table and jumps there (sub_92089988); a button's
// highlight is gotoAndStop("over").
REXCVAR_DEFINE_BOOL(hexic_menu_trace, false, "Hexic", "Test-only: log menu frame-label jumps");

namespace {
uint32_t GuestU32(const uint8_t* base, uint32_t address) {
  const uint8_t* p = base + address;
  return uint32_t(p[0]) << 24 | uint32_t(p[1]) << 16 | uint32_t(p[2]) << 8 | p[3];
}
// A player string: [refcount][length][text]. Empty if it doesn't look like one.
std::string GuestString(const uint8_t* base, uint32_t object) {
  if (object < 0x40000000u || object >= 0xC0000000u) return {};
  const uint32_t length = GuestU32(base, object + 4);
  if (length == 0 || length > 64) return {};
  return std::string(reinterpret_cast<const char*>(base + object + 8), length);
}
}  // namespace

// Also how the menu mouse learns which button is highlighted (hexic_mouse.h).
extern "C" REX_FUNC(sub_92074078) {
  const uint32_t clip = ctx.r3.u32;
  const uint32_t holder = ctx.r4.u32;
  const uint32_t object = holder ? GuestU32(base, holder) : 0;
  const std::string label = GuestString(base, object);
  hexic_mouse::NoteLabel(clip, clip ? GuestU32(base, clip + 196) : 1, label.data(),
                         label.size());
  if (REXCVAR_GET(hexic_menu_trace)) {
    REXLOG_INFO("[menu] goto clip {:08X} label \"{}\" (holder {:08X} -> {:08X})", clip, label,
                holder, object);
  }
  __imp__sub_92074078(ctx, base);
}

// CPU use in GPU waits. The Xbox D3D library waits for the GPU by polling: its
// fence waits (four of them) loop on sub_920AA8E8, which checks for a GPU hang
// and returns 1 while still waiting. On the Xbox 360 that shared a core with
// other hardware threads; on a PC it burned a whole core (measured: the main
// thread at 99.6% on the title screen). Now, in the still-waiting path
// (generated/default/hexic_hd_recomp.2.cpp, a hand edit), the first 0.5 ms of
// a wait yields and after that each poll sleeps 0.5 ms on a high-resolution
// timer. Ported from the Perfect Dark port (PdGpuWaitBackoff, HANDOVER 4ah).
REXCVAR_DEFINE_BOOL(hexic_sleep_in_waits, true, "Hexic",
                    "Let the game's GPU waits sleep in 0.5 ms steps instead of spinning a CPU "
                    "core");

namespace {
void SleepHalfMillisecond() {
  struct Timer {
    HANDLE handle = CreateWaitableTimerExW(nullptr, nullptr,
                                           0x00000002 /* CREATE_WAITABLE_TIMER_HIGH_RESOLUTION */,
                                           TIMER_ALL_ACCESS);
    ~Timer() {
      if (handle) CloseHandle(handle);
    }
  };
  thread_local Timer timer;
  LARGE_INTEGER due;
  due.QuadPart = -5000;  // 0.5 ms, relative, in 100 ns units
  if (timer.handle && SetWaitableTimer(timer.handle, &due, 0, nullptr, nullptr, FALSE)) {
    WaitForSingleObject(timer.handle, INFINITE);
  } else {
    SwitchToThread();
  }
}
}  // namespace

void HexicGpuWaitBackoff() {
  if (!REXCVAR_GET(hexic_sleep_in_waits)) return;
  thread_local int64_t wait_start = 0;
  thread_local int64_t last_poll = 0;
  static const int64_t freq = [] {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return f.QuadPart;
  }();
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  // Polls within one wait come microseconds apart; a gap over 2 ms means a new wait.
  if (now.QuadPart - last_poll > freq / 500) wait_start = now.QuadPart;
  if (now.QuadPart - wait_start < freq / 2000) {
    SwitchToThread();
  } else {
    SleepHalfMillisecond();
  }
  QueryPerformanceCounter(&now);
  last_poll = now.QuadPart;
}

// Game steps in the timing log (vblank_timing_log). Hexic's game time is the
// kernel's millisecond tick count (KeTimeStampBundle.TickCount, read by
// sub_92056528), so the game moves on by however many milliseconds that tick
// moved since the last frame. Called from the D3D present routine
// (generated/default/hexic_hd_recomp.11.cpp sub_921B5218, a hand edit), once
// per frame on the game thread. Every 10 s: game time against real time, and
// frames whose game step disagrees with the real frame time - a frame that
// stepped the game two frames' worth while under 20 ms of real time passed is
// a jump forward on screen (a "double step"). Also times the keycap overlay's
// screen changes to the frames (hexic_mouse::NotePresent).
void HexicNoteGameFrame(uint8_t* base) {
  hexic_mouse::NotePresent();
  if (!rex::diag::TimingLogOn()) return;
  constexpr uint32_t kTimeStampBundleSlot = 0x9200052C;  // import variable: pointer to the bundle
  const uint32_t bundle =
      _byteswap_ulong(*reinterpret_cast<const uint32_t*>(base + kTimeStampBundleSlot));
  if (!bundle) return;
  const uint32_t tick = _byteswap_ulong(*reinterpret_cast<const uint32_t*>(base + bundle + 16));
  static const int64_t freq = [] {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return f.QuadPart;
  }();
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  static int64_t window_start = 0, last_frame = 0, window_real_start = 0;
  static uint32_t last_tick = 0, window_tick_start = 0;
  static uint64_t frames = 0, doubles = 0, mismatches = 0, zero_steps = 0;
  static uint32_t most = 0;
  static double sum = 0.0, sq = 0.0;
  if (last_frame && now.QuadPart - last_frame < freq) {
    const double real_ms = double(now.QuadPart - last_frame) * 1000.0 / double(freq);
    const uint32_t game_ms = tick - last_tick;
    ++frames;
    sum += game_ms;
    sq += double(game_ms) * game_ms;
    most = std::max(most, game_ms);
    if (game_ms == 0) ++zero_steps;
    if (game_ms >= 25 && real_ms < 20.0) ++doubles;
    if (std::fabs(double(game_ms) - real_ms) > 3.0) ++mismatches;
  } else {
    window_start = 0;
  }
  last_frame = now.QuadPart;
  last_tick = tick;
  if (!window_start) {
    window_start = window_real_start = now.QuadPart;
    window_tick_start = tick;
    frames = doubles = mismatches = zero_steps = 0;
    most = 0;
    sum = sq = 0.0;
    return;
  }
  if (now.QuadPart - window_start >= 10 * freq && frames) {
    const double seconds = double(now.QuadPart - window_real_start) / double(freq);
    const double mean = sum / double(frames);
    REXLOG_INFO("[timing] game steps: {} frames, game time {:.3f}% of real time, game ms per "
                "frame mean {:.2f} sd {:.2f} most {}; {} double steps (25+ ms of game time in a "
                "frame under 20 ms), {} frames off real time by over 3 ms, {} frames with no "
                "game time",
                frames, double(tick - window_tick_start) / (seconds * 1000.0) * 100.0, mean,
                std::sqrt(std::max(0.0, sq / double(frames) - mean * mean)), most, doubles,
                mismatches, zero_steps);
    window_start = window_real_start = now.QuadPart;
    window_tick_start = tick;
    frames = doubles = mismatches = zero_steps = 0;
    most = 0;
    sum = sq = 0.0;
  }
}

REX_DEFINE_APP(hexic_hd, HexicHdApp::Create)
