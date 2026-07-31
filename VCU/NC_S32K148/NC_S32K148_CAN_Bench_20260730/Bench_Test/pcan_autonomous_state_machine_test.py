#!/usr/bin/env python3
"""Closed-loop CAN0 bench test for the VCU autonomous state machine.

The test uses only PCAN-Basic and keeps all simulated-node messages alive.  It
verifies the autonomous state sequence, actuator-command gating, sensor fault
debounce/recovery, RES communication monitoring, emergency response and the
post-emergency safety latch.

Power actuators and the inverter must be disconnected or positively disabled.
"""

from __future__ import annotations

import ctypes
import pathlib
import time


PCAN_USBBUS1 = 0x51
PCAN_BAUD_500K = 0x001C
PCAN_MESSAGE_STANDARD = 0x00
PCAN_ERROR_OK = 0x00000
PCAN_ERROR_QRCVEMPTY = 0x00020

ID_RES = 0x1E4
ID_IPC1 = 0x011
ID_IPC2 = 0x012
ID_ESP3 = 0x013
ID_ESP6 = 0x016
ID_ESP7 = 0x017
ID_AMI_TX = 0x042
ID_EPS1 = 0x401
ID_EPS2 = 0x402
ID_DBG_CONTROL = 0x7A0
ID_DBG_PEDAL = 0x7A1
ID_DBG_AIR = 0x7A2
ID_DBG_DIGITAL = 0x7A3

ID_ESP_CMD = 0x020
ID_AMI_RX = 0x041
ID_EPS_CMD = 0x469
ID_DBG_STATUS = 0x7B0
ID_MOTOR_CMD = 0x0CFF08EF

STATE = {
    1: "AS_Off",
    2: "Manual_Driving",
    4: "AS_Ready",
    8: "R2D",
    16: "AS_Driving",
    32: "AS_Finished",
    64: "AS_Emergency",
}


class TPCANMsg(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("ID", ctypes.c_uint32),
        ("MSGTYPE", ctypes.c_uint8),
        ("LEN", ctypes.c_uint8),
        ("DATA", ctypes.c_uint8 * 8),
    ]


class TPCANTimestamp(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("millis", ctypes.c_uint32),
        ("millis_overflow", ctypes.c_uint16),
        ("micros", ctypes.c_uint16),
    ]


def load_api() -> ctypes.WinDLL:
    dll = pathlib.Path(r"C:\Windows\System32\PCANBasic.dll")
    api = ctypes.WinDLL(str(dll))
    api.CAN_Initialize.argtypes = [ctypes.c_uint16, ctypes.c_uint16,
                                   ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint16]
    api.CAN_Initialize.restype = ctypes.c_uint32
    api.CAN_Uninitialize.argtypes = [ctypes.c_uint16]
    api.CAN_Uninitialize.restype = ctypes.c_uint32
    api.CAN_GetStatus.argtypes = [ctypes.c_uint16]
    api.CAN_GetStatus.restype = ctypes.c_uint32
    api.CAN_Write.argtypes = [ctypes.c_uint16, ctypes.POINTER(TPCANMsg)]
    api.CAN_Write.restype = ctypes.c_uint32
    api.CAN_Read.argtypes = [ctypes.c_uint16, ctypes.POINTER(TPCANMsg),
                             ctypes.POINTER(TPCANTimestamp)]
    api.CAN_Read.restype = ctypes.c_uint32
    return api


def u16le(value: int) -> bytes:
    return int(value).to_bytes(2, "little", signed=False)


def adc5(volts: float) -> int:
    return max(0, min(0xFFFF, round(volts / 0.0001875)))


def pack_ipc1(pressure_mpa: float, torque_nm: int) -> bytes:
    pressure = max(0, min(800, round(pressure_mpa / 0.01)))
    packed = (pressure | (pressure << 10) | (pressure << 20) |
              (pressure << 30) | ((torque_nm + 5000) << 48))
    return packed.to_bytes(8, "little")


