param(
  [string]$Port = "COM3",
  [ValidateSet("ArduinoNano_GPIO_Test", "TSAL_Bench_Test", "LOCK_Bench_Test")]
  [string]$SketchName = "ArduinoNano_GPIO_Test",
  [ValidateSet("New", "Old")]
  [string]$Bootloader = "New",
  [switch]$NoUpload,
  [switch]$NoBackup
)

$ErrorActionPreference = "Stop"
$Arduino15 = Join-Path $env:LOCALAPPDATA "Arduino15"
$Hardware = Join-Path $Arduino15 "packages\arduino\hardware\avr\1.8.8"
$Toolchain = Join-Path $Arduino15 "packages\arduino\tools\avr-gcc\7.3.0-atmel3.6.1-arduino7\bin"
$AvrdudeRoot = Join-Path $Arduino15 "packages\arduino\tools\avrdude\8.0.0-arduino1"
$Avrdude = Join-Path $AvrdudeRoot "bin\avrdude.exe"
$AvrdudeConf = Join-Path $AvrdudeRoot "etc\avrdude.conf"
$Core = Join-Path $Hardware "cores\arduino"
$Variant = Join-Path $Hardware "variants\eightanaloginputs"
$SketchDir = $PSScriptRoot
$Build = Join-Path $SketchDir "build\$SketchName"
$Backup = Join-Path $SketchDir "backups"
$Sketch = Join-Path $SketchDir "$SketchName.ino"
$UploadBaud = if ($Bootloader -eq "New") { 115200 } else { 57600 }

foreach ($required in @($Avrdude, $AvrdudeConf, $Core, $Variant, $Sketch)) {
  if (-not (Test-Path -LiteralPath $required)) { throw "Missing dependency: $required" }
}

New-Item -ItemType Directory -Force -Path $Build | Out-Null
if (-not $NoBackup -and -not $NoUpload) {
  New-Item -ItemType Directory -Force -Path $Backup | Out-Null
  $stamp = Get-Date -Format "yyyyMMdd-HHmmss"
  & $Avrdude -C $AvrdudeConf -p atmega328p -c arduino -P $Port -b $UploadBaud -U "flash:r:$Backup\flash-$stamp.hex:i" -U "eeprom:r:$Backup\eeprom-$stamp.hex:i"
  if ($LASTEXITCODE -ne 0) { throw "Backup failed; upload was not attempted." }
}

Get-ChildItem -LiteralPath $Build -File -ErrorAction SilentlyContinue | Remove-Item -Force
$SketchCpp = Join-Path $Build "$SketchName.cpp"
$SketchText = "#include <Arduino.h>`r`n" + (Get-Content -Raw -LiteralPath $Sketch)
[IO.File]::WriteAllText($SketchCpp, $SketchText, [Text.UTF8Encoding]::new($false))

$Common = @(
  "-c", "-g", "-Os", "-w", "-flto", "-ffunction-sections", "-fdata-sections",
  "-mmcu=atmega328p", "-DF_CPU=16000000L", "-DARDUINO=10819",
  "-DARDUINO_AVR_NANO", "-DARDUINO_ARCH_AVR", "-I$Core", "-I$Variant"
)
$CppExtra = @("-std=gnu++11", "-fpermissive", "-fno-exceptions", "-fno-threadsafe-statics", "-Wno-error=narrowing")
$CExtra = @("-std=gnu11", "-fno-fat-lto-objects")
$Gpp = Join-Path $Toolchain "avr-g++.exe"
$Gcc = Join-Path $Toolchain "avr-gcc.exe"
$Ar = Join-Path $Toolchain "avr-gcc-ar.exe"
$Objcopy = Join-Path $Toolchain "avr-objcopy.exe"
$Size = Join-Path $Toolchain "avr-size.exe"

& $Gpp @Common @CppExtra $SketchCpp -o (Join-Path $Build "sketch.o")
if ($LASTEXITCODE -ne 0) { throw "Sketch compilation failed." }

$CoreObjects = @()
foreach ($source in Get-ChildItem -LiteralPath $Core -File | Where-Object { $_.Extension -in ".c", ".cpp", ".S" }) {
  $object = Join-Path $Build ("core_" + $source.Name + ".o")
  if ($source.Extension -eq ".cpp") {
    & $Gpp @Common @CppExtra $source.FullName -o $object
  } elseif ($source.Extension -eq ".c") {
    & $Gcc @Common @CExtra $source.FullName -o $object
  } else {
    & $Gcc @Common -x assembler-with-cpp $source.FullName -o $object
  }
  if ($LASTEXITCODE -ne 0) { throw "Core compilation failed: $($source.Name)" }
  $CoreObjects += $object
}

$CoreArchive = Join-Path $Build "core.a"
foreach ($object in $CoreObjects) {
  & $Ar rcs $CoreArchive $object
  if ($LASTEXITCODE -ne 0) { throw "Core archive creation failed." }
}

$Elf = Join-Path $Build "$SketchName.elf"
$Hex = Join-Path $Build "$SketchName.hex"
& $Gcc -w -Os -g -flto -fuse-linker-plugin "-Wl,--gc-sections" -mmcu=atmega328p -o $Elf (Join-Path $Build "sketch.o") $CoreArchive -lm
if ($LASTEXITCODE -ne 0) { throw "Link failed." }
& $Objcopy -O ihex -R .eeprom $Elf $Hex
if ($LASTEXITCODE -ne 0) { throw "HEX generation failed." }
& $Size -A $Elf

if (-not $NoUpload) {
  & $Avrdude -C $AvrdudeConf -p atmega328p -c arduino -P $Port -b $UploadBaud -D -U "flash:w:${Hex}:i"
  if ($LASTEXITCODE -ne 0) { throw "Upload failed." }
  Write-Host "Uploaded $SketchName to $Port using Nano $($Bootloader.ToLowerInvariant())-bootloader settings."
} else {
  Write-Host "Built: $Hex"
}
