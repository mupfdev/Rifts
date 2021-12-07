// DriveInfo.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#include <f32file.h>
#include "CommonFramework.h"
	

LOCAL_D RFs fsSession;

// example functions
void PrintDriveVolInfo();

// utility functions
void FormatDriveInfo(TDes& aBuffer, const TDriveInfo aDriveInfo);
void FormatVolumeInfo(TDes& aBuffer, const TVolumeInfo aVolumeInfo);

void WaitForKey()
	{
	_LIT(KMessage,"Press any key to continue\n\n");
	console->Printf(KMessage);
	console->Getch();
	}

// do the example
LOCAL_C void doExampleL()
    {
	// Connect to file server
	User::LeaveIfError(fsSession.Connect()); // Start session
	PrintDriveVolInfo();
	fsSession.Close(); // close file server session
	}

void PrintDriveVolInfo()
	{
	_LIT(KMessage,"PrintDriveVolInfo()\n");
	_LIT(KValidDriveMsg,"Valid drives as characters (and as numbers) are:\n");
	_LIT(KDriveChar,"%c");
	_LIT(KDriveNum,"(%d) ");
	_LIT(KNewLine,"\n");
	_LIT(KAvailDriveMsg,"Using DriveList(), available drives are: ");
	_LIT(KDriveAtts,"%c: %02x ");
	_LIT(KDriveInfo,"Drive information for %c: drive is:\n%S");
	_LIT(KVolInfo,"Volume information for %c: is:\n%S");

	console->Printf(KMessage);

	// Print the valid drives as characters and as numbers. 
	// Then print the drive list (list of available drives), and
	// information about each drive in the list using Drive(). 
	// Finally, print volume information.

	console->Printf(KValidDriveMsg);

	TInt driveNumber=EDriveA; 
	TChar driveLetter; 
	for (; driveNumber<=EDriveZ; driveNumber++)
		{
		if (fsSession.IsValidDrive(driveNumber))
			{
			fsSession.DriveToChar(driveNumber,driveLetter);
			console->Printf(KDriveChar,TUint(driveLetter));
			fsSession.CharToDrive(driveLetter, driveNumber);
			console->Printf(KDriveNum,driveNumber);
			}
		}
	console->Printf(KNewLine);

	TDriveList drivelist; 
	User::LeaveIfError(fsSession.DriveList(drivelist));
	// A TDriveList (the list of available drives), is an array of 
	// 26 bytes. Each byte with a non zero value signifies that the 
	// corresponding drive is available.

	console->Printf(KAvailDriveMsg);
	for (driveNumber=EDriveA; driveNumber<=EDriveZ;driveNumber++)
		{
		if (drivelist[driveNumber]) // if drive-list entry non-zero, drive is available
			{
			User::LeaveIfError(fsSession.DriveToChar(driveNumber,driveLetter));
			// The following line prints the drive letter followed by the hex value 
			// of the integer indicating that drive's attributes 
			console->Printf(KDriveAtts,TUint(driveLetter), drivelist[driveNumber]);
			}
		}
	console->Printf(KNewLine);

	// Print information about available drives 

	TBuf<200> buffer;
	TDriveInfo driveInfo; 
	for (driveNumber=EDriveA; driveNumber<=EDriveZ; driveNumber++)
		{
		fsSession.Drive(driveInfo,driveNumber);
		if (driveInfo.iDriveAtt==KDriveAbsent)
			// test whether drive is available. If not, skip to next drive
			continue;
		FormatDriveInfo(buffer,driveInfo);
		User::LeaveIfError(fsSession.DriveToChar(driveNumber,driveLetter));
		console->Printf(KDriveInfo,TUint(driveLetter),&buffer);
		buffer.Zero();
		WaitForKey();
		}

	// Print volume information for all available drives. TVolumeInfo
	// provides drive information, and additional information about
	// the volume. Just print out the volume information.
 
	TVolumeInfo volumeInfo;
	for (driveNumber=EDriveA; driveNumber<=EDriveZ; driveNumber++)
		{
		TInt err=fsSession.Volume(volumeInfo,driveNumber);
		if (err!=KErrNotReady) 
			// Volume() returns KErrNotReady if no volume present.
			// In this case, check next drive number
			{
			buffer.Zero();
			FormatVolumeInfo(buffer,volumeInfo);
			User::LeaveIfError(fsSession.DriveToChar(driveNumber,driveLetter));
			console->Printf(KVolInfo,
				(TUint)driveLetter,&buffer);
			WaitForKey();
			}
		}
	}

