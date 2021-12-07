// MSVENTRY.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVENTRY_H__)
#define __MSVENTRY_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__MSVSTORE_H__)
#include "msvstore.h"
#endif

//////////////////////////////////////
// Forward declarations
class CMsvStore;
class CMsvCopyMoveEntriesBase;
class CMsvServer;

//**********************************
// CMsvServerEntry
//**********************************
//
//
//

class CMsvServerEntry : public CActive, public MMsvStoreObserver
	{
public:
	IMPORT_C static CMsvServerEntry* NewL(CMsvServer& aServer, TMsvId aId);
	~CMsvServerEntry();
	//
	// Set and get the current context
	IMPORT_C TInt SetEntry(TMsvId aId);
	inline const TMsvEntry& Entry() const;
	IMPORT_C TMsvId OwningService() const;
	//
	// current entry only functions
	IMPORT_C TInt ChangeEntry(const TMsvEntry& aEntry);
	IMPORT_C TInt GetFilePath(TFileName& aFilePath);
	//
	// child entry only functions
	IMPORT_C TInt CreateEntry(TMsvEntry& aEntry);
	IMPORT_C TInt DeleteEntry(TMsvId aId);
	IMPORT_C TInt DeleteEntries(CMsvEntrySelection& aSelection);
	IMPORT_C TInt MoveEntryWithinService(TMsvId aId, TMsvId aDestination);
	IMPORT_C TInt MoveEntriesWithinService(CMsvEntrySelection& aSelection, TMsvId aDestination);
	IMPORT_C TInt ChangeAttributes(const CMsvEntrySelection& aSelection, TUint aSetAttributes, TUint aClearAttributes);
	IMPORT_C void MoveEntryL(TMsvId aId, TMsvId aDestination, TRequestStatus& aObserverStatus);
	IMPORT_C void MoveEntriesL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aObserverStatus);
	IMPORT_C void CopyEntryL(TMsvId aId, TMsvId aDestination, TRequestStatus& aObserverStatus);
	IMPORT_C void CopyEntriesL(const CMsvEntrySelection& aSelection, TMsvId aDestination, TRequestStatus& aObserverStatus);
	IMPORT_C TInt GetEntryFromId(TMsvId aId,TMsvEntry*& aEntry);
	//
	// read and write the store associated with the context
	IMPORT_C CMsvStore* ReadStoreL();
	IMPORT_C CMsvStore* EditStoreL();
	//
	// List the children of the context 
	inline const TMsvSelectionOrdering& Sort();
	inline void SetSort(TMsvSelectionOrdering& aOrdering);
	inline void SetMtm(TUid aMtm);
	IMPORT_C TInt GetChildren(CMsvEntrySelection& aSelection);
	//
	IMPORT_C TInt GetChildrenWithService(TMsvId aServiceId, CMsvEntrySelection& aSelection);
	IMPORT_C TInt GetChildrenWithMtm(TUid aMtm, CMsvEntrySelection& aSelection);
	IMPORT_C TInt GetChildrenWithType(TUid aType, CMsvEntrySelection& aSelection);
	//
	// Spawns a new CMsvServerEntry object
	IMPORT_C CMsvServerEntry* NewEntryL(TMsvId aId);
	// 
	// from MMsvStoreObserver
	void HandleStoreEvent(MMsvStoreObserver::TMsvStoreEvent aEvent, TMsvId aId);
	//
	//
	IMPORT_C TBool HasDirectoryL() const;
	IMPORT_C TBool HasStoreL() const;
	//
	IMPORT_C RFs& FileSession();
	//
protected:
	CMsvServerEntry(CMsvServer& aIndex);
	void ConstructL(TMsvId aId);
	//
	void RunL();
	void DoCancel();
	//
private:
	TInt IncreaseBufferSizes(TInt aNewDescriptionSize, TInt aNewDetailsSize);
	TBool AreChildren(const CMsvEntrySelection& aSelection) const;
	TBool IsAChild(TMsvId aId) const;
	void DoMoveEntryL(TMsvId aId, TMsvId aDestination);
	void DoDeleteEntryL(TMsvId aId, CMsvEntrySelection*& aDeleted, CMsvEntrySelection*& aMoved);
	void DoDeleteEntriesL(CMsvEntrySelection& aSelection, CMsvEntrySelection*& aDeleted, CMsvEntrySelection*& aMoved);
	void DoMoveEntriesL(CMsvEntrySelection& aSelection, TMsvId aDestination, CMsvEntrySelection*& aMoved);
	TInt DoGetChildren(TMsvId aServiceId, TUid aMtm, TUid aType, CMsvEntrySelection& aSelection);
	void DoGetChildrenL(TMsvId aServiceId, TUid aMtm, TUid aType, CMsvEntrySelection& aSelection);
	//
private:
	TBool iLockedStore;
	TMsvSelectionOrdering iOrdering;
	TMsvEntry iEntry;
	HBufC* iDescription;
	HBufC* iDetails;
	CMsvServer& iServer;
	CMsvStore* iStore;
	TUid iMtm;
	TBool iMandatoryStore;
	CMsvCopyMoveEntriesBase* iCopyMove;
	TMsvId iSource;
	enum { EMsvIdle, EMsvMoving, EMsvCopying } iEntryState;
	TRequestStatus* iObserverStatus;
	};


#include "msventry.inl"

#endif
