// MSVIPC.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVIPC_H__)
#define __MSVIPC_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__MSVSTD_H__)
#include "msvstd.h"
#endif


//
const TInt KMsvNullOperation=0;
const TInt KMsvFirstOperation=1;

//
const TInt KMsvSessionBufferLength=0x1000;
const TInt KMsvProgressBufferLength=256;


// ***** NOTE!!!!! TMsvPackedChangeNotification::UnpackL() MUST be	****
// ***** updated when adding new types								*****
enum TMsvServerChangeNotificationType 
	{
	EMsvNullNotification=-1,
	EMsvEntriesNoChange=0,
	EMsvEntriesCreated=1,
	EMsvEntriesChanged=2,
	EMsvEntriesDeleted=3,
	EMsvEntriesMoved=4,
	EMsvMtmGroupInstalled=5,
	EMsvMtmGroupDeInstalled=6,
//	EMsvStoreDeleted=7,  // Not used
	EMsvCloseSession=8,
	EMsvIndexLoaded=9,
	EMsvIndexFailedToLoad=10,
	EMsvCorruptedIndexRebuilt=11,
	EMsvMediaChanged=12, // Note: I assume the following four follow each other in order
	EMsvMediaUnavailable=13,
	EMsvMediaAvailable=14,
	EMsvMediaIncorrect=15,
	EMsvCorruptedIndexRebuilding=16
	};


//**********************************
// TMsvPackedEntry
//**********************************
//
// Packs a TMsvEntry and the two associated descriptors into a buffer for
// sending across IPC. Also unpacks the data into a TMsvEntry and two heap 
// descriptors
//
//
class TMsvEntry;

class TMsvPackedEntry
	{
public:
	IMPORT_C TMsvPackedEntry(HBufC8*& aBuffer);
	IMPORT_C TInt PackEntry(const TMsvEntry& aEntry);
	IMPORT_C void UnpackEntry(TMsvEntry& aEntry);
private:
	HBufC8*& iBuffer;
	};


//**********************************
// TMsvPackedEntryArray
//**********************************
//
// Packs 1+ TMsvEntry's and the associated descriptors into a buffer for
// sending across IPC. Also unpacks the data into a TMsvEntry and two heap 
// descriptors using indexed access
//
//

class TMsvPackedEntryArray
	{
public:
	IMPORT_C TMsvPackedEntryArray(HBufC8*& aBuffer, TInt aCount=0);
	IMPORT_C TInt PackEntry(const TMsvEntry& aEntry);
	IMPORT_C TInt UnpackEntry(TInt aEntryIndex, TMsvEntry& aEntry);
	IMPORT_C void Reset();
private:
	TInt FindEntryInArray(TInt aIndex);
private:
	TInt	iIndex;
	TInt	iCount;
	const TUint8* iPos;
	HBufC8*& iBuffer;
	};


//**********************************
// TMsvChildrenDetails
//**********************************
//
// Contains the information about the number of children of an entry and how many
// have been sent in the main buffer
//

class TMsvChildrenDetails
	{
public:
	IMPORT_C TMsvChildrenDetails();
public:
	TMsvId	iParentId;
	TInt	iTotalNumberChildren;
	TInt	iNumberChildrenInArray;
	TInt	iLastEntryInArray;
	};


//**********************************
// TMsvLocalOperationProgress
//**********************************
//
// Contains the information about a local operation
//

class TMsvLocalOperationProgress
	{
public:
	enum TLocalOperation{	ELocalNone=0,
							ELocalMove,
							ELocalDelete,
							ELocalCopy,
							ELocalNew,
							ELocalChanged
							};
public:
	IMPORT_C TMsvLocalOperationProgress();
public:
	TLocalOperation iType;
	TInt iTotalNumberOfEntries;
	TInt iNumberCompleted;	
	TInt iNumberFailed;	
	TInt iNumberRemaining;	
	TInt iError;
	TMsvId	iId;
	};

//**********************************
// TMsvServerOperationProgress
//**********************************

class TMsvServerOperationProgress
	{
public:
	enum TMsvServerOperationType { EMsvNoOperation = 0, EMsvChangeDriveOperation };
	//
public:
	IMPORT_C TMsvServerOperationProgress();
	TMsvServerOperationProgress(TMsvServerOperationType aType);
	//
public:
	TMsvServerOperationType iOperationType;
	};

//**********************************
// TMsvIndexProgress
//**********************************

class TMsvIndexProgress
	{
public:
	IMPORT_C TMsvIndexProgress();
	//
public:
	TInt iTotal;
	TInt iCompleted;
	TInt iRemaining;
	TMsvId iId;
	};

//**********************************
// TMsvIndexLoadProgress
//**********************************

class TMsvIndexLoadProgress : public TMsvServerOperationProgress
	{
public:
	enum TIndexState {EIndexNotLoaded = 0, EIndexLoading, EIndexRebuilding, EIndexComplete};
	//
public:
	IMPORT_C TMsvIndexLoadProgress();
	//
public:
	TInt iError;
	TIndexState iState;
	TMsvIndexProgress iIndex;
	};

//**********************************
// TMsvPackedOperation
//**********************************
//
// Packs an operation, the selection, and some associated parameters (TInt) into the
// IPC buffer
//
//

class TMsvPackedOperation
	{
public:
	IMPORT_C TMsvPackedOperation(HBufC8*& aBuffer);
	IMPORT_C TInt Pack(const CMsvEntrySelection& aSelection, TInt aParameter1=0, TInt aParameter2=0);
	IMPORT_C void UnpackL(CMsvEntrySelection& aSelection, TInt& aParameter1, TInt& aParameter2);
private:
	HBufC8*& iBuffer;
	};


//**********************************
// TMsvPackedChangeNotification
//**********************************
//
// Packs the CMsvEntrySelection of index entries that have been changed, and also 
// the integer describing the type of change. There is a limit of KMsvPackedChangeLimit
// top the number of entry ids that can be sent at one time
//
//

typedef TBuf8<128> TMsvNotifBuffer;

class TMsvPackedChangeNotification
	{
public:
	enum {	KMsvChangeNotificationNumberOfTInts=4,
			KMsvPackedChangeLimit=28, // 32-KMsvChangeNotificationNumberOfTInts
			}; 
public:
	IMPORT_C TMsvPackedChangeNotification(TMsvNotifBuffer& aBuffer);
	inline void Pack(TMsvServerChangeNotificationType aChangeType, const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2);
	IMPORT_C void Pack(TMsvServerChangeNotificationType aChangeType, const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2, TInt aStartIndex, TInt aFinishIndex);
	IMPORT_C void Pack(TMsvServerChangeNotificationType aChangeType, TMsvId aId, TInt aParameter1, TInt aParameter2);
	IMPORT_C void UnpackL(TMsvServerChangeNotificationType& aChangeType, CMsvEntrySelection& aSelection, TInt& aParameter1, TInt& aParameter2);
private:
	TMsvNotifBuffer& iBuffer;
	};

//**********************************
// TMsvPackedEntryFilter
//**********************************

class TMsvPackedEntryFilter
	{
public:
	TMsvPackedEntryFilter(HBufC8*& aBuffer);
	TInt PackFilter(const CMsvEntryFilter& aFilter);
	void UnpackFilter(CMsvEntryFilter& aFilter);
private:
	HBufC8*& iBuffer;
	};


#include "msvipc.inl"

#endif

