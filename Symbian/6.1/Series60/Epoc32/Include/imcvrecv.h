//****************************************************************************************
// IMCVRECV.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//****************************************************************************************

#if !defined (__IMCVRECV_H__)
#define __IMCVRECV_H__

#if !defined (__S32MEM_H__)
#include <s32mem.h>
#endif

#if !defined (__BADESCA_H__)
#include <BADESCA.H> // required for CBufSeg
#endif

// Oyster includes
#if !defined(__MSVSTD_H__)
#include <msvstd.h>
#endif

#if !defined(__MSVENTRY_H__)
#include <msventry.h>
#endif

#if !defined(__MSVSTORE_H__)
#include <msvstore.h>
#endif

#if !defined(__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif

#if !defined(__MSVIDS_H__)
#include <MSVIDS.H>
#endif

#include <miutatch.h>
#include <miutlog.h>
#include "imcvcodc.h"
#include "imcvtext.h"
#include "imutdll.h"

class CImHeader;
class CRichText;
class CMimeParser;
class CImRecvConvert;
class RFs;
class TImConvert;
class TImAttachmentFile;
class CImcvUtils;

const TInt KHeaderBufferLength = 100;

// Max filename length
const TInt MaxMimeParameterValueLength = 256;

const TInt KConversionRemainderLength=20;

//boundary stuff
const TInt KBoundaryNotFound	=0;
const TInt KBoundaryFound		=1;
const TInt KBoundaryError		=2;


struct TParentDetails
	{
	TInt	iSize;
	TBool	iAttachment;
	TBool	iMHTML;
	};

//----------------------------------------------------------------------------------------
class CRfc822Token : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	enum THeaderPart { EUnknown, ENotFinished, EFrom, EReplyTo, ETo, ECc, EBcc, ESubject, EDate, EMessageId, EPriority, EReturnReceiptTo, EEndOfHeader };
	THeaderPart iHeaderPart;
	TBool iLastToken;
	TBool iFirstLine;
	TBool i822FieldsExist;

	IMPORT_C static CRfc822Token* NewLC();
	IMPORT_C void Reset();
	inline HBufC8* OutputLine();
	IMPORT_C void ParseNextLineL( const TDesC8& aSourceLine );
	IMPORT_C ~CRfc822Token();
	inline TBool LastToken();

	inline void SetImRecvConvert( CImRecvConvert* );
private:
	TBool MatchAndRemoveL( const TDesC8& );
	TBool PriorityAndReceiptsMatchAndRemoveL(THeaderPart aPriority);

	CRfc822Token();
	void ConstructL();

private:
	TBuf8<KMaxIMailHeaderReadLineLength+1> iInputLine;
	TBuf8<KMaxIMailHeaderReadLineLength+1> iBufferedInput;
	HBufC8* iOutputLine;
	CImRecvConvert* iImRecvConvert;
	};