def pack_ipc2(angle_deg: int, velocity: int, heartbeat: int,
              task_finish: bool) -> bytes:
    raw_angle = max(0, min(0xFFFF, angle_deg + 1024))
    byte3 = ((heartbeat & 0x0F) << 2) | (0x40 if task_finish else 0)
    return bytes((raw_angle >> 8, raw_angle & 0xFF, velocity, byte3, 0, 0, 0, 0))


def pack_esp_pressure(pressure_mpa: float, life: int) -> bytes:
    raw = max(0, min(0x0FFF, round(pressure_mpa / 0.01)))
    high = raw >> 4
    low = raw & 0x0F
    return bytes((high, (low << 4) | (raw >> 8), raw & 0xFF,
                  high, (low << 4) | (raw >> 8), raw & 0xFF,
                  life & 0x0F, 0))


def pack_eps_feedback(actual_angle_deg: int, counter: int) -> tuple[bytes, bytes]:
    raw = max(0, min(0xFFFF, actual_angle_deg + 1024))
    msg1 = bytes((32, 0, 0, raw >> 8, raw & 0xFF, 0, 0, 0))
    msg2 = bytes((32, 0, counter & 0xFF, raw >> 8, raw & 0xFF, 0, 0,
                  counter & 0xFF))
    return msg1, msg2


class Stimulus:
    def __init__(self) -> None:
        self.hin = 0x0079       # EBS check, cockpit/side DI8, RUN and TSMS high.
        self.brake_adc = adc5(0.50)
        self.air1_adc = 4000    # 0.00241699 V/count: approximately 9.67 V.
        self.air2_adc = 2000    # Approximately 4.83 V; EBS is not active.
        self.esp_pressure = 1.00
        self.ipc_pressure = 1.00
        self.motor_torque = 20
        self.ipc_finish = False
        self.eps_angle = 10
        self.ami_task = 1
        self.res_go = False
        self.res_stop = False
        self.freeze_res_heartbeat = False
        self.heartbeat = 0
        self.counter = 0
        self.life = 0

    def res(self) -> bytes:
        byte0 = 0x04 | (0x10 if self.res_go else 0) | (1 if self.res_stop else 0)
        return bytes((byte0, self.heartbeat, byte0 ^ self.heartbeat, 0, 0, 0, 0, 0))

    def debug_control(self) -> bytes:
        return bytes((0xA5, 0x5A, 0x0F, self.counter, 0, 0, 0, 0))

    def debug_pedal(self) -> bytes:
        app = adc5(0.252)
        return u16le(app) + u16le(app) + u16le(self.brake_adc) + bytes((self.counter, 0))

    def debug_air(self) -> bytes:
        return (u16le(self.air1_adc) + u16le(self.air2_adc) +
                u16le(0) + u16le(0))

    def debug_digital(self) -> bytes:
        return u16le(self.hin) + bytes((self.counter, 0, 0, 0, 0, 0))


