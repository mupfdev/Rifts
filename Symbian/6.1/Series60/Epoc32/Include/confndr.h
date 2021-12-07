// CONFNDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONFNDR_H__)

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__CONARC_H__)
#include <conarc.h>
#endif

#if !defined(__CONCNF_H__)
#include <concnf.h>
#endif

class CCnaFoundConverter : public CBase
	{
public:
	static CCnaFoundConverter* NewLC(TFileName& anEntry, CCnaConverter& aConverter);
	static CCnaFoundConverter* NewL(TFileName& anEntry, CCnaConverter& aConverter);
	CCnaFoundConverter();
	~CCnaFoundConverter();
private:
	void ConstructL(CCnaConverter& aConverter);
	CCnaFoundConverter(TFileName& aConEntry);
public:
	TFileName iConEntry; // reference to the containing dll
	TBuf<2> iDllDrive;
	CCnaConverter* iConverter;
	};

//
// classes to supply scanning for converters
//

class CCnaScanningCnfFinder : public CBase
// provide scanning for CNF files
	{
public:
	static CCnaScanningCnfFinder* NewLC(RFs& aFs);
	static CCnaScanningCnfFinder* NewL(RFs& aFs);
	~CCnaScanningCnfFinder();
	void FindAllCnfL();
	TBool NextL(TFileName& aCnfFile, TUid& aUid);
private:
	CCnaScanningCnfFinder(RFs& aFs);
	TInt GetFileList(TInt aDriveNum);
	TBool GetFullPathAndUid(TFileName& aCnfFile, TUid& aUid);
private:
	CDir* iFileList;
	TDriveList* iDriveList;
	TInt iDriveNum;
	TInt iDirIndex;
	RFs& iFs;
	};

class CCnaScanningConverterFinder : public CBase
// concrete converter finder class, encodes rules on converter
// locations
	{
public:
	IMPORT_C static CCnaScanningConverterFinder* NewLC(RFs& aFs);
	IMPORT_C static CCnaScanningConverterFinder* NewL(RFs& aFs);
	IMPORT_C ~CCnaScanningConverterFinder();
public:
	void FindAllConvL();
	TBool NextL(CCnaFoundConverter& aConverter);
private:
	CCnaScanningConverterFinder(RFs& aFs);
	TBool FoundDll(TDes& aDllDrive);
private:
	TUid iUid;
	TFileName iCnfFile;
	CCnaScanningCnfFinder* iCnfFinder;
	CCnaConvInfoFileReader* iReadConverter;
	TInt iConverterIndex;
	RFs& iFs;
	};

#endif