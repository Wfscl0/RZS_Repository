"""Capture logic samples directly from a DSLogic Plus (2A0E:0034).

This follows the open-source DSView/libsigrok4DSL USB protocol and does not use
GUI automation. It configures a triggerless 16-channel buffer capture, reads
the cross-channel sample format, and reports periodic square waves.
"""

from __future__ import annotations

import argparse
import ctypes
from ctypes import wintypes
import json
import math
from pathlib import Path
import statistics
import struct
import time

import dsl_usb_probe as usb


PIPE_OUT = 0x02
PIPE_IN = 0x86
PIPE_TRANSFER_TIMEOUT = 0x03
CMD_CTL_WR = 0xB0
DSL_CTL_HW_STATUS = 2
DSL_CTL_INTRDY = 6
DSL_CTL_WORDWIDE = 7
DSL_CTL_START = 8
DSL_CTL_STOP = 9
DSL_CTL_BULK_WR = 10
BM_GPIF_DONE = 0x80
BM_SYS_CLR = 0x08
BM_WR_INTRDY = 0x80
BM_WR_WORDWIDE = 0x01
TRIG_CHECK_ID = 0x55555555
SAMPLES_ALIGN = 1023
CHANNELS = 16
ATOMIC_SAMPLES = 64


class DSLSetting(ctypes.Structure):
    _fields_ = [
        ("sync", ctypes.c_uint32),
        ("mode_header", ctypes.c_uint16),
        ("mode", ctypes.c_uint16),
        ("divider_header", ctypes.c_uint16),
        ("div_l", ctypes.c_uint16),
        ("div_h", ctypes.c_uint16),
        ("count_header", ctypes.c_uint16),
        ("cnt_l", ctypes.c_uint16),
        ("cnt_h", ctypes.c_uint16),
        ("trig_pos_header", ctypes.c_uint16),
        ("tpos_l", ctypes.c_uint16),
        ("tpos_h", ctypes.c_uint16),
        ("trig_glb_header", ctypes.c_uint16),
        ("trig_glb", ctypes.c_uint16),
        ("dso_count_header", ctypes.c_uint16),
        ("dso_cnt_l", ctypes.c_uint16),
        ("dso_cnt_h", ctypes.c_uint16),
        ("ch_en_header", ctypes.c_uint16),
        ("ch_en_l", ctypes.c_uint16),
        ("ch_en_h", ctypes.c_uint16),
        ("fgain_header", ctypes.c_uint16),
        ("fgain", ctypes.c_uint16),
        ("trig_header", ctypes.c_uint16),
        ("trig_mask0", ctypes.c_uint16 * 16),
        ("trig_mask1", ctypes.c_uint16 * 16),
        ("trig_value0", ctypes.c_uint16 * 16),
        ("trig_value1", ctypes.c_uint16 * 16),
        ("trig_edge0", ctypes.c_uint16 * 16),
        ("trig_edge1", ctypes.c_uint16 * 16),
        ("trig_logic0", ctypes.c_uint16 * 16),
        ("trig_logic1", ctypes.c_uint16 * 16),
        ("trig_count", ctypes.c_uint32 * 16),
        ("end_sync", ctypes.c_uint32),
    ]


usb.winusb.WinUsb_SetPipePolicy.argtypes = [
    ctypes.c_void_p,
    ctypes.c_ubyte,
    wintypes.ULONG,
    wintypes.ULONG,
    ctypes.c_void_p,
]
usb.winusb.WinUsb_SetPipePolicy.restype = wintypes.BOOL
usb.winusb.WinUsb_WritePipe.argtypes = [
    ctypes.c_void_p,
    ctypes.c_ubyte,
    ctypes.c_void_p,
    wintypes.ULONG,
    ctypes.POINTER(wintypes.ULONG),
    ctypes.c_void_p,
]
usb.winusb.WinUsb_WritePipe.restype = wintypes.BOOL
usb.winusb.WinUsb_ReadPipe.argtypes = [
    ctypes.c_void_p,
    ctypes.c_ubyte,
    ctypes.c_void_p,
    wintypes.ULONG,
    ctypes.POINTER(wintypes.ULONG),
    ctypes.c_void_p,
]
usb.winusb.WinUsb_ReadPipe.restype = wintypes.BOOL


def ctl_write(handle: ctypes.c_void_p, destination: int, offset: int = 0, data: bytes = b"") -> None:
    header = struct.pack("<BHB", destination, offset, len(data))
    usb.control_transfer(handle, 0x40, CMD_CTL_WR, header + data)


def set_timeout(handle: ctypes.c_void_p, pipe_id: int, milliseconds: int) -> None:
    value = wintypes.ULONG(milliseconds)
    if not usb.winusb.WinUsb_SetPipePolicy(
        handle,
        pipe_id,
        PIPE_TRANSFER_TIMEOUT,
        ctypes.sizeof(value),
        ctypes.byref(value),
    ):
        raise usb.winerror(f"WinUsb_SetPipePolicy(0x{pipe_id:02X}) failed")


