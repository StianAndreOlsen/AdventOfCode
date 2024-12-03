@echo off
title %~n0
set clean=%SAO_Source%\Tools\Scripts\Clean.sub.bat

echo Current directory is "%cd%"
call "%clean%" app Day1
call "%clean%" app Day2
call "%clean%" app Day3
call "%clean%" app Day4

if not "%~1"=="continue" pause
