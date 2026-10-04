await eda.sch_PrimitiveWire.delete([
  "2c46a562e3b0d50b",
  "08ec0ccac68482fd",
  "83da4fa3f65f25ed",
  "f460c221e3926416",
  "cfe2fe1ea5764fdb",
  "c2756719a8f274c7"
]);

await eda.sch_PrimitiveComponent.delete([
  "6bc28e1bffb92ad6",
  "04c5224aea8cc232",
  "ecfbd3cc5530ca4a",
  "40020944cfc62442",
  "87b2f29d010989f8",
  "cc995f0241ec48bb"
]);

await eda.sch_Document.save();

return { ok: true };
