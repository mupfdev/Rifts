// IMCVSEND.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined(__IMCVSEND_H__)
#define __IMCVSEND_H__

#include <s32mem.h>
#include <badesca.h>
#include <miutatch.h>
#include <miuthdr.h>
#include <mentact.h>
#include <msvuids.h>
#include <msventry.h>
#include <smtpset.h>

#include "imutdll.h"
#include "imcvtext.h"
#include "imcvcodc.h"
#include "imcvutil.h"

class CImSendEmail;
class CImEmailTraverser;
class CImSendPlainEmail;
class CImSendMimeEmail;
class CImSendMimeHeader;
class CImSendRfc822Header;
class CImSendRichText;
class CImSendFile;


enum TMimeHeaderType { EMainMimeHeader, EPartMimeHeader };


const TImHeaderEncodingInfo::TEncodingType	
			KDefaultSendingHeaderEncoding = TImHeaderEncodingInfo::EBase64;
const TUint KDefaultSendingCharset		  = KCharacterSetIdentifierIso88591;
const TInt KArrayAllocationNumber		  =6;

// Length of text to extract when encoding using B64 or UU
const TInt KDecodeLineLength = 45;


// External interface to imcvsend.

//----------------------------------------------------------------------------------------
class CImSendMessage : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	IMPORT_C static CImSendMessage* NewL(CMsvServerEntry& aServerEntry);
	IMPORT_C static CImSendMessage* NewLC(CMsvServerEntry& aServerEntry);

	IMPORT_C ~CImSendMessage( );

	// Returns KImcvFinished when done.
	IMPORT_C TInt NextLineL( TDes8& rOutputLine, TInt& rPaddingCount );
	IMPORT_C void InitialiseL(TMsvId aMessageId, const TTime aTimeDate,
						const TDesC& aDomainName, const TImEmailTransformingInfo& aInfo, 
						const TImSMTPSendCopyToSelf aCopyToSelf);
	IMPORT_C void InitialiseL(TMsvId aMessageId, TImSendMethod aSendMethod, const TTime aTimeDate,
		const TDesC& aDomainName, TUint aCharset, const TImSMTPSendCopyToSelf aCopyToSelf);
	IMPORT_C TInt HeaderSize();
	IMPORT_C TInt BodySizeL();
	IMPORT_C void Reset();

private:

	CImSendMessage(CMsvServerEntry& aServerEntry);
	void ConstructL();
	void SetSendMethodL(TImSendMethod aSendMethod);

private:
	CMsvServerEntry& iServerEntry;

	CImSendEmail* iSendEmail;
	TMsvId iMessageId;
	TTime	iTimeDate;

	TBool	iLogFileExists;	// Logging.
	RFile	iLogFile;
	};



// This class is a VIRTUAL base class from which email protocol classes are derived. 
// gives derived classes  ability to traverse the entry structure and extract  
// information from entries.
//  It determines which entry to set the current context to and which entry will follow,
//  and knows when the end of the message has been reached.

//----------------------------------------------------------------------------------------
class CImSendEmail : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	CImSendEmail(CMsvServerEntry& aServerEntry);
	~CImSendEmail( );

	virtual TInt NextLineL(TDes8& rOutputLine, TInt& rPaddingCount) = 0;
	virtual void Reset();

	virtual void InitialiseL( const TTime aTimeDate, const TDesC& aDomainName, 
								const TImSMTPSendCopyToSelf aCopyToSelf,
								const TImEmailTransformingInfo& aTransformingInfo);
	virtual TInt HeaderSize();
	virtual TInt BodySizeL();

protected:
	virtual void ConstructL(); // Call base class Construct in the derived function
	TBool InitBodyObjectL(TMsvEntry& rEntry);
	TBool InitAttachmentObjectL(TMsvEntry& rEntry);
	TImFileCodec& Encoder(TImEncodingType aType);

protected:
	CMsvServerEntry&	iServerEntry;

	// Encoding classes including a default.
	TImCodecNull		iNULLEncoder;
	TImCodecUU			iUUEncoder;
	TImCodecB64			iB64Encoder;
	TImCodecQP			iQPEncoder;

	// Objects common to all email types

	CImSendFile*					iSendFile;
	CImSendRfc822Header*			iRfc822Header;
	CImSendRichText*				iSendRichText;

	CImConvertCharconv*			iCharConv;
	CCnvCharacterSetConverter*	iCharacterConverter;
	CImConvertHeader*			iHeaderConverter;

	TInt						iState;
	CImEmailTraverser*			iEmailTraverser;
	CImHeader*					iHeader;

	TInt						iEmbeddedEmail;

	TTime						iTimeDate;
	TPtrC						iDomainName;

	TUint						iAlgorithm; // used for encoding a body/attachment.
	TImEmailTransformingInfo	iDefaultTransformingInfo;	
	};


