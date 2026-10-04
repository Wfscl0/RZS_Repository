<#
Build the two STM32G0B1 CubeMX projects with the locally installed GNU Arm
toolchain. This script is a reproducible artifact generator for HIL; the
primary editable projects remain the MDK-ARM projects generated for Keil.

Examples:
  .\build_stm32_g0b1_gcc.ps1 -Target remote
  .\build_stm32_g0b1_gcc.ps1 -Target vehicle
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('remote', 'vehicle')]
    [string]$Target,
    # Keep new candidates separate from previously verified delivery images.
    [string]$OutputRoot = '',
    [switch]$RadioStopBench,
    [switch]$StockBridgeCompat,
    [switch]$BenchNoCan,
    # Optional portable toolchain; keep the existing workstation default.
    [string]$ToolchainBin = 'E:\toolchain\arm-gcc\bin'
)

if ($StockBridgeCompat -and [string]::IsNullOrWhiteSpace($OutputRoot)) {
    throw 'StockBridgeCompat uses a 3000 ms timeout and is bench-only. Supply a separate OutputRoot; delivery images must not be overwritten.'
}
if ($StockBridgeCompat -and $RadioStopBench) {
    throw 'Select only one bench profile.'
}
if ($BenchNoCan -and ($Target -ne 'vehicle' -or [string]::IsNullOrWhiteSpace($OutputRoot) -or $StockBridgeCompat -or $RadioStopBench)) {
    throw 'BenchNoCan requires vehicle target, an isolated OutputRoot, and no other bench profile.'
}

$firmwareRoot = Split-Path -Parent $PSScriptRoot
$gcc = Join-Path $ToolchainBin 'arm-none-eabi-gcc.exe'
$objcopy = Join-Path $ToolchainBin 'arm-none-eabi-objcopy.exe'
$size = Join-Path $ToolchainBin 'arm-none-eabi-size.exe'

foreach ($tool in @($gcc, $objcopy, $size)) {
    if (-not (Test-Path -LiteralPath $tool)) {
        throw "Required GNU Arm tool is missing: $tool"
    }
}

if ($Target -eq 'remote') {
    $projectDirectory = Join-Path $firmwareRoot 'remote_g0b1'
    $imageName = 'RES_Remote_G0B1'
    $applicationSources = @(
        'Core/Src/main.c',
        'Core/Src/gpio.c',
        'Core/Src/i2c.c',
        'Core/Src/iwdg.c',
        'Core/Src/usart.c',
        'Core/Src/stm32g0xx_hal_msp.c',
        'Core/Src/stm32g0xx_it.c',
        'Core/Src/system_stm32g0xx.c',
        'Core/Src/ina226.c',
        'Core/Src/res_protocol_build.c',
        'Core/Src/res_remote_app.c',
        'Core/Src/res_stm32_port.c'
    )
    $halSources = @(
        'stm32g0xx_hal.c', 'stm32g0xx_hal_cortex.c',
        'stm32g0xx_hal_dma.c', 'stm32g0xx_hal_dma_ex.c',
        'stm32g0xx_hal_exti.c', 'stm32g0xx_hal_flash.c',
        'stm32g0xx_hal_flash_ex.c', 'stm32g0xx_hal_gpio.c',
        'stm32g0xx_hal_i2c.c', 'stm32g0xx_hal_i2c_ex.c',
        'stm32g0xx_hal_iwdg.c', 'stm32g0xx_hal_pwr.c',
        'stm32g0xx_hal_pwr_ex.c', 'stm32g0xx_hal_rcc.c',
        'stm32g0xx_hal_rcc_ex.c', 'stm32g0xx_hal_uart.c',
        'stm32g0xx_hal_uart_ex.c', 'stm32g0xx_ll_rcc.c'
    )
} else {
    $projectDirectory = Join-Path $firmwareRoot 'vehicle_g0b1'
    $imageName = 'RES_Vehicle_G0B1'
    $applicationSources = @(
        'Core/Src/main.c',
        'Core/Src/fdcan.c',
        'Core/Src/gpio.c',
        'Core/Src/iwdg.c',
        'Core/Src/usart.c',
        'Core/Src/stm32g0xx_hal_msp.c',
        'Core/Src/stm32g0xx_it.c',
        'Core/Src/system_stm32g0xx.c',
        'Core/Src/res_protocol_build.c',
        'Core/Src/res_can_contract_build.c',
        'Core/Src/res_vehicle_app.c',
        'Core/Src/res_vehicle_stm32_port.c'
    )
    $halSources = @(
        'stm32g0xx_hal.c', 'stm32g0xx_hal_cortex.c',
        'stm32g0xx_hal_dma.c', 'stm32g0xx_hal_dma_ex.c',
        'stm32g0xx_hal_exti.c', 'stm32g0xx_hal_fdcan.c',
        'stm32g0xx_hal_flash.c', 'stm32g0xx_hal_flash_ex.c',
        'stm32g0xx_hal_gpio.c', 'stm32g0xx_hal_iwdg.c',
        'stm32g0xx_hal_pwr.c', 'stm32g0xx_hal_pwr_ex.c',
        'stm32g0xx_hal_rcc.c', 'stm32g0xx_hal_rcc_ex.c',
        'stm32g0xx_hal_uart.c', 'stm32g0xx_hal_uart_ex.c',
        'stm32g0xx_ll_rcc.c'
    )
}

