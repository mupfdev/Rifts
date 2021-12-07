// FXUT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#ifndef FXUT_H_
#define FXUT_H_

#include <BADESCA.H>
#include <faxstd.h>
#include <faxdefn.h>
#include <faxset.h>		// TFaxSettings
#include <msvrcpt.h>
#include <msvstd.h>
#include <msvstore.h>
#include <etel.h>

////////////////////////////////
// global definitions

const TUid KMsgFileFaxHeaderUid	= {0x100001D7};
const TUint KFaxsSendLockMask=0x00000010;
const TUint16 KFaxSettingsVersion = 1;	// identify which version of this class has been stored

enum TFaxSendingState
	{
	EFaxSendingStateCalling = (KMsvSendStateLast + 1),
	EFaxSendingStateNegotiating,
	EFaxSendingStatePreparing
	};

class TMsvFaxEntry : public TMsvEntry
	{
public:
	IMPORT_C TMsvFaxEntry();
	IMPORT_C TMsvFaxEntry(const TMsvEntry& aGenericEntry); 
	//
	inline TInt16 SendingPage() const;
	inline void SetSendingPage(TInt16 aPage);
	//
	inline TInt16 TotalPages() const;
	inline void SetTotalPages(TInt16 aTotal);
	//
	inline TInt16 SendingRecipient() const;
	inline void SetSendingRecipient(TInt16 aRecipient);
	//
	inline TInt16 TotalRecipients() const;
	inline void SetTotalRecipients(TInt16 aTotal);
	//
	inline TFaxResolution Resolution() const;
	inline void SetResolution(TFaxResolution aResolution);
	//
	inline TInt8 RenderingComplete() const;
	inline void SetRenderingComplete(TInt8 aComplete);

private:
	enum TMsvFaxEntryFlags { EMsvFineResolution = 1 };
	};

class TMTMFaxSettings : public TFaxSettings
	{
public:
	IMPORT_C void Reset();
	IMPORT_C TMTMFaxSettings();
	IMPORT_C void ExternalizeL (RWriteStream &) const;
    IMPORT_C void InternalizeL (RReadStream &);
    IMPORT_C TMTMFaxSettings& operator=(const TMTMFaxSettings& aFaxSettings);

	IMPORT_C void StoreL(CMsvStore& aMsvStore) const;
	IMPORT_C void RestoreL(const CMsvStore& aMessageStore );

	// Id of folder where sent messages can be kept
	IMPORT_C const TMsvId MessageLogFolder() const;
	IMPORT_C void SetMessageLogFolder(TMsvId aMessageLogFolder);

	// Version number of this stream (incremented when contents of class is altered)
	IMPORT_C const TUint16 Version() const;
	IMPORT_C void SetVersion(const TUint16 aVersion);

	inline TBool ProgressInEntry() const;
	inline void SetProgressInEntry(TBool aProgress);

	inline TBool PartialResend() const;
	inline void SetPartialResend(TBool aResend);

	inline TBool UnRenderOnSend() const;
	inline void SetUnRenderOnSend(TBool aUnRender);

	inline TBool WatcherEnabled() const;
	inline void SetWatcherEnabled(TBool aEnabled);

	inline TBool SentFaxesReadOnly() const;
	inline void SetSentFaxesReadOnly(TBool aReadOnly);

public:
	TBuf<20> iUserName;
	
	//specifies the fax settings.
	enum TFaxSettingsFlags
		{
		KFaxSettingsClearFlag		= 0x00000000,
		EFaxNoProgressInEntry		= 0x00000001,
		EFaxNoPartialResend			= 0x00000002,
		EFaxWatcherDisabled			= 0x00000004,
		EFaxNoUnRenderOnSend		= 0x00000008,
		EFaxSentFaxesNotReadOnly	= 0x00000010,
		KFaxSettingsUnusedFlag		= EFaxSentFaxesNotReadOnly << 1
		};
	

protected:
	TUint16 iVersion;		// Version number for stream persisted in store
	TUint32 iFlags;			// space for flags info (now and for future)
	TMsvId	iMessageLogFolder;
	//
private:
	TUint32 iReserved1;
	TUint32 iReserved2;
	};

//
//
//
class CFaxRecipient : public CMsvRecipient
	{
public:
	IMPORT_C CFaxRecipient();
	IMPORT_C ~CFaxRecipient();

	// streaming operations
	IMPORT_C void InternalizeL( RMsvReadStream& aReadStream);
	IMPORT_C void ExternalizeL( RMsvWriteStream& aWriteStream) const;

	IMPORT_C TPtrC Name() const;
	IMPORT_C void SetNameL( const TDesC& );

	IMPORT_C TPtrC8 Number() const;
	IMPORT_C void SetNumberL(const TDesC8&);

	inline TInt16 SendingPage() const;
	inline void SetSendingPage(TInt16 aPage);

private: //data
	TInt16 iSendingPage;
	TFaxResolution iAttachmentResolution;
	HBufC8* iNumber;
	HBufC*  iName;
	};

