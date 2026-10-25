$ErrorActionPreference='Stop'
$taskRoot='D:\git\RZS_Repository'
$taskOut=Join-Path $taskRoot '设计报告\答辩准备_20261016\_work\excel_render'
New-Item -ItemType Directory -Path $taskOut -Force | Out-Null
$taskJobs=@(
 @{file='低压盒\硬件电路接口.xlsx';sheet='接口表';area='A14:J25';name='低压盒_EBS与锁存'},
 @{file='低压盒\硬件电路接口.xlsx';sheet='接口表';area='A29:J36';name='低压盒_继电器位号'},
 @{file='低压盒\硬件电路接口.xlsx';sheet='校核清单';area='A4:F17';name='低压盒_校核清单'},
 @{file='基板\基板全部接口特性与定义_2026-07-31_v7.xlsx';sheet='总览';area='A1:H16';name='基板_总览'},
 @{file='基板\基板全部接口特性与定义_2026-07-31_v7.xlsx';sheet='外部接口CN7-CN12';area='A14:M18';name='基板_ROTATE'},
 @{file='基板\基板全部接口特性与定义_2026-07-31_v7.xlsx';sheet='外部接口CN7-CN12';area='A65:M76';name='基板_EBS与RES'},
 @{file='基板\基板全部接口特性与定义_2026-07-31_v7.xlsx';sheet='待确认与测试';area='A4:G18';name='基板_校核清单'}
)
$taskExcel=New-Object -ComObject Excel.Application
$taskExcel.Visible=$false;$taskExcel.DisplayAlerts=$false
try{
 foreach($taskJob in $taskJobs){
  $taskBook=$taskExcel.Workbooks.Open((Join-Path $taskRoot $taskJob.file),0,$true)
  try{
   $taskSheet=$taskBook.Worksheets.Item($taskJob.sheet)
   $taskSheet.PageSetup.PrintArea=$taskJob.area
   $taskSheet.PageSetup.Orientation=2
   $taskSheet.PageSetup.PaperSize=8
   $taskSheet.PageSetup.Zoom=$false
   $taskSheet.PageSetup.FitToPagesWide=1
   $taskSheet.PageSetup.FitToPagesTall=1
   $taskSheet.ExportAsFixedFormat(0,(Join-Path $taskOut ($taskJob.name+'.pdf')))
   Write-Output $taskJob.name
  }finally{$taskBook.Close($false)}
 }
}finally{$taskExcel.Quit()}
