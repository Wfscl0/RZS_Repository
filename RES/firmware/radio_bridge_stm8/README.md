# E220-400MBL-01 board MCU bridge

`E220_IAR_SDK/3_代码工程/0_Project/IAR_for_Stm8/Uart_PingPong/project.eww`
is a ready-overlaid copy of Ebyte's official project. Open it directly in IAR
for STM8. This folder also keeps the individual replacement files for review.

The replacements are based on Ebyte's official
`E15-EVB02_E220-400M22S/3_代码工程/0_Project/IAR_for_Stm8/Uart_PingPong`
project:

1. Replace the project's `main.c` with `res_bridge_main.c`.
2. Replace `ebyte/E220xMx/ebyte_callback.c` with `res_bridge_callback.c`.
3. Add `res_bridge_config.h` and `res_bridge_control.h` to the include path.
4. In `ebyte/E220xMx/ebyte_e220x.h`, change `RF_LORA_AIR_BPS` from `2` to
   `4` (SF8/BW500/CR4/6, nominal 9.6 kbit/s). The default SF11 mode is too slow
   for the 200 ms application heartbeat.
5. Keep `EBYTE_RF_TRANSMIT_CHECK_MODE=1`; frequency changes after a send assume
   the official blocking transmit-completion check.
6. Select the `E220xMx` driver/configuration and build for STM8L151G4 in IAR.
7. Program both radio boards through their SWIM and RESET pins.

The bridge checks framing and CRC, tunes to the channel carried by each local TX
frame, transmits it, then executes the same deterministic next-channel function
as the STM32 endpoints. After an RF receive timeout it scans the three channels
in order; a valid frame restores the deterministic sequence. It forwards RF
frames unchanged and does not possess the authentication key, so it cannot grant
GO by itself.

The official example contains callback expressions such as `state &= mask`.
The replacements use `state & mask`; do not copy the original expressions back.

The frequency table in `res_bridge_config.h` is a bench plan, not a radio-law or
competition approval. Confirm permitted frequencies, occupied bandwidth, output
power/EIRP and duty cycle, then program the identical table into both bridges.
