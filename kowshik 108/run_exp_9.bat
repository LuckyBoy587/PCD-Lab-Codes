@title PCD Exp 9 - Backend Codegen - kowshik 108
@cd /d "%~dp0"
@echo on

gcc exp9_backend_codegen.c -o exp9
@if errorlevel 1 goto :end
echo a=b+c*d | exp9.exe

@:end
@echo.
@echo Completed Exp 9.
