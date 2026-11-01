// Hexic HD PC - the setup window.
//
// The Hexic HD title screen, rebuilt from primitives (no game artwork): a black
// field of slate hexagons, a pearl-silver bezel, a dark card with a violet glow,
// an indigo honeycomb strip carrying a cyan SCORE-style step bar, and a
// white-to-periwinkle panel. Jewel hexagons in the game's piece colours stand
// in for checkboxes and decoration. One page: the package line (Browse package
// or drag and drop), the import progress, the optional extras and Play.
//
// Everything is painted with GDI+ in 96-DPI layout units and scaled for the
// monitor's DPI, so the window stays sharp at any Windows scaling. The parts
// that never change are drawn once into a bitmap at the real pixel size.
#include <algorithm>
namespace Gdiplus {
using std::max;
using std::min;
}  // namespace Gdiplus

#include "launcher.h"

#include <objidl.h>
#include <gdiplus.h>
#include <shellapi.h>
#include <windowsx.h>
#include <shobjidl.h>

#include <cmath>
#include <memory>
#include <thread>

#include "resource.h"

namespace hexic {
namespace {

using namespace Gdiplus;

// ------------------------------------------------------------- layout --
constexpr float kW = 720, kH = 600;
constexpr float kUiScale = 1.0f;

struct Box {
  float x, y, w, h, r;
};
constexpr Box kBezel = {44, 12, 632, 576, 34};
constexpr Box kCard = {62, 92, 596, 480, 28};
constexpr Box kPill = {90, 109, 540, 28, 14};
constexpr Box kPanel = {74, 152, 572, 408, 20};
constexpr Box kField = {98, 252, 380, 34, 7};
constexpr Box kBar = {98, 356, 524, 12, 6};
constexpr float kRowsY = 250, kRowPitch = 30;  // candidate rows when several packages are found
constexpr int kMaxRows = 4;
constexpr float kExtrasY = 402, kExtraFirst = 426, kExtraPitch = 42;

enum Control { kNone = -1, kBrowse, kLeft, kPlay, kExtra0, kExtra1, kRow0 };

enum class Mode { Idle, Choosing, Importing, Ready };

constexpr UINT WM_APP_START = WM_APP + 1;
constexpr UINT WM_APP_PROGRESS = WM_APP + 2;
constexpr UINT WM_APP_DONE = WM_APP + 3;

const wchar_t* const kClassName = L"HexicHDSetup";
const wchar_t kDot[] = L"·";
const wchar_t kEllipsis[] = L"…";

Color Hex(uint32_t rgb, BYTE alpha = 255) { return Color(alpha, (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF); }

Color Mix(uint32_t a, uint32_t b, double t) {
  auto channel = [&](int shift) {
    const double ca = (a >> shift) & 0xFF, cb = (b >> shift) & 0xFF;
    return static_cast<BYTE>(ca + (cb - ca) * t);
  };
  return Color(255, channel(16), channel(8), channel(0));
}

namespace pal {
const uint32_t Ink = 0x15132E, Soft = 0x2E2C4E, Muted = 0x55537A, Violet = 0x5B3FD6, Cyan = 0x22D4F0,
               CyanDeep = 0x0C5E96, Ok = 0x1B7F36, Bad = 0xC42837;
const uint32_t Jewels[6] = {0xE8303A, 0xF59A1E, 0xF5D73A, 0x3CC84A, 0x2E7CF0, 0x9A3FE0};
}  // namespace pal

struct ProgressMsg {
  int percent;
  std::wstring phase, detail;
};

struct RectL {
  float x, y, w, h;
  bool Contains(float px, float py) const { return px >= x && px < x + w && py >= y && py < y + h; }
};

struct ExtraDef {
  const wchar_t* title;
  const wchar_t* detail;
};
const ExtraDef kExtraDefs[2] = {
    {L"Start in fullscreen", L"Switch at any time from Settings on the main menu."},
    {L"Create desktop shortcut", L"Adds a Hexic HD icon to your desktop that opens this folder's game."},
};

// ------------------------------------------------------------ helpers --
void RoundedPath(GraphicsPath& path, float x, float y, float w, float h, float r) {
  const float d = std::max(1.0f, std::min(r * 2, std::min(w, h)));
  path.AddArc(x, y, d, d, 180, 90);
  path.AddArc(x + w - d, y, d, d, 270, 90);
  path.AddArc(x + w - d, y + h - d, d, d, 0, 90);
  path.AddArc(x, y + h - d, d, d, 90, 90);
  path.CloseFigure();
}

// Pointy-top hexagon, like the game's pieces.
void HexPath(GraphicsPath& path, double cx, double cy, double r) {
  PointF points[6];
  for (int i = 0; i < 6; ++i) {
    const double a = 3.14159265358979323846 / 180 * (60 * i - 90);
    points[i] = PointF(static_cast<REAL>(cx + r * std::cos(a)), static_cast<REAL>(cy + r * std::sin(a)));
  }
  path.AddPolygon(points, 6);
}

// Multi-stop gradient. The rectangle is padded by a pixel because GDI+ wraps
// the first colour onto the last row otherwise.
std::unique_ptr<LinearGradientBrush> Blend(double x, double y, double w, double h, std::vector<Color> colors,
                                           std::vector<REAL> positions, REAL angle = 90) {
  const RectF rect(static_cast<REAL>(x - 1), static_cast<REAL>(y - 1), static_cast<REAL>(w + 2), static_cast<REAL>(h + 2));
  auto brush = std::make_unique<LinearGradientBrush>(rect, colors.front(), colors.back(), angle);
  brush->SetInterpolationColors(colors.data(), positions.data(), static_cast<INT>(colors.size()));
  return brush;
}

void PaintJewel(Graphics& g, double cx, double cy, double r, uint32_t color) {
  GraphicsPath path;
  HexPath(path, cx, cy, r);
  auto fill = Blend(cx - r, cy - r, r * 2, r * 2, {Mix(color, 0xFFFFFF, 0.5), Hex(color), Mix(color, 0x000000, 0.45)}, {0, 0.5f, 1});
  g.FillPath(fill.get(), &path);
  GraphicsPath gloss;
  HexPath(gloss, cx, cy - r * 0.3, r * 0.6);
  LinearGradientBrush shine(RectF(static_cast<REAL>(cx - r), static_cast<REAL>(cy - r), static_cast<REAL>(r * 2), static_cast<REAL>(r * 1.1)),
                            Hex(0xFFFFFF, 170), Hex(0xFFFFFF, 0), 90.0f);
  g.FillPath(&shine, &gloss);
  Pen pen(Mix(color, 0x000000, 0.6), static_cast<REAL>(std::max(1.0, r / 10)));
  g.DrawPath(&pen, &path);
}

void DrawTick(Graphics& g, float cx, float cy, float size, Color color, float width) {
  Pen tick(color, width);
  tick.SetStartCap(LineCapRound);
  tick.SetEndCap(LineCapRound);
  tick.SetLineJoin(LineJoinRound);
  const PointF points[3] = {PointF(cx - size * 0.45f, cy + size * 0.02f), PointF(cx - size * 0.1f, cy + size * 0.38f),
                            PointF(cx + size * 0.5f, cy - size * 0.38f)};
  g.DrawLines(&tick, points, 3);
}

// Fonts: the first installed family wins (GDI+ would silently substitute).
std::unique_ptr<FontFamily> FirstFamily(std::initializer_list<const wchar_t*> names) {
  for (const wchar_t* name : names) {
    auto family = std::make_unique<FontFamily>(name);
    if (family->IsAvailable()) return family;
  }
  return std::make_unique<FontFamily>(L"Segoe UI");
}

// Fonts are sized in 96-DPI pixels (points * 96 / 72); the paint transform scales them.
std::unique_ptr<Font> MakePoints(const wchar_t* family, float points, int style) {
  FontFamily f(family);
  return std::make_unique<Font>(&f, points * 96.0f / 72.0f, style, UnitPixel);
}

class SetupWindow {
 public:
  SetupWindow(const Paths& p, const SetupOptions& o) : p_(p), options_(o) {}
  int Run(HINSTANCE instance);

 private:
  static LRESULT CALLBACK Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
  LRESULT Handle(UINT msg, WPARAM wp, LPARAM lp);

  void CreateFonts();
  void ApplyScale(UINT dpi, const RECT* suggested);
  void BuildBackdrop();
  void DrawLogo(Graphics& g, float x, float bottom);
  void Paint(HDC dc);
  void PaintButton(Graphics& g, Control id, const wchar_t* text, bool enabled, bool primary, Font* font);
  void PaintGlow(Graphics& g, double x, double y, double w, double h, double fraction);
  void PaintText(Graphics& g, const std::wstring& text, Font* font, uint32_t color, RectF rect,
                 StringAlignment align = StringAlignmentNear, bool wrap = false, bool is_path = false);

  RectL ControlRect(Control id) const;
  bool Enabled(Control id) const;
  Control HitTest(float x, float y) const;
  void Click(Control id);

  void Start();
  void Browse();
  void SelectPath(const fs::path& path);
  void StartImport(Source source);  // by value: it may come from candidates_, which is cleared
  void OnProgress(ProgressMsg* msg);
  void OnDone(ImportResult* result);
  void Play();
  void RequestClose();
  void Invalidate() { InvalidateRect(hwnd_, nullptr, FALSE); }

  const Paths& p_;
  SetupOptions options_;
  HWND hwnd_ = nullptr;
  HICON icon_ = nullptr;
  float scale_ = 1;
  Mode mode_ = Mode::Idle;
  bool installed_ = false;
  bool imported_now_ = false;
  bool close_after_import_ = false;
  std::vector<Source> candidates_;
  std::wstring heading_, hint_, path_text_, status_, phase_, stats_, detail_;
  uint32_t status_color_ = pal::Muted, phase_color_ = pal::Violet;
  bool path_set_ = false;
  int progress_ = 0;
  bool show_bar_ = false;
  Extras want_, was_;
  Control hover_ = kNone, pressed_ = kNone;
  bool tracking_ = false;
  std::atomic<bool> cancel_{false};
  std::thread worker_;
  std::unique_ptr<Bitmap> backdrop_;
  std::unique_ptr<FontFamily> logo_family_, hd_family_;
  std::unique_ptr<Font> title_, caps_, body_, small_, foot_, button_, play_, row_title_, row_detail_, tag_, pill_;
};

void SetupWindow::CreateFonts() {
  logo_family_ = FirstFamily({L"Bahnschrift Condensed", L"Bahnschrift SemiLight Condensed", L"Arial Narrow", L"Segoe UI Light"});
  hd_family_ = FirstFamily({L"Bahnschrift SemiBold Condensed", L"Bahnschrift SemiBold", L"Segoe UI Black"});
  title_ = MakePoints(L"Segoe UI Semibold", 15, FontStyleRegular);
  caps_ = MakePoints(L"Segoe UI Semibold", 8.25f, FontStyleRegular);
  body_ = MakePoints(L"Segoe UI", 10, FontStyleRegular);
  small_ = MakePoints(L"Segoe UI", 9, FontStyleRegular);
  foot_ = MakePoints(L"Segoe UI", 8, FontStyleRegular);
  button_ = MakePoints(L"Segoe UI Semibold", 10, FontStyleRegular);
  play_ = MakePoints(L"Segoe UI Semibold", 13, FontStyleRegular);
  row_title_ = MakePoints(L"Segoe UI Semibold", 10, FontStyleRegular);
  row_detail_ = MakePoints(L"Segoe UI", 8.5f, FontStyleRegular);
  tag_ = MakePoints(L"Segoe UI Semibold", 8.5f, FontStyleRegular);
  pill_ = MakePoints(L"Segoe UI Semibold", 8.5f, FontStyleRegular);
}

// --------------------------------------------------------------- scale --
// The layout scale for a monitor: its DPI, reduced when the window would not
// fit the monitor's work area (small laptop screens).
void SetupWindow::ApplyScale(UINT dpi, const RECT* suggested) {
  HMONITOR monitor = suggested ? MonitorFromRect(suggested, MONITOR_DEFAULTTONEAREST)
                               : (hwnd_ ? MonitorFromWindow(hwnd_, MONITOR_DEFAULTTONEAREST)
                                        : MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY));
  MONITORINFO info = {sizeof(info)};
  GetMonitorInfoW(monitor, &info);
  const RECT work = info.rcWork;
  const float base = dpi / 96.0f;
  const float fit = std::min((work.right - work.left) * 0.95f / kW, (work.bottom - work.top) * 0.95f / kH);
  scale_ = std::max(0.5f, std::min(base * kUiScale, fit));
  const int w = static_cast<int>(kW * scale_ + 0.5f), h = static_cast<int>(kH * scale_ + 0.5f);
  int x, y;
  if (suggested) {
    x = suggested->left;
    y = suggested->top;
  } else {
    x = work.left + ((work.right - work.left) - w) / 2;
    y = work.top + ((work.bottom - work.top) - h) / 2;
  }
  SetWindowPos(hwnd_, nullptr, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
  const int r = static_cast<int>(18 * scale_);
  SetWindowRgn(hwnd_, CreateRoundRectRgn(0, 0, w + 1, h + 1, r * 2, r * 2), TRUE);
  BuildBackdrop();
  Invalidate();
}

// -------------------------------------------------------------- backdrop --
// "HEXIC" in black chrome with a violet edge light and a tall centre X, and a
// cyan "HD" tucked in after it - drawn as outlines from a system font.
void SetupWindow::DrawLogo(Graphics& g, float x, float bottom) {
  GraphicsPath logo;
  const StringFormat* format = StringFormat::GenericTypographic();
  float cursor = x;
  struct Piece {
    const wchar_t* text;
    float size, dy, gap;
  };
  const Piece pieces[] = {{L"HE", 54, 0, 2}, {L"X", 84, 10, 2}, {L"IC", 54, 0, 9}};
  for (const Piece& piece : pieces) {
    GraphicsPath part;
    part.AddString(piece.text, -1, logo_family_.get(), FontStyleRegular, piece.size, PointF(0, 0), format);
    RectF b;
    part.GetBounds(&b);
    Matrix m;
    m.Translate(cursor - b.X, bottom + piece.dy - (b.Y + b.Height));
    part.Transform(&m);
    logo.AddPath(&part, FALSE);
    cursor += b.Width + piece.gap;
  }
  RectF lb;
  logo.GetBounds(&lb);
  Pen glow(Hex(0x7B5CFF, 55), 4.0f);
  glow.SetLineJoin(LineJoinRound);
  g.DrawPath(&glow, &logo);
  auto chrome = Blend(lb.X, lb.Y, lb.Width, lb.Height, {Hex(0x7A7A92), Hex(0x24243A), Hex(0x000000), Hex(0x3A3A54)},
                      {0, 0.46f, 0.54f, 1});
  g.FillPath(chrome.get(), &logo);
  Pen edge(Hex(0x8D70FF), 1.2f);
  g.DrawPath(&edge, &logo);

  GraphicsPath hd;
  hd.AddString(L"HD", -1, hd_family_.get(), FontStyleRegular, 28.0f, PointF(0, 0), format);
  RectF hb;
  hd.GetBounds(&hb);
  Matrix m;
  m.Translate(cursor - hb.X, bottom + 10 - (hb.Y + hb.Height));
  hd.Transform(&m);
  hd.GetBounds(&hb);
  auto cyan = Blend(hb.X, hb.Y, hb.Width, hb.Height, {Hex(0xC8F8FF), Hex(0x38C4F2), Hex(0x0A6CB4)}, {0, 0.5f, 1});
  g.FillPath(cyan.get(), &hd);
  Pen hd_edge(Hex(0x062A48), 1.1f);
  g.DrawPath(&hd_edge, &hd);
}

// Everything that never changes is drawn once into a bitmap at the real pixel
// size; Paint then only adds the step bar, fields, text and buttons.
void SetupWindow::BuildBackdrop() {
  const int pw = static_cast<int>(kW * scale_ + 0.5f), ph = static_cast<int>(kH * scale_ + 0.5f);
  backdrop_ = std::make_unique<Bitmap>(pw, ph, PixelFormat32bppPARGB);
  Graphics g(backdrop_.get());
  g.SetSmoothingMode(SmoothingModeAntiAlias);
  g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
  g.ScaleTransform(scale_, scale_);
  g.Clear(Color(255, 0, 0, 0));

  // Slate hexagons scattered down both sides of the black field.
  const double r = 21.0;
  const double step_x = std::sqrt(3.0) * r;
  for (int row = 0; row < 20; ++row) {
    for (int col = 0; col < 21; ++col) {
      const double cx = col * step_x + (row % 2 ? step_x / 2 : 0) - 12;
      const double cy = row * 1.5 * r - 8;
      if (cx > 70 && cx < 650) continue;
      const int n = (row * 7 + col * 13 + (row * col) % 5) % 9;
      if (n < 3) continue;
      GraphicsPath hex;
      HexPath(hex, cx, cy, r * 0.9);
      const double shade = 0.25 + 0.09 * (n - 3);
      auto fill = Blend(cx - r, cy - r, r * 2, r * 2, {Mix(0x101020, 0x9A9AC6, shade), Mix(0x05050C, 0x3A3A5C, shade)}, {0, 1});
      g.FillPath(fill.get(), &hex);
    }
  }

  // Pearl-silver bezel.
  GraphicsPath bezel;
  RoundedPath(bezel, kBezel.x, kBezel.y, kBezel.w, kBezel.h, kBezel.r);
  auto silver = Blend(kBezel.x, kBezel.y, kBezel.w, kBezel.h, {Hex(0xF6F6FA), Hex(0xDADAE4), Hex(0xC4C4D2), Hex(0xA8A8BA)},
                      {0, 0.2f, 0.62f, 1});
  g.FillPath(silver.get(), &bezel);
  Pen rim(Hex(0x7E7E98), 1.2f);
  g.DrawPath(&rim, &bezel);
  GraphicsPath shine_rim;
  RoundedPath(shine_rim, kBezel.x + 2, kBezel.y + 2, kBezel.w - 4, kBezel.h - 4, kBezel.r - 2);
  Pen shine_pen(Hex(0xFFFFFF, 170), 1.0f);
  g.DrawPath(&shine_pen, &shine_rim);

  DrawLogo(g, 76, 74);
  StringFormat right;
  right.SetAlignment(StringAlignmentFar);
  SolidBrush tag_brush(Hex(0x3E3C5E));
  g.DrawString(L"XBLA PC PORT", -1, tag_.get(), RectF(420, 34, 226, 18), &right, &tag_brush);
  const std::wstring setup_tag = std::wstring(L"SETUP  ") + kDot + L"  V" + kVersion;
  g.DrawString(setup_tag.c_str(), -1, tag_.get(), RectF(420, 52, 226, 18), &right, &tag_brush);

  // Dark card with a violet glow.
  GraphicsPath card;
  RoundedPath(card, kCard.x, kCard.y, kCard.w, kCard.h, kCard.r);
  const float glow_steps[3][2] = {{9, 30}, {5, 70}, {2.2f, 230}};
  for (const auto& s : glow_steps) {
    Pen pen(Hex(0x6A48FF, static_cast<BYTE>(s[1])), s[0]);
    g.DrawPath(&pen, &card);
  }
  SolidBrush dark(Hex(0x0B0A1C));
  g.FillPath(&dark, &card);

  // Indigo honeycomb strip across the top of the card.
  g.SetClip(&card, CombineModeIntersect);
  auto strip = Blend(kCard.x, kCard.y, kCard.w, 58, {Hex(0x4C38CC), Hex(0x2A1E86), Hex(0x1A1258)}, {0, 0.6f, 1});
  g.FillRectangle(strip.get(), kCard.x, kCard.y, kCard.w, 58.0f);
  Pen comb(Hex(0xA898FF, 80), 1.0f);
  const double hr = 8.0;
  const double hx = std::sqrt(3.0) * hr;
  for (int row = 0; row < 6; ++row) {
    for (int col = 0; col < 40; ++col) {
      GraphicsPath hex;
      HexPath(hex, kCard.x + col * hx + (row % 2 ? hx / 2 : 0), kCard.y + row * 1.5 * hr, hr);
      g.DrawPath(&comb, &hex);
    }
  }
  g.ResetClip();

  // The step bar's dark well.
  GraphicsPath well;
  RoundedPath(well, kPill.x, kPill.y, kPill.w, kPill.h, kPill.r);
  SolidBrush well_fill(Hex(0x05051A));
  g.FillPath(&well_fill, &well);
  Pen well_pen(Hex(0x000000, 200), 1.5f);
  g.DrawPath(&well_pen, &well);

  // White-to-periwinkle panel.
  GraphicsPath panel;
  RoundedPath(panel, kPanel.x, kPanel.y, kPanel.w, kPanel.h, kPanel.r);
  auto pearl = Blend(kPanel.x, kPanel.y, kPanel.w, kPanel.h, {Hex(0xFFFFFF), Hex(0xE6E6F3), Hex(0xB6B6DD), Hex(0x9C9CCF)},
                     {0, 0.34f, 0.78f, 1});
  g.FillPath(pearl.get(), &panel);
  Pen panel_pen(Hex(0x6A4FE0), 1.6f);
  g.DrawPath(&panel_pen, &panel);

  GraphicsPath outline;
  RoundedPath(outline, 0.5f, 0.5f, kW - 1, kH - 1, 18);
  Pen outline_pen(Hex(0x6A48FF, 150), 1.0f);
  g.DrawPath(&outline_pen, &outline);
}

// ------------------------------------------------------------ controls --
RectL SetupWindow::ControlRect(Control id) const {
  switch (id) {
    case kBrowse: return {490, 252, 132, 34};
    case kLeft: return {352, 510, 112, 40};
    case kPlay: return {476, 506, 146, 46};
    case kExtra0:
    case kExtra1: return {98, kExtraFirst + (id - kExtra0) * kExtraPitch - 6, 524, kExtraPitch - 2};
    default: {
      const int row = id - kRow0;
      return {98, kRowsY + row * kRowPitch, 380, kRowPitch - 2};  // as wide as the package field: Browse stays clear
    }
  }
}

bool SetupWindow::Enabled(Control id) const {
  switch (id) {
    case kBrowse: return mode_ != Mode::Importing && !imported_now_;
    case kLeft: return !(mode_ == Mode::Importing && cancel_.load());
    case kPlay: return mode_ == Mode::Ready && installed_;
    case kExtra0:
    case kExtra1: return true;
    default: return mode_ == Mode::Choosing && id - kRow0 < static_cast<int>(candidates_.size());
  }
}

Control SetupWindow::HitTest(float x, float y) const {
  std::vector<Control> ids = {kBrowse, kLeft, kPlay, kExtra0, kExtra1};
  if (mode_ == Mode::Choosing) {
    for (int i = 0; i < static_cast<int>(candidates_.size()) && i < kMaxRows; ++i)
      ids.push_back(static_cast<Control>(kRow0 + i));
  }
  for (Control id : ids) {
    if (ControlRect(id).Contains(x, y) && Enabled(id)) return id;
  }
  return kNone;
}

// --------------------------------------------------------------- paint --
void SetupWindow::PaintText(Graphics& g, const std::wstring& text, Font* font, uint32_t color, RectF rect,
                            StringAlignment align, bool wrap, bool is_path) {
  if (text.empty()) return;
  StringFormat format;
  format.SetAlignment(align);
  format.SetLineAlignment(StringAlignmentNear);
  format.SetTrimming(wrap ? StringTrimmingWord : is_path ? StringTrimmingEllipsisPath : StringTrimmingEllipsisCharacter);
  if (!wrap) format.SetFormatFlags(StringFormatFlagsNoWrap);
  SolidBrush brush(Hex(color));
  g.DrawString(text.c_str(), -1, font, rect, &format, &brush);
}

// Cyan SCORE-bar fill with a gloss line, clipped to a rounded track.
void SetupWindow::PaintGlow(Graphics& g, double x, double y, double w, double h, double fraction) {
  if (fraction <= 0) return;
  GraphicsPath track;
  RoundedPath(track, static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), static_cast<float>(h / 2));
  g.SetClip(&track, CombineModeIntersect);
  const float fill_width = static_cast<float>(w * std::min(1.0, fraction));
  auto fill = Blend(x, y, w, h, {Hex(pal::CyanDeep), Hex(0x1A9ED8), Hex(pal::Cyan)}, {0, 0.55f, 1}, 0);
  g.FillRectangle(fill.get(), static_cast<REAL>(x), static_cast<REAL>(y), fill_width, static_cast<REAL>(h));
  SolidBrush shine(Hex(0xFFFFFF, 60));
  g.FillRectangle(&shine, static_cast<REAL>(x), static_cast<REAL>(y), fill_width, static_cast<REAL>(h * 0.42));
  g.ResetClip();
}

// Glossy pills, like the game's own menus: green gem for the main action, silver
// for the rest, a faded one when unavailable.
void SetupWindow::PaintButton(Graphics& g, Control id, const wchar_t* text, bool enabled, bool primary, Font* font) {
  const RectL r = ControlRect(id);
  std::vector<Color> stops;
  uint32_t edge, fore;
  bool shadow = false;
  if (!enabled) {
    stops = {Hex(0xE4E4EE), Hex(0xD2D2E0), Hex(0xC4C4D4)};
    edge = 0xA8A8C0;
    fore = 0x8C8AA8;
  } else if (primary) {
    stops = {Hex(0xA8F07E), Hex(0x4CC23E), Hex(0x2A9A2C)};
    edge = 0x1D6E22;
    fore = 0xFFFFFF;
    shadow = true;
  } else {
    stops = {Hex(0xFFFFFF), Hex(0xE2E2EE), Hex(0xBDBDD2)};
    edge = 0x7676A0;
    fore = 0x1E1C3A;
  }
  GraphicsPath path;
  RoundedPath(path, r.x, r.y, r.w, r.h, r.h / 2);
  auto fill = Blend(r.x, r.y, r.w, r.h, stops, {0, 0.5f, 1});
  g.FillPath(fill.get(), &path);
  GraphicsPath gloss;
  RoundedPath(gloss, r.x + 3, r.y + 2, r.w - 6, r.h * 0.45f, r.h * 0.22f);
  SolidBrush shine(Hex(0xFFFFFF, 70));
  g.FillPath(&shine, &gloss);
  if (enabled) {
    if (pressed_ == id) {
      SolidBrush shade(Hex(0x000000, 40));
      g.FillPath(&shade, &path);
    } else if (hover_ == id) {
      SolidBrush shade(Hex(0xFFFFFF, 55));
      g.FillPath(&shade, &path);
    }
  }
  Pen pen(Hex(edge), primary && enabled ? 1.8f : 1.2f);
  g.DrawPath(&pen, &path);
  StringFormat center;
  center.SetAlignment(StringAlignmentCenter);
  center.SetLineAlignment(StringAlignmentCenter);
  center.SetFormatFlags(StringFormatFlagsNoWrap);
  if (shadow) {
    SolidBrush shade(Hex(0x1A5A1E));
    g.DrawString(text, -1, font, RectF(r.x, r.y + 1.2f, r.w, r.h), &center, &shade);
  }
  SolidBrush brush(Hex(fore));
  g.DrawString(text, -1, font, RectF(r.x, r.y, r.w, r.h), &center, &brush);
}

void SetupWindow::Paint(HDC dc) {
  RECT client;
  GetClientRect(hwnd_, &client);
  HDC memory = CreateCompatibleDC(dc);
  HBITMAP bitmap = CreateCompatibleBitmap(dc, client.right, client.bottom);
  HGDIOBJ old = SelectObject(memory, bitmap);
  {
    Graphics g(memory);
    if (backdrop_) g.DrawImage(backdrop_.get(), 0, 0, client.right, client.bottom);
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
    g.SetPixelOffsetMode(PixelOffsetModeHalf);
    g.ScaleTransform(scale_, scale_);

    StringFormat center;
    center.SetAlignment(StringAlignmentCenter);
    center.SetLineAlignment(StringAlignmentCenter);

    // Step bar. Done steps are lit cyan with a tick; the current one is white,
    // and Import lights up with the real progress; later steps stay dim.
    const int stage = mode_ == Mode::Ready ? 2 : mode_ == Mode::Importing ? 1 : 0;
    double lit = stage / 3.0;
    if (mode_ == Mode::Ready) lit = 1.0;
    else if (mode_ == Mode::Importing && show_bar_) lit += progress_ / 300.0;
    PaintGlow(g, kPill.x + 2, kPill.y + 2, kPill.w - 4, kPill.h - 4, lit);
    const wchar_t* tabs[3] = {L"PACKAGE", L"IMPORT", L"PLAY"};
    const float segment = kPill.w / 3.0f;
    Pen divider(Hex(0xFFFFFF, 45), 1.0f);
    for (int i = 0; i < 3; ++i) {
      const float tx = kPill.x + i * segment;
      if (i > 0) g.DrawLine(&divider, tx, kPill.y + 7, tx, kPill.y + kPill.h - 7);
      const bool done = i < stage || mode_ == Mode::Ready;
      std::wstring label = tabs[i];
      uint32_t color = 0x6C6C96;
      if (done) {
        color = 0x04182C;
      } else if (i == stage) {
        color = 0xFFFFFF;
        if (i == 1 && show_bar_) label = std::wstring(L"IMPORT  ") + kDot + L"  " + std::to_wstring(progress_) + L"%";
      }
      const RectF rect(tx, kPill.y, segment, kPill.h);
      if (i == stage && !done) {
        SolidBrush shadow(Hex(0x000000, 170));
        g.DrawString(label.c_str(), -1, pill_.get(), RectF(tx, kPill.y + 1, segment, kPill.h), &center, &shadow);
      }
      SolidBrush brush(Hex(color));
      g.DrawString(label.c_str(), -1, pill_.get(), rect, &center, &brush);
      if (done) {
        RectF bounds;
        g.MeasureString(label.c_str(), -1, pill_.get(), rect, &center, &bounds);
        DrawTick(g, tx + segment / 2 - bounds.Width / 2 - 11, kPill.y + kPill.h / 2, 9, Hex(0x04182C), 1.8f);
      }
    }
    Pen under(Hex(pal::Cyan, 150), 1.2f);
    g.DrawLine(&under, kPill.x + 16, kPill.y + kPill.h - 1, kPill.x + kPill.w - 16, kPill.y + kPill.h - 1);

    // Title.
    const wchar_t* title = mode_ == Mode::Ready ? L"Ready to play" : mode_ == Mode::Importing ? L"Importing your game" : L"Set up your game";
    PaintText(g, title, title_.get(), pal::Ink, RectF(98, 164, 420, 32));

    // Package section.
    PaintText(g, L"GAME PACKAGE", caps_.get(), pal::Violet, RectF(98, 206, 300, 18));
    PaintText(g, mode_ == Mode::Choosing ? heading_ : hint_, body_.get(), pal::Soft, RectF(98, 224, 524, 22));
    if (mode_ == Mode::Choosing) {
      for (int i = 0; i < static_cast<int>(candidates_.size()) && i < kMaxRows; ++i) {
        const RectL r = ControlRect(static_cast<Control>(kRow0 + i));
        if (hover_ == kRow0 + i) {
          GraphicsPath row;
          RoundedPath(row, r.x, r.y, r.w, r.h, 6);
          SolidBrush hover(Hex(0x5B3FD6, 40));
          g.FillPath(&hover, &row);
        }
        GraphicsPath hex;
        HexPath(hex, r.x + 14, r.y + r.h / 2, 8.5);
        SolidBrush white(Hex(0xFFFFFF, 235));
        g.FillPath(&white, &hex);
        Pen ring(Hex(pal::Violet, 200), 1.4f);
        g.DrawPath(&ring, &hex);
        const Source& s = candidates_[i];
        const std::wstring text = (s.kind == SourceKind::PreviousInstall ? L"Previous install  " : L"") + s.path.wstring();
        PaintText(g, text, small_.get(), pal::Ink, RectF(r.x + 32, r.y + 5, r.w - 128, 22), StringAlignmentNear, false, true);
        PaintText(g, FormatMB(s.bytes), small_.get(), pal::Muted, RectF(r.x + r.w - 92, r.y + 5, 86, 22), StringAlignmentFar);
      }
    } else {
      GraphicsPath field;
      RoundedPath(field, kField.x, kField.y, kField.w, kField.h, kField.r);
      SolidBrush white(Hex(0xFFFFFF, 235));
      g.FillPath(&white, &field);
      Pen field_pen(Hex(pal::Violet, 150), 1.2f);
      g.DrawPath(&field_pen, &field);
      StringFormat left;
      left.SetAlignment(StringAlignmentNear);
      left.SetLineAlignment(StringAlignmentCenter);
      left.SetTrimming(StringTrimmingEllipsisPath);
      left.SetFormatFlags(StringFormatFlagsNoWrap);
      SolidBrush path_brush(Hex(path_set_ ? pal::Ink : pal::Muted));
      g.DrawString(path_text_.c_str(), -1, small_.get(), RectF(kField.x + 8, kField.y, kField.w - 16, kField.h), &left, &path_brush);
      PaintText(g, status_, small_.get(), status_color_, RectF(98, 294, 524, 34), StringAlignmentNear, true);
    }
    PaintButton(g, kBrowse, imported_now_ ? L"Imported" : L"Browse package" , Enabled(kBrowse), false, button_.get());

    // Progress: phase on the left, live counts on the right, a cyan bar.
    if (mode_ != Mode::Choosing) {
      PaintText(g, phase_, caps_.get(), phase_color_, RectF(98, 334, 524, 18));
      PaintText(g, stats_, small_.get(), pal::Muted, RectF(322, 334, 300, 18), StringAlignmentFar);
      if (show_bar_) {
        GraphicsPath track;
        RoundedPath(track, kBar.x, kBar.y, kBar.w, kBar.h, kBar.r);
        SolidBrush well(Hex(0x0B0A1C));
        g.FillPath(&well, &track);
        PaintGlow(g, kBar.x + 1, kBar.y + 1, kBar.w - 2, kBar.h - 2, progress_ / 100.0);
      }
      PaintText(g, detail_, small_.get(), pal::Muted, RectF(98, 374, 524, 18));
    }

    // Extras: a jewel checkbox, a title and a one-line explanation each.
    PaintText(g, std::wstring(L"OPTIONAL EXTRAS  ") + kDot + L"  APPLIED WHEN YOU PRESS PLAY", caps_.get(), pal::Violet,
              RectF(98, kExtrasY, 524, 18));
    Pen sep(Hex(pal::Violet, 60), 1.0f);
    g.DrawLine(&sep, 98.0f, kExtrasY + 20, 622.0f, kExtrasY + 20);
    const bool on[2] = {want_.fullscreen, want_.shortcut};
    for (int i = 0; i < 2; ++i) {
      const float y = kExtraFirst + i * kExtraPitch;
      if (hover_ == kExtra0 + i) {
        const RectL r = ControlRect(static_cast<Control>(kExtra0 + i));
        GraphicsPath row;
        RoundedPath(row, r.x, r.y, r.w, r.h, 8);
        SolidBrush hover(Hex(0x5B3FD6, 28));
        g.FillPath(&hover, &row);
      }
      if (on[i]) {
        PaintJewel(g, 110, y + 13, 12, pal::Jewels[3]);
        DrawTick(g, 110, y + 13, 13, Hex(0xFFFFFF), 2.4f);
      } else {
        GraphicsPath hex;
        HexPath(hex, 110, y + 13, 12);
        SolidBrush white(Hex(0xFFFFFF, 235));
        g.FillPath(&white, &hex);
        Pen edge(Hex(pal::Violet, 200), 1.4f);
        g.DrawPath(&edge, &hex);
      }
      PaintText(g, kExtraDefs[i].title, row_title_.get(), pal::Ink, RectF(132, y - 2, 490, 20));
      PaintText(g, kExtraDefs[i].detail, row_detail_.get(), pal::Muted, RectF(132, y + 17, 490, 18));
    }

    // A cleared flower: six jewels around a silver centre, once it is ready.
    if (mode_ == Mode::Ready) {
      const double cx = 592, cy = 190, r = 13, step = std::sqrt(3.0) * r;
      for (int i = 0; i < 6; ++i) {
        const double a = 3.14159265358979323846 / 180 * (60 * i - 60);
        PaintJewel(g, cx + step * std::cos(a), cy + step * std::sin(a), r * 0.94, pal::Jewels[i]);
      }
      PaintJewel(g, cx, cy, r * 0.94, 0xE6E6F4);
    }

    // Footer and the two buttons.
    PaintText(g, L"Title ID 584107D1", foot_.get(), pal::Muted, RectF(98, 524, 220, 18));
    const wchar_t* left = mode_ == Mode::Importing ? (cancel_.load() ? L"Cancelling" : L"Cancel") : L"Close";
    PaintButton(g, kLeft, left, Enabled(kLeft), false, button_.get());
    PaintButton(g, kPlay, L"PLAY", Enabled(kPlay), true, play_.get());
  }
  BitBlt(dc, 0, 0, client.right, client.bottom, memory, 0, 0, SRCCOPY);
  SelectObject(memory, old);
  DeleteObject(bitmap);
  DeleteDC(memory);
}

// ---------------------------------------------------------------- flow --
void SetupWindow::Start() {
  hint_ = L"Drop the package file or its folder onto this window, or browse for it.";
  std::wstring missing;
  installed_ = IsInstalled(p_, &missing);
  // The extras start unticked on a first setup, where an unticked box changes
  // nothing. Reopened with --setup they show what is set, and unticking one
  // switches it off.
  was_ = installed_ ? CurrentExtras(p_, options_.shortcut_folder) : Extras{};
  want_ = was_;
  if (!options_.package.empty()) {
    SelectPath(options_.package);
    return;
  }
  if (installed_) {
    mode_ = Mode::Ready;
    heading_ = L"Hexic HD is installed in this folder";
    hint_ = L"Press Play, change your extras, or import again to repair the game data.";
    path_text_ = L"resources\\assets";
    path_set_ = true;
    status_ = L"Game data imported. Saves and high scores are in resources\\userdata.";
    status_color_ = pal::Ok;
    phase_.clear();
    Invalidate();
    return;
  }
  heading_ = L"Select your Xbox 360 Hexic HD package";
  hint_ = std::wstring(L"Looking beside Hexic HD.exe") + kEllipsis;
  path_text_ = L"No package selected";
  path_set_ = false;
  Invalidate();
  UpdateWindow(hwnd_);
  std::vector<Source> found = DetectSources(p_);
  Log(L"Detected " + std::to_wstring(found.size()) + L" package(s) or previous install(s).");
  hint_ = L"Drop the package file or its folder onto this window, or browse for it.";
  if (found.size() == 1) {
    StartImport(found[0]);
  } else if (found.size() > 1) {
    candidates_ = found;
    if (candidates_.size() > kMaxRows) candidates_.resize(kMaxRows);
    mode_ = Mode::Choosing;
    heading_ = L"More than one was found. Choose the one to import:";
    Invalidate();
  } else {
    // Setup reopened because a file is missing: say which, on its own line.
    std::wstring note;
    if (options_.reason.rfind(L"missing ", 0) == 0 && options_.reason.find(L"no finished import") == std::wstring::npos)
      note = L"A game file is missing: " + options_.reason.substr(8) + L"\n";
    status_ = note + L"No package was found beside Hexic HD.exe or in a \"Game Package\" folder.";
    status_color_ = note.empty() ? pal::Muted : pal::Bad;
    Invalidate();
  }
}

void SetupWindow::Browse() {
  IFileOpenDialog* dialog = nullptr;
  if (FAILED(CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&dialog)))) return;
  DWORD flags = 0;
  dialog->GetOptions(&flags);
  dialog->SetOptions(flags | FOS_FORCEFILESYSTEM | FOS_FILEMUSTEXIST | FOS_DONTADDTORECENT);
  dialog->SetTitle(L"Select your Hexic HD Xbox 360 package");
  COMDLG_FILTERSPEC filter = {L"Xbox 360 package (any file)", L"*.*"};
  dialog->SetFileTypes(1, &filter);
  IShellItem* folder = nullptr;
  if (SUCCEEDED(SHCreateItemFromParsingName(p_.root.c_str(), nullptr, IID_PPV_ARGS(&folder)))) {
    dialog->SetFolder(folder);
    folder->Release();
  }
  if (SUCCEEDED(dialog->Show(hwnd_))) {
    IShellItem* item = nullptr;
    if (SUCCEEDED(dialog->GetResult(&item))) {
      PWSTR path = nullptr;
      if (SUCCEEDED(item->GetDisplayName(SIGDN_FILESYSPATH, &path))) {
        SelectPath(path);
        CoTaskMemFree(path);
      }
      item->Release();
    }
  }
  dialog->Release();
}

