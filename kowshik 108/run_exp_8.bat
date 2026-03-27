@title PCD Exp 8 - Three Address Code - kowshik 108
@cd /d "%~dp0"
@echo on

gcc exp8_three_address_code.c -o exp8
@if errorlevel 1 goto :end
echo a=b+c/d | exp8.exe

@:end
@echo.
@echo Completed Exp 8.
