const deleted = [
  "2855ffa39a9e72fb",
  "c6b564e46c460e05",
  "e06d97aad4660e69",
  "f8b18bdee95f6b70"
];

await eda.sch_PrimitiveWire.delete(deleted);
await eda.sch_Document.save();

return { ok: true, deleted };
