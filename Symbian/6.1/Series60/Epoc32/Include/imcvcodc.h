// IMCVCODC.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//


#if !defined(__IMCVCODC_H__)
#define __IMCVCODC_H__

#include <s32buf.h>
#include <s32stor.h>
#include <txtrich.h>
#include <miutatch.h>
#include <miutconv.h>
#include <miuthdr.h>
#include <mentact.h>		// CMsgActive

#include "imcvdata.h"
#include "imcvtext.h"
#include "imutdll.h"

#define KBase64 _L("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=")
#define KCharFormat _L("%c")

 // Maximum length allowed for an 'encoded-word' rfc2047
const TInt KEncodedWordMaxLength = 75;

// All encoding information except data and charset name length. =?B?=?    => 7
const TInt KMaxEncodedInformationLength = 7;

// Length of the field name, eg "Subject: ". This may change as other fields are processed.  
const TInt KMaxHeaderFieldNameLength = 12;

const TInt KImCvFinished=(-1);
const TInt KImCvAdvance=(1);


// error states involved in sending attachments etc.
enum TIattErrorCode
	{
	KImAttNoError = 0,
	KImAttFinished = 1
	};


enum TImBodyConvAlgorithm
	{
	ENoAlgorithm,
	EQPEncode,
	EQPDecode,
	EBase64Encode,
	EBase64Decode,
	EUUEncode,
	EUUDecode
	};
	
// Used in CImSendConvert
enum TImSendEncoding 
	{ 
	ESendNoAlgorithm,
	ESendMimeAlgorithm
	};	

struct SAttachmentInfo
	{
	TInt iSize;
	TFileName iName;
	TFileName iPath;
	TBool iComplete;
	};

// Shared implementation code	
//----------------------------------------------------------------------------------------
class TImCodec
//----------------------------------------------------------------------------------------
	{
protected:
	// base64 and UU coding defines.
	enum EMaskValues{ ESixBitMask = 0x3F, EEightBitMask = 0xFF };
	enum EMaskShiftValues{ ESix = 6, EFour = 4, ETwo = 2, EZero = 0 };

public:
	virtual TInt Encode( const TDesC8& aSrcString, TDes8& rDestString)=0 ;
	virtual TBool Decode( const TDesC8& aInputLine, TDes8& rOutputLine)=0;

protected:
	// TImCodec();
	inline TBool IsDigit( TChar aChar );
	};


// Interface for sending file data.
//----------------------------------------------------------------------------------------
class TImFileCodec : public TImCodec
//----------------------------------------------------------------------------------------
	{
public:
	virtual TInt PrefixNextLineL( TDes8& rOutputLine, const TFileName& aName, TInt& rPaddingCount );
	virtual TInt PostfixNextLine( TDes8& rOutputLine, TInt& rPaddingCount );
	virtual void Initialise();

protected:
	TInt iPrefixState;
	TInt iPostfixState;
	};	

// Dummy, just copies
//----------------------------------------------------------------------------------------
class TImCodecNull :  public TImFileCodec
//----------------------------------------------------------------------------------------
	{
public:
	TInt Encode( const TDesC8& aSrcString, TDes8& rDestString);
	TBool Decode( const TDesC8& aInputLine, TDes8& rOutputLine);
	};
	
// Quoted-printable encoding/decoding

//----------------------------------------------------------------------------------------
class TImCodecQP : public TImFileCodec
//----------------------------------------------------------------------------------------
	{
public:
	IMPORT_C TImCodecQP();
	IMPORT_C TInt Encode( const TDesC8& aSrcString, TDes8& rDestString);
	IMPORT_C TBool Decode( const TDesC8& aInputLine, TDes8& rOutputLine);

	// Not to be used anymore..
	IMPORT_C TInt EncodeRichText( const TDesC8& aInputLine, TDes8& rOutputLine);
	IMPORT_C TInt DecodeRichText( const TDesC8& aSrcString, TDes& rDestString );

	// Functions which allow flexiblity. Can replace the '=' char or add characters..
	// to what is defined as 'plain.
	inline void AddPlainChar(const TDesC8&  aCharList );
	inline void AddEncodeChar(const TDesC8&  aCharList );
	inline void SetQPChar( TUint8 aChar);

	inline TUint8 ReplacementChar( TChar aControlChar );
	inline TBool IsPlain( TChar aChar );

private:
	TBool SmartBreak( TInt written, const TDesC8& pSource );
	inline TBool IsBreakable( TChar aChar);
	inline void AddSoftLineBreak(TDes8& aPtr, TInt& aPadding, TInt& aWritten);
	inline void AddSoftLineBreak(const TUint8* apEnd, TUint8* aPtr, TInt& aPadding, TInt& aWritten);

private:
	TUint8 iQPCharacter;
	TPtrC8 iPlainCharList;  
	TPtrC8 iEncodeCharList;  

	TInt iPaddingCount;
	};



// Base64 coding/decoding

