"""Check revised netlist topology and settled-state latch sequences.

Assumes U9 is a pin-compatible NAND, U10 a three-input OR and U11 the
previous SN74LVC2G74. This is not a power-off leakage or analog simulation.
"""
from pathlib import Path
import hashlib
import json
import re

HERE = Path(__file__).resolve().parent
SOURCE = Path('C:/Users/30836/Desktop/Netlist_Schematic1_2026-09-16.tel')

def parse(path):
    text = path.read_text(encoding='utf-8-sig')
    body = text.split('$NETS',1)[1].split('$SCHEDULE',1)[0]
    nets = {}
    for m in re.finditer(r"(?m)^('[^']+'|[^\s;]+)\s*;\s*(.*?)(?=\n(?:'[^']+'|[^\s;]+)\s*;|\Z)",body,re.S):
        nets[m[1].strip("'")] = set(re.findall(r'\b[A-Z]+\d+\.\d+\b',m[2]))
    return nets, {pin: name for name,pins in nets.items() for pin in pins}

new,pins = parse(SOURCE)
old,old_pins = parse(HERE.parent/'lock.tel')
def connected(*args):
    assert len({pins[x] for x in args}) == 1, args

for group in [('U11.2','U11.8','U9.5','U10.5'),
              ('U9.4','U10.3','U11.1'),('U10.4','U11.6'),
              ('U10.1','H3.3'),('U10.6','U22.4'),
              ('U11.7','U17.4'),('U11.3','U8.2'),
              ('U9.1','H2.1','R17.2'),('U9.2','R18.1','R19.2')]:
    connected(*group)
assert pins['U11.2']=='+5V'
assert pins['U11.7']=='POR#'
assert pins['U10.6']=='POR'

# All old BMS-related connections are retained, using actual pin sets rather
# than automatically generated net names.
bms_refs={'U5','U21','R4','R5','R7','R9','R11','R12','C7','R27'}
bms_pinsets=[(p,n,pins[p],old[n],new[pins[p]]) for p,n in old_pins.items()
             if p.split('.')[0] in bms_refs]
# Other channels changed their membership of shared rails; this does not
# constitute a change to BMS rail/PGOOD connections.
shared={'GND','+5V','POR','POR#'}
bms_unchanged=all(n==nn if n in shared else a==b
                  for _,n,nn,a,b in bms_pinsets)
assert bms_unchanged

class Revised:
    def __init__(self,e=1,r=1):
        self.e=e; self.r=r; self.por_n=0; self.reset_n=1; self.q=1
        self.trace=[]
    def step(self,label,**changes):
        old_f=1-(self.e & self.r)
        for key,value in changes.items(): setattr(self,key,value)
        f=1-(self.e & self.r)
        clr_n=self.reset_n | f | (1-self.por_n)
        if not self.por_n: self.q=1
        elif not clr_n: self.q=0
        elif f and not old_f: self.q=1
        self.trace.append(dict(step=label,E=self.e,R=self.r,POR_n=self.por_n,
                               RESET_n=self.reset_n,F=f,CLR_n=clr_n,STATE=1-self.q))
        return 1-self.q

def pulse(c):
    c.step('reset asserted',reset_n=0)
    return c.step('reset released',reset_n=1)

cases={}
c=Revised()
assert c.step('EBS and RES healthy before board startup')==0
assert c.step('POR released',por_n=1)==0
assert pulse(c)==1
assert c.step('first EBS fault',e=0)==0
assert pulse(c)==0
assert c.step('EBS recovers, latch retains',e=1)==0
assert pulse(c)==1
assert c.step('first RES fault',r=0)==0
assert c.step('RES recovers, latch retains',r=1)==0
assert pulse(c)==1
assert c.step('brownout with both external inputs high',por_n=0)==0
assert c.step('POR releases again',por_n=1)==0
assert pulse(c)==1
assert c.step('first fault after brownout',e=0)==0
cases['inputs_power_first_then_normal_reset']=c.trace

for e,r in [(0,0),(0,1),(1,0)]:
    c=Revised(e,r)
    c.step('initial fault during POR')
    assert c.step('POR released',por_n=1)==0
    assert pulse(c)==0
    cases[f'initial_E{e}_R{r}']=c.trace

c=Revised()
c.step('reset held during power-up',reset_n=0)
assert c.step('POR released with all inputs healthy',por_n=1)==1
cases['reset_held_at_startup_auto_enables']=c.trace

result=dict(source=str(SOURCE),sha256=hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
            removed_components=sorted({p.split('.')[0] for p in old_pins}-{p.split('.')[0] for p in pins}),
            added_components=sorted({p.split('.')[0] for p in pins}-{p.split('.')[0] for p in old_pins}),
            BMS_connections_unchanged=bms_unchanged,cases=cases,
            limits=['User identified U9 as 74LVC1G00GW; U10 is assumed to remain the former three-input OR function.',
                    'Settled Boolean model only; fault during active reset still has an asynchronous timing race.',
                    'No power-off injection current, transient, thermal or physical-board validation.'])
(HERE/'revision_evidence.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps({k:v for k,v in result.items() if k!='cases'},ensure_ascii=False,indent=2))
print('Settled-state scenarios checked:',len(cases))
