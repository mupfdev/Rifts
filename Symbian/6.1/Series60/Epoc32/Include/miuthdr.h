// MIUTHDR.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#ifndef __MIUTHDR_H__
#define __MIUTHDR_H__

#if !defined (__S32STRM_H__)
#include <S32STRM.H>
#endif 

#if !defined (__BADESCA_H__)
#include <BADESCA.H>
#endif

#if !defined (__POP3CMDS_H__)
#include "POP3CMDS.H"
#endif

#if !defined (__MSVSTD_H__)
#include <MSVSTD.H>
#endif

#if !defined (__MSVIDS_H__)
#include <MSVIDS.H>			// KMsvNullIndexEntryId
#endif

#if !defined (__MIUTSTD_HRH__)
#include "MIUTSTD.HRH"			// KUidMsvEmailTextEntryValue
#endif


// IMail-specific stream type within an IMail file store for CImHeader
const TUid KUidMsgFileMimeHeader	= {0x1000160F};		// 268441103 decimal

// IMail-specific stream type within an IMail file store for CImMimeHeader
const TUid KUidMsgFileIMailHeader	= {0x100001D8};		// 268435928 decimal

const TUid KUidMsvEmailTextEntry			= {KUidMsvEmailTextEntryValue};
const TUid KUidMsvEmailHtmlEntry			= {KUidMsvEmailHtmlEntryValue};
const TUid KUidMsvEmailExternalBodyEntry	= {KUidMsvEmailExternalBodyEntryValue};

_LIT8(KMiutDateFormat, " %S, %2d %S %04d %02d:%02d:%02d ");
_LIT8(KMiutMonthNames, "JanFebMarAprMayJunJulAugSepOctNovDec");
_LIT8(KMiutDayNames, "MonTueWedThuFriSatSun");
_LIT8(KMiutTimeZoneNeg, "-%02d%02d");
_LIT8(KMiutTimeZonePos, "+%02d%02d");

_LIT8(KMiutBase64String, "Base64");
_LIT8(KMiutQPString, "quoted-printable");
_LIT8(KMiut7BitString, "7bit");
_LIT8(KMiut8BitString, "8bit");
_LIT8(KMiutBinaryString, "binary");
_LIT8(KMiutUUString, "uuencode");

_LIT8(KMiutWildcardBase64, "*base64*");
_LIT8(KMiutWildcardQP, "*quoted-printable*");
_LIT8(KMiutWildcard7Bit, "*7bit*");
_LIT8(KMiutWildcard8Bit, "*8bit*");
_LIT8(KMiutWildcardBinary, "*binary*");
_LIT8(KMiutWildcardUU, "*uu*");

#define KMiutEmptyString KNullDesC

_LIT(KMiutFormatString, "%S");
_LIT(KImEngineResourceFile, "\\system\\data\\imcm.rsc");

const TInt KMiutDateStringLength	= 32;
const TInt KCenturyThreshold		= 100;
const TInt KCenturyOffset			= 70;
const TInt KThisCentury				= 1900;	// as defined in 1998
const TInt KNextCentury				= 2000;


class CMsvStore;
class TMsvEntry;
class RMsvReadStream;
class RMsvWriteStream;


// Maximum size for descriptors stored in HBufC members of CImHeader = 1000 chars
const TInt KMaxImHeaderStringLength = 1000;
const TInt KMaxImMimeFieldLength	= 1000;
const TInt KImMailMaxBufferSize		= 1000;	// 1000 is defined by the SMTP spec as max space

enum TMsgOutboxBodyEncoding
	{
	EMsgOutboxDefault,
	EMsgOutboxNoAlgorithm,
	EMsgOutboxMIME,
	EMsgOutboxMHTMLAsMIME,
	EMsgOutboxMHTMLAlternativeAsMIME
	};

enum TImEncodingType 
	{
	EEncodingTypeUnknown,
	EEncodingTypeNone,
	EEncodingType7Bit,
	EEncodingType8Bit,		// ie lines still <1000 chars and terminated by CRLF
	EEncodingTypeBinary,	// ie any length of data, not terminated by CRLF
	EEncodingTypeQP,
	EEncodingTypeBASE64,
	EEncodingTypeUU
	};


