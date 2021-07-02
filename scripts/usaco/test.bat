@echo off
set filename=%1
set /a numTests=%2+1

set i=1
:loop
copy /y testcases\%i%.in %filename%.in > nul
@REM copy /y testcases\I.%i% %filename%.in > nul
start /b %filename% 2> nul
timeout /t 2 > nul
taskkill /f /im %filename%.exe > nul 2> nul
if not errorlevel 1 (
	echo Test Case %i%: TLE
) else (
	for %%a in (%filename%.out) do if %%~za equ 0 (
		echo Test Case %i%: RE
		goto end
	)
	fc testcases\%i%.out %filename%.out > nul
	@REM fc testcases\O.%i% %filename%.out > nul
	if errorlevel 1 (
		echo Test Case %i%: WA
	) else (
		echo Test Case %i%: AC
	)
)
:end
set /a i += 1
if %i% == %numTests% (
goto :eof
)
goto loop