def write_pipe(handle: ctypes.c_void_p, data: bytes) -> None:
    buffer = (ctypes.c_ubyte * len(data)).from_buffer_copy(data)
    transferred = wintypes.ULONG()
    if not usb.winusb.WinUsb_WritePipe(
        handle, PIPE_OUT, buffer, len(data), ctypes.byref(transferred), None
    ):
        raise usb.winerror("WinUsb_WritePipe failed")
    if transferred.value != len(data):
        raise OSError(f"short USB write: {transferred.value}/{len(data)} bytes")


def read_pipe(handle: ctypes.c_void_p, size: int) -> bytes:
    buffer = (ctypes.c_ubyte * size)()
    transferred = wintypes.ULONG()
    if not usb.winusb.WinUsb_ReadPipe(
        handle, PIPE_IN, buffer, size, ctypes.byref(transferred), None
    ):
        raise usb.winerror("WinUsb_ReadPipe failed")
    return bytes(buffer[: transferred.value])


def open_device() -> tuple[int, ctypes.c_void_p]:
    marker = f"vid_{usb.VID:04x}&pid_{usb.PID:04x}"
    matches = [p for p in usb.enumerate_usb_paths() if marker in p.lower()]
    if len(matches) != 1:
        raise OSError(f"expected one USB {usb.VID:04X}:{usb.PID:04X}, found {len(matches)}")
    file_handle = usb.kernel32.CreateFileW(
        matches[0],
        usb.GENERIC_READ | usb.GENERIC_WRITE,
        0,
        None,
        usb.OPEN_EXISTING,
        usb.FILE_ATTRIBUTE_NORMAL | usb.FILE_FLAG_OVERLAPPED,
        None,
    )
    if file_handle == usb.INVALID_HANDLE_VALUE:
        raise usb.winerror("CreateFileW failed")
    winusb_handle = ctypes.c_void_p()
    if not usb.winusb.WinUsb_Initialize(file_handle, ctypes.byref(winusb_handle)):
        usb.kernel32.CloseHandle(file_handle)
        raise usb.winerror("WinUsb_Initialize failed")
    return file_handle, winusb_handle


def build_setting(sample_rate: int, sample_count: int) -> tuple[DSLSetting, int]:
    if not 50_000 <= sample_rate <= 100_000_000:
        raise ValueError("sample rate must be 50 kHz to 100 MHz in 16-channel buffer mode")
    actual_samples = (sample_count + SAMPLES_ALIGN) & ~SAMPLES_ALIGN
    divider = math.ceil(100_000_000 / sample_rate)
    effective_rate = 100_000_000 // divider

    setting = DSLSetting()
    setting.sync = 0xF5A5F5A5
    setting.mode_header = 0x0001
    setting.mode = 0  # triggerless, non-RLE, internal clock, buffer mode
    setting.divider_header = 0x0102
    setting.div_l = divider & 0xFFFF
    setting.div_h = (divider >> 16) & 0xFF
    setting.count_header = 0x0302
    capture_units = actual_samples >> 4
    setting.cnt_l = capture_units & 0xFFFF
    setting.cnt_h = (capture_units >> 16) & 0xFFFF
    setting.trig_pos_header = 0x0502
    setting.tpos_l = 64
    setting.tpos_h = 0
    setting.trig_glb_header = 0x0701
    setting.trig_glb = CHANNELS << 8
    setting.dso_count_header = 0x0802
    setting.dso_cnt_l = actual_samples & 0xFFFF
    setting.dso_cnt_h = (actual_samples >> 16) & 0xFFFF
    setting.ch_en_header = 0x0A02
    setting.ch_en_l = 0xFFFF
    setting.ch_en_h = 0
    setting.fgain_header = 0x0C01
    setting.fgain = 0
    setting.trig_header = 0x40A0
    for stage in range(16):
        setting.trig_mask0[stage] = 0xFFFF
        setting.trig_mask1[stage] = 0xFFFF
        setting.trig_logic0[stage] = 2
        setting.trig_logic1[stage] = 2
    setting.end_sync = 0xFA5AFA5A
    return setting, effective_rate


def wait_status(handle: ctypes.c_void_p, mask: int, timeout: float = 2.0) -> int:
    deadline = time.monotonic() + timeout
    status = 0
    while time.monotonic() < deadline:
        status = usb.dsl_ctl_read(handle, DSL_CTL_HW_STATUS, 0, 1)[0]
        if status & mask:
            return status
    raise TimeoutError(f"timed out waiting for hardware status mask 0x{mask:02X}; last=0x{status:02X}")