// Traverses the TMsvEntry structure of email message, used by CImSendEmail.
// Complex email messages have a hierarchical structure with more than one LEVEL.

//----------------------------------------------------------------------------------------
class CImEmailTraverser : CBase 
//----------------------------------------------------------------------------------------
	{
public:
	static CImEmailTraverser* NewL( CMsvServerEntry& aServerEntry );
	~CImEmailTraverser();
	void InitialiseL(TMsvId aId);

	TBool				NextEntryL(TMsvEntry& rEntry);
	TBool				DownLevelL();
	TBool				UpLevelL();
	inline void			SetBaseEntry();

	inline TBool				IsBaseLevel() const;
	inline CMsvEntrySelection&	CurrentList() const;
	inline const TMsvEntry&		ThisEntry() const;	

private:
	CImEmailTraverser( CMsvServerEntry& aServerEntry );
	void ConstructL();
	void Reset();

	inline TBool	LevelExists() const;
	inline TBool	DeleteCurrentList();
	inline void		AddList(CMsvEntrySelection&	children);
	inline TInt		CurrentEntry();

private:
	TMsvId				iBaseId;  // ID of the Top level email entry.
	CMsvServerEntry&	iServerEntry;

	// Storing the child entries in a hierarchical entry structure.
	// List and count arrays
	CArrayFixFlat<CMsvEntrySelection*>*	iSelectionList; 
	CArrayFixFlat<TInt>					iCurrentEntryList; 
	};


// This class is derived from CImSendEmail and encapsulates the non-MIME protocol. 
// The class only knows about the entry which is currently in its context, which is 
// determined by it base class. 

//----------------------------------------------------------------------------------------
class CImSendPlainEmail : public CImSendEmail
//----------------------------------------------------------------------------------------
	{
private:
	enum TSendState	{
		ERfc822Header = 0,
		EBody,
		EAttachmentFile,
		};

public:
	static CImSendPlainEmail* NewL(CMsvServerEntry& aServerEntry );
	static CImSendPlainEmail* NewLC(CMsvServerEntry& aServerEntry );
	TInt NextLineL( TDes8& rOutputLine, TInt& rPaddingCount );

private:
	CImSendPlainEmail(CMsvServerEntry& aServerEntry);
	TBool ChangeStateL();
	};



//	It encapsulates the MIME protocol and controls what needs to be sent for a specific
//  entry type, this being the type of entry that is currently in context. 
//  Only knows about the entry which is currently in its context, which is determined by 
//  it base class. Creates and looks after the boundary strings. 

//----------------------------------------------------------------------------------------
class CImSendMimeEmail : public CImSendEmail
//----------------------------------------------------------------------------------------
	{
public:
	// From RFC 1521, (Boundaries) must be no longer than 70 characters.
	enum{KBoundaryStringLength = 55};

private:
	enum TSendState	{
		ERfc822Header = 0,
		EMimeMainHeader,
		EMimeText,
		EBoundary,
		EMimePartHeader,
		EBody,
		EAttachmentFile,
		EEndBoundary,
		ELineAfterEndBoundary,
		};

public:
	static CImSendMimeEmail* NewL(CMsvServerEntry& aServerEntry );
	static CImSendMimeEmail* NewLC(CMsvServerEntry& aServerEntry );
	~CImSendMimeEmail( );

	TInt NextLineL( TDes8& rOutputLine, TInt& rPaddingCount );

	void Reset();
	TInt HeaderSize();
	TBool InitBodyObjectL(TMsvEntry& rEntry);

private:
	CImSendMimeEmail(CMsvServerEntry& aServerEntry );
	void ConstructL();
	TBool ChangeStateL();

	void CreateBoundaryL();
	void DeleteBoundary();

	inline void Boundary(TDes8& rOutputLine);
	inline TPtrC8 Boundary();
	inline TPtrC8 SetBoundaryL(TBool aMultipart);
	inline TInt SendBoundaryLine( TDes8& rOutputLine, TInt& rPaddingCount);
	inline TBool ValidBoundaryChar( TUint aCharacter );
	
	void InitEmbeddedEmailL();

	TBool CreateMimeHeaderL();
	void InitMimeHeaderL( TMsvEntry& aEntry, TPtrC8& rBoundary, TPtrC& rFilename);
	void InitSendMimeHeaderL(TMsvEntry& aEntry, TMimeHeaderType aMimeHeaderType	);

	inline TBool Next(TMsvEntry& rEntry);
	inline TBool Down(TMsvEntry& rEntry);
	inline void GetNextEntryL(TMsvEntry& rEntry);
	inline TBool CheckForEmbeddedEmailL(const TMsvEntry& aEntry) const;
	inline TBool CheckForMultipartEmailL( TMsvEntry& rEntry, TImEmailFolderType& aFolder);

private:
	CDesC8ArrayFlat*		iBoundaryArray;
	CImSendMimeHeader*		iSendMimeHeader;
	CImMimeHeader*			iMimeHeader;
	TBool					iTextDisplayed;
	TInt64					iRandSeed;
	};