void FormatDriveInfo(TDes& aBuffer, const TDriveInfo aDriveInfo)
	{
	// Append battery, media and drive information to aBuffer
	// Define descriptor constants using the _LIT macro 
	_LIT(KFormatString,"iType=%02x,iBattery=%02x,iDriveAtt=%02x,iMediaAtt=%02x\n");
	_LIT(KBatLow,"Battery low\n");
	_LIT(KBatGood,"Battery good\n");
	_LIT(KBatNotSupported,"Battery not supported\n");
	_LIT(KNotPresent,"No media present\n");
	_LIT(KFloppy,"Media is floppy disk\n");
	_LIT(KHard,"Media is hard disk\n");
	_LIT(KCDROM,"Media is CD-ROM\n");
	_LIT(KRam,"Media is RAM\n");
	_LIT(KFlash,"Media is flash\n");
	_LIT(KRom,"Media is ROM\n");
	_LIT(KRemote,"Media is remote\n");
	_LIT(KUnknown,"Media unknown\n");
	_LIT(KDriveAtts,"Drive attributes:");
	_LIT(KLocal," local");
	_LIT(KROMDrive," ROM");
	_LIT(KRedirected," redirected");
	_LIT(KSubstituted," substituted");
	_LIT(KInternal," internal");
	_LIT(KRemovable," removable");
	_LIT(KMediaAtts,"\nMedia attributes:");
	_LIT(KDynamic," dynamic");
	_LIT(KDual," dual-density");
	_LIT(KFormattable," formattable");
	_LIT(KWriteProtected," write-protected");
	_LIT(KNewLine,"\n");

	aBuffer.AppendFormat(KFormatString, TInt(aDriveInfo.iType), 
		TInt(aDriveInfo.iBattery), TInt(aDriveInfo.iDriveAtt), TInt(aDriveInfo.iMediaAtt));

	switch (aDriveInfo.iBattery)
		{
		case EBatLow:
			aBuffer.Append(KBatLow);
			break;
		case EBatGood:
			aBuffer.Append(KBatGood);
			break;
		default:
			aBuffer.Append(KBatNotSupported);
		}

	switch (aDriveInfo.iType)
			{
		case EMediaNotPresent:
			aBuffer.Append(KNotPresent);			
			break;
		case EMediaFloppy:
			aBuffer.Append(KFloppy);
			break;
		case EMediaHardDisk:	
			aBuffer.Append(KHard);
			break;
		case EMediaCdRom:
			aBuffer.Append(KCDROM);
			break;
		case EMediaRam:
			aBuffer.Append(KRam);
			break;
		case EMediaFlash:
			aBuffer.Append(KFlash);
			break;
		case EMediaRom:
			aBuffer.Append(KRom);
			break;
		case EMediaRemote:
			aBuffer.Append(KRemote);
			break;
		default: 
			aBuffer.Append(KUnknown);
		}
		aBuffer.Append(KDriveAtts);
		if (aDriveInfo.iDriveAtt & KDriveAttLocal)
	 		aBuffer.Append(KLocal);
		if (aDriveInfo.iDriveAtt & KDriveAttRom)
			aBuffer.Append(KROMDrive);
 		if (aDriveInfo.iDriveAtt & KDriveAttRedirected)
	 		aBuffer.Append(KRedirected);
		if (aDriveInfo.iDriveAtt & KDriveAttSubsted)
	 		aBuffer.Append(KSubstituted);
		if (aDriveInfo.iDriveAtt & KDriveAttInternal)
	 		aBuffer.Append(KInternal);
		if (aDriveInfo.iDriveAtt & KDriveAttRemovable)
	 		aBuffer.Append(KRemovable);
		aBuffer.Append(KMediaAtts);
		if (aDriveInfo.iMediaAtt & KMediaAttVariableSize)
			aBuffer.Append(KDynamic);
		if (aDriveInfo.iMediaAtt & KMediaAttDualDensity)
			aBuffer.Append(KDual);
		if (aDriveInfo.iMediaAtt & KMediaAttFormattable)
			aBuffer.Append(KFormattable);
		if (aDriveInfo.iMediaAtt & KMediaAttWriteProtected)
			aBuffer.Append(KWriteProtected);
		aBuffer.Append(KNewLine);
	}

void FormatVolumeInfo(TDes& aBuffer, const TVolumeInfo aVolumeInfo)
	{
	// Append volume information to aBuffer
	_LIT(KUID,"Unique ID: %08x\n");
	_LIT(KSize,"Size: %d bytes\n");
	_LIT(KFree,"Free space: %d bytes\n");
	_LIT(KVolName,"Volume name: %S\n");
	aBuffer.AppendFormat(KUID,aVolumeInfo.iUniqueID);
	aBuffer.AppendFormat(KSize,aVolumeInfo.iSize);
	aBuffer.AppendFormat(KFree,aVolumeInfo.iFree);
	aBuffer.AppendFormat(KVolName,&aVolumeInfo.iName);
	}
