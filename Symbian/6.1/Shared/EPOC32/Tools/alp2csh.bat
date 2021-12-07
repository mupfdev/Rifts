@echo off

perl -S alp2csh.pl %1 %2 %3 %4 %5 %6 %7 %8 %9
if errorlevel==1 goto CheckPerl
goto End

:CheckPerl
perl -v >NUL
if errorlevel==1 echo Is Perl, version 5.005_03 or later, installed?
goto End

:End
@echo on