void SetupWindow::SelectPath(const fs::path& path) {
  if (mode_ == Mode::Importing || imported_now_) return;
  path_text_ = path.wstring();
  path_set_ = true;
  phase_.clear();
  stats_.clear();
  detail_.clear();
  show_bar_ = false;
  SetCursor(LoadCursorW(nullptr, IDC_WAIT));
  std::wstring why;
  std::vector<Source> found = SourcesIn(path, &why);
  if (found.empty()) {
    Log(L"Rejected " + path.wstring() + L": " + why);
    if (mode_ == Mode::Choosing) mode_ = Mode::Idle;
    if (installed_) mode_ = Mode::Ready;
    status_ = why;
    status_color_ = pal::Bad;
    Invalidate();
    return;
  }
  if (found.size() == 1) {
    StartImport(found[0]);
    return;
  }
  candidates_ = found;
  if (candidates_.size() > kMaxRows) candidates_.resize(kMaxRows);
  mode_ = Mode::Choosing;
  heading_ = L"That folder holds more than one. Choose the one to import:";
  Invalidate();
}

void SetupWindow::StartImport(Source source) {
  if (worker_.joinable()) worker_.join();
  mode_ = Mode::Importing;
  candidates_.clear();
  path_text_ = Describe(source);
  path_set_ = true;
  heading_ = L"Importing your game data";
  hint_ = L"Your package is only read, never changed. Nothing leaves this folder.";
  status_ = L"Hexic HD  " + std::wstring(kDot) + L"  " +
            (source.kind == SourceKind::PreviousInstall ? L"previous install" : L"Xbox LIVE Arcade package") + L"  " + kDot +
            L"  " + FormatMB(source.bytes);
  status_color_ = pal::Ok;
  phase_ = L"PREPARING";
  phase_color_ = pal::Violet;
  stats_.clear();
  detail_.clear();
  progress_ = 0;
  show_bar_ = true;
  cancel_ = false;
  Invalidate();
  const fs::path saves_from = source.kind == SourceKind::PreviousInstall ? source.path : FindPreviousInstall(p_);
  HWND hwnd = hwnd_;
  worker_ = std::thread([this, hwnd, source, saves_from]() {
    ImportResult* result = new ImportResult(Import(
        p_, source, saves_from, cancel_, [hwnd](int percent, const std::wstring& phase, const std::wstring& detail) {
          PostMessageW(hwnd, WM_APP_PROGRESS, 0, reinterpret_cast<LPARAM>(new ProgressMsg{percent, phase, detail}));
        }));
    PostMessageW(hwnd, WM_APP_DONE, 0, reinterpret_cast<LPARAM>(result));
  });
}

