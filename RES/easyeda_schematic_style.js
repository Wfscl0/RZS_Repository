const deleted = [
  "bd0e6843d233b86b",
  "a236d215a57cc160",
  "7e5a335142228f91",
  "90d5eb7e747029b5",
  "c75c951bcc6d663d"
];

await eda.sch_PrimitiveWire.delete(deleted);

const rectangles = [];
const titles = [];

const addFrame = async (x, topY, width, height, title) => {
  const rect = await eda.sch_PrimitiveRectangle.create(
    x,
    topY,
    width,
    height,
    0,
    0,
    "#404040",
    null,
    1,
    1
  );
  rectangles.push(rect.getState_PrimitiveId());

  const text = await eda.sch_PrimitiveText.create(
    x + 10,
    topY - 10,
    title,
    0,
    "#008000",
    null,
    9,
    true
  );
  titles.push(text.getState_PrimitiveId());
};

await addFrame(35, 800, 120, 420, "1  EXTERNAL SCREW TERMINALS");
await addFrame(220, 800, 245, 420, "2  STM32G0B1 MODULE INTERFACE");
await addFrame(470, 800, 580, 300, "3  E220 RADIO INTERFACE");
await addFrame(470, 490, 180, 280, "4  PROTECTED STATUS OUTPUTS");
await addFrame(660, 490, 230, 330, "5  INPUT BIAS / DEBOUNCE");
await addFrame(35, 360, 420, 230, "6  POWER PROTECTION / FILTER");

await eda.sch_Document.save();

return {
  ok: true,
  deleted,
  rectangles,
  titles
};