$startup = Join-Path $projectDirectory 'STM32CubeIDE/Application/User/Startup/startup_stm32g0b1cbtx.s'
$linker = Join-Path $projectDirectory 'STM32CubeIDE/STM32G0B1CBTX_FLASH.ld'
if ($Target -eq 'vehicle') {
    # CubeMX generated this project with GCC11-only READONLY section attributes.
    # Keep the original file intact and use the reviewed GCC10-compatible copy.
    $linker = Join-Path $projectDirectory 'MDK-ARM/STM32G0B1CBTX_FLASH_GCC10.ld'
}
$outputDirectory = if ($OutputRoot) {
    Join-Path $OutputRoot "$Target/gcc"
} else {
    Join-Path $firmwareRoot "artifacts/$Target/gcc"
}
New-Item -ItemType Directory -Force -Path $outputDirectory | Out-Null

$includeArguments = @(
    "-I$(Join-Path $projectDirectory 'Core/Inc')",
    "-I$(Join-Path $projectDirectory 'Drivers/STM32G0xx_HAL_Driver/Inc')",
    "-I$(Join-Path $projectDirectory 'Drivers/STM32G0xx_HAL_Driver/Inc/Legacy')",
    "-I$(Join-Path $projectDirectory 'Drivers/CMSIS/Device/ST/STM32G0xx/Include')",
    "-I$(Join-Path $projectDirectory 'Drivers/CMSIS/Include')",
    "-I$(Join-Path $firmwareRoot 'shared/include')"
)

$sourcePaths = @($startup)
$sourcePaths += $applicationSources | ForEach-Object { Join-Path $projectDirectory $_ }
$sourcePaths += $halSources | ForEach-Object {
    Join-Path $projectDirectory "Drivers/STM32G0xx_HAL_Driver/Src/$_"
}
$sourcePaths += Join-Path $projectDirectory 'Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_hal_spi.c'

foreach ($source in ($sourcePaths + @($linker))) {
    if (-not (Test-Path -LiteralPath $source)) {
        throw "Required project file is missing: $source"
    }
}

$elf = Join-Path $outputDirectory "$imageName.elf"
$hex = Join-Path $outputDirectory "$imageName.hex"
$bin = Join-Path $outputDirectory "$imageName.bin"
$map = Join-Path $outputDirectory "$imageName.map"

$arguments = @(
    '-mcpu=cortex-m0plus', '-mthumb', '-mfloat-abi=soft',
    '-std=gnu99', '-Og', '-g3', '-Wall', '-Wextra',
    '-ffunction-sections', '-fdata-sections', '-fno-common',
    '-DUSE_HAL_DRIVER', '-DSTM32G0B1xx'
)
$arguments += $includeArguments
if ($BenchNoCan) { $arguments += '-DRES_BENCH_NO_CAN=1' }
if ($RadioStopBench) {
    if ($Target -ne 'remote' -or [string]::IsNullOrWhiteSpace($OutputRoot)) {
        throw 'RadioStopBench requires remote target and a separate OutputRoot.'
    }
    $arguments += '-DRES_RADIO_STOP_BENCH=1'
}
if ($StockBridgeCompat) {
    $arguments += '-DRES_RADIO_SI4463=0'
    $arguments += '-DRES_E220_STOCK_BRIDGE_TEST=1'
    # Vendor bridge UART frame delimiter is >10 timer ticks; 15 ms leaves
    # margin without changing the production transport timing.
    $arguments += '-DRES_STOCK_BRIDGE_GAP_MS=15'
}
$arguments += $sourcePaths
$arguments += @(
    "-T$linker", '-Wl,--gc-sections', "-Wl,-Map,$map",
    '--specs=nano.specs', '--specs=nosys.specs',
    '-Wl,--start-group', '-lc', '-lm', '-Wl,--end-group',
    '-o', $elf
)

Write-Host "Building $imageName with GNU Arm Embedded Toolchain..."
& $gcc @arguments
if ($LASTEXITCODE -ne 0) {
    throw "$imageName ELF build failed with exit code $LASTEXITCODE."
}

& $objcopy '-O' 'ihex' $elf $hex
if ($LASTEXITCODE -ne 0) {
    throw "$imageName HEX conversion failed with exit code $LASTEXITCODE."
}

& $objcopy '-O' 'binary' $elf $bin
if ($LASTEXITCODE -ne 0) {
    throw "$imageName BIN conversion failed with exit code $LASTEXITCODE."
}

& $size $elf
if ($LASTEXITCODE -ne 0) {
    throw "$imageName size check failed with exit code $LASTEXITCODE."
}

Write-Host "Artifacts generated:"
Write-Host "  $hex"
Write-Host "  $bin"
Write-Host "  $elf"
