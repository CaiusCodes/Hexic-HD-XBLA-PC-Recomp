<#
.SYNOPSIS
    Relabels Hexic HD's main-menu text for the PC build: "Achievements"
    becomes "PC Settings" (matching the native PC settings dialog that now
    opens in its place, since the Xbox Achievements viewer has no PC
    equivalent), and "Xbox Dashboard" becomes "Quit Hexic" (there is no Xbox
    Dashboard to return to on PC). Leaderboards becomes "High Scores": the
    game's own screen works offline, listing this PC's scores (the SDK's
    local leaderboards answer its Xbox LIVE stats requests), so the movie
    behind it (HexicDeluxe.swf) is patched to show only the Overall list
    with no Sort Mode button - see the byte edits below.
.DESCRIPTION
    g.xml is plain UTF-8 text (unlike BBR/Aegis Wing's UTF-16 INI files).
    The replacement targets the exact original strings, so it is a no-op
    (and safe to re-run) once already applied or if the source text has
    already changed.
.PARAMETER AssetsPath
    Path to the installed assets folder containing g.xml.
#>
param(
    [Parameter(Mandatory)]
    [string]$AssetsPath,
    [string]$ProgressPath
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

function Write-PatchProgressState {
    param([int]$Percent)
    if ([string]::IsNullOrWhiteSpace($ProgressPath)) { return }
    try {
        [System.IO.File]::WriteAllText($ProgressPath, "patch|$Percent")
    }
    catch {
        # Progress is optional telemetry for the graphical installer.
    }
}

Write-PatchProgressState 0

$gxmlPath = Join-Path $AssetsPath "g.xml"
if (-not (Test-Path -LiteralPath $gxmlPath -PathType Leaf)) {
    Write-Warning "g.xml not found at '$gxmlPath'; skipping PC menu text patch."
    Write-PatchProgressState 100
    exit 0
}

$content = [System.IO.File]::ReadAllText($gxmlPath, [System.Text.Encoding]::UTF8)
Write-PatchProgressState 40

$replacements = @(
    @{ From = '>Achievements</text>'; To = '>PC Settings</text>' },
    @{ From = "Show off the awards you've earned."; To = 'Change display, audio and performance settings.' },
    @{ From = '>Xbox Dashboard</text>'; To = '>Quit Hexic</text>' },
    @{ From = 'Quit Hexic, and return to the Xbox Dashboard.'; To = 'Quit Hexic, and return to the desktop.' },
    # Leaderboards -> High Scores: the screen lists this PC's scores only.
    @{ From = '>Leaderboards</text>'; To = '>High Scores</text>' },
    @{ From = 'View high scores on Xbox Live.'; To = 'View your best scores for each mode.' },
    @{ From = 'Congratulations! You have a new high score on the Xbox Live leaderboards!!'; To = 'Congratulations! You have a new high score!' },
    @{ From = '-->Sort Mode</text>'; To = '--></text>' },
    @{ From = 'No scores have been posted to this leaderboard.'; To = 'No high scores yet for this mode.' },
    @{ From = '-->Signed In:</text>'; To = '-->Player:</text>' }
)

$changed = $false
foreach ($replacement in $replacements) {
    if ($content.Contains($replacement.From)) {
        $content = $content.Replace($replacement.From, $replacement.To)
        $changed = $true
    }
}
Write-PatchProgressState 80

if ($changed) {
    # g.xml ships without a BOM; preserve that.
    $utf8NoBom = New-Object System.Text.UTF8Encoding($false)
    [System.IO.File]::WriteAllText($gxmlPath, $content, $utf8NoBom)
    Write-Host "Relabeled the menus for PC: PC Settings, High Scores, Quit Hexic."
}
else {
    Write-Host "PC menu text already applied (or source text changed); nothing to do."
}

# HexicDeluxe.swf: the High Scores (Leaderboards) screen lists this PC's
# scores only, so it opens on Overall and the Sort Mode (X) control goes.
# In-place byte edits to the decompressed movie - offsets count from the
# start of the body after the 8-byte SWF header - each checked against the
# original bytes first; the movie is only rewritten when all of them match.
#   SortOrder starts as SO_Overall instead of SO_Friends (constant index)
#   the first title shown is Overall instead of Friends (constant index)
#   ChangeSortOrder, bound to X, jumps straight to its end
#   the X button icon's three pieces are placed at zero scale
$swfEdits = @(
    @{ Offset = 0x2583CA; From = '0F'; To = '47' },
    @{ Offset = 0x258590; From = '27'; To = '29' },
    @{ Offset = 0x258A05; From = '960400082B'; To = '9902006F00' },
    @{ Offset = 0x25AC4D; From = 'C92BBB4B290F74362858'; To = 'C8000000000F74362858' },
    @{ Offset = 0x25AC5E; From = 'C5E842F4DF3DB080A440'; To = 'C4000000003DB080A440' },
    @{ Offset = 0x25AC6F; From = 'C92BBB4B290F74362858'; To = 'C8000000000F74362858' }
)

function ConvertFrom-HexString([string]$Hex) {
    $bytes = New-Object byte[] ($Hex.Length / 2)
    for ($i = 0; $i -lt $bytes.Length; $i++) {
        $bytes[$i] = [Convert]::ToByte($Hex.Substring($i * 2, 2), 16)
    }
    return , $bytes
}

function Test-BytesAt([byte[]]$Data, [int]$Offset, [byte[]]$Expected) {
    if ($Offset + $Expected.Length -gt $Data.Length) { return $false }
    for ($i = 0; $i -lt $Expected.Length; $i++) {
        if ($Data[$Offset + $i] -ne $Expected[$i]) { return $false }
    }
    return $true
}

$swfPath = Join-Path $AssetsPath "HexicDeluxe.swf"
if (Test-Path -LiteralPath $swfPath -PathType Leaf) {
    $raw = [System.IO.File]::ReadAllBytes($swfPath)
    $signature = [System.Text.Encoding]::ASCII.GetString($raw, 0, 3)
    $body = $null
    if ($signature -eq 'CWS') {
        # zlib stream: skip its 2-byte header and inflate the deflate data.
        $compressed = New-Object System.IO.MemoryStream -ArgumentList $raw, 10, ($raw.Length - 10)
        $inflater = New-Object System.IO.Compression.DeflateStream($compressed,
            [System.IO.Compression.CompressionMode]::Decompress)
        $inflated = New-Object System.IO.MemoryStream
        $inflater.CopyTo($inflated)
        $inflater.Dispose()
        $body = $inflated.ToArray()
    }
    elseif ($signature -eq 'FWS') {
        $body = New-Object byte[] ($raw.Length - 8)
        [Array]::Copy($raw, 8, $body, 0, $body.Length)
    }
    Write-PatchProgressState 90

    # The header's length field should cover the 8-byte header too, but this
    # movie's equals the body alone; accept either, and keep it as it was.
    $declaredLength = [BitConverter]::ToUInt32($raw, 4)
    if ($null -eq $body -or ($declaredLength -ne $body.Length -and $declaredLength -ne $body.Length + 8)) {
        Write-Warning "HexicDeluxe.swf is not the expected movie; High Scores screen left unchanged."
    }
    else {
        $original = @($swfEdits | Where-Object { Test-BytesAt $body $_.Offset (ConvertFrom-HexString $_.From) }).Count
        $patched = @($swfEdits | Where-Object { Test-BytesAt $body $_.Offset (ConvertFrom-HexString $_.To) }).Count
        if ($patched -eq $swfEdits.Count) {
            Write-Host "High Scores screen already patched; nothing to do."
        }
        elseif ($original -ne $swfEdits.Count) {
            Write-Warning "HexicDeluxe.swf differs from the expected build; High Scores screen left unchanged."
        }
        else {
            foreach ($edit in $swfEdits) {
                $to = ConvertFrom-HexString $edit.To
                [Array]::Copy($to, 0, $body, $edit.Offset, $to.Length)
            }
            # Written back uncompressed ("FWS") with the original version and
            # length field.
            $movie = New-Object byte[] ($body.Length + 8)
            [Array]::Copy([byte[]](0x46, 0x57, 0x53), 0, $movie, 0, 3)
            [Array]::Copy($raw, 3, $movie, 3, 5)
            [Array]::Copy($body, 0, $movie, 8, $body.Length)
            [System.IO.File]::WriteAllBytes($swfPath, $movie)
            Write-Host "High Scores screen: opens on Overall, Sort Mode removed."
        }
    }
}
else {
    Write-Warning "HexicDeluxe.swf not found at '$swfPath'; High Scores screen left unchanged."
}

Write-PatchProgressState 100
exit 0
