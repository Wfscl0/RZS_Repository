"""Read link diagnostics without halting either MCU. Resolve addresses from ELF."""
import json
import time
import argparse
from contextlib import ExitStack
from pathlib import Path
from elftools.elf.elffile import ELFFile
from pyocd.core.helpers import ConnectHelper

ROOT = Path(__file__).resolve().parents[1]
args_parser = argparse.ArgumentParser()
args_parser.add_argument('--build', default='production_can_20260924')
args_parser.add_argument('--samples', type=int, default=3)
args_parser.add_argument('--role', choices=['remote','vehicle','both'], default='both')
args = args_parser.parse_args()
BOARDS = [('remote', '20090928', 'RES_Remote_G0B1'),
          ('vehicle', '2C01131E5118303030303032', 'RES_Vehicle_G0B1')]

def symbols(role, name):
    path = ROOT / 'artifacts' / args.build / role / 'gcc' / (name + '.elf')
    with path.open('rb') as stream:
        table = ELFFile(stream).get_section_by_name('.symtab')
        return [table.get_symbol_by_name(s)[0]['st_value']
                for s in ('res_si4463_diag', 'res_uart_diag')]

with ExitStack() as stack:
    boards = []
    for _, probe, _ in BOARDS:
        session = ConnectHelper.session_with_chosen_probe(
            blocking=False, unique_id=probe, target_override='cortex_m', frequency=1000000,
            options={'connect_mode': 'attach', 'auto_unlock': False})
        if session is None:
            raise RuntimeError(f'Probe missing: {probe}')
        stack.enter_context(session)
        # 调试器可能被对调；以板上诊断标识识别角色，禁止解释错位内存。
        matches = []
        for role, _, name in BOARDS:
            addresses = symbols(role, name)
            identity = session.target.read_memory_block32(addresses[1], 3)
            expected_role = 1 if role == 'remote' else 2
            if identity[0] == 0x52455344 and identity[1] == expected_role:
                matches.append((role, addresses))
        if len(matches) != 1:
            raise RuntimeError(f'{probe}: diagnostic identity does not match selected ELF build')
        role, addresses = matches[0]
        if args.role == 'both' or args.role == role:
            boards.append((role, probe, session.target, addresses))
    if len({b[0] for b in boards}) != len(boards) or not boards:
        raise RuntimeError('Missing or duplicate application roles')
    for sample in range(args.samples):
        for role, probe, target, (rf_addr, app_addr) in boards:
            rf = target.read_memory_block32(rf_addr, 25)
            app = target.read_memory_block32(app_addr, 27)
            if app[0] != 0x52455344 or app[1] != (1 if role == 'remote' else 2):
                raise RuntimeError(f'{probe}: diagnostic identity changed during sampling')
            # TX submission alone is not proof of delivery. Inspect RX and ACK.
            print(json.dumps(dict(sample=sample, role=role, probe=probe, revision=hex(app[2]),
                tick_ms=app[3], ready=rf[0], error=rf[1], tx_done=rf[4],
                rx_packets=rf[5], crc_errors=rf[6], spi_errors=rf[3],
                part=hex(rf[11]), property_failure=hex(rf[23]), accepted_acks=app[26],
                decoded_frames=app[24], unmatched_acks=app[25],
                state=app[17], faults=hex(app[18]), outputs=app[23],
                battery_mv=app[20], battery_valid=app[21], stop_input=app[22])), flush=True)
        if sample + 1 < args.samples:
            time.sleep(5)
