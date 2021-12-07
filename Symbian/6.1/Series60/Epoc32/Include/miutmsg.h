// MIUTMSG.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#ifndef __MIUTMSG_H__
#define __MIUTMSG_H__

#include <msvstd.h>
#include <msvapi.h>			// TMsvEntry, CMsvOperation etc
#include <mentact.h>		// CMsgActive
#include "miuthdr.h"		// CImHeader, CImMimeHeader
#include <txtrich.h>		// CRichText etc
#include "miutdef.h"		// CImHeader, CImMimeHeader
#include <mtmdef.h>
#include "miutatch.h"
#include "smtpset.h"

#include <barsc.h>		// RResourceFile
#include <conarc.h>
#include <conlist.h>

#include <txtmrtsr.h>

//Content-Transfer-Encoding: types
_LIT8(KMimeQuotedPrintable, " quoted-printable");
_LIT8(KMimeApplOctet, " application/octet-stream");
_LIT8(KMime7Bit, " 7-bit");
_LIT8(KMimeBase64, " base64");
_LIT8(KMimeMime, "MIME*");
// Content-Disposition: types
_LIT8(KMimeInline, "inline");
_LIT8(KMimeAttachment, "attachment");
// Content-Type: types
_LIT8(KMimeMultipart, "multipart");
_LIT8(KMimeText, "text");
_LIT8(KMimeImage, "image");
_LIT8(KMimeAudio, "audio");
_LIT8(KMimeVideo, "video");
_LIT8(KMimeApplication, "application");
_LIT8(KMimeMessage, "message");
// Content-Type: Multipart types
_LIT8(KMimeMixed, "mixed");
_LIT8(KMimeRelated, "related");
_LIT8(KMimeAlternative, "alternative");
_LIT8(KMimeEncrypted, "encrypted");
_LIT8(KMimeParallel, "parallel");
_LIT8(KMimeDigest, "digest");
_LIT8(KMimeSigned, "signed");
// Content-Type: Text types
_LIT8(KMimeHtml, "html");
_LIT8(KMimePlain, "plain");
_LIT8(KMimeDirectory, "directory");
// Content-Type: Message types
_LIT8(KMimePartial, "partial");
_LIT8(KMimeExternal, "external-body");
_LIT8(KMimeRfc822, "rfc822");
// Content-Type: Directory types
_LIT8(KMimeProfile, "profile");
_LIT(KMimeVCardExtension, ".vcf");
_LIT8(KMimeVCalender, "vcalendar");
// Content-Type: Image, Audio, Video, Application types
_LIT8(KMimeBmp, "bmp");
_LIT8(KMimeGif, "gif");
_LIT8(KMimeJpeg, "jpeg");
_LIT8(KMimeTiff, "tiff");
_LIT8(KMimeWav, "wav");
_LIT8(KMimeZip, "x-gzip");
_LIT(KMimeHtmlExtension, ".html");
_LIT(KMiutMsgDefaultHtmlFileName, "attachment.html");

class CImHtmlConverter;


class TImAttachmentInfo
	{
public:
	TFileName iFullName;
	TInt32 iSize;
	TMsvId iId;
	TBool iComplete;
	};

class TImCreateMessageOptions
	{
public:
	TMsvPartList		iMsvPartList;
	TMsvEmailTypeList	iMsvEmailTypeList;
	TUid				iMessageType;
	};

// Mixin provides interface to Browser control to resolve MHTML URIs.

class MImURITranslator
	{
public:
	virtual void FindUniversalResourceIdentifierL(TMsvId aMessageId, const TDesC& rBase, const TDesC& rURI, TRequestStatus &aStatus) = 0;
	virtual HBufC* GetUniversalResourceIdentifierL(TMsvId& aLinkedEntryId, TBool& aFileFound) const = 0;
	};

class CImMhtmlUriResolver;
class CImRemoveMessagePart;
class CImStoreMessagePart;