// Class used for storing extracting information (to/from header)..
// regarding the encoding in an incoming email message header.
//----------------------------------------------------------------------------------------
class TImHeaderEncodingInfo
//----------------------------------------------------------------------------------------
	{
public:
	enum TFieldList { EFrom, EReplyTo, ETo, ECc, EBcc, ESubject};
	enum TEncodingType { EBase64, EQP, ENoEncoding, EUU};


public:
	IMPORT_C TImHeaderEncodingInfo();
	IMPORT_C TImHeaderEncodingInfo(const TImHeaderEncodingInfo& aFrom);

	IMPORT_C void ExternalizeL( RWriteStream& aWriteStream ) const;
	IMPORT_C void InternalizeL( RReadStream& aReadStream );

	inline void SetField(const TFieldList aField);
	inline TFieldList Field() const;

	inline void SetOffset(const TInt aOffset);
	inline TInt Offset() const;

	inline void SetLength(const TInt aLength);
	inline TInt Length() const;

	inline void SetCharsetUid(const TUint aUid);
	inline TUint CharsetUid() const;

	inline void SetEncodingType(const TDesC8& aChar);
	inline void SetEncodingType(const TEncodingType aType);
	inline  TEncodingType EncodingType() const;

	inline void SetArrayValue(const TInt aValue);
	inline  TInt ArrayValue() const;

	inline void SetAddSpace(const TBool atrueFalse);
	inline  TBool AddSpace() const;

	inline void SetEncodedLength(const TInt aLength);
	inline TInt EncodedLength() const;

private:
	TFieldList		iField; 
	TUint16			iOffset;
	TUint16			iLength;
	TEncodingType	iType;
	TUint16			iArrayValue;
	TBool	iAddSpace; // A space char needs adding between two adjoining 'encoded-words'
	TUint8	iEncodedLength; // This can be used to determine space needed for buffer.
	TUint	iCharsetUid; 

	};




const TUint16 KImHeaderVersion		= 2; // identifies which version of CImHeader has been stored in stream


