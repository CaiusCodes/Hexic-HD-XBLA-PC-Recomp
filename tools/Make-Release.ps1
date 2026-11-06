# Builds the Hexic HD PC portable release in out\release. The ZIP holds one folder:
#
#   Hexic HD PC\
#     Hexic HD.exe                the launcher: the only program to open
#     README.txt
#     licenses\
#     resources\
#       runtime\                  the game (hexic_hd.exe, rexruntime.dll,
#                                 rexgpu-xenos.dll, VC++ runtime DLLs) and version.txt
#
# The first time the launcher runs it imports the game data from the player's
# own Xbox 360 package into resources\assets; saves, high scores and settings go
# to resources\userdata. The release carries no original game content; the audit
# below refuses to package anything that looks like game data, debug output or
# user state, and anything at the root besides the four items above.
[CmdletBinding()]
param(
    [string]$BuildPreset = "win-amd64-release",
    # The release version: the VERSION file at the repository root, which the
    # game is built with too (Check for Updates compares against it). A
    # different -Version is refused, so the launcher and the game agree.
    [string]$Version = "",
    # Added to the ZIP's name: Hexic-HD-PC-v<Version><Suffix>.zip (the name Check
    # for Updates looks for on a GitHub release tagged v<Version>)
    [string]$Suffix = "",
    # Replace an existing ZIP of the same name (never the default: a shipped
    # release's ZIP must not be overwritten by accident).
    [switch]$Force,
    # Folder holding the Visual C++ runtime DLLs to ship; found automatically.
    [string]$VcRedistDir,
    # Extracted game data to compare the release against byte for byte.
    [string]$AssetsDir
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$fileVersion = (Get-Content -LiteralPath (Join-Path $PSScriptRoot "..\VERSION") -TotalCount 1).Trim()
if (-not $Version) { $Version = $fileVersion }
if ($Version -ne $fileVersion) {
    throw "Version $Version differs from the VERSION file ($fileVersion): edit VERSION and rebuild the game instead."
}
if ($Version -notmatch '^[A-Za-z0-9._-]+$') {
    throw "Version may contain only letters, numbers, dots, underscores and hyphens."
}
if ($Suffix -notmatch '^[A-Za-z0-9._-]*$') {
    throw "Suffix may contain only letters, numbers, dots, underscores and hyphens."
}

$projectRoot = [System.IO.Path]::GetFullPath((Join-Path -Path $PSScriptRoot -ChildPath ".."))
$buildRoot = Join-Path $projectRoot "out\build\$BuildPreset"
$packagingRoot = Join-Path $projectRoot "packaging"
$releaseRoot = Join-Path $projectRoot "out\release"
# Staged under out\release\staging so a copy someone plays from out\release is never touched.
$releaseName = "Hexic HD PC"
$stageRoot = Join-Path $releaseRoot "staging\$releaseName"
$zipPath = Join-Path $releaseRoot "Hexic-HD-PC-v$Version$Suffix.zip"
$shaPath = "$zipPath.sha256"
$launcherName = "Hexic HD.exe"
$exeName = "hexic_hd.exe"

$runtimeFiles = @($exeName, "rexruntime.dll", "rexgpu-xenos.dll")
$vcRuntimeFiles = @("msvcp140.dll", "msvcp140_atomic_wait.dll", "vcruntime140.dll", "vcruntime140_1.dll")

if ((Test-Path -LiteralPath $zipPath) -and -not $Force) {
    throw "$zipPath already exists. Pass -Suffix to name this build differently, or -Force to replace it."
}

# --- 1. Inputs ---------------------------------------------------------------
foreach ($file in $runtimeFiles) {
    if (-not (Test-Path -LiteralPath (Join-Path $buildRoot $file) -PathType Leaf)) {
        throw "Build output is missing: $file. Build $BuildPreset first."
    }
}

# A release must never ship a binary older than the source it claims to be.
$exeTime = (Get-Item -LiteralPath (Join-Path $buildRoot $exeName)).LastWriteTimeUtc
$newestSource = Get-ChildItem -LiteralPath (Join-Path $projectRoot "src") -File -Recurse |
    Sort-Object LastWriteTimeUtc -Descending | Select-Object -First 1
if ($newestSource.LastWriteTimeUtc -gt $exeTime) {
    throw "$exeName is older than src\$($newestSource.Name). Rebuild before packaging."
}

if (-not $VcRedistDir) {
    $candidates = @(Get-Item -Path "C:\Program Files\Microsoft Visual Studio\*\*\VC\Redist\MSVC\*\x64\Microsoft.VC14*.CRT" -ErrorAction SilentlyContinue |
        Where-Object { $dir = $_.FullName; @($vcRuntimeFiles | Where-Object { -not (Test-Path -LiteralPath (Join-Path $dir $_)) }).Count -eq 0 } |
        Sort-Object { [version]($_.FullName -replace '^.*\\MSVC\\([0-9.]+)\\.*$', '$1') } -Descending)
    if ($candidates.Count -eq 0) {
        throw "Visual C++ redistributable DLLs not found. Pass -VcRedistDir."
    }
    $VcRedistDir = $candidates[0].FullName
}
foreach ($file in $vcRuntimeFiles) {
    if (-not (Test-Path -LiteralPath (Join-Path $VcRedistDir $file) -PathType Leaf)) {
        throw "Missing $file in $VcRedistDir"
    }
}

# ReXGlue 0.9.0 uses GPU plugin ABI 2. Validate the exported ABI function
# before packaging so a stale plugin cannot produce a broken release.
if (-not ("GpuPluginInspector" -as [type])) {
    Add-Type -TypeDefinition @"
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

public static class GpuPluginInspector {
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    private delegate UInt32 GpuAbiVersionDelegate();

    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    private static extern IntPtr LoadLibraryExW(
        string fileName, IntPtr file, UInt32 flags);

    [DllImport("kernel32.dll", CharSet = CharSet.Ansi, SetLastError = true)]
    private static extern IntPtr GetProcAddress(IntPtr module, string symbolName);

    [DllImport("kernel32.dll")]
    private static extern bool FreeLibrary(IntPtr module);

    public static UInt32 GetAbiVersion(string pluginPath) {
        const UInt32 LoadLibrarySearchDllLoadDir = 0x00000100;
        const UInt32 LoadLibrarySearchDefaultDirs = 0x00001000;
        IntPtr module = LoadLibraryExW(
            pluginPath, IntPtr.Zero,
            LoadLibrarySearchDllLoadDir | LoadLibrarySearchDefaultDirs);
        if (module == IntPtr.Zero) {
            throw new Win32Exception(Marshal.GetLastWin32Error(),
                "Could not load GPU plugin for ABI validation");
        }

        try {
            IntPtr symbol = GetProcAddress(module, "rex_gpu_abi_version");
            if (symbol == IntPtr.Zero) {
                throw new InvalidOperationException(
                    "GPU plugin does not export rex_gpu_abi_version");
            }

            var function = (GpuAbiVersionDelegate)Marshal.GetDelegateForFunctionPointer(
                symbol, typeof(GpuAbiVersionDelegate));
            return function();
        }
        finally {
            FreeLibrary(module);
        }
    }
}
"@
}

$gpuPluginAbi = [GpuPluginInspector]::GetAbiVersion((Join-Path $buildRoot "rexgpu-xenos.dll"))
if ($gpuPluginAbi -ne 2) {
    throw "GPU plugin ABI mismatch: found $gpuPluginAbi, expected 2. Rebuild with GPU_PLUGINS xenos."
}

# --- 2. Launcher ----------------------------------------------------------------
& (Join-Path $packagingRoot "Build-Launcher.ps1") -Version $Version
$launcher = Join-Path $packagingRoot $launcherName
if (-not (Test-Path -LiteralPath $launcher -PathType Leaf)) {
    throw "The launcher was not built: $launcherName"
}

# --- 3. Stage -----------------------------------------------------------------
foreach ($played in @("resources\assets", "resources\userdata")) {
    if (Test-Path -LiteralPath (Join-Path $stageRoot $played)) {
        throw "The staging folder has been played from ($played; saves?). Move it away first: $stageRoot"
    }
}
if (Test-Path -LiteralPath $stageRoot) { Remove-Item -LiteralPath $stageRoot -Recurse -Force }
if (Test-Path -LiteralPath $zipPath) { Remove-Item -LiteralPath $zipPath -Force }

$licensesStage = Join-Path $stageRoot "licenses"
$runtimeStage = Join-Path $stageRoot "resources\runtime"
foreach ($dir in @($stageRoot, $licensesStage, $runtimeStage)) {
    New-Item -ItemType Directory -Path $dir -Force | Out-Null
}

# Release root: the launcher, README and licences.
Copy-Item -LiteralPath $launcher -Destination $stageRoot
$readme = [System.IO.File]::ReadAllText((Join-Path $packagingRoot "README.txt")).Replace("@VERSION@", $Version)
$readme = $readme -replace "`r?`n", "`r`n"  # Notepad-friendly line endings
[System.IO.File]::WriteAllText((Join-Path $stageRoot "README.txt"), $readme, (New-Object System.Text.UTF8Encoding($false)))
Get-ChildItem -LiteralPath (Join-Path $packagingRoot "licenses") -File |
    ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $licensesStage }

