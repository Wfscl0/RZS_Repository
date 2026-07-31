#!/usr/bin/env python3
"""Run the autonomous VCU test suite through a ZLG USBCAN-II adapter.

This file is intentionally a thin transport adapter.  The complete stimulus,
state assertions and output checks remain in
``pcan_autonomous_state_machine_test.py`` so PCAN and ZLG runs are identical.

Run with the 32-bit Python bundled with TSMaster because ControlCAN.dll is a
32-bit library.
"""

from __future__ import annotations

import ctypes
import os
import pathlib
import sys


HERE = pathlib.Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import pcan_autonomous_state_machine_test as suite  # noqa: E402


VCI_USBCAN2 = 4
DEVICE_INDEX = 0
CAN_INDEX = 0


class VCI_INIT_CONFIG(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("AccCode", ctypes.c_uint32),
        ("AccMask", ctypes.c_uint32),
        ("Reserved", ctypes.c_uint32),
        ("Filter", ctypes.c_uint8),
        ("Timing0", ctypes.c_uint8),
        ("Timing1", ctypes.c_uint8),
        ("Mode", ctypes.c_uint8),
    ]


class VCI_CAN_OBJ(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("ID", ctypes.c_uint32),
        ("TimeStamp", ctypes.c_uint32),
        ("TimeFlag", ctypes.c_uint8),
        ("SendType", ctypes.c_uint8),
        ("RemoteFlag", ctypes.c_uint8),
        ("ExternFlag", ctypes.c_uint8),
        ("DataLen", ctypes.c_uint8),
        ("Data", ctypes.c_uint8 * 8),
        ("Reserved", ctypes.c_uint8 * 3),
    ]


class VCI_ERR_INFO(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("ErrCode", ctypes.c_uint32),
        ("Passive_ErrData", ctypes.c_uint8 * 3),
        ("ArLost_ErrData", ctypes.c_uint8),
    ]


