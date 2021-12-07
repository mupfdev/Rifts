@echo off
rem cnftool.bat
echo CNF tool
echo Copyright (C) Symbian Ltd 1999-2001

if "%1"=="" goto help
if "%1"=="/?" goto help
if "%1"=="/h" goto help
if "%1"=="/H" goto help

if "%temp%"=="" goto notemp1
if not exist %temp%\nul goto notemp1
set _tempdir=\epoc32\wins\c\cnftool\
goto gottemp
:notemp1

if "%tmp%"=="" goto notemp2
if not exist %tmp%\nul goto notemp2
set _tempdir=\epoc32\wins\c\cnftool\
goto gottemp
:notemp2

set _tempdir=\epoc32\wins\c\cnftool\

:gottemp

echo Compiling resource file
cpp -I\. -I..\inc -I..\..\epoc32\include < %1.RSS > %1.RPP
rcomp -u -ocnf.Rsc -h%1.rs~ -i%1.RSS -s%1.RPP
if errorlevel==1 goto terminated
if not exist \epoc32\wins\c\cnftool\nul md \epoc32\wins\c\cnftool
copy cnf.rsc %_tempdir%\cnf.rsc
del %1.rs~
del %1.rpp
del cnf.rsc

echo Running CNF writer
call \epoc32\release\wins\udeb\cnftool.exe %_tempdir%\
copy %_tempdir%\out.cnf %1.cnf

goto end

:help

echo.
echo CNFTOOL filename
echo Use this command to produce an CNF from
echo a resource file
goto finalend

:terminated
echo Error: conversion terminated :-(

:end
erase %_tempdir%\cnf.rsc
erase %_tempdir%\out.cnf

:finalend
set _tempdir=
