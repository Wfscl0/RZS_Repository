"""Read GO pulse history and relay GPIOs; no target writes."""
import argparse
import json
import time
from pathlib import Path
from elftools.elf.elffile import ELFFile
from pyocd.core.helpers import ConnectHelper

p=argparse.ArgumentParser();p.add_argument('--seconds',type=float,default=45);a=p.parse_args()
root=Path(__file__).resolve().parents[1]/'artifacts/bench_nocan_20260924'
with (root/'vehicle/gcc/RES_Vehicle_G0B1.elf').open('rb') as f:
    syms=ELFFile(f).get_section_by_name('.symtab')
    addr={n:syms.get_symbol_by_name(n)[0]['st_value'] for n in
          ['res_vehicle_output_diag','res_uart_diag','res_bench_no_can']}
with ConnectHelper.session_with_chosen_probe(unique_id='20090928',blocking=False,
        target_override='cortex_m',frequency=1000000,
        options={'connect_mode':'attach','auto_unlock':False}) as s:
    t=s.target
    if t.read32(addr['res_bench_no_can'])!=1:
        raise RuntimeError('Not the isolated no-CAN bench image')
    end=time.monotonic()+a.seconds; previous=None
    with (root/'outputs_observed.jsonl').open('a',encoding='utf-8') as log:
        while True:
            app=t.read_memory_block32(addr['res_uart_diag'],24)
            if app[:3]!=[0x52455344,2,0x20260924]: raise RuntimeError('Identity mismatch')
            out=t.read_memory_block32(addr['res_vehicle_output_diag'],4)
            gpio=t.read32(0x50000414)  # ODR is drive command, not relay contact feedback.
            row=dict(tick=app[3],state=app[17],faults=hex(app[18]),relays=out[0],
                     go_pulses=out[1],rise_ms=out[2],fall_ms=out[3],
                     relay_pin_levels=(gpio>>10)&3,start_pin=(gpio>>12)&1)
            key=tuple(v for k,v in row.items() if k!='tick')
            if key!=previous or time.monotonic()>=end:
                line=json.dumps(row);print(line,flush=True);log.write(line+'\n');log.flush()
                previous=key
            if time.monotonic()>=end:break
            time.sleep(0.15)