//----------------------------------------------------------------------------------------
class CImRecvConvert : public CBase
//----------------------------------------------------------------------------------------	
	{
friend class CMimeParser;
public:
	IMPORT_C static CImRecvConvert* NewLC( RFs& anFs, CMsvServerEntry* aServerEntry, 
												TUid aMsgType, TMsvId aEmailServiceId);
	IMPORT_C static CImRecvConvert* NewL( RFs& anFs, CMsvServerEntry* aServerEntry,
												TUid aMsgType, TMsvId aEmailServiceId);
	IMPORT_C ~CImRecvConvert();

	IMPORT_C void ResetL();
	IMPORT_C void ResetForHeadersL();

	inline void SetAttachmentPathL(const TDesC& aFullPath);	// attachment path, if not set then IMCV will reject attachments
	inline void SetMsvId(TMsvId aId);

	IMPORT_C TInt ParseNextField(const TDesC8& aSourceLine);
	IMPORT_C void MessageCompleteL();
	IMPORT_C void MessageCompleteL(TMsvEmailEntry aEmailEntry);
	IMPORT_C TMsvEmailEntry MessageEntryDetailsL();

	enum TValidEntryType {EUnknownEntry, EMessageEntry, EFolderEntry, EAttachmentEntry, ETextEntry, EHtmlEntry};
	enum TImEntryStreamSaveSettings
		{
		KStoreBodyText					= 0x00000001,
		KStore822Header					= KStoreBodyText << 1,		//0x00000002
		KStoreMIMEHeader				= KStore822Header << 1,	//0x00000004
		};

	inline const TTime Date() const;	// return RFC822 date
	inline const TMsvPriority Priority() const;
	inline void SaveAllAttachments(TBool aSave);
	inline const TInt ReceiveError() const;
	inline CMsvServerEntry& ServerEntry();
	inline const CImHeader& Header() const;
	inline const TBool ValidCompleteHeader() const;
	inline const TMsvId EntryId() const;	
	inline TBool NotFinishedRfc822Header();
	inline CImConvertCharconv& CharacterConverter();

private:
	CImRecvConvert(RFs& anFs, CMsvServerEntry* aServerEntry, 
							TUid aMsgType, TMsvId aEmailServiceId);
	void ConstructL(RFs& anFs);

	void ParseNextLineL(const TDesC8& aSourceLine);
	void ParseBodyLineL(const TDesC8& aSourceLine);
	void ParseMimeLineL(const TDesC8& aSourceLine);
	void EndOfHeaderProcessingL();
	void EndOfHeaderMIMEProcessingL();
	TBool CreateNonMIMEFolderEntryL(TMsvId aCurrentId);
	void DecodeAndStoreLineL(const TDesC8& aSourceLine);

	void ParseRecipientListL(CDesCArray& aRecipientList);
	void PrepareDecoder();

	void WriteToBodyL(const TDesC8& aText, TBool aBlankLine=EFalse);
	void WriteToBodyL(const TDesC16& aText);

	void AddFileExtension();
	void ExtractFilename(TLex& aLex, TDes& rFileName);
	void ReplaceInvalidCharacters(TDes& rFileName);
	
	TBool CheckUUEStartL(const TDesC8& aSourceLine);

	// returns numeric value of text up to next delimiter
	TInt Value(const TUint8*&);
	void Whitespace(const TUint8*&);
	TBool LineIsAllWhitespace();	

	TBool CreateAttachmentL();
	void WriteToAttachmentL(const TDesC8& text);
	void CloseAttachmentFileL();

	// Message Entry specific functions
	void ResetForNewEntryL(TValidEntryType entryType);
	void ResetForNonMimeEntryL();
	void MoveUpFromFolderEntryL();
	void MoveToParentEntryL();
	void UpdateMultipartDataL();

	TBool StoreEntryDataL();

	void StoreEntryStreamsL();
	void StoreEntryStreamsL(TInt aSettings);
	void Store822HeaderL(CMsvStore& aStore, TBool& aCommit);
	void StoreMIMEHeaderL(CMsvStore& aStore, TBool& aCommit);
	void StoreBodyTextL(CMsvStore& aStore, TBool& aCommit);


	void CreateEntryL();
	void Logging(const TDesC8& aString1, const TDesC8& aString2);
	void StoreMessageEntryDetails();

private:
	enum { KNoPart = 0, KParentPart, KMultiPart };
	TInt iEmailPart;
	TMsvId iCurrentMultipartFolderEntryId;

	TBool iMessageEntryCalled;
	TBool iReceivingHeadersOnly;
	TInt iReceiveError; // indicates if any anomalies were observed whilst the message was received
	TInt iLeaveError; // keeps any errors that have caused a leave (ie Out of memory, Corrupt file, Server error)

	TMsvId iRootEntryId;
	TMsvId iTopMessagePart;

	TImAttachmentFile iAttachmentFile;	// attachment file object
	CMsvServerEntry* iServerEntry;
	TUid iNewMsgType;

	CRfc822Token* iRfc822Token;

	TValidEntryType iDefaultEntryType;
	TValidEntryType iEntryType;

	TMsvEmailEntry* iEmailEntry;
	CImHeader* iOutputHeader;
	CParaFormatLayer* iParaLayer;
	CCharFormatLayer* iCharLayer;
	CRichText* iOutputBody;
	
	CImConvertCharconv* iCharConv;
	CCnvCharacterSetConverter* iConverter;
	TBool iPreparedToConvert;
	
	TBool iMIMEPart_822Header;	
	TInt iEmptyHeaderSize;
	TImBodyConvAlgorithm iAlgorithm;

	TBool iCommitLine;	
	TBool iFinalLine;	
	TBool iPrepared;
	TBool iFinishedHeader;
	TBool iNotFinishedRfc822Header;
	TBool iNewNonMIMEBodyPart;
	TBool iFirstBoundaryReached;

	CCnvCharacterSetConverter* iCharacterConverter;
	CImConvertHeader* iHeaderConverter;

	TImRfc822DateField iRfc822Date;

	RFs* iFsSession;  

	TBool iSkipData;
	TBool iEncounteredLineEndingInCarriageReturn;

	TBool iCurrentPartIsRichText;	//indicates if current body part is RichText, set on every Close Attachment()
	TImCodecQP iQPCodec;
	TImCodecB64 iB64Codec;
	TImCodecUU iUUCodec;
	TPtrC8 iThisLine;
	
	HBufC* iRemovedAttachmentTag;		// resource text which is put into the body in place of a removed MIME attachment
	HBufC* iRetainedAttachmentTag;		// resource text which is put into the body next to a retained MIME attachment
	HBufC* iDefaultAttachmentName;		// used when no name found	
	HBufC* iAttachmentFullPath;			// full path to current message file

	TBool iSavingAttachments;			// Turn on/off saving of attachments

	TBuf8<KMaxBoundaryTextLength> iSeekBoundary;
	
	TInt iGlobalIndent;
	TInt iPreviousLineLength;
	TInt iPreviousTrailingWhitespace;
	TChar iLastChar;
	TInt iLongestLine;
	TBool iNewEntry;

	TImAttachmentFileState iAttachmentFileState;
	TUint32 iEntryDataSize;

	TBool	iLogFileExists;
	RFile	iLogFile;
	TLex8	iLineLex;
	TTime   iTimeDate;

	//priorities   //vk
	TInt iPriority;		//{1..5}
	TInt iXPriority;   // {1..5} 1,2-high, 3-normal, 4,5-low
	TBuf8<KMaxPriorityTextLength> iPrecedence;  //   {bulk-low, list-normal,first class,special delivery-0}
	TBuf8<KMaxPriorityTextLength> iImportance;  // {high, low, normal}
	TMsvPriority iImPriority;

	TMsvId	iEmailServiceId;
	TBool	iPopulateMessage;
	CImcvUtils* iImcvUtils;

	TBuf8<KConversionRemainderLength> iLeftOver;

	TMsvId	iSavedEntryId;
	CArrayFixFlat<TParentDetails>* iParent;
	// Logging
	CImLog*					iImcvLog;

public:
	TFileName iAttachmentName;
	CMimeParser* iMimeParser;
private:
	TBool	iRelatedAttachments;
	};


