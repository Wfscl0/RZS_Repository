const oldNamedWires = [
  "c3445d095ed4f825",
  "c2116965a7f54096",
  "f88096863149d152",
  "2e20b783af74c374",
  "cd37d64016740d27",
  "4f8ab8650af8f636",
  "2aad3dabae81f7d0",
  "4c033b7f8cd9e8e7",
  "4c80f5d4949c894d",
  "456695fd6fd9630a",
  "44c09cbad5a4d40b",
  "8528f5c83ca3cbfe",
  "9172f0403ef8a305"
];

await eda.sch_PrimitiveWire.delete(oldNamedWires);

const wires = [];
const addWire = async (points) => {
  const wire = await eda.sch_PrimitiveWire.create(
    points,
    undefined,
    null,
    null,
    null
  );
  wires.push(wire.getState_PrimitiveId());
};

// H1 5 V pins join above the module and touch the existing +5V_MCU flag.
await addWire([321, 763, 321, 783, 381, 783, 381, 763]);

// Power protection joints are explicit physical wires, not overlapping stubs.
await addWire([220, 330, 235, 330]);
await addWire([260, 330, 274, 330]);
await addWire([265, 323, 265, 330]);
await addWire([265, 330, 265, 342]);

// Local ground and radio rail links use nearby existing/new flags.
await addWire([330, 234, 350, 234]);
await addWire([330, 198, 350, 198]);
await addWire([219, 199, 239, 199]);
await addWire([291, 163, 280.5, 163, 280.5, 164.5]);

// Reset and mode-strapping grounds use clear orthogonal channels.
await addWire([554, 621, 587, 621, 587, 643]);
await addWire([587, 621, 587, 600]);
await addWire([693, 636, 715, 636, 715, 652, 705, 652]);
await addWire([715, 636, 735, 636, 735, 655, 706, 655]);

await eda.sch_Document.save();

return { ok: true, deleted: oldNamedWires, wires };