class TestRig:
    def __init__(self, api: ctypes.WinDLL) -> None:
        self.api = api
        self.stim = Stimulus()
        self.latest: dict[int, bytes] = {}
        self.counts: dict[int, int] = {}
        self.failures: list[str] = []
        self.trace: list[str] = []
        self.start = time.monotonic()
        self.last_state: int | None = None
        self.next_20 = self.start
        self.next_50 = self.start
        self.next_100 = self.start

    def send(self, arbitration_id: int, payload: bytes) -> None:
        message = TPCANMsg()
        message.ID = arbitration_id
        message.MSGTYPE = PCAN_MESSAGE_STANDARD
        message.LEN = len(payload)
        for index, value in enumerate(payload):
            message.DATA[index] = value
        status = self.api.CAN_Write(PCAN_USBBUS1, ctypes.byref(message))
        if status != PCAN_ERROR_OK:
            raise RuntimeError(f"CAN_Write 0x{arbitration_id:X}: 0x{status:08X}")

    def receive_all(self) -> None:
        while True:
            message = TPCANMsg()
            timestamp = TPCANTimestamp()
            status = self.api.CAN_Read(PCAN_USBBUS1, ctypes.byref(message),
                                       ctypes.byref(timestamp))
            if status == PCAN_ERROR_QRCVEMPTY:
                break
            if status != PCAN_ERROR_OK:
                raise RuntimeError(f"CAN_Read: 0x{status:08X}")
            payload = bytes(message.DATA[:message.LEN])
            self.latest[message.ID] = payload
            self.counts[message.ID] = self.counts.get(message.ID, 0) + 1

        state = self.state()
        if state is not None and state != self.last_state:
            entry = f"t={time.monotonic() - self.start:6.2f}s {STATE.get(state, state)}"
            self.trace.append(entry)
            print("STATE " + entry, flush=True)
            self.last_state = state

    def transmit_due(self) -> None:
        now = time.monotonic()
        while now >= self.next_20:
            eps1, eps2 = pack_eps_feedback(self.stim.eps_angle, self.stim.counter)
            self.send(ID_ESP3, pack_esp_pressure(self.stim.esp_pressure, self.stim.life))
            self.send(ID_ESP6, bytes((0, 0, 0, 0, 0, 0, self.stim.life, 0)))
            self.send(ID_ESP7, bytes((0, 0, 0, 0, 0, 0, self.stim.life, 0)))
            self.send(ID_IPC1, pack_ipc1(self.stim.ipc_pressure, self.stim.motor_torque))
            self.send(ID_IPC2, pack_ipc2(0, 20, self.stim.counter,
                                        self.stim.ipc_finish))
            self.send(ID_AMI_TX, bytes(((self.stim.ami_task & 0x0F) << 4, 0, 0, 0, 0, 0, 0, 0)))
            self.send(ID_EPS1, eps1)
            self.send(ID_EPS2, eps2)
            self.stim.life = (self.stim.life + 1) & 0x0F
            self.next_20 += 0.020
        while now >= self.next_50:
            self.send(ID_RES, self.stim.res())
            if not self.stim.freeze_res_heartbeat:
                self.stim.heartbeat = (self.stim.heartbeat + 1) & 0xFF
            self.next_50 += 0.050
        while now >= self.next_100:
            self.send(ID_DBG_CONTROL, self.stim.debug_control())
            self.send(ID_DBG_PEDAL, self.stim.debug_pedal())
            self.send(ID_DBG_AIR, self.stim.debug_air())
            self.send(ID_DBG_DIGITAL, self.stim.debug_digital())
            self.stim.counter = (self.stim.counter + 1) & 0xFF
            self.next_100 += 0.100

    def run(self, duration: float) -> None:
        end = time.monotonic() + duration
        while time.monotonic() < end:
            self.transmit_due()
            self.receive_all()
            time.sleep(0.001)

    def wait_state(self, expected: int, timeout: float, label: str) -> bool:
        end = time.monotonic() + timeout
        while time.monotonic() < end:
            self.run(0.02)
            if self.state() == expected:
                print(f"PASS {label}: {STATE[expected]}", flush=True)
                return True
        self.failures.append(f"{label}: expected {STATE[expected]}, got {self.state_name()}")
        print("FAIL " + self.failures[-1], flush=True)
        return False

    def state(self) -> int | None:
        frame = self.latest.get(ID_AMI_RX, b"")
        return ((frame[0] >> 1) & 0x7F) if len(frame) == 8 else None

    def state_name(self) -> str:
        state = self.state()
        return STATE.get(state, str(state))

    def lox(self) -> int:
        frame = self.latest.get(ID_DBG_STATUS, b"")
        return frame[4] if len(frame) == 8 else 0

    def assert_true(self, condition: bool, label: str, detail: str = "") -> None:
        if condition:
            print("PASS " + label + (f": {detail}" if detail else ""), flush=True)
        else:
            failure = label + (f": {detail}" if detail else "")
            self.failures.append(failure)
            print("FAIL " + failure, flush=True)

    def output_snapshot(self) -> tuple[int, int, int, int]:
        eps = self.latest.get(ID_EPS_CMD, b"")
        esp = self.latest.get(ID_ESP_CMD, b"")
        motor = self.latest.get(ID_MOTOR_CMD, b"")
        eps_mode = eps[0] if len(eps) == 8 else -1
        esp_mode = (esp[6] >> 6) & 0x03 if len(esp) == 8 else -1
        motor_enable = motor[0] & 1 if len(motor) == 8 else -1
        motor_torque = int.from_bytes(motor[4:6], "little") - 5000 if len(motor) == 8 else -999
        return eps_mode, esp_mode, motor_enable, motor_torque


