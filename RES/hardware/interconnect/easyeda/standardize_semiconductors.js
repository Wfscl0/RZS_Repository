// Finalize D1 test replacement and remove its stale pre-standardization copy.
// Other semiconductors are replaced by the CLI one at a time, then normalized
// here so their stable unique IDs survive schematic-to-PCB synchronization.
const stale = await eda.sch_PrimitiveComponent.get(["b632826dd827ed52"]);
if (stale.length) await eda.sch_PrimitiveComponent.delete(stale);

const updates = {
  "5a62f55fd1e23b53": {
    uniqueId: "A2_D1",
    manufacturer: "TECH PUBLIC(台舟)",
    manufacturerId: "PESD5V0S1BA",
    supplier: "LCSC",
    supplierId: "C2827694",
    otherProperty: { Value: "PESD5V0S1BA", Package: "SOD-323", LCSC: "C2827694" }
  }
};

const applied=[];
for (const [id, patch] of Object.entries(updates)) {
  const a=await eda.sch_PrimitiveComponent.get([id]);
  if (!a.length) throw new Error("missing replacement "+id);
  const m=await eda.sch_PrimitiveComponent.modify(a[0],patch);
  applied.push(m.getState_PrimitiveId());
}
return {deleted:stale.length,applied};