# resources\runtime: the game and its DLLs, and the version. The game reads its
# data from resources\assets and resources\userdata (the launcher carries the
# default hexic_hd.toml and writes it into userdata on first run).
foreach ($file in $runtimeFiles) { Copy-Item -LiteralPath (Join-Path $buildRoot $file) -Destination $runtimeStage }
foreach ($file in $vcRuntimeFiles) { Copy-Item -LiteralPath (Join-Path $VcRedistDir $file) -Destination $runtimeStage }
[System.IO.File]::WriteAllText((Join-Path $runtimeStage "version.txt"), $Version)

# --- 4. Audit: nothing from the game package, no debug output, no user state -
$staged = @(Get-ChildItem -LiteralPath $stageRoot -Recurse -Force)
foreach ($item in @(Get-ChildItem -LiteralPath $stageRoot -Force)) {
    if (@($launcherName, "README.txt", "licenses", "resources") -notcontains $item.Name) {
        throw "Unexpected item in the release root: $($item.Name)"
    }
}
if (@(Get-ChildItem -LiteralPath $stageRoot -Force).Count -ne 4) {
    throw "The release root must hold exactly: $launcherName, README.txt, licenses, resources."
}
foreach ($item in @(Get-ChildItem -LiteralPath (Join-Path $stageRoot "resources") -Force)) {
    if ($item.Name -ne "runtime") { throw "Unexpected item in resources: $($item.Name)" }
}
$forbiddenNames = @("assets", "assets_import_tmp", "userdata", "logs", "cache", "Game", "hexic_hd.toml",
    "highscores.txt", "default.xex", "arcadeinfo.xml", "g.xml", "HexicDeluxe.swf", "guest_image.bin",
    "xstr_decompressed.bin", "memdump.bin", "release-manifest.json")
