Option Explicit

Dim CATIA_APP, FSO, sourceDir, outputDir, names, i, sourcePath, outputPath, doc

Set FSO = CreateObject("Scripting.FileSystemObject")
sourceDir = "C:\Users\icemi\Desktop\PART\PART"
outputDir = FSO.GetParentFolderName(WScript.ScriptFullName) & "\module_inspection_20260728"
If Not FSO.FolderExists(outputDir) Then FSO.CreateFolder outputDir

On Error Resume Next
Set CATIA_APP = GetObject(, "CATIA.Application")
If Err.Number <> 0 Or CATIA_APP Is Nothing Then
  WScript.Echo "ERROR: CATIA.Application is not available."
  WScript.Quit 1
End If
On Error GoTo 0

names = Array("DCDC", "INA226", "LORA", "Relay_2", "Relay_4", "STM32G0B1CBT6")

For i = 0 To UBound(names)
  sourcePath = sourceDir & "\" & names(i) & ".CATPart"
  outputPath = outputDir & "\" & names(i) & ".stl"
  If FSO.FileExists(outputPath) Then FSO.DeleteFile outputPath, True
  Set doc = CATIA_APP.Documents.Open(sourcePath)
  doc.ExportData outputPath, "stl"
  doc.Close
  WScript.Echo "EXPORTED " & names(i)
Next

WScript.Echo "DONE " & outputDir
