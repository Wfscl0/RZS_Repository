$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$lt = Resolve-Path (Join-Path $root '..\LTspice\LTspice.exe')
Get-ChildItem $root -Filter '*.cir' | ForEach-Object {
    $p = Start-Process -FilePath $lt -ArgumentList @('-b', ('"' + $_.FullName + '"')) -WindowStyle Hidden -PassThru
    $p.WaitForExit()
    if ($p.ExitCode -ne 0) { throw "LTspice failed: $($_.Name), exit=$($p.ExitCode)" }
    Write-Host "PASS process: $($_.Name)"
}
