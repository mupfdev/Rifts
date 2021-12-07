@echo off
echo ALTERING ENVIRONMENT
xcopy /R \epoc32\wins\c\system\data\cdbv2_noras.dat \epoc32\wins\c\system\data\cdbv2.dat
ren  \epoc32\release\wins\udeb\fbusmedia.sav fbusmedia.pmm  2> null
echo commsdb set for using phone/data and fbusmedia.pmm restored
