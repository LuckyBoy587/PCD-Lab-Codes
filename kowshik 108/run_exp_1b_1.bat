@title PCD Exp 1B-1 - LEX Count - kowshik 108
@cd /d "%~dp0"
@echo on

win_flex exp1b_count.l
@if errorlevel 1 goto :end
gcc lex.yy.c -o exp1b_count
@if errorlevel 1 goto :end
exp1b_count.exe exp1b_input.txt

@:end
@echo.
@echo Completed Exp 1B-1.
