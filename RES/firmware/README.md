# 2026 RES firmware

This directory contains the two STM32G0B1 applications and the two E220-board
STM8 radio bridges for the current modular RES prototype.

Chinese delivery, pinout and programming notes are in
`docs/DELIVERY_CN.md`.

## Buildable projects

- `remote_g0b1/RES_Remote_G0B1.ioc` and `remote_g0b1/STM32CubeIDE`: handheld
  controller, buttons, INA226, four indicators and E220 UART.
- `vehicle_g0b1/RES_Vehicle_G0B1.ioc` and `vehicle_g0b1/STM32CubeIDE`: vehicle
  receiver, two relay drives, START/FAULT logic outputs, Classic CAN and E220.
- `radio_bridge_stm8`: replacements for Ebyte's official STM8L151G4 example;
  install the same code and frequency table at both ends.
- `shared`: authenticated wire protocol, replay protection, hopping function and
  CAN payload contract.
- `tests`: hardware-independent state-machine and protocol tests.

Open each `STM32CubeIDE` directory as an existing project. The `.project` files
already link every RES source file. If CubeMX regenerates a project, preserve the
USER CODE blocks in `main.c` and re-check that the four custom RES `.c` files are
still linked in the IDE project.

## Safety state behavior

| Situation | Relay 1 | Relay 2 | Vehicle state |
|---|---:|---:|---|
| both ends unpowered | open | open | no power |
| receiver powered, remote absent/self-testing | closed | open | WAIT_LINK |
| authenticated link, remote READY | closed | closed | READY |
| fresh GO edge | closed | closed | 100 ms START_OUT + CAN event |
| E-stop, authenticated STOP or >500 ms radio loss | open | open | latched fault |
| remote restarted, new authenticated session, three READY frames | closed | closed | READY |

The handheld's startup STOP is only an input/power self-test state; it is not a
latched E-stop command. A real STOP is sent repeatedly over all three channels.
Once latched, the receiver ignores same-session READY frames. Recovery requires
the E-stop to be released and the handheld to be power-cycled, creating a new
authenticated session.

## Automatic hopping

Every authenticated frame contains its physical channel, session and sequence.
The two STM32 endpoints and both STM8 bridges calculate the same deterministic
next channel. Local UART frames force the bridge to their declared channel before
TX. A bridge that misses a frame scans all three channels using 240 ms dwell
windows until it receives a valid RES frame. Thus hopping is physical, not just a
channel field in the packet.

The bench table is in `radio_bridge_stm8/res_bridge_config.h`. It must be reviewed
for event allocation, occupied bandwidth, output power/EIRP and local radio rules
before use. Both E220 bridges must contain the identical table. The official
Ebyte default must also be changed from air-rate index 2 to index 4 as described
in `radio_bridge_stm8/README.md`.

## CAN/VCU responsibility

The receiver sends 8-byte Classic CAN frames at 500 kbit/s:

- `0x510 RES_STATUS`, every 50 ms;
- `0x511 RES_GO_EVENT`, once per new operator GO action;
- `0x512 RES_DIAGNOSTIC`, accompanying a GO event.

The receiver does **not** create `RES_ERROR`. VCU validates `0x510`, detects CAN
timeout or inconsistent states and drives the separate RES_ERROR hardware line.
See `docs/VCU_INTEGRATION.md`.

## Watchdog and electrical defaults

Both `.ioc` files enable IWDG at prescaler 32/reload 999 (nominal ~1 s from the
32 kHz LSI). Vehicle relay outputs are initialized inactive and require external
pull-ups so MCU reset or an unpowered GPIO cannot energize the low-trigger relay
modules. Software never refreshes the watchdog from an interrupt.

Replace `RES_DEMO_AUTH_KEY_BYTES` at both ends with one random, team-private
16-byte key stored outside version control. The public demo key provides no
authentication security.

## Host verification

On this Windows host the configured MinGW build is:

```powershell
cmake --build firmware/build-mingw --clean-first
ctest --test-dir firmware/build-mingw --output-on-failure
```

These tests validate algorithms and state transitions only. Before vehicle use,
complete the HIL/fault-injection matrix in `docs/VERIFICATION.md`; software tests
cannot certify the relay modules, CAN transceiver, RF range or competition
compliance.
