
set MATLAB=D:\matlab

cd .

if "%1"=="" ("D:\matlab\bin\win64\gmake"  -f rzs10thnew2021b.mk all) else ("D:\matlab\bin\win64\gmake"  -f rzs10thnew2021b.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1