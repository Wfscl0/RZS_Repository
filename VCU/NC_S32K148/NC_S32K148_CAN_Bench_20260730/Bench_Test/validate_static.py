#!/usr/bin/env python3
"""Dependency-free structural check for the VCU bench DBC."""

from __future__ import annotations

import pathlib
import re


DBC = pathlib.Path(__file__).resolve().parents[1] / "DBC" / "VCU_TSMaster_Debug.dbc"

EXPECTED = {
    0x7A0: ("VCU_DBG_Control", {"Dbg_Unlock", "Dbg_MasterEnable"}),
    0x7A1: ("VCU_DBG_PedalADC", {"Dbg_APP1_V", "Dbg_APP2_V", "Dbg_Brake_V"}),
    0x7A2: ("VCU_DBG_AirWheel", {"Dbg_AirPressure1", "Dbg_AirPressure2"}),
    0x7A3: ("VCU_DBG_Digital", {"Dbg_HIN1_EBSDriverCheck", "Dbg_HIN8_ASMS"}),
    0x7B0: ("VCU_DBG_Status", {"Dbg_ActiveMaster", "Dbg_ModelLOX", "Dbg_ModelHOX"}),
    0x7B1: ("VCU_DBG_PedalEcho", {"Dbg_EchoAPP1_V", "Dbg_EchoBrake_V"}),
    0x7B2: ("VCU_DBG_AirWheelEcho", {"Dbg_EchoAirPressure1", "Dbg_EchoAirPressure2"}),
}


def main() -> int:
    text = DBC.read_text(encoding="utf-8")
    messages: dict[int, tuple[str, int, set[str]]] = {}
    current_id: int | None = None

    for line in text.splitlines():
        message = re.match(r"BO_\s+(\d+)\s+(\w+):\s+(\d+)\s+", line)
        if message:
            current_id = int(message.group(1))
            messages[current_id] = (message.group(2), int(message.group(3)), set())
            continue
        signal = re.match(r"\s+SG_\s+(\w+)\s+:", line)
        if signal and current_id is not None:
            messages[current_id][2].add(signal.group(1))

    for arbitration_id, (expected_name, expected_signals) in EXPECTED.items():
        assert arbitration_id in messages, f"missing ID 0x{arbitration_id:03X}"
        name, dlc, signals = messages[arbitration_id]
        assert name == expected_name, f"0x{arbitration_id:03X}: {name} != {expected_name}"
        assert dlc == 8, f"0x{arbitration_id:03X}: DLC {dlc} != 8"
        missing = expected_signals - signals
        assert not missing, f"0x{arbitration_id:03X}: missing signals {sorted(missing)}"

    print(f"DBC_STATIC_CHECK=PASS ({len(messages)} messages, {len(EXPECTED)} debug messages)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