class CImHeader : public CBase
	{
public:
	enum TReplyTo 
		{ 
		EOriginator, 
		ESender, 
		EAll,
		ERecipients
		};

	IMPORT_C static CImHeader* NewLC();
	IMPORT_C ~CImHeader();
	IMPORT_C void Reset();

	// streaming operations
	IMPORT_C void InternalizeL(RMsvReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aWriteStream) const;
	IMPORT_C void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C void StoreL  (CMsvStore& aMessageStore) const;
	IMPORT_C void StoreWithoutCommitL(CMsvStore& aMessageStore) const;

	// the bulk of the member functions are accessors & mutators so we can use
	// objects of the class as data repositories during the data-marshalling stage
	// of getting imail headers to/from the internet
	IMPORT_C const TPtrC Subject() const;
	IMPORT_C void SetSubjectL(const TDesC8& aSubject);

	// Internet message ID
	IMPORT_C const TPtrC8 ImMsgId() const;
	IMPORT_C void SetImMsgIdL(const TDesC8& aImMsgIdL);

	IMPORT_C const TPtrC From() const;
	IMPORT_C void SetFromL(const TDesC8& aFrom);

	IMPORT_C const TPtrC ReplyTo() const;
	IMPORT_C void SetReplyToL(const TDesC8& aReplyTo);

	IMPORT_C const TPtrC ReceiptAddress() const;
	IMPORT_C void SetReceiptAddressL(const TDesC8& aReceiptAddress);

	IMPORT_C const TUint Charset() const;
	IMPORT_C void SetCharset(const TUint aCharset);

#if defined (_UNICODE)
	IMPORT_C void SetFromL(const TDesC16& aFrom);
	IMPORT_C void SetReplyToL(const TDesC16& aReplyTo);
	IMPORT_C void SetReceiptAddressL(const TDesC16& aReceiptAddress);
	IMPORT_C void SetSubjectL(const TDesC16& aSubject);
#endif

	IMPORT_C TInt DataSize();

	inline const TUint RemoteSize() const;
	inline void SetRemoteSize(TUint aSize);

	inline const TUint16 Version() const;
	inline void SetVersion(TUint16 aVersion);

	// give const access to the recipient lists
	inline const CDesCArray& ToRecipients () const;
	inline const CDesCArray& CcRecipients () const;
	inline const CDesCArray& BccRecipients() const;
	
	// give non-const access to the recipient lists
	inline CDesCArray& ToRecipients () ;
	inline CDesCArray& CcRecipients () ;
	inline CDesCArray& BccRecipients() ;

	inline CArrayFix<TImHeaderEncodingInfo>& EncodingInfo() ;
	inline const CArrayFix<TImHeaderEncodingInfo>& EncodingInfo() const;

	IMPORT_C void AddEncodingInfoL(TImHeaderEncodingInfo& aInfo);

//-------------------------------------------------------------------------------------
//----------------------Used for forwarding/replying to an email ----------------------

	IMPORT_C const TPtrC8 ResentMsgId() const;
	IMPORT_C void SetResentMsgIdL( const TDesC8& );

	IMPORT_C const TPtrC ResentFrom() const;
	IMPORT_C void SetResentFromL( const TDesC& );

	// give const access to the recipient lists
	inline const CDesCArray& ResentToRecipients () const;
	inline const CDesCArray& ResentCcRecipients () const;
	inline const CDesCArray& ResentBccRecipients() const;

	// give non-const access to the recipient lists
	inline CDesCArray& ResentToRecipients ();
	inline CDesCArray& ResentCcRecipients ();
	inline CDesCArray& ResentBccRecipients();

	IMPORT_C const TPtrC8 InReplyTo() const;
	IMPORT_C void SetInReplyToL(const TDesC8&);

	IMPORT_C TInt CreateForwardL(CImHeader&, TDesC&);
	IMPORT_C TInt CreateReplyL(CImHeader&, TReplyTo, TDesC&);
	IMPORT_C void CreateReceiptL(CImHeader&, TDesC&);

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------

	// Body Encoding (charset) stored on a per message basis
	IMPORT_C const TMsgOutboxBodyEncoding BodyEncoding() const;
	IMPORT_C void SetBodyEncoding(TMsgOutboxBodyEncoding aMessageBodyEncoding);
private:
	CImHeader();
	void ConstructL();
	
	// these four functions keep the line count down as there are several instances
	// of streaming in/out HBufC objects.
	void ReadRecipientsL ( RReadStream&, CDesCArray* );
	void WriteRecipientsL( RWriteStream&, const CDesCArray* ) const;
	void FormatSubjectL(CImHeader&, TDesC&);

private:
	TUint16 iVersion;

	HBufC* iFrom;
	HBufC* iSubject;
	HBufC8* iImMsgId;
	HBufC* iReplyTo;
	HBufC* iReceipt;

	CDesCArray* iTo;
	CDesCArray* iCc;
	CDesCArray* iBcc;
	TUint iRemoteSize;

//-------------------------------------------------------------------------------------
//----------------------Used for forwarding/replying to an email ----------------------

	HBufC* iResentFrom;
	HBufC8* iResentMsgId;
 	CDesCArray* iResentTo;
	CDesCArray* iResentCc;
	CDesCArray* iResentBcc;
	HBufC8* iInReplyTo;

//-------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
	CArrayFix<TImHeaderEncodingInfo>* iEncodingInfo;
	TMsgOutboxBodyEncoding			iBodyEncoding;
	// The character set to be when sending message.
	// Overrides the charset passed in from the settings.
	TUint							i822HeaderCharset; 

	};

class TImRfc822DateField
	{
public:
	IMPORT_C TInt ParseDateField(const TDesC8& aRfc822DateField, TTime& rTime);
	IMPORT_C void SetDate(const TTime& aTimeDate, TDes8& rOutputLine);	// NB assumes that "Date: " string has already been inserted into  rOutputLine

private:
	TBool GetMonth( const TDesC8& name, TMonth& month );
	TBool GetTimezone( const TDesC8& name, TInt& minsOffset );
	};


