@echo off
title PCD Exp 9 - Backend Codegen - kowshik 108
cd /d "%~dp0"

gcc exp9_backend_codegen.c -o exp9
if errorlevel 1 goto :end
exp9.exe < exp9_input.txt

:end
echo.
echo Completed Exp 9.