void SetupWindow::OnProgress(ProgressMsg* msg) {
  if (mode_ == Mode::Importing) {
    progress_ = std::clamp(msg->percent, 0, 100);
    phase_ = msg->phase;
    stats_ = msg->detail;
    Invalidate();
  }
  delete msg;
}

void SetupWindow::OnDone(ImportResult* result) {
  if (worker_.joinable()) worker_.join();
  stats_.clear();
  if (result->ok) {
    mode_ = Mode::Ready;
    installed_ = true;
    imported_now_ = true;
    heading_ = L"Hexic HD is ready";
    hint_ = L"Your package is not needed again. Hexic HD.exe starts the game straight away.";
    progress_ = 100;
    phase_ = L"HEXIC HD IS READY";
    phase_color_ = pal::Ok;
    detail_ = result->migrated.empty() ? L"Game data imported into resources\\assets." : result->migrated;
    status_ = L"Imported and verified. Press Play when you are ready.";
    status_color_ = pal::Ok;
    if (GetForegroundWindow() != hwnd_) {
      FLASHWINFO flash = {sizeof(flash), hwnd_, FLASHW_ALL | FLASHW_TIMERNOFG, 0, 0};
      FlashWindowEx(&flash);
    }
  } else {
    mode_ = installed_ ? Mode::Ready : Mode::Idle;
    show_bar_ = false;
    phase_ = result->cancelled ? L"IMPORT CANCELLED" : L"IMPORT DID NOT COMPLETE";
    phase_color_ = pal::Bad;
    status_ = result->message;
    status_color_ = result->cancelled ? pal::Muted : pal::Bad;
    detail_ = result->cancelled ? L"" : L"Your package was not changed. Details: resources\\runtime\\logs\\setup.log";
    heading_ = installed_ ? L"Hexic HD is installed in this folder" : L"Select your Xbox 360 Hexic HD package";
    hint_ = L"Drop the package file or its folder onto this window, or browse for it.";
  }
  delete result;
  cancel_ = false;
  Invalidate();
  if (close_after_import_) DestroyWindow(hwnd_);
}

