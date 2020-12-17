@echo off
set i=1

:loop
gen %i% > test.in
echo %i%
a < test.in > out1.out
b < test.in > out2.out
fc /b out1.out out2.out > nul
if errorlevel 1 (
goto :eof
)
set /a i += 1
goto loop