// CONARC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONARC_H__)
#define __CONARC_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif

//
// base interface for converters
//

#ifdef _UNICODE
#define KUidConverterDll KUidConverterDll16
#else
#define KUidConverterDll KUidConverterDll8
#endif

const TInt KUidConverterDllValue8=0x10000C61;
const TUid KUidConverterDll8={KUidConverterDllValue8};
const TInt KUidConverterInfoFileValue=0x10000C62;
const TUid KUidConverterInfoFile={KUidConverterInfoFileValue};
const TInt KUidConverterInfoStreamValue=0x10000CD0;
const TUid KUidConverterInfoStream={KUidConverterInfoStreamValue};
const TUid KUidConverterDll16={0x10003A30};

_LIT(KConverterInfoFileExtension,".CNF");
_LIT(KConverterDllExtension,".CNV");

class MConverterUiObserver
// abstract base class for observer UI interface
	{
public:
	enum TResult
		{
		ESuccess,
		EPartialSuccess,
		EFailure
		};
	enum TAction
		{
		ERetain,
		ERemove,
		ERepeat
		}; 
public:
	virtual void MaxSteps(TInt aMax, TInt aObject)=0;
	virtual TInt Result(TInt aResult, TInt aObject)=0; // Passes in a TResult, returns a TAction
	virtual HBufC* QueryPasswordL(const TDesC& aClue)=0;
	IMPORT_C virtual void Reserved1_Conv_Obs();
	};

class CConverterBase : public CBase
// abstract base class for all converters
	{
public:
	enum TCapability
		{
		EConvertsFiles=0x01,
		EConvertsObjects=0x02,
		EConvertsExtract=0x04
		};
public:
	IMPORT_C virtual void ConvertL(const TFileName& aSourceFile, const TFileName& aTargetFile, MConverterUiObserver* aObserver=NULL); // These default to calling the async versions in a loop
	IMPORT_C virtual void ConvertObjectL(RReadStream& aReadStream, RWriteStream& aWriteStream, MConverterUiObserver* aObserver=NULL);
	IMPORT_C virtual void ConvertAL(const TFileName& aSourceFile, const TFileName& aTargetFile, MConverterUiObserver* aObserver=NULL); // these default to leaving with KErrNotSupported
	IMPORT_C virtual void ConvertObjectAL(RReadStream& aReadStream, RWriteStream& aWriteStream, MConverterUiObserver* aObserver=NULL); // these default to leaving with KErrNotSupported
	IMPORT_C virtual TBool DoConvertL(); // these default to leaving with KErrNotSupported
	virtual TUid Uid() =0;
	IMPORT_C virtual TInt Capabilities(); // defaults to "everything"
	IMPORT_C virtual void CancelConvert(); // for any cleanup
	IMPORT_C virtual CConverterBase* EmbeddedObjectL(TDataType& aType);
	IMPORT_C virtual TBool GetEmbeddedFileName(TFileName& aFileName);
private:
	IMPORT_C virtual void Reserved_1();
	};

class CConverterLibrary : public CBase
	{
public:
	virtual CConverterBase* Converter(TUid aUid)=0;	// passes ownership
	// returns a converter with Uid aUid
	// NOTE this cannot allocate ANYTHING 
	// that it does not return
	};

#endif