class CImEmailMessage : public CMsgActive , public MImURITranslator
	{
public:
	enum TImEmailEntryType
		{
		EThisMessageOnly,
		EThisMessageAndEmbeddedMessages  // i.e messages with in a message
		};
	enum TImAttachmentType
		{
		EAllAttachments=0,	// all attachment files contained within this message (but not inside messages within this message)
		EVCards,
		EVCalendars,
		EVEntries,			// ie VCards or VCalendars (or both)
		EEncrypted,
		ESigned,
		ESecure				// ie Encrypted or signed (or both)
		//.. add new items here
		};
public:
	IMPORT_C static CImEmailMessage* NewL(CMsvEntry& aServerEntry);
	IMPORT_C static CImEmailMessage* NewLC(CMsvEntry& aServerEntry);
	IMPORT_C ~CImEmailMessage();

	IMPORT_C void GetAttachmentsListL(TRequestStatus& aStatus, TMsvId aMessageId, TImAttachmentType aAttachmentType,TImEmailEntryType aEntryType);

	IMPORT_C void FindFirstHTMLPageL(TMsvId aMessageId, TRequestStatus& aStatus);

	IMPORT_C const CMsvEntrySelection& Selection() const;	// return selection
	IMPORT_C const CArrayFixFlat<TImAttachmentInfo>& AttachmentSelection() const;	// return selection

	IMPORT_C const TDesC8& ProgressL() const;

	IMPORT_C void GetBodyTextL(TRequestStatus& aStatus, TMsvId aMessageId, TImEmailEntryType aEntryType, CRichText& rRichText,CParaFormatLayer& aParaLayer,CCharFormatLayer& aCharLayer);
	void GetBodyTextL(TMsvId aMessageId, TImEmailEntryType aEntryType, CRichText& rRichText,CParaFormatLayer& aParaLayer,CCharFormatLayer& aCharLayer);
	void DoGetBodyTextInitL(TMsvId aMessageId, TImEmailEntryType aEntryType, CRichText& rRichText,CParaFormatLayer& aParaLayer, CCharFormatLayer& aCharLayer);

	IMPORT_C virtual void FindUniversalResourceIdentifierL(TMsvId aMessageId, const TDesC& rBase, const TDesC& rURI, TRequestStatus &aStatus);
	IMPORT_C virtual HBufC* GetUniversalResourceIdentifierL(TMsvId& aLinkedEntryId, TBool& aFileFound) const;

	IMPORT_C void AddAttachmentL(TMsvId aMessageId, const TDesC& aAttachmentFullName, TRequestStatus& aStatus);
	IMPORT_C void AddMessageAsAttachmentL(TMsvId aMessageId, TMsvId aAttachmentMessageId, TRequestStatus &aStatus);
	IMPORT_C void AddRelatedPartL(TMsvId aMessageId, const TDesC& aAttachmentFullName, TRequestStatus& aStatus, TMsvId aRelatedPartId, const TDesC8& aContentId);
	IMPORT_C void DeleteAttachmentL(TMsvId aMessageId, TMsvId aAttachmentId, TRequestStatus& aStatus);
	IMPORT_C void DeleteAttachedMessageL(TMsvId aMessageId, TMsvId aAttachedMessageId, TRequestStatus& aStatus);
	IMPORT_C void StoreBodyTextL(TMsvId aMessageId, CRichText& aRichText, TRequestStatus& aStatus);
	IMPORT_C void GetMessageDigestEntriesL(TRequestStatus& aStatus, TMsvId aMessageId);
private:
	void DoRunL();
	void DoCancel();
	CImEmailMessage(CMsvEntry& aEntry);
	void ConstructL();
	void DoComplete(TInt&);
	void DoStateL();

	void Start(TRequestStatus& aStatus);
	void StartL();

	void Reset();
	void ChangeMessageContextL();
	void CompareChildrenAndPopulateSelL();
	void AttachmentInfoL();
	void AssembleBodyTextL();
	void CheckAndInitialiseL(TMsvId aMessageId);
	
	void AppendAttachmentL();
	TBool MessageDigestEntry();
	TBool HandleDifferentFolderTypesL();
	void GetTextForAlternateFolderL();
	void GetTextForRelatedFolderL();

	enum TImEmailMessageStates
		{
		EIdle=0,
		ETextForThisMsg,
		ETextForMsgDigest,
		EAttachmentsForThisMsg,
		EAttachmentsForMsgDigest,
		EMsgDigestEntries,
		EResolveURI,
		EStoreMessagePart,
		ERemoveMessagePart,
		EFinished
		};
	CMsvEntry& iClientEntry;
	CMsvEntrySelection* iCompleteSel;
	CMsvEntrySelection* iResultSel;

	CRichText* iRichText;
	CParaFormatLayer* iParaLayer;
	CCharFormatLayer* iCharLayer;

	CArrayFixFlat<TImAttachmentInfo>* iAttachmentList;
	TMsvId iParentMsgId;			// the Id passed into Getxxx() function representing the 'parent' message ID
	TImEmailMessageStates iState;
	TImAttachmentType iAttachmentType;
	TMsvEmailEntry iEntry;
	CImMhtmlUriResolver* iUriResolver;
	TBool iUriFileFound;
	CImStoreMessagePart* iStoreMessagePart;
	CImRemoveMessagePart* iRemoveMessagePart;
	TPckgBuf<TMsvId>	iProgress;
	TImEmailEntryType iEntryType;
	TBool iIsAMHTMLmessage;
	};

