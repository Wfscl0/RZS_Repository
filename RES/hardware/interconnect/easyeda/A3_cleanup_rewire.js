// Clean up the first-pass A3 schematic and rewire it for a readable, routable carrier PCB.
const deleteIds = new Set([
  "92152719021cb655","b8c9e07d879c83ed","e296a66a0d3f0db3","2ee0da607d3eeefb",
  "79cfcf8dedc26bed","f96392c32935c2e6","ecd1b15384f5d696","54959f4494ad66fb",
  "001fd53ebbc58e7c","982e632267482fe9","98204b8d7859a4ce","1fec43a1c621b538",
  "ec6db3e285535567","2bb74e29bf6f4f31","84a65a429d554686","642ab03e32f53a55",
  "22c83b0e9ac77f9a","6121432277526022"
]);

const oldWires=await eda.sch_PrimitiveWire.get([...deleteIds]);
if (oldWires.length) await eda.sch_PrimitiveWire.delete(oldWires);

const byD={};
for (const c of await eda.sch_PrimitiveComponent.getAll()) {
  const d=c.getState_Designator && c.getState_Designator();
  if (d) byD[d]=c;
}

async function move(d,x,y,rotation){
  const patch={x,y};
  if (rotation!==undefined) patch.rotation=rotation;
  await eda.sch_PrimitiveComponent.modify(byD[d],patch);
}

// Separate the receive channel and align the protected auxiliary I/O blocks.
await move("R2",700,625,0);
await move("R10",410,300,0);
await move("R11",410,230,0);
await move("R12",680,300,0);
await move("R13",680,230,0);
await move("D3",500,325,90);
await move("D4",500,255,90);
await move("D5",770,325,90);
await move("D6",770,255,90);
await move("J10",600,290,0);
await move("J11",870,290,0);

const wire = async (net,line)=>eda.sch_PrimitiveWire.create(line.flat(),net);

// USART receive: escape from the left side of J3 and route above the module symbols.
await wire("MCU_RX_PA10",[[560,490],[535,490],[535,625],[680,625]]);
await wire("LORA_TX_TO_MCU",[[720,625],[920,625],[920,565],[965,565]]);

// LoRa reset open-drain control; keep the long run to the far right, away from UART.
await wire("PB5_LORA_RESET_CTL",[[560,540],[545,540],[545,410],[635,410],[635,430],[655,430]]);
await wire("LORA_RESET_N",[[760,450],[1040,450],[1040,650],[1100,650],[1100,710],[1075,710]]);

// Protected auxiliary I/O. Pin order preserves the MCU-side physical routing.
await wire("PA1_EXT",[[425,560],[340,560],[340,300],[390,300]]);
await wire("PA3_EXT",[[425,550],[360,550],[360,230],[390,230]]);
await wire("PA0_EXT",[[485,570],[510,570],[510,380],[640,380],[640,300],[660,300]]);
await wire("PA2_EXT",[[485,560],[500,560],[500,370],[630,370],[630,230],[660,230]]);

// J10: PA1, PA3, GND.
await wire("PA1_EXT_PROT",[[430,300],[500,300],[580,300]]);
await wire("PA3_EXT_PROT",[[430,230],[500,230],[550,230],[550,290],[580,290]]);
await wire("GND",[[500,350],[500,365]]);
await wire("GND",[[500,280],[500,290]]);
await wire("GND",[[580,280],[600,280]]);

// J11: PA0, PA2, GND.
await wire("PA0_EXT_PROT",[[700,300],[770,300],[850,300]]);
await wire("PA2_EXT_PROT",[[700,230],[770,230],[820,230],[820,290],[850,290]]);
await wire("GND",[[770,350],[770,365]]);
await wire("GND",[[770,280],[770,290]]);
await wire("GND",[[850,280],[870,280]]);

// Explicit layout/value notes remain readable even when library symbols suppress Value fields.
await eda.sch_PrimitiveText.create(70,625,"F1/F2: PTC 0.5A HOLD / 1A TRIP",0,"#008800",null,8);
await eda.sch_PrimitiveText.create(70,640,"FB1/FB2: 60R @ 100MHz, DCR <= 20mR",0,"#008800",null,8);
await eda.sch_PrimitiveText.create(70,445,"C1/C3: 10uF 10V X5R; C2: 47uF 16V X5R; C4: 100nF 50V X7R",0,"#008800",null,8);
await eda.sch_PrimitiveText.create(650,680,"R1/R2/R5=33R; R6=100k; R7=10k; R8/R9=0R; R10-R13=100R",0,"#008800",null,8);

return {ok:true};
