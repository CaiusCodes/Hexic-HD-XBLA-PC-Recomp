# Builds the portable Hexic HD PC release in out\release:
#
#   Hexic HD PC\
#     Install Hexic HD.exe          Setup (resources\installer\Install-HexicHD.ps1)
#     README.txt
#     release-manifest.json         bytes + SHA-256 of every file shipped
#     licenses\
#     resources\installer\          Setup script, STFS extractor, menu patcher, play launcher
#     resources\game\               PC runtime copied into Game\ by Setup
#
# The release carries no original game content. Setup builds Game\assets from
# the player's own package; the audit below refuses to package anything that
# looks like game data, debug output or user state.
[CmdletBinding()]
param(
    [string]$BuildPreset = "win-amd64-release",
    [string]$Version = "1.1.0",
    # Folder holding the Visual C++ runtime DLLs to ship; found automatically.
    [string]$VcRedistDir,
    # Extracted game data to compare the release against byte for byte.
    [string]$AssetsDir
)

$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

if ($Version -notmatch '^[A-Za-z0-9._-]+$') {
    throw "Version may contain only letters, numbers, dots, underscores and hyphens."
}

$projectRoot = [System.IO.Path]::GetFullPath((Join-Path -Path $PSScriptRoot -ChildPath ".."))
$buildRoot = Join-Path $projectRoot "out\build\$BuildPreset"
$packagingRoot = Join-Path $projectRoot "packaging"
$releaseRoot = Join-Path $projectRoot "out\release"
$stageRoot = Join-Path $releaseRoot "Hexic HD PC"
$zipPath = Join-Path $releaseRoot "Hexic-HD-PC-$Version.zip"

$runtimeFiles = @("hexic_hd.exe", "rexruntime.dll", "rexgpu-xenos.dll")
$vcRuntimeFiles = @("msvcp140.dll", "msvcp140_atomic_wait.dll", "vcruntime140.dll", "vcruntime140_1.dll")

# --- 1. Inputs ---------------------------------------------------------------
foreach ($file in $runtimeFiles) {
    if (-not (Test-Path -LiteralPath (Join-Path $buildRoot $file) -PathType Leaf)) {
        throw "Build output is missing: $file. Build $BuildPreset first."
    }
}

# A release must never ship a binary older than the source it claims to be.
$exeTime = (Get-Item -LiteralPath (Join-Path $buildRoot "hexic_hd.exe")).LastWriteTimeUtc
$newestSource = Get-ChildItem -LiteralPath (Join-Path $projectRoot "src") -File -Recurse |
    Sort-Object LastWriteTimeUtc -Descending | Select-Object -First 1
if ($newestSource.LastWriteTimeUtc -gt $exeTime) {
    throw "hexic_hd.exe is older than src\$($newestSource.Name). Rebuild before packaging."
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

# --- 2. Native launchers ------------------------------------------------------
& (Join-Path $packagingRoot "Build-Stubs.ps1") -Version $Version
foreach ($stub in @("Install Hexic HD.exe", "Hexic HD.exe")) {
    if (-not (Test-Path -LiteralPath (Join-Path $packagingRoot $stub) -PathType Leaf)) {
        throw "Launcher was not built: $stub"
    }
}

# --- 3. Stage -----------------------------------------------------------------
if (Test-Path -LiteralPath $stageRoot) { Remove-Item -LiteralPath $stageRoot -Recurse -Force }
if (Test-Path -LiteralPath $zipPath) { Remove-Item -LiteralPath $zipPath -Force }

$licensesStage = Join-Path $stageRoot "licenses"
$installerStage = Join-Path $stageRoot "resources\installer"
$gameStage = Join-Path $stageRoot "resources\game"
foreach ($dir in @($stageRoot, $licensesStage, $installerStage, $gameStage)) {
    New-Item -ItemType Directory -Path $dir -Force | Out-Null
}

Copy-Item -LiteralPath (Join-Path $packagingRoot "Install Hexic HD.exe") -Destination $stageRoot
$readme = [System.IO.File]::ReadAllText((Join-Path $packagingRoot "README.txt")).Replace("@VERSION@", $Version)
$readme = $readme -replace "`r?`n", "`r`n"  # Notepad-friendly line endings
[System.IO.File]::WriteAllText((Join-Path $stageRoot "README.txt"), $readme, (New-Object System.Text.UTF8Encoding($false)))

Get-ChildItem -LiteralPath (Join-Path $packagingRoot "licenses") -File |
    ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $licensesStage }

