@title PCD Exp 3-2 - Expression Parser - kowshik 108
@cd /d "%~dp0"
@echo on

win_bison -dy exp3_parser2.y
@if errorlevel 1 goto :end
win_flex exp3_parser2.l
@if errorlevel 1 goto :end
gcc y.tab.c lex.yy.c -o exp3_p2
@if errorlevel 1 goto :end
echo a+b*4 | exp3_p2.exe

@:end
@echo.
@echo Input used: a+b*4
@echo Completed Exp 3-2.
