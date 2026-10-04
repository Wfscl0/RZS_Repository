await eda.sch_PrimitiveRectangle.delete([
  "a28af751a5f86966",
  "67a2de603cd766c0",
  "0e80b15614ba6075",
  "e85a7db8a80d879e",
  "4d6f2c7dfadcf7b7",
  "ee68141a6fd386e3"
]);

await eda.sch_PrimitiveText.delete([
  "b965c3cb9ff6c0af",
  "6daf69c24d018d4d"
]);

const rectangles = [];

const addSolidFrame = async (x, topY, width, height) => {
  const rect = await eda.sch_PrimitiveRectangle.create(
    x,
    topY,
    width,
    height,
    0,
    0,
    "#404040",
    null,
    1
  );
  rectangles.push(rect.getState_PrimitiveId());
};

await addSolidFrame(35, 800, 120, 420);
await addSolidFrame(220, 800, 245, 420);
await addSolidFrame(470, 800, 580, 305);
await addSolidFrame(470, 480, 180, 270);
await addSolidFrame(660, 480, 230, 298);
await addSolidFrame(35, 360, 420, 230);

const title4 = await eda.sch_PrimitiveText.create(
  480,
  470,
  "4  PROTECTED STATUS OUTPUTS",
  0,
  "#008000",
  null,
  9,
  true
);

const title5 = await eda.sch_PrimitiveText.create(
  670,
  470,
  "5  INPUT BIAS / DEBOUNCE",
  0,
  "#008000",
  null,
  9,
  true
);

await eda.sch_Document.save();

return {
  ok: true,
  rectangles,
  titles: [title4.getState_PrimitiveId(), title5.getState_PrimitiveId()]
};