Get-ChildItem -LiteralPath (Join-Path $packagingRoot "resources\installer") -File |
    ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $installerStage }
Copy-Item -LiteralPath (Join-Path $packagingRoot "Hexic HD.exe") -Destination $installerStage
[System.IO.File]::WriteAllText((Join-Path $installerStage "version.txt"), $Version)

foreach ($file in $runtimeFiles) { Copy-Item -LiteralPath (Join-Path $buildRoot $file) -Destination $gameStage }
foreach ($file in $vcRuntimeFiles) { Copy-Item -LiteralPath (Join-Path $VcRedistDir $file) -Destination $gameStage }
Copy-Item -LiteralPath (Join-Path $packagingRoot "hexic_hd.toml") -Destination $gameStage

# --- 4. Audit: nothing from the game package, no debug output, no user state -
$staged = @(Get-ChildItem -LiteralPath $stageRoot -Recurse -Force)
# An installed Game folder must never be packaged (resources\game is the
# runtime payload, so this one is checked at the root only).
if (Test-Path -LiteralPath (Join-Path $stageRoot "Game")) {
    throw "An installed Game folder entered the release."
}
$forbiddenNames = @("assets", "assets_import_tmp", "userdata", "logs", "cache", "highscores.txt",
    "default.xex", "arcadeinfo.xml", "g.xml", "guest_image.bin", "xstr_decompressed.bin", "memdump.bin")
$forbiddenPatterns = @("*.pdb", "*.xex", "*.bin", "*.log", "*.ilk", "*.exp", "*.lib",
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

# --- 5. Manifest ----------------------------------------------------------------
$entries = New-Object System.Collections.Generic.List[object]
foreach ($file in $stagedFiles) {
    $entries.Add([pscustomobject]@{
            Path = $file.FullName.Substring($stageRoot.Length + 1)
            Bytes = $file.Length
            Sha256 = (Get-FileHash -LiteralPath $file.FullName -Algorithm SHA256).Hash
        })
}
$entries.Sort([System.Comparison[object]] { param($a, $b) [string]::CompareOrdinal($a.Path, $b.Path) })

$json = New-Object System.Text.StringBuilder
[void]$json.Append("{`n  `"files`": [`n")
for ($i = 0; $i -lt $entries.Count; $i++) {
    $entry = $entries[$i]
    $path = $entry.Path.Replace('\', '\\').Replace('"', '\"')
    [void]$json.Append("    {`n")
    [void]$json.Append("      `"bytes`": $($entry.Bytes),`n")
    [void]$json.Append("      `"path`": `"$path`",`n")
    [void]$json.Append("      `"sha256`": `"$($entry.Sha256)`"`n")
    [void]$json.Append("    }")
    if ($i -lt $entries.Count - 1) { [void]$json.Append(",") }
    [void]$json.Append("`n")
}
[void]$json.Append("  ]`n}`n")
[System.IO.File]::WriteAllText((Join-Path $stageRoot "release-manifest.json"), $json.ToString(),
    (New-Object System.Text.UTF8Encoding($false)))

# --- 6. Zip ---------------------------------------------------------------------
Add-Type -AssemblyName System.IO.Compression.FileSystem
[System.IO.Compression.ZipFile]::CreateFromDirectory($stageRoot, $zipPath,
    [System.IO.Compression.CompressionLevel]::Optimal, $true)

$releaseSize = ($stagedFiles | Measure-Object -Property Length -Sum).Sum
$zip = Get-Item -LiteralPath $zipPath
Write-Host "Portable release created."
Write-Host "Folder:   $stageRoot"
Write-Host "ZIP:      $zipPath"
Write-Host "Files:    $($entries.Count) + release-manifest.json"
Write-Host "GPU ABI:  $gpuPluginAbi"
Write-Host "VC++ CRT: $VcRedistDir"
Write-Host "Audit:    no forbidden items; $assetComparisons same-size game files compared, none identical"
Write-Host ("Size:     {0:N2} MB uncompressed; {1:N2} MB ZIP" -f ($releaseSize / 1MB), ($zip.Length / 1MB))
Write-Host "SHA256:   $((Get-FileHash -LiteralPath $zipPath -Algorithm SHA256).Hash)"