class CImRemoveMessagePart : public CMsvOperation
	{
public:
	static CImRemoveMessagePart* DeleteAttachmentL(TRequestStatus &aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId, TMsvId aAttachmentId);
	static CImRemoveMessagePart* DeleteAttachedMessageL(TRequestStatus &aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId, TMsvId aAttachedMessageId);
	~CImRemoveMessagePart();
	const TDesC8& FinalProgress();
	void DoCancel();
	void RunL();
	const TDesC8& ProgressL();		// returns NULL until operation completed - then returns MessageId
private:
	CImRemoveMessagePart(TRequestStatus& aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId);
	void ConstructL(TMsvId aAttachmentId);
	void ErrorRecovery(TInt aError);
	void SelectNextStateL();					// selects next state to go to
	void ChangeStateL();					// initiates the next state operation
	void SelectAndChangeToNextStateL();
	void RequestComplete(TInt aError);
	void Recover();							// leave message in a 'good' state

	void CheckAttachmentParentTypeL();
	void MoveOtherEntryToParentOfFolderL();
	void DeleteAttachmentEntryL();
	void DeleteFolderEntryL();
	void CompleteRemoveMessagePartL();
private:
	enum TImRemoveMessagePartState
		{
		ECheckAttachmentParentType,
		EMoveOtherEntryToParentOfFolder,
		EDeleteAttachmentEntry,
		EDeleteFolderEntry,
		ECompleteRemoveMessagePart,
		EFinished
		};
	CMsvEntry&			iMsvEntry;
	CMsvOperation*		iMsvOperation;

	CMsvEntrySelection*	iMessageEntrySelection;
	CImEmailMessage*	iEmailMessage;

	TInt				iState;
	TPckgBuf<TMsvId>	iDataMember;
	TMsvId				iMessageId;
	TMsvId				iFolderToDeleteId;
	TInt				iAttachmentSize;
	TMsvId				iAttachmentId;
	TMsvId				iEntryToMoveId;
	};

