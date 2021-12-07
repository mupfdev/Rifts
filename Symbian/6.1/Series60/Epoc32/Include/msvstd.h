// MSVSTD.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVSTD_H__)
#define __MSVSTD_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__S32FILE_H__)
#include <s32file.h>
#endif


// Global typedefs
typedef TInt32 TMsvId;
typedef TInt32 TMsvOp;

// Global enumerations
enum TMsvPriority {	EMsvHighPriority,
					EMsvMediumPriority,
					EMsvLowPriority};	

// forward definitions
class CRichText;
class CMsvStore;

// file structure
_LIT(KMsvDefaultFolder, "\\System\\Mail\\");
_LIT(KMsvDefaultIndexFile, "\\System\\Mail\\Index");
_LIT(KMsvDirectoryExt, "_S\\");
_LIT(KMsvBinaryFolderExt, "_F\\");

const TInt KFileNameFixedWidth=8;

// misc
_LIT(KSendAsRenderedImage, "Image");

// Server name and moving semaphore
_LIT(KMsvServerName, "MsvServer");
_LIT(KMsvMovingSemaphore, "MsvMovingSemaphore");


//**********************************
// TMsvEntry
//**********************************
//
// The generic data that is stored in the index for all entries
//
	
class TMsvEntry
	{
public: 
	IMPORT_C TMsvEntry(); 
	IMPORT_C TMsvEntry(const TMsvEntry& aEntry);
	IMPORT_C TMsvEntry& operator=(const TMsvEntry& aEntry);
	IMPORT_C TBool operator==(const TMsvEntry& aEntry) const;
	IMPORT_C TBool PermanentDataUnchanged(const TMsvEntry& aEntry) const;
	//
	IMPORT_C TMsvPriority Priority() const;
	IMPORT_C void SetPriority(TMsvPriority aPriority);
	// 
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	// Read only for clients
	inline TMsvId Id() const;
	inline TMsvId Parent() const;
	inline TBool Owner() const;
	inline TBool Deleted() const;
	// Read & write for clients
	inline TBool Complete() const;
	inline void SetComplete(TBool aComplete);
	inline TBool New() const;
	inline void SetNew(TBool aNew);
	inline TBool Unread() const;
	inline void SetUnread(TBool aRead);
	inline TBool Failed() const;
	inline void SetFailed(TBool aFailed);
	inline TBool Operation() const;
	inline void SetOperation(TBool aOperation);
	inline TBool Visible() const;
	inline void SetVisible(TBool aVisible);
	inline TBool MultipleRecipients() const;
	inline void SetMultipleRecipients(TBool aMultipleRecipients);
	inline TBool ReadOnly() const;
	inline void SetReadOnly(TBool aReadOnly);
	inline TBool StandardFolder() const;
	inline void SetStandardFolder(TBool aStanardFolder);
	inline TBool Attachment() const;
	inline void SetAttachment(TBool aAttachmentFlag);
	inline TBool Connected() const;
	inline void SetConnected(TBool aConnected);
	inline TBool InPreparation() const;
	inline void SetInPreparation(TBool aInPreparation);
	//
	inline TInt PcSyncCount() const;
	inline void DecPcSyncCount();
	inline void IncPcSyncCount();
	//
	inline TBool OffPeak() const;
	inline void SetOffPeak(TBool aOffPeak);
	inline TBool Scheduled() const;
	inline void SetScheduled(TBool aScheduled);
	inline TUint SendingState() const;
	inline void SetSendingState(TUint aSendingState);
	//
protected:
	// only the server will be able to set the following
	inline void SetId(TMsvId aId);
	inline void SetParent(TMsvId aId);
	inline void SetOwner(TBool aAttachment);
	inline void SetDeleted(TBool aDeletedFlag);
	//
	inline TUint PersistedFlags() const;
	inline TUint TemporaryFlags() const;
	//
private:
	void Copy(const TMsvEntry& aEntry);
	//
private:
	TMsvId iId;
	TMsvId iParentId;  
	TInt32 iData;         
	TInt32 iPcSyncCount;
	TInt32 iReserved; // reserved for future proofing
public: 
	TMsvId iServiceId; 
	TMsvId iRelatedId; 
	TUid   iType;        
	TUid   iMtm;     
	TTime  iDate;       
	TInt32 iSize;      
	TInt32 iError;
	TInt32 iBioType;
	// following three can be used by MTM
	TInt32 iMtmData1; 
	TInt32 iMtmData2; 
	TInt32 iMtmData3; 
	// The TPtrC must be kept at end of class to simplify comparisons and initialisation
	TPtrC iDescription;
	TPtrC iDetails;    
	//
	//
private:
	//
friend class CMsvEntry;
friend class CMsvServer;
friend class CMsvServerEntry;
friend class CMsvClientEntry;
friend class CMsvServerSession;
friend class TMsvServerEntry; 
friend class CMsvServerIndex;
friend class RMsvServerSession;
friend class CMsvLocalCopyOperation;
friend class CMsvMove;
friend class CMsvIndexRebuild;
friend class CMsvCopyEntry;
friend class CMsvDelete;
friend class CMsvIndexContext;
friend class CMsvEntryArray;
	//
private:
	//
enum {	KMsvEntryPriorityMask=			0x00000003,
		KMsvEntryHighPriority=			0x00000002,
		KMsvEntryMediumPriority=		0x00000001,
		KMsvEntryLowPriority=			0x00000000,
		KMsvEntryClearFlag=				0x00000000,
		KMsvOffPeakFlag=				0x00000004,
		KMsvEntryNotCompleteFlag=		0x00000008,
		KMsvEntryNewFlag=				0x00000010,
		KMsvEntryUnreadFlag=			0x00000020,
		KMsvEntryFailedFlag=			0x00000040,
		KMsvEntryOperationFlag=			0x00000080,
		KMsvEntryOwnerFlag=				0x00000100,
		KMsvEntryInvisibleFlag=			0x00000200,
		KMsvEntryMultipleRecipientFlag=	0x00000400,
		KMsvScheduledFlag=				0x00000800,
		KMsvEntryReadOnlyFlag=			0x00001000,
		KMsvEntryDeletedFlag=			0x00002000,
		KMsvEntryStandardFolderFlag=	0x00004000,
		KMsvEntryAttachmentFlag=		0x00008000,
		KMsvEntryInPreparationFlag=		0x00010000,
		KMsvSendingStateFlags=			0x001E0000, // Note: Sending state is shifted KMsvSendingStateShift places left
		KMsvEntryPersistedFlags=		0x00FFFFFF,
		KMsvEntryTemporaryFlags=		0xFF000000,
		KMsvEntryConnectedFlag=			0x01000000};
	};

