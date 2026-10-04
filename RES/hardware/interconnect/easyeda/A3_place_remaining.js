// Place the remaining A3 parts in small batches. Avoid slow PTC library symbols: use
// hand-solderable 1206 two-pin symbols and retain the exact PTC LCSC/MPN in properties.
const LIB="0819f05c4eef4c71ace90d822a990e87";
const parts=[
 ["F1","c1b17fa23f304726bc91c5924d9b7c0f",175,705,0],["FB1","9a036d90211a4df79dae8b43cf4fdfda",245,705,0],
 ["D1","93250235cc8d4546a65e7ad6d841ccc2",300,680,90],["C1","2c8bdaeb33624757a7871109432b253d",350,680,90],
 ["F2","c1b17fa23f304726bc91c5924d9b7c0f",175,590,0],["FB2","9a036d90211a4df79dae8b43cf4fdfda",245,590,0],
 ["D2","a7cd7428f1cf491fa1024dbb27bd014c",300,565,90],["C2","9087862aa5754cc9b0c32846063234ba",350,600,90],
 ["C3","2c8bdaeb33624757a7871109432b253d",350,550,90],["C4","96b39256cc3f4d80bd3b503deb4f3328",350,500,90],
 ["J2","a8637fc769e848c39be208f75091c1c6",455,525,0],["J3","a8637fc769e848c39be208f75091c1c6",590,525,0],
 ["R1","c1b17fa23f304726bc91c5924d9b7c0f",700,560,0],["R2","c1b17fa23f304726bc91c5924d9b7c0f",700,625,0],
 ["R5","c1b17fa23f304726bc91c5924d9b7c0f",675,430,0],["Q1","f8007837564a4f1fa0e6b57b81dccb0d",750,430,0],
 ["R6","40ff282b3d594c33b798d1707d8406cb",705,380,90],["R7","b948db94476e4027ac8953235755ec96",810,430,90],
 ["J4","4f4168f9934b4be2b934e441928fe016",855,705,180],["J5","4f4168f9934b4be2b934e441928fe016",955,705,180],
 ["J6","4f4168f9934b4be2b934e441928fe016",1055,705,180],["J7","e0b5dd52129349b48af6010a5d4a81b6",945,535,180],
 ["J8","4f4168f9934b4be2b934e441928fe016",880,360,180],["J9","4f4168f9934b4be2b934e441928fe016",1030,360,180],
 ["R8","fc38f436091b49a696be03a7955956ed",820,360,0],["R9","fc38f436091b49a696be03a7955956ed",1090,360,0],
 ["R10","5303080f43d74b41ae76fc5142aa97e5",410,300,0],["R11","5303080f43d74b41ae76fc5142aa97e5",410,230,0],
 ["R12","5303080f43d74b41ae76fc5142aa97e5",680,300,0],["R13","5303080f43d74b41ae76fc5142aa97e5",680,230,0],
 ["D3","a7cd7428f1cf491fa1024dbb27bd014c",500,325,90],["D4","a7cd7428f1cf491fa1024dbb27bd014c",500,255,90],
 ["D5","a7cd7428f1cf491fa1024dbb27bd014c",770,325,90],["D6","a7cd7428f1cf491fa1024dbb27bd014c",770,255,90],
 ["J10","e8a458104842480998ac0d6f045ee70a",600,290,0],["J11","e8a458104842480998ac0d6f045ee70a",870,290,0]
];
const vals={F1:"PTC 0.5A HOLD / 1A TRIP",F2:"PTC 0.5A HOLD / 1A TRIP",FB1:"60R@100MHz / DCR 20mR",FB2:"60R@100MHz / DCR 20mR",D1:"PESD5V0S1BA 5V TVS",D2:"PESD3V3S1BA-ES",D3:"PESD3V3S1BA-ES",D4:"PESD3V3S1BA-ES",D5:"PESD3V3S1BA-ES",D6:"PESD3V3S1BA-ES",C1:"10uF 10V X5R",C2:"47uF 16V X5R",C3:"10uF 10V X5R",C4:"100nF 50V X7R",R1:"33R",R2:"33R",R5:"33R",R6:"100k",R7:"10k",R8:"0R",R9:"0R",R10:"100R",R11:"100R",R12:"100R",R13:"100R",Q1:"2N7002"};
const noBom=new Set(["J2","J3","J4","J5","J6","J7","J8","J9"]);
const before=await eda.sch_PrimitiveComponent.getAll();
const existing=new Set(before.map(c=>c.getState_Designator&&c.getState_Designator()).filter(Boolean));
const orphan=before.filter(c=>["F?","R?"].includes(c.getState_Designator&&c.getState_Designator()));
if(orphan.length) await eda.sch_PrimitiveComponent.delete(orphan);
const placed=[];
for(const [d,u,x,y,r] of parts){
 if(existing.has(d)) continue;
 let c=await eda.sch_PrimitiveComponent.create({libraryUuid:LIB,uuid:u},x,y,undefined,r,false,!noBom.has(d),true);
 if(!c) throw new Error("place "+d);
 const prop={Value:vals[d]||d};
 if(d==="F1"||d==="F2") Object.assign(prop,{LCSC:"C151162",ManufacturerPart:"1206L050/15YR",Package:"1206"});
 c=await eda.sch_PrimitiveComponent.modify(c,{designator:d,uniqueId:"A3_"+d,addIntoBom:!noBom.has(d),otherProperty:prop});
 placed.push(d);
}
return {placed};
