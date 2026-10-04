// Final electrical wiring and readable labels for A3.
// On connector 0.21.2 the explicit net argument can reject otherwise valid wires;
// EasyEDA compiles the net from electrical continuity and attached flags.
const W=(n,p)=>eda.sch_PrimitiveWire.create(p.flat(),undefined,null,null,null);
const F=(kind,n,x,y,r=0)=>eda.sch_PrimitiveComponent.createNetFlag(kind,n,x,y,r);
const T=(x,y,s,c="#008000",fs=8)=>eda.sch_PrimitiveText.create(x,y,s,0,c,null,fs);

// Input J1: pin1 GND, pin2 +3V3, pin3 +5V.
await W("GND",[[110,665],[125,665]]); await F("Ground","GND",125,665,270);
await W("+3V3_IN",[[110,675],[145,675],[145,590],[155,590]]);
await W("+5V_IN",[[110,685],[145,685],[145,705],[155,705]]);

// 5 V protected rail for STM32 board.
await W("+5V_IN_FUSED",[[195,705],[225,705]]);
await W("+5V_MCU",[[265,705],[330,705],[330,695],[350,695]]);
await W("+5V_MCU",[[300,700],[300,705]]);
await W("GND",[[300,660],[300,645]]); await F("Ground","GND",300,645,0);
await W("GND",[[350,665],[350,650]]); await F("Ground","GND",350,650,0);
await W("+5V_MCU",[[330,705],[380,705],[380,460],[425,460],[425,470],[485,470]]);

// Independent radio 3.3 V protected rail and local decoupling.
await W("+3V3_IN_FUSED",[[195,590],[225,590]]);
await W("+3V3_RADIO",[[265,590],[350,590],[350,580]]);
await W("GND",[[300,540],[300,525]]); await F("Ground","GND",300,525,0);
await W("GND",[[350,620],[350,635]]); await F("Ground","GND",350,635,0);
await W("+3V3_RADIO",[[350,580],[380,580],[380,535],[350,535]]);
await W("GND",[[350,565],[350,575]]); await F("Ground","GND",350,575,0);
await W("+3V3_RADIO",[[380,535],[380,480],[350,480]]);
await W("GND",[[350,520],[350,530]]); await F("Ground","GND",350,530,0);

// STM32 module grounds.
await W("GND",[[425,580],[485,580],[500,580]]); await F("Ground","GND",500,580,270);
await W("GND",[[560,580],[620,580],[635,580]]); await F("Ground","GND",635,580,270);

// UART: series resistors at the source/receiver side, route around J3 pins.
await W("MCU_TX_PA9",[[485,480],[520,480],[520,440],[650,440],[650,560],[680,560]]);
await W("LORA_RXD",[[720,560],[900,560],[900,575],[965,575]]);
await W("MCU_RX_PA10",[[560,490],[535,490],[535,625],[680,625]]);
await W("LORA_TXD",[[720,625],[920,625],[920,565],[965,565]]);

// Open-drain E220 reset. R5=33R, R6=100k pulldown, R7=10k pullup.
await W("PB5_LORA_RESET_CTL",[[560,540],[545,540],[545,410],[635,410],[635,430],[655,430]]);
await W("RESET_GATE",[[695,430],[730,430]]);
await W("RESET_GATE",[[705,400],[705,430]]);
await W("GND",[[705,360],[705,345]]); await F("Ground","GND",705,345,0);
await W("GND",[[760,410],[760,395]]); await F("Ground","GND",760,395,0);
await W("LORA_RESET_N",[[760,450],[810,450],[1040,450],[1040,650],[1100,650],[1100,710],[1075,710]]);
await W("+3V3_RADIO",[[810,410],[810,395]]); await F("Power","+3V3_RADIO",810,395,180);

// E220 manual mapping: P1-2 and P3-4 shorted on their own power islands.
await W("+3V3_RADIO",[[875,700],[875,710]]); await F("Power","+3V3_RADIO",875,705,270);
await W("+3V3_RADIO",[[975,700],[975,710]]); await F("Power","+3V3_RADIO",975,705,270);
await W("GND",[[1075,700],[1090,700]]); await F("Ground","GND",1090,700,270);
await W("+3V3_RADIO",[[965,505],[945,505]]); await F("Power","+3V3_RADIO",945,505,90);

// M1/M0 fixed LOW by fitted 0R straps; adjacent E17/E19 are GND.
await W("E220_M1",[[900,355],[840,355]]); await W("GND",[[800,355],[790,355]]); await F("Ground","GND",790,355,90);
await W("GND",[[900,365],[915,365]]); await F("Ground","GND",915,365,270);
await W("E220_M0",[[1050,355],[1110,355]]); await W("GND",[[1070,355],[1060,355]]); await F("Ground","GND",1060,355,90);
await W("GND",[[1050,365],[1065,365]]); await F("Ground","GND",1065,365,270);

// Protected auxiliary I/O, connectors: J10=PA1/PA3/GND, J11=PA0/PA2/GND.
await W("PA1_EXT",[[425,560],[340,560],[340,300],[390,300]]);
await W("PA3_EXT",[[425,550],[360,550],[360,230],[390,230]]);
await W("PA0_EXT",[[485,570],[510,570],[510,380],[640,380],[640,300],[660,300]]);
await W("PA2_EXT",[[485,560],[500,560],[500,370],[630,370],[630,230],[660,230]]);
await W("PA1_EXT_PROT",[[430,300],[500,300],[580,300]]);
await W("PA3_EXT_PROT",[[430,230],[500,230],[550,230],[550,290],[580,290]]);
await W("GND",[[500,350],[500,365]]); await F("Ground","GND",500,365,0);
await W("GND",[[500,280],[510,280]]); await F("Ground","GND",510,280,270);
await W("GND",[[580,280],[600,280]]); await F("Ground","GND",600,280,270);
await W("PA0_EXT_PROT",[[700,300],[770,300],[850,300]]);
await W("PA2_EXT_PROT",[[700,230],[770,230],[820,230],[820,290],[850,290]]);
await W("GND",[[770,350],[770,365]]); await F("Ground","GND",770,365,0);
await W("GND",[[770,280],[780,280]]); await F("Ground","GND",780,280,270);
await W("GND",[[850,280],[870,280]]); await F("Ground","GND",870,280,270);

// One readable label per functional net plus explicit values.
await T(70,790,"STACKED DIRECT-SOLDER CARRIER - NO SOCKET BODY", "#B00000",11);
await T(70,640,"F1/F2 = 0.5A hold / 1A trip PTC, 1206 (C151162)");
await T(70,625,"FB1/FB2 = BLM21PG600SN1D, 60R @ 100MHz, DCR 20mR, 0805");
await T(70,445,"C1/C3=10uF 10V X5R; C2=47uF 16V X5R; C4=100nF 50V X7R");
await T(650,680,"R1/R2/R5=33R; R6=100k; R7=10k; R8/R9=0R; R10-R13=100R");
await T(650,665,"J4..J9 map E220 logical pins P1..P19; P7..P15 are J7-1..J7-9");
await T(680,645,"UART: PA9 -> E220 RXD; E220 TXD -> PA10");
await T(690,465,"RESET: PB5 open-drain; active LOW");
await T(565,315,"J10: PA1 / PA3 / GND"); await T(835,315,"J11: PA0 / PA2 / GND");
return {ok:true};
