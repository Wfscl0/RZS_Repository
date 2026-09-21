"""Netlist-anchored Boolean audit, not transistor/SPICE or hardware simulation.

Run with Python 3. Writes evidence.json beside this file. Analog calculations
are nominal estimates. Discrete steps assume signals settle between operations;
the asynchronous-clear/clock race is checked separately as a timing constraint.
"""
from pathlib import Path
import hashlib
import json
import math
import re

HERE = Path(__file__).resolve().parent
SOURCE = HERE.parent / 'lock.tel'
raw = SOURCE.read_text(encoding='utf-8-sig')
net_text = raw.split('$NETS', 1)[1].split('$SCHEDULE', 1)[0]
nets = {}
for m in re.finditer(r"(?m)^('[^']+'|[^\s;]+)\s*;\s*(.*?)(?=\n(?:'[^']+'|[^\s;]+)\s*;|\Z)", net_text, re.S):
    nets[m[1].strip("'")] = set(re.findall(r'\b[A-Z]+\d+\.\d+\b', m[2]))
pin_net = {pin: name for name, pins in nets.items() for pin in pins}

def joined(*pins):
    assert len({pin_net[p] for p in pins}) == 1, pins

# Explicitly verify every signal connection used in the latch abstraction.
for pins in [
    ('U13.2', 'U13.7', 'U13.8'),
    ('U13.6', 'U11.7', 'U1.7', 'U5.7', 'U17.4'),
    ('U13.1', 'U24.4'), ('U13.5', 'U11.2', 'U23.2'),
    ('U9.4', 'U11.1', 'U23.1'), ('U23.4', 'U20.3'),
    ('U20.4', 'U11.6'), ('U20.1', 'H3.3'),
    ('U11.3', 'U8.2'), ('U9.1', 'U24.1', 'H2.1'),
    ('U9.2', 'U24.2', 'R18.1', 'R19.2'),
    ('U1.1', 'U2.3', 'U7.7'), ('U1.6', 'U2.4'),
    ('U5.1', 'U21.3', 'U7.1'), ('U5.6', 'U21.4'),
    ('U2.6', 'U20.6', 'U21.6', 'U22.4'),
]:
    joined(*pins)
assert pin_net['U13.2'] == '+5V'
assert pin_net['U13.6'] == 'POR#'

class REChannel:
    def __init__(self):
        self.e = self.r = self.por_n = 0
        self.reset_n = 1
        self.armed = 0  # U13.Q, D tied high, /CLR=POR#
        self.fault_latched = 1  # U11.Q, /PRE=POR#, STATE=/Q
        self.trace = []

    def step(self, label, **changes):
        old_healthy = self.e & self.r
        old_fault = 1 - old_healthy
        old_armed = self.armed
        for name, value in changes.items():
            setattr(self, name, value)
        healthy = self.e & self.r
        fault = 1 - healthy
        clear_n = self.reset_n | (fault & old_armed) | (1 - self.por_n)
        if not self.por_n:
            self.fault_latched = 1
        elif not clear_n:
            self.fault_latched = 0
        elif fault and not old_fault:
            self.fault_latched = old_armed
        if not self.por_n:
            self.armed = 0
        elif healthy and not old_healthy:
            self.armed = 1
        self.trace.append(dict(step=label, E=self.e, R=self.r, POR_n=self.por_n,
                               RESET_n=self.reset_n, U13_Q=self.armed,
                               U11_Q=self.fault_latched, RE_STATE=1-self.fault_latched))
        return 1-self.fault_latched

def reset(c):
    c.step('reset asserted', reset_n=0)
    return c.step('reset released', reset_n=1)

cases = {}
c = REChannel()
c.step('power-on reset active')
c.step('POR released', por_n=1)
c.step('manual EBS high after POR', e=1)
c.step('manual RES high after POR', r=1)
assert c.armed == 1
assert reset(c) == 1
assert c.step('first EBS fault', e=0) == 0
assert reset(c) == 0
assert c.step('EBS recovered, fault remains latched', e=1) == 0
assert reset(c) == 1
assert c.step('RES fault', r=0) == 0
cases['manual_high_after_POR_expected_sequence'] = c.trace

c = REChannel()
c.step('both inputs high while POR active', e=1, r=1)
c.step('POR released with inputs unchanged', por_n=1)
assert c.armed == 0
assert reset(c) == 1
assert c.step('first EBS fault is not captured', e=0) == 1
c.step('first recovery arms U13', e=1)
assert c.step('second EBS fault is captured', e=0) == 0
cases['early_high_or_brownout_restart_counterexample'] = c.trace

# /CLR must be inactive at least 1.6 ns before CLK rising at 5 V.
# A fault rises at CLK directly, but /CLR only rises after OR gate delay.
# For armed RE, the same path also includes U23 AND delay.
race = []
for delay_ns in (1.0, 3.0, 4.5):
    race.append(dict(or_delay_ns=delay_ns, required_clear_release_by_ns=-1.6,
                     actual_clear_release_ns=delay_ns, meets_requirement=False,
                     consequence='Fault capture is not guaranteed; no second clock edge for a persistent fault.'))

g = 1/16000 + 1/10000 + 1/1000000
fall = ((5/16000 + 0.1/1000000) / g) * (1 + 47000/10000)
rise = ((5/16000 + 5/1000000) / g) * (1 + 47000/10000)
tau = (47000*10000/(47000+10000))*220e-9
analog = dict(
    comparator_falling_threshold_V=fall,
    comparator_rising_threshold_V_approx=rise,
    comparator_hysteresis_V_approx=rise-fall,
    comparator_input_tau_ms=tau*1000,
    step_12_to_10_detection_ms=-tau*math.log((fall-10)/(12-10))*1000,
    step_12_to_9_detection_ms=-tau*math.log((fall-9)/(12-9))*1000,
    RES_divider_ratio=12000/(20000+12000),
    RES_node_V={str(v): v*12000/(20000+12000) for v in (12,14.4,14.67,16,24)},
    RES_max_external_V_for_5p5V_input_nominal=5.5*(20000+12000)/12000,
    RES_node_at_14p4_assuming_R18_1pct_R19_5pct_V=14.4*(12000*1.05)/(20000*.99+12000*1.05),
    POR_supply_threshold_V=.405*(1+1000000/100000),
    POR_sense_filter_tau_ms=(1000000*100000/(1000000+100000))*4.7e-9*1000,
    POR_CT_resistor_delay_typ_ms=300,
    comparator_output_capacitance_estimate_pF=8.5,
    comparator_output_tau_ns=5000*8.5e-12*1e9,
    comparator_output_30_to_70_pct_ns=5000*8.5e-12*math.log(.7/.3)*1e9,
    comparator_output_avg_ns_per_V_30_to_70_pct=5000*8.5e-12*math.log(.7/.3)*1e9/2,
    DFF_recommended_max_transition_ns_per_V=5,
)
result = dict(netlist_sha256=hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
              method='Netlist assertions + settled-state truth-table model + timing inequality + nominal circuit calculations',
              limitations='Not SPICE, not hardware measurement; analog capacitance and selected tolerances are estimates.',
              cases=cases, reset_fault_race=race, analog=analog)
(HERE/'evidence.json').write_text(json.dumps(result,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(result,ensure_ascii=False,indent=2))
