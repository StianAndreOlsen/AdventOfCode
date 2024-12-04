@echo off
title %~n0
set clean=%SAO_Source%\Tools\Scripts\Clean.sub.bat

echo Current directory is "%cd%"
call "%clean%" subdirs 2024 AdventOfCode2024

if not "%~1"=="continue" pause