$forbiddenPatterns = @("*.pdb", "*.xex", "*.bin", "*.log", "*.ilk", "*.exp", "*.lib", "*.ps1",
    "*.swf", "*.wma", "*.ttf", "*.png", "*.bmp", "*_g.xml")
foreach ($item in $staged) {
    if ($forbiddenNames -contains $item.Name) {
        throw "Forbidden item entered the release: $($item.FullName)"
    }
    foreach ($pattern in $forbiddenPatterns) {
        if ($item.Name -like $pattern) { throw "Forbidden file type entered the release: $($item.FullName)" }
    }
    if (-not $item.PSIsContainer -and $item.Length -gt 64MB) {
        throw "Unexpectedly large file in the release: $($item.FullName)"
    }
}

# Byte-level check against the developer's extracted game data, when present:
# no shipped file may be identical to any file from the package.
if (-not $AssetsDir) {
    foreach ($candidate in @((Join-Path $projectRoot "..\hexic_hd_extracted"), (Join-Path $buildRoot "assets"))) {
        if (Test-Path -LiteralPath $candidate) { $AssetsDir = [System.IO.Path]::GetFullPath($candidate); break }
    }
}
$stagedFiles = @($staged | Where-Object { -not $_.PSIsContainer })
$assetComparisons = 0
if ($AssetsDir -and (Test-Path -LiteralPath $AssetsDir)) {
    $stagedSizes = @{}
    foreach ($file in $stagedFiles) { $stagedSizes[$file.Length] = $true }
    $stagedHashes = @{}
    foreach ($file in $stagedFiles) {
        $stagedHashes[(Get-FileHash -LiteralPath $file.FullName -Algorithm SHA256).Hash] = $file.FullName
    }
    foreach ($asset in @(Get-ChildItem -LiteralPath $AssetsDir -File -Recurse)) {
        if (-not $stagedSizes.ContainsKey($asset.Length)) { continue }
        $assetComparisons++
        $hash = (Get-FileHash -LiteralPath $asset.FullName -Algorithm SHA256).Hash
        if ($stagedHashes.ContainsKey($hash)) {
            throw "Release file $($stagedHashes[$hash]) is identical to game data $($asset.FullName)"
        }
    }
}

