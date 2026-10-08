<#
.SYNOPSIS
  Builds the ReXGlue SDK that Hexic HD PC needs, from a fresh clone of upstream.

.DESCRIPTION
  Clones https://github.com/rexglue/rexglue-sdk at the pinned v0.9.0 commit,
  fetches its submodules, applies sdk\rexglue-sdk-v0.9.0.patch, then builds and
  installs the SDK into
  <Destination>\out\install\win-amd64. The game's CMake presets look for it there
  (..\rexglue-sdk next to this project), so afterwards:

      cmake --preset win-amd64-release
      cmake --build out/build/win-amd64-release --target hexic_hd

  Nothing that already exists is ever replaced: Destination must not exist yet, or
  must be an empty folder.

  libmspack keeps some of its files as symlinks, which git checks out as tiny text
  files where symlinks are off (the default on many Windows setups). The patch makes
  the SDK build libmspack from its real sources instead, so this works whatever the
  machine's git symlink setting is.

.PARAMETER Destination
  Where to put the SDK. Default: rexglue-sdk, next to this project's folder.

.PARAMETER Source
  Where to clone from. Default: the upstream GitHub repository. A local path to an
  existing clone also works (for offline use).

.PARAMETER SkipBuild
  Stop after the patch is applied; do not build or install.

.NOTES
  Needs git, cmake, ninja and clang on PATH, plus the Visual C++ build tools and the
  Windows SDK that clang uses.
#>
[CmdletBinding()]
param(
    [string]$Destination,
    [string]$Source = 'https://github.com/rexglue/rexglue-sdk.git',
    [switch]$SkipBuild
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

# What the patch was made against: upstream tag v0.9.0.
$Tag = 'v0.9.0'
$Pin = '3eb9b511b4140d2769e27be63eae57d41bfa2afa'

$projectRoot = Split-Path -Parent $PSScriptRoot
$patch = Join-Path $projectRoot 'sdk\rexglue-sdk-v0.9.0.patch'
if (-not $Destination) {
    $Destination = Join-Path (Split-Path -Parent $projectRoot) 'rexglue-sdk'
}
$Destination = [IO.Path]::GetFullPath($Destination)

function Step([string]$Text) { Write-Host ''; Write-Host "== $Text" -ForegroundColor Cyan }

function Invoke-Git {
    & git.exe @args
    if ($LASTEXITCODE -ne 0) { throw ("git " + ($args -join ' ') + " failed (exit $LASTEXITCODE)") }
}

function Run([string]$Exe, [string[]]$Arguments) {
    & $Exe @Arguments
    if ($LASTEXITCODE -ne 0) { throw "$Exe $($Arguments -join ' ') failed (exit $LASTEXITCODE)" }
}

# --- 1. Before touching anything ---------------------------------------------------
Step 'Checking the tools and the patch'
$missing = @('git', 'cmake', 'ninja', 'clang') | Where-Object { -not (Get-Command $_ -ErrorAction SilentlyContinue) }
if ($missing) { throw "Not on PATH: $($missing -join ', '). See README.md, Prerequisites." }
if (-not (Test-Path -LiteralPath $patch -PathType Leaf)) { throw "Missing SDK patch: $patch" }
if ((Test-Path -LiteralPath $Destination) -and (Get-ChildItem -LiteralPath $Destination -Force | Select-Object -First 1)) {
    throw "$Destination already exists and is not empty. Existing files are never replaced; choose a new folder (-Destination)."
}
Write-Host "Project:     $projectRoot"
Write-Host "Patch:       $patch"
Write-Host "SDK folder:  $Destination"
Write-Host "Cloning:     $Source"

# --- 2. Clone at the pinned commit ---------------------------------------------------
Step "Cloning ReXGlue at $Tag"
# core.autocrlf=false so the patch's line endings match the files exactly, whatever the
# machine's own setting; core.longpaths because some submodules have deep trees.
Invoke-Git -c core.autocrlf=false -c core.longpaths=true clone --no-checkout $Source $Destination
Invoke-Git -C $Destination config core.autocrlf false
Invoke-Git -C $Destination config core.longpaths true
Invoke-Git -C $Destination checkout --detach $Pin
$head = (& git -C $Destination rev-parse HEAD).Trim()
if ($head -ne $Pin) { throw "Checked out $head, expected $Pin ($Tag)." }
Write-Host "At $Tag ($($Pin.Substring(0, 7)))"

# --- 3. Submodules -------------------------------------------------------------------
Step 'Fetching submodules (large: this takes a few minutes)'
Invoke-Git -C $Destination submodule update --init --recursive

# --- 4. libmspack ---------------------------------------------------------------------
Step 'Checking libmspack'
# The patch points the build at libmspack's real sources (libmspack\mspack), so the
# symlink stubs git leaves in cabextract\mspack where symlinks are off do not matter.
$lzxd = Join-Path $Destination 'thirdparty\libmspack\libmspack\mspack\lzxd.c'
if (-not (Test-Path -LiteralPath $lzxd -PathType Leaf)) { throw "libmspack was not fetched: $lzxd" }
Write-Host 'libmspack: real sources present'

# --- 5. The patch ---------------------------------------------------------------------
Step 'Applying the Hexic HD SDK patch'
Invoke-Git -C $Destination apply --check $patch
Invoke-Git -C $Destination apply $patch
# Commit it on a branch, so the SDK folder is a normal repository and the patch can be
# regenerated with: git diff v0.9.0 hexic-minimal -- src include thirdparty/CMakeLists.txt
Invoke-Git -C $Destination switch -c hexic-minimal
Invoke-Git -C $Destination add -- src include thirdparty/CMakeLists.txt
Invoke-Git -C $Destination -c user.name='Hexic HD PC contributors' -c user.email='' commit -q -m 'Hexic HD SDK changes (sdk/rexglue-sdk-v0.9.0.patch applied to v0.9.0)'
$changed = @(& git -C $Destination diff --name-only $Tag HEAD).Count
Write-Host "Patch applied: $changed files changed on branch hexic-minimal"

if ($SkipBuild) {
    Write-Host ''
    Write-Host 'Stopped before the build (-SkipBuild).' -ForegroundColor Yellow
    return
}

# --- 6. Build and install ---------------------------------------------------------------
Push-Location $Destination
try {
    Step 'Configuring the SDK'
    Run 'cmake' @('--preset', 'win-amd64')
    Step 'Building the SDK (Release) - this takes a while'
    Run 'cmake' @('--build', 'out/build/win-amd64', '--config', 'Release')
    # --config Release is required here: without it the install defaults to Debug and fails.
    Step 'Installing the SDK'
    Run 'cmake' @('--install', 'out/build/win-amd64', '--config', 'Release')
}
finally {
    Pop-Location
}

$prefix = Join-Path $Destination 'out\install\win-amd64'
foreach ($dll in 'rexruntime.dll', 'rexgpu-xenos.dll') {
    if (-not (Test-Path -LiteralPath (Join-Path $prefix "bin\$dll"))) { throw "Install is missing bin\$dll" }
}

Step 'Done'
Write-Host "SDK installed: $prefix"
Write-Host ''
Write-Host 'Now build the game:'
Write-Host "  cd `"$projectRoot`""
Write-Host '  cmake --preset win-amd64-release'
Write-Host '  cmake --build out/build/win-amd64-release --target hexic_hd'