void SetupWindow::Play() {
  const std::wstring note = ApplyExtras(p_, want_, was_, options_.shortcut_folder, [this](const fs::path& link) {
    const std::wstring text = L"There is already a Hexic HD shortcut on your desktop that opens a different copy:\n\n" +
                              link.wstring() + L"\n\nReplace it with one for this folder?";
    return MessageBoxW(hwnd_, text.c_str(), L"Hexic HD", MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDYES;
  });
  was_ = want_;
  if (!note.empty()) MessageBoxW(hwnd_, note.c_str(), L"Hexic HD", MB_OK | MB_ICONINFORMATION);
  std::wstring error;
  if (!LaunchGame(p_, options_.game_args, &error)) {
    Log(L"FAILED to start the game: " + error);
    MessageBoxW(hwnd_, error.c_str(), L"Hexic HD", MB_OK | MB_ICONERROR);
    return;
  }
  Log(L"Play: game started.");
  DestroyWindow(hwnd_);
}

void SetupWindow::RequestClose() {
  if (mode_ == Mode::Importing) {
    // Closing stops the import first; the window goes once it has cleaned up.
    close_after_import_ = true;
    cancel_ = true;
    Invalidate();
    return;
  }
  DestroyWindow(hwnd_);
}

void SetupWindow::Click(Control id) {
  switch (id) {
    case kBrowse: Browse(); break;
    case kLeft:
      if (mode_ == Mode::Importing) {
        cancel_ = true;
        Invalidate();
      } else {
        RequestClose();
      }
      break;
    case kPlay: Play(); break;
    case kExtra0: want_.fullscreen = !want_.fullscreen; break;
    case kExtra1: want_.shortcut = !want_.shortcut; break;
    default:
      if (id >= kRow0 && id - kRow0 < static_cast<int>(candidates_.size())) StartImport(candidates_[id - kRow0]);
      break;
  }
  Invalidate();
}

// ------------------------------------------------------------- messages --
LRESULT CALLBACK SetupWindow::Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  SetupWindow* self = reinterpret_cast<SetupWindow*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
  if (msg == WM_NCCREATE) {
    self = static_cast<SetupWindow*>(reinterpret_cast<CREATESTRUCTW*>(lp)->lpCreateParams);
    self->hwnd_ = hwnd;
    SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));
  }
  return self ? self->Handle(msg, wp, lp) : DefWindowProcW(hwnd, msg, wp, lp);
}

