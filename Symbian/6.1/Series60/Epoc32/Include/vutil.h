// VUTIL.H
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//
#ifndef __VUTIL_H__
#define __VUTIL_H__

// System includes
#ifndef __E32BASE_H__
#include <e32base.h>
#endif
#ifndef __F32FILE_H__
#include <f32file.h>
#endif
#ifndef __CHARCONV_H__
#include <charconv.h>
#endif


class Versit
	{
public:
	enum TVersitEncoding
		{
		ENoEncoding,
		EQuotedPrintableEncoding,
		EBase64Encoding,

		// Used internally - not to be used by versit clients
		EEightBitEncoding
		};

	/**
	  * Versit-specific character set identifiers.
	  *
	  * These are used in the Versit API to represent foreign (non-Unicode)
	  * character set encodings for vCard and vCalendar properties.
	  * 
	  * @since 5.1
	  */
	enum TVersitCharSet
		{
		EUnknownCharSet,
		EUSAsciiCharSet,	/** ASCII (7-bit).*/
		EUTF8CharSet,		/** UTF-8 Unicode transformation format (really an encoding of the unicode char set - 8 bit).*/
		EUTF7CharSet,		/** UTF-7 Unicode transformation format (really an encoding of the unicode char set - 7 bit).*/
		EISO88591CharSet,	/** ISO 8859-1 (8-bit)*/
		EISO88592CharSet,	/** ISO 8859-2 (8-bit)*/
		EISO88594CharSet,	/** ISO 8859-4 (8-bit)*/
		EISO88595CharSet,	/** ISO 8859-5 (8-bit)*/
		EISO88597CharSet,	/** ISO 8859-7 (8-bit)*/
		EISO88599CharSet,	/** ISO 8859-9 (8-bit)*/
		EISO88593CharSet,	/** ISO 8859-3 (8-bit)*/
		EISO885910CharSet,	/** ISO 8859-10 (8-bit)*/
		EGB231280CharSet,	/** GB 2312*/
		EGBKCharSet,		/** GBK*/
		EBIG5CharSet,		/** Big 5*/
		EISO2022JPCharSet,	/** ISO-2022-JP*/
		EEUCJPCharSet,		/** EUC-JP*/
		EShiftJISCharSet,
		EJISCharSet,		/** JIS Encoding*/
		EFirstCharSet=EUSAsciiCharSet,	/** Must be first Character Set */
		ELastCharSet=EJISCharSet	/** Must be last Character Set */
		};

	class TEncodingAndCharset
		{
	public:
		inline TEncodingAndCharset(TVersitEncoding aEncoding,TUint aCharSetId) :iEncoding(aEncoding), iCharSetId(aCharSetId) {}
	public:
		TVersitEncoding iEncoding;
		TUint iCharSetId;
		CCnvCharacterSetConverter* iConverter;
		};
	};

class CVersitUnicodeUtils : public CBase
	{
public:
	IMPORT_C ~CVersitUnicodeUtils();
	IMPORT_C HBufC8* NarrowL(const TDesC& aDesC);
	IMPORT_C HBufC8* NarrowLC(const TDesC& aDesC);
	IMPORT_C HBufC* WidenL(const TDesC8& aDesC8);
	IMPORT_C HBufC* WidenLC(const TDesC8& aDesC8);
	IMPORT_C void CreateConverterL();
	CCnvCharacterSetConverter::TAvailability SetCurrentCharSetL(TUint aCharacterSet);

public:
	inline CCnvCharacterSetConverter& CharacterSetConverter() const;
	inline TUint ConvertStandardNameL(const TDesC8& aStandardNameOfCharacterSet);
	inline HBufC8* StandardNameL(TUint aCharSetId);
	TUint AutoDetectCharSetL(const TDesC8& aSample,const CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* aAutoDetectCharSets);

private:
	RFs iFsSession;
	CCnvCharacterSetConverter* iUnicodeConverter;
	TBool iFsConnected;
	TUint iCurrentConverterCharSet;
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* iCharSetsAvailable;
	};


inline CCnvCharacterSetConverter& CVersitUnicodeUtils::CharacterSetConverter() const
	{
	return *iUnicodeConverter;
	}
inline TUint CVersitUnicodeUtils::ConvertStandardNameL(const TDesC8& aStandardNameOfCharacterSet)
	{
	return iUnicodeConverter->ConvertStandardNameOfCharacterSetToIdentifierL(aStandardNameOfCharacterSet,iFsSession);
	}
inline HBufC8* CVersitUnicodeUtils::StandardNameL(TUint aCharSetId)
	{
	return iUnicodeConverter->ConvertCharacterSetIdentifierToStandardNameL(aCharSetId,iFsSession);
	}

#endif
