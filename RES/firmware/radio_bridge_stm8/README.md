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

## 2026-09-15 streaming repair

The ready-overlaid SDK now also changes its USART RX interrupt to call
`RES_Bridge_OnUartByte(temp)`. Do not deploy only the replacement main:
without this ISR change the new ring buffer receives nothing.

The bridge drains an ISR-fed 128-byte ring (127 usable) continuously and uses
the RES header length and CRC to forward individual frames without waiting
for the demonstration FIFO's 500-tick idle flag. Two consecutive 37-byte
frames no longer become one rejected 74-byte batch. Overflow discards queued
partial data and resumes searching for a complete CRC-valid frame.

On RF reception the bridge validates CRC and arms the next receive channel
before writing the frame to the STM32 UART. The selected E220 driver no
longer overwrites that bounded receive dwell with SetRx(0) after the callback.
Invalid RF frames are discarded and scanning resumes. No authentication keys
or safety input overrides are added.

Host tests cover fragmentation, adjacent frames, CRC errors, maximum frames,
overflow recovery, and receive rearming. These tests do not verify STM8 code
size, physical RF timing, USB-TX contention, or ASF acceptance.

Current repair is source-only until compiled with IAR for STM8 and deployed
to BOTH board STM8L151G4 devices over SWIM. The STM32 J-Link SWD connections
and CH340 Micro-USB serial ports cannot by themselves deploy this firmware.
Keep the original STM8 firmware backed up where readout protection permits;
do not unlock/erase readout protection to obtain a backup.

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
