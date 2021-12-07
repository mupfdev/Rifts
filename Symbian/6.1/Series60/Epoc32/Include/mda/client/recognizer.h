// Mda\Client\Recognizer.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_RECOGNIZER_H__
#define __MDA_CLIENT_RECOGNIZER_H__

#include <e32base.h>

#include <Mda\Client\Base.h>
#include <Mda\Client\Resource.h>

class CPackageHolder;
class CMdaRecognizer : public CBase
	{
public:
	enum TMatchMethod
		{
		ENotMatched,
		EByName,
		EBySignature
		};
public:
	IMPORT_C CMdaRecognizer();
	IMPORT_C virtual ~CMdaRecognizer();
	IMPORT_C void BuildListL();

	IMPORT_C TMatchMethod Match(const TDesC& aName, const TDesC8& aBuffer);
	IMPORT_C const TDesC8& MimeString();

	IMPORT_C const TDesC8& SupportedDataTypeL(TInt aIndex) const;
	IMPORT_C TInt NumMimeTypes();

private:
	void CountMimeTypes();
	TMatchMethod DoMatch(TBool aCountingMimeTypes,const TDesC& aName, const TDesC8& aBuffer);

private:
	class CFormatList : public CBase
		{
	public:
		CFormatList();
		virtual ~CFormatList();
		void BuildListL();
	private:
		void Clear();
	public:
		RMdaSession iSession;
		TSglQue<CPackageHolder> iData;
		};
private:
	CFormatList iList;
	TPtrC8 iMimeString;
	TInt iNumMimeTypes;
	};

class TMdaResourceEntryParser
	{
public:
	enum TType
		{
		EConfigDef,
		ESignature,
		ECapabilities,
		EExtension,
		EStrings
		};
public:
	IMPORT_C void Set(const TDesC8& aResource);
	IMPORT_C TUint Count(TType aType) const;
	IMPORT_C const TPtrC8 Entry(TType aType, TInt aIndex) const;
private:
	TPtrC8 iPtr;
	TUint iIndices[EStrings+1];
	TUint iCounts[EStrings+1];
	};

#endif
