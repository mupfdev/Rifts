@echo off
echo ALTERING ENVIRONMENT
xcopy /R \epoc32\wins\c\system\data\cdbv2_ras.dat \epoc32\wins\c\system\data\cdbv2.dat
ren  \epoc32\release\wins\udeb\fbusmedia.pmm fbusmedia.sav
echo commsdb set for using NT RAS and fbusmedia.pmm renamed
