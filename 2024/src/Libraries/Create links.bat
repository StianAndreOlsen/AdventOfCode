@echo off

rem Create directory junction points instead of symbolic links (works better with qmake)
mklink /j Sao           "%SAO_Source%\Libraries\src\Sao"
mklink /j SaoExpression "%SAO_Source%\Libraries\src\SaoExpression"
mklink /j SaoWin        "%SAO_Source%\Libraries\src\SaoWin"

pause
