@echo off
title PCD Exp 10 - Code Optimization - kowshik 108
cd /d "%~dp0"

gcc exp10_code_optimization.c -o exp10
if errorlevel 1 goto :end
exp10.exe < exp10_input.txt

:end
echo.
echo Completed Exp 10.
