@title PCD Exp 2 - LEX+YACC Calculator - kowshik 108
@cd /d "%~dp0"
@echo on

win_bison -dy exp2_calc.y
@if errorlevel 1 goto :end
win_flex exp2_calc.l
@if errorlevel 1 goto :end
gcc y.tab.c lex.yy.c -o exp2
@if errorlevel 1 goto :end
echo (10+20)*3-5 | exp2.exe


@:end
@echo.
@echo Input used: (10+20)*3-5
@echo Completed Exp 2.
