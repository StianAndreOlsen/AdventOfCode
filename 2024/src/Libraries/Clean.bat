@echo off
title %~n0
set clean=%SAO_Source%\Tools\Scripts\Clean.sub.bat

echo Current directory is "%cd%"
call "%clean%" lib Sao
call "%clean%" lib SaoExpression
call "%clean%" lib SaoWin

if not "%~1"=="continue" pause
