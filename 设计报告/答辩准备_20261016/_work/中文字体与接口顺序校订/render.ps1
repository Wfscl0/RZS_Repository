$ErrorActionPreference='Stop'
$taskPath='D:\git\RZS_Repository\设计报告\答辩准备_20261016\RZS整车电气系统答辩准备材料.docx'
$taskPdf='D:\git\RZS_Repository\设计报告\答辩准备_20261016\_work\中文字体与接口顺序校订\preview.pdf'
$taskWord=New-Object -ComObject Word.Application
$taskWord.Visible=$false
$taskWord.DisplayAlerts=0
try{
 $taskDoc=$taskWord.Documents.Open($taskPath,$false,$true)
 try{
  $taskDoc.Fields.Update() | Out-Null
  $taskDoc.Repaginate()
  $taskDoc.ExportAsFixedFormat($taskPdf,17)
  Write-Output ('Pages: '+$taskDoc.ComputeStatistics(2))
 }finally{$taskDoc.Close(0)}
}finally{$taskWord.Quit()}
