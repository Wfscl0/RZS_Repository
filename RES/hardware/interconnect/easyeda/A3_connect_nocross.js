// A3 schematic interconnect: every functional signal uses a short local stub plus
// an ordinary named-net marker. This intentionally eliminates long cross-sheet wires.
const W = p => eda.sch_PrimitiveWire.create(p.flat(), undefined, null, null, null);
const P = (net,x,y,r=0) => eda.sch_PrimitiveComponent.createNetFlag("Power",net,x,y,r);
// This connector build advertises createNetLabel but does not expose it live.
// Use the ordinary named-net flag (not the hexagonal I/O port) as its fallback.
const L = (net,x,y) => P(net,x,y,270);
const G = (x,y,r=0) => eda.sch_PrimitiveComponent.createNetFlag("Ground","GND",x,y,r);
const T = (x,y,s,c="#008000",fs=8) => eda.sch_PrimitiveText.create(x,y,s,0,c,null,fs);
const N = async(net,p) => { await W(p); const q=p[p.length-1]; await L(net,q[0],q[1]); };

// Functional separators: placement is grouped, but electrical connections are labels.
await eda.sch_PrimitiveRectangle.create(60,450,330,315,0,0,"#808080",null,1);
await eda.sch_PrimitiveRectangle.create(405,450,230,315,0,0,"#808080",null,1);
await eda.sch_PrimitiveRectangle.create(645,340,495,425,0,0,"#808080",null,1);
await eda.sch_PrimitiveRectangle.create(315,190,600,160,0,0,"#808080",null,1);

// J1 power input: pin 1 GND, pin 2 +3V3_IN, pin 3 +5V_IN.
await W([[110,665],[125,665]]); await G(125,665,270);
await N("+3V3_IN",[[110,675],[135,675]]);
await N("+5V_IN",[[110,685],[135,685]]);

// 5 V branch. Each series device is connected by same-name local labels.
await N("+5V_IN",[[155,705],[145,705]]);
await N("+5V_FUSED",[[195,705],[210,705]]);
await N("+5V_FUSED",[[225,705],[215,705]]);
await N("+5V_MCU",[[265,705],[280,705]]);
await N("+5V_MCU",[[300,700],[300,715]]);
await W([[300,660],[300,645]]); await G(300,645,0);
await N("+5V_MCU",[[350,695],[350,710]]);
await W([[350,665],[350,650]]); await G(350,650,0);

// 3.3 V radio branch.
await N("+3V3_IN",[[155,590],[145,590]]);
await N("+3V3_FUSED",[[195,590],[210,590]]);
await N("+3V3_FUSED",[[225,590],[215,590]]);
await N("+3V3_RADIO",[[265,590],[280,590]]);
await N("+3V3_RADIO",[[300,590],[315,590]]);
await W([[300,540],[285,540]]); await G(285,540,90);
await N("+3V3_RADIO",[[350,580],[365,580]]);
await W([[350,620],[350,635]]); await G(350,635,0);
await N("+3V3_RADIO",[[350,535],[365,535]]);
await W([[350,565],[350,575]]); await G(350,575,0);
await N("+3V3_RADIO",[[350,480],[365,480]]);
await W([[350,520],[350,530]]); await G(350,530,0);

// STM32 module: only used pins have short stubs. No line passes through either module.
await W([[425,580],[410,580]]); await G(410,580,90);
await W([[485,580],[500,580]]); await G(500,580,270);
await W([[560,580],[545,580]]); await G(545,580,90);
await W([[620,580],[635,580]]); await G(635,580,270);
await N("+5V_MCU",[[425,470],[405,470]]);
await N("+5V_MCU",[[485,470],[505,470]]);
await N("MCU_TX_PA9",[[485,480],[505,480]]);
await N("MCU_RX_PA10",[[560,490],[540,490]]);
await N("PB5_LORA_RESET_CTL",[[560,540],[540,540]]);
await N("PA1_RAW",[[425,560],[405,560]]);
await N("PA3_RAW",[[425,550],[405,550]]);
await N("PA0_RAW",[[485,570],[505,570]]);
await N("PA2_RAW",[[485,560],[505,560]]);

// UART series damping. R1: PA9 -> E220 RXD. R2: E220 TXD -> PA10.
await N("MCU_TX_PA9",[[680,560],[665,560]]);
await N("LORA_RXD",[[720,560],[735,560]]);
await N("MCU_RX_PA10",[[680,625],[665,625]]);
await N("LORA_TXD",[[720,625],[735,625]]);