# --- 5. The release ZIP ---------------------------------------------------------
# Entries are written one by one with forward slashes: under Windows PowerShell
# 5.1, ZipFile.CreateFromDirectory stores backslashes ("Hexic HD PC\README.txt"),
# which the ZIP format does not allow and some unzip tools turn into single
# files with backslashes in their names instead of folders.
Add-Type -AssemblyName System.IO.Compression
Add-Type -AssemblyName System.IO.Compression.FileSystem
if (Test-Path -LiteralPath $zipPath) { Remove-Item -LiteralPath $zipPath }  # -Force was checked above
$stageParent = Split-Path -Parent $stageRoot
$archive = [System.IO.Compression.ZipFile]::Open($zipPath, [System.IO.Compression.ZipArchiveMode]::Create)
try {
    foreach ($item in @(Get-Item -LiteralPath $stageRoot) + @(Get-ChildItem -LiteralPath $stageRoot -Recurse)) {
        $name = $item.FullName.Substring($stageParent.Length + 1).Replace('\', '/')
        if ($item.PSIsContainer) {
            # Only empty folders need an entry of their own.
            if (-not (Get-ChildItem -LiteralPath $item.FullName -Force | Select-Object -First 1)) {
                [void]$archive.CreateEntry("$name/")
            }
        } else {
            [void][System.IO.Compression.ZipFileExtensions]::CreateEntryFromFile($archive, $item.FullName, $name,
                [System.IO.Compression.CompressionLevel]::Optimal)
        }
    }
}
finally {
    $archive.Dispose()
}

$releaseSize = ($stagedFiles | Measure-Object -Property Length -Sum).Sum
$zip = Get-Item -LiteralPath $zipPath
# <zip>.sha256 beside it ("<hash>  <name>", as sha256sum writes): upload it with
# the ZIP. Check for Updates uses GitHub's own asset digest, and this file when
# GitHub reports none; players can check their download with it too.
$zipSha = (Get-FileHash -LiteralPath $zipPath -Algorithm SHA256).Hash.ToLowerInvariant()
[System.IO.File]::WriteAllText($shaPath, "$zipSha  $(Split-Path -Leaf $zipPath)`n")
Write-Host "Portable release created."
Write-Host "Folder:   $stageRoot"
Write-Host "ZIP:      $zipPath"
Write-Host "Root:     $(@(Get-ChildItem -LiteralPath $stageRoot | ForEach-Object Name) -join ', ')"
Write-Host "Runtime:  $(@(Get-ChildItem -LiteralPath $runtimeStage -File -Recurse).Count) files in resources\runtime"
Write-Host "GPU ABI:  $gpuPluginAbi"
Write-Host "VC++ CRT: $VcRedistDir"
Write-Host "Audit:    root holds only the 4 expected items; no forbidden items; $assetComparisons same-size game files compared, none identical"
Write-Host ("Size:     {0:N2} MB uncompressed; {1:N2} MB ZIP" -f ($releaseSize / 1MB), ($zip.Length / 1MB))
Write-Host "SHA256:   $zipSha  ($shaPath)"
