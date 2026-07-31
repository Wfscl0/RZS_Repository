# RES vehicle controller — STM32G0B1CBT6

Open `RES_Vehicle_G0B1.ioc` with STM32CubeMX and generate for STM32CubeIDE.
The intended clock is HSI16 -> PLL /1 x8 /2 = 64 MHz.

## Pin contract

| Function | Pin | Configuration | Reset-safe requirement |
|---|---:|---|---|
| E220 TX/RX | PA9/PA10 | USART1, 9600 8N1, RX interrupt | 3.3 V logic |
| CAN RX/TX | PB8/PB9 | FDCAN1, classic CAN 500 kbit/s | external transceiver |
| CAN STB | PA0 | output, initially high | module standby until app init |
| Relay 1 | PB10 | output, initially high | external 4.7–10 kOhm pull-up |
| Relay 2 | PB11 | output, initially high | external 4.7–10 kOhm pull-up |
| START_OUT | PB12 | output, initially low | VCU logic input only |
| FAULT_OUT | PB13 | output, initially high | VCU logic input only |

FDCAN nominal timing at 64 MHz is prescaler 8, TSEG1 13, TSEG2 2,
SJW 2: 16 time quanta/bit, 500 kbit/s, 87.5% sample point. The frame format is
classic CAN, not CAN-FD.

## Integration hooks

Add `res_protocol.c`, `res_can_contract.c`, `res_vehicle_app.c`, and
`res_vehicle_stm32_port.c` to the build. Add shared/include and Core/Inc to the
include search path. After CubeMX initialization call
`RES_Vehicle_Application_Init()`, then call `RES_Vehicle_Application_Task()` in
the main loop. Forward `HAL_UART_RxCpltCallback()` to
`RES_Vehicle_UART_RxComplete()`.

`RES_ERROR` is deliberately absent here. VCU software evaluates CAN ID 0x510
and its timeout, then drives the separate hardware RES_ERROR circuit.
