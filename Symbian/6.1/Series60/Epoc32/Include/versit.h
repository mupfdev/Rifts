// VERSIT.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __VERSIT_H__
#define __VERSIT_H__

// System includes
#include <e32base.h>
#include <badesca.h>
#include <s32file.h>

// User includes
#include "vuid.h"
#include "vtoken.h"
#include "vprop.h"
#include "versittls.h"

// Classes referenced
class RFile;
class TVersitDateTime;
class MVersitObserver;
class MVersitPlugIn;

// Panic enumeration
enum TVersitParserPanic
	{
	ECurrentTokenNotFound,		//Unused
	EUnicodeUtilsNotFound,		//Unused
	ENoPropertyValue,		//Unused
	ENoWeekdayFound,
	EWeekNoOverTen,
	ENoRecognizedRepeatType,
	EVersitPanicEscapedTextAlreadyExists,		//Unused
	EVersitPanicCannotSetEightBitEncoding,
	EVersitPanicUnexpectedEightBitEncoding,
	EVersitPanicNeedToSpecifyParser,
	//
	EVersitPanicLast
	};

GLREF_C void DestroyHBufC(TAny* aHBufC);
IMPORT_C void Panic(TVersitParserPanic aPanic);

/**
 * Line Reader for a vCalendar or vCard parser.
 *
 * This class reads in a line at a time for the parser.
 * It also allows the first character of the next line to be check to see if it is a space.
 *
 * @since 7.0
 * @lib "versit.lib"
 */
class CLineReader : public CBase
	{
public:
	enum
		{
		EInitialLineSize=96,
		EExpandSize=16,
		};
	enum
		{
		ELineHasContent=0,
		ELineIsWhiteSpace=1,		//Doesn't include next case
		ELineIsCRLFOnly=2,
		};
public:
	IMPORT_C static CLineReader* NewL(RReadStream& aStream);
	IMPORT_C ~CLineReader();
	IMPORT_C virtual TBool ReadLineL(TInt aPos,TInt& aErr);
	IMPORT_C TBool AppendLineIfSpaceNextL();
	IMPORT_C TBool IsSpaceNextL();
	IMPORT_C TInt AppendSpaceL();
	inline void SetPlugIn(MVersitPlugIn* aPlugIn);
protected:
	inline CLineReader(RReadStream& aStream) :iReadStream(&aStream), iBufPtr(NULL,0), iFirstCharNextLine(-1) {}
	IMPORT_C void ConstructL();
	IMPORT_C void ExpandBufferL(TInt aCurrentSize);
	IMPORT_C TUint8 ReadChar(TInt& aErr);
private:
	IMPORT_C virtual void Reserved();
public:
	RReadStream* iReadStream;
	TPtr8 iBufPtr;
protected:
	HBufC8* iLineBuf;
	TInt iFirstCharNextLine;
private:
	MVersitPlugIn* iPlugIn;
	TInt iReserved;
	};

/**
 * vCalendar or vCard parser.
 *
 * The vCalendar or vCard data is read from or written to a stream.
 * <code>InternalizeL()</code> reads the vCalendar or vCard contained in
 * the stream and parses it, breaking it down into its constituent
 * sub-entities (e.g. to-dos, events, and nested vCards) and properties.
 * It also converts all date/times into machine-local values.
 * <code>ExternalizeL()</code> writes the vCalendar or vCard to a write
 * stream, converting all date/time values from machine-local into
 * universal time. Most users of this class will only need to use these
 * two functions.The class also provides functions to add properties and
 * sub-entities to an existing object. Although this is not an abstract
 * class, in practice, you would create and use objects of one of the
 * derived classes instead (<code>CParserVCard</code> or
 * <code>CParserVCal</code>).
 *
 * Note: The functions of this class do not perform any roll back.
 * If an Internalize leaves then the data is likely to be corrupt
 * and the stream could be at any random point.
 *
 * @since 5.0
 * @lib " versit.lib "
 */
