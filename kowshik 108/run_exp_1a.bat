@title PCD Exp 1A - C Lexical Analyzer - kowshik 108
@cd /d "%~dp0"
@echo on

gcc exp1a_lexical_analyzer.c -o exp1a
@if errorlevel 1 goto :end
echo int main() { int a=10, b=25; float z=a+b; return 0; } | exp1a.exe


@:end
@echo.
@echo Completed Exp 1A.
