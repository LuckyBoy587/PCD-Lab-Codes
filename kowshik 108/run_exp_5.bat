@echo off
title PCD Exp 5 - Predictive Parser - kowshik 108
cd /d "%~dp0"

gcc exp5_predictive_parser.c -o exp5
if errorlevel 1 goto :end
exp5.exe < exp5_input.txt

:end
echo.
echo Completed Exp 5.