class CImStoreMessagePart : public CMsvOperation
	{
public:
	static CImStoreMessagePart* AddAttachmentL(TRequestStatus &aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId, const TDesC& aAttachmentFullName);
	static CImStoreMessagePart* AddMessageAsAttachmentL(TRequestStatus &aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId, TMsvId aAttachmentMessageId);
	static CImStoreMessagePart* AddRelatedPartL(TRequestStatus &aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId, const TDesC& aAttachmentFullName, TMsvId aRelatedPartId, const TDesC8& aContentId);
	static CImStoreMessagePart* StoreBodyTextL(TRequestStatus& aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId, CRichText& aRichText);
	~CImStoreMessagePart();
	const TDesC8& FinalProgress();
	void DoCancel();
	void RunL();
	const TDesC8& ProgressL();
private:
	CImStoreMessagePart(TRequestStatus& aStatus, CMsvEntry& aMsvEntry, TMsvId aMessageId);
	void ConstructL();
	void ConstructL(const TDesC& aAttachmentFullName);
	void ConstructL(TMsvId aAttachmentMessageId);
	void ConstructL(const TDesC& aAttachmentFullName, TMsvId aRelatedPartId, const TDesC8& aContentId);
	void ConstructL(CRichText& aRichText);
	void ErrorRecovery(TInt error);
	void SelectNextStateL();				// selects next state to go to
	void ChangeStateL();					// initiates the next state operation
	void SelectAndChangeToNextStateL();
	void RequestComplete(TInt aError);
	void Recover();

	const TBool HTMLMessage() const;
	void SetHTMLMessage(TBool aFlag);
	const TBool MultipartMixedExists() const;
	void SetMultipartMixedExists(TBool aFlag);
	const TBool MultipartMixedCreated() const;
	void SetMultipartMixedCreated(TBool aFlag);
	const TBool MultipartAlternativeExists() const;
	void SetMultipartAlternativeExists(TBool aFlag);
	const TBool MultipartAlternativeCreated() const;
	void SetMultipartAlternativeCreated(TBool aFlag);
	const TBool MultipartRelatedExists() const;
	void SetMultipartRelatedExists(TBool aFlag);
	const TBool MultipartRelatedCreated() const;
	void SetMultipartRelatedCreated(TBool aFlag);
	const TBool TextPartExists() const;
	void SetTextPartExists(TBool aFlag);
	const TBool TextPartCreated() const;
	void SetTextPartCreated(TBool aFlag);
	const TBool AttachmentEntryCreated() const;
	void SetAttachmentEntryCreated(TBool aFlag);

	void FindMultipartRelatedFolderL();
	void CheckForSubfolderL();
	void CreateAttachmentEntryL();
	void StoreAttachmentL();
	void CopyOrigMessageToMessageL();
	void CreateMultipartMixedFolderEntryL();
	void CreateMultipartAlternativeFolderEntryL();
	void CreateMultipartRelatedFolderEntryL();
	void MoveOriginalMessageEntryChildrenToNewFolderL();
	void CreateTextEntryL();
	void StoreRichTextL();
	void CompleteStoreMessagePartL();
	void CreateHTMLEntryL();
	void PrepareToStoreHTMLEntryTextL();
	void StoreHTMLEntryTextL();
	TPtrC GetDefaultAttachmentName();
	void OpenAndReadResourceFileL();
	void StoreMimeHeaderL();
	TBool CreateAttachmentMimeHeaderL(CImMimeHeader& aMimeHeader, const TDesC& aDetails);
	void CreateFolderMimeHeaderL(CImMimeHeader& aMimeHeader);
	void CreateMessageMimeHeaderL(CImMimeHeader& aMimeHeader);

private:
	enum TImStoreMessagePartState
		{
		EFindMultipartRelatedFolder,
		ECheckForSubfolder,
		ECreateAttachmentEntry,
		EStoreAttachment,
		ECopyOrigMessageToMessage,
		ECreateMultipartMixedFolderEntry,
		ECreateMultipartRelatedFolderEntry,
		ECreateMultipartAlternativeFolderEntry,
		EMoveOriginalMessageEntryChildrenToNewFolder,
		ECreateTextEntry,
		EStoreRichText,
		ECreateHTMLEntry,
		EPrepareToStoreHTMLEntryText,
		EStoreHTMLEntryText,
		ECompleteStoreMessage,
		EFinished
		};
	enum TImMessagePart
		{
		EMessagePartAttachment,
		EMessagePartBody,
		EMessagePartMessageAttachment
		};
	enum TImStoreMessagePartFlags
		{
		KStoreMessagePartClearFlag							= 0x00000000,
		KStoreMessagePartHTMLMessage						= 0x00000001,
		KStoreMessagePartMultipartMixedExists				= 0x00000002,
		KStoreMessagePartMultipartMixedCreated				= 0x00000004,
		KStoreMessagePartMultipartAlternativeExists			= 0x00000008,
		KStoreMessagePartMultipartAlternativeCreated		= 0x00000010,
		KStoreMessagePartTextPartExists						= 0x00000020,
		KStoreMessagePartTextPartCreated					= 0x00000040,
		KStoreMessagePartAttachmentEntryCreated				= 0x00000080,
		KStoreMessagePartOrigMessageEntryChildrenCopied		= 0x00000100,
		KStoreMessagePartOrigMessageEntryChildrenDeleted	= 0x00000200,
		KStoreMessagePartMultipartRelatedExists				= 0x00000400,
		KStoreMessagePartMultipartRelatedCreated			= 0x00000800
		};
	CMsvEntry&			iMsvEntry;
	CMsvOperation*		iMsvOperation;
	
	CRichText*			iRichTextToStore; // I don't own this object!
	CRichText*			iRichText;
	CFileMan*			iFileMan;
	CMsvEntrySelection* iMessageEntrySelection;

	TInt				iState;
	TPckgBuf<TMsvId>	iDataMember;
	TMsvId				iMessageId;
	TImMessagePart		iMessagePart;
	TMsvId				iMixFolderId;
	TMsvId				iAltFolderId;
	TMsvId				iRelFolderId;
	HBufC*				iAttachmentFullName;
	TInt				iAttachmentSize;
	TMsvId				iAttachmentId;
	TMsvId				iTextId;
	TMsvId				iHtmlId;
	TMsvId				iRelatedPartId;
	TMsvId				iAttachmentMessageId;
	TUint32				iFlags;
	HBufC8*				iContentId;
	CImEmailMessage*	iEmailMessage;

	// Used when converting rich text to html
	CParaFormatLayer*	iParaLayer;
	CCharFormatLayer*	iCharLayer;
	CImHtmlConverter* iHtmlConverter;
	TBool iFinishedConvertingHTML;
	};