LRESULT SetupWindow::Handle(UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC dc = BeginPaint(hwnd_, &ps);
      Paint(dc);
      EndPaint(hwnd_, &ps);
      return 0;
    }
    case WM_PRINTCLIENT: Paint(reinterpret_cast<HDC>(wp)); return 0;
    case WM_ERASEBKGND: return 1;
    case WM_DPICHANGED: ApplyScale(HIWORD(wp), reinterpret_cast<RECT*>(lp)); return 0;
    case WM_APP_START: Start(); return 0;
    case WM_APP_PROGRESS: OnProgress(reinterpret_cast<ProgressMsg*>(lp)); return 0;
    case WM_APP_DONE: OnDone(reinterpret_cast<ImportResult*>(lp)); return 0;
    case WM_MOUSEMOVE: {
      if (!tracking_) {
        TRACKMOUSEEVENT track = {sizeof(track), TME_LEAVE, hwnd_, 0};
        tracking_ = TrackMouseEvent(&track) != FALSE;
      }
      const Control hit = HitTest(GET_X_LPARAM(lp) / scale_, GET_Y_LPARAM(lp) / scale_);
      if (hit != hover_) {
        hover_ = hit;
        Invalidate();
      }
      return 0;
    }
    case WM_MOUSELEAVE:
      tracking_ = false;
      if (hover_ != kNone) {
        hover_ = kNone;
        Invalidate();
      }
      return 0;
    case WM_SETCURSOR:
      if (LOWORD(lp) == HTCLIENT) {
        SetCursor(LoadCursorW(nullptr, hover_ != kNone ? IDC_HAND : IDC_ARROW));
        return TRUE;
      }
      break;
    case WM_LBUTTONDOWN: {
      const Control hit = HitTest(GET_X_LPARAM(lp) / scale_, GET_Y_LPARAM(lp) / scale_);
      if (hit == kNone) {
        // Borderless window: drag it from anywhere that is not a control.
        ReleaseCapture();
        SendMessageW(hwnd_, WM_NCLBUTTONDOWN, HTCAPTION, 0);
        return 0;
      }
      pressed_ = hit;
      SetCapture(hwnd_);
      Invalidate();
      return 0;
    }
    case WM_LBUTTONUP: {
      const Control was = pressed_;
      pressed_ = kNone;
      ReleaseCapture();
      const Control hit = HitTest(GET_X_LPARAM(lp) / scale_, GET_Y_LPARAM(lp) / scale_);
      if (was != kNone && was == hit) Click(hit);
      Invalidate();
      return 0;
    }
    case WM_KEYDOWN:
      if (wp == VK_ESCAPE) RequestClose();
      if (wp == VK_RETURN && Enabled(kPlay)) Play();
      return 0;
    case WM_DROPFILES: {
      HDROP drop = reinterpret_cast<HDROP>(wp);
      wchar_t path[32768] = {};
      if (DragQueryFileW(drop, 0, path, 32768) > 0) SelectPath(path);
      DragFinish(drop);
      return 0;
    }
    case WM_CLOSE: RequestClose(); return 0;
    case WM_DESTROY:
      if (worker_.joinable()) {
        cancel_ = true;
        worker_.join();
      }
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProcW(hwnd_, msg, wp, lp);
}