class CFaxHeader : public CArrayPtrFlat<CFaxRecipient>
	{
public:
	IMPORT_C CFaxHeader();
	IMPORT_C ~CFaxHeader();

	IMPORT_C void RestoreL( CMsvStore& aStore );
	IMPORT_C void StoreL( CMsvStore& aStore );// const;
	};

class FaxUtils
	{
public:
	IMPORT_C static TInt SizeL(CMsvEntry& aEntry, RFs& aFs);
	IMPORT_C static void GetTsyNameL(TDes& aName);
	IMPORT_C static TBool GetPhoneInfoForTsyL(RTelServer& aTelServer, const TDes& aTsyName, RTelServer::TPhoneInfo& aPhoneInfo);
	IMPORT_C static TBool GetFaxLineInfoForPhoneL(RPhone& aPhone, RPhone::TLineInfo& aLineInfo);
	IMPORT_C static void UnRenderFaxL(CMsvEntry& aEntry);
	};

////////////////////////////////////////////////////////////////////////////
//
//	TFaxProgress Declaration
//
////////////////////////////////////////////////////////////////////////////

class TFaxProgress
	{
public:
	enum TFaxProgressType { EFaxInvalid = 0, EFaxPreparing, EFaxSending, EFaxReceiving };
	//
public:
	IMPORT_C TFaxProgress();
	TFaxProgress(TFaxProgressType aType);
	//
public:
	TFaxProgressType iType;
	};

typedef TPckgBuf<TFaxProgress> TFaxProgressBuf;

////////////////////////////////////////////////////////////////////////////
//
//	TFaxSessionProgress Declaration
//
////////////////////////////////////////////////////////////////////////////

class TFaxSessionProgress : public TFaxProgress
	{
public:
	enum TFaxSessionState { EFaxSessionNotStarted, EFaxSessionTransfering, EFaxSessionStopped, EFaxSessionCompleted, EFaxSessionCancelled, EFaxSessionOOM };
	//
public:
	IMPORT_C TFaxSessionProgress();
	//
public:
	TFaxSessionState iState;
	TInt iMessage;
	TInt iMessagesSuccessful;
	TFaxPhase iPhase;
	TFaxMode iMode;
	TInt iPageNumber;
	TBuf8<64> iFaxNumber;
	TInt iError;
	TMsvId iId;
	};

typedef TPckgBuf<TFaxSessionProgress> TFaxSessionProgressBuf;

////////////////////////////////////////////////////////////////////////////
//
//	TFaxRenderProgress Declaration
//
////////////////////////////////////////////////////////////////////////////

class TFaxRenderProgress
	{
public:
	enum TRenderStage { EInitialising, EPaginating, EPrinting, ESettingCompleteFlag, EDone };
	enum TRenderErrors
		{
		EProblemInitialisingEntry				= -900,
		EProblemInitialisingStore				= EProblemInitialisingEntry-1,
		EProblemInitialisingRestoringBodyText	= EProblemInitialisingEntry-2,
		EProblemInitialisingOutOfMemory			= EProblemInitialisingEntry-3,
		EProblemInitialisingGettingBinaryFile	= EProblemInitialisingEntry-4,
		EProblemInitialisingPrintObjects		= EProblemInitialisingEntry-5,
		EProblemPaginatingOutOfMemory			= EProblemInitialisingEntry-6,
		EProblemPaginatingCompletion			= EProblemInitialisingEntry-7,
		EProblemPaginating						= EProblemInitialisingEntry-8,
		EProblemPrintingOutOfMemory				= EProblemInitialisingEntry-9,
		EProblemPrintingInitialisation			= EProblemInitialisingEntry-10,
		EProblemSettingCompleteFlag				= EProblemInitialisingEntry-11
		};
	//
public:
	IMPORT_C TFaxRenderProgress();
	//
public:
	TRenderStage iStage;
	TInt8 iPercentDone;
	TInt iError;
	};

typedef TPckgBuf<TFaxRenderProgress> TFaxRenderProgressBuf;

////////////////////////////////////////////////////////////////////////////
//
//	TFaxPrepareProgress Declaration
//
////////////////////////////////////////////////////////////////////////////

class TFaxPrepareProgress : public TFaxProgress
	{
public:
	IMPORT_C TFaxPrepareProgress();
	//
public:
	TMsvId iId;
	TInt iCurrent;
	TInt iTotal;
	TFaxRenderProgress iRender;
	};

typedef TPckgBuf<TFaxPrepareProgress> TFaxPrepareProgressBuf;

#include "fxut.inl"

#endif 

