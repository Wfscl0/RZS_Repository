
set MATLAB=D:\21b

cd .

if "%1"=="" ("D:\21b\bin\win64\gmake"  -f VCU10.mk all) else ("D:\21b\bin\win64\gmake"  -f VCU10.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1