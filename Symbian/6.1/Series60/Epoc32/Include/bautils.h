// BAUTILS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__BAUTILS_H__)
#define __BAUTILS_H__

#include <e32std.h>
#include <f32file.h>
#include <barsread.h>
#include <badesca.h>

const TUint KBaflCharTruncation=0x85; // '…';

class RFs;
class CBaflFileSortTable;
class BaflUtils
	{
public:
	IMPORT_C static void CopyWithTruncation(TDes& aDest,const TDesC& aSrc,TChar aTruncationSymbol=KBaflCharTruncation);
	IMPORT_C static TBool FileExists(const RFs& aFs,const TDesC& aFileName);
	IMPORT_C static void EnsurePathExistsL(RFs& aFs,const TDesC& aFileName);
	IMPORT_C static TPtrC ExtractAppNameFromFullName(const TFullName &aName);
	IMPORT_C static void NearestLanguageFile(const RFs& aFs,TFileName& aName);
	IMPORT_C static TInt GetSystemDrive(TDriveNumber& aDriveNumber);
	IMPORT_C static TBool PathExists(RFs& aFs,const TDesC& aFileName);
	IMPORT_C static TInt IsFolder(const RFs& aFs, const TDesC& aFullName, TBool& aIsFolder);
	IMPORT_C static TBool FolderExists(RFs& aFs, const TDesC& aFolderName);
	IMPORT_C static TFileName FolderNameFromFullName(const TDesC& aFullName);
	IMPORT_C static TFileName DriveAndPathFromFullName(const TDesC& aFullName);
	IMPORT_C static TFileName RootFolderPath(const TBuf<1> aDriveLetter);
	IMPORT_C static void AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName);
	IMPORT_C static TBool UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid);
	IMPORT_C static TInt Parse(const TDesC& aName);
	IMPORT_C static TInt ValidateFolderNameTypedByUserL(const RFs& aFs, const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath, TFileName& aNewFolderFullName);
	IMPORT_C static TInt CopyFile(RFs& aFs, const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch = CFileMan::EOverWrite);
	IMPORT_C static TInt RenameFile(RFs& aFs, const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch = CFileMan::EOverWrite);
	IMPORT_C static TInt DeleteFile(RFs& aFs, const TDesC& aSourceFullName, TUint aSwitch = 0);
	IMPORT_C static TInt CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder);
	IMPORT_C static TInt MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart);
	IMPORT_C static TInt CheckFolder(RFs& aFs, const TDesC& aFolderName);
	IMPORT_C static TInt DiskIsReadOnly(RFs& aFs, const TDesC& aFullName, TBool& aIsReadOnly);
	IMPORT_C static void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);
	IMPORT_C static void RemoveSystemDirectory(CDir& aDir);
	IMPORT_C static TBool IsFirstDriveForSocket(TDriveUnit aDriveUnit);
	IMPORT_C static TInt SortByTable(CDir& aDir,CBaflFileSortTable* aTable);
private:
	static void DoCopyFileL(RFs& aFs, const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch);
	static void DoRenameFileL(RFs& aFs, const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch);
	static void DoDeleteFileL(RFs& aFs, const TDesC& aSourceFullName, TUint aSwitch);
	};

/**
 * @internal
 * Internal to Symbian
 */
class CBaflFileSortTable : public CArrayFixFlat<TUid>
	{
public:
	IMPORT_C CBaflFileSortTable();
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
private:
	enum {EArrayGranularity=4};
	};

#endif
