// Replace endpoint-touching stubs with single pin-to-pin wires.
// This is required because the current editor does not merge a newly drawn
// wire with a pre-existing dangling stub reliably during netlist compilation.

const removeWireIds = [
  // old endpoint stubs
  "1f14aa46c37b0e64","ea9e31155d59f03d",
  "2a2cc3d0a02d062a","f51b62db840f2563",
  "512aec2a6fe09971","3c043b5148e170b8",
  "c24897bb8c542986","5e591aa18981576f",
  "49ee7b5e9f471445","cedaa031bb335b82",
  "31d8913f75b3870b","ff62b6ca847d7509",
  "471012333b16a7bf","89d8974aa0669e0b",
  "f38381bdf86f6d1a","688030f89c7cf09f",
  "c4498b68060af34d","8bbcdb659c69e163",
  "7d4fd4f9196982fd","fdfdeb00c2e22e3c",
  "99aadf279fbad5a6","6f799c66454a0ced",
  "5a186f5bf87fb09c","e30c7f51a9d8c20e",
  // v1 bridge wires
  "16b5ab49c738209c","55566aa45433a48f",
  "272612970528b59d","4222a07a72578288",
  "1a158225036613ac","a98feff2dc222710",
  "d20f3a24b28b6d24","dc62e102780ee779",
  "b9d3cf69dffd3fc5","3be17ea20897d1fe",
  "dd6cf8a77d43de74","fbcb589fe59e7451",
  "1983f6430fa4b39e","5f0fc73f73640556"
];

const old = await eda.sch_PrimitiveWire.get(removeWireIds);
if (old.length) await eda.sch_PrimitiveWire.delete(old);

const routes = [
  // STM32 module GPIO pins -> input side of series resistors.
  {net:"PA0_AUX", line:[495,650, 540,650, 540,430, 440,430, 440,220, 480,220]},
  {net:"PA1_AUX", line:[435,640, 410,640, 410,270, 480,270]},
  {net:"PA2_AUX", line:[495,640, 550,640, 550,440, 430,440, 430,320, 480,320]},
  {net:"PA3_AUX", line:[435,630, 420,630, 420,370, 480,370]},

  // STM32 USART1 <-> E220 UART.
  {net:"UART_MCU_TX", line:[495,560, 700,560, 700,640, 760,640]},
  {net:"UART_MCU_RX", line:[575,570, 680,570, 680,680, 760,680]},
  {net:"LORA_RXD", line:[800,640, 850,640, 850,650, 1080,650, 1080,630, 1030,630]},
  {net:"LORA_TXD", line:[800,680, 840,680, 840,670, 1090,670, 1090,620, 1030,620]},

  // PB5 drives an open-drain reset.  Q1 drain, R7 pull-up, and E220 REST
  // are drawn as one continuous net.
  {net:"PB5_LORA_RESET_CTL", line:[575,620, 520,620, 520,465, 360,465, 360,255, 120,255]},
  {net:"LORA_RESET_N", line:[240,275, 300,275, 320,275, 320,190, 370,190, 370,460, 970,460, 970,560, 930,560]},

  // Protected expansion terminals.
  {net:"PA0_EXT", line:[520,220, 650,220, 650,280, 740,280]},
  {net:"PA1_EXT", line:[520,270, 740,270]},
  {net:"PA2_EXT", line:[520,320, 660,320, 660,260, 740,260]},
  {net:"PA3_EXT", line:[520,370, 700,370, 700,430, 740,430]}
];

const made=[];
for(const r of routes){
  const w=await eda.sch_PrimitiveWire.create(r.line,r.net);
  if(!w) throw new Error("wire create failed: "+r.net);
  made.push(w.getState_PrimitiveId());
}
return {deleted:old.length,created:made};
