@echo off
title PCD Exp 8 - Three Address Code - kowshik 108
cd /d "%~dp0"

gcc exp8_three_address_code.c -o exp8
if errorlevel 1 goto :end
exp8.exe < exp8_input.txt

:end
echo.
echo Completed Exp 8.