const TUint KMsvSendingStateShift=0x11; // Places to shift sending state

enum TMsvSendState
	{
	KMsvSendStateUnknown		= 0x0,
	KMsvSendStateUponRequest	= 0x1,
	KMsvSendStateWaiting		= 0x2,
	KMsvSendStateSending		= 0x3,
	KMsvSendStateScheduled		= 0x4,
	KMsvSendStateResend			= 0x5,
	KMsvSendStateSuspended		= 0x6,
	KMsvSendStateFailed			= 0x7,
	KMsvSendStateSent			= 0x8,
	KMsvSendStateNotApplicable	= 0x9
	};

const TUint KMsvSendStateLast = KMsvSendStateNotApplicable;
const TUint KMsvSendStateMax = 0xF;

//**********************************
// TMsvAttribute
//**********************************
//
// Flags for ChangeAttributes functions
// 
// Matches the flags for TMsvEntry iData

enum TMsvAttribute    { KMsvPcSyncCountAttribute	=0x00000001,
						KMsvVisibilityAttribute		=0x00000200,
						KMsvUnreadAttribute			=0x00000020,
						KMsvInPreparationAttribute	=0x00010000,
						KMsvConnectedAttribute		=0x01000000,
						KMsvNewAttribute			=0x00000010};


//**********************************
// TMsvSelectionOrdering
//**********************************
//
// The grouping and sort type for CMsvEntrySelection
//

enum TMsvSorting 
	{
	EMsvSortByNone=0,				// Don't sort
	EMsvSortByDate,					// Date (earliest-latest)
	EMsvSortByDateReverse,			// Date (latest-earliest)
	EMsvSortBySize,					// Size (smallest-largest)
	EMsvSortBySizeReverse,			// Size (largest-smallest)
	EMsvSortByDetails,				// ToFrom (A-Z collated)
	EMsvSortByDetailsReverse,		// ToFrom (Z-A collated)
	EMsvSortByDescription,			// Description (A-Z collated)
	EMsvSortByDescriptionReverse,	// Description (Z-A collated)
	EMsvSortById,			        // Id (lowest-highest)
	EMsvSortByIdReverse	            // Id (highest-lowest)
	};

