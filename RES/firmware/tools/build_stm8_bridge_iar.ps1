param(
    [Parameter(Mandatory = $true)][string]$IarBuild,
    [ValidateSet('Debug', 'Release')][string]$Configuration = 'Debug'
)
$ErrorActionPreference = 'Stop'
$builder = (Resolve-Path -LiteralPath $IarBuild).Path
$bridge = Join-Path $PSScriptRoot '../radio_bridge_stm8'
$sdk = Join-Path $bridge 'E220_IAR_SDK/3_代码工程/0_Project/IAR_for_Stm8/Uart_PingPong'
$project = (Resolve-Path -LiteralPath (Join-Path $sdk 'project.ewp')).Path
# Refuse to compile a stale SDK copy of the canonical repair.
$pairs = @(
    @('res_bridge_main.c', 'main.c'),
    @('res_bridge_callback.c', 'ebyte/E220xMx/ebyte_callback.c'),
    @('res_bridge_control.h', 'res_bridge_control.h'),
    @('res_bridge_config.h', 'res_bridge_config.h')
)
foreach ($pair in $pairs) {
    $sourceHash = (Get-FileHash -LiteralPath (Join-Path $bridge $pair[0])).Hash
    $sdkHash = (Get-FileHash -LiteralPath (Join-Path $sdk $pair[1])).Hash
    if ($sourceHash -ne $sdkHash) { throw "SDK copy is stale: $($pair[1])" }
}
$started = [DateTime]::UtcNow
& $builder $project -build $Configuration -log all
if ($LASTEXITCODE -ne 0) { throw "IAR build failed (exit $LASTEXITCODE). No firmware is approved for deployment." }
$artifact = Join-Path $sdk "$Configuration/Exe/project.out"
if (!(Test-Path -LiteralPath $artifact) -or
    (Get-Item -LiteralPath $artifact).LastWriteTimeUtc -lt $started) {
    throw 'No fresh target output was produced. Do not use old Debug artifacts.'
}
Get-FileHash -LiteralPath $artifact -Algorithm SHA256
Write-Host 'Target build finished. This does not verify SWIM programming, RF communication or ASF acceptance.'
