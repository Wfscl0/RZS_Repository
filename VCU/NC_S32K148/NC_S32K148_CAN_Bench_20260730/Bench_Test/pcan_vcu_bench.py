#!/usr/bin/env python3
"""VCU CAN0 single-bus bench tester for PEAK PCAN adapters.

The script transmits the simulated-node and debug 11-bit standard frames on
the VCU CAN0 bench connector. The VCU also emits its motor-control extended
frames on this bus, so keep the inverter disconnected or positively disabled.
"""

from __future__ import annotations

import argparse
import pathlib
import sys
import time

import can
import cantools


DEBUG_CONTROL = 0x7A0
DEBUG_PEDAL = 0x7A1
DEBUG_AIR = 0x7A2
DEBUG_DIGITAL = 0x7A3
DEBUG_STATUS = 0x7B0
DEBUG_PEDAL_ECHO = 0x7B1
DEBUG_AIR_ECHO = 0x7B2

LOX_NAMES = {
    0: "Brake lamp",
    1: "ASSI blue",
    2: "ASSI yellow",
    3: "EBS error lamp",
    4: "RES error",
}
HOX_NAMES = {
    0: "EBS trigger",
    1: "BMS error lamp",
    2: "IMD error lamp",
    3: "DI8",
    4: "RUN",
    5: "R2D buzzer",
    6: "Emergency buzzer",
}


def u16_le(value: int) -> bytes:
    return int(value).to_bytes(2, byteorder="little", signed=False)


def adc5_count(volts: float) -> int:
    return max(0, min(0xFFFF, round(volts / 0.0001875)))


def air_count(mpa: float) -> int:
    return max(0, min(0xFFFF, round(mpa / 0.000241699219)))


def active_names(value: int, names: dict[int, str]) -> str:
    result = [name for bit, name in names.items() if value & (1 << bit)]
    return ", ".join(result) if result else "none"


class BenchFrames:
    def __init__(self, database: cantools.database.Database, scenario: str):
        self.db = database
        self.scenario = scenario
        self.counter = 0
        self.heartbeat = 0
        self.esp_life = 0

    def debug_control(self) -> bytes:
        return bytes((0xA5, 0x5A, 0x0F, self.counter, 0, 0, 0, 0))

    def debug_pedal(self, elapsed: float) -> bytes | None:
        if self.scenario == "pedal-timeout" and elapsed >= 2.5:
            return None
        brake_v = 0.0 if self.scenario == "brake-open" and elapsed >= 2.5 else 0.5
        return b"".join(
            (u16_le(adc5_count(0.252)), u16_le(adc5_count(0.252)),
             u16_le(adc5_count(brake_v)), bytes((self.counter, 0)))
        )

    def debug_air(self) -> bytes:
        # 0.40 MPa reservoir and 0.20 MPa downstream avoid an EBS-working
        # indication while retaining plausible, nonzero sensor values.
        return b"".join(
            (u16_le(air_count(0.40)), u16_le(air_count(0.20)),
             u16_le(0), u16_le(0))
        )

    def debug_digital(self) -> bytes:
        # HIN1, HIN4, HIN5, HIN6 and HIN7 high; ASMS (HIN8) remains off.
        # The vehicle-state machine therefore stays in the manual/low-risk path.
        hin = 0x0079
        return u16_le(hin) + bytes((self.counter, 0, 0, 0, 0, 0))

    def res(self) -> bytes:
        byte0 = 0x04  # communication=1, Go/Stop=0
        byte1 = self.heartbeat
        return bytes((byte0, byte1, byte0 ^ byte1, 0, 0, 0, 0, 0))

    def encode(self, message_name: str, values: dict[str, float | int]) -> bytes:
        message = self.db.get_message_by_name(message_name)
        return message.encode(values, strict=False)

    def esp_t03(self) -> bytes:
        return self.encode("ESP_T_03", {
            "curPrsFL": 1.00,
            "curPrsFR": 1.00,
            "curPrsRL": 1.00,
            "curPrsRR": 1.00,
            "esp13_lifeSig": self.esp_life,
            "esp13_checkSum": 0,
        })

    def ipc_msg1(self) -> bytes:
        return self.encode("IPC_Tx_Msg1", {
            "ipc_esp_flprs": 0,
            "ipc_esp_frprs": 0,
            "ipc_esp_rlprs": 0,
            "ipc_esp_rrprs": 0,
            "ipc_motor_torque": 0,
        })

    def ipc_msg2(self) -> bytes:
        return self.encode("IPC_Tx_Msg2", {
            "ipc_cmd_angle": 0,
            "ipc_eps_velocity": 20,
            "ipc_heartbeat": self.counter & 0x0F,
            "ipc_task_finish": 0,
            "ipc_err": 0,
            "ipc_lspd": 0,
            "ipc_hspd": 0,
        })

    def ami(self) -> bytes:
        return self.encode("AMI_Tx", {"ami_astask": 1})

    def eps_msg1(self) -> bytes:
        return self.encode("EPS_Send_Msg1", {
            "eps_workmode": 0,
            "eps_torque": 0,
            "eps_errorcode1": 0,
            "eps_angle": 0,
            "eps_middlefeedback": 0,
            "eps_errorcode2": 0,
            "eps_send_xor": 0,
        })

    def eps_msg2(self) -> bytes:
        return self.encode("EPS_Send_Msg2", {
            "eps2_workmode": 0,
            "eps2_received_command_count": self.counter,
            "eps2_received_angle": 0,
            "eps2_actual_angle": 0,
            "eps2_send_counter": self.counter,
        })

    def tick_20ms(self) -> None:
        self.esp_life = (self.esp_life + 1) & 0x0F

    def tick_50ms(self) -> None:
        self.heartbeat = (self.heartbeat + 1) & 0xFF

    def tick_100ms(self) -> None:
        self.counter = (self.counter + 1) & 0xFF