//----------------------------------------------------------------------------------------
class TImCodecB64 : public TImFileCodec
//----------------------------------------------------------------------------------------
	{
private:
	// base64 coding defines
	enum{ EPadChar = 64 };

public:
	IMPORT_C TImCodecB64();
	IMPORT_C TInt Encode( const TDesC8& aSrcString, TDes8& rDestString);
	IMPORT_C TBool Decode( const TDesC8& aSrcString, TDes8& rDestString);
 	IMPORT_C void  Initialise();

private:
	TInt iShiftStored;
	TInt iMaskShiftStored;
	};


// UU coding/decoding

//----------------------------------------------------------------------------------------
class TImCodecUU : public TImFileCodec
//----------------------------------------------------------------------------------------
	{
private:
	// UU coding defines

	enum{ ESpace = 32, EBackQuote = 96 };

	enum TImBodyPostfix
		{
		EInvertedComma = 0,
		EEndString,
		EEndOfPostfix
		};

public:
	IMPORT_C TImCodecUU();
	IMPORT_C TInt Encode( const TDesC8& aSrcString, TDes8& rDestString );
	IMPORT_C TBool Decode( const TDesC8& aSrcString, TDes8& rDestString );

	TInt PrefixNextLineL( TDes8& rOutputLine, const TFileName& aName, TInt& rPaddingCount );
	TInt PostfixNextLine( TDes8& rOutputLine, TInt& rPaddingCount );
private:
	void AppendFilenameL( TDes8& rOutputLine, const TFileName& aName );
	
	};




// For converting a text string to/from encoded form
// Note: 'Word' here has special meaning derived from the one defined in rfc2047.
// It refers to one encoding instance.

//----------------------------------------------------------------------------------------
class CImConvertHeader : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	IMPORT_C static CImConvertHeader* NewL(CImConvertCharconv& aConverter);
	~CImConvertHeader();

	IMPORT_C void SetMessageType(TBool aIsMIME); 
	IMPORT_C void DecodeAllHeaderFieldsL(CImHeader& rHeader); 

	// Functions for decoding & converting descriptors

	IMPORT_C void DecodeNonMIMEHeaderFieldL(const TDesC8& aBufIn, TDes& rBufOut); 
	IMPORT_C void DecodeHeaderFieldL(const TDesC8& aBufIn, TDes& rBufOut); 
	IMPORT_C void DecodeHeaderFieldL(const TDesC16& aBufIn, TDes& rBufOut); 

	IMPORT_C void ConvertHeaderFieldL(const TDesC16& aBufIn, TDes8& rBufOut); 
	IMPORT_C void EncodeHeaderFieldL(const TDesC& aBufIn, TDes8& rBufOut, 
		const TUint aCharset, const TImHeaderEncodingInfo::TEncodingType aType);
	
	// Header needed for retrieving encoding information, used in Send code.
	IMPORT_C void EncodeHeaderFieldL(const TDesC& aBufIn, TDes8& rBufOut, 
			CArrayFix<TImHeaderEncodingInfo>* aInfoArray, TInt aState, TInt aArrayVal = 0);

	IMPORT_C TBool FindEncodedWord(TPtrC8& aData, TInt& aInit,TInt& rStart, TInt& rEnd);

	void Append(TDes& aBuffer, const TDesC8& aAddition);
	inline CImConvertCharconv& CharConv();	

private:
	void ConstructL();
	CImConvertHeader(CImConvertCharconv&);

	// Functions dealing only with single 'encoded-word's
	void EncodeWordL(const TDesC& aBufIn, TDes8& rBufOut, TImHeaderEncodingInfo& aInfo);
	TBool DecodeWordL(const TDesC8& aBufIn, TDes& rBufOut, TInt rRemainder); 

	void DecodeRecipientListL( CDesCArray& aArray);
	void DecodeFieldL(const TDesC& aField);

	TBool EncodeWordDataL(const TDesC& aBufIn, TDes8& rBufOut, TImHeaderEncodingInfo& aInfo);
	TInt AddEncodedWordInfo(const TDesC8& aBufIn, TDes8& rBufOut, 
							TImHeaderEncodingInfo& aInfo, TDesC8& aCharsetName);

	TBool IsAscii( TUint aChar ) const;
	TBool ExtractTextToEncode(const TDesC& aBufIn, TInt& rStart, TInt& rEnd);
	void Insert(TDes8& aBuffer, const TDesC16& aInsert);

private:
	TImHeaderEncodingInfo iEncodingInfo;
	CImConvertCharconv& iCharConv;

	// Get access to QP/ Base64 encoding/decoding functions
	TImCodecB64	 iB64Codec;
	TImCodecQP	 iQPCodec;

	// Need in the narrow build, to check if possible to convert to/from
	// the machines character set.
	TUint iCharacterSetId; 

	CImHeader* iHeader;	

	// Converted static variables used in EncodeWordL()
	HBufC8* iBuf;
	TInt	iRecurse;
	TBool	isMIMEMessageHeader;

	};


#include "imcvcodc.inl"

#endif