enum TImEmailFolderType
	{
	EFolderTypeUnknown,
	EFolderTypeRelated,
	EFolderTypeMixed,
	EFolderTypeParallel,
	EFolderTypeAlternative,
	EFolderTypeDigest,
	EFolderTypeRFC822,
	EFolderTypePartial,
	EFolderTypeDirectory,
	EFolderTypeExternal
	};

enum TImDisconnectedOperationType
	{
	ENoDisconnectedOperations,
	EDisconnectedCreateOperation,
	EDisconnectedDeleteOperation,
	EDisconnectedChangeOperation,
	EDisconnectedCopyToOperation,
	EDisconnectedCopyFromOperation,
	EDisconnectedCopyWithinServiceOperation,
	EDisconnectedMoveToOperation,
	EDisconnectedMoveFromOperation,
	EDisconnectedMoveWithinServiceOperation,
	EDisconnectedSpecialOperation,
	EDisconnectedUnknownOperation,
	EDisconnectedMultipleOperation
	};

// Remote folder message count limited to TUint16 by using lower 16 bits of "iMtmData3".
// Note: The upper 16 bits of "iMtmData3" are not currently used by "TMsvEmailEntry".
const TUint KMsvRemoteFolderEntriesMask =		0x0000FFFF;

class TMsvEmailEntry : public TMsvEntry
	{
public: // Public member functions
	IMPORT_C TMsvEmailEntry();	// default constructor
	IMPORT_C TMsvEmailEntry(const TMsvEntry& aGenericEntry); 

	IMPORT_C TBool operator==(const TMsvEntry& aEntry) const;
	IMPORT_C TBool operator==(const TMsvEmailEntry& aEntry) const;

	IMPORT_C void GetIMAP4Flags(TBool& rUnread,TBool& rSeen,TBool& rAnswered,TBool& rFlagged,TBool& rDeleted,TBool& rDraft,TBool& rRecent);
	IMPORT_C void SetIMAP4Flags(TBool aUnread,TBool aSeen,TBool aAnswered,TBool aFlagged,TBool aDeleted,TBool aDraft,TBool aRecent);

	IMPORT_C void SetMessageFolderType(TImEmailFolderType aFolderType);
	IMPORT_C TImEmailFolderType MessageFolderType() const;

	IMPORT_C void SetDisconnectedOperation(TImDisconnectedOperationType aDisconnectedOperationType);
	IMPORT_C TImDisconnectedOperationType DisconnectedOperation() const;

	//
	inline void SetEncrypted(TBool aEncrypt);
	inline TBool Encrypted() const;
	//
	inline void SetSigned(TBool aSignature);
	inline TBool Signed() const;
	//
	inline TBool VCard() const;
	inline void SetVCard(TBool aVCard);
	//
	inline TBool VCalendar() const;
	inline void SetVCalendar(TBool aVCal);
	//
	inline TBool Receipt() const;
	inline void SetReceipt(TBool aReceipt);

	inline TBool MHTMLEmail() const;
	inline void SetMHTMLEmail(TBool aMhtml);

	inline TBool BodyTextComplete() const;
	inline void SetBodyTextComplete(TBool aFlag);

	//
	// IMAP4-specific flags
	//
	inline void SetUnreadIMAP4Flag(TBool aUnread);
	inline TBool UnreadIMAP4Flag() const;
	//
	inline void SetSeenIMAP4Flag(TBool aSeen);
	inline TBool SeenIMAP4Flag() const;
	//
	inline void SetAnsweredIMAP4Flag(TBool aAnswered);
	inline TBool AnsweredIMAP4Flag() const;
	//
	inline void SetFlaggedIMAP4Flag(TBool aFlagged);
	inline TBool FlaggedIMAP4Flag() const;
	//
	inline void SetDeletedIMAP4Flag(TBool aDeleted);
	inline TBool DeletedIMAP4Flag() const;
	//
	inline void SetDraftIMAP4Flag(TBool aDraft);
	inline TBool DraftIMAP4Flag() const;
	//
	inline void SetRecentIMAP4Flag(TBool aRecent);
	inline TBool RecentIMAP4Flag() const;
	//
	inline void SetMailbox(TBool aMailbox);
	inline TBool Mailbox() const;
	//
	inline TBool Orphan() const;
	inline void SetOrphan(TBool aOrphan);
	//
	inline void SetValidUID(TBool aValid);
	inline TBool ValidUID() const;
	//
	inline void SetSubscribed(TBool aSubscribed);
	inline TBool Subscribed() const;
	//
	inline void SetLocalSubscription(TBool aLocal);		// i.e. is subscription local, or remote
	inline TBool LocalSubscription() const;
	//
	inline void SetUID(TUint32 aUid);
	inline TUint32 UID() const;

	//
	inline TInt RemoteFolderEntries() const;
	inline void SetRemoteFolderEntries(TInt aEntries);

private:
	enum TMsvEmailEntryFlags
		{	
		KMsvEmailEntryClearFlag				=0x00,
		// Flags set on Message entries...
		KMsvEmailEntryEncryptedFlag			=0x00000001,
		KMsvEmailEntrySignedFlag			=0x00000002,
		KMsvEmailEntryReceiptFlag			=0x00000004,
		KMsvEmailEntryOrphanFlag			=0x00000008,

		// VCard and VCalendar entries may be set on folders or attachments
		KMsvEmailEntryVCardFlag				=0x00000010,
		KMsvEmailEntryVCalendarFlag			=0x00000020,

		// Message contains MHTML data
		KMsvEmailEntryMHTMLFlag				= 0x00000040,
		KMsvEmailEntryBodyTextCompleteFlag	= 0x00000080,

		KMsvEmailEntryNoDisconnectedOperations					= 0x00000000,
		KMsvEmailEntryDisconnectedCreateOperation				= 0x00000100,
		KMsvEmailEntryDisconnectedDeleteOperation				= 0x00000200,
		KMsvEmailEntryDisconnectedChangeOperation				= 0x00000300,
		KMsvEmailEntryDisconnectedCopyToOperation				= 0x00000400,
		KMsvEmailEntryDisconnectedCopyFromOperation				= 0x00000500,
		KMsvEmailEntryDisconnectedCopyWithinServiceOperation	= 0x00000600,
		KMsvEmailEntryDisconnectedMoveToOperation				= 0x00000700,
		KMsvEmailEntryDisconnectedMoveFromOperation				= 0x00000800,
		KMsvEmailEntryDisconnectedMoveWithinServiceOperation	= 0x00000900,
		KMsvEmailEntryDisconnectedSpecialOperation				= 0x00000A00,
		KMsvEmailEntryDisconnectedUnknownOperation				= 0x00000B00,
		KMsvEmailEntryDisconnectedMultipleOperation				= 0x00000C00,
		KMsvEmailEntryDisconnectedOperation						= 0x00000F00,

		// IMAP4-specific masks. Can be re-used by non-IMAP4 entries (eg POP3, SMTP)
		KMsvEmailEntryIMAP4SubscribedFlag	=0x00001000,
		KMsvEmailEntryIMAP4UnreadFlag		=0x00002000,
		KMsvEmailEntryIMAP4SeenFlag			=0x00004000,
		KMsvEmailEntryIMAP4AnsweredFlag		=0x00008000,	
		KMsvEmailEntryIMAP4FlaggedFlag		=0x00010000,	
		KMsvEmailEntryIMAP4DeletedFlag		=0x00020000,	
		KMsvEmailEntryIMAP4DraftFlag		=0x00040000,	
		KMsvEmailEntryIMAP4RecentFlag		=0x00080000,	
		KMsvEmailEntryIMAP4ValidUIDFlag		=0x00100000,
		KMsvEmailEntryIMAP4MailboxFlag		=0x00200000,
		KMsvEmailEntryIMAP4LocalSubFlag		=0x00400000,

		// MIME "multipart" types assigned to folders. 
		KMsvMimeFolderUnknownMask			=0x00000000,
		KMsvMimeFolderRelatedMask			=0x01000000,
		KMsvMimeFolderMixedMask				=0x02000000,
		KMsvMimeFolderAlternativeMask		=0x03000000,
		KMsvMimeFolderParallelMask			=0x04000000,
		KMsvMimeFolderDigestMask			=0x05000000,

		// MIME message types
		KMsvMimeFolderRFC822Mask			=0x06000000,
		KMsvMimeFolderPartialMask			=0x07000000,
		KMsvMimeFolderDirectoryMask			=0x08000000,	// for VCard, VCalendar types
		KMsvMimeFolderExternalMask			=0x09000000,
		KMsvMimeFolderMask					=0x0F000000
		};

	};

