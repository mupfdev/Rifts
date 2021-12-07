// CONLIST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONLIST_H__)
#define __CONLIST_H__

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

struct SConverterInfo
	{
	TTranslation iTranslation;
	TUid iUid;
	TInt iIndex;
	};

// classes referenced
class CCnaFoundConverter;

class CCnaConverterList : public CBase
// Holds a list of converters and provides a means for querying
// the list and obtaining pointers to the constructed converters
	{
public:
	IMPORT_C static CCnaConverterList* NewL();
	IMPORT_C static CCnaConverterList* NewLC();
	IMPORT_C void Release();
	IMPORT_C ~CCnaConverterList();
//
	IMPORT_C TInt Count();
	IMPORT_C CConverterBase* NewConverterL(TUid aUid);
	IMPORT_C void UpdateL();
	IMPORT_C TUid ConvFromL(const TDataType& aMimeType); // searches for a particular converter
	IMPORT_C TUid ConvToL(const TDataType& aMimeType);
	IMPORT_C TUid ConverterL(const TDataType& aFrom,const TDataType& aTo);
	IMPORT_C void ConvFromListL(const TDataType& aMimeType,CArrayFix<SConverterInfo>* aSConverterInfoArray);
	IMPORT_C void ConvToListL(const TDataType& aMimeType,CArrayFix<SConverterInfo>* aSConverterInfoArray);
/**
 * returns the MimeTypeFrom from a SConverterInfo. Returns KErrNotFound if the Converter is missing
*/
	IMPORT_C TInt MimeTypeFrom(TDataType& aDataType,const SConverterInfo& aConverterInfo) const;
/**
 * returns the MimeTypeTo from a SConverterInfo. Returns KErrNotFound if the Converter is missing
*/
	IMPORT_C TInt MimeTypeTo(TDataType& aDataType,const SConverterInfo& aConverterInfo) const;
private:
	CCnaConverterList();
	void ConstructL();
	CConverterBase* LoadConverterL(CCnaFoundConverter& aConverter);
private:
	CArrayPtr<CCnaFoundConverter>* iConverterList;
	CArrayFix<RLibrary>* iLoadedDlls;
	TBool iDoneScan;
	};

class ConverterListUtil
	{
public:
	static CConverterBase* UtilityConverterL(TUid aUid);
	static TInt CountUtilityConverters();
	};

#endif
