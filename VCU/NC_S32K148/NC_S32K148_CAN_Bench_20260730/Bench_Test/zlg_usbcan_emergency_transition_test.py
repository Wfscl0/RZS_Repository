#!/usr/bin/env python3
"""Focused ZLG USBCAN test for autonomous Emergency transitions."""

from __future__ import annotations

import argparse
import ctypes
import pathlib
import sys
import time


HERE = pathlib.Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import pcan_autonomous_state_machine_test as suite  # noqa: E402
from zlg_usbcan_autonomous_state_machine_test import ZlgPcanCompatibility  # noqa: E402


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cause", choices=("res-stop", "asms-drop",
                                             "res-stop-driving", "brake-open",
                                             "res-timeout", "ebs-working"),
                        required=True)
    args = parser.parse_args()

    api = ZlgPcanCompatibility()
    status = api.CAN_Initialize(0, 0, 0, 0, 0)
    if status != suite.PCAN_ERROR_OK:
        print(f"RESULT PRECONDITION FAIL: USBCAN init 0x{status:08X}")
        return 3

    rig = suite.TestRig(api)
    try:
        rig.receive_all()
        rig.run(1.2)
        if rig.state() != 1:
            print(f"RESULT PRECONDITION FAIL: expected AS_Off, got {rig.state_name()}")
            return 3

        rig.stim.hin = 0x00F9
        rig.run(0.20)
        rig.stim.hin = 0x00C9
        rig.run(0.20)
        rig.stim.hin = 0x00F9
        if not rig.wait_state(4, 2.0, "Off -> Ready"):
            print("RESULT FAIL: pre-emergency Ready not reached")
            return 2

        if args.cause == "res-stop-driving":
            rig.stim.res_go = True
            rig.stim.eps_angle = 0
            if not rig.wait_state(16, 6.0, "Ready -> Driving"):
                print("RESULT FAIL: Driving not reached before emergency")
                return 2
            rig.stim.res_stop = True
            label = "validated RES Stop while Driving"
        elif args.cause == "res-stop":
            rig.stim.res_stop = True
            label = "validated RES Stop"
        elif args.cause == "brake-open":
            rig.stim.brake_adc = 0
            label = "brake sensor open circuit"
        elif args.cause == "res-timeout":
            rig.stim.freeze_res_heartbeat = True
            label = "RES heartbeat timeout"
        elif args.cause == "ebs-working":
            rig.stim.air2_adc = 2600  # Approximately 6.28 V, above 6 V threshold.
            label = "EBS downstream pressure active"
        else:
            rig.stim.hin = 0x0079
            label = "ASMS deassertion"

        rig.wait_state(64, 2.0, label + " -> Emergency")
        rig.run(0.25)
        eps, esp, enable, torque = rig.output_snapshot()
        rig.assert_true(eps == 0 and esp == 0 and enable == 0 and torque == 0,
                        "Emergency disables EPS/ESP/traction",
                        f"EPS={eps}, ESP={esp}, enable={enable}, motor={torque} Nm")

        rig.stim.res_stop = False
        rig.stim.freeze_res_heartbeat = False
        rig.stim.brake_adc = suite.adc5(0.50)
        rig.stim.air2_adc = 2000
        rig.stim.esp_pressure = 0.0
        rig.stim.hin = 0x0079
        rig.wait_state(1, 1.5, "Emergency -> Off after safe release")

        rig.stim.esp_pressure = 1.0
        rig.stim.hin = 0x00F9
        rig.run(1.0)
        rig.assert_true(rig.state() == 1,
                        "safety lock prevents automatic restart",
                        rig.state_name())

        rig.assert_true(api.CAN_GetStatus(0) == suite.PCAN_ERROR_OK,
                        "USBCAN channel remains open")
        print("TRACE " + " -> ".join(rig.trace))
        if rig.failures:
            print(f"RESULT FAIL ({len(rig.failures)} checks)")
            for failure in rig.failures:
                print(" - " + failure)
            return 2
        print("RESULT PASS: " + label + " emergency path")
        return 0
    finally:
        try:
            rig.send(suite.ID_DBG_CONTROL,
                     bytes((0xA5, 0x5A, 0, 0, 0, 0, 0, 0)))
            time.sleep(0.05)
        finally:
            api.CAN_Uninitialize(0)


if __name__ == "__main__":
    raise SystemExit(main())
