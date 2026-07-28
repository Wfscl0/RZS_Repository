"""Direct WinUSB probe for DreamSourceLab instruments (no GUI automation).

Enumerates the Windows USB device interface for VID 2A0E / PID 0034,
opens it through WinUSB, prints descriptors and endpoint information, and can
optionally keep the handle open until interrupted.
"""

from __future__ import annotations

import argparse
import ctypes
from ctypes import wintypes
import sys
import time


VID = 0x2A0E
PID = 0x0034

DIGCF_PRESENT = 0x00000002
DIGCF_DEVICEINTERFACE = 0x00000010
GENERIC_READ = 0x80000000
GENERIC_WRITE = 0x40000000
OPEN_EXISTING = 3
FILE_ATTRIBUTE_NORMAL = 0x00000080
FILE_FLAG_OVERLAPPED = 0x40000000
ERROR_NO_MORE_ITEMS = 259
INVALID_HANDLE_VALUE = ctypes.c_void_p(-1).value


class GUID(ctypes.Structure):
    _fields_ = [
        ("Data1", wintypes.DWORD),
        ("Data2", wintypes.WORD),
        ("Data3", wintypes.WORD),
        ("Data4", ctypes.c_ubyte * 8),
    ]


GUID_DEVINTERFACE_USB_DEVICE = GUID(
    0xA5DCBF10,
    0x6530,
    0x11D2,
    (ctypes.c_ubyte * 8)(0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED),
)


class SP_DEVICE_INTERFACE_DATA(ctypes.Structure):
    _fields_ = [
        ("cbSize", wintypes.DWORD),
        ("InterfaceClassGuid", GUID),
        ("Flags", wintypes.DWORD),
        ("Reserved", ctypes.c_size_t),
    ]


class USB_DEVICE_DESCRIPTOR(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("bLength", ctypes.c_ubyte),
        ("bDescriptorType", ctypes.c_ubyte),
        ("bcdUSB", wintypes.WORD),
        ("bDeviceClass", ctypes.c_ubyte),
        ("bDeviceSubClass", ctypes.c_ubyte),
        ("bDeviceProtocol", ctypes.c_ubyte),
        ("bMaxPacketSize0", ctypes.c_ubyte),
        ("idVendor", wintypes.WORD),
        ("idProduct", wintypes.WORD),
        ("bcdDevice", wintypes.WORD),
        ("iManufacturer", ctypes.c_ubyte),
        ("iProduct", ctypes.c_ubyte),
        ("iSerialNumber", ctypes.c_ubyte),
        ("bNumConfigurations", ctypes.c_ubyte),
    ]


class USB_INTERFACE_DESCRIPTOR(ctypes.Structure):
    _fields_ = [
        ("bLength", ctypes.c_ubyte),
        ("bDescriptorType", ctypes.c_ubyte),
        ("bInterfaceNumber", ctypes.c_ubyte),
        ("bAlternateSetting", ctypes.c_ubyte),
        ("bNumEndpoints", ctypes.c_ubyte),
        ("bInterfaceClass", ctypes.c_ubyte),
        ("bInterfaceSubClass", ctypes.c_ubyte),
        ("bInterfaceProtocol", ctypes.c_ubyte),
        ("iInterface", ctypes.c_ubyte),
    ]


class WINUSB_PIPE_INFORMATION(ctypes.Structure):
    _fields_ = [
        ("PipeType", ctypes.c_int),
        ("PipeId", ctypes.c_ubyte),
        ("MaximumPacketSize", wintypes.WORD),
        ("Interval", ctypes.c_ubyte),
    ]


class WINUSB_SETUP_PACKET(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("RequestType", ctypes.c_ubyte),
        ("Request", ctypes.c_ubyte),
        ("Value", wintypes.WORD),
        ("Index", wintypes.WORD),
        ("Length", wintypes.WORD),
    ]


