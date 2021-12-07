// EIKFUTIL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKFUTIL_H__)
#define __EIKFUTIL_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__BADESCA_H__)
#include <badesca.h>
#endif

#if !defined(__BAUTILS_H__)
#include <bautils.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

class CFont;
class CBaflFileSortTable;
class TResourceReader;

class EikFileUtils
	{ 
public:
	inline static TBool PathExists(const TDesC& aPath);
	inline static TInt IsFolder(const TDesC& aFullName, TBool& aIsFolder);
	inline static TBool FolderExists(const TDesC& aFolderName);
	inline static TFileName FolderNameFromFullName(const TDesC& aFullName);
	inline static TFileName DriveAndPathFromFullName(const TDesC& aFullName);
	inline static TFileName RootFolderPath(const TBuf<1> aDriveLetter);
	inline static void AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName);
	IMPORT_C static TFileName AbbreviatePath(TDesC& aPathName, const CFont& aFont, TInt aMaxWidthInPixels);
	inline static TBool UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid);
	inline static TInt Parse(const TDesC& aName);
	IMPORT_C static TFileName ValidateFolderNameTypedByUserL(const TDesC& aFolderNameTypedByUser, const TDesC& aCurrentPath);
	inline static TInt CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch = CFileMan::EOverWrite);
	inline static TInt RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch = CFileMan::EOverWrite);
	inline static TInt DeleteFile(const TDesC& aSourceFullName, TUint aSwitch=0);
	inline static TInt CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder);
	inline static TInt MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart);
	inline static TInt CheckFolder(const TDesC& aFolderName);
	inline static TInt DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly);
	inline static void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);
	inline static void RemoveSystemDirectory(CDir& aDir);
	inline static TBool IsFirstDriveForSocket(TDriveUnit aDriveUnit);
	inline static TInt SortByTable(CDir& aDir,CBaflFileSortTable* aTable);
	};

//
// class EikFileUtils
//

inline TBool EikFileUtils::PathExists(const TDesC& aPath)
	{
	return BaflUtils::PathExists(CEikonEnv::Static()->FsSession(),aPath);
	}

inline TInt EikFileUtils::IsFolder(const TDesC& aFullName, TBool& aIsFolder)
	{
	return BaflUtils::IsFolder(CEikonEnv::Static()->FsSession(), aFullName,aIsFolder);
	}

inline TBool EikFileUtils::FolderExists(const TDesC& aFolderName)
	{
	return BaflUtils::FolderExists(CEikonEnv::Static()->FsSession(), aFolderName);
	}

inline TFileName EikFileUtils::FolderNameFromFullName(const TDesC& aFullName)
	{
	return BaflUtils::FolderNameFromFullName(aFullName);
	}

inline TFileName EikFileUtils::DriveAndPathFromFullName(const TDesC& aFullName)
	{
	return BaflUtils::DriveAndPathFromFullName(aFullName);
	}

inline TFileName EikFileUtils::RootFolderPath(const TBuf<1> aDriveLetter)
	{
	return BaflUtils::RootFolderPath(aDriveLetter);
	}

inline void EikFileUtils::AbbreviateFileName(const TFileName& aOriginalFileName, TDes& aAbbreviatedFileName)
	{
	BaflUtils::AbbreviateFileName(aOriginalFileName,aAbbreviatedFileName);
	}

inline TBool EikFileUtils::UidTypeMatches(const TUidType& aFileUid, const TUidType& aMatchUid)
	{
	return BaflUtils::UidTypeMatches(aFileUid,aMatchUid);
	}

inline TInt EikFileUtils::Parse(const TDesC& aName)
	{
	return BaflUtils::Parse(aName);
	}

inline TInt EikFileUtils::CopyFile(const TDesC& aSourceFullName, const TDesC& aTargetFullName, TUint aSwitch)
	{
	return BaflUtils::CopyFile(CEikonEnv::Static()->FsSession(),aSourceFullName,aTargetFullName,aSwitch);
	}

inline TInt EikFileUtils::RenameFile(const TDesC& aOldFullName, const TDesC& aNewFullName, TUint aSwitch)
	{
	return BaflUtils::RenameFile(CEikonEnv::Static()->FsSession(),aOldFullName,aNewFullName,aSwitch);
	}

inline TInt EikFileUtils::DeleteFile(const TDesC& aSourceFullName, TUint aSwitch)
	{
	return BaflUtils::DeleteFile(CEikonEnv::Static()->FsSession(), aSourceFullName,aSwitch);
	}

inline TInt EikFileUtils::CheckWhetherFullNameRefersToFolder(const TDesC& aFullName, TBool& aIsFolder)
	{
	return BaflUtils::CheckWhetherFullNameRefersToFolder(aFullName,aIsFolder);
	}

inline TInt EikFileUtils::MostSignificantPartOfFullName(const TDesC& aFullName, TFileName& aMostSignificantPart)
	{
	return BaflUtils::MostSignificantPartOfFullName(aFullName,aMostSignificantPart);
	}

inline TInt EikFileUtils::CheckFolder(const TDesC& aFolderName)
	{
	return BaflUtils::CheckFolder(CEikonEnv::Static()->FsSession(),aFolderName);
	}

inline TInt EikFileUtils::DiskIsReadOnly(const TDesC& aFullName, TBool& aIsReadOnly)
	{
	return BaflUtils::DiskIsReadOnly(CEikonEnv::Static()->FsSession(),aFullName,aIsReadOnly);
	}

inline void EikFileUtils::UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber)
	{
	BaflUtils::UpdateDiskListL(aFs,aArray,aIncludeRom,aDriveNumber);
	}

inline void EikFileUtils::RemoveSystemDirectory(CDir& aDir)
	{
	BaflUtils::RemoveSystemDirectory(aDir);
	}

inline TBool EikFileUtils::IsFirstDriveForSocket(TDriveUnit aDriveUnit)
	{
	return BaflUtils::IsFirstDriveForSocket(aDriveUnit);
	}

inline TInt EikFileUtils::SortByTable(CDir& aDir,CBaflFileSortTable* aTable)
	{
	return BaflUtils::SortByTable(aDir,aTable);
	}


#endif