//----------------------------------------------------------------------------------------
class CMimeParser : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	IMPORT_C static CMimeParser* NewLC(CImRecvConvert& aImRecvConvert);
	IMPORT_C static CMimeParser* NewL(CImRecvConvert& aImRecvConvert);
	IMPORT_C ~CMimeParser();
	void Reset();
	void ResetForNewEntry();
	void ParseLineL(const TDesC8& aSourceLine);

	void SetBoundaryL(const TDesC8& aBoundaryText);
	TBool IsBoundary(const TDesC8& aSourceLine);
	void RemoveBoundary();
	
	inline void StoreMimeHeaderL(CMsvStore& entryStore);
	inline void StoreMimeHeaderWithoutCommitL(CMsvStore& entryStore);
	inline void RestoreMimeHeaderL(CMsvStore& entryStore);

	inline TImEncodingType ContentEncoding();
	inline TMimeContentType ContentType();
	TPtrC8 ContentSubType() const;
	TUint CurrentCharsetL() const;

	inline const TBool MessageIsMime() const;
	inline const TBool IsTerminatingBoundary() const;
	inline const TBool BoundaryExists() const;
	inline const TBool BoundaryFound() const;
	inline const TInt MimeHeaderSize() const;
	inline const TInt ReceiveError() const;
	inline const TDesC& ContentDescription() const;
	inline const TPtrC ContentLocation() const;
	inline const TPtrC8 ContentId() const;
	inline const TPtrC8 ContentDisposition() const;
	inline TBool IsMessageDigest();

	const TBool VCard() const;
	const TBool VCalendar() const;
	const TImEmailFolderType MessageFolderType() const;
	void SetMessageFolderType(TImEmailFolderType aFolderType);
	const TBool StartPart() const;
	void RestoreMimeParserL(CMsvStore& entryStore);
	void ExtractParameterInfoL(const TDesC8& aTag, TDes16& rBuffer);	
	void ExtractParameterInfoL(const TDesC8& aTag, TDes8& rBuffer);	
	TBool MimeFieldsExist() const;
	void ResetMimeFieldsExist();
	void DoMultipartTypeForNonMIMEL();

