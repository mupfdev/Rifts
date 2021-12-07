@echo off

rem AIFBuilder.bat
rem
rem Copyright (C) Symbian LTD 1999 - 2001.  All rights reserved
rem

if "%1"=="-console" goto guiconsole
if "%1"=="-CONSOLE" goto guiconsole
if "%1"=="-echo" goto guiecho
if "%1"=="-ECHO" goto guiecho
if "%1"=="-generate" goto commandline
if "%1"=="-GENERATE" goto commandline
if "%1"=="-Generate" goto commandline
if "%1"=="-Locale" goto commandline
if "%1"=="-locale" goto commandline
if "%1"=="-LOCALE" goto commandline
if "%1"=="-help" goto help
if "%1"=="-HELP" goto help
if "%1"=="-Help" goto help

:gui
splash aifbuilder\aifbuilder.jar %1 %2 %3 %4
goto end

:guiconsole
splash -console aifbuilder\aifbuilder.jar %2 %3 %4 %5
goto end

:guiecho
splash -echo aifbuilder\aifbuilder.jar %2 %3 %4 %5
goto end

:commandline
start /w splash -noshow -console -cmdline$symbian-AIFBuilder$.bat aifbuilder\aifbuilder.jar %1 %2 %3 %4
call $symbian-AIFBuilder$.bat
if not exist $symbian-AIFBuilder$.bat goto end
del $symbian-AIFBuilder$.bat
goto end

:help
echo AIF Builder (Release 003 - 12/01)
echo.
echo Syntax : aifbuilder (-generate -help aifbuilder_project_file)
echo.

:end