// 	This class creates the main message header lines which conform to the rfc822 specification. 
//  The code is currently implemented in Imcvsend.cpp.

//----------------------------------------------------------------------------------------
class CImSendRfc822Header : public CBase
//----------------------------------------------------------------------------------------
	{
private:
	// Defines the state order of the CImSendRfc822Header object... 
	// !! DO NOT CHANGE THE ORDER !!

	enum TSendState	{
		EFrom=0, // 0
		EReplyTo,
		ETo,
		ECc,
		EBcc,
		ESubject,
		EDate,
		EReturnReceiptTo,
		EPriority,
		EImportance,
		EMessageID,
		EXMailer,
		EEndOfRfc822Header
		};

public:
	static CImSendRfc822Header* NewLC( RFs& anFs, CImConvertHeader& aConverter );
	static CImSendRfc822Header* NewL( RFs& anFs, CImConvertHeader& aConverter  );
	~CImSendRfc822Header();

	TInt NextLineL( TDes8& rOutputLine, TInt& rPaddingCount );
	TBool InitialiseL( const TTime aTimeDate , const TDesC& aDomainName, 
					CMsvServerEntry& aServerEntry, const TMsvPriority aPriority, 
					const TImSMTPSendCopyToSelf aCopyToSelf,
					TImEmailTransformingInfo& rInfo);

	TInt DoRecipientsL( TDes8& rOutputLine, const TPtrC8& aPrompt, CDesCArray& aList );
	void PrepareBufferL( const TPtrC8& aPrompt, const TDesC& aData);
	void PrepareBufferL( const TPtrC8& aPrompt, const TDesC8& aData);
	TInt SendOutput( TDes8& rOutputLine );
	TInt PriorityL(TDes8& rOutputLine);

	TUint HeaderCharset() const;
	void SetMessageIdL();
	void Reset();
	TInt Size() const;
	inline const TImEmailTransformingInfo& TransformingInfo() const;

private:
	CImSendRfc822Header( RFs& anFs, CImConvertHeader& aConverter );
	void ConstructL();

	inline TInt FromL( TDes8& rOutputLine );
	inline TInt ReplyToL( TDes8& rOutputLine );
	inline TInt ToL( TDes8& rOutputLine );
	inline TInt CcL( TDes8& rOutputLine );
	inline TInt BccL( TDes8& rOutputLine );
	inline TInt SubjectL( TDes8& rOutputLine );
	inline TInt MessageIdL( TDes8& rOutputLine );
	inline TInt XMailerL( TDes8& rOutputLine );
	inline TInt ReturnReceiptsL(TDes8& rOutputLine);

	TBool ValidEmailAddress(const TPtrC8& aData, const TInt aPos, TInt& rStart, TInt& rEnd);
	void EncodeHeaderFieldL(const TDesC& aBufIn, TDes8& rBufOut, const TInt aArrayVal);
	void AddCopyToSelfL(TImSMTPSendCopyToSelf aCopyToSelf, CDesCArray& aList);

private:
	RFs&			iFs;
	CImHeader*		iHeader;
	TInt			iState;

	HBufC8*			iOutputBuffer;
	const TUint8*	ipOutputBuffer;

	TImRfc822DateField	iRfc822Date;
	TTime				iTimeDate;
	TMsvPriority		iPriority;

	// resource strings
	HBufC*		iProductName;
	HBufC*		iDomainName;

	CImConvertHeader&   iHeaderConverter;
	CImcvUtils*			iImcvUtils;
	CDesC8Array*		iPriorityFields;
	CDesC8Array*		iReceiptFields;

	TUint			iHeaderCharset;
	TImEncodingType iHeaderEncoding;

	TImSMTPSendCopyToSelf		iCopyToSelf;
	TImEmailTransformingInfo	iTransformingInfo;	
	};