// Reset: PB5 drives a 2N7002 open-drain stage. No long reset wire.
await N("PB5_LORA_RESET_CTL",[[655,430],[640,430]]);
await W([[695,430],[730,430]]);
await N("RESET_GATE",[[705,400],[705,415]]);
await W([[705,360],[705,345]]); await G(705,345,0);
await W([[760,410],[760,395]]); await G(760,395,0);
await N("LORA_RESET_N",[[760,450],[780,450]]);
await N("LORA_RESET_N",[[810,450],[810,465]]);
await N("+3V3_RADIO",[[810,410],[810,395]]);

// E220 stacked upward pins. J4..J9 are bare plated-hole placeholders, no sockets.
await N("+3V3_RADIO",[[875,700],[860,700]]);
await N("+3V3_RADIO",[[875,710],[860,710]]);
await N("+3V3_RADIO",[[975,700],[960,700]]);
await N("+3V3_RADIO",[[975,710],[960,710]]);
await W([[1075,700],[1090,700]]); await G(1090,700,270);
await N("LORA_RESET_N",[[1075,710],[1090,710]]);
await N("+3V3_RADIO",[[965,505],[945,505]]);
await N("LORA_TXD",[[965,565],[945,565]]);
await N("LORA_RXD",[[965,575],[945,575]]);

// E220 mode pins strapped low by fitted 0R resistors.
await N("E220_M1",[[900,355],[915,355]]);
await W([[900,365],[915,365]]); await G(915,365,270);
await N("E220_M1",[[840,360],[855,360]]);
await W([[800,360],[785,360]]); await G(785,360,90);
await N("E220_M0",[[1050,355],[1035,355]]);
await W([[1050,365],[1035,365]]); await G(1035,365,90);
await N("E220_M0",[[1110,360],[1125,360]]);
await W([[1070,360],[1085,360]]); await G(1085,360,270);

// Four protected extension I/O channels. Short stubs only; no signal crossing.
await N("PA1_RAW",[[390,300],[375,300]]);
await N("PA1_PROT",[[430,300],[445,300]]);
await N("PA1_PROT",[[500,300],[485,300]]);
await W([[500,350],[515,350]]); await G(515,350,270);
await N("PA1_PROT",[[580,300],[565,300]]);

await N("PA3_RAW",[[390,230],[375,230]]);
await N("PA3_PROT",[[430,230],[445,230]]);
await N("PA3_PROT",[[500,230],[485,230]]);
await W([[500,280],[515,280]]); await G(515,280,270);
await N("PA3_PROT",[[580,290],[565,290]]);
await W([[580,280],[565,280]]); await G(565,280,90);

await N("PA0_RAW",[[660,300],[645,300]]);
await N("PA0_PROT",[[700,300],[715,300]]);
await N("PA0_PROT",[[770,300],[755,300]]);
await W([[770,350],[785,350]]); await G(785,350,270);
await N("PA0_PROT",[[850,300],[835,300]]);

await N("PA2_RAW",[[660,230],[645,230]]);
await N("PA2_PROT",[[700,230],[715,230]]);
await N("PA2_PROT",[[770,230],[755,230]]);
await W([[770,280],[785,280]]); await G(785,280,270);
await N("PA2_PROT",[[850,290],[835,290]]);
await W([[850,280],[835,280]]); await G(835,280,90);

// Notes and values kept outside symbols to avoid symbol/wire/text overlap.
await T(70,790,"1  POWER INPUT / PROTECTION", "#008000",10);
await T(415,790,"2  STM32G0 CORE MODULE", "#008000",10);
await T(655,790,"3  E220 RADIO / UART / RESET", "#008000",10);
await T(325,355,"4  PROTECTED AUXILIARY I/O", "#008000",10);
await T(70,625,"F1/F2: 1206L050/15YR, 0.5A hold / 1A trip (C151162)");
await T(70,610,"FB1/FB2: BLM21PG600SN1D, 60R@100MHz, DCR 20mR, 0805");
await T(70,450,"C1/C3=10uF 10V X5R; C2=47uF 16V X5R; C4=100nF 50V X7R");
await T(650,680,"R1/R2/R5=33R; R6=100k; R7=10k; R8/R9=0R; R10-R13=100R");
await T(650,665,"D1=PESD5V0S1BA; D2-D6=PESD3V3S1BA-ES; Q1=2N7002");
await T(650,645,"UART: PA9 -> E220 RXD; E220 TXD -> PA10");
await T(650,410,"RESET: PB5 open-drain, active LOW; M0/M1 default LOW");
await T(840,740,"J4..J9: BARE PTH DIRECT-SOLDER HOLES, NO SOCKET BODY", "#B00000",8);
await T(525,315,"J10: PA1 / PA3 / GND");
await T(795,315,"J11: PA0 / PA2 / GND");

return {ok:true, topology:"short stubs + ordinary named-net markers", expectedWireCrossings:0};
