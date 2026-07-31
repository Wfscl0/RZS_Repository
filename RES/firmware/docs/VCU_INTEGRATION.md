# VCU integration contract

## CAN status frame 0x510 (8 bytes, 50 ms)

| Byte | Meaning |
|---:|---|
| 0 | protocol version (`1`) |
| 1 | state: 0 boot, 1 wait link, 2 ready, 3 GO event, 4 stopped/fault |
| 2..3 | little-endian flags from `res_can_contract.h` |
| 4 | current RF channel index |
| 5 | bit0 relay 1 command, bit1 relay 2 command |
| 6..7 | little-endian GO event counter |

## Required VCU supervision

VCU owns `RES_ERROR`. Run this check in a fixed-period safety task, not only in a
CAN receive callback:

```c
if (now_ms - last_valid_res_status_ms > 150u ||
    status.version != 1u ||
    status.state == RES_CAN_STATE_STOPPED_FAULT ||
    (status.flags & (RES_CAN_FLAG_REMOTE_STOP |
                     RES_CAN_FLAG_RADIO_TIMEOUT |
                     RES_CAN_FLAG_RELAY_MISMATCH |
                     RES_CAN_FLAG_SOFTWARE_LATCHED)) != 0u ||
    (status.state == RES_CAN_STATE_READY && status.relay_bits != 0x03u)) {
    RES_ERROR = 1;                 /* drive the separate hardware circuit */
} else {
    RES_ERROR = 0;
}
```

For autonomous-system start, accept CAN ID `0x511` only if it carries a new
command counter, the most recent `0x510` is READY/link-valid, both relay bits are
set, and all independent AS Ready preconditions pass. `START_OUT` is a redundant
100 ms electrical indication; it must not bypass those checks.

On VCU boot, CAN bus-off, decoder error or task overrun, default `RES_ERROR` to
active. The VCU-generated error reaches the existing non-programmable hardware
fault/lock circuit; it is not looped back as a software command to this receiver.
