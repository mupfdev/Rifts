@echo off
rem aiftoolu.bat
echo AIF tool - Unicode build
echo Copyright (C) Symbian 2000

if "%EPOCROOT%"=="" goto badroot
if not exist %EPOCROOT%nul goto badroot2

if "%1"=="" goto help
if "%1"=="/?" goto help
if "%1"=="/h" goto help
if "%1"=="/H" goto help

if "%temp%"=="" goto notemp1
if not exist %temp%\nul goto notemp1
set _tempdir=%temp%
goto gottemp
:notemp1

if "%tmp%"=="" goto notemp2
if not exist %tmp%\nul goto notemp2
set _tempdir=%tmp%
goto gottemp
:notemp2

set _tempdir=C:

:gottemp

echo Compiling AIF file
perl -S epocaif.pl -t%_tempdir% -I. -I%EPOCROOT%epoc32\include %1.RSS -m%2 -o%1.aif
if errorlevel==1 goto terminated

goto end

:help

echo.
echo AIFTOOL filename mbmname
echo Use this command to produce an AIF from
echo -	a resource file containing language, caption
echo 	and capability specifications
echo -	a multi-bitmap file containing icons and masks
echo 	in various sizes
echo Specify
echo	filename: the name of the input resource file; the
echo		.rss extension is added by AIFTOOL
echo	mbmname: the name of the input .mbm file: you
echo		must specify the extension
goto end

:badroot
echo You must set the EPOCROOT variable before running aiftool
goto end
:badroot2
echo The EPOCROOT environment variable must refer to an existing directory
goto end

:terminated
echo Error: conversion terminated :-(

:end
set _tempdir=
