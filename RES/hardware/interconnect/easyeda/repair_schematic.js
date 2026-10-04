// RES_LoRa_32 schematic cleanup, intended for easyeda-agent `debug exec`.
// The current EasyEDA Pro 3.2.69 connector cannot create native net labels,
// therefore every managed signal below is an electrically continuous wire.
// The green text is a single, non-electrical readable name per signal.

const staleWireIds = [
  "76c75261100b54c8", // temporary PA0_AUX test stub
  "e4de9e8e140d1b7d", // temporary PA0_AUX test stub
  "d0b85bee605781a0"  // zero-length wire
];

const oldWires = await eda.sch_PrimitiveWire.get(staleWireIds);
if (oldWires.length) {
  await eda.sch_PrimitiveWire.delete(oldWires);
}

const routes = [
  // STM32 auxiliary GPIO to protection resistors.
  { net: "PA0_AUX", line: [525,650, 540,650, 540,455, 420,455, 420,220, 450,220] },
  { net: "PA1_AUX", line: [395,640, 390,640, 390,270, 450,270] },
  { net: "PA2_AUX", line: [525,640, 550,640, 550,445, 430,445, 430,320, 450,320] },
  { net: "PA3_AUX", line: [395,630, 400,630, 400,370, 450,370] },

  // STM32 <-> E220 UART.  The E220 TXD goes to MCU RX and vice versa.
  { net: "UART_MCU_TX", line: [535,560, 690,560, 690,640, 730,640] },
  { net: "UART_MCU_RX", line: [535,570, 675,570, 675,680, 730,680] },
  { net: "LORA_RXD", line: [830,640, 860,640, 860,650, 1080,650, 1080,630, 1060,630] },
  { net: "LORA_TXD", line: [830,680, 850,680, 850,670, 1090,670, 1090,620, 1060,620] },

  // Open-drain E220 reset control.
  { net: "PB5_LORA_RESET_CTL", line: [535,620, 520,620, 520,465, 360,465, 360,255, 40,255] },
  { net: "LORA_RESET_N", line: [300,275, 320,275, 320,190, 370,190, 370,460, 970,460, 970,560, 960,560] },

  // Protected expansion terminals.  J8 is ordered PA2, PA1, PA0 top-to-bottom
  // so the schematic and PCB can route without crossovers.
  { net: "PA2_EXT", line: [710,280, 680,280, 680,320, 520,320] },
  { net: "PA1_EXT", line: [710,270, 520,270] },
  { net: "PA0_EXT", line: [710,260, 670,260, 670,220, 520,220] },
  { net: "PA3_EXT", line: [710,430, 700,430, 700,370, 520,370] },

  // E220 MBL power jumpers required by the user manual:
  // global pins 1-2 (RF VCC) and 3-4 (MCU VIO).
  { net: "+3V3_RADIO", line: [930,520, 940,520, 940,510] },
  { net: "+3V3_RADIO", line: [930,530, 940,530, 940,540] }
];

const managedLabels = routes.map(r => r.net).filter((v, i, a) => a.indexOf(v) === i);
const allText = await eda.sch_PrimitiveText.getAll();
const staleText = allText.filter(t => managedLabels.includes(t.getState_Content()));
if (staleText.length) {
  await eda.sch_PrimitiveText.delete(staleText);
}

const wireIds = [];
for (const route of routes) {
  const wire = await eda.sch_PrimitiveWire.create(route.line, route.net);
  if (!wire) throw new Error("Failed to create " + route.net);
  wireIds.push(wire.getState_PrimitiveId());
}

const labels = [
  [425,455,"PA0_AUX"], [392,500,"PA1_AUX"],
  [435,445,"PA2_AUX"], [402,500,"PA3_AUX"],
  [585,560,"UART_MCU_TX"], [585,570,"UART_MCU_RX"],
  [900,650,"LORA_RXD"], [900,670,"LORA_TXD"],
  [365,465,"PB5_LORA_RESET_CTL"], [650,460,"LORA_RESET_N"],
  [575,210,"PA0_EXT"], [575,270,"PA1_EXT"],
  [575,320,"PA2_EXT"], [575,370,"PA3_EXT"]
];
const textIds = [];
for (const [x,y,content] of labels) {
  const text = await eda.sch_PrimitiveText.create(x, y, content, 0, "#008000", null, 8);
  if (!text) throw new Error("Failed to create label text " + content);
  textIds.push(text.getState_PrimitiveId());
}

return { createdWires: wireIds, createdTexts: textIds };