int SetupWindow::Run(HINSTANCE instance) {
  ULONG_PTR token = 0;
  GdiplusStartupInput input;
  if (GdiplusStartup(&token, &input, nullptr) != Ok) return 1;
  CreateFonts();
  icon_ = LoadIconW(instance, MAKEINTRESOURCEW(IDI_APP));
  WNDCLASSEXW wc = {sizeof(wc)};
  wc.style = CS_DROPSHADOW;
  wc.lpfnWndProc = Proc;
  wc.hInstance = instance;
  wc.hIcon = icon_;
  wc.hIconSm = icon_;
  wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
  wc.lpszClassName = kClassName;
  RegisterClassExW(&wc);
  hwnd_ = CreateWindowExW(WS_EX_APPWINDOW | WS_EX_ACCEPTFILES, kClassName, L"Hexic HD Setup",
                          WS_POPUP | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 100, 100, nullptr, nullptr, instance, this);
  if (!hwnd_) return 1;
  // Explorer runs unelevated like us, but allow drops from it either way.
  ChangeWindowMessageFilterEx(hwnd_, WM_DROPFILES, MSGFLT_ALLOW, nullptr);
  ChangeWindowMessageFilterEx(hwnd_, WM_COPYDATA, MSGFLT_ALLOW, nullptr);
  ChangeWindowMessageFilterEx(hwnd_, 0x0049 /* WM_COPYGLOBALDATA */, MSGFLT_ALLOW, nullptr);
  heading_ = L"Select your Xbox 360 Hexic HD package";
  ApplyScale(GetDpiForWindow(hwnd_), nullptr);
  ShowWindow(hwnd_, SW_SHOWNORMAL);
  SetForegroundWindow(hwnd_);
  UpdateWindow(hwnd_);
  PostMessageW(hwnd_, WM_APP_START, 0, 0);
  MSG msg;
  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
  const int code = installed_ ? 0 : 1;
  // Fonts and the backdrop are GDI+ objects: release them before GDI+ shuts down.
  backdrop_.reset();
  logo_family_.reset(), hd_family_.reset();
  title_.reset(), caps_.reset(), body_.reset(), small_.reset(), foot_.reset(), button_.reset(), play_.reset();
  row_title_.reset(), row_detail_.reset(), tag_.reset(), pill_.reset();
  GdiplusShutdown(token);
  return code;
}

}  // namespace

int RunSetupWindow(HINSTANCE instance, const Paths& p, const SetupOptions& options) {
  Log(L"Setup opened" + (options.reason.empty() ? std::wstring() : L" (" + options.reason + L")"));
  SetupWindow window(p, options);
  return window.Run(instance);
}

}  // namespace hexic
