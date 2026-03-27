@echo off
title PCD Exp 1B-2 - LEX Analyzer - kowshik 108
cd /d "%~dp0"

win_flex exp1b_lexer.l
if errorlevel 1 goto :end
gcc lex.yy.c -o exp1b_lexer
if errorlevel 1 goto :end
exp1b_lexer.exe exp1a_input.c

:end
echo.
echo Completed Exp 1B-2.