def capture(handle: ctypes.c_void_p, sample_rate: int, sample_count: int) -> tuple[bytes, int, dict]:
    setting, effective_rate = build_setting(sample_rate, sample_count)
    setting_bytes = ctypes.string_at(ctypes.byref(setting), ctypes.sizeof(setting))
    actual_samples = (sample_count + SAMPLES_ALIGN) & ~SAMPLES_ALIGN
    expected_bytes = actual_samples * CHANNELS // 8

    set_timeout(handle, PIPE_IN, 5000)
    set_timeout(handle, PIPE_OUT, 3000)
    ctl_write(handle, DSL_CTL_STOP)
    ctl_write(handle, DSL_CTL_WORDWIDE, data=bytes((BM_WR_WORDWIDE,)))
    ctl_write(
        handle,
        DSL_CTL_BULK_WR,
        data=bytes((len(setting_bytes) // 2 & 0xFF, (len(setting_bytes) // 2 >> 8) & 0xFF, 0)),
    )
    wait_status(handle, BM_SYS_CLR)
    write_pipe(handle, setting_bytes)
    ctl_write(handle, DSL_CTL_INTRDY, data=bytes((BM_WR_INTRDY,)))
    arm_status = wait_status(handle, BM_GPIF_DONE)

    ctl_write(handle, DSL_CTL_START)
    header = read_pipe(handle, 512)
    if len(header) != 512:
        raise OSError(f"short trigger header: {len(header)}/512 bytes")
    check_id, real_pos, ram_start, remain_low, remain_high, status = struct.unpack_from("<6I", header)
    if check_id != TRIG_CHECK_ID:
        raise OSError(f"invalid trigger header check ID 0x{check_id:08X}")

    chunks: list[bytes] = []
    received = 0
    while received < expected_bytes:
        block = read_pipe(handle, min(1_048_576, expected_bytes - received))
        if not block:
            raise OSError(f"empty USB read after {received}/{expected_bytes} bytes")
        chunks.append(block)
        received += len(block)

    ctl_write(handle, DSL_CTL_STOP)
    return b"".join(chunks), effective_rate, {
        "arm_status": arm_status,
        "real_pos": real_pos,
        "ram_start": ram_start,
        "remain_count": (remain_high << 32) | remain_low,
        "capture_status": status,
        "samples": actual_samples,
    }


def decode_channels(raw: bytes) -> list[list[int]]:
    group_size = CHANNELS * 8
    if len(raw) % group_size:
        raise ValueError(f"cross-channel data length {len(raw)} is not a multiple of {group_size}")
    channels = [[] for _ in range(CHANNELS)]
    for base in range(0, len(raw), group_size):
        for channel in range(CHANNELS):
            word = int.from_bytes(raw[base + channel * 8 : base + channel * 8 + 8], "little")
            channels[channel].extend((word >> bit) & 1 for bit in range(ATOMIC_SAMPLES))
    return channels


def analyze(values: list[int], sample_rate: int, channel: int) -> dict:
    transitions = [i for i in range(1, len(values)) if values[i] != values[i - 1]]
    rising = [i for i in transitions if values[i] == 1]
    falling = [i for i in transitions if values[i] == 0]
    result = {
        "channel": channel,
        "samples": len(values),
        "transitions": len(transitions),
        "high_percent": 100.0 * sum(values) / len(values),
        "rising_edges": len(rising),
        "falling_edges": len(falling),
    }
    if len(rising) >= 2:
        periods = [b - a for a, b in zip(rising, rising[1:])]
        mean_period = statistics.mean(periods)
        result["frequency_hz"] = sample_rate / mean_period
        result["period_us"] = 1_000_000.0 * mean_period / sample_rate
        result["period_jitter_percent"] = (
            100.0 * statistics.pstdev(periods) / mean_period if len(periods) > 1 else 0.0
        )
    return result


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--rate", type=int, default=1_000_000)
    parser.add_argument("--samples", type=int, default=200_000)
    parser.add_argument("--output", type=Path, default=Path("captures") / "latest")
    args = parser.parse_args()

    file_handle, handle = open_device()
    try:
        raw, effective_rate, metadata = capture(handle, args.rate, args.samples)
    finally:
        usb.winusb.WinUsb_Free(handle)
        usb.kernel32.CloseHandle(file_handle)

    channels = decode_channels(raw)
    summaries = [analyze(values, effective_rate, index) for index, values in enumerate(channels)]
    candidates = [item for item in summaries if item["transitions"] >= 4]
    candidates.sort(key=lambda item: (item.get("period_jitter_percent", 1e9), -item["transitions"]))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.with_suffix(".bin").write_bytes(raw)
    report = {
        "device": "DreamSourceLab DSLogic Plus 2A0E:0034",
        "sample_rate_hz": effective_rate,
        "metadata": metadata,
        "channels": summaries,
    }
    args.output.with_suffix(".json").write_text(json.dumps(report, indent=2), encoding="utf-8")

    print(f"CAPTURED: {metadata['samples']} samples/channel at {effective_rate} Hz")
    if not candidates:
        print("NO_SQUARE_WAVE: no channel had at least four transitions")
        return 4
    print("ACTIVE_CHANNELS:")
    for item in candidates:
        freq = item.get("frequency_hz")
        freq_text = f"{freq:.3f} Hz" if freq is not None else "insufficient rising edges"
        jitter = item.get("period_jitter_percent")
        jitter_text = f", jitter={jitter:.3f}%" if jitter is not None else ""
        print(
            f"  CH{item['channel']}: {freq_text}, high={item['high_percent']:.2f}%, "
            f"edges={item['transitions']}{jitter_text}"
        )
    print(f"RAW: {args.output.with_suffix('.bin').resolve()}")
    print(f"REPORT: {args.output.with_suffix('.json').resolve()}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