#if defined (_DEBUG)
	inline TLex8& Lex() {return iLex;};
#endif

private:
	CMimeParser(CImRecvConvert& aImRecvConvert);
	void ConstructL();

	// String scanning functions
	TBool IsSpecialChar(const TUint8 aChar);
	TBool MatchAndRemoveToken(const TDesC8& aToken);

	// MIME token recognition functions
	void DoMimeVersion();
	void DoContentTypeL();
	void DoContentLocationL();
	void DoContentBaseL();
	void DoContentIdL();
	void DoEncodingL();
	void DoDescriptionL();
	void DoDispositionL();

	// MIME Content-Type type recognition functions
	void DoTextTypeL();
	void DoMultipartTypeL();
	void DoMessageTypeL();
	void DoAttachmentTypeL();

	// Will be moved to MIUT, but for now ..
	const TPtrC8 GetContentTypeValue(const TDesC8& aContentTypeParameter) const;

	TBool ParseRfc2047ParameterInfoL( const TDesC8& aTag, TDes& rBuffer, TInt aOffset );
	TBool ParseRfc2231ParameterInfoL( const TDesC8& aTag, TDes& rBuffer, TInt aOffset );
	TBool DecodeRfc2231ParameterInfoL( TDes8& aInput, TDes& rBufOut, 
											TPtrC8 aCharset/*, TPtrC8 aLanguage*/);
	TPtrC8 ExtractParameterString(TLexMark8& rMark);

private:
	CImRecvConvert& iImRecvConvert;
	
	CImMimeHeader* iMimeHeader;
	TInt iEmptyMimeHeaderSize;
	
	TBool isMime;
	TBool iCorrectMimeVersion;
	TImEncodingType iContentEncoding;
	TMimeContentType iContentType;
	TFileName iContentDescription;
	TBool iVCard;
	TBool iVCalendar;
	TBool iStartPart;
	TImEmailFolderType iMessageFolderType;
	TUint iCharset;
	TUint iDefaultCharset;
	HBufC8* iStartId;

	// Boundary stuff
	CDesC8ArrayFlat* iBoundaryText;
	TInt iBoundaryIndex;
	TInt iBoundaryLength;
	TBool iTerminatingBoundary;
	TBool iBoundaryFound;
	TInt iReceiveError; // Indicates if any anomalies were observed whilst the message was received
						// Can be accessed via the inline ReceiveError()
	TPtrC8 iTestLine;

	HBufC8* iMimeHeaderLine;
	TLexMark8 iMark;
	TLex8 iLex;
	TLex8 iTestLex;	
	TBool isMessageDigest;
	TBool iMimeFieldsExist;

	};

#include "imcvrecv.inl"

#endif 
