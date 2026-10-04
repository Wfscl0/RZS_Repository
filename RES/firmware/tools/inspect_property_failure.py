"""Capture first property mismatch before shutdown; reset to normal code afterward."""
import time
from pathlib import Path
from pyocd.core.helpers import ConnectHelper
from pyocd.core.target import Target

with ConnectHelper.session_with_chosen_probe(
        unique_id='2C01131E5118303030303032', target_override='cortex_m',
        frequency=1000000, options={'connect_mode':'attach','auto_unlock':False}) as s:
    t = s.target
    expected = (Path(__file__).resolve().parents[1] /
                'artifacts/dupont_spi_20260922/vehicle/gcc/RES_Vehicle_G0B1.bin').read_bytes()
    if bytes(t.read_memory_block8(0x08000000, len(expected))) != expected:
        raise RuntimeError('This breakpoint experiment only supports the exact 20260922 vehicle image')
    bp = 0x080024b4  # 20260922 ELF, first mismatching GET_PROPERTY response.
    try:
        t.reset_and_halt()
        # Freeze only the watchdog while halted; restore the debug setting below.
        freeze = t.read32(0x40015808)
        t.write32(0x40015808, freeze | 0x1000)
        t.set_breakpoint(bp, Target.BreakpointType.HW)
        t.resume()
        deadline = time.monotonic() + 3
        while t.get_state() != Target.State.HALTED and time.monotonic() < deadline:
            time.sleep(0.01)
        if t.get_state() != Target.State.HALTED:
            raise RuntimeError('Mismatch breakpoint not reached')
        sp, setting = t.read_core_register('sp'), t.read_core_register('r4')
        print('PC', hex(t.read_core_register('pc')))
        print('setting', bytes(t.read_memory_block8(setting,8)).hex(' '))
        print('reply', bytes(t.read_memory_block8(sp+8,4)).hex(' '))
        print('GPIOA', [hex(x) for x in t.read_memory_block32(0x50000000, 10)])
        t.remove_breakpoint(bp)
        # Call the existing firmware command function using isolated scratch RAM.
        # Only the same radio configuration values as startup are written.
        t.write_memory_block8(0x20020000, [0x00, 0xbe])
        def command(data, reply_n=0):
            t.write_memory_block8(0x20020100, data)
            t.write_memory_block8(0x20020200, [0xaa]*16)
            t.write32(0x20021000, 5)
            for reg, value in [('sp',0x20021000),('r0',0x20020100),('r1',len(data)),
                               ('r2',0x20020200),('r3',reply_n),
                               ('lr',0x20020001),('pc',0x08001f58),('xpsr',0x01000000)]:
                t.write_core_register(reg,value)
            t.resume()
            end=time.monotonic()+0.5
            while t.get_state()!=Target.State.HALTED and time.monotonic()<end:
                time.sleep(0.005)
            if t.get_state()!=Target.State.HALTED:
                t.halt()
                raise RuntimeError('Command did not return')
            print('command',bytes(data).hex(' '),'ok',t.read_core_register('r0'),
                  'reply',bytes(t.read_memory_block8(0x20020200,reply_n)).hex(' '),flush=True)
        command([0x01],8)
        command([0x11,1,4,0,5,0x38,0,0x28])
        command([0x12,1,4,0],4)
        command([0x12,0x40,8,0],8)
    finally:
        t.remove_breakpoint(bp)
        if 'freeze' in locals():
            t.write32(0x40015808,freeze)
        t.reset()
