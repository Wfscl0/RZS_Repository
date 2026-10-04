// Normalize values and BOM behavior for the stacked direct-solder carrier.
const values = {
  C1:"10uF 10V X5R", C2:"47uF 16V X5R", C3:"10uF 10V X5R", C4:"100nF 50V X7R",
  D1:"PESD5V0S1BA 5V TVS", D2:"PESD3V3S1BA-ES", D3:"PESD3V3S1BA-ES",
  D4:"PESD3V3S1BA-ES", D5:"PESD3V3S1BA-ES", D6:"PESD3V3S1BA-ES",
  F1:"PTC 0.5A HOLD / 1A TRIP", F2:"PTC 0.5A HOLD / 1A TRIP",
  FB1:"60R@100MHz / DCR 20mR", FB2:"60R@100MHz / DCR 20mR",
  Q1:"2N7002", R1:"33R", R2:"33R", R5:"33R", R6:"100k", R7:"10k",
  R8:"0R", R9:"0R", R10:"100R", R11:"100R", R12:"100R", R13:"100R"
};

const modulePads = {
  J2:"STM32 LEFT PAD ARRAY - DIRECT SOLDER",
  J3:"STM32 RIGHT PAD ARRAY - DIRECT SOLDER",
  J4:"E220 P1-P2 PAD GROUP", J5:"E220 P3-P4 PAD GROUP", J6:"E220 P5-P6 PAD GROUP",
  J7:"E220 P7-P15 PAD GROUP", J8:"E220 P16-P17 PAD GROUP", J9:"E220 P18-P19 PAD GROUP"
};

const all = await eda.sch_PrimitiveComponent.getAll();
const parts = all.filter(c => {
  const d = c.getState_Designator && c.getState_Designator();
  return d && (values[d] || modulePads[d] || ["J1","J10","J11"].includes(d));
});
const changed=[];
for (const c of parts) {
  const d=c.getState_Designator();
  const patch={ uniqueId:`A3_${d}` };
  if (values[d]) patch.otherProperty={Value:values[d]};
  if (modulePads[d]) {
    patch.addIntoBom=false;
    patch.otherProperty={Value:modulePads[d], Assembly:"NO CONNECTOR BODY; MODULE PINS THROUGH PCB AND DIRECT-SOLDERED"};
  }
  await eda.sch_PrimitiveComponent.modify(c,patch);
  changed.push(d);
}
return {changed};
