@echo off
REM CORE.CMD ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
REM COmpile REsource.  Bare(ish) metal framework to do test resource compiles.
REM First released with RCOMP 313.
REM Version released with 314 uses a different command syntax.
REM
REM Some of the functionality of this command procedure should ultimately
REM appear in the RCOMP command itself.
REM
REM The first parameter is the name of the resource source file (without
REM the .RSS extension).  Output is a generated header file (.RSG) in the same
REM directory as the source file and a resource object file (.RSC) which
REM would normally be placed in the object file directory of any component
REM build.
REM
REM The optional second parameter specifies the target directory and the
REM optional third parameter is qualifiers to pass to RCOMP.
REM
REM The generated header file is only produced if its contents are different
REM to the pre-existing one that may be present. This is to try and minimise
REM on the work done in component rebuilds.
REM
REM ---------------------------------------------------------------------------
if %1.==. goto Usage
SETLOCAL

SET _source_name=%1
SET _intermediate_source=%_source_name%.RSS_Intermediate
SET _target_dir=%2
IF "%_target_dir%"=="" SET _target_dir=.
SET _target=%_target_dir%\%1.RSC

REM Before starting, erase the target file to prevent any
REM source errors being overlooked in a component build.
REM
IF EXIST %_target% ERASE %_target%

REM analyse options

:options

IF "%3" == "" GOTO run

SET _option=%3
IF "%_option%" == "/UNICODE" GOTO set_unicode
IF "%_option%" == "/unicode" GOTO set_unicode

IF "%_option%" == "/DEFINE" GOTO set_defines
IF "%_option%" == "/define" GOTO set_defines

IF "%_option%" == "/VERBOSE" GOTO set_verbose
IF "%_option%" == "/verbose" GOTO set_verbose

ECHO Unrecognised option -%_option%- - continuing anyway...
GOTO next_option

:set_defines
IF "%4" == "" GOTO run
SET _cpp_option=%_cpp_option% -D%4
SHIFT /4
GOTO set_defines

:set_unicode
SET _rcomp_option=-u
GOTO next_option

:set_verbose
SET _verbose_option=-v
GOTO next_option

:next_option
SHIFT /3
GOTO options

:run

REM
REM The preprocessor currently has to be called externally to the
REM resource compiler.  Note that there is currently an explicit
REM include path defined here.
REM
ECHO Calling preprocessor...
cpp %_cpp_option% -I..\inc -I..\..\epoc32\include < %_source_name%.RSS > %_intermediate_source%

REM Tidy up if the preprocessor step failed.

IF errorlevel==1 GOTO prep_fail



REM
REM Call the actual resource compiler with the intermediate source.
REM

SET _intermediate_g=%_source_name%.RSG_Intermediate
SET _final_g=%_source_name%.RSG


ECHO Calling RCOMP...
rcomp   %_rcomp_option% %_verbose_option% -o%_target% -h%_intermediate_g% -i%_source_name%.RSS -s%_intermediate_source%

IF errorlevel==1 GOTO rcomp_fail

REM
REM RCOMP complete.  Now update the generated header, only if it has changed.

ERASE %_intermediate_source%

FC4BAT %_intermediate_g% %_final_g%

IF errorlevel==1 GOTO gcopy
GOTO nogcopy

:gcopy
ECHO Updating generated header file...
copy %_intermediate_g% %_final_g%

:nogcopy
ERASE %_intermediate_g%

GOTO end


:Usage
echo COmpile REsource
echo Usage: CORE filename [object_directory [options]]
echo e.g.   CORE tsig
ECHO Options may be /UNICODE to generate Unicode text resources
ECHO or /DEFINE thing...
ECHO to provide preprocessor definitions
GOTO End


:prep_fail
REM Come here if preprocessor step failed

ECHO Preprocessor step failed...
IF EXIST %_intermediate_source% ERASE %_intermediate_source%
GOTO end


:rcomp_fail
REM Come here if RCOMP step failed.  We ensure that there is no
REM partial object file left dangling, but we leave the intermediate
REM source file which may be needed for diagnostic purposes.

ECHO RCOMP step failed. (%_intermediate_source% left for diagnosis).

IF EXIST %_target% ERASE %_target%
IF EXIST %_intermediate_g% ERASE %_intermediate_g%

GOTO end



:End
ENDLOCAL

REM end of CORE.CMD
