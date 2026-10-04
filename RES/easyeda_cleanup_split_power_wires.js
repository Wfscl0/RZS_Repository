await eda.sch_PrimitiveWire.delete([
  "c02e4fef3ec4029f",
  "2df3d73f849b4ba4",
  "69ef84adeb10d12f",
  "6a924037e1d67de7",
  "ed136ff9a147c7cf",
  "4742dbc2176a94fc",
  "48f15f525ff838c6"
]);

await eda.sch_Document.save();

return { ok: true };
