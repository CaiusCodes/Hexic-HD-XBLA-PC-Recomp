# Hexic HD PC

A native Windows port of the Xbox 360 (Xbox LIVE Arcade) release of **Hexic HD**,
built with the [ReXGlue](https://github.com/rexglue/rexglue-sdk) static recompiler.

**No game files are included.** You need your own legally obtained Xbox 360 Hexic HD
package (title ID `584107D1`). The first time you open the game it imports the game
data from it.

## Features

- **Portable, one program.** Extract the release and open `Hexic HD.exe`. The first
  time, it imports your package into `resources\assets`; saves, high scores and
  settings stay in `resources\userdata`. Nothing is installed elsewhere, no
  administrator rights or registry entries, and the folder can be moved or copied.
- **Settings** in the main menu (in place of the Xbox-only Achievements viewer):
  player name, windowed/fullscreen, resolution up to 3840 x 2160, render scale
  (1x / 2x / 3x), VSync, an FPS counter and keyboard controls.
- **High Scores** that work offline: the game's own Leaderboards screen, renamed,
  shows your best Marathon, Timed and Survival scores from this PC under your
  player name.
- **Keyboard and controller** at the same time. Every controller input has a
  keyboard default and can be remapped in Settings > Keyboard Controls.
- **Light on the PC.** A steady 60 fps with even frame pacing; on the title screen
  the whole game uses about a third of one CPU core.
- "Quit Hexic" returns to the desktop.

## Install and play

1. Download the latest `Hexic-HD-PC-<version>.zip` from the Releases page.
2. Extract the whole folder somewhere writable (not Program Files).
3. Open `Hexic HD.exe`. If your package is beside it, in a `Game Package` folder
   next to it, or in an older release of this port nearby, it is found and imported
   automatically; otherwise drag it onto the window or click **Browse package**.
4. Click **PLAY**. From then on, `Hexic HD.exe` starts the game straight away.

Setup opens your package read-only and only accepts the exact game build this port
was recompiled from (it checks the SHA-256 of `default.xex`). The README inside the
release covers controls, settings, updating from older releases and troubleshooting.

Requirements: Windows 10 or 11 (64-bit) and a DirectX 12 graphics card.

## Building from source

### Prerequisites

- Windows 10 or 11 (64-bit)
- [LLVM](https://github.com/llvm/llvm-project/releases) (clang, clang-cl and llvm-rc,
  installed to `C:\Program Files\LLVM`)
- [CMake](https://cmake.org/) 3.25 or newer and [Ninja](https://ninja-build.org/)
- Visual Studio 2022 or newer with the C++ workload (Windows SDK and the Visual C++
  runtime DLLs that the release ships)
- Git

### 1. Build the ReXGlue SDK with this port's changes

The port needs changes to ReXGlue v0.9.0 that are not upstream: the offline high
scores, keyboard input, the player name, window and settings hooks, and timing, CPU
and presentation fixes. They are in `sdk/rexglue-sdk-v0.9.0.patch` (56 files, applies
to a clean v0.9.0) and contain no networking code. The patch also makes the SDK build
libmspack from its real sources, because libmspack stores some files as symlinks that
Git for Windows checks out as unusable text files unless symlinks are enabled; with
the patch it does not matter what your git symlink setting is.

**The easy way.** One command clones ReXGlue at v0.9.0, applies the patch, then builds
and installs the SDK into `..\rexglue-sdk`, where the
game's CMake presets look for it. It never replaces anything that already exists:

```powershell
powershell -ExecutionPolicy Bypass -File tools\Get-Sdk.ps1
```

(`-Destination <folder>` puts the SDK somewhere else; `-SkipBuild` stops after the
patch.) Or do the same by hand:

```bat
git clone https://github.com/rexglue/rexglue-sdk.git
cd rexglue-sdk
git checkout v0.9.0
git submodule update --init --recursive
git apply path\to\hexic-hd-pc\sdk\rexglue-sdk-v0.9.0.patch
```

```bat
cmake --preset win-amd64
cmake --build out/build/win-amd64 --config Release
cmake --install out/build/win-amd64 --config Release --prefix C:\rexglue-sdk-install
```

### 2. Build the game

```bat
cd path\to\hexic-hd-pc
cmake --preset win-amd64-release
cmake --build out/build/win-amd64-release --target hexic_hd
```

The presets look for the SDK in `..\rexglue-sdk\out\install\win-amd64`, which is
where `tools\Get-Sdk.ps1` puts it, and will not fall back to any other install. If you
built the SDK by hand and installed it elsewhere, add
`-DCMAKE_PREFIX_PATH=C:\rexglue-sdk-install` (your install folder) to the first command.

### 3. Package a release

`Make Release.bat` builds the game and runs `tools/Make-Release.ps1`, which builds the
launcher (`packaging/Build-Launcher.ps1`), stages the portable folder in
`out/release`, audits it (only `Hexic HD.exe`, `README.txt`, `licenses` and
`resources` at the top, and no game data anywhere), writes `release-manifest.json`
and creates the ZIP.

### Regenerating `generated/`

`generated/` is the C++ that ReXGlue's recompiler produced from the game's
`default.xex`, so a normal build doesn't need the game. To regenerate it, extract
your package to `../hexic_hd_extracted` (next to this repository) and run:

```bat
rexglue codegen hexic_hd_manifest.toml
```

Two functions in `generated/` carry small hand edits, marked `Hexic hand edit`
(`hexic_hd_recomp.2.cpp`: the GPU-wait backoff; `hexic_hd_recomp.11.cpp`: the
frame-timing log). Re-apply them after regenerating.

## Repository layout

| Path | Contents |
| --- | --- |
| `src/` | The PC app: paths, fonts, Settings panel, timing hooks, Xbox LIVE sign-in shim |
| `generated/` | Recompiled game code (ReXGlue codegen output) |
| `packaging/launcher/` | `Hexic HD.exe`: the launcher and setup window (native C++) |
| `packaging/` | Launcher build script, player README, licenses; `legacy-setup/` holds the older Setup and play launchers |
| `tools/` | SDK setup script (`Get-Sdk.ps1`), release builder and STFS extractor |
| `sdk/` | Patch for ReXGlue v0.9.0 |

## Legal

Hexic HD, Xbox, Xbox 360 and related names and marks belong to their respective
owners. This project is not affiliated with or endorsed by Microsoft or Carbonated
Games. It contains no game assets; please don't share a release folder once it has
imported your package (`resources\assets`).

## License

The original code in this repository (`src/`, `packaging/`, `tools/`) is released
under the [MIT License](LICENSE), except the launcher in `packaging/launcher/`, whose
package reader is derived from [Velocity](https://github.com/hetelek/Velocity) and
which is therefore licensed under the GNU GPL version 3
(`packaging/licenses/LICENSE-Extract-STFS.txt`). The SDK patch modifies
ReXGlue, which is BSD 3-Clause licensed; those changes are offered under the same
terms. The MIT license does not cover `generated/`, which is machine-translated from
the game program, or the game itself.

## Credits

- [ReXGlue](https://github.com/rexglue/rexglue-sdk) by Tom Clay and contributors,
  which includes code derived from the [Xenia](https://xenia.jp/) project
- [Velocity](https://github.com/hetelek/Velocity), whose STFS handling the package
  reader is derived from
- SDL, Dear ImGui, FFmpeg and the other open-source components listed in
  `packaging/licenses`
