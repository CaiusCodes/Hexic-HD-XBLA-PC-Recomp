<#
    Hexic HD PC - Setup

    Started by "Install Hexic HD.exe" through a hidden Windows PowerShell host.
    Installs the PC runtime shipped in resources\game, plus the game data from
    the player's own Xbox 360 package, into a Game folder beside Setup.

    No original game content ships with the release. Everything that ends up in
    Game\assets comes from the package the player selects, and that package is
    only ever opened for reading.

      -PackagePath <file>   preselect a package (the window still opens)
      -Unattended           install -PackagePath without a window; exit code 0/1
      -Extras a,b           with -Unattended: extras to switch on (mnk, fullscreen, shortcut)
      -ShortcutFolder <dir> testing: put the desktop shortcut here instead
#>
[CmdletBinding()]
param(
    [string]$PackagePath,
    [switch]$Unattended,
    [string[]]$Extras = @(),
    [string]$ShortcutFolder
)

$ErrorActionPreference = 'Stop'
Set-StrictMode -Version 2.0

# ------------------------------------------------------------------ paths --
$installerDir = $PSScriptRoot
$resourcesDir = Split-Path -Parent $installerDir
$releaseRoot = Split-Path -Parent $resourcesDir
$runtimeDir = Join-Path $resourcesDir 'game'
$extractorPath = Join-Path $installerDir 'Extract-STFS.ps1'
$patcherPath = Join-Path $installerDir 'Patch-PcMenuText.ps1'
$launcherSource = Join-Path $installerDir 'Hexic HD.exe'
$launcherTarget = Join-Path $releaseRoot 'Hexic HD.exe'
$setupExe = Join-Path $releaseRoot 'Install Hexic HD.exe'
$gameDir = Join-Path $releaseRoot 'Game'
$gameExe = Join-Path $gameDir 'hexic_hd.exe'
$assetsDir = Join-Path $gameDir 'assets'
$stagingDir = Join-Path $gameDir '.setup-import'
$previousAssetsDir = Join-Path $gameDir '.setup-previous-assets'
$progressFile = Join-Path $gameDir '.setup-progress'
$logDir = Join-Path $releaseRoot 'logs'
$logFile = Join-Path $logDir ('installer-{0}.log' -f (Get-Date -Format 'yyyyMMdd-HHmmss'))
$powershellExe = Join-Path $env:SystemRoot 'System32\WindowsPowerShell\v1.0\powershell.exe'

$versionFile = Join-Path $installerDir 'version.txt'
$releaseVersion = 'dev'
if (Test-Path -LiteralPath $versionFile -PathType Leaf) {
    $releaseVersion = (Get-Content -LiteralPath $versionFile -TotalCount 1).Trim()
}

# The port is a static recompilation of one specific build of the game
# program: its code is compiled into hexic_hd.exe, and the package supplies the
# data that build expects. Only a package carrying that exact build works.
$expectedTitleId = [uint32]0x584107D1
$expectedContentType = [uint32]0x000D0000
$expectedXexSha256 = 'EE18728AB4C4B45CC6D55F7917ABBB20B5D700C9410EAD400E2F687D51EFEEE0'
$requiredGameFiles = @('default.xex', 'g.xml', 'arcadeinfo.xml')

# Built from code points so this file stays plain ASCII for PowerShell 5.1.
$dot = [string][char]0x00B7
$ellipsis = [string][char]0x2026
$check = [string][char]0x2713

# ---------------------------------------------------------------- logging --
function Write-Log {
    param([string]$Message)
    try {
        if (-not (Test-Path -LiteralPath $logDir)) {
            New-Item -ItemType Directory -Path $logDir -Force | Out-Null
        }
        $line = '{0}  {1}' -f (Get-Date -Format 'yyyy-MM-dd HH:mm:ss.fff'), $Message
        [System.IO.File]::AppendAllText($logFile, $line + [Environment]::NewLine)
    }
    catch {
        # Logging must never be the reason Setup fails.
    }
}

# ------------------------------------------------------ package inspection --
function Read-UInt32BE {
    param([byte[]]$Bytes, [int]$Offset)
    return ([uint32]$Bytes[$Offset] -shl 24) -bor ([uint32]$Bytes[$Offset + 1] -shl 16) -bor
        ([uint32]$Bytes[$Offset + 2] -shl 8) -bor [uint32]$Bytes[$Offset + 3]
}

# Reads only the STFS header: magic, content type, title ID and display name.
function Get-PackageInfo {
    param([string]$Path)

    $info = @{ Ok = $false; Message = ''; Name = ''; Bytes = [long]0 }
    if ([string]::IsNullOrWhiteSpace($Path) -or -not (Test-Path -LiteralPath $Path -PathType Leaf)) {
        $info.Message = 'The selected file could not be found.'
        return $info
    }

    try {
        $info.Bytes = (Get-Item -LiteralPath $Path).Length
        if ($info.Bytes -lt 0xC000) {
            $info.Message = 'This file is too small to be an Xbox 360 package.'
            return $info
        }

        $header = New-Object byte[] 0x1000
        $stream = [System.IO.File]::Open($Path, [System.IO.FileMode]::Open,
            [System.IO.FileAccess]::Read, [System.IO.FileShare]::Read)
        try {
            [void]$stream.Read($header, 0, $header.Length)
        }
        finally {
            $stream.Dispose()
        }
    }
    catch {
        $info.Message = 'The package could not be read: ' + $_.Exception.Message
        return $info
    }

    $magic = [System.Text.Encoding]::ASCII.GetString($header, 0, 4)
    if (@('LIVE', 'PIRS', 'CON') -notcontains $magic.TrimEnd()) {
        $info.Message = 'This is not an Xbox 360 package. Choose the Hexic HD package file itself.'
        return $info
    }

    $contentType = Read-UInt32BE $header 0x344
    $titleId = Read-UInt32BE $header 0x360
    if ($titleId -ne $expectedTitleId) {
        $info.Message = ('This package is for a different game (title ID {0:X8}). Hexic HD is 584107D1.' -f $titleId)
        return $info
    }
    if ($contentType -ne $expectedContentType) {
        $info.Message = 'This Hexic HD package is not the game itself (it may be a title update, save or theme). Choose the Xbox LIVE Arcade game package.'
        return $info
    }

    $info.Name = [System.Text.Encoding]::BigEndianUnicode.GetString($header, 0x411, 0x80).Trim([char]0).Trim()
    $info.Ok = $true
    return $info
}

# -------------------------------------------------------------- install ---
function Remove-Tree {
    param([string]$Path)
    if (Test-Path -LiteralPath $Path) {
        Remove-Item -LiteralPath $Path -Recurse -Force
    }
}

function Test-GameRunning {
    $running = @(Get-Process -Name 'hexic_hd' -ErrorAction SilentlyContinue | Where-Object {
            try { $_.Path -and $_.Path.StartsWith($gameDir, [StringComparison]::OrdinalIgnoreCase) }
            catch { $false }
        })
    return $running.Count -gt 0
}

# The extractor rewrites "doneBytes|totalBytes|doneFiles|totalFiles".
function Read-ExtractorProgress {
    if (-not (Test-Path -LiteralPath $progressFile -PathType Leaf)) {
        return $null
    }
    try {
        $share = [System.IO.FileShare]::ReadWrite -bor [System.IO.FileShare]::Delete
        $stream = [System.IO.File]::Open($progressFile, [System.IO.FileMode]::Open,
            [System.IO.FileAccess]::Read, $share)
        try {
            $text = (New-Object System.IO.StreamReader($stream)).ReadToEnd()
        }
        finally {
            $stream.Dispose()
        }
        $parts = $text.Split('|')
        if ($parts.Count -ne 4) {
            return $null
        }
        return @{
            Done = [long]$parts[0]; Total = [long]$parts[1]
            Files = [int]$parts[2]; TotalFiles = [int]$parts[3]
        }
    }
    catch {
        # Mid-rewrite; the next poll will get it.
        return $null
    }
}

# Portable builds before this Setup kept saves (and the high-score table)
# beside the game in the folder root. When this release is extracted over one
# of those, carry the saves into Game\ once so nothing is lost.
function Move-LegacyUserData {
    $legacy = Join-Path $releaseRoot 'userdata'
    $target = Join-Path $gameDir 'userdata'
    if ((Test-Path -LiteralPath $legacy -PathType Container) -and -not (Test-Path -LiteralPath $target)) {
        Move-Item -LiteralPath $legacy -Destination $target
        Write-Log 'Moved saves from an earlier portable build into Game\userdata.'
    }
    $legacyConfig = Join-Path $releaseRoot 'hexic_hd.toml'
    $configTarget = Join-Path $gameDir 'hexic_hd.toml'
    if ((Test-Path -LiteralPath $legacyConfig -PathType Leaf) -and -not (Test-Path -LiteralPath $configTarget)) {
        Copy-Item -LiteralPath $legacyConfig -Destination $configTarget
        Write-Log 'Kept the settings from an earlier portable build.'
    }
}

