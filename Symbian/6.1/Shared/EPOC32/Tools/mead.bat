@echo off
rem Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.

if "%1"=="-console" goto console
if "%1"=="-CONSOLE" goto console
if "%1"=="-echo" goto echo
if "%1"=="-ECHO" goto echo

call splash mead\mead.jar
goto end

:console
splash -console mead\mead.jar
goto end

:echo
splash -echo mead\mead.jar

:end
