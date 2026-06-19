# TSAL LTspice checked high-precision project

Open `TSAL_checked_high_precision.asc` in LTspice with all files in this folder.

## Important corrections/checks

- U18/U19 are `SN74LVC1G32DBVR`: pin 1=A, pin 2=B, pin 3=GND, pin 4=Y, pin 5=VCC.
- TL331 DBV is modeled as pin 1=IN-, pin 2=GND, pin 3=IN+, pin 4=OUT, pin 5=VCC.
  This is essential: U1 releases RESET high when `V_CONTROLLER > 0.6V`; U2 releases `V_SAFE` high when `V_BATTERY < 0.6V`.
- U13 is `SN74LV1T32DBVR` OR, not AND. It implements `FAULT_SET = V_DISCONNECT OR REL_FAULT_SET`.
- U15 is `SN74LVC1G14DBVR` inverter and U20 is `SN74LVC1G17QDCKRQ1` Schmitt buffer.
- The TEL netlist shows U20.A/R64 tied to GND, which prevents a real POR pulse. For the definition-compliant simulation,
  this project connects `C18/R55` POR RC through R64 into U20.A. U20.Y is `POR_RESET` (`N1N198`).

## Internal logic nets

- `N1N12`: red comparator output / 555 RESET. High means red flash enabled.
- `V_SAFE`: green voltage comparator output. High means `V_BATTERY <= 0.6V`.
- `REL_FAULT_SET`: relay open-circuit fault = OR of three `DISCONNECT AND SHOULD` terms.
- `N1N133`: total fault = `V_DISCONNECT OR REL_FAULT_SET`.
- `N1N198`: POR reset pulse from U20.
- `N1N93`: latch OK, high when no latched fault.
- `N1N130`: green MOS gate drive.

## Testbench timing and expected results

| Time window | Stimulus | Expected RED_OUT_K | Expected GREEN_OUT_K |
|---:|---|---|---|
| 0-20 ms | Power-up, safe battery, relays actual open, no fault | High/off | Low/on after POR |
| 25-60 ms | `V_CONTROLLER > 0.6V` | 2-5 Hz low pulses/on pulses | Low/on if battery safe and latch OK |
| 40-55 ms | `V_BATTERY > 0.6V` | As above | High/off |
| 81-100 ms | `MAINP_ACTUAL = 0` | Off unless controller high | High/off |
| 120-130 ms | `MAINP_DISCONNECT=1` and `MAINP_SHOULD=1` | Off unless controller high | Goes high/off and remains latched |
| 131-160 ms | Fault input removed | Off unless controller high | Remains high/off |
| 161-176 ms | 12V power cycle | Off | Reset interval |
| 176-209 ms | Power restored, no fault | Off | Low/on after POR |
| 210-220 ms | `V_DISCONNECT=1` | Off unless controller high | Goes high/off and remains latched |

`RED_OUT_K` and `GREEN_OUT_K` are low-side sink nodes: low voltage means the external LED is ON.
