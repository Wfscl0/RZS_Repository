#!/usr/bin/env python3
"""Dependency-free PCAN-Basic smoke test for the VCU CAN0 bench firmware."""

from __future__ import annotations

import ctypes
import pathlib
import time


PCAN_USBBUS1 = 0x51
PCAN_BAUD_500K = 0x001C
PCAN_MESSAGE_STANDARD = 0x00
PCAN_ERROR_OK = 0x00000
PCAN_ERROR_QRCVEMPTY = 0x00020


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
    if not dll.exists():
        raise FileNotFoundError(dll)
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


def send(api: ctypes.WinDLL, arbitration_id: int, payload: bytes) -> None:
    message = TPCANMsg()
    message.ID = arbitration_id
    message.MSGTYPE = PCAN_MESSAGE_STANDARD
    message.LEN = len(payload)
    for index, value in enumerate(payload):
        message.DATA[index] = value
    status = api.CAN_Write(PCAN_USBBUS1, ctypes.byref(message))
    if status != PCAN_ERROR_OK:
        raise RuntimeError(f"CAN_Write 0x{arbitration_id:03X} failed: 0x{status:08X}")


def receive_all(api: ctypes.WinDLL, latest: dict[int, bytes], counters: dict[int, int]) -> None:
    while True:
        message = TPCANMsg()
        timestamp = TPCANTimestamp()
        status = api.CAN_Read(PCAN_USBBUS1, ctypes.byref(message), ctypes.byref(timestamp))
        if status == PCAN_ERROR_QRCVEMPTY:
            return
        if status != PCAN_ERROR_OK:
            raise RuntimeError(f"CAN_Read failed: 0x{status:08X}")
        payload = bytes(message.DATA[:message.LEN])
        latest[message.ID] = payload
        counters[message.ID] = counters.get(message.ID, 0) + 1


CONTROL = bytes.fromhex("A5 5A 0F 00 00 00 00 00")
PEDAL = bytes.fromhex("40 05 40 05 6B 0A 00 00")
AIR = bytes.fromhex("77 06 3B 03 00 00 00 00")
DIGITAL = bytes.fromhex("79 00 00 00 00 00 00 00")


def run_phase(api: ctypes.WinDLL, duration: float, include_pedal: bool,
              latest: dict[int, bytes], counters: dict[int, int]) -> None:
    start = time.monotonic()
    next_send = start
    while time.monotonic() - start < duration:
        now = time.monotonic()
        if now >= next_send:
            send(api, 0x7A0, CONTROL)
            if include_pedal:
                send(api, 0x7A1, PEDAL)
            send(api, 0x7A2, AIR)
            send(api, 0x7A3, DIGITAL)
            next_send += 0.1
        receive_all(api, latest, counters)
        time.sleep(0.002)


def main() -> int:
    api = load_api()
    status = api.CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K, 0, 0, 0)
    if status != PCAN_ERROR_OK:
        print(f"FAIL: PCAN initialize returned 0x{status:08X}")
        return 3

    latest: dict[int, bytes] = {}
    counters: dict[int, int] = {}
    failures: list[str] = []
    try:
        receive_all(api, latest, counters)

        run_phase(api, 1.5, True, latest, counters)
        status_frame = latest.get(0x7B0, b"")
        pedal_echo = latest.get(0x7B1, b"")
        air_echo = latest.get(0x7B2, b"")
        active_before = status_frame[0] & 0x0F if len(status_frame) == 8 else -1
        if active_before != 0x0F:
            failures.append(f"initial Active=0x{active_before:02X}, expected 0x0F")
        if len(pedal_echo) != 8 or pedal_echo[:6] != PEDAL[:6] or not (pedal_echo[6] & 1):
            failures.append(f"pedal echo mismatch: {pedal_echo.hex(' ')}")
        if len(air_echo) != 8 or air_echo != AIR:
            failures.append(f"air echo mismatch: {air_echo.hex(' ')}")

        run_phase(api, 0.9, False, latest, counters)
        status_frame = latest.get(0x7B0, b"")
        active_timeout = status_frame[0] & 0x0F if len(status_frame) == 8 else -1
        if active_timeout != 0x0D:
            failures.append(f"pedal-timeout Active=0x{active_timeout:02X}, expected 0x0D")

        run_phase(api, 0.8, True, latest, counters)
        status_frame = latest.get(0x7B0, b"")
        active_recovered = status_frame[0] & 0x0F if len(status_frame) == 8 else -1
        if active_recovered != 0x0F:
            failures.append(f"recovered Active=0x{active_recovered:02X}, expected 0x0F")

        bus_status = api.CAN_GetStatus(PCAN_USBBUS1)
        print(f"PCAN_STATUS=0x{bus_status:08X}")
        print(f"RX_COUNTS 7B0={counters.get(0x7B0, 0)} "
              f"7B1={counters.get(0x7B1, 0)} 7B2={counters.get(0x7B2, 0)} "
              f"MOTOR={counters.get(0x0CFF08EF, 0)}")
        print(f"STATUS_INITIAL=0x{active_before:02X} "
              f"STATUS_TIMEOUT=0x{active_timeout:02X} "
              f"STATUS_RECOVERED=0x{active_recovered:02X}")
        print("LAST_7B0=" + latest.get(0x7B0, b"").hex(" "))
        print("LAST_7B1=" + latest.get(0x7B1, b"").hex(" "))
        print("LAST_7B2=" + latest.get(0x7B2, b"").hex(" "))

        if failures:
            for failure in failures:
                print("FAIL: " + failure)
            return 2
        print("PASS: CAN0 debug override, echo, pedal timeout and recovery")
        return 0
    finally:
        try:
            send(api, 0x7A0, bytes.fromhex("A5 5A 00 00 00 00 00 00"))
            time.sleep(0.05)
        finally:
            api.CAN_Uninitialize(PCAN_USBBUS1)


if __name__ == "__main__":
    raise SystemExit(main())