setupapi = ctypes.WinDLL("setupapi", use_last_error=True)
kernel32 = ctypes.WinDLL("kernel32", use_last_error=True)
winusb = ctypes.WinDLL("winusb", use_last_error=True)

setupapi.SetupDiGetClassDevsW.argtypes = [
    ctypes.POINTER(GUID),
    wintypes.LPCWSTR,
    wintypes.HWND,
    wintypes.DWORD,
]
setupapi.SetupDiGetClassDevsW.restype = wintypes.HANDLE
setupapi.SetupDiEnumDeviceInterfaces.argtypes = [
    wintypes.HANDLE,
    ctypes.c_void_p,
    ctypes.POINTER(GUID),
    wintypes.DWORD,
    ctypes.POINTER(SP_DEVICE_INTERFACE_DATA),
]
setupapi.SetupDiEnumDeviceInterfaces.restype = wintypes.BOOL
setupapi.SetupDiGetDeviceInterfaceDetailW.argtypes = [
    wintypes.HANDLE,
    ctypes.POINTER(SP_DEVICE_INTERFACE_DATA),
    ctypes.c_void_p,
    wintypes.DWORD,
    ctypes.POINTER(wintypes.DWORD),
    ctypes.c_void_p,
]
setupapi.SetupDiGetDeviceInterfaceDetailW.restype = wintypes.BOOL
setupapi.SetupDiDestroyDeviceInfoList.argtypes = [wintypes.HANDLE]
setupapi.SetupDiDestroyDeviceInfoList.restype = wintypes.BOOL

kernel32.CreateFileW.argtypes = [
    wintypes.LPCWSTR,
    wintypes.DWORD,
    wintypes.DWORD,
    ctypes.c_void_p,
    wintypes.DWORD,
    wintypes.DWORD,
    wintypes.HANDLE,
]
kernel32.CreateFileW.restype = wintypes.HANDLE
kernel32.CloseHandle.argtypes = [wintypes.HANDLE]
kernel32.CloseHandle.restype = wintypes.BOOL

winusb.WinUsb_Initialize.argtypes = [wintypes.HANDLE, ctypes.POINTER(ctypes.c_void_p)]
winusb.WinUsb_Initialize.restype = wintypes.BOOL
winusb.WinUsb_Free.argtypes = [ctypes.c_void_p]
winusb.WinUsb_Free.restype = wintypes.BOOL
winusb.WinUsb_GetDescriptor.argtypes = [
    ctypes.c_void_p,
    ctypes.c_ubyte,
    ctypes.c_ubyte,
    wintypes.WORD,
    ctypes.c_void_p,
    wintypes.ULONG,
    ctypes.POINTER(wintypes.ULONG),
]
winusb.WinUsb_GetDescriptor.restype = wintypes.BOOL
winusb.WinUsb_QueryInterfaceSettings.argtypes = [
    ctypes.c_void_p,
    ctypes.c_ubyte,
    ctypes.POINTER(USB_INTERFACE_DESCRIPTOR),
]
winusb.WinUsb_QueryInterfaceSettings.restype = wintypes.BOOL
winusb.WinUsb_QueryPipe.argtypes = [
    ctypes.c_void_p,
    ctypes.c_ubyte,
    ctypes.c_ubyte,
    ctypes.POINTER(WINUSB_PIPE_INFORMATION),
]
winusb.WinUsb_QueryPipe.restype = wintypes.BOOL
winusb.WinUsb_ControlTransfer.argtypes = [
    ctypes.c_void_p,
    WINUSB_SETUP_PACKET,
    ctypes.c_void_p,
    wintypes.ULONG,
    ctypes.POINTER(wintypes.ULONG),
    ctypes.c_void_p,
]
winusb.WinUsb_ControlTransfer.restype = wintypes.BOOL


def winerror(prefix: str) -> OSError:
    code = ctypes.get_last_error()
    return OSError(code, f"{prefix}: {ctypes.FormatError(code).strip()}")


