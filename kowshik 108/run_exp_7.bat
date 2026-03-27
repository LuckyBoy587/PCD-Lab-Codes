@title PCD Exp 7 - SLR Parser - kowshik 108
@cd /d "%~dp0"
@echo on

gcc exp7_slr_parser.c -o exp7
@if errorlevel 1 goto :end
exp7.exe < exp7_input.txt

@:end
@echo.
@echo Completed Exp 7.
