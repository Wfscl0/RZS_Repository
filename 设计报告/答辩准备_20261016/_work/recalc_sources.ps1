$ErrorActionPreference='Stop'
$taskExcel=New-Object -ComObject Excel.Application
$taskExcel.Visible=$false;$taskExcel.DisplayAlerts=$false
try{
 foreach($taskFile in @('D:\git\RZS_Repository\低压盒\硬件电路接口.xlsx','D:\git\RZS_Repository\基板\基板全部接口特性与定义_2026-07-31_v7.xlsx')){
  $taskBook=$taskExcel.Workbooks.Open($taskFile)
  try{$taskExcel.CalculateFullRebuild();$taskBook.Save()}finally{$taskBook.Close($false)}
 }
}finally{$taskExcel.Quit()}
Write-Output 'Recalculated and saved both corrected source workbooks'