class CImEmailOperation : public CMsvOperation
	{
public:
	IMPORT_C static CImEmailOperation* CreateNewL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateNewL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aDestination, TMsvId aSmtpServiceId, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType, TInt aPriority = EPriorityStandard);
	IMPORT_C static CImEmailOperation* CreateReplyL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TDesC& aFormatString, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateReplyL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateReplyL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType, TInt aPriority);
	IMPORT_C static CImEmailOperation* CreateForwardL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TDesC& aFormatString, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateForwardL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateForwardL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvId aSmtpServiceId, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType, TInt aPriority = EPriorityStandard);
	IMPORT_C static CImEmailOperation* CreateForwardAsAttachmentL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateForwardAsAttachmentL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aSmtpServiceId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType, TInt aPriority = EPriorityStandard);
	IMPORT_C static CImEmailOperation* CreateReceiptL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TDesC& aFormatString, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateReceiptL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType);
	IMPORT_C static CImEmailOperation* CreateReceiptL(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aMessageId, TMsvId aDestination, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType, TInt aPriority);
	IMPORT_C ~CImEmailOperation();
	IMPORT_C const TDesC8& FinalProgress();
	void DoCancel();
	void RunL();
	const TDesC8& ProgressL();

private:
	enum TImEmailOperation 
		{
		ENew,
		EReply,
		EForward,
		EReceipt,
		EDeletingBadEmail,
		EForwardAsAttachment
		};

private:
	CImEmailOperation(TRequestStatus& aObserverRequestStatus, CMsvSession& aMsvSession, TMsvId aDestination, TMsvId aSmtpServiceId, TMsvPartList aPartList, const TMsvEmailTypeList& aMsvEmailTypeList, TUid aMsgType, TInt aPriority);
	void ConstructL(TMsvId aMessageId, const TDesC& aFormatString, TImEmailOperation aOperation);
	void ConstructL(TMsvId aMessageId, TImEmailOperation aOperation);
	void ConstructL(TImEmailOperation aOperation);
	void OpenAndReadResourceFileL();
	void SetDefaultSmtpServiceL();
	void SetUserEmailAddressFromSmtpServiceL();
	void ErrorRecovery(TInt error);
	void SelectNextStateL();				// selects next state to go to
	void ChangeStateL();					// initiates the next state operation
	void SelectAndChangeToNextStateL();
	void RequestComplete(TInt aError);
	void CreateNewHeaderL();
	void GetBodyTextL();
	TInt RemoveIncompleteAttachmentsL();
	void CreateEntryDetailsL(TMsvEmailEntry& aMsvEmailEntry);
	void CreateNewMessageL(TMsvId aDestinationId);
	void CreateMultipartMixedFolderEntryL();
	void CreateTextEntryL(TMsvId aFolderId);
	void StoreBodyL();
	void DoWeNeedSignatureOrVCardL();
	void CreateAttachmentEntryL();
	void StoreAttachmentL();
	void CreateMultipartAlternativeFolderEntryL();
	void AppendHtmlAttachmentL();
	void CopyOrigMessageToNewMessageL();
	void CompleteEmailOperationL();
	void CreateHTMLEntryL();
	void PrepareToStoreHTMLEntryTextL();
	void StoreHTMLEntryTextL();
	void CreateVCardAttachmentL();
	void AddVCardAttachmentL();
	TPtrC GetDefaultAttachmentName();
	void StoreSmtpSettingsL();
	TMsvId ServiceId();

