const W=p=>eda.sch_PrimitiveWire.create(p.flat(),undefined,null,null,null);
const F=(k,n,x,y,r=0)=>eda.sch_PrimitiveComponent.createNetFlag(k,n,x,y,r);
// Join the real radio rail nodes; keep clear of the STM32 pad banks.
await W([[265,590],[280,590],[280,610],[370,610],[370,535],[350,535]]);
await W([[370,535],[370,480],[350,480]]);
await W([[370,535],[390,535],[390,505],[945,505]]);
await W([[875,700],[875,680],[975,680],[975,700]]);
await W([[390,505],[390,680],[875,680]]);
// Join MCU 5 V bypass/clamp node to the protected rail.
await W([[300,700],[315,700],[315,695],[350,695]]);
// R6 gate pulldown must connect to Q1 gate.
await W([[705,400],[705,430],[730,430]]);
// M1 and M0 low straps, straight through 0R to GND.
await W([[900,355],[870,355],[870,360],[840,360]]);
await W([[800,360],[785,360]]); await F("Ground","GND",785,360,90);
await W([[1050,355],[1070,355],[1070,360]]);
await W([[1110,360],[1125,360]]); await F("Ground","GND",1125,360,270);
return true;