def main() -> int:
    api = load_api()
    status = api.CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K, 0, 0, 0)
    if status != PCAN_ERROR_OK:
        print(f"FAIL PCAN initialize: 0x{status:08X}")
        return 3

    rig = TestRig(api)
    try:
        rig.receive_all()
        print("PHASE baseline and monitor recovery", flush=True)
        rig.run(1.2)
        rig.assert_true(rig.state() == 1, "power-up state", rig.state_name())
        status_frame = rig.latest.get(ID_DBG_STATUS, b"")
        active = status_frame[0] & 0x0F if len(status_frame) == 8 else -1
        rig.assert_true(active == 0x0F, "four debug override groups active",
                        f"active=0x{active:02X}")
        if (rig.state() is None or active != 0x0F or
                rig.counts.get(ID_AMI_RX, 0) < 5 or
                rig.counts.get(ID_DBG_STATUS, 0) < 5):
            print("RESULT PRECONDITION FAIL: no continuous VCU status frames; "
                  "the application is not running", flush=True)
            return 3

        print("PHASE autonomous ignition/run edge and self-check", flush=True)
        rig.stim.hin = 0x00F9             # ASMS high.
        rig.run(0.20)
        rig.stim.hin = 0x00C9             # Side DI8 and RUN active-low edge.
        rig.run(0.20)
        rig.stim.hin = 0x00F9
        rig.wait_state(4, 2.0, "Off -> Ready after ASB self-check")

        print("PHASE Ready minimum dwell and RES Go", flush=True)
        rig.stim.res_go = True
        rig.run(2.0)
        rig.assert_true(rig.state() == 4, "early RES Go is blocked for 5 s",
                        rig.state_name())
        rig.wait_state(8, 4.0, "Ready -> R2D after 5 s")
        rig.run(0.20)
        eps, esp, enable, torque = rig.output_snapshot()
        rig.assert_true(eps == 32 and esp == 1 and torque == 0,
                        "R2D actuator gating",
                        f"EPS={eps}, ESP={esp}, motor={torque} Nm")

        print("PHASE steering centered and autonomous driving", flush=True)
        rig.stim.eps_angle = 0
        rig.wait_state(16, 1.0, "R2D -> Driving on steering zero")
        rig.run(0.20)
        eps, esp, enable, torque = rig.output_snapshot()
        rig.assert_true(eps == 32 and esp == 1 and enable == 1 and torque == 20,
                        "Driving controls all subsystems",
                        f"EPS={eps}, ESP={esp}, enable={enable}, motor={torque} Nm")

        print("PHASE IPC task completion at zero vehicle speed", flush=True)
        rig.stim.ipc_finish = True
        rig.wait_state(32, 1.0, "Driving -> Finished")
        rig.run(0.20)
        eps, esp, enable, torque = rig.output_snapshot()
        rig.assert_true(eps == 0 and esp == 0 and torque == 0,
                        "Finished commands safe outputs",
                        f"EPS={eps}, ESP={esp}, motor={torque} Nm")

        rig.stim.ipc_finish = False
        rig.stim.esp_pressure = 0.0
        rig.stim.hin = 0x0079             # ASMS low.
        rig.wait_state(1, 1.0, "Finished -> Off after brake release and ASMS off")

        # Restore normal wheel-brake feedback before evaluating the shared EBS
        # error lamp.  LOX bit3 also rises for low ESP feedback pressure, so
        # leaving the release value here would mask individual fault recovery.
        rig.stim.esp_pressure = 1.0
        rig.run(0.30)

        print("PHASE brake sensor open-circuit debounce and recovery", flush=True)
        rig.stim.brake_adc = 0
        rig.run(0.35)
        rig.assert_true(bool(rig.lox() & 0x08), "brake open detected after 100 ms",
                        f"LOX=0x{rig.lox():02X}")
        rig.stim.brake_adc = adc5(0.50)
        rig.run(1.00)
        rig.assert_true(not bool(rig.lox() & 0x08), "brake sensor fault recovers",
                        f"LOX=0x{rig.lox():02X}")

        print("PHASE air sensor low-range fault debounce and recovery", flush=True)
        # air1~=1.93 V is below the 2.5 V threshold.  air2~=1.21 V is changed at
        # the same time so the independent air2>air1+1.5 V relation latch is not
        # triggered and this remains a single sensor-range test.
        rig.stim.air1_adc = 800
        rig.stim.air2_adc = 500
        rig.run(0.70)
        rig.assert_true(bool(rig.lox() & 0x08), "air sensor low-range fault detected after 500 ms",
                        f"LOX=0x{rig.lox():02X}")
        rig.stim.air1_adc = 4000
        rig.stim.air2_adc = 2000
        rig.run(1.00)
        rig.assert_true(not bool(rig.lox() & 0x08), "air sensor low-range fault recovers",
                        f"LOX=0x{rig.lox():02X}")

        print("PHASE RES heartbeat timeout and recovery", flush=True)
        rig.stim.freeze_res_heartbeat = True
        rig.run(0.80)
        rig.assert_true(bool(rig.lox() & 0x08), "RES heartbeat timeout detected",
                        f"LOX=0x{rig.lox():02X}")
        rig.stim.freeze_res_heartbeat = False
        rig.run(1.20)
        rig.assert_true(not bool(rig.lox() & 0x08), "RES communication recovers",
                        f"LOX=0x{rig.lox():02X}")

        print("PHASE emergency stop and safety latch", flush=True)
        rig.stim.res_go = False
        rig.stim.hin = 0x00F9
        rig.wait_state(4, 3.0, "second Off -> Ready")
        rig.stim.res_stop = True
        rig.wait_state(64, 1.0, "validated RES Stop -> Emergency")
        rig.run(0.20)
        eps, esp, enable, torque = rig.output_snapshot()
        rig.assert_true(eps == 0 and esp == 0 and enable == 0 and torque == 0,
                        "Emergency disables EPS/ESP/traction",
                        f"EPS={eps}, ESP={esp}, enable={enable}, motor={torque} Nm")

        rig.stim.res_stop = False
        rig.stim.esp_pressure = 0.0
        rig.stim.hin = 0x0079
        rig.wait_state(1, 1.5, "Emergency -> Off after safe release")
        rig.stim.esp_pressure = 1.0
        rig.stim.hin = 0x00F9
        rig.run(1.0)
        rig.assert_true(rig.state() == 1,
                        "post-emergency safety lock blocks automatic restart",
                        rig.state_name())

        bus = api.CAN_GetStatus(PCAN_USBBUS1)
        rig.assert_true(bus == PCAN_ERROR_OK, "PCAN bus remains error-free",
                        f"status=0x{bus:08X}")
        required = (ID_AMI_RX, ID_ESP_CMD, ID_EPS_CMD, ID_DBG_STATUS, ID_MOTOR_CMD)
        rig.assert_true(all(rig.counts.get(identifier, 0) > 10 for identifier in required),
                        "all VCU output families observed",
                        ", ".join(f"0x{x:X}={rig.counts.get(x, 0)}" for x in required))

        print("TRACE " + " -> ".join(rig.trace), flush=True)
        if rig.failures:
            print(f"RESULT FAIL ({len(rig.failures)} checks)", flush=True)
            for failure in rig.failures:
                print(" - " + failure, flush=True)
            return 2
        print("RESULT PASS: autonomous state machine and mapped controls", flush=True)
        return 0
    finally:
        try:
            rig.send(ID_DBG_CONTROL, bytes((0xA5, 0x5A, 0, 0, 0, 0, 0, 0)))
            time.sleep(0.05)
        finally:
            api.CAN_Uninitialize(PCAN_USBBUS1)


if __name__ == "__main__":
    raise SystemExit(main())
