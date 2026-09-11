# Draws packaging\hexic_hd.ico: a "flower" of seven glossy jewel hexagons in
# the game's piece colours (three at the smallest sizes, so it stays legible).
# Original artwork - no game assets. Every size is stored as PNG, which Windows
# Vista and later read natively.
[CmdletBinding()]
param([string]$OutputPath = (Join-Path $PSScriptRoot 'hexic_hd.ico'))

$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing

function Color([string]$Hex) { return [System.Drawing.ColorTranslator]::FromHtml($Hex) }

function Mix($A, $B, [double]$T) {
    $ca = if ($A -is [string]) { Color $A } else { $A }
    $cb = if ($B -is [string]) { Color $B } else { $B }
    return [System.Drawing.Color]::FromArgb(
        [int]($ca.R + ($cb.R - $ca.R) * $T), [int]($ca.G + ($cb.G - $ca.G) * $T), [int]($ca.B + ($cb.B - $ca.B) * $T))
}

# Pointy-top hexagon.
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

function Paint-Jewel($g, [double]$Cx, [double]$Cy, [double]$R, [string]$Hex) {
    $path = New-HexPath $Cx $Cy $R
    $rect = New-Object System.Drawing.RectangleF(($Cx - $R), ($Cy - $R - 1), ($R * 2), ($R * 2 + 2))
    $fill = New-Object System.Drawing.Drawing2D.LinearGradientBrush($rect, (Mix $Hex '#FFFFFF' 0.5), (Mix $Hex '#000000' 0.45), [single]90)
    $blend = New-Object System.Drawing.Drawing2D.ColorBlend(3)
    $blend.Colors = [System.Drawing.Color[]]@((Mix $Hex '#FFFFFF' 0.5), (Color $Hex), (Mix $Hex '#000000' 0.45))
    $blend.Positions = [single[]]@(0, 0.5, 1)
    $fill.InterpolationColors = $blend
    $g.FillPath($fill, $path)

    $gloss = New-HexPath $Cx ($Cy - $R * 0.3) ($R * 0.6)
    $glossRect = New-Object System.Drawing.RectangleF(($Cx - $R), ($Cy - $R), ($R * 2), ($R * 1.1))
    $shine = New-Object System.Drawing.Drawing2D.LinearGradientBrush($glossRect,
        [System.Drawing.Color]::FromArgb(170, 255, 255, 255), [System.Drawing.Color]::FromArgb(0, 255, 255, 255), [single]90)
    $g.FillPath($shine, $gloss)

    $pen = New-Object System.Drawing.Pen((Mix $Hex '#000000' 0.6), [single][Math]::Max(0.8, $R / 9))
    $g.DrawPath($pen, $path)
    foreach ($o in @($pen, $shine, $gloss, $fill, $path)) { $o.Dispose() }
}

function New-IconPng([int]$Size) {
    $bitmap = New-Object System.Drawing.Bitmap($Size, $Size, [System.Drawing.Imaging.PixelFormat]::Format32bppArgb)
    $g = [System.Drawing.Graphics]::FromImage($bitmap)
    $g.SmoothingMode = [System.Drawing.Drawing2D.SmoothingMode]::AntiAlias
    $g.Clear([System.Drawing.Color]::Transparent)

    $n = [double]$Size
    $pad = [Math]::Max(0.5, $n * 0.03)
    if ($Size -ge 32) {
        # Centre piece plus a ring of six: the flower that clears the board.
        $r = ($n / 2 - $pad) / 2.6
        $step = [Math]::Sqrt(3) * $r
        $ring = @('#E8303A', '#F59A1E', '#F5D73A', '#3CC84A', '#2E7CF0', '#9A3FE0')
        for ($i = 0; $i -lt 6; $i++) {
            $a = [Math]::PI / 180 * (60 * $i - 60)
            Paint-Jewel $g ($n / 2 + $step * [Math]::Cos($a)) ($n / 2 + $step * [Math]::Sin($a)) ($r * 0.93) $ring[$i]
        }
        Paint-Jewel $g ($n / 2) ($n / 2) ($r * 0.93) '#E6E6F4'
    }
    else {
        # Three touching pieces: a cluster.
        $r = ($n - 2 * $pad) / 3.5
        $d = [Math]::Sqrt(3) * $r
        $left = ($n - 2 * $d) / 2 + $d / 2
        $top = ($n - 3.5 * $r) / 2 + $r
        Paint-Jewel $g ($left + $d / 2) $top ($r * 0.94) '#9A3FE0'
        Paint-Jewel $g $left ($top + 1.5 * $r) ($r * 0.94) '#E8303A'
        Paint-Jewel $g ($left + $d) ($top + 1.5 * $r) ($r * 0.94) '#3CC84A'
    }

    $g.Dispose()
    $stream = New-Object System.IO.MemoryStream
    $bitmap.Save($stream, [System.Drawing.Imaging.ImageFormat]::Png)
    $bitmap.Dispose()
    return , $stream.ToArray()
}

$sizes = @(256, 128, 64, 48, 32, 24, 16)
$images = New-Object System.Collections.Generic.List[byte[]]
foreach ($size in $sizes) { $images.Add((New-IconPng $size)) }

$out = New-Object System.IO.MemoryStream
$writer = New-Object System.IO.BinaryWriter($out)
$writer.Write([uint16]0)
$writer.Write([uint16]1)
$writer.Write([uint16]$sizes.Count)
$offset = 6 + 16 * $sizes.Count
for ($i = 0; $i -lt $sizes.Count; $i++) {
    $dim = if ($sizes[$i] -ge 256) { 0 } else { $sizes[$i] }
    $writer.Write([byte]$dim)
    $writer.Write([byte]$dim)
    $writer.Write([byte]0)
    $writer.Write([byte]0)
    $writer.Write([uint16]1)
    $writer.Write([uint16]32)
    $writer.Write([uint32]$images[$i].Length)
    $writer.Write([uint32]$offset)
    $offset += $images[$i].Length
}
foreach ($image in $images) { $writer.Write($image) }
$writer.Flush()
[System.IO.File]::WriteAllBytes($OutputPath, $out.ToArray())
Write-Host ('Icon written: {0} ({1:N0} bytes, {2} sizes)' -f $OutputPath, $out.Length, $sizes.Count)
