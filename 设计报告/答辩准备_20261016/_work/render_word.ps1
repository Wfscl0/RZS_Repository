$ErrorActionPreference='Stop'
$taskRoot='D:\git\RZS_Repository'
$taskOutput=Join-Path $taskRoot '设计报告\答辩准备_20261016\_work\word_render'
New-Item -ItemType Directory -Path $taskOutput -Force | Out-Null
$taskFiles=@(
'设计报告\答辩准备_20261016\RZS整车电气系统答辩准备材料.docx',
'继电器检测\继电器检测说明.docx',
'EBS\EBS功能说明（2026）.docx',
'与其他组\硬件电路和整车控制有交集的地方.docx',
'VCU\方程式\方程式\FSAC测试台架说明.docx',
'设计报告\设计报告.docx'
)
$taskWord=New-Object -ComObject Word.Application
$taskWord.Visible=$false
$taskWord.DisplayAlerts=0
$taskReports=@()
try {
 foreach($taskFile in $taskFiles){
  $taskDoc=$null
  try{
   $taskPath=Join-Path $taskRoot $taskFile
   $taskDoc=$taskWord.Documents.Open($taskPath,$false,$false)
   $taskDoc.Fields.Update() | Out-Null
   $taskDoc.Repaginate()
   $taskPdf=Join-Path $taskOutput (([IO.Path]::GetFileNameWithoutExtension($taskFile))+'.pdf')
   $taskDoc.ExportAsFixedFormat($taskPdf,17)
   $taskReports+=@{source=$taskFile;pdf=$taskPdf;pages=$taskDoc.ComputeStatistics(2)}
   $taskDoc.Close(0)
  } catch { if($taskDoc){$taskDoc.Close(0)}; throw }
 }
}finally{$taskWord.Quit()}
$taskReports | ConvertTo-Json -Depth 4 | Set-Content -LiteralPath (Join-Path $taskOutput 'render_manifest.json') -Encoding UTF8
$taskReports | ConvertTo-Json -Depth 4
