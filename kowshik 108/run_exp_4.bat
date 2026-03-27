@echo off
title PCD Exp 4 - Symbol Table - kowshik 108
cd /d "%~dp0"

gcc exp4_symbol_table.c -o exp4
if errorlevel 1 goto :end
exp4.exe

:end
echo.
echo Completed Exp 4.
