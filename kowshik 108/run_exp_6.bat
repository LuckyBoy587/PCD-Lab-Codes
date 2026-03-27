@echo off
title PCD Exp 6 - Shift Reduce Parser - kowshik 108
cd /d "%~dp0"

gcc exp6_shift_reduce_parser.c -o exp6
if errorlevel 1 goto :end
exp6.exe < exp6_input.txt

:end
echo.
echo Completed Exp 6.
