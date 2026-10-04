await eda.sch_PrimitiveComponent.delete([
  "d0c67964be7ece3b",
  "63a603ddc44c228e",
  "4731a3313944f174"
]);

await eda.sch_PrimitiveText.delete([
  "432e137ec0fcd8fe"
]);

const title4 = await eda.sch_PrimitiveText.create(
  500,
  470,
  "4  STATUS OUTPUT PROTECTION",
  0,
  "#008000",
  null,
  9,
  true
);

await eda.sch_Document.save();

return { ok: true, title4: title4.getState_PrimitiveId() };
