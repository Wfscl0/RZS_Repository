<#
Verify and program one RES STM32G0B1 candidate image through J-Link/SWD.

This script intentionally requires -Program. Without it, it only checks the
selected artifact and prints the command that would access the target.

Examples (run from firmware/):
  .\tools\flash_stm32_g0b1_jlink.ps1 -Target remote
  .\tools\flash_stm32_g0b1_jlink.ps1 -Target remote -Program
  .\tools\flash_stm32_g0b1_jlink.ps1 -Target vehicle -Program -RunAfterFlash
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('remote', 'vehicle')]
    [string]$Target,

    [switch]$Program,
    [switch]$RunAfterFlash,
    [switch]$SkipHashCheck
)

$firmwareRoot = Split-Path -Parent $PSScriptRoot
$jlink = 'E:\JLink_V826\JLink.exe'
$device = 'STM32G0B1CBTx'

if ($Target -eq 'remote') {
    $imageName = 'RES_Remote_G0B1'
    $expectedHash = '58A8DCE67D35608A708B3DE8EE6B9F13CC18CAFE6068ECE45D55443345C3B32F'
} else {
    $imageName = 'RES_Vehicle_G0B1'
    $expectedHash = '3450484EE9A4C9585E1DE5829323933565D3EB0A9FF986D04207A062CD93FC8C'
}

$image = Join-Path $firmwareRoot "artifacts/$Target/gcc/$imageName.hex"
if (-not (Test-Path -LiteralPath $image)) {
    throw "Candidate image is missing: $image. Rebuild it with build_stm32_g0b1_gcc.ps1 first."
}

$actualHash = (Get-FileHash -LiteralPath $image -Algorithm SHA256).Hash
if (-not $SkipHashCheck -and $actualHash -ne $expectedHash) {
    throw "SHA-256 differs from artifacts/HIL_BUILD_MANIFEST_20260903.md. Expected $expectedHash; got $actualHash. Rebuild/review the manifest before programming."
}

Write-Host "Target: $Target ($device)"
Write-Host "Image : $image"
Write-Host "SHA-256: $actualHash"

if (-not $Program) {
    Write-Host 'Verification only: no board was accessed. Re-run with -Program only on an isolated HIL bench.'
    return
}

if (-not (Test-Path -LiteralPath $jlink)) {
    throw "J-Link Commander is missing: $jlink"
}

Write-Warning 'Confirm that real SDC/LVMS and vehicle actuation are isolated and fake loads are connected before continuing.'
$scriptPath = Join-Path ([System.IO.Path]::GetTempPath()) "res_${Target}_$PID.jlink"
$jlinkCommands = @(
    'r',
    'h',
    "loadfile `"$image`"",
    'r'
)
if ($RunAfterFlash) {
    $jlinkCommands += 'g'
} else {
    $jlinkCommands += 'h'
}
$jlinkCommands += 'exit'

try {
    [System.IO.File]::WriteAllLines($scriptPath, $jlinkCommands, [System.Text.UTF8Encoding]::new($false))
    & $jlink -device $device -if SWD -speed 4000 -autoconnect 1 -CommanderScript $scriptPath
    if ($LASTEXITCODE -ne 0) {
        throw "J-Link programming failed with exit code $LASTEXITCODE. Do not connect the safety loop; inspect SWD wiring, target power and the J-Link log."
    }
} finally {
    if (Test-Path -LiteralPath $scriptPath) {
        Remove-Item -LiteralPath $scriptPath -Force
    }
}

if ($RunAfterFlash) {
    Write-Host 'Programming completed and the MCU was released to run. Continue with the HIL checklist.'
} else {
    Write-Host 'Programming completed; MCU remains halted. Inspect before releasing it in the debugger.'
}
