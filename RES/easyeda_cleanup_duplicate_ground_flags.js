await eda.sch_PrimitiveComponent.delete([
  "01f1c51fb3e2f53e",
  "13d11b9c5bba9ae5"
]);

await eda.sch_PrimitiveWire.delete([
  "e1f9ea48b37cb1e7",
  "4c551ed87adfb71a"
]);

await eda.sch_Document.save();

return { ok: true };
