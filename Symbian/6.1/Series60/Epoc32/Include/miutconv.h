// MIUTCONV.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//

#ifndef __MIUTCONV_H__
#define __MIUTCONV_H__

#include <e32base.h>


#if !defined (__CHARCONV_H_)
#include <charconv.h>
#endif

#if !defined (__MIUTHDR_H__)
#include "MIUTHDR.H"		
#endif

#if !defined (__UTF_H_)
#include <utf.h>
#endif

// IMail-specific stream type within an IMail file store for TImEmailTransformingInfo
//
const TUint KUidMsvCharsetNone				= {0x10003C7F};		// 268450943
const TUid KUidMsgFileTransformingInfo		= {0x100094A5};		// 268473509
const TUid KUidMiutSystemDefaultCharset		= {0x10009418};		// 268473368
const TUid KUidMiutOverrideCharset			= {0x10009419};		// 268473369

_LIT8(KMiutUndisplayableChar, "?");

enum TImSendMethod
	{ 
	ESendAsSimpleEmail,
	ESendAsMimeEmail
	};	


// Information to be used when sending an email message.
// Relating to how parts are encoded and converted.
//
class TImEmailTransformingInfo
	{
public:
    IMPORT_C TImEmailTransformingInfo& operator=(const TImEmailTransformingInfo& aInfo);
    IMPORT_C TBool operator==(const TImEmailTransformingInfo& aInfo);
	
	// streaming operations
	IMPORT_C void ExternalizeL( RWriteStream& aWriteStream ) const;
	IMPORT_C void InternalizeL( RReadStream& aReadStream );
	IMPORT_C void StoreL( CMsvStore& aStore ) const;
	IMPORT_C void RestoreL( CMsvStore& aStore );

	// Setting functions
	IMPORT_C void SetToDefault(const TImSendMethod aMethod);
	IMPORT_C void SetSendMethod(const TImSendMethod aMethod);
	IMPORT_C TImSendMethod SendMethod() const;

	IMPORT_C void SetHeaderEncodingQ();
	IMPORT_C void SetHeaderEncodingB();
	IMPORT_C void SetBodyTextEncoding(TImEncodingType aType);
	IMPORT_C void SetHTMLEncoding(TImEncodingType aType);
	IMPORT_C void SetAttachmentEncoding(TImEncodingType aType);
	
	IMPORT_C void SetHeaderAndBodyCharset(TUint aCharset);
	IMPORT_C void SetHeaderCharset(TUint aCharset);
	IMPORT_C void SetBodyTextCharset(TUint aCharset);
	IMPORT_C void SetHTMLCharset(TUint aCharset);

	// Accessor functions
	IMPORT_C TImEncodingType HeaderEncoding() const;
	IMPORT_C TImEncodingType BodyTextEncoding() const;
	IMPORT_C TImEncodingType HTMLEncoding() const;
	IMPORT_C TImEncodingType AttachmentEncoding() const;
	
	IMPORT_C TUint HeaderCharset() const;
	IMPORT_C TUint BodyTextCharset() const;
	IMPORT_C TUint HTMLCharset() const;

private:
	void SetHeaderEncoding(TImEncodingType aType);

private:
	TImEncodingType	iHeaderEncoding;	
	TImEncodingType	iBodyEncoding;	
	TImEncodingType	iHTMLEncoding;	
	TImEncodingType	iAttachmentEncoding;	

	TUint	iHeaderCharset;	
	TUint	iBodyCharset;	
	TUint	iHTMLCharset;	
	TUint	iTextAttachmentCharset;	

	TImSendMethod iSendMethod;
	};


// Default Sending Charset/Encoding Values
const TImEncodingType KDefaultMIMEHeaderEncoding	=	EEncodingTypeBASE64;		// MIME
const TImEncodingType KDefaultMIMEBodyTextEncoding	=	EEncodingTypeQP;
const TImEncodingType KDefaultMIMEHTMLEncoding		=	EEncodingTypeBASE64;
const TImEncodingType KDefaultMIMEAttachmentEncoding=	EEncodingTypeBASE64;

#define KDefaultPlainCharset		KCharacterSetIdentifierIso88591

const TImEncodingType	KDefaultPlainHeaderEncoding		=	EEncodingTypeNone;	// Non-MIME or Plain
const TImEncodingType	KDefaultPlainBodyTextEncoding	=	EEncodingTypeNone;
const TImEncodingType KDefaultPlainAttachmentEncoding	=	EEncodingTypeUU;




// Wrapper class for CHARCONV.
// 'Our' charset dependant on build, UNICODE or CodePage 1252.
//
class CImConvertCharconv : public CBase
	{
public:	
	IMPORT_C static CImConvertCharconv* NewL(CCnvCharacterSetConverter& aConverter, RFs& anFs);
	~CImConvertCharconv();

	// MUST call prepare function first.
	IMPORT_C TInt ConvertToOurCharsetL( const TDesC8& aBufIn, TDes& rBufOut, 
										TInt& rNumUnconvertedChars, 
										TInt& rIndexOfFirstUnconvertedChar);
	IMPORT_C TInt ConvertFromOurCharsetL(const TDesC& aBufIn, TDes8& rBufOut, 
										 TInt& rNumUnconvertedChars,
										 TInt& rIndexOfFirstUnconvertedChar);

	// MUST be called prior to calling above two functions.
	IMPORT_C TInt PrepareToConvertToFromOurCharsetL(const TUint aUid);

	IMPORT_C TUint GetMimeCharsetUidL(const TDesC8& aBufIn) const;
	IMPORT_C HBufC8* GetMimeCharsetTextStringL(const TUint& aUid) const;
	IMPORT_C TUint DefaultCharset() const;
	IMPORT_C TUint SystemDefaultCharset() const;

	static TInt StraightCopy( const TDesC8& aBufIn, TDes& rBufOut);
	static TInt StraightCopy( const TDesC& aBufIn, TDes8& rBufOut);
private:
	void ConstructL();
	CImConvertCharconv(CCnvCharacterSetConverter& aConverter, RFs& anFs);
	TBool CharsetAvailable(const TUint aUid);
	void SetSystemDefaultCharsetL();

private:
	CCnvCharacterSetConverter& iConverter;
	CArrayFix<CCnvCharacterSetConverter::SCharacterSet>* iCharsetsAvailable; 

	RFs& iFs;
	TUint iCharsetUid;
	TUint iSystemDefaultCharset;		// Value obtained from .ini file
	};

#endif
