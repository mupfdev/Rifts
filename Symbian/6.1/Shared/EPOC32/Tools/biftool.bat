@echo off

rem *********************************************************************************
rem   biftool.bat
rem 
rem   %1 is filename of resource file without extension
rem   %2 is filename of multi-bitmap file with extension 
rem   %3 is command parameter for biftool (should be blank or /v)
rem *********************************************************************************

echo Bio-Message Information File (BIF) tool - Unicode build
echo Copyright (C) Symbian 1999
echo.

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

echo Compiling resource file
perl -S epocrc.pl -u -I. -I%EPOCROOT%epoc32\include %1.RSS -o%_tempdir%\bif.rsc
if errorlevel==1 goto terminated

echo Copying mbm
copy %2 %_tempdir%\bif.mbm
if errorlevel==1 goto terminated

echo Running BIF writer
if NOT exist \epoc32\release\winc\udeb\biftool.exe goto noexe
call %EPOCROOT%epoc32\release\winc\udeb\biftool.exe %_tempdir%\ %3
copy %_tempdir%\out.bif %1.bif

goto end

:help

echo BIFTOOL rscname mbmname [/v]
echo.
echo rscname: the name of the input resource file; the
echo          .rss extension is added by biftool
echo mbmname: the name of the input .mbm file; you
echo          must specify the extension
echo /v:      run tool in verbose mode
echo.
echo Use this command to produce a BIF from;
echo  - a resource file containing language, description and UID
echo  - a multi-bitmap file containing icons for various zoom states
goto finalend

:noexe
echo Error: \epoc32\release\winc\udeb\biftool.exe not found.

:terminated
echo Error: conversion terminated :-(

:end
echo Cleaning up
erase %_tempdir%\out.bif
erase %_tempdir%\bif.rsc
erase %_tempdir%\bif.mbm

:finalend
set _tempdir=
