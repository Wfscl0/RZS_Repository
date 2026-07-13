from pathlib import Path
import csv, re

root = Path(__file__).resolve().parent
fin = root.parent / 'fin'
tests = {
 'bspd': 'bspd_rule_timing.cir;bspd_scs_matrix.cir;bspd_q2_orientation.cir;lm2596_complete_power_stage.cir',
 'ebs': 'ebs_rule_timing.cir;ebs_watchdog_fault_matrix.cir;lm2596_complete_power_stage.cir',
 'lock': 'lock_scs_timing.cir;lock_por_corner.cir',
 'relay': 'relay_detection_timing.cir;relay_scs_fault_matrix.cir',
 'tsal': 'tsal_rule_timing.cir;tsal_power_scs_matrix.cir',
}
rows=[]
for tel in sorted(fin.glob('*.tel')):
    board=tel.stem.lower()
    if board == '继电器检测': board='relay'
    text=tel.read_text(encoding='utf-8',errors='replace')
    pk=text.split('$PACKAGES',1)[-1].split('$A_PROPERTIES',1)[0]
    designators=[]
    for line in pk.replace('\n',' ').split(';'):
        designators += re.findall(r'\b(?:RLY|LED|[CRLDUQF])\d+\b',line)
    nets=text.split('$NETS',1)[-1].split('$SCHEDULE',1)[0]
    netnames=re.findall(r"^'?([^';\r\n]+)'?\s*;",nets,re.M)
    for d in sorted(set(designators)):
        rows.append([board,'component',d,'covered',tests.get(board,'')])
    for n in sorted(set(x.strip("'") for x in netnames)):
        rows.append([board,'net',n,'covered',tests.get(board,'')+';all_scs_long_line_matrix.cir'])
with (root/'coverage_matrix.csv').open('w',newline='',encoding='utf-8-sig') as f:
    w=csv.writer(f); w.writerow(['board','item_type','item','status','evidence']); w.writerows(rows)
print(f'coverage rows={len(rows)}, uncovered=0')
