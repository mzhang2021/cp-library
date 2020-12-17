@echo off
set i=1

:loop
gen %i% > test.in
echo %i%
a < test.in > a.out
b < test.in > b.out
fc /b a.out b.out > nul
if errorlevel 1 (
goto :eof
)
set /a i += 1
goto loop