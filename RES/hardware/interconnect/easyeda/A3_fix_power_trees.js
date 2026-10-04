const W=p=>eda.sch_PrimitiveWire.create(p.flat(),undefined,null,null,null);
const F=(k,n,x,y,r=0)=>eda.sch_PrimitiveComponent.createNetFlag(k,n,x,y,r);
// Use one global netflag per local island: this is electrically explicit and avoids long visual power wires.
await W([[265,705],[280,705]]); await F("Power","+5V_MCU",280,705,270);
await W([[300,700],[315,700]]); await F("Power","+5V_MCU",315,700,270);
await W([[350,695],[365,695]]); await F("Power","+5V_MCU",365,695,270);
await W([[425,470],[485,470],[500,470]]); await F("Power","+5V_MCU",500,470,270);

await W([[265,590],[280,590]]); await F("Power","+3V3_RADIO",280,590,270);
await W([[350,580],[365,580]]); await F("Power","+3V3_RADIO",365,580,270);
await W([[350,535],[365,535]]); await F("Power","+3V3_RADIO",365,535,270);
await W([[350,480],[365,480]]); await F("Power","+3V3_RADIO",365,480,270);
await W([[875,700],[875,710]]); await F("Power","+3V3_RADIO",890,705,270);
await W([[875,705],[890,705]]);
await W([[975,700],[975,710]]); await W([[975,705],[990,705]]); await F("Power","+3V3_RADIO",990,705,270);

// Give the PTC/TVS branch a proper junction away from D2's pin location.
await W([[265,590],[285,590],[285,610],[300,610],[300,590]]);
return true;
