# Hexic HD PC

A native Windows port of the Xbox 360 (Xbox LIVE Arcade) release of **Hexic HD**,
built with the [ReXGlue](https://github.com/rexglue/rexglue-sdk) static recompiler.

**No game files are included.** You need your own legally obtained Xbox 360 Hexic HD
package (title ID `584107D1`). Setup installs the game from it.

## Features

- Portable install: one Setup program extracts your package into a `Game` folder
  beside it, and everything (saves, settings, scores) stays in that folder.
- **PC Settings** in the main menu (in place of the Xbox-only Achievements viewer):
  player name, windowed/fullscreen, resolution up to 3840 x 2160, VSync, an FPS
  counter and keyboard controls.
- **High Scores** that work offline: the game's own Leaderboards screen, renamed,
  shows your best Marathon, Timed and Survival scores from this PC under your
  player name.
- **Keyboard and controller** at the same time. Every controller input has a
  keyboard default and can be remapped in PC Settings > Keyboard Controls.
- "Quit Hexic" returns to the desktop.

## Install and play

1. Download the latest `Hexic-HD-PC-<version>.zip` from the Releases page.
2. Extract the whole folder somewhere writable (not Program Files).
3. Run `Install Hexic HD.exe`, choose your Hexic HD package, then **Install game**.
4. Play with **Play now**, or later with `Hexic HD.exe` beside Setup.

Setup opens your package read-only and only accepts the exact game build this port
was recompiled from (it checks the SHA-256 of `default.xex`). The README inside the
release covers controls, settings and troubleshooting.

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

The port needs changes to ReXGlue v0.9.0 that are not upstream (local leaderboards,
input, window and settings hooks). They are in `sdk/rexglue-sdk-v0.9.0.patch`.

```bat
git clone https://github.com/rexglue/rexglue-sdk.git
cd rexglue-sdk
git checkout v0.9.0
git submodule update --init --recursive
git apply path\to\hexic-hd-pc\sdk\rexglue-sdk-v0.9.0.patch
cmake --preset win-amd64
cmake --build out/build/win-amd64 --config Release
cmake --install out/build/win-amd64 --config Release --prefix C:\rexglue-sdk-install
```

### 2. Build the game

```bat
cd path\to\hexic-hd-pc
cmake --preset win-amd64-release -DCMAKE_PREFIX_PATH=C:\rexglue-sdk-install
cmake --build out/build/win-amd64-release --target hexic_hd
```

### 3. Package a release

`Make Release.bat` builds the game and runs `tools/Make-Release.ps1`, which builds
the Setup and play launchers, stages the portable folder in `out/release`, audits it
for game data, writes `release-manifest.json` and creates the ZIP.

### Regenerating `generated/`

`generated/` is the C++ that ReXGlue's recompiler produced from the game's
`default.xex`, so a normal build doesn't need the game. To regenerate it, extract
your package to `../hexic_hd_extracted` (next to this repository) and run:

```bat
rexglue codegen hexic_hd_manifest.toml
```

## Repository layout

| Path | Contents |
| --- | --- |
| `src/` | The PC app: paths, fonts, PC Settings panel, Xbox LIVE sign-in shim |
| `generated/` | Recompiled game code (ReXGlue codegen output) |
| `packaging/` | Setup, play launcher, installer scripts, player README, licenses |
| `tools/` | Release builder and STFS extractor |
| `sdk/` | Patch for ReXGlue v0.9.0 |

## Legal

Hexic HD, Xbox, Xbox 360 and related names and marks belong to their respective
owners. This project is not affiliated with or endorsed by Microsoft or Carbonated
Games. It contains no game assets; please don't share the `Game` folder Setup
creates from your package.

## License

The original code in this repository (`src/`, `packaging/`, `tools/`) is released
under the [MIT License](LICENSE). The SDK patch modifies ReXGlue, which is BSD
3-Clause licensed; those changes are offered under the same terms. The MIT license
does not cover `generated/`, which is machine-translated from the game program, or
the game itself.

## Credits

- [ReXGlue](https://github.com/rexglue/rexglue-sdk) by Tom Clay and contributors,
  which includes code derived from the [Xenia](https://xenia.jp/) project
- Extract-STFS, SDL, Dear ImGui, FFmpeg and the other open-source components listed
  in `packaging/licenses`
