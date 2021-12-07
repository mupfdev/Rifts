@echo off
rem Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.

if "%1"=="-console" goto console
if "%1"=="-CONSOLE" goto console
if "%1"=="-echo" goto echo
if "%1"=="-ECHO" goto echo
if "%1"=="-build" goto commandline
if "%1"=="-BUILD" goto commandline
if "%1"=="-help" goto help
if "%1"=="-HELP" goto help
if "%1"=="?" goto help
if "%1"=="-?" goto help

:gui
splash menubuilder\menubuilder.jar %1
goto end

:console
splash -console menubuilder\menubuilder.jar %2
goto end

:echo
splash -echo menubuilder\menubuilder.jar %2
goto end

:commandline
start /w splash -noshow -console -cmdline$SYMBIAN-menubuilder$.bat menubuilder\menubuilder.jar %1 %2
call $SYMBIAN-menubuilder$.bat
if not exist $SYMBIAN-menubuilder$.bat goto end
del $SYMBIAN-menubuilder$.bat
goto end

:help
echo Menu Builder
echo Syntax :       menubuilder [-help] [menubuilder.mbld] [-build menubuilder.mbld] 
echo (no options)   Launch menubuilder GUI, opening a menubuilder.mbld menu
echo                definition file if specified.
echo -build         Build source and resource files from a specified menubuilder.mbld
echo                definition file.
echo -help          Output this help message.
echo.

:end
