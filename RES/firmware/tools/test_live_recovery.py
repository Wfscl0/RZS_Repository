"""Bench STOP-state link test: baseline and remote reset/recovery.

Does not drive GO or clear faults. This is not a power-loss test.
The existing fault state cannot establish READY-to-safe shutdown timing.
"""
import json
import time
from pathlib import Path
from contextlib import ExitStack
from elftools.elf.elffile import ELFFile
from pyocd.core.helpers import ConnectHelper

root = Path(__file__).resolve().parents[1]
build = root / 'artifacts/spi_diagnostic_20260924'
addresses = {}
for role, name in [('remote','RES_Remote_G0B1'),('vehicle','RES_Vehicle_G0B1')]:
    with (build/role/'gcc'/f'{name}.elf').open('rb') as stream:
        sym = ELFFile(stream).get_section_by_name('.symtab')
        addresses[role] = [sym.get_symbol_by_name(n)[0]['st_value']
                          for n in ('res_si4463_diag','res_uart_diag')]

with ExitStack() as stack:
    boards = {}
    for probe in ['20090928','2C01131E5118303030303032']:
        session = ConnectHelper.session_with_chosen_probe(
            blocking=False, unique_id=probe, target_override='cortex_m', frequency=1000000,
            options={'connect_mode':'attach','auto_unlock':False})
        if session is None:
            raise RuntimeError(f'Probe missing: {probe}')
        stack.enter_context(session)
        for role, (_, app_addr) in addresses.items():
            ident = session.target.read_memory_block32(app_addr,3)
            if ident == [0x52455344, 1 if role=='remote' else 2, 0x20260924]:
                if role in boards:
                    raise RuntimeError('Duplicate role')
                boards[role] = session.target
    if set(boards) != {'remote','vehicle'}:
        raise RuntimeError('Firmware identity mismatch')
    log = stack.enter_context((build/'recovery_test.jsonl').open('a',encoding='utf-8'))
    def sample(phase):
        result = {}
        for role,t in boards.items():
            rf_addr,app_addr = addresses[role]
            rf = t.read_memory_block32(rf_addr,25)
            app = t.read_memory_block32(app_addr,27)
            if app[:3] != [0x52455344,1 if role=='remote' else 2,0x20260924]:
                raise RuntimeError('Diagnostic identity changed')
            row = dict(phase=phase, role=role, tick=app[3], ready=rf[0], error=rf[1],
                       tx=rf[4], rx=rf[5], crc=rf[6], spi=rf[3], acks=app[26],
                       unmatched=app[25], state=app[17], faults=hex(app[18]),
                       outputs=app[23], last_valid=app[16])
            result[role] = row
            line=json.dumps(row)
            print(line,flush=True)
            log.write(line+'\n');log.flush()
        return result
    start=sample('baseline_start')
    if start['remote']['state']!=2 or start['vehicle']['state']!=4 or start['vehicle']['outputs']!=0:
        raise RuntimeError('This bench sequence requires existing STOP/fault and inactive vehicle outputs')
    time.sleep(10)
    sample('baseline_end')
    boards['remote'].reset()
    time.sleep(5)
    sample('remote_restart_5s')
    # 暂停实验曾意外复位，故不再自动执行；不能当作纯断链计时证据。
    time.sleep(5)
    sample('remote_restart_10s')
    time.sleep(5)
    sample('remote_restart_15s')