// This class encapsulates the MIME header protocol. 
// The header strings are created from a text resource of standard MIME tokens
// Info obtained from cImMimeHeader object. 

//----------------------------------------------------------------------------------------
class CImSendMimeHeader : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	enum TMimeHeaderState		
		{
		EMimeVersion = 0, // Main only
		EContentLanguage, // Main only
		EDescription,	 // Part only
		EContentType,
		EBoundaryString,
		EDisposition,
		ETransferEncoding,
		ECRLF,
		EEndOfMimeHeader
		};

	enum TImSplitLine
		{	
		EFirstLine = 0,
		ESecondLine
		};
public:
	static CImSendMimeHeader* NewL(CImConvertHeader& aConverter, TMimeHeaderType aType);
	static CImSendMimeHeader* NewLC(CImConvertHeader& aConverter, TMimeHeaderType aType);
	~CImSendMimeHeader();

	TInt NextLine( TDes8& rOutputLine, TInt& rPaddingCount );
	void InitialiseL( CImMimeHeader& aMimeHeader, const TPtrC aFilename, 
					const TPtrC8& aBoundary,  const TBool aEmbedded, 
					const TMsvEntry& aEntry,  const TImEmailTransformingInfo& aInfo);
	inline TInt BlankLine( TDes8& rOutputLine ) const;
	inline TInt MimeVersion( TDes8& rOutputLine ) const;
	inline TBool ContentType( TDes8& rOutputLine) const;
	inline TBool TransferEncoding(TDes8& rOutputLine) const;
	inline TInt ContentLanguage( TDes8& rOutputLine ) const;
	inline TBool Description( TDes8& rOutputLine) const;
	inline TBool Disposition( TDes8& rOutputLine, TInt& rAdvance);
	inline const TPtrC8 EncodingType() const;

	TUint CharsetUid() const;
	void SetCharsetUidL(const TUint aId);
	TPtrC8 GetCharsetString() const;

	inline TInt Boundary(TDes8& rOutputLine) const;
	void AppendFilenameL( TDes8& rOutputLine ) const;
	TInt Size() const;

private:
	CImSendMimeHeader( CImConvertHeader& aConverter, TMimeHeaderType aType);

private:
	CImConvertHeader&	iConverter;
	TInt				iHeaderState;
	CImMimeHeader*		iMimeHeader;

	// Info needed when filling in header details
	TImEncodingType		iAlgorithm;
	HBufC8*				iCharsetString;
	TPtrC8				iBoundaryString;
	TFileName			iFilename;
	TMsvEntry			iEntry;

	TInt				iLine;
	TBool				iIsMultipart;
	TMimeHeaderType		iMimeHeaderType;

	TUint			iHeaderCharset;
	TImEncodingType iHeaderEncodingType;

	TUint			iCharsetUid;
	TImEncodingType iEncodingType;
	};


// 	This class sends the text from a richtext object. 
//  The text can be encoded using any of the available encoding techniques

//----------------------------------------------------------------------------------------
class CImSendRichText : public CBase
//----------------------------------------------------------------------------------------
	{
public:
	static CImSendRichText* NewL( CImConvertCharconv& aConv );
	static CImSendRichText* NewLC( CImConvertCharconv& aConv );

	TBool InitialiseL( CMsvServerEntry& aServerEntry,  TImCodec& anEncoder,
										    TImEncodingType aType, TUint aCharset);
	TInt NextLineL( TDes8& rOutputLine, TInt& rPaddingCount );

	~CImSendRichText();
	inline TInt Size() const;

private:
	CImSendRichText(CImConvertCharconv& aConv);
	void ConstructL();

	TInt NoEncodeNextLineL( TDes8& rOutputLine, TInt& rPaddingCount );
	TInt RemoveControlCharacters( const TDesC& aInputLine, TDes& rOutputLine, TInt& rPaddingCount );

	TInt EncodeNextLineL( TDes8& rOutputLine, TInt& rPaddingCount );
	TInt EncodeQPNextLineL( TDes8& rOutputLine, TInt& rPaddingCount );

	TInt ConvertNextLineL( const TDesC& aInput, TDes8& rOutput);
	TBool SmartBreak( TInt written, const TDesC& pSource );
	TBool SmartBreak( TInt written, const TUint8* pSource, TInt aMaxLength );
	void InitialiseBodyL();

	inline TBool IsBreakable( TChar aChar ) const;
	inline TBool IsEOL(TChar aChar) const;
	inline TUint8 ReplacementChar(TChar aControlChar) const;
	inline TBool IsPlain(TChar aChar) const;
	inline int ConvertLineBreaks( TDes& aSource, TBool aLineBreak) const;

private:
	CRichText*		iRichText;
	CImConvertCharconv& iConverter;
	TBool	iPreparedToConvert;

	TImCodec*		iEncoder;

	CParaFormatLayer* iParaLayer;
	CCharFormatLayer* iCharLayer;

	TInt			iMaxLength;
	TBool			iUseRichText;
	TInt			iBodySize;
	TInt			iPos;

	TImEncodingType	iBodyEncoding;
	HBufC8*			iLeftOver;
	};


