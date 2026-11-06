// Hexic HD PC - the launcher ("Hexic HD.exe" in the release root).
//
// Release folder:
//   Hexic HD.exe          this program: starts the game, or shows setup first
//   README.txt, licenses\
//   resources\
//     runtime\            the game (hexic_hd.exe, DLLs), logs\
//     assets\             imported once from the player's own Xbox 360 package
//     userdata\           saves, high scores, caches and hexic_hd.toml (settings)
//
// Everything is found relative to this exe, so the folder can be moved.
#pragma once

#include <windows.h>

#include <atomic>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace hexic {

struct Paths {
  fs::path root;       // the folder holding this launcher
  fs::path launcher;   // root\Hexic HD.exe
  fs::path resources;  // root\resources
  fs::path runtime;    // resources\runtime
  fs::path game_exe;   // runtime\hexic_hd.exe
  fs::path assets;     // resources\assets
  fs::path userdata;   // resources\userdata
  fs::path config;     // userdata\hexic_hd.toml
  fs::path logs;       // runtime\logs (the game's own logs go there too)
  fs::path staging;    // resources\.import        (an import in progress)
  fs::path previous;   // resources\.assets-previous (the old copy during the swap)
};
Paths MakePaths();

extern const wchar_t* const kVersion;  // the release version, set by the build
extern const char* const kMarkerName;  // assets\<marker> is written last by a good import

// ------------------------------------------------------------------ log --
void LogTo(const fs::path& logs_dir);
void Log(const std::wstring& line);

// --------------------------------------------------------------- state --
// Cheap checks only (no hashing): the runtime files and a finished import.
// *missing names the first missing file.
bool IsInstalled(const Paths& p, std::wstring* missing);
// Puts back resources\assets from .assets-previous if an import was cut off
// in the middle of swapping the folders. Safe to call any time.
void RecoverInterruptedSwap(const Paths& p);
// True while the game from this folder is running (its exe cannot be opened
// for writing then).
bool GameRunning(const Paths& p);

// -------------------------------------------------------------- sources --
enum class SourceKind { Package, PreviousInstall };
struct Source {
  SourceKind kind = SourceKind::Package;
  fs::path path;        // the package file, or a previous install's Game folder
  uint64_t bytes = 0;   // package size, or the size of the previous install's assets
};
std::wstring Describe(const Source& s);  // one line for the window

// Header check of one file: an Xbox 360 package of the Hexic HD XBLA game.
// *why gets a sentence for the player when it is not.
bool CheckPackageHeader(const fs::path& file, std::wstring* why, uint64_t* bytes);
// A previous release's Game folder (or a release folder holding one, or the
// flat folder of the earliest portable builds) with the game data in it.
bool CheckPreviousInstall(const fs::path& folder, fs::path* game_dir, uint64_t* bytes);

// What a file or folder the player chose (or dropped) contains. Folders are
// searched a few levels deep. Returns the usable sources; *why explains an
// empty result.
std::vector<Source> SourcesIn(const fs::path& chosen, std::wstring* why);
// Automatic detection beside the launcher: the root's files, "Game Package"
// and the other folders beside the launcher (a few levels deep), and previous
// releases' Game folders here or in sibling folders. Never wider than that.
std::vector<Source> DetectSources(const Paths& p);
// A previous release's Game folder found beside this one, for carrying saves over.
fs::path FindPreviousInstall(const Paths& p);

// --------------------------------------------------------------- import --
using Report = std::function<void(int percent, const std::wstring& phase, const std::wstring& detail)>;
struct ImportResult {
  bool ok = false;
  bool cancelled = false;
  std::wstring message;    // why it failed
  std::wstring migrated;   // what was carried over from a previous install
};
// Validates the source against the build this port was compiled from, then
// imports the game data into resources\assets through a staging folder. The
// source is only ever read. saves_from: a previous Game folder whose saves and
// settings are copied into resources\userdata where none exist yet (may be empty).
ImportResult Import(const Paths& p, const Source& source, const fs::path& saves_from,
                    const std::atomic<bool>& cancel, const Report& report);

