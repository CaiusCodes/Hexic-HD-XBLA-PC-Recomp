# Building Hexic HD XBLA PC Recomp

## Prerequisites

- Windows 10 or 11 (64-bit)
- [LLVM](https://github.com/llvm/llvm-project/releases) (clang, clang-cl and llvm-rc,
  installed to `C:\Program Files\LLVM`)
- [CMake](https://cmake.org/) 3.25 or newer and [Ninja](https://ninja-build.org/)
- Visual Studio 2022 or newer with the C++ workload (Windows SDK and the Visual C++
  runtime DLLs that the release ships)
- Git

## 1. Build the ReXGlue SDK with this port's changes

The port needs changes to ReXGlue v0.9.0 that are not upstream: offline high scores,
keyboard input and the input hooks the mouse support uses, the player name, window and
settings hooks, timing, CPU and presentation fixes, the renderer choice, and fixes for a
texture-cache race and a hang on quit. They are in `sdk/rexglue-sdk-v0.9.0.patch`, which
applies to a clean v0.9.0 and contains no networking code.

One command clones ReXGlue at v0.9.0, applies the patch, then builds and installs the SDK
into `..\rexglue-sdk`, where the game's CMake presets look for it. It never replaces
anything that already exists:

```powershell
powershell -ExecutionPolicy Bypass -File tools\Get-Sdk.ps1
```

`-Destination <folder>` puts the SDK somewhere else, `-Source <folder>` clones from a local
copy instead of GitHub, and `-SkipBuild` stops after the patch.

Or by hand:

```bat
git clone https://github.com/rexglue/rexglue-sdk.git
cd rexglue-sdk
git checkout v0.9.0
git submodule update --init --recursive
git apply path\to\Hexic-HD-XBLA-PC-Recomp\sdk\rexglue-sdk-v0.9.0.patch
cmake --preset win-amd64 -DREXGLUE_USE_VULKAN=ON
cmake --build out/build/win-amd64 --config Release
cmake --install out/build/win-amd64 --config Release --prefix C:\rexglue-sdk-install
```

The patch also builds libmspack from its real sources, so your git symlink setting does
not matter.

## 2. Build the game

```bat
cmake --preset win-amd64-release
cmake --build out/build/win-amd64-release --target hexic_hd
```

The presets look for the SDK in `..\rexglue-sdk\out\install\win-amd64` and never fall back
to another install. If you installed the SDK elsewhere, add
`-DCMAKE_PREFIX_PATH=C:\rexglue-sdk-install` to the first command.

## 3. Package a release

The version comes from the `VERSION` file. `Make Release.bat` builds the game and runs
`tools/Make-Release.ps1`, which builds the launcher, stages the portable folder in
`out/release`, audits it (only `Hexic HD.exe`, `README.txt`, `licenses` and `resources` at
the top, and no game data anywhere) and creates `Hexic-HD-PC-v<version>.zip` with its
`.sha256`. Publish both on a GitHub release tagged `v<version>`: Check for Updates looks
for exactly that.

## Regenerating `generated/`

`generated/` is the C++ that ReXGlue's recompiler produced from the game's `default.xex`,
so a normal build doesn't need the game. To regenerate it, extract your package to
`../hexic_hd_extracted` and run:

```bat
rexglue codegen hexic_hd_manifest.toml
```

Two functions in `generated/` carry small hand edits marked `Hexic hand edit`
(`hexic_hd_recomp.2.cpp`: the GPU-wait backoff; `hexic_hd_recomp.11.cpp`: the frame
timing hook). Re-apply them after regenerating.

## Repository layout

| Path | Contents |
| --- | --- |
| `src/` | The PC app: paths, Settings, mouse and keyboard, title and menu hooks, updater |
| `generated/` | Recompiled game code (ReXGlue codegen output) |
| `packaging/launcher/` | `Hexic HD.exe`: the launcher, setup window and updater (native C++) |
| `packaging/` | Launcher build script, player README, licences; `legacy-setup/` holds the older Setup |
| `tools/` | SDK setup script, release builder and package extractor |
| `sdk/` | Patch for ReXGlue v0.9.0 |
| `docs/` | This file and the screenshots |