//	This class creates lines to send from files, 
//  the files can be encoded using any of the available encoding techniques.

//----------------------------------------------------------------------------------------
class CImSendFile : public CBase
//----------------------------------------------------------------------------------------
	{
private:
	enum TImSplitLine
		{
		EFirstLine = 0,
		ESecondLine
		};

	// Length of source text buffer used when encoding and outputting.
	// Taking into account that the length may increase.

	enum TImAttachmentSend
		{
		ENextFile = 0,
		EPrefixLines,
		EEncodeFile,
		EPostfixLines,
		EEndOfAttachments,
		ECloseDelimiter,
		ECRLFLine,
		EEnd
		};
public:
	static CImSendFile* NewLC(RFs& anFs, CImConvertCharconv& aCharConv);
	static CImSendFile* NewL(RFs& anFs, CImConvertCharconv& aCharConv);
	~CImSendFile();

	void InitialiseL(  CMsvServerEntry& aServerEntry, TImFileCodec& anEncoder);

	TInt NextLineL( TDes8& rOutputLine, TInt& rPaddingCount );

	inline TInt BlankLine( TDes8& rOutputLine, TInt& rPaddingCount );
    const TFileName& Filename() const;
	static TFileName& Filename( CMsvServerEntry& aEntry, SAttachmentInfo& rInfo);
	inline TInt Size() const;

private:
	CImSendFile(RFs& anFs, CImConvertCharconv& aCharConv);

private:
	const RFs&			iFs;

	TImFileCodec* iEncoder;  // Either B64 or UU encoder or none
	CImConvertCharconv& iConverter;

	SAttachmentInfo		iAttachmentInfo;
	TImAttachmentFile*	iAttachmentFile;
	TBuf8<KDecodeLineLength> iSourceLine;
	CImMimeHeader*		iMimeHeader; // Passed in.

	TInt	iAttachmentState;  // so dont change there order
	TInt	iFileIndex;		// The following are init'ed in the Ctor list
	TInt	iBodyHeaderState;

	TInt	iPrefixState;
	TInt	iPostfixState;
	};


//----------------------------------------------------------------------------------------
class CImCalculateMsgSize : public CMsgActive
//----------------------------------------------------------------------------------------
	{
public:
	IMPORT_C static CImCalculateMsgSize* NewL(RFs &anFs,CMsvServerEntry& aServerEntry);
	IMPORT_C ~CImCalculateMsgSize();
	IMPORT_C void StartL(TRequestStatus& aStatus,TMsvId aMsvId, 
			TImSendMethod aAlgorithm, TTime& aTimeDate, 
			const TDesC& aDomainName, const TUint aCharset);

	inline TInt MessageSize() const;	// total size of Email - once active object has completed
	inline void Progress(TInt& aBytes, TInt& aTotal);	// current info on size of Email

private:
	void DoRunL();
	void DoCancel();
private:
	CImCalculateMsgSize(RFs &anFs,CMsvServerEntry& aServerEntry);
	void ConstructL();
	void Reset();
private:
	RFs& iFs;
	CMsvServerEntry& iServerEntry;
	TMsvId iMsvId;

	TInt iSize;
	TInt iTotal;

	CImSendMessage* iSendMsg;
	TBuf8<KImMailMaxBufferSize> iMailString;
	TBool iFinished;
#if defined (_DEBUG)
	RFile iFile;
	TBool iFileOpen;
#endif
	};


#include "imcvsend.inl"

#endif