def enumerate_usb_paths() -> list[str]:
    info_set = setupapi.SetupDiGetClassDevsW(
        ctypes.byref(GUID_DEVINTERFACE_USB_DEVICE),
        None,
        None,
        DIGCF_PRESENT | DIGCF_DEVICEINTERFACE,
    )
    if info_set == INVALID_HANDLE_VALUE:
        raise winerror("SetupDiGetClassDevsW failed")

    paths: list[str] = []
    try:
        index = 0
        while True:
            interface = SP_DEVICE_INTERFACE_DATA()
            interface.cbSize = ctypes.sizeof(interface)
            if not setupapi.SetupDiEnumDeviceInterfaces(
                info_set,
                None,
                ctypes.byref(GUID_DEVINTERFACE_USB_DEVICE),
                index,
                ctypes.byref(interface),
            ):
                code = ctypes.get_last_error()
                if code == ERROR_NO_MORE_ITEMS:
                    break
                raise winerror("SetupDiEnumDeviceInterfaces failed")

            required = wintypes.DWORD()
            setupapi.SetupDiGetDeviceInterfaceDetailW(
                info_set,
                ctypes.byref(interface),
                None,
                0,
                ctypes.byref(required),
                None,
            )
            buffer = ctypes.create_string_buffer(required.value)
            ctypes.cast(buffer, ctypes.POINTER(wintypes.DWORD))[0] = (
                8 if ctypes.sizeof(ctypes.c_void_p) == 8 else 6
            )
            if not setupapi.SetupDiGetDeviceInterfaceDetailW(
                info_set,
                ctypes.byref(interface),
                buffer,
                required.value,
                None,
                None,
            ):
                raise winerror("SetupDiGetDeviceInterfaceDetailW failed")
            paths.append(ctypes.wstring_at(ctypes.addressof(buffer) + 4))
            index += 1
    finally:
        setupapi.SetupDiDestroyDeviceInfoList(info_set)
    return paths


def get_descriptor(handle: ctypes.c_void_p, descriptor_type: int, index: int, lang: int, size: int) -> bytes:
    buffer = (ctypes.c_ubyte * size)()
    transferred = wintypes.ULONG()
    if not winusb.WinUsb_GetDescriptor(
        handle,
        descriptor_type,
        index,
        lang,
        buffer,
        size,
        ctypes.byref(transferred),
    ):
        raise winerror(f"WinUsb_GetDescriptor(type={descriptor_type}, index={index}) failed")
    return bytes(buffer[: transferred.value])


def get_string(handle: ctypes.c_void_p, index: int, lang: int) -> str:
    if index == 0:
        return ""
    raw = get_descriptor(handle, 3, index, lang, 255)
    return raw[2 : raw[0]].decode("utf-16-le", errors="replace") if len(raw) >= 2 else ""


def control_transfer(handle: ctypes.c_void_p, request_type: int, request: int, data: bytes | bytearray) -> bytes:
    buffer = (ctypes.c_ubyte * len(data)).from_buffer_copy(data)
    transferred = wintypes.ULONG()
    setup = WINUSB_SETUP_PACKET(request_type, request, 0, 0, len(data))
    if not winusb.WinUsb_ControlTransfer(
        handle, setup, buffer, len(data), ctypes.byref(transferred), None
    ):
        raise winerror(f"WinUsb_ControlTransfer(request=0x{request:02X}) failed")
    return bytes(buffer[: transferred.value])


