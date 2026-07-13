# LTspice timing verification report

Run date: 2026-05-18
LTspice: 26.0.1 for Windows

## Inputs

- Interface workbook: `fin/硬件电路接口.xlsx`
- Board sources: `fin/*.png`, `fin/*.tel`
- LTspice decks: `simulations/*.cir`
- LTspice logs/waveforms: `simulations/*.log`, `simulations/*.raw`

## Official models downloaded

Downloaded from TI official `ti.com/lit/zip` URLs into `models/official/` and expanded under `models/official/extracted/`.

- LM2596-5.0 transient model: `snvma62`
- LM393 / LM2903B comparator model: `slcj016`
- TL331 comparator model: `slvm937`
- SN74LVC1G08: `scem642`
- SN74LVC1G14: `scem637`
- SN74LVC1G17: `scem635`
- SN74LVC2G17: `scem615`
- SN74LVC1G00: `scem646`
- SN74AHC1G00: `sclm277`
- SN74LVC1G332: `scem631`
- SN74LVC2G02: `scem624`
- SN74LV1T32: `sclm181`
- SN74LVC2G74 HSPICE package: `scej238`

Local LTspice library also contains `NE555.sub` and Toshiba encrypted 2N7002 contribution models.

## Results

| Board | LTspice deck | Result | Key measurements |
|---|---|---:|---|
| 继电器检测 | `relay_detection.cir` | PASS | Contact closed: sense=4.733 V, `*_ACTUAL`=5.000 V, `*#`=0 V. Contact open: sense=0.019 V, `*_ACTUAL`=0 V, `*#`=5.000 V. This matches the workbook polarity. |
| EBS | `ebs.cir` | PASS | Normal: `EBS_WORK`=24 V, `AS_LOCK`=4.225 V. Watchdog fault: `EBS_WORK`=0 V. `EBS_TRIG` fault: `EBS_WORK`=0 V. Recovery: `EBS_WORK`=24 V. |
| 锁存 | `lock_latch.cir` | PASS | Normal: `SDC_OUT`=24 V. IMD fault: state low and `SDC_OUT`=0 V. Fault remains latched after input recovery. Reset low restores state and `SDC_OUT`=24 V. |
| BSPD | `bspd.cir` | CONDITIONAL PASS | Fault condition asserts at 100.93 ms and `SDC_OUT` trips at 415.22 ms, so trip delay is 314.29 ms (<500 ms). After the conflict clears, `SDC_OUT` remains 0 V past 10 s and returns to 24 V after BSPD power/reset. Oil pressure thresholds are not specified in the workbook, so threshold correctness cannot be fully verified. |
| TSAL | `tsal.cir` | PASS | Red lamp blink period is 360.36 ms, frequency is 2.775 Hz, and duty is 51.92%. Unsafe/high-voltage state blinks red with `GREEN_OUT_K` high; safe/open-relay state has `RED_OUT_K`=5 V and `GREEN_OUT_K`=0 V. |

## Important limitations

- The available board files are PNG schematics plus `.tel` package/net lists, not native LTspice `.asc` schematics. The decks therefore verify the timing and interface logic, not parasitic-accurate full PCB analog behavior.
- UCC2946, relay coils/contacts, fuses, AO3400/AO3480C MOSFETs, and some diodes did not have directly usable official LTspice SPICE models in the searched official sources; those parts are represented by behavioral equivalents where they do not affect the interface timing conclusion.
- The TI SN74LVC2G74 package is official HSPICE, not directly used as an LTspice D flip-flop model here. Latch behavior was modeled behaviorally according to the schematic and interface table.
- `硬件电路接口.xlsx` marks BSPD oil-pressure thresholds as not measured, so BSPD cannot be fully qualified until those thresholds and timing tolerance are defined.
