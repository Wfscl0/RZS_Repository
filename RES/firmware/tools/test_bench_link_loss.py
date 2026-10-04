"""Isolated no-CAN bench only: shut down remote radio via SDN and measure release.

Leaves the remote radio off and the receiver fault-latched for physical inspection.
No CPU halt or watchdog manipulation. GPIO timing is not relay contact timing.
"""
import json
import time
from contextlib import ExitStack
from pathlib import Path
from elftools.elf.elffile import ELFFile
from pyocd.core.helpers import ConnectHelper

root=Path(__file__).resolve().parents[1]/'artifacts/bench_nocan_20260924'
def symbols(role,name):
    with (root/role/'gcc'/f'{name}.elf').open('rb') as f:
        tab=ELFFile(f).get_section_by_name('.symtab')
        return {n:tab.get_symbol_by_name(n)[0]['st_value'] for n in
                (['res_uart_diag','res_bench_no_can'] if role=='vehicle' else ['res_uart_diag'])}
with ExitStack() as stack:
    boards={}
    for role,probe,name in [('vehicle','20090928','RES_Vehicle_G0B1'),
                             ('remote','2C01131E5118303030303032','RES_Remote_G0B1')]:
        s=ConnectHelper.session_with_chosen_probe(unique_id=probe,blocking=False,
            target_override='cortex_m',frequency=1000000,
            options={'connect_mode':'attach','auto_unlock':False})
        if s is None:raise RuntimeError('Probe missing')
        stack.enter_context(s);boards[role]=(s.target,symbols(role,name))
    v,vs=boards['vehicle'];r,rs=boards['remote']
    def read(t,syms,role):
        app=t.read_memory_block32(syms['res_uart_diag'],24)
        if app[:3]!=[0x52455344,role,0x20260924]:raise RuntimeError('Identity mismatch')
        return app
    va=read(v,vs,2);ra=read(r,rs,1)
    if v.read32(vs['res_bench_no_can'])!=1 or va[17]!=2 or va[18]!=0 or va[23]!=3 or ra[17]!=1 or ra[18]!=0:
        raise RuntimeError('Requires isolated bench, READY, no faults, both relays commanded on')
    log=stack.enter_context((root/'link_loss.jsonl').open('a',encoding='utf-8'))
    def emit(phase,app):
        gpio=v.read32(0x50000414)
        row=dict(phase=phase,tick=app[3],last_valid=app[16],
                 age_ms=(app[3]-app[16])&0xffffffff,state=app[17],faults=hex(app[18]),
                 relays=app[23],relay_pin_levels=(gpio>>10)&3,start_pin=(gpio>>12)&1)
        line=json.dumps(row);print(line,flush=True);log.write(line+'\n');log.flush()
    emit('before',va)
    # Atomic PB3 SET: same SDN shutdown level used by the driver on radio faults.
    r.write32(0x50000418,1<<3);r.flush()
    end=time.monotonic()+2; previous=None
    while time.monotonic()<end:
        va=read(v,vs,2)
        key=(va[17],va[18],va[23])
        if key!=previous:emit('after_sdn',va);previous=key
        if va[23]==0:
            emit('released',va)
            break
        time.sleep(0.01)
    else:
        raise RuntimeError('No relay release observed within 2 seconds')
