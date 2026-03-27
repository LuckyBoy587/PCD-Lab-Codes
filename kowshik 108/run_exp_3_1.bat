@echo off
title PCD Exp 3-1 - Parser Statements - kowshik 108
cd /d "%~dp0"

win_bison -dy exp3_parser1.y
if errorlevel 1 goto :end
win_flex exp3_parser1.l
if errorlevel 1 goto :end
gcc y.tab.c lex.yy.c -o exp3_p1
if errorlevel 1 goto :end
type exp3_p1_input.txt | exp3_p1.exe

:end
echo.
echo Input used: (a,12,(x,3))
echo Completed Exp 3-1.
