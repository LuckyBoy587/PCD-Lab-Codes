@echo off
title PCD Exp 1A - C Lexical Analyzer - kowshik 108
cd /d "%~dp0"

gcc exp1a_lexical_analyzer.c -o exp1a
if errorlevel 1 goto :end
exp1a.exe

:end
echo.
echo Completed Exp 1A.
