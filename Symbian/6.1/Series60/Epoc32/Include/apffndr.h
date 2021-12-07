// APFFNDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APFFNDR_H__
#define __APFFNDR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

// classes defined:
class CApaScanningAppFinder;
//
// classes referenced:
class CDir;
//

_LIT(KAppDllSearchPath,"\\System\\Apps\\");
_LIT(KAppDllSearchString,"?:\\System\\Apps\\");

/**
 * @internal
 * Internal to Symbian
 */
class CApaScanningAppFinder : public CApaAppFinder
	{
public:
	IMPORT_C static CApaScanningAppFinder* NewLC(const RFs& aFs);
	IMPORT_C static CApaScanningAppFinder* NewL(const RFs& aFs);
	//
	IMPORT_C void FindAllAppsL();
	IMPORT_C TBool NextL(TApaAppEntry& aEntry);
	IMPORT_C TFileName FindAppL(const TDesC& aFileName,TUid aFileUid); 
	//
	IMPORT_C TFileName TempPath()const;
	IMPORT_C TFileName DefaultAppInfoFileName()const;
	//
	IMPORT_C ~CApaScanningAppFinder();
private:
	CApaScanningAppFinder(const RFs& aFs);
	TBool ScanDriveByNameL(TFileName& aFullPath,const TDesC& aDriveName,const TDesC& aTargetName);
	TBool ScanDriveByUidL(TFileName& aFullName,TUid aUid,const TDesC& aExtension,const TDesC& aDriveName);
	void SetSearchPathL(TFileName& aSearchPath,const TDesC& aFileName)const;
	TInt GetAppEntryL(TApaAppEntry& aAppEntry,const TEntry& aDir);
	TInt GetFileListL(TInt aDriveNum);
	TInt NextDriveToScan(TInt aCurrentDrive)const;
	static void CheckErrorL(TInt aError);
private:
	CDir* iFileList;
	TDriveList* iDriveList;
	TInt iDriveNum;
	TInt iDirIndex;
	const RFs& iFs;
	};


#endif