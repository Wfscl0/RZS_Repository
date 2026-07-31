import { FileBlob, SpreadsheetFile } from "@oai/artifact-tool";

const files = [
  "C:/Users/icemi/Desktop/VCU_SW/方程式/方程式/NXPS32K_引脚分配(1).xlsx",
  "C:/Users/icemi/Desktop/RZS_Repository/基板/基板全部接口特性与定义_2026-07-20_v6.xlsx",
];

for (const file of files) {
  const blob = await FileBlob.load(file);
  const workbook = await SpreadsheetFile.importXlsx(blob);
  console.log(`\n=== ${file} ===`);
  console.log((await workbook.inspect({
    kind: "workbook,sheet,table",
    include: "id,name,values,formulas",
    maxChars: 8000,
    tableMaxRows: 8,
    tableMaxCols: 12,
    tableMaxCellChars: 100,
  })).ndjson);
  console.log((await workbook.inspect({
    kind: "match",
    searchTerm: "AIN0|AIN1|AIN2|AIN4|AIN5|OUT5|HO1|EBS|RES|R2D|PWM1|PA30|CAN0|CAN1",
    options: { useRegex: true, maxResults: 300 },
    summary: "VCU IO and CAN mapping matches",
    maxChars: 30000,
  })).ndjson);
}
