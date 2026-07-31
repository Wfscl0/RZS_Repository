import { FileBlob, SpreadsheetFile } from "@oai/artifact-tool";

const workbookPath = "D:/git/RZS_Repository/所有板子完整仿真/fin/tsal.xlsx";
const input = await FileBlob.load(workbookPath);
const workbook = await SpreadsheetFile.importXlsx(input);

const overview = await workbook.inspect({
  kind: "workbook,sheet,table,drawing,definedName",
  maxChars: 12000,
  tableMaxRows: 12,
  tableMaxCols: 16,
  tableMaxCellChars: 160,
});

const sheetInfo = await workbook.inspect({
  kind: "sheet",
  include: "id,name",
  maxChars: 4000,
});

console.log("=== OVERVIEW ===");
console.log(overview.ndjson);
console.log("=== SHEETS ===");
console.log(sheetInfo.ndjson);

for (const sheet of workbook.worksheets.items) {
  const used = sheet.getUsedRange();
  if (!used) continue;
  const region = await workbook.inspect({
    kind: "region",
    sheetId: sheet.name,
    range: used.address,
    maxChars: 16000,
    tableMaxRows: 80,
    tableMaxCols: 30,
    tableMaxCellChars: 200,
  });
  console.log(`=== REGION ${sheet.name} ${used.address} ===`);
  console.log(region.ndjson);
}
