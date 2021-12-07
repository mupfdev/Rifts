// BSP.H (Base Script Parser)
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
// 
// Abstract class for different Parsers.


#if !defined(__BSP_H__)
#define __BSP_H__

#if !defined(__MTCLREG_H__)
#include <mtclreg.h>
#endif

#if !defined(__MTCLBASE_H__)
#include <mtclbase.h>
#endif

#include <e32base.h>
#if !defined(__S32STRM_H__)
#include <s32strm.h>
#endif

#include <msvstd.h>
// CRichText etc. includes
#include <txtrich.h>
#include <txtfmlyr.h>

#include <bif.h>

// Symbols:
#define KCharSpace          ' '
#define KCharTab            '\t'
#define KCharLineFeed       '\n'


// Define some generic error codes:
const TInt KBspBaseError					= (-500);

const TInt KBspInvalidMessage				= (KBspBaseError);
const TInt KBspSmartMessageInvalidToken		= (KBspBaseError-1);
const TInt KBspSmartMessageNoParserDefined	= (KBspBaseError-2);

// Parsed field class for use by parsers.
class CParsedField : public CBase
{
public:
	IMPORT_C CParsedField();
	IMPORT_C ~CParsedField();

	IMPORT_C TPtrC FieldName() const;
	IMPORT_C void SetFieldNameL( const TDesC& aFieldName);
	IMPORT_C TPtrC FieldValue() const;
	IMPORT_C void SetFieldValueL( const TDesC& aFieldValue);
	IMPORT_C TBool MandatoryField() const;
	IMPORT_C void SetMandatoryField(TBool aMandatoryField);

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	void Reset();
private:
	HBufC* iFieldName;
	HBufC* iFieldValue;
	TBool  iMandatoryField;
};

// Forward declarations:
class CMsvServerEntry;
class CRegisteredParserDll;
class RMsvReadStream;
class RMsvWriteStream;
class CMsvStore;
class CSmsMessage;

// Parser base class:
class CBaseScriptParser: public CActive
{
public:
	IMPORT_C CBaseScriptParser(CRegisteredParserDll& aRegisteredParserDll, CMsvServerEntry& aEntry, RFs& aFs);
	IMPORT_C ~CBaseScriptParser();

	virtual void ParseL(TRequestStatus& aStatus, const TDesC& aSms)=0; //parses sms data into CParsedField
	virtual void ProcessL(TRequestStatus& aStatus)=0; //stores parsed data into streams and data base

	IMPORT_C TUid ParserUid();
	IMPORT_C void RestoreL( CMsvStore& aMessageStore );
	IMPORT_C void StoreL  ( CMsvStore& aMessageStore ) const;
	IMPORT_C void RestoreL( const TFileName& aFileName );
	IMPORT_C void StoreL  (const TFileName& aFileName ) const;
	IMPORT_C void ResetL();
//	virtual const TMsvBIODataLocation() const;	// hard-coded based on parser type
	
protected:
//	CActive:
	virtual void DoCancel() =0;
	virtual void RunL() =0;

//	Parsing:
	IMPORT_C void UnfoldMessageL();

//	Streaming operations:
	void InternalizeL(RMsvReadStream& aStream);
	void ExternalizeL(RMsvWriteStream& aStream) const;

protected:
	CRegisteredParserDll&		iRegisteredParserDll;
	CMsvServerEntry&			iEntry;
	RFs&						iFs;

	TLex						iSms;
	CArrayPtrSeg<CParsedField>* iParsedFieldArray;

	TBool						iSmsParsed;
	TMsvId						iEntryId;
	
	HBufC*						iSettings;
    HBufC*						iSmsBuf;                // Local copy of buffer passed to ParseL()
	HBufC8*						iReadBuffer;			// used to restore data from file
};


 
enum TMsvBIODataLocation
	{
	EUnknown,
	EBodyText,		// parser wrote data back into richText
	EBIODataStream,	// parser wrote data into KUIDMsvBioStream
	EFile			// parser wrote data into attachment file
	};


// Bearer Independent Object entry.
class TMsvBIOEntry : public TMsvEntry
	{
public:
	TMsvBIOEntry() : TMsvEntry() {};
	void SetBIOParserUid(const TUid aId);
	const TUid BIOParserUid() const;
	void SetLocationOfData(const TMsvBIODataLocation aLocation);
	const TMsvBIODataLocation LocationOfData() const;

private:
	TMsvBIODataLocation	iLocationOfData;
	};

#include "bsp.inl"

#endif

