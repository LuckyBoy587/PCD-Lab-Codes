@echo off
setlocal

set "BASE=%~dp0"
set "DELAY_MS=25"
echo Launching experiment windows from: %BASE%
echo Inter-launch delay: %DELAY_MS% ms
echo.

start "PCD Exp 10 - Code Optimization - kowshik 108" cmd.exe /k "%BASE%run_exp_10.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 9 - Backend Codegen - kowshik 108" cmd.exe /k "%BASE%run_exp_9.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 8 - Three Address Code - kowshik 108" cmd.exe /k "%BASE%run_exp_8.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 7 - SLR Parser - kowshik 108" cmd.exe /k "%BASE%run_exp_7.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 6 - Shift Reduce Parser - kowshik 108" cmd.exe /k "%BASE%run_exp_6.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 5 - Predictive Parser - kowshik 108" cmd.exe /k "%BASE%run_exp_5.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 4 - Symbol Table - kowshik 108" cmd.exe /k "%BASE%run_exp_4.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 3-2 - Expression Parser - kowshik 108" cmd.exe /k "%BASE%run_exp_3_2.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 3-1 - Parser Statements - kowshik 108" cmd.exe /k "%BASE%run_exp_3_1.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 2 - LEX+YACC Calculator - kowshik 108" cmd.exe /k "%BASE%run_exp_2.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 1B-2 - LEX Analyzer - kowshik 108" cmd.exe /k "%BASE%run_exp_1b_2.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 1B-1 - LEX Count - kowshik 108" cmd.exe /k "%BASE%run_exp_1b_1.bat"
powershell -NoProfile -Command "Start-Sleep -Milliseconds %DELAY_MS%" > nul

start "PCD Exp 1A - C Lexical Analyzer - kowshik 108" cmd.exe /k "%BASE%run_exp_1a.bat"

echo All experiment windows launched.
endlocal