class CVersitParser : public CBase
	{
	friend class CParserProperty;
public:
	IMPORT_C CVersitParser(TUint aFlags);
	IMPORT_C void ConstructL();
	IMPORT_C ~CVersitParser();
	IMPORT_C void								InternalizeL(RFile& aInputFile,TInt& aBytesThroughFile);
	IMPORT_C virtual void						InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void						InternalizeL(HBufC* aEntityName,CLineReader* aLineReader);
	IMPORT_C void								ExternalizeL(RFile& aOutputFile);
	IMPORT_C virtual void						ExternalizeL(RWriteStream& aStream);
	IMPORT_C void								AddEntityL(CVersitParser* aEntity);
	IMPORT_C void								AddPropertyL(CParserProperty* aProperty,TBool aInternalizing=EFalse);
	IMPORT_C CArrayPtr<CVersitParser>*			EntityL(const TDesC& aEntityName,TBool aTakeOwnership=ETrue);
	IMPORT_C CArrayPtr<CVersitParser>*			ArrayOfEntities(TBool aTakeOwnership=ETrue);
	IMPORT_C CArrayPtr<CParserProperty>*		PropertyL(const TDesC8& aPropertyName,const TUid& aPropertyUid,TBool aTakeOwnership=ETrue) const;
	IMPORT_C CArrayPtr<CParserProperty>*		ArrayOfProperties(TBool aTakeOwnership=ETrue);
	IMPORT_C virtual void						ConvertAllPropertyDateTimesToMachineLocalL(const TTimeIntervalSeconds& aIncrement,const CVersitDaylight* aDaylight);
	IMPORT_C static TBool						IsValidParameterValue(TInt& aPos,const TDesC& aParamValue);
	IMPORT_C void								SetEntityNameL(const TDesC& aEntityName);
	IMPORT_C TPtrC								EntityName() const;
	IMPORT_C static TBool						IsValidLabel(const TDesC& aLabel, TInt& aPos);
	IMPORT_C static TInt						Val(const TDesC& aString, TInt& aNumber);
	IMPORT_C void								SetCharacterConverter(Versit::TEncodingAndCharset& encodingAndCharset);

	//
	// Set/Get the default settings for the [en|de]coding process
	//
	IMPORT_C Versit::TVersitEncoding			DefaultEncoding() const;
	IMPORT_C void								SetDefaultEncoding(const Versit::TVersitEncoding aEncoding);
	IMPORT_C Versit::TVersitCharSet				DefaultCharSet() const;
	IMPORT_C TUint								DefaultCharSetId() const;
	IMPORT_C void								SetDefaultCharSet(const Versit::TVersitCharSet aCharSet);
	IMPORT_C void								SetDefaultCharSetId(TUint aCharSetId);
	IMPORT_C void								SetAutoDetect(TBool aOn,const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* aAutoDetectCharSets=NULL);

	//
	// Set/Get Observers and PlugIn's
	//
	inline void									SetObserver(MVersitObserver* aObserver);
	inline MVersitObserver*						Observer();
	inline void									SetPlugIn(MVersitPlugIn* aPlugIn);
	inline MVersitPlugIn*						PlugIn();

public:	
	enum TCharCodes
		{
		ESpace				= ' ',
		EHTab				= 9,
		ELineFeed			= 10,
		ECarriageReturn		= 13
		};
	enum TVersitParserFlags
		{
		ENoVersionProperty	= 0,		//This entity does not need a version property
		ESupportsVersion	= 0x01,		//This entity should have a version property
		//Gap since other flags have been used in past
		EUseAutoDetection	= 0x4000,	//If set use CharConnv auto detection of Char Set when one not specified.
		//versit Internal use only
		ECharSetIdentified	= 0x8000,	//The current property has specified a Char Set.
		};

	//
	// Unicode support conversion functions
	// 
	IMPORT_C static TInt						ConvertFromUnicodeToISOL(TDes8& aIso, const TDesC16& aUnicode, CCnvCharacterSetConverter* aConverter);
protected:
	IMPORT_C TInt								ConvertToUnicodeFromISOL(TDes16& aUnicode, const TDesC8& aIso, TUint aCharacterSet);
	
	//
	// Parsing high level functions
	//
	IMPORT_C void								ParsePropertiesL();
	IMPORT_C void								ParseBeginL();
	IMPORT_C void								ParseEndL();
	IMPORT_C TBool								ParseEntityL();
	IMPORT_C virtual void						ParsePropertyL();
	IMPORT_C CArrayPtr<CParserParam>*			ReadLineAndDecodeParamsLC(TInt& aValueStart,TInt& aNameLen);
	IMPORT_C void								MakePropertyL(TPtr8& aPropName,TInt aValueStart);
	IMPORT_C CArrayPtr<CParserParam>*			GetPropertyParamsLC(TPtr8 aParams);
	IMPORT_C void								ParseParamL(CArrayPtr<CParserParam>* aArray,TPtr8 aParam);
	IMPORT_C void								AnalysesEncodingCharset(CArrayPtr<CParserParam>* aArrayOfParams);
	IMPORT_C void								ReadMultiLineValueL(TPtr8& aValue,TInt aValueStart,TBool aBinaryData);
	inline TPtr8&								BufPtr();
	
	//
	// Append standard versit tokens to streams
	//
	IMPORT_C void								AppendBeginL();
	IMPORT_C void								AppendEndL();
	void										AppendEntityNameL();
	IMPORT_C void								DoAddPropertyL(CParserProperty* aProperty);

	//
	// Dispatcher functions to create entities/properties based upon a Versit identifying Uid
	//
	IMPORT_C virtual CVersitParser*				MakeEntityL(TInt aEntityUid,HBufC* aEntityName);
	IMPORT_C virtual CParserPropertyValue*		MakePropertyValueL(const TUid& aPropertyUid,HBufC16*& aValue);
	IMPORT_C HBufC*								DecodePropertyValueL(const TDesC8& aValue);
	IMPORT_C void								DecodePropertyValueL(const TDesC8& aValue,const TUid& aEncodingUid);
	HBufC*										ConvertToUnicodeL(const TDesC8& aValue);
	IMPORT_C CDesCArray*						MakePropertyValueCDesCArrayL(TPtr16 aStringValue);
	IMPORT_C CArrayPtr<TVersitDateTime>*		MakePropertyValueMultiDateTimeL(TPtr16 aDateTimeGroup);
	IMPORT_C CVersitDaylight*					MakePropertyValueDaylightL(TPtr16 aDaylightValue);
	IMPORT_C TBool								FindFirstField(TPtr16& aField,TPtr16& aRemaining, TBool aTrimSpace=ETrue);

	//
	// Helper methods to decode versit dates, times, and time periods
	//
	IMPORT_C TVersitDateTime*					DecodeDateTimeL(TDes& aToken) const;
	IMPORT_C TTimeIntervalSeconds				DecodeTimeZoneL(const TDesC& aToken) const;
	IMPORT_C TTime*								DecodeTimePeriodL(const TDesC& aToken) const;
	IMPORT_C TInt								GetNumberL(const TDesC& aToken,TInt& aNumChars) const;

public:
	IMPORT_C virtual TUid						RecognizeToken(const TDesC8& aToken) const;
	IMPORT_C virtual TInt						RecognizeEntityName() const;
	//
	// Cleanup support methods
	//
	IMPORT_C static void						ResetAndDestroyArrayOfParams(TAny* aObject);	
	IMPORT_C static void						ResetAndDestroyArrayOfProperties(TAny* aObject);	
	IMPORT_C static void						ResetAndDestroyArrayOfEntities(TAny* aObject);	
	IMPORT_C static void						ResetAndDestroyArrayOfDateTimes(TAny* aObject);	

protected:
	//
	// Enquiry functions
	//
	static TBool								IsPunctuationToken(TUint aChar);
	inline TBool								SupportsVersion() const;
	inline void									SetSupportsVersion();
	inline void									ClearSupportsVersion();

	//
	// Set the settings for the [en|de]coding of the current property
	//
	IMPORT_C void								RestoreLineCodingDetailsToDefault();
	IMPORT_C void								SetLineEncoding(Versit::TVersitEncoding aLineEncoding);
	IMPORT_C void								SetLineEncoding(TUint aVersitEncodingUid);
	IMPORT_C void								SetLineCharacterSet(Versit::TVersitCharSet aLineCharSet);
	IMPORT_C void								SetLineCharacterSetId(TUint aLineCharSetId);
	IMPORT_C void								SetLineCoding(Versit::TVersitCharSet aLineCharSet, Versit::TVersitEncoding aLineEncoding);

	//
	// Return the settings for the current property
	//
	IMPORT_C Versit::TVersitEncoding			LineEncoding() const;
	IMPORT_C Versit::TVersitCharSet				LineCharSet() const;
	IMPORT_C TUint								LineEncodingId() const;
	IMPORT_C TUint								LineCharSetId() const;

	inline CVersitUnicodeUtils&					UnicodeUtils();

public:
	//
	// Static utility functions to aid with the Unicode conversion process
	//
	static TUint								MapVersitCharsetToCharConvCharset(Versit::TVersitCharSet aVersitSet);
	static TUint								MapVersitEncodingToConArcUid(Versit::TVersitEncoding aVersitEncoding);

private:
	void										SetLineCharsetDetailsToDefault();
	void										SetLineEncodingDetailsToDefault();

protected:
	struct TParserCodingDetails
		{
		Versit::TVersitEncoding		iEncoding;
		TUint						iEncodingUid;
		Versit::TVersitCharSet		iCharSet;
		TUint						iCharSetUid;
		};
	
protected:
	// Default settings & internal flags
	TInt							iFlags;
	TParserCodingDetails			iDefaultCodingDetails;
	TParserCodingDetails			iCurrentPropertyCodingDetails;
	TBuf<KVersitMaxVersionLength>	iDefaultVersion;
	const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* iAutoDetectCharSets;

	// Member data relating to the current item being parsed
	HBufC*							iEntityName;
	CArrayPtr<CVersitParser>*		iArrayOfEntities;
	CArrayPtr<CParserProperty>*		iArrayOfProperties;
	CParserProperty*				iCurrentProperty;
	CLineReader*					iOwnedLineReader;
	CLineReader*					iLineReader;
	HBufC8*							iDecodedValue;
	CBufSeg*						iLargeDataBuf;

	// In memory buffers
	RWriteStream*					iWriteStream;

	// General utility class
	CVersitTlsData*					iStaticUtils;

	// Plug-in classes
	MVersitObserver*				iObserver;
	MVersitPlugIn*					iPlugIn;

private:
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
private:
	TInt iReserved1;
	TInt iReserved2;
	};

#include "versit.inl"

#endif
