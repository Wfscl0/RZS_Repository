import { FileBlob, SpreadsheetFile } from "@oai/artifact-tool";

const inputs = [
  "C:/Users/icemi/Desktop/VCU_SW/方程式/方程式/NXPS32K_引脚分配(1).xlsx",
  "C:/Users/icemi/Desktop/RZS_Repository/基板/基板全部接口特性与定义_2026-07-20_v6.xlsx",
];

for (const path of inputs) {
  const blob = await FileBlob.load(path);
  const workbook = await SpreadsheetFile.importXlsx(blob);
  console.log(`WORKBOOK ${path}`);
  const sheets = await workbook.inspect({ kind: "sheet", include: "id,name", maxChars: 8000 });
  console.log(sheets.ndjson);
  if (path.includes("NXPS32K")) {
    console.log((await workbook.inspect({ kind: "table", sheetId: "VCU接插件示意图", range: "A76:G88", include: "values,formulas", tableMaxRows: 20, tableMaxCols: 10, maxChars: 12000 })).ndjson);
    console.log((await workbook.inspect({ kind: "table", sheetId: "引脚分配图", range: "A36:I49", include: "values,formulas", tableMaxRows: 20, tableMaxCols: 12, maxChars: 12000 })).ndjson);
  }
  for (const term of ["CAN", "CAN0", "CAN_H", "CAN_L", "CANH", "CANL", "PTE4", "PTE5", "电机"]) {
    const result = await workbook.inspect({
      kind: "match",
      searchTerm: term,
      options: { useRegex: false, maxResults: 80 },
      maxChars: 12000,
      summary: `find ${term}`,
    });
    if (result.ndjson && !result.ndjson.includes('"count":0')) {
      console.log(`MATCH ${term}`);
      console.log(result.ndjson);
    }
  }
}