def dsl_ctl_read(handle: ctypes.c_void_p, destination: int, offset: int, size: int) -> bytes:
    # ctl_header is packed as uint8 destination, uint16 offset, uint8 size.
    header = bytes((destination, offset & 0xFF, (offset >> 8) & 0xFF, size))
    control_transfer(handle, 0x40, 0xB1, header)
    time.sleep(0.010)
    return control_transfer(handle, 0xC0, 0xB2, bytes(size))


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--hold", action="store_true", help="keep the WinUSB handle open")
    args = parser.parse_args()

    marker = f"vid_{VID:04x}&pid_{PID:04x}"
    matches = [path for path in enumerate_usb_paths() if marker in path.lower()]
    if not matches:
        print(f"NOT_FOUND: USB {VID:04X}:{PID:04X}", flush=True)
        return 2
    if len(matches) != 1:
        print(f"AMBIGUOUS: found {len(matches)} matching interfaces", flush=True)
        for path in matches:
            print(path, flush=True)
        return 3

    path = matches[0]
    file_handle = kernel32.CreateFileW(
        path,
        GENERIC_READ | GENERIC_WRITE,
        0,
        None,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        None,
    )
    if file_handle == INVALID_HANDLE_VALUE:
        raise winerror("CreateFileW failed (another program may own the device)")

    usb_handle = ctypes.c_void_p()
    try:
        if not winusb.WinUsb_Initialize(file_handle, ctypes.byref(usb_handle)):
            raise winerror("WinUsb_Initialize failed")

        raw = get_descriptor(usb_handle, 1, 0, 0, ctypes.sizeof(USB_DEVICE_DESCRIPTOR))
        desc = USB_DEVICE_DESCRIPTOR.from_buffer_copy(raw)
        langs = get_descriptor(usb_handle, 3, 0, 0, 255)
        lang = int.from_bytes(langs[2:4], "little") if len(langs) >= 4 else 0x0409

        interface = USB_INTERFACE_DESCRIPTOR()
        if not winusb.WinUsb_QueryInterfaceSettings(usb_handle, 0, ctypes.byref(interface)):
            raise winerror("WinUsb_QueryInterfaceSettings failed")

        print(f"CONNECTED: USB {desc.idVendor:04X}:{desc.idProduct:04X}", flush=True)
        print(f"PATH: {path}", flush=True)
        print(f"USB: {desc.bcdUSB >> 8}.{desc.bcdUSB & 0xFF:02X}", flush=True)
        print(f"MANUFACTURER: {get_string(usb_handle, desc.iManufacturer, lang)}", flush=True)
        print(f"PRODUCT: {get_string(usb_handle, desc.iProduct, lang)}", flush=True)
        print(f"SERIAL: {get_string(usb_handle, desc.iSerialNumber, lang) or '(none)'}", flush=True)
        print(
            f"INTERFACE: {interface.bInterfaceNumber}, endpoints={interface.bNumEndpoints}, "
            f"class=0x{interface.bInterfaceClass:02X}",
            flush=True,
        )
        pipe_types = {0: "control", 1: "isochronous", 2: "bulk", 3: "interrupt"}
        for index in range(interface.bNumEndpoints):
            pipe = WINUSB_PIPE_INFORMATION()
            if not winusb.WinUsb_QueryPipe(usb_handle, 0, index, ctypes.byref(pipe)):
                raise winerror(f"WinUsb_QueryPipe({index}) failed")
            direction = "IN" if pipe.PipeId & 0x80 else "OUT"
            print(
                f"ENDPOINT {index}: 0x{pipe.PipeId:02X} {direction} "
                f"{pipe_types.get(pipe.PipeType, str(pipe.PipeType))} max_packet={pipe.MaximumPacketSize}",
                flush=True,
            )

        hardware_status = dsl_ctl_read(usb_handle, 2, 0, 1)[0]
        print(
            f"HW_STATUS: 0x{hardware_status:02X} "
            f"FPGA_DONE={int(bool(hardware_status & 0x40))} "
            f"GPIF_DONE={int(bool(hardware_status & 0x80))}",
            flush=True,
        )

        if args.hold:
            print("READY: direct WinUSB session is open; press Ctrl+C to close", flush=True)
            try:
                while True:
                    time.sleep(1)
            except KeyboardInterrupt:
                pass
    finally:
        if usb_handle.value:
            winusb.WinUsb_Free(usb_handle)
        kernel32.CloseHandle(file_handle)
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except OSError as exc:
        print(f"ERROR: {exc}", file=sys.stderr, flush=True)
        raise SystemExit(1)