enum TMsvGrouping
	{
	KMsvNoGrouping=0,				// No grouping
	KMsvGroupByType=0x2,			// Folder, Message, Attachment
	KMsvGroupByStandardFolders=0x6,	// Standrad folders first (must have sorting by type set aswell)
	KMsvGroupByPriority=0x8,		// High, Mediem, Low
	KMsvGroupByMtm=0x10,			// By increasing uid value
	};

class TMsvSelectionOrdering
	{
public:
	//
public:
	IMPORT_C TMsvSelectionOrdering();
	IMPORT_C TMsvSelectionOrdering(TInt aGroupingKey, TMsvSorting aSorting, TBool aShowInvisible=EFalse);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	IMPORT_C TBool operator==(const TMsvSelectionOrdering& aEntry) const;
	//
	inline TMsvSorting Sorting() const;
	inline TBool GroupByType() const;
	inline TBool GroupStandardFolders() const;
	inline TBool GroupByPriority() const;
	inline TBool GroupByMtm() const;
	inline TBool ShowInvisibleEntries() const;
	inline TBool GroupingOn() const;
	// 
	inline void SetGroupByType(TBool aFlag);
	inline void SetGroupStandardFolders(TBool aFlag);
	inline void SetGroupByPriority(TBool aFlag);
	inline void SetGroupByMtm(TBool aFlag);
	inline void SetShowInvisibleEntries(TBool aFlag);
	inline void SetSorting(TMsvSorting aSortType);
	//
	//
private:
	enum TMsvGroupingPrivate
		{
		KMsvInvisibleFlag=0x1,
		KMsvStandardFolders=0x4,
		KMsvAllGroupingFlags=0x1e
		};
	TInt iGrouping;
	TMsvSorting iSortType;
	};	

const TInt KMsvInvisibleFlag=1;

//**********************************
// CMsvEntrySelection
//**********************************
//
// The array of TMsvId which is used to pass selection of entries
//

class CMsvEntrySelection : public CArrayFixFlat<TMsvId>
// 
// Arrays of entry id
//
	{ 
public: 
	IMPORT_C CMsvEntrySelection();
	IMPORT_C CMsvEntrySelection* CopyL()  const;
	IMPORT_C CMsvEntrySelection* CopyLC() const;
	IMPORT_C TInt Find(TMsvId aId) const;
	};


//**********************************
// CMsvDefaultServices
//**********************************
//
// The array of default services
//

class TMsvDefaultService
	{
public:
	TUid iMtm;
	TMsvId iService;
	};

class CMsvDefaultServices: public CArrayFixFlat<TMsvDefaultService>
	{
public:
	IMPORT_C CMsvDefaultServices();
	IMPORT_C ~CMsvDefaultServices();
	//
	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);
	//
	IMPORT_C void ChangeDefaultServiceL(const TMsvDefaultService& aDefaultService);
	IMPORT_C TInt RemoveDefaultService(TUid aMtm);
	//
	IMPORT_C TInt DefaultService(TUid aMtm, TMsvId& aService) const;
private:
	TInt FindService(TUid aMtm) const;
	};

//**********************************
// CMsvEntryFilter
//**********************************

class CMsvEntryFilter : public CBase
	{
public:
	IMPORT_C static CMsvEntryFilter* NewLC();
	IMPORT_C static CMsvEntryFilter* NewL();
	//
public:
	inline TMsvId Service() const;
	inline void SetService(TMsvId aServiceId);
	//
	inline TUid Mtm() const;
	inline void SetMtm(TUid aMtm);
	//
	inline TUid Type() const;
	inline void SetType(TUid aType);
	//
	inline const TTime& LastChangeDate() const;
	inline void SetLastChangeDate(const TTime& aLastChange);
	//
	inline const TMsvSelectionOrdering& Order() const;
	inline void SetOrder(const TMsvSelectionOrdering& aOrder);
	//
	inline TUid SortMtm() const;
	inline void SetSortMtm(TUid aSortMtm);
	//
private:
	CMsvEntryFilter();
	//
private:
	TMsvId iServiceId;
	TUid iMtm;
	TUid iType;
	TTime iLastChange;
	TMsvSelectionOrdering iOrdering;
	TUid iSortMtm;
	};

// Error resolver leave codes -7000 to -7127
enum TMsvResolverLeave
	{
	KMsvMediaUnavailable = -7000,
	KMsvMediaIncorrect = -7001,
	KMsvMediaChanged = -7002,
	KMsvIndexBackup      = -7003,
	KMsvIndexRestore     = -7004
	};

#include "msvstd.inl"

#endif
