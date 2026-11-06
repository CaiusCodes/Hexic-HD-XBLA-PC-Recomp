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

function Alpha([int]$A, [string]$Hex) { $c = Color $Hex; return [System.Drawing.Color]::FromArgb($A, $c.R, $c.G, $c.B) }

# Pointy-top hexagon; $Round > 0 softens each corner with a short curve.
function New-HexPath([double]$Cx, [double]$Cy, [double]$R, [double]$Round = 0) {
    $pts = @()
    for ($i = 0; $i -lt 6; $i++) {
        $a = [Math]::PI / 180 * (60 * $i - 90)
        $pts += , @(($Cx + $R * [Math]::Cos($a)), ($Cy + $R * [Math]::Sin($a)))
    }
    $path = New-Object System.Drawing.Drawing2D.GraphicsPath
    if ($Round -le 0) {
        $points = New-Object 'System.Drawing.PointF[]' 6
        for ($i = 0; $i -lt 6; $i++) { $points[$i] = New-Object System.Drawing.PointF($pts[$i][0], $pts[$i][1]) }
        $path.AddPolygon($points)
        return , $path
    }
    $t = [Math]::Min(0.45, $Round)
    for ($i = 0; $i -lt 6; $i++) {
        $p = $pts[$i]; $prev = $pts[($i + 5) % 6]; $next = $pts[($i + 1) % 6]
        $ax = $p[0] + ($prev[0] - $p[0]) * $t; $ay = $p[1] + ($prev[1] - $p[1]) * $t
        $bx = $p[0] + ($next[0] - $p[0]) * $t; $by = $p[1] + ($next[1] - $p[1]) * $t
        if ($i -gt 0) { $path.AddLine($lastX, $lastY, $ax, $ay) } else { $firstX = $ax; $firstY = $ay }
        $path.AddBezier($ax, $ay, $p[0], $p[1], $p[0], $p[1], $bx, $by)
        $lastX = $bx; $lastY = $by
    }
    $path.AddLine($lastX, $lastY, $firstX, $firstY)
    $path.CloseFigure()
    return , $path
}

# A cut gem: vertical shading, a lighter inner facet, a gloss on top, dark rim.
function Paint-Jewel($g, [double]$Cx, [double]$Cy, [double]$R, [string]$Hex) {
    $path = New-HexPath $Cx $Cy $R 0.12
    $rect = New-Object System.Drawing.RectangleF(($Cx - $R), ($Cy - $R - 1), ($R * 2), ($R * 2 + 2))
    $fill = New-Object System.Drawing.Drawing2D.LinearGradientBrush($rect, (Color $Hex), (Color $Hex), [single]90)
    $blend = New-Object System.Drawing.Drawing2D.ColorBlend(3)
    $blend.Colors = [System.Drawing.Color[]]@((Mix $Hex '#FFFFFF' 0.55), (Color $Hex), (Mix $Hex '#000000' 0.5))
    $blend.Positions = [single[]]@(0, 0.5, 1)
    $fill.InterpolationColors = $blend
    $g.FillPath($fill, $path)

    $facet = New-HexPath $Cx $Cy ($R * 0.62) 0.12
    $facetBrush = New-Object System.Drawing.SolidBrush((Alpha 60 '#FFFFFF'))
    $g.FillPath($facetBrush, $facet)

    $gloss = New-HexPath $Cx ($Cy - $R * 0.32) ($R * 0.55) 0.3
    $glossRect = New-Object System.Drawing.RectangleF(($Cx - $R), ($Cy - $R), ($R * 2), ($R * 1.1))
    $shine = New-Object System.Drawing.Drawing2D.LinearGradientBrush($glossRect, (Alpha 200 '#FFFFFF'), (Alpha 0 '#FFFFFF'), [single]90)
    $g.FillPath($shine, $gloss)

    $pen = New-Object System.Drawing.Pen((Mix $Hex '#000000' 0.65), [single][Math]::Max(0.7, $R / 10))
    $g.DrawPath($pen, $path)
    foreach ($o in @($pen, $shine, $gloss, $facetBrush, $facet, $fill, $path)) { $o.Dispose() }
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