def send(bus: can.BusABC, arbitration_id: int, payload: bytes) -> None:
    bus.send(can.Message(
        arbitration_id=arbitration_id,
        is_extended_id=False,
        data=payload,
    ), timeout=0.02)


def decode_status(database: cantools.database.Database, message: can.Message):
    try:
        return database.decode_message(message.arbitration_id, message.data,
                                       decode_choices=False)
    except (KeyError, ValueError, cantools.database.errors.DecodeError):
        return None


def main() -> int:
    parser = argparse.ArgumentParser(description="VCU CAN0 single-bus PCAN bench test")
    parser.add_argument("--channel", default="PCAN_USBBUS1",
                        help="python-can PCAN channel (default: PCAN_USBBUS1)")
    parser.add_argument("--bitrate", type=int, default=500000)
    parser.add_argument("--duration", type=float, default=8.0)
    parser.add_argument("--scenario", choices=("override", "pedal-timeout", "brake-open"),
                        default="override")
    parser.add_argument("--dbc", type=pathlib.Path,
                        default=pathlib.Path(__file__).resolve().parents[1]
                        / "DBC" / "VCU_TSMaster_Debug.dbc")
    args = parser.parse_args()

    if args.duration < 4.0:
        parser.error("duration must be at least 4 seconds")

    database = cantools.database.load_file(args.dbc, strict=False)
    frames = BenchFrames(database, args.scenario)

    print("WARNING: connect to VCU CAN0; disconnect or positively disable the inverter.")
    print(f"PCAN channel={args.channel}, bitrate={args.bitrate}, scenario={args.scenario}")

    bus = can.Bus(interface="pcan", channel=args.channel, bitrate=args.bitrate)
    start = time.monotonic()
    next_20 = start
    next_50 = start
    next_100 = start
    next_print = start
    latest: dict[int, dict] = {}
    saw_all_active = False
    saw_pedal_timeout = False
    saw_ebs_error_before = False
    saw_ebs_error_after = False

    try:
        while True:
            now = time.monotonic()
            elapsed = now - start
            if elapsed >= args.duration:
                break

            if now >= next_20:
                send(bus, 0x013, frames.esp_t03())
                send(bus, 0x011, frames.ipc_msg1())
                send(bus, 0x012, frames.ipc_msg2())
                send(bus, 0x042, frames.ami())
                send(bus, 0x401, frames.eps_msg1())
                send(bus, 0x402, frames.eps_msg2())
                frames.tick_20ms()
                next_20 += 0.020

            if now >= next_50:
                send(bus, 0x1E4, frames.res())
                frames.tick_50ms()
                next_50 += 0.050

            if now >= next_100:
                send(bus, DEBUG_CONTROL, frames.debug_control())
                pedal = frames.debug_pedal(elapsed)
                if pedal is not None:
                    send(bus, DEBUG_PEDAL, pedal)
                send(bus, DEBUG_AIR, frames.debug_air())
                send(bus, DEBUG_DIGITAL, frames.debug_digital())
                frames.tick_100ms()
                next_100 += 0.100

            received = bus.recv(timeout=0.005)
            if received is not None and not received.is_extended_id:
                decoded = decode_status(database, received)
                if decoded is not None:
                    latest[received.arbitration_id] = decoded

            status = latest.get(DEBUG_STATUS)
            if status:
                all_active = all(status.get(name, 0) == 1 for name in (
                    "Dbg_ActiveMaster", "Dbg_ActivePedalADC",
                    "Dbg_ActiveAirWheel", "Dbg_ActiveDigital"))
                saw_all_active |= all_active
                if elapsed >= 3.0 and status.get("Dbg_ActivePedalADC", 1) == 0:
                    other_active = all(status.get(name, 0) == 1 for name in (
                        "Dbg_ActiveMaster", "Dbg_ActiveAirWheel", "Dbg_ActiveDigital"))
                    saw_pedal_timeout |= other_active

                lox = int(status.get("Dbg_ModelLOX", 0))
                if elapsed < 2.5:
                    saw_ebs_error_before |= bool(lox & (1 << 3))
                else:
                    saw_ebs_error_after |= bool(lox & (1 << 3))

            if now >= next_print:
                status = latest.get(DEBUG_STATUS, {})
                lox = int(status.get("Dbg_ModelLOX", 0))
                hox = int(status.get("Dbg_ModelHOX", 0))
                ami = latest.get(0x041, {}).get("ami_process", "-")
                print(
                    f"t={elapsed:5.2f}s active="
                    f"{int(status.get('Dbg_ActiveMaster', 0))}"
                    f"{int(status.get('Dbg_ActivePedalADC', 0))}"
                    f"{int(status.get('Dbg_ActiveAirWheel', 0))}"
                    f"{int(status.get('Dbg_ActiveDigital', 0))} "
                    f"LOX=0x{lox:02X}[{active_names(lox, LOX_NAMES)}] "
                    f"HOX=0x{hox:02X}[{active_names(hox, HOX_NAMES)}] "
                    f"AMI={ami}"
                )
                next_print += 0.5
    finally:
        # Send an explicit disable before releasing the PCAN handle. The VCU
        # also exits every override automatically after 500 ms.
        try:
            send(bus, DEBUG_CONTROL, bytes((0xA5, 0x5A, 0, 0, 0, 0, 0, 0)))
            time.sleep(0.05)
        finally:
            bus.shutdown()

    if args.scenario == "override":
        passed = saw_all_active
        criterion = "all four override groups became active"
    elif args.scenario == "pedal-timeout":
        passed = saw_all_active and saw_pedal_timeout
        criterion = "pedal override expired while the other groups stayed active"
    else:
        passed = saw_all_active and (not saw_ebs_error_before) and saw_ebs_error_after
        criterion = "brake open-circuit caused EBS error output bit3 to rise"

    print(("PASS: " if passed else "FAIL: ") + criterion)
    return 0 if passed else 2


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except can.CanError as error:
        print(f"PCAN error: {error}", file=sys.stderr)
        raise SystemExit(3)