# Installs into Game\. $Report receives (percent, phase, detail) as it goes.
function Invoke-HexicInstall {
    param(
        [Parameter(Mandatory = $true)] [string]$PackagePath,
        [scriptblock]$Report
    )

    $script:lastPhase = ''
    function Step([int]$Percent, [string]$Phase, [string]$Detail) {
        if ($Phase -ne $script:lastPhase) {
            Write-Log ('{0} ({1}%)' -f $Phase, $Percent)
            $script:lastPhase = $Phase
        }
        if ($Report) {
            & $Report $Percent $Phase $Detail
        }
    }

    Write-Log ('Setup {0}: installing from {1}' -f $releaseVersion, $PackagePath)
    foreach ($required in @($extractorPath, $patcherPath, (Join-Path $runtimeDir 'hexic_hd.exe'),
            (Join-Path $runtimeDir 'hexic_hd.toml'))) {
        if (-not (Test-Path -LiteralPath $required -PathType Leaf)) {
            throw ('This download is incomplete ({0} is missing). Extract the whole release again.' -f
                (Split-Path -Leaf $required))
        }
    }

    $package = Get-PackageInfo $PackagePath
    if (-not $package.Ok) {
        throw $package.Message
    }
    if (Test-GameRunning) {
        throw 'Hexic HD is running from this folder. Close the game, then install again.'
    }

    Step 2 'PREPARING' ('Creating the Game folder' + $ellipsis)
    New-Item -ItemType Directory -Path $gameDir -Force | Out-Null
    Remove-Tree $stagingDir
    Remove-Tree $progressFile
    New-Item -ItemType Directory -Path $stagingDir -Force | Out-Null

    $extractOut = Join-Path $gameDir '.setup-extract-out.txt'
    $extractErr = Join-Path $gameDir '.setup-extract-err.txt'
    $process = $null
    $succeeded = $false
    try {
        # 1. Unpack into a staging folder. The extractor opens the package read-only.
        $arguments = '-NoProfile -ExecutionPolicy Bypass -File "{0}" -Path "{1}" -OutputDir "{2}" -ProgressPath "{3}"' -f
            $extractorPath, $PackagePath, $stagingDir, $progressFile
        $process = Start-Process -FilePath $powershellExe -ArgumentList $arguments -WindowStyle Hidden `
            -PassThru -RedirectStandardOutput $extractOut -RedirectStandardError $extractErr
        $null = $process.Handle  # keeps ExitCode readable once it exits (PowerShell 5.1)

        while (-not $process.HasExited) {
            $state = Read-ExtractorProgress
            if ($state -and $state.Total -gt 0) {
                $fraction = [Math]::Min(1.0, $state.Done / [double]$state.Total)
                Step ([int](5 + 80 * $fraction)) 'UNPACKING YOUR GAME DATA' (
                    '{0} of {1} files  {4}  {2:N0} of {3:N0} MB' -f $state.Files, $state.TotalFiles,
                    ($state.Done / 1MB), ($state.Total / 1MB), $dot)
            }
            else {
                Step 5 'UNPACKING YOUR GAME DATA' ('Reading the package file table' + $ellipsis)
            }
            Start-Sleep -Milliseconds 60
        }
        $process.WaitForExit()
        foreach ($captured in @($extractOut, $extractErr)) {
            if (Test-Path -LiteralPath $captured) {
                Get-Content -LiteralPath $captured | ForEach-Object { Write-Log ('  extractor: ' + $_) }
            }
        }
        if ($process.ExitCode -ne 0) {
            throw ('The package could not be unpacked (extractor exit code {0}). The file may be damaged or incomplete.' -f
                $process.ExitCode)
        }

        # 2. Check it is the build this port was recompiled from.
        Step 87 'CHECKING THE GAME DATA' ('Verifying the unpacked files' + $ellipsis)
        foreach ($relative in $requiredGameFiles) {
            if (-not (Test-Path -LiteralPath (Join-Path $stagingDir $relative) -PathType Leaf)) {
                throw ('The package unpacked, but {0} is missing from it. The package may be damaged.' -f $relative)
            }
        }
        $xexHash = (Get-FileHash -LiteralPath (Join-Path $stagingDir 'default.xex') -Algorithm SHA256).Hash
        Write-Log ('default.xex SHA-256 ' + $xexHash)
        if ($xexHash -ne $expectedXexSha256) {
            throw ('This Hexic HD package carries a different build of the game program than the one this port was made from, so it cannot be used. Nothing was changed. (default.xex SHA-256 {0})' -f $xexHash)
        }

        # 3. PC menu labels: Achievements -> PC Settings, Xbox Dashboard -> Quit Hexic.
        Step 90 'PREPARING THE PC MENUS' ('Relabelling the Xbox-only menu entries' + $ellipsis)
        & $patcherPath -AssetsPath $stagingDir *>&1 | ForEach-Object { Write-Log ('  menus: ' + $_) }

        # 4. The PC runtime. Settings are only written when missing, so a
        # reinstall keeps the player's options.
        Step 93 'INSTALLING HEXIC HD' ('Copying the PC runtime' + $ellipsis)
        Move-LegacyUserData
        Get-ChildItem -LiteralPath $runtimeDir -File | Where-Object { $_.Name -ne 'hexic_hd.toml' } |
            ForEach-Object { Copy-Item -LiteralPath $_.FullName -Destination $gameDir -Force }
        $configTarget = Join-Path $gameDir 'hexic_hd.toml'
        if (Test-Path -LiteralPath $configTarget) {
            Write-Log 'Kept the existing hexic_hd.toml.'
        }
        else {
            Copy-Item -LiteralPath (Join-Path $runtimeDir 'hexic_hd.toml') -Destination $configTarget
        }

        # 5. Swap the game data in, restoring the previous copy if the move fails.
        Step 97 'INSTALLING HEXIC HD' ('Moving the game data into place' + $ellipsis)
        Remove-Tree $previousAssetsDir
        if (Test-Path -LiteralPath $assetsDir) {
            Move-Item -LiteralPath $assetsDir -Destination $previousAssetsDir
        }
        try {
            Move-Item -LiteralPath $stagingDir -Destination $assetsDir
        }
        catch {
            if ((Test-Path -LiteralPath $previousAssetsDir) -and -not (Test-Path -LiteralPath $assetsDir)) {
                Move-Item -LiteralPath $previousAssetsDir -Destination $assetsDir
            }
            throw
        }
        Remove-Tree $previousAssetsDir
        New-Item -ItemType Directory -Path (Join-Path $gameDir 'userdata') -Force | Out-Null

        # 6. The play button beside Setup.
        if (Test-Path -LiteralPath $launcherSource -PathType Leaf) {
            Copy-Item -LiteralPath $launcherSource -Destination $launcherTarget -Force
        }

        Step 100 'HEXIC HD IS READY' 'Installed in the Game folder.'
        $succeeded = $true
        return $package
    }
    finally {
        if ($process -and -not $process.HasExited) {
            Stop-Process -Id $process.Id -Force -ErrorAction SilentlyContinue
        }
        Remove-Tree $progressFile
        Remove-Tree $extractOut
        Remove-Tree $extractErr
        if (-not $succeeded) {
            Remove-Tree $stagingDir
        }
    }
}

function Start-Game {
    if (Test-Path -LiteralPath $gameExe -PathType Leaf) {
        Start-Process -FilePath $gameExe -WorkingDirectory $gameDir
    }
}

# ----------------------------------------------------------------- extras --
# Optional features offered after the install. Every one is off unless the
# player ticks it. Game settings are keys in Game\hexic_hd.toml, which the game
# reads when it starts; the desktop shortcut is the only extra Setup applies
# itself. Adding an extra later means one entry here (and, for a game feature,
# the setting it controls).
$configPath = Join-Path $gameDir 'hexic_hd.toml'
$shortcutName = 'Hexic HD.lnk'
$extraDefinitions = @(
    @{ Id = 'mnk'; Title = 'Keyboard controls'; Short = 'Keyboard'
        Detail = 'Play without a controller: arrows move, Space and Shift act as A and B.'; Setting = 'mnk_mode' },
    @{ Id = 'fullscreen'; Title = 'Start in fullscreen'; Short = 'Fullscreen'
        Detail = 'Switch at any time from PC Settings on the main menu.'; Setting = 'fullscreen' },
    @{ Id = 'shortcut'; Title = 'Desktop shortcut'; Short = 'Desktop shortcut'
        Detail = 'Adds a Hexic HD icon to your desktop. It stops working if you move this folder.'; Setting = $null }
)

function Get-ShortcutPath {
    $folder = if ($ShortcutFolder) { $ShortcutFolder } else { [Environment]::GetFolderPath('Desktop') }
    return Join-Path $folder $shortcutName
}

function Get-ConfigValue([string]$Key) {
    if (-not (Test-Path -LiteralPath $configPath -PathType Leaf)) { return $null }
    foreach ($line in [System.IO.File]::ReadAllLines($configPath)) {
        if ($line -match ('^\s*' + [regex]::Escape($Key) + '\s*=\s*(.+?)\s*$')) { return $Matches[1].Trim('"') }
    }
    return $null
}

# Replaces the key's line, or appends it; every other line is left as it was.
function Set-ConfigValue([string]$Key, [string]$Value) {
    $lines = New-Object System.Collections.Generic.List[string]
    if (Test-Path -LiteralPath $configPath -PathType Leaf) {
        $lines.AddRange([string[]][System.IO.File]::ReadAllLines($configPath))
    }
    $pattern = '^\s*' + [regex]::Escape($Key) + '\s*='
    $found = $false
    for ($i = 0; $i -lt $lines.Count; $i++) {
        if ($lines[$i] -match $pattern) { $lines[$i] = "$Key = $Value"; $found = $true }
    }
    if (-not $found) { $lines.Add("$Key = $Value") }
    [System.IO.File]::WriteAllLines($configPath, $lines, (New-Object System.Text.UTF8Encoding($false)))
}

# True only for a shortcut that points at this install's play button, so an
# unrelated "Hexic HD" shortcut is never touched.
function Test-OurShortcut {
    $path = Get-ShortcutPath
    if (-not (Test-Path -LiteralPath $path -PathType Leaf)) { return $false }
    try {
        $shell = New-Object -ComObject WScript.Shell
        return [string]::Equals($shell.CreateShortcut($path).TargetPath, $launcherTarget,
            [StringComparison]::OrdinalIgnoreCase)
    }
    catch {
        return $false
    }
}

function Get-ExtraState([string]$Id) {
    $def = $extraDefinitions | Where-Object { $_.Id -eq $Id }
    if ($def.Setting) { return (Get-ConfigValue $def.Setting) -eq 'true' }
    return (Test-OurShortcut)
}

# $Chosen holds the ids of the ticked extras. Every extra is written, so
# unticking one turns it back off.
function Set-Extras([string[]]$Chosen) {
    foreach ($def in $extraDefinitions) {
        $on = $Chosen -contains $def.Id
        if ($def.Setting) {
            Set-ConfigValue $def.Setting $(if ($on) { 'true' } else { 'false' })
        }
        elseif ($def.Id -eq 'shortcut') {
            $path = Get-ShortcutPath
            if ($on) {
                $shell = New-Object -ComObject WScript.Shell
                $link = $shell.CreateShortcut($path)
                $link.TargetPath = $launcherTarget
                $link.WorkingDirectory = $releaseRoot
                $link.IconLocation = $launcherTarget + ',0'
                $link.Description = 'Hexic HD (XBLA PC port)'
                $link.Save()
            }
            elseif (Test-OurShortcut) {
                Remove-Item -LiteralPath $path -Force
            }
        }
        Write-Log ('Extra {0}: {1}' -f $def.Id, $(if ($on) { 'on' } else { 'off' }))
    }
}

# ------------------------------------------------------------ unattended --
if ($Unattended) {
    if ([string]::IsNullOrWhiteSpace($PackagePath)) {
        Write-Log 'Unattended install needs -PackagePath.'
        exit 2
    }
    try {
        [void](Invoke-HexicInstall -PackagePath $PackagePath)
        Write-Log 'Install finished.'
        # From a command line "-Extras a,b" arrives as one string.
        $chosen = @($Extras | ForEach-Object { $_ -split ',' } | ForEach-Object { $_.Trim() } | Where-Object { $_ })
        if ($chosen.Count -gt 0) { Set-Extras $chosen }
        exit 0
    }
    catch {
        Write-Log ('FAILED: ' + $_.Exception.Message)
        [Console]::Error.WriteLine($_.Exception.Message)
        exit 1
    }
}

# --------------------------------------------------------------- window ---
Add-Type -AssemblyName System.Windows.Forms
Add-Type -AssemblyName System.Drawing
Add-Type -Namespace HexicSetup -Name Native -MemberDefinition @'
[DllImport("user32.dll")] public static extern bool SetProcessDPIAware();
[DllImport("user32.dll")] public static extern bool ReleaseCapture();
[DllImport("user32.dll")] public static extern IntPtr SendMessage(IntPtr hWnd, int msg, IntPtr wParam, IntPtr lParam);
'@
[void][HexicSetup.Native]::SetProcessDPIAware()
[System.Windows.Forms.Application]::EnableVisualStyles()

# Layout is written in 96-DPI units and scaled, so the window stays sharp on
# high-DPI displays instead of being bitmap-stretched by Windows.
$probe = [System.Drawing.Graphics]::FromHwnd([IntPtr]::Zero)
$script:scale = $probe.DpiX / 96.0
$probe.Dispose()
function Px([double]$Value) { return [int][Math]::Round($Value * $script:scale) }
function Color([string]$Hex) { return [System.Drawing.ColorTranslator]::FromHtml($Hex) }
function Alpha([int]$A, [string]$Hex) { return [System.Drawing.Color]::FromArgb($A, (Color $Hex)) }
function Mix($A, $B, [double]$T) {
    $ca = if ($A -is [string]) { Color $A } else { $A }
    $cb = if ($B -is [string]) { Color $B } else { $B }
    return [System.Drawing.Color]::FromArgb(
        [int]($ca.R + ($cb.R - $ca.R) * $T), [int]($ca.G + ($cb.G - $ca.G) * $T), [int]($ca.B + ($cb.B - $ca.B) * $T))
}

# The Hexic HD title screen, rebuilt from primitives (no game artwork): a
# black field of slate hexagons, a pearl-silver bezel, a dark card with a
# violet glow, an indigo honeycomb strip carrying the cyan SCORE-style bar, and
# a white-to-periwinkle panel. Jewel hexagons in the game's piece colours
# stand in for checkboxes and decoration.
$palette = @{
    Ink = '#15132E'; Soft = '#2E2C4E'; Muted = '#55537A'; Violet = '#5B3FD6'
    Cyan = '#22D4F0'; CyanDeep = '#0C5E96'; Ok = '#1B7F36'; Bad = '#C42837'
}
$jewels = @('#E8303A', '#F59A1E', '#F5D73A', '#3CC84A', '#2E7CF0', '#9A3FE0')
$W = 720
$H = 560
$footerText = 'Title ID 584107D1'

# Geometry (96-DPI units).
$bezel = @{ X = 44; Y = 12; W = 632; H = 536; R = 34 }
$card = @{ X = 62; Y = 92; W = 596; H = 440; R = 28 }
$pill = @{ X = 90; Y = 109; W = 540; H = 28 }
$panel = @{ X = 74; Y = 152; W = 572; H = 368; R = 20 }
$barBox = @{ X = 98; Y = 410; W = 524; H = 12 }
$fieldBox = @{ X = 98; Y = 254; W = 380; H = 34 }
$extrasTop = 208
$rowPitch = 42

function New-RoundedPath([single]$X, [single]$Y, [single]$Width, [single]$Height, [single]$Radius) {
    $path = New-Object System.Drawing.Drawing2D.GraphicsPath
    $d = [Math]::Max([single]1, [Math]::Min($Radius * 2, [Math]::Min($Width, $Height)))
    $path.AddArc($X, $Y, $d, $d, 180, 90)
    $path.AddArc($X + $Width - $d, $Y, $d, $d, 270, 90)
    $path.AddArc($X + $Width - $d, $Y + $Height - $d, $d, $d, 0, 90)
    $path.AddArc($X, $Y + $Height - $d, $d, $d, 90, 90)
    $path.CloseFigure()
    return , $path
}

# Pointy-top hexagon, like the game's pieces.
function New-HexPath([double]$Cx, [double]$Cy, [double]$R) {
    $points = New-Object 'System.Drawing.PointF[]' 6
    for ($i = 0; $i -lt 6; $i++) {
        $a = [Math]::PI / 180 * (60 * $i - 90)
        $points[$i] = New-Object System.Drawing.PointF(($Cx + $R * [Math]::Cos($a)), ($Cy + $R * [Math]::Sin($a)))
    }
    $path = New-Object System.Drawing.Drawing2D.GraphicsPath
    $path.AddPolygon($points)
    return , $path
}

# Vertical multi-stop gradient. The rectangle is padded by a pixel because
# GDI+ wraps the first colour onto the last row otherwise.
function New-Blend([double]$X, [double]$Y, [double]$Width, [double]$Height, [object[]]$Colors, [single[]]$Positions, [single]$Angle = 90) {
    $rect = New-Object System.Drawing.RectangleF(($X - 1), ($Y - 1), ($Width + 2), ($Height + 2))
    $resolved = [System.Drawing.Color[]]@($Colors | ForEach-Object { if ($_ -is [string]) { Color $_ } else { $_ } })
    $brush = New-Object System.Drawing.Drawing2D.LinearGradientBrush($rect, $resolved[0], $resolved[-1], $Angle)
    $blend = New-Object System.Drawing.Drawing2D.ColorBlend($resolved.Count)
    $blend.Colors = $resolved
    $blend.Positions = $Positions
    $brush.InterpolationColors = $blend
    return $brush
}

function Paint-Jewel($g, [double]$Cx, [double]$Cy, [double]$R, [string]$Hex) {
    $path = New-HexPath $Cx $Cy $R
    $fill = New-Blend ($Cx - $R) ($Cy - $R) ($R * 2) ($R * 2) @((Mix $Hex '#FFFFFF' 0.5), $Hex, (Mix $Hex '#000000' 0.45)) @(0, 0.5, 1)
    $g.FillPath($fill, $path)
    $gloss = New-HexPath $Cx ($Cy - $R * 0.3) ($R * 0.6)
    $shine = New-Object System.Drawing.Drawing2D.LinearGradientBrush(
        (New-Object System.Drawing.RectangleF(($Cx - $R), ($Cy - $R), ($R * 2), ($R * 1.1))),
        (Alpha 170 '#FFFFFF'), (Alpha 0 '#FFFFFF'), [single]90)
    $g.FillPath($shine, $gloss)
    $pen = New-Object System.Drawing.Pen((Mix $Hex '#000000' 0.6), [single][Math]::Max(1, $R / 10))
    $g.DrawPath($pen, $path)
    foreach ($o in @($pen, $shine, $gloss, $fill, $path)) { $o.Dispose() }
}

# The first installed family wins; GDI+ silently substitutes a missing one,
# so the returned name is checked.
function New-PixelFont([string[]]$Families, [single]$Pixels, [System.Drawing.FontStyle]$Style = [System.Drawing.FontStyle]::Regular) {
    foreach ($family in $Families) {
        try {
            $font = New-Object System.Drawing.Font($family, $Pixels, $Style, [System.Drawing.GraphicsUnit]::Pixel)
            if ($font.Name -eq $family) { return $font }
            $font.Dispose()
        }
        catch { }
    }
    return New-Object System.Drawing.Font('Segoe UI', $Pixels, $Style, [System.Drawing.GraphicsUnit]::Pixel)
}

# Painted text runs under the DPI scale transform, so it is sized in 96-DPI
# pixels rather than points, which Windows would scale a second time.
$script:logoFont = New-PixelFont @('Bahnschrift Condensed', 'Bahnschrift SemiLight Condensed', 'Arial Narrow', 'Segoe UI Light') 40
$script:hdFont = New-PixelFont @('Bahnschrift SemiBold Condensed', 'Bahnschrift SemiBold', 'Segoe UI Black') 20
$script:tagFont = New-PixelFont @('Segoe UI Semibold') ([single](8.5 * 96 / 72))
$script:pillFont = New-PixelFont @('Segoe UI Semibold') ([single](8.5 * 96 / 72))
$script:buttonFont = New-PixelFont @('Segoe UI Semibold') ([single](10 * 96 / 72))
$script:checkFont = New-PixelFont @('Segoe UI') 14 ([System.Drawing.FontStyle]::Bold)
$script:centerFormat = New-Object System.Drawing.StringFormat
$script:centerFormat.Alignment = [System.Drawing.StringAlignment]::Center
$script:centerFormat.LineAlignment = [System.Drawing.StringAlignment]::Center
$script:rightFormat = New-Object System.Drawing.StringFormat
$script:rightFormat.Alignment = [System.Drawing.StringAlignment]::Far

# "HEXIC" in black chrome with a violet edge light and a tall centre X, and a
# cyan "HD" tucked in after it - drawn as outlines from a system font.
function Draw-Logo($g, [single]$X, [single]$Bottom) {
    $logo = New-Object System.Drawing.Drawing2D.GraphicsPath
    $format = [System.Drawing.StringFormat]::GenericTypographic
    $cursor = $X
    foreach ($piece in @(@('HE', 54, 0, 2), @('X', 84, 10, 2), @('IC', 54, 0, 9))) {
        $part = New-Object System.Drawing.Drawing2D.GraphicsPath
        $part.AddString($piece[0], $script:logoFont.FontFamily, [int]$script:logoFont.Style, [single]$piece[1],
            (New-Object System.Drawing.PointF(0, 0)), $format)
        $b = $part.GetBounds()
        $m = New-Object System.Drawing.Drawing2D.Matrix
        $m.Translate([single]($cursor - $b.X), [single]($Bottom + $piece[2] - ($b.Y + $b.Height)))
        $part.Transform($m)
        $logo.AddPath($part, $false)
        $cursor += $b.Width + $piece[3]
        $m.Dispose(); $part.Dispose()
    }
    $lb = $logo.GetBounds()
    $glow = New-Object System.Drawing.Pen((Alpha 55 '#7B5CFF'), [single]4)
    $glow.LineJoin = [System.Drawing.Drawing2D.LineJoin]::Round
    $g.DrawPath($glow, $logo)
    $chrome = New-Blend $lb.X $lb.Y $lb.Width $lb.Height @('#7A7A92', '#24243A', '#000000', '#3A3A54') @(0, 0.46, 0.54, 1)
    $g.FillPath($chrome, $logo)
    $edge = New-Object System.Drawing.Pen((Color '#8D70FF'), [single]1.2)
    $g.DrawPath($edge, $logo)

    $hd = New-Object System.Drawing.Drawing2D.GraphicsPath
    $hd.AddString('HD', $script:hdFont.FontFamily, [int]$script:hdFont.Style, [single]28,
        (New-Object System.Drawing.PointF(0, 0)), $format)
    $hb = $hd.GetBounds()
    $m = New-Object System.Drawing.Drawing2D.Matrix
    $m.Translate([single]($cursor - $hb.X), [single]($Bottom + 10 - ($hb.Y + $hb.Height)))
    $hd.Transform($m)
    $hb = $hd.GetBounds()
    $cyan = New-Blend $hb.X $hb.Y $hb.Width $hb.Height @('#C8F8FF', '#38C4F2', '#0A6CB4') @(0, 0.5, 1)
    $g.FillPath($cyan, $hd)
    $hdEdge = New-Object System.Drawing.Pen((Color '#062A48'), [single]1.1)
    $g.DrawPath($hdEdge, $hd)
    foreach ($o in @($hdEdge, $cyan, $m, $hd, $edge, $chrome, $glow, $logo)) { $o.Dispose() }
}

# Everything that never changes is drawn once into a bitmap at the real pixel
# size; Paint then only adds the pill, fields, bar, checkboxes and buttons.
function New-Backdrop {
    $bitmap = New-Object System.Drawing.Bitmap((Px $W), (Px $H))
    $g = [System.Drawing.Graphics]::FromImage($bitmap)
    $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    $g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAliasGridFit
    $g.ScaleTransform([single]$script:scale, [single]$script:scale)
    $g.Clear([System.Drawing.Color]::Black)

    # Slate hexagons scattered down both sides of the black field.
    $r = 21.0
    $stepX = [Math]::Sqrt(3) * $r
    for ($row = 0; $row -lt 20; $row++) {
        for ($col = 0; $col -lt 21; $col++) {
            $cx = $col * $stepX + $(if ($row % 2) { $stepX / 2 } else { 0 }) - 12
            $cy = $row * 1.5 * $r - 8
            if ($cx -gt 70 -and $cx -lt 650) { continue }
            $n = ($row * 7 + $col * 13 + ($row * $col) % 5) % 9
            if ($n -lt 3) { continue }
            $hex = New-HexPath $cx $cy ($r * 0.9)
            $shade = 0.25 + 0.09 * ($n - 3)
            $fill = New-Blend ($cx - $r) ($cy - $r) ($r * 2) ($r * 2) @((Mix '#101020' '#9A9AC6' $shade), (Mix '#05050C' '#3A3A5C' $shade)) @(0, 1)
            $g.FillPath($fill, $hex)
            $fill.Dispose(); $hex.Dispose()
        }
    }

    # Pearl-silver bezel.
    $bez = New-RoundedPath $bezel.X $bezel.Y $bezel.W $bezel.H $bezel.R
    $silver = New-Blend $bezel.X $bezel.Y $bezel.W $bezel.H @('#F6F6FA', '#DADAE4', '#C4C4D2', '#A8A8BA') @(0, 0.2, 0.62, 1)
    $g.FillPath($silver, $bez)
    $rim = New-Object System.Drawing.Pen((Color '#7E7E98'), [single]1.2)
    $g.DrawPath($rim, $bez)
    $shineRim = New-RoundedPath ($bezel.X + 2) ($bezel.Y + 2) ($bezel.W - 4) ($bezel.H - 4) ($bezel.R - 2)
    $shinePen = New-Object System.Drawing.Pen((Alpha 170 '#FFFFFF'), [single]1)
    $g.DrawPath($shinePen, $shineRim)
    foreach ($o in @($shinePen, $shineRim, $rim, $silver, $bez)) { $o.Dispose() }

    Draw-Logo $g 76 74
    $tagBrush = New-Object System.Drawing.SolidBrush((Color '#3E3C5E'))
    $g.DrawString('XBLA PC PORT', $script:tagFont, $tagBrush, (New-Object System.Drawing.RectangleF(420, 34, 226, 18)), $script:rightFormat)
    $g.DrawString(('SETUP  ' + $dot + '  V' + $releaseVersion.ToUpperInvariant()), $script:tagFont, $tagBrush,
        (New-Object System.Drawing.RectangleF(420, 52, 226, 18)), $script:rightFormat)
    $tagBrush.Dispose()

    # Dark card with a violet glow.
    $cardPath = New-RoundedPath $card.X $card.Y $card.W $card.H $card.R
    foreach ($glowStep in @(@(9, 30), @(5, 70), @(2.2, 230))) {
        $pen = New-Object System.Drawing.Pen((Alpha $glowStep[1] '#6A48FF'), [single]$glowStep[0])
        $g.DrawPath($pen, $cardPath)
        $pen.Dispose()
    }
    $dark = New-Object System.Drawing.SolidBrush((Color '#0B0A1C'))
    $g.FillPath($dark, $cardPath)
    $dark.Dispose()

    # Indigo honeycomb strip across the top of the card.
    $g.SetClip($cardPath)
    $strip = New-Blend $card.X $card.Y $card.W 58 @('#4C38CC', '#2A1E86', '#1A1258') @(0, 0.6, 1)
    $g.FillRectangle($strip, [single]$card.X, [single]$card.Y, [single]$card.W, [single]58)
    $strip.Dispose()
    $comb = New-Object System.Drawing.Pen((Alpha 80 '#A898FF'), [single]1)
    $hr = 8.0
    $hx = [Math]::Sqrt(3) * $hr
    for ($row = 0; $row -lt 6; $row++) {
        for ($col = 0; $col -lt 40; $col++) {
            $hex = New-HexPath ($card.X + $col * $hx + $(if ($row % 2) { $hx / 2 } else { 0 })) ($card.Y + $row * 1.5 * $hr) $hr
            $g.DrawPath($comb, $hex)
            $hex.Dispose()
        }
    }
    $comb.Dispose()
    $g.ResetClip()
    $cardPath.Dispose()

    # The SCORE-style bar's dark well.
    $well = New-RoundedPath $pill.X $pill.Y $pill.W $pill.H 14
    $wellFill = New-Object System.Drawing.SolidBrush((Color '#05051A'))
    $g.FillPath($wellFill, $well)
    $wellPen = New-Object System.Drawing.Pen((Alpha 200 '#000000'), [single]1.5)
    $g.DrawPath($wellPen, $well)
    foreach ($o in @($wellPen, $wellFill, $well)) { $o.Dispose() }

    # White-to-periwinkle panel.
    $panelPath = New-RoundedPath $panel.X $panel.Y $panel.W $panel.H $panel.R
    $pearl = New-Blend $panel.X $panel.Y $panel.W $panel.H @('#FFFFFF', '#E6E6F3', '#B6B6DD', '#9C9CCF') @(0, 0.34, 0.78, 1)
    $g.FillPath($pearl, $panelPath)
    $panelPen = New-Object System.Drawing.Pen((Color '#6A4FE0'), [single]1.6)
    $g.DrawPath($panelPen, $panelPath)
    foreach ($o in @($panelPen, $pearl, $panelPath)) { $o.Dispose() }

    $outline = New-RoundedPath 0.5 0.5 ($W - 1) ($H - 1) 18
    $outlinePen = New-Object System.Drawing.Pen((Alpha 150 '#6A48FF'), [single]1)
    $g.DrawPath($outlinePen, $outline)
    $outlinePen.Dispose(); $outline.Dispose()

    $g.Dispose()
    return $bitmap
}

$form = New-Object System.Windows.Forms.Form
$form.Text = 'Hexic HD Setup'
$form.FormBorderStyle = [System.Windows.Forms.FormBorderStyle]::None
$form.StartPosition = [System.Windows.Forms.FormStartPosition]::CenterScreen
$form.AutoScaleMode = [System.Windows.Forms.AutoScaleMode]::None
$form.ClientSize = New-Object System.Drawing.Size((Px $W), (Px $H))
$form.BackColor = [System.Drawing.Color]::Black
$form.KeyPreview = $true
$form.AllowDrop = $true
$form.ShowInTaskbar = $true
$form.GetType().GetProperty('DoubleBuffered', [Reflection.BindingFlags]'NonPublic,Instance').SetValue($form, $true, $null)
$form.Region = New-Object System.Drawing.Region((New-RoundedPath 0 0 (Px $W) (Px $H) (Px 18)))
if (Test-Path -LiteralPath $setupExe -PathType Leaf) {
    try { $form.Icon = [System.Drawing.Icon]::ExtractAssociatedIcon($setupExe) } catch { }
}

$fontTitle = New-Object System.Drawing.Font('Segoe UI Semibold', 15)
$fontCaps = New-Object System.Drawing.Font('Segoe UI Semibold', 8.25)
$fontBody = New-Object System.Drawing.Font('Segoe UI', 10)
$fontSmall = New-Object System.Drawing.Font('Segoe UI', 9)
$fontFoot = New-Object System.Drawing.Font('Segoe UI', 8)
$fontRowTitle = New-Object System.Drawing.Font('Segoe UI Semibold', 10)
$fontRowDetail = New-Object System.Drawing.Font('Segoe UI', 8.5)

function New-Label([string]$Text, [double]$X, [double]$Y, [double]$Width, [double]$Height,
    [System.Drawing.Font]$Font, [string]$ColorHex) {
    $label = New-Object System.Windows.Forms.Label
    $label.AutoSize = $false
    $label.Location = New-Object System.Drawing.Point((Px $X), (Px $Y))
    $label.Size = New-Object System.Drawing.Size((Px $Width), (Px $Height))
    $label.Font = $Font
    $label.ForeColor = Color $ColorHex
    $label.BackColor = [System.Drawing.Color]::Transparent
    $label.UseMnemonic = $false
    $label.Text = $Text
    $form.Controls.Add($label)
    return $label
}

# Buttons are painted onto the form - glossy pills, like the game's own menus -
# and hit-tested in 96-DPI units.
$script:buttons = @{}
$script:buttonOrder = @('choose', 'extras', 'left', 'right')
$script:hoverId = $null
$script:pressId = $null
function New-PaintedButton([string]$Id, [double]$X, [double]$Y, [double]$Width, [double]$Height, [string]$Text, [string]$Style) {
    $script:buttons[$Id] = @{ X = $X; Y = $Y; W = $Width; H = $Height; Text = $Text; Style = $Style; Visible = $true }
}
New-PaintedButton 'choose' 490 254 132 34 ('Choose file' + $ellipsis) 'secondary'
New-PaintedButton 'extras' 262 470 112 36 'Change extras' 'secondary'
New-PaintedButton 'left' 386 470 112 36 'Close' 'secondary'
New-PaintedButton 'right' 510 470 112 36 'Install game' 'disabled'

function Invalidate-Box([double]$X, [double]$Y, [double]$Width, [double]$Height) {
    $form.Invalidate((New-Object System.Drawing.Rectangle((Px ($X - 4)), (Px ($Y - 4)), (Px ($Width + 8)), (Px ($Height + 8)))))
}
function Invalidate-Button([string]$Id) {
    if ($Id -and $script:buttons.ContainsKey($Id)) {
        $b = $script:buttons[$Id]
        Invalidate-Box $b.X $b.Y $b.W $b.H
    }
}
function Set-Button([string]$Id, [string]$Text, [string]$Style, [bool]$Visible = $true) {
    $b = $script:buttons[$Id]
    if ($Text) { $b.Text = $Text }
    if ($Style) { $b.Style = $Style }
    $b.Visible = $Visible
    Invalidate-Button $Id
}
function Find-Button([double]$X, [double]$Y) {
    foreach ($id in $script:buttonOrder) {
        $b = $script:buttons[$id]
        if ($b.Visible -and $X -ge $b.X -and $X -le ($b.X + $b.W) -and $Y -ge $b.Y -and $Y -le ($b.Y + $b.H)) { return $id }
    }
    return $null
}

function Paint-Button($g, [string]$Id) {
    $b = $script:buttons[$Id]
    if (-not $b.Visible) { return }
    $look = switch ($b.Style) {
        'primary' { @{ Stops = @('#A8F07E', '#4CC23E', '#2A9A2C'); Edge = '#1D6E22'; Text = '#FFFFFF'; Shadow = '#1A5A1E' } }
        'disabled' { @{ Stops = @('#E4E4EE', '#D2D2E0', '#C4C4D4'); Edge = '#A8A8C0'; Text = '#8C8AA8'; Shadow = $null } }
        default { @{ Stops = @('#FFFFFF', '#E2E2EE', '#BDBDD2'); Edge = '#7676A0'; Text = '#1E1C3A'; Shadow = $null } }
    }
    $path = New-RoundedPath $b.X $b.Y $b.W $b.H ($b.H / 2)
    $fill = New-Blend $b.X $b.Y $b.W $b.H $look.Stops @(0, 0.5, 1)
    $g.FillPath($fill, $path)
    $gloss = New-RoundedPath ($b.X + 3) ($b.Y + 2) ($b.W - 6) ($b.H * 0.45) ($b.H * 0.22)
    $shine = New-Object System.Drawing.SolidBrush((Alpha 70 '#FFFFFF'))
    $g.FillPath($shine, $gloss)
    if ($b.Style -ne 'disabled' -and -not $script:busy) {
        if ($script:pressId -eq $Id) {
            $shade = New-Object System.Drawing.SolidBrush((Alpha 40 '#000000')); $g.FillPath($shade, $path); $shade.Dispose()
        }
        elseif ($script:hoverId -eq $Id) {
            $shade = New-Object System.Drawing.SolidBrush((Alpha 55 '#FFFFFF')); $g.FillPath($shade, $path); $shade.Dispose()
        }
    }
    $pen = New-Object System.Drawing.Pen((Color $look.Edge), [single]1.2)
    $g.DrawPath($pen, $path)
    $rect = New-Object System.Drawing.RectangleF([single]$b.X, [single]$b.Y, [single]$b.W, [single]$b.H)
    if ($look.Shadow) {
        $shadow = New-Object System.Drawing.SolidBrush((Color $look.Shadow))
        $g.DrawString($b.Text, $script:buttonFont, $shadow,
            (New-Object System.Drawing.RectangleF([single]$b.X, [single]($b.Y + 1), [single]$b.W, [single]$b.H)), $script:centerFormat)
        $shadow.Dispose()
    }
    $textBrush = New-Object System.Drawing.SolidBrush((Color $look.Text))
    $g.DrawString($b.Text, $script:buttonFont, $textBrush, $rect, $script:centerFormat)
    foreach ($o in @($textBrush, $pen, $shine, $gloss, $fill, $path)) { $o.Dispose() }
}

# Shared by every page.
$lblTitle = New-Label 'Install your game' 98 164 420 32 $fontTitle $palette.Ink
$lblFoot = New-Label $footerText 98 480 150 18 $fontFoot $palette.Muted

# Package page.
$lblPkgCaps = New-Label 'GAME PACKAGE' 98 206 300 18 $fontCaps $palette.Violet
$lblPkgHint = New-Label 'Select your legally obtained Xbox 360 Hexic HD package' 98 224 520 22 $fontBody $palette.Soft
$lblPath = New-Label 'No file selected' 106 255 366 32 $fontSmall $palette.Muted
$lblPath.TextAlign = [System.Drawing.ContentAlignment]::MiddleLeft
$lblPath.AutoEllipsis = $true
$lblPath.Cursor = [System.Windows.Forms.Cursors]::Hand
$lblPkgStatus = New-Label 'You can also drag the package onto this window.' 98 294 524 34 $fontSmall $palette.Muted
$lblNote1 = New-Label 'Hexic installs beside Setup in the Game folder. Saves and high scores stay inside it.' 112 336 510 20 $fontSmall $palette.Soft
$lblNote2 = New-Label 'Your original package stays untouched. No game assets are included.' 112 358 510 20 $fontSmall $palette.Soft
$lblPhase = New-Label '' 98 388 524 18 $fontCaps $palette.Violet
# Live counts sit right-aligned on the phase line while installing. Kept in
# front of the phase label and hidden otherwise, so a long phase message is
# never covered.
$lblStats = New-Label '' 322 388 300 18 $fontSmall $palette.Muted
$lblStats.TextAlign = [System.Drawing.ContentAlignment]::TopRight
$lblStats.Visible = $false
$lblStats.BringToFront()
$lblDetail = New-Label '' 98 428 524 18 $fontSmall $palette.Muted
$packageControls = @($lblPkgCaps, $lblPkgHint, $lblPath, $lblPkgStatus, $lblNote1, $lblNote2, $lblPhase, $lblDetail)

# Extras page: a painted jewel checkbox, a title and a one-line explanation
# per extra. Clicking any of the three toggles it.
$script:extraRows = New-Object System.Collections.Generic.List[object]
$toggleExtra = {
    param($sender, $e)
    $row = $script:extraRows[[int]$sender.Tag]
    $row.On = -not $row.On
    Invalidate-Box 96 ($row.Y - 2) 28 30
}
for ($i = 0; $i -lt $extraDefinitions.Count; $i++) {
    $rowY = $extrasTop + $i * $rowPitch
    $box = New-Label '' 96 ($rowY - 1) 28 28 $fontSmall $palette.Ink
    $title = New-Label $extraDefinitions[$i].Title 132 ($rowY - 2) 480 20 $fontRowTitle $palette.Ink
    $detail = New-Label $extraDefinitions[$i].Detail 132 ($rowY + 17) 490 18 $fontRowDetail $palette.Muted
    foreach ($control in @($box, $title, $detail)) {
        $control.Tag = $i
        $control.Cursor = [System.Windows.Forms.Cursors]::Hand
        $control.Add_Click($toggleExtra)
    }
    $script:extraRows.Add(@{ Def = $extraDefinitions[$i]; On = $false; Y = $rowY; Controls = @($box, $title, $detail) })
}

# Play page.
$lblPlay1 = New-Label 'Installed in the Game folder beside Setup.' 98 208 400 20 $fontSmall $palette.Soft
$lblPlay2 = New-Label 'Saves and your local high scores stay in Game\userdata.' 98 230 400 20 $fontSmall $palette.Soft
$lblPlay3 = New-Label '' 98 264 400 20 $fontSmall $palette.Ink
$lblPlay4 = New-Label 'To play later, open Hexic HD.exe beside Setup. Run Setup again to change your extras.' 98 298 380 40 $fontSmall $palette.Muted
$playControls = @($lblPlay1, $lblPlay2, $lblPlay3, $lblPlay4)

$script:page = 'package'
$script:selectedPackage = $null
$script:canInstall = $false
$script:installed = $false
$script:busy = $false
$script:showProgress = $false
$script:progress = 0
$script:existingInstall = $false
$script:backdrop = New-Backdrop

# Cyan SCORE-bar fill with a gloss line, clipped to a rounded track.
function Paint-Glow($g, [double]$X, [double]$Y, [double]$Width, [double]$Height, [double]$Fraction) {
    if ($Fraction -le 0) { return }
    $track = New-RoundedPath $X $Y $Width $Height ($Height / 2)
    $g.SetClip($track, [System.Drawing.Drawing2D.CombineMode]::Intersect)
    $fillWidth = [single]($Width * [Math]::Min(1.0, $Fraction))
    $fill = New-Blend $X $Y $Width $Height @($palette.CyanDeep, '#1A9ED8', $palette.Cyan) @(0, 0.55, 1) 0
    $g.FillRectangle($fill, [single]$X, [single]$Y, $fillWidth, [single]$Height)
    $shine = New-Object System.Drawing.SolidBrush((Alpha 60 '#FFFFFF'))
    $g.FillRectangle($shine, [single]$X, [single]$Y, $fillWidth, [single]($Height * 0.42))
    $g.ResetClip()
    foreach ($o in @($shine, $fill, $track)) { $o.Dispose() }
}

$form.Add_Paint({
        param($sender, $e)
        $g = $e.Graphics
        $g.DrawImageUnscaled($script:backdrop, 0, 0)
        $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
        $g.TextRenderingHint = [System.Drawing.Text.TextRenderingHint]::AntiAliasGridFit
        $g.ScaleTransform([single]$script:scale, [single]$script:scale)

        # Step bar. Done steps are lit cyan with a tick; the current one is
        # white, and Install lights up with the real progress; later steps
        # stay dim.
        $stage = switch ($script:page) {
            'extras' { 2 }
            'play' { 3 }
            default { if ($script:canInstall) { 1 } else { 0 } }
        }
        $lit = $stage / 4.0
        if ($script:page -eq 'play') { $lit = 1.0 }
        elseif ($stage -eq 1 -and $script:showProgress) { $lit += $script:progress / 400.0 }
        Paint-Glow $g ($pill.X + 2) ($pill.Y + 2) ($pill.W - 4) ($pill.H - 4) $lit
        $tabNames = @('PACKAGE', 'INSTALL', 'EXTRAS', 'PLAY')
        $segment = $pill.W / 4.0
        $divider = New-Object System.Drawing.Pen((Alpha 45 '#FFFFFF'), [single]1)
        for ($i = 0; $i -lt 4; $i++) {
            $tx = $pill.X + $i * $segment
            if ($i -gt 0) { $g.DrawLine($divider, [single]$tx, [single]($pill.Y + 7), [single]$tx, [single]($pill.Y + $pill.H - 7)) }
            if ($i -lt $stage -or $script:page -eq 'play') {
                $label = $check + '  ' + $tabNames[$i]; $tabColor = Color '#04182C'
            }
            elseif ($i -eq $stage) {
                $label = $tabNames[$i]; $tabColor = [System.Drawing.Color]::White
                if ($i -eq 1 -and $script:showProgress) { $label = 'INSTALL  ' + $dot + '  ' + $script:progress + '%' }
            }
            else {
                $label = $tabNames[$i]; $tabColor = Color '#6C6C96'
            }
            $rect = New-Object System.Drawing.RectangleF([single]$tx, [single]$pill.Y, [single]$segment, [single]$pill.H)
            if ($i -eq $stage -and $script:page -ne 'play') {
                $shadow = New-Object System.Drawing.SolidBrush((Alpha 170 '#000000'))
                $g.DrawString($label, $script:pillFont, $shadow,
                    (New-Object System.Drawing.RectangleF([single]$tx, [single]($pill.Y + 1), [single]$segment, [single]$pill.H)), $script:centerFormat)
                $shadow.Dispose()
            }
            $tabBrush = New-Object System.Drawing.SolidBrush($tabColor)
            $g.DrawString($label, $script:pillFont, $tabBrush, $rect, $script:centerFormat)
            $tabBrush.Dispose()
        }
        $divider.Dispose()
        $underGlow = New-Object System.Drawing.Pen((Alpha 150 $palette.Cyan), [single]1.2)
        $g.DrawLine($underGlow, [single]($pill.X + 16), [single]($pill.Y + $pill.H - 1), [single]($pill.X + $pill.W - 16), [single]($pill.Y + $pill.H - 1))
        $underGlow.Dispose()

        if ($script:page -eq 'package') {
            $field = New-RoundedPath $fieldBox.X $fieldBox.Y $fieldBox.W $fieldBox.H 7
            $white = New-Object System.Drawing.SolidBrush((Alpha 235 '#FFFFFF'))
            $g.FillPath($white, $field)
            $fieldPen = New-Object System.Drawing.Pen((Alpha 150 $palette.Violet), [single]1.2)
            $g.DrawPath($fieldPen, $field)
            foreach ($o in @($fieldPen, $white, $field)) { $o.Dispose() }

            # Small jewel bullets for the notes.
            Paint-Jewel $g 102 346 5.5 $jewels[3]
            Paint-Jewel $g 102 368 5.5 $jewels[4]

            if ($script:showProgress) {
                $track = New-RoundedPath $barBox.X $barBox.Y $barBox.W $barBox.H 6
                $well = New-Object System.Drawing.SolidBrush((Color '#0B0A1C'))
                $g.FillPath($well, $track)
                $well.Dispose(); $track.Dispose()
                Paint-Glow $g ($barBox.X + 1) ($barBox.Y + 1) ($barBox.W - 2) ($barBox.H - 2) ($script:progress / 100.0)
            }
        }
        elseif ($script:page -eq 'extras') {
            $sep = New-Object System.Drawing.Pen((Alpha 60 $palette.Violet), [single]1)
            for ($i = 1; $i -lt $script:extraRows.Count; $i++) {
                $y = [single]($extrasTop + $i * $rowPitch - 6)
                $g.DrawLine($sep, [single]98, $y, [single]622, $y)
            }
            $sep.Dispose()
            foreach ($row in $script:extraRows) {
                if ($row.On) {
                    Paint-Jewel $g 110 ($row.Y + 13) 12 $jewels[3]
                    $tick = New-Object System.Drawing.SolidBrush([System.Drawing.Color]::White)
                    $g.DrawString($check, $script:checkFont, $tick,
                        (New-Object System.Drawing.RectangleF([single]98, [single]($row.Y + 1), [single]24, [single]24)), $script:centerFormat)
                    $tick.Dispose()
                }
                else {
                    $hex = New-HexPath 110 ($row.Y + 13) 12
                    $white = New-Object System.Drawing.SolidBrush((Alpha 235 '#FFFFFF'))
                    $g.FillPath($white, $hex)
                    $edge = New-Object System.Drawing.Pen((Alpha 200 $palette.Violet), [single]1.4)
                    $g.DrawPath($edge, $hex)
                    foreach ($o in @($edge, $white, $hex)) { $o.Dispose() }
                }
            }
        }
        else {
            # A cleared flower: six jewels around a silver centre.
            $cx = 560.0; $cy = 300.0; $r = 21.0
            $step = [Math]::Sqrt(3) * $r
            for ($i = 0; $i -lt 6; $i++) {
                $a = [Math]::PI / 180 * (60 * $i - 60)
                Paint-Jewel $g ($cx + $step * [Math]::Cos($a)) ($cy + $step * [Math]::Sin($a)) ($r * 0.94) $jewels[$i]
            }
            Paint-Jewel $g $cx $cy ($r * 0.94) '#E6E6F4'
        }

        foreach ($id in $script:buttonOrder) { Paint-Button $g $id }
    })

function Set-InstallReady([bool]$Ready) {
    $script:canInstall = $Ready
    if ($script:page -eq 'package') {
        Set-Button 'right' $null $(if ($Ready) { 'primary' } else { 'disabled' })
    }
}

# Shows one page's controls and relabels the shared buttons for it.
function Show-Page([string]$Name) {
    $script:page = $Name
    foreach ($control in $packageControls) { $control.Visible = ($Name -eq 'package') }
    if ($Name -ne 'package') { $lblStats.Visible = $false }
    foreach ($row in $script:extraRows) {
        foreach ($control in $row.Controls) { $control.Visible = ($Name -eq 'extras') }
    }
    foreach ($control in $playControls) { $control.Visible = ($Name -eq 'play') }
    Set-Button 'choose' $null $null ($Name -eq 'package')
    Set-Button 'extras' $null $null ($Name -eq 'package' -and $script:existingInstall)
    switch ($Name) {
        'package' {
            $lblTitle.Text = 'Install your game'
            $lblFoot.Text = $footerText
            $lblFoot.Width = Px 150
            Set-Button 'left' 'Close' 'secondary'
            Set-Button 'right' 'Install game' $(if ($script:canInstall) { 'primary' } else { 'disabled' })
        }
        'extras' {
            $lblTitle.Text = 'Choose your extras'
            $lblFoot.Text = 'Nothing is switched on unless you tick it.'
            $lblFoot.Width = Px 280
            Set-Button 'left' 'Skip' 'secondary'
            Set-Button 'right' 'Apply' 'primary'
        }
        'play' {
            $lblTitle.Text = 'Ready to play'
            $lblFoot.Text = $footerText
            $lblFoot.Width = Px 150
            Set-Button 'left' 'Close' 'secondary'
            Set-Button 'right' 'Play now' 'primary'
        }
    }
    $form.Invalidate()
}

# Ticks reflect what is set now, so re-running Setup shows the current extras.
function Enter-Extras {
    foreach ($row in $script:extraRows) { $row.On = [bool](Get-ExtraState $row.Def.Id) }
    Show-Page 'extras'
}

function Enter-Play {
    $on = @($extraDefinitions | Where-Object { Get-ExtraState $_.Id } | ForEach-Object { $_.Short })
    $lblPlay3.Text = if ($on.Count -gt 0) { 'Extras:  ' + ($on -join ('  ' + $dot + '  ')) } else { 'Extras:  none' }
    Show-Page 'play'
}

# While installing, $Detail (the live counts) sits right-aligned on the phase
# line; -Below puts it on its own line under the bar instead.
function Update-Progress([int]$Percent, [string]$Phase, [string]$Detail, [switch]$Below) {
    $script:progress = [Math]::Max(0, [Math]::Min(100, $Percent))
    if ($lblPhase.Text -ne $Phase) { $lblPhase.Text = $Phase }
    if ($Below) {
        $lblStats.Visible = $false
        $lblDetail.Text = $Detail
    }
    else {
        if ($lblStats.Text -ne $Detail) { $lblStats.Text = $Detail }
        $lblStats.Visible = $true
        if ($lblDetail.Text -ne '') { $lblDetail.Text = '' }
    }
    # The bar and the step bar (its fill and percentage) both move.
    Invalidate-Box $barBox.X $barBox.Y $barBox.W $barBox.H
    Invalidate-Box $pill.X $pill.Y $pill.W $pill.H
    [System.Windows.Forms.Application]::DoEvents()
}

function Select-Package([string]$Path) {
    if ($script:busy -or $script:page -ne 'package') { return }
    $script:selectedPackage = $null
    $script:showProgress = $false
    $lblStats.Visible = $false
    $lblPhase.ForeColor = Color $palette.Violet
    $lblPath.Text = $Path
    $lblPath.ForeColor = Color $palette.Ink

    $info = Get-PackageInfo $Path
    if ($info.Ok) {
        $script:selectedPackage = $Path
        $name = 'Hexic HD'
        if ($info.Name) { $name = $info.Name }
        $lblPkgStatus.Text = ('{0}  {1}  {2}  Xbox LIVE Arcade  {2}  {3:N0} MB' -f $check, $name, $dot, ($info.Bytes / 1MB))
        $lblPkgStatus.ForeColor = Color $palette.Ok
        Set-InstallReady $true
        $lblPhase.Text = ('READY TO INSTALL  {0}  Setup unpacks about {1:N0} MB into the Game folder.' -f $dot, ($info.Bytes / 1MB))
        $lblDetail.Text = if ($script:existingInstall) { 'Installing again updates the game and keeps your saves and settings.' } else { '' }
        Write-Log ('Package accepted: {0} ({1} bytes)' -f $Path, $info.Bytes)
    }
    else {
        $lblPkgStatus.Text = $info.Message
        $lblPkgStatus.ForeColor = Color $palette.Bad
        Set-InstallReady $false
        if ($script:existingInstall) {
            $lblPhase.Text = 'HEXIC HD IS ALREADY INSTALLED HERE'
            $lblDetail.Text = 'Installing again updates the game and keeps your saves and settings.'
        }
        else {
            $lblPhase.Text = ''
            $lblDetail.Text = ''
        }
        Write-Log ('Package rejected: {0} - {1}' -f $Path, $info.Message)
    }
    $form.Invalidate()
}

function Show-PackagePicker {
    $dialog = New-Object System.Windows.Forms.OpenFileDialog
    $dialog.Title = 'Select your Hexic HD Xbox 360 package'
    $dialog.Filter = 'Xbox 360 package (any file)|*.*'
    $dialog.CheckFileExists = $true
    $dialog.Multiselect = $false
    if ($script:selectedPackage) {
        $dialog.InitialDirectory = Split-Path -Parent $script:selectedPackage
    }
    if ($dialog.ShowDialog($form) -eq [System.Windows.Forms.DialogResult]::OK) {
        Select-Package $dialog.FileName
    }
    $dialog.Dispose()
}

function Start-Install {
    if (-not $script:canInstall -or -not $script:selectedPackage) { return }
    $script:busy = $true
    foreach ($id in $script:buttonOrder) { Set-Button $id $null 'disabled' $script:buttons[$id].Visible }
    $lblPhase.ForeColor = Color $palette.Violet
    $script:showProgress = $true
    Update-Progress 0 'PREPARING' ''
    try {
        [void](Invoke-HexicInstall -PackagePath $script:selectedPackage -Report {
                param($p, $phase, $detail)
                Update-Progress $p $phase $detail
            })
        $script:installed = $true
        $script:existingInstall = $true
        $script:showProgress = $false
        Write-Log 'Install finished.'
        $script:busy = $false
        Enter-Extras
    }
    catch {
        $message = $_.Exception.Message
        Write-Log ('FAILED: ' + $message)
        $script:showProgress = $false
        $lblStats.Visible = $false
        $lblPhase.Text = 'INSTALLATION DID NOT COMPLETE'
        $lblPhase.ForeColor = Color $palette.Bad
        $lblDetail.Text = 'Your package was not changed. Details are in the logs folder.'
        $form.Invalidate()
        [void][System.Windows.Forms.MessageBox]::Show($form, $message, 'Hexic HD Setup',
            [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Error)
    }
    finally {
        $script:busy = $false
        if ($script:page -eq 'package') { Show-Page 'package' }
    }
}

function Save-Extras {
    $chosen = @($script:extraRows | Where-Object { $_.On } | ForEach-Object { $_.Def.Id })
    try {
        Set-Extras $chosen
        Enter-Play
    }
    catch {
        Write-Log ('Extras not saved: ' + $_.Exception.Message)
        [void][System.Windows.Forms.MessageBox]::Show($form,
            ('Your extras could not be saved: ' + $_.Exception.Message + "`n`nThe game is installed and will still run."),
            'Hexic HD Setup', [System.Windows.Forms.MessageBoxButtons]::OK, [System.Windows.Forms.MessageBoxIcon]::Warning)
    }
}

function Invoke-Button([string]$Id) {
    if ($script:busy -or -not $Id -or $script:buttons[$Id].Style -eq 'disabled') { return }
    switch ($Id) {
        'choose' { Show-PackagePicker }
        'extras' { Enter-Extras }
        'left' {
            if ($script:page -eq 'extras') {
                Write-Log 'Extras skipped.'
                Enter-Play
            }
            else {
                $form.Close()
            }
        }
        'right' {
            switch ($script:page) {
                'package' { Start-Install }
                'extras' { Save-Extras }
                'play' { Start-Game; $form.Close() }
            }
        }
    }
}

$form.Add_MouseMove({
        param($sender, $e)
        $id = Find-Button ($e.X / $script:scale) ($e.Y / $script:scale)
        if ($id -ne $script:hoverId) {
            $old = $script:hoverId
            $script:hoverId = $id
            Invalidate-Button $old
            Invalidate-Button $id
        }
        $clickable = $id -and $script:buttons[$id].Style -ne 'disabled' -and -not $script:busy
        $form.Cursor = if ($clickable) { [System.Windows.Forms.Cursors]::Hand } else { [System.Windows.Forms.Cursors]::Default }
    })
$form.Add_MouseLeave({
        if ($script:hoverId) {
            $old = $script:hoverId
            $script:hoverId = $null
            Invalidate-Button $old
        }
    })
# Borderless window: a press outside the buttons drags it.
$form.Add_MouseDown({
        param($sender, $e)
        if ($e.Button -ne [System.Windows.Forms.MouseButtons]::Left) { return }
        $id = Find-Button ($e.X / $script:scale) ($e.Y / $script:scale)
        if ($id) {
            if ($script:buttons[$id].Style -ne 'disabled' -and -not $script:busy) {
                $script:pressId = $id
                Invalidate-Button $id
            }
        }
        else {
            [void][HexicSetup.Native]::ReleaseCapture()
            [void][HexicSetup.Native]::SendMessage($form.Handle, 0xA1, [IntPtr]2, [IntPtr]::Zero)
        }
    })
$form.Add_MouseUp({
        param($sender, $e)
        if (-not $script:pressId) { return }
        $id = $script:pressId
        $script:pressId = $null
        Invalidate-Button $id
        if ((Find-Button ($e.X / $script:scale) ($e.Y / $script:scale)) -eq $id) { Invoke-Button $id }
    })
$lblPath.Add_Click({ if (-not $script:busy) { Show-PackagePicker } })
$lblTitle.Add_MouseDown({
        param($sender, $e)
        if ($e.Button -eq [System.Windows.Forms.MouseButtons]::Left) {
            [void][HexicSetup.Native]::ReleaseCapture()
            [void][HexicSetup.Native]::SendMessage($form.Handle, 0xA1, [IntPtr]2, [IntPtr]::Zero)
        }
    })

$form.Add_FormClosing({
        param($sender, $e)
        if ($script:busy) { $e.Cancel = $true }
    })
$form.Add_KeyDown({
        param($sender, $e)
        if ($script:busy) { return }
        if ($e.KeyCode -eq [System.Windows.Forms.Keys]::Escape) { $form.Close() }
        elseif ($e.KeyCode -eq [System.Windows.Forms.Keys]::Enter) { Invoke-Button 'right' }
    })

# Dropping the package anywhere on the package page selects it.
$dragEnter = {
    param($sender, $e)
    if (-not $script:busy -and $script:page -eq 'package' -and
        $e.Data.GetDataPresent([System.Windows.Forms.DataFormats]::FileDrop)) {
        $e.Effect = [System.Windows.Forms.DragDropEffects]::Copy
    }
    else {
        $e.Effect = [System.Windows.Forms.DragDropEffects]::None
    }
}
$dragDrop = {
    param($sender, $e)
    $files = $e.Data.GetData([System.Windows.Forms.DataFormats]::FileDrop)
    if ($files -and $files.Count -gt 0) { Select-Package ([string]$files[0]) }
}
$form.Add_DragEnter($dragEnter)
$form.Add_DragDrop($dragDrop)
foreach ($control in $form.Controls) {
    $control.AllowDrop = $true
    $control.Add_DragEnter($dragEnter)
    $control.Add_DragDrop($dragDrop)
}

$form.Add_Shown({
        $form.Activate()
        if ((Test-Path -LiteralPath $gameExe) -and (Test-Path -LiteralPath (Join-Path $assetsDir 'default.xex'))) {
            $script:existingInstall = $true
            $lblPhase.Text = 'HEXIC HD IS ALREADY INSTALLED HERE'
            $lblDetail.Text = 'Reinstalling keeps your saves and settings. Just changing extras? Choose Change extras.'
        }
        Show-Page 'package'
        if ($PackagePath) { Select-Package $PackagePath }
    })

Show-Page 'package'
Write-Log ('Setup {0} opened in {1}' -f $releaseVersion, $releaseRoot)
[void]$form.ShowDialog()
$form.Dispose()
$script:backdrop.Dispose()
exit 0