const TUint16 KImMimeHeaderVersion =		2; // identify which version of this class has been stored


class CImMimeHeader : public CBase
	{
public:
	IMPORT_C static CImMimeHeader* NewLC();
	IMPORT_C static CImMimeHeader* NewL();
	IMPORT_C ~CImMimeHeader();
	IMPORT_C void Reset();
	IMPORT_C TInt Size();	// number of header fields stored in object

	// streaming operations
	IMPORT_C void InternalizeL( RMsvReadStream& aReadStream );
	IMPORT_C void ExternalizeL( RMsvWriteStream& aWriteStream ) const;
	IMPORT_C void RestoreL( CMsvStore& aMessageStore );
	IMPORT_C void StoreL  ( CMsvStore& aMessageStore ) const;
	IMPORT_C void StoreWithoutCommitL(CMsvStore& aMessageStore) const;

	IMPORT_C void SetContentTypeL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 ContentType() const;

	IMPORT_C void SetContentSubTypeL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 ContentSubType() const;

	IMPORT_C void SetContentDispositionL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 ContentDisposition() const;

	IMPORT_C void SetContentDescriptionL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 ContentDescription() const;

	IMPORT_C void SetContentBaseL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 ContentBase() const;

	IMPORT_C void SetContentIDL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 ContentID() const;

	IMPORT_C void SetContentLocationL(const TDesC16& aPath);
	IMPORT_C const TPtrC16 ContentLocation() const;

	// IMAP-specific info describing relative location of entry w.r.t. parent Email message
	IMPORT_C void SetRelativePathL(const TDesC8& aPath);
	IMPORT_C const TPtrC8 RelativePath() const;

	IMPORT_C void SetContentTransferEncodingL(const TDesC8& aType);
	IMPORT_C const TImEncodingType ContentTransferEncoding() const;
	IMPORT_C const TImEncodingType ContentTransferEncoding(TDes8& rType) const;
	IMPORT_C const TPtrC8 GetContentTypeValue(const TDesC8& aContentTypeParameter) const;

	// inlines to access arrays
	inline const CDesC8Array& ContentTypeParams() const;
	inline const CDesC8Array& ContentDispositionParams() const;
	inline const CDesC8Array& XTypeParams() const;

	inline CDesC8Array& ContentTypeParams();
	inline CDesC8Array& ContentDispositionParams();
	inline CDesC8Array& XTypeParams();		// anything else that is in the header, but not recognised

	inline const TUint16 Version() const;
	inline void SetVersion( TUint16 aVersion );

	IMPORT_C void SetMimeCharset(const TUint aCharset);
	IMPORT_C const TUint MimeCharset() const;

private:
	CImMimeHeader();
	void ConstructL();
	TBool ArrayEntryExists(CDesCArray& aArray, TInt aField);

private:
	TUint16 iVersion;
	HBufC8* iRelativePath;
	HBufC8* iContentDescription;

	TImEncodingType iContentTransferEncoding;

	// MHTML parameters
	HBufC8* iContentBase;
	HBufC16* iContentLocation;
	HBufC8* iContentID;
	//
	HBufC8* iContentType;
	HBufC8* iContentSubType;
	HBufC8* iContentDisposition;
	//
	CDesC8Array* iContentTypeParams;			// zero or more "parameter"
	CDesC8Array* iContentDispositionParams;		// zero or more "parameters"
	CDesC8Array* iXTypeParams;					// zero or more X-Type "parameters"
	//
	TBuf<20> iContentTransferEncodingBuffer;	// must be big enough to store "quoted-printable" string

	// The uid value is always used in preference to the stored string.
	// Only when the uid is not set is the string used when sending.
	TUint iMimeCharset;	
	};



#include "miuthdr.inl"

#endif // #defined __MIUTHDR_H__