// ------------------------------------------------------------- settings --
// hexic_hd.toml holds one "key = value" per line. Set replaces the key's line
// or appends one; every other line is left as it is.
bool ReadConfig(const Paths& p, const std::string& key, std::string* value);
bool WriteConfig(const Paths& p, const std::string& key, const std::string& value);
// Writes the default hexic_hd.toml when there is none.
void EnsureSettings(const Paths& p);

// --------------------------------------------------------------- extras --
struct Extras {
  bool fullscreen = false;
  bool shortcut = false;
};
Extras CurrentExtras(const Paths& p, const fs::path& shortcut_folder);
// Applies only what differs from `was`. ask_replace is asked before an
// existing desktop shortcut that is not ours is replaced (nullptr: never).
// Returns a note for the player when something could not be done.
std::wstring ApplyExtras(const Paths& p, const Extras& want, const Extras& was,
                         const fs::path& shortcut_folder,
                         const std::function<bool(const fs::path&)>& ask_replace);
// Points our desktop shortcut at this folder again after the folder moved.
void RepairShortcut(const Paths& p, const fs::path& shortcut_folder);

// ----------------------------------------------------------------- game --
// Starts the game from resources\runtime. args are passed on unchanged.
bool LaunchGame(const Paths& p, const std::wstring& args, std::wstring* error);

// ------------------------------------------------------------------- UI --
struct SetupOptions {
  fs::path package;          // preselected (--package)
  fs::path shortcut_folder;  // where the desktop shortcut goes (--shortcut-folder, testing)
  std::wstring game_args;    // passed to the game on Play
  bool forced = false;       // --setup on a complete install
  bool update = false;       // --update: the update mode (RunUpdate), then the game again
  std::wstring reason;       // why setup opened (a missing file), for the log
};
int RunSetupWindow(HINSTANCE instance, const Paths& p, const SetupOptions& options);

// ---------------------------------------------------------------- utils --
std::wstring FormatMB(uint64_t bytes);
std::wstring Quote(const std::wstring& s);
std::wstring Widen(const std::string& s);   // UTF-8 -> UTF-16
std::string Narrow(const std::wstring& s);  // UTF-16 -> UTF-8
bool SameFile(const fs::path& a, const fs::path& b);

// ---------------------------------------------------------------- patch --
// The PC wording and the High Scores screen, applied to an unpacked assets
// folder (patch.cpp). Returns one log line per patch. A file that is not the
// expected build is left exactly as it was.
std::vector<std::wstring> PatchPcMenus(const fs::path& assets);

// Inflates a zlib stream (a compressed SWF body). False on any error.
bool Inflate(const uint8_t* zlib_data, size_t size, std::vector<uint8_t>* out);
// Inflates a raw deflate stream (a ZIP entry); `expected` sizes the output.
bool InflateRaw(const uint8_t* data, size_t size, size_t expected, std::vector<uint8_t>* out);

// --------------------------------------------------------------- update --
// "Hexic HD.exe --update" (update.cpp; the game's Settings > Updates opens it):
// asks GitHub for the latest release (src/hexic_update.h), downloads its ZIP
// into resources\.update, checks its SHA-256, unpacks it and replaces the
// program files (Hexic HD.exe, README.txt, licenses\, resources\runtime\ but
// not its logs). resources\assets and resources\userdata are never touched.
struct UpdateOutcome {
  enum Kind { kUpdated, kUpToDate, kFailed, kCancelled } kind = kFailed;
  std::wstring version;  // the latest release's version, when known
  std::wstring message;  // why it failed, for the player
};
UpdateOutcome RunUpdate(const Paths& p, const std::atomic<bool>& cancel, const Report& report);
// Puts back program files from an update cut off half-way, deletes leftovers
// (the previous launcher's exe, which cannot be deleted while it runs) and the
// download folder. Safe to call any time; cheap when there is nothing to do.
void RecoverInterruptedUpdate(const Paths& p);

}  // namespace hexic