class ZlgPcanCompatibility:
    """Expose the small PCAN-Basic surface used by the shared test rig."""

    def __init__(self) -> None:
        os.add_dll_directory(r"E:\TSMaster\bin")
        self.dll = ctypes.WinDLL(r"E:\TSMaster\bin\ControlCAN.dll")
        self.dll.VCI_OpenDevice.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                            ctypes.c_uint32]
        self.dll.VCI_OpenDevice.restype = ctypes.c_uint32
        self.dll.VCI_CloseDevice.argtypes = [ctypes.c_uint32, ctypes.c_uint32]
        self.dll.VCI_CloseDevice.restype = ctypes.c_uint32
        self.dll.VCI_InitCAN.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                        ctypes.c_uint32,
                                        ctypes.POINTER(VCI_INIT_CONFIG)]
        self.dll.VCI_InitCAN.restype = ctypes.c_uint32
        self.dll.VCI_StartCAN.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                         ctypes.c_uint32]
        self.dll.VCI_StartCAN.restype = ctypes.c_uint32
        self.dll.VCI_ClearBuffer.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                            ctypes.c_uint32]
        self.dll.VCI_ClearBuffer.restype = ctypes.c_uint32
        self.dll.VCI_Transmit.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                         ctypes.c_uint32,
                                         ctypes.POINTER(VCI_CAN_OBJ),
                                         ctypes.c_uint32]
        self.dll.VCI_Transmit.restype = ctypes.c_uint32
        self.dll.VCI_Receive.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                        ctypes.c_uint32,
                                        ctypes.POINTER(VCI_CAN_OBJ),
                                        ctypes.c_uint32, ctypes.c_int]
        self.dll.VCI_Receive.restype = ctypes.c_uint32
        self.dll.VCI_ReadErrInfo.argtypes = [ctypes.c_uint32, ctypes.c_uint32,
                                            ctypes.c_uint32,
                                            ctypes.POINTER(VCI_ERR_INFO)]
        self.dll.VCI_ReadErrInfo.restype = ctypes.c_uint32
        self.opened = False

    def CAN_Initialize(self, _channel: int, _bitrate: int, _hwtype: int,
                       _ioport: int, _interrupt: int) -> int:
        if self.dll.VCI_OpenDevice(VCI_USBCAN2, DEVICE_INDEX, 0) != 1:
            return 0x10000
        self.opened = True
        config = VCI_INIT_CONFIG(
            AccCode=0,
            AccMask=0xFFFFFFFF,
            Reserved=0,
            Filter=1,
            Timing0=0x00,
            Timing1=0x1C,  # 500 kbit/s for the classic ZLG timing table.
            Mode=0,
        )
        if self.dll.VCI_InitCAN(VCI_USBCAN2, DEVICE_INDEX, CAN_INDEX,
                                ctypes.byref(config)) != 1:
            self.CAN_Uninitialize(0)
            return 0x10001
        self.dll.VCI_ClearBuffer(VCI_USBCAN2, DEVICE_INDEX, CAN_INDEX)
        if self.dll.VCI_StartCAN(VCI_USBCAN2, DEVICE_INDEX, CAN_INDEX) != 1:
            self.CAN_Uninitialize(0)
            return 0x10002
        return suite.PCAN_ERROR_OK

    def CAN_Uninitialize(self, _channel: int) -> int:
        if self.opened:
            self.dll.VCI_CloseDevice(VCI_USBCAN2, DEVICE_INDEX)
            self.opened = False
        return suite.PCAN_ERROR_OK

    def CAN_GetStatus(self, _channel: int) -> int:
        if not self.opened:
            return 0x10000
        error = VCI_ERR_INFO()
        if self.dll.VCI_ReadErrInfo(VCI_USBCAN2, DEVICE_INDEX, CAN_INDEX,
                                    ctypes.byref(error)) != 1:
            return 0x10005
        return int(error.ErrCode)

    def CAN_Write(self, _channel: int, message_pointer) -> int:
        source = ctypes.cast(message_pointer,
                             ctypes.POINTER(suite.TPCANMsg)).contents
        message = VCI_CAN_OBJ()
        message.ID = source.ID
        message.SendType = 0
        message.RemoteFlag = 0
        message.ExternFlag = 1 if source.ID > 0x7FF else 0
        message.DataLen = source.LEN
        for index in range(source.LEN):
            message.Data[index] = source.DATA[index]
        count = self.dll.VCI_Transmit(VCI_USBCAN2, DEVICE_INDEX, CAN_INDEX,
                                      ctypes.byref(message), 1)
        return suite.PCAN_ERROR_OK if count == 1 else 0x10003

    def CAN_Read(self, _channel: int, message_pointer, timestamp_pointer) -> int:
        source = VCI_CAN_OBJ()
        count = self.dll.VCI_Receive(VCI_USBCAN2, DEVICE_INDEX, CAN_INDEX,
                                     ctypes.byref(source), 1, 0)
        if count == 0:
            return suite.PCAN_ERROR_QRCVEMPTY
        if count != 1:
            return 0x10004
        target = ctypes.cast(message_pointer,
                             ctypes.POINTER(suite.TPCANMsg)).contents
        target.ID = source.ID
        target.MSGTYPE = 0x02 if source.ExternFlag else 0x00
        target.LEN = source.DataLen
        for index in range(source.DataLen):
            target.DATA[index] = source.Data[index]
        if timestamp_pointer:
            timestamp = ctypes.cast(timestamp_pointer,
                                    ctypes.POINTER(suite.TPCANTimestamp)).contents
            timestamp.millis = source.TimeStamp
            timestamp.millis_overflow = 0
            timestamp.micros = 0
        return suite.PCAN_ERROR_OK


def main() -> int:
    adapter = ZlgPcanCompatibility()
    suite.load_api = lambda: adapter
    print("TRANSPORT ZLG USBCAN-II channel 0, 500 kbit/s", flush=True)
    return suite.main()


if __name__ == "__main__":
    raise SystemExit(main())