private:
	enum TImEmailOperationState
		{
		ECreateNewHeader,
		EGetBodyText,
		EGetAttachmentList,
		ECreateNewMessageEntry,
		ECreateMultipartMixedFolderEntry,
		ECreateAttachmentEntry,
		EStoreAttachment,
		ECompleteEmailOperation,
		ECreateMultipartMixedMimeHeader,
		ECreateTextEntry,
		EStoreBody,
		ECreateHTMLEntry,
		EPrepareToStoreHTMLEntryText,
		EStoreHTMLEntryText,
		ECreateMultipartAlternativeFolderEntry,
		EFindHTMLPage,
		ECopyHtmlPartToAttachment,
		ECopyOrigMessageToNewMessage,
		ECreateVCardAttachment,
		EAddVCardAttachment,
		EFinished
		};
	
	CMsvEntry* iMsvEntry;
	CMsvOperation* iMsvOperation;
	
	CImHeader* iNewHeader;
	CParaFormatLayer* iParaLayer;
	CCharFormatLayer* iCharLayer;
	CRichText* iRichText;
	CImEmailMessage* iEmailMessage;
	HBufC* iFormatString;
	CFileMan* iFileMan;
	CImSmtpSettings* iSmtpSettings;
	
	TInt iState;
	TImEmailOperation iOperation;
	TMsvId iDestinationId;
	TMsvId iMultipartMixedId;
	TMsvId iMultipartAlternativeId;
	TMsvId iOrigMessageId;
	TMsvId iNewMessageId;
	TMsvId iSmtpServiceId;
	TUid iMsgType;
	TMsvPartList iPartList;
	TMsvEmailTypeList iMsvEmailTypeList;
	TInt iAttachmentCount;
	TInt iTotalAttachments;
	TPckgBuf<TMsvId> iDataMember;
	CArrayFixFlat<TImAttachmentInfo>* iAttachmentList;
	HBufC* iBodyHeaderFormatString;
	HBufC* iBodyHeader;
	HBufC* iUserEmailAddress;
	TInt iRichTextSize;
	TInt iVCardAndHtmlSize;
	TBool iOrigMessageHtml;
	TBool iHtmlNoTextAlt;

	// for MIME messages:
	TBool iCreateHtmlMessage;
	TBool iMultipartMixedFolderCreated;
	TBool iMultipartAlternativeFolderCreated;
	TMsvId iTextId;
	TMsvId iHtmlId;
	TMsvId iVcardId;

	// Used when converting rich text to html
	CImHtmlConverter* iHtmlConverter;
	TBool iFinishedConvertingHTML;

	// Relating to adding Signature and/or Vcard to an email
	TBool iNeedToAddVCardAttachment;
	HBufC* iDefaultVCardNameFormatString;
	TStreamId iVcardStoreId;
	CStreamStore* iVcardStore;
	CRichText* iSignatureText;
	TFileName iFileName;
	TImAttachmentFile iAttachmentFile;

	// PCMail
	TMsvId iPCMailServiceId;
	};


class CImHtmlConverter : public CBase
	{
public:
	static CImHtmlConverter* CImHtmlConverter::NewL(CMsvEntry& aMsvEntry, 
								   CParaFormatLayer& aParaLayer, CCharFormatLayer& aCharLayer);
	~CImHtmlConverter();
	void PrepareToStoreHTMLEntryTextL(TMsvId& aHtmlId, const TMsvId aTextId);
	CMsvOperation* StoreHTMLEntryTextAL(TRequestStatus& aStatus);
	void ReadDefaultAttachmentNameL( RResourceFile& resourceFile);
	TInt Size() const;

private:
	CImHtmlConverter(CMsvEntry&	aMsvEntry, CParaFormatLayer& aParaLayer, CCharFormatLayer& aCharLayer);
	TFileName HtmlFilename(CMsvEntry& aEntry, TPtrC aFileName);
	TPtrC GetDefaultAttachmentName();
	void ConstructL();

private:
	CMsvEntry&			iMsvEntry;
	CParaFormatLayer&	iParaLayer;
	CCharFormatLayer&	iCharLayer;

	CConverterBase*		iToHTMLConverter;
	CCnaConverterList*	iConverterList;

	TMsvId				iTextId;
	TMsvId				iHtmlId;
	TInt				iSize;
	HBufC*				iDefaultAttachmentName;
	};

class CImStoreResolver : public CBase, public MRichTextStoreResolver
	{
public:
	CImStoreResolver(CStreamStore* aStore);
	~CImStoreResolver();
	//
private:
	const CStreamStore& StreamStoreL(TInt aPos)const;
	//
private:
	CStreamStore* iStore;
	};

#endif
