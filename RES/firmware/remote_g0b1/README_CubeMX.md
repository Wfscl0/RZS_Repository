# STM32CubeMX configuration (STM32G0B1CBT6, LQFP48)

The ready-to-open project configuration is `RES_Remote_G0B1.ioc` in this
directory. Open it directly in STM32CubeMX and select **Generate Code**. It was
round-trip loaded and exported with STM32CubeMX 6.16.1. If CubeMX asks for an
MCU package, install `STM32Cube FW_G0 V1.6.3` (or migrate to the installed newer
G0 package while preserving the settings below).

The following list is also the review checklist for the supplied `.ioc`.

## 1. System and clock

- `SYS > Debug`: Serial Wire.
- `RCC > HSI16`: enabled.
- Clock tree: HSI16 = 16 MHz, PLL source HSI16, PLLM = /1, PLLN = x8,
  PLLR = /2, SYSCLK = 64 MHz. AHB and APB prescalers = /1.
- Flash latency is selected by CubeMX. Do not overclock this MCU.
- IWDG is enabled: LSI /32, reload 999, nominal timeout about 1 s. During initial
  debugging use "debug freeze IWDG" in the probe settings instead of deleting
  watchdog refresh from the safety task.

## 2. E220 board UART

- USART1 asynchronous: PA9=TX, PA10=RX, 9600 bit/s, 8 data bits, no parity,
  1 stop bit, no flow control, oversampling 16.
- Enable USART1 global interrupt.
- This 9600 rate matches Ebyte's official E15-EVB02 `board.h` default.
- Connect G0 PA9 to E220 `RXD`, PA10 to E220 `TXD`, and common GND. Both sides
  use 3.3 V logic.
- Do not configure or drive the G0 wires connected to E220 `PC0/PB4..PB7`.
  Set them to Analog/No-pull or physically leave them disconnected. Those pins
  belong to the E220 board's STM8-to-LLCC68 interface.

## 3. INA226

- I2C1: PB6=SCL, PB7=SDA, Standard Mode 100 kHz, 7-bit addressing, analog
  filter enabled, digital filter 0. Use external 4.7 kOhm pull-ups to 3.3 V if
  the purchased module does not already contain them.
- PA8 GPIO input, label `INA_ALERT`, pull-up. The first release polls every
  100 ms; ALERT is reserved for a later hardware threshold interrupt.
- The driver assumes address 0x40, a 10 mOhm shunt and 500 uA/current-bit.
  Confirm the module's R010 marking before use.

## 4. Buttons and relay indicators

| Function | Pin | CubeMX mode | Electrical default |
|---|---|---|---|
| GO contact | PB0 | GPIO input, pull-up | active low |
| STOP/fault loop | PB1 | GPIO input, pull-up | low=healthy; high=STOP/wire break |
| Blue state lamp relay | PB10 | output push-pull | inactive high |
| Yellow state lamp relay | PB11 | output push-pull | inactive high |
| Green battery lamp relay | PB12 | output push-pull | inactive high |
| Red battery lamp relay | PB13 | output push-pull | inactive high |

The inexpensive relay boards are often low-level triggered, but variants differ.
Before connecting the safety wiring, power one board on the bench and verify that
the relay is released during MCU reset. If polarity differs, change
`RES_OUTPUT_ACTIVE_LOW`; do not invert application logic ad hoc.

## 5. Add files to generated project

- The supplied STM32CubeIDE `.project` already links `res_protocol_build.c`,
  `res_remote_app.c`, `ina226.c` and `res_stm32_port.c`.
- `main.c` already calls `RES_Application_Init()` after all `MX_*_Init()` calls,
  runs `RES_Application_Task()` continuously, and forwards the UART callback.

```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    RES_Application_UART_RxComplete(huart);
}
```

Replace `RES_DEMO_AUTH_KEY_BYTES` with a random team key supplied through a local,
untracked header. The demo key is public and provides no security.
