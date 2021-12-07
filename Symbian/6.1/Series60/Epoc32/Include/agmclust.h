// AGMCLUST.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMCLUST_H__
#define __AGMCLUST_H__

#include "agmentry.h"
#include "agmcomon.h"

// ---------------------- Referenced classes -----------------------------------
class TAgnEntryIter;
class CAgnEntryStore;


class CAgnEntryManager : public CBase
//
// Manages adding,deleting and updating entries in the store
//
	{
public:
	friend class TAgnEntryIter;
	enum TBufferType {ETodo,ERpt,EGeneral};
	enum {EMaxNumEntriesPerStream=16}; 
	enum TStoreComponents {EStoreComponents,EDontStoreComponents};
	static CAgnEntryManager* NewL(const CAgnEntryStore* aOwningEntryStore);
	virtual ~CAgnEntryManager();
	TStreamId AddEntryL(CAgnEntry* aEntry,TStoreComponents = EStoreComponents);
	TStreamId DeleteEntryL(TAgnEntryId aEntryId);
	CAgnEntry* FetchEntryL(TAgnEntryId aEntryId);
	TStreamId UpdateEntryL(CAgnEntry* aEntry,TStreamId& aNewStreamId);
	void StoreBuffersL();
	void FlushBuffersL();
	void FreeBuffers();
	inline TBool BufferedStoring() const;
	void SetBufferedStoring(TBool aSetting);
	inline TBool BufferedDeleting() const;
	void SetBufferedDeleting(TBool aSetting);
	TAgnEntryId NextAvailableIdL(TBufferType aBufferType);
	inline void SetStore(CStreamStore& aStore);
	inline TBool BufferHasBeenStored() const;
	void Reset();
	TInt EntryCount() const;
	inline TInt MaxNumEntriesPerStream() const;
	TInt RestoreBufferL(TStreamId aStreamId);
	TBufferType BufferTypeAndCountL(TInt& aCount,TStreamId aId);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	inline void SetNextAvailableGeneralStreamId(TStreamId aId);
	inline void SetNextAvailableTodoStreamId(TStreamId aId);
	inline void SetNextAvailableRptStreamId(TStreamId aId);
	inline void SetUseExtended(TBool aUseExtended);
private:
	class TBufItem
		{
	public:
		inline TBufItem() {};
		inline TBufItem(CAgnEntry* aEntry, TBool aToBeDeleted=EFalse); 
		inline TBool ToBeDeleted() const;
		inline void SetToBeDeleted(TBool aSetting);
		inline void SetEntry(CAgnEntry* aEntry);
		inline CAgnEntry* Entry() const;
	private:		
		CAgnEntry	*iEntry;
		TBool		iToBeDeleted;
		};
	typedef CArrayFixFlat<TBufItem> CBuffer;

	CAgnEntryManager();
	const CAgnEntry* operator[](TInt aIndex) const;
	void StoreBufferL(TStreamId aStreamId,const CBuffer* aBuffer,TBufferType aType);
	TUint FindUniqueIdPortion(const CBuffer* aBuffer);
	CAgnEntry* SearchBuffers(TAgnEntryId aEntryId,TInt& aPos);
	void SetBufferHasBeenStored(TBool aHasBeenStored,TBufferType aType);
	void FreeBuffer(TBufferType aBufferType);
	void DeleteEntriesInBufferFromStoreL(CBuffer* aBuffer,TInt& aNumEntriesToDelete);	
	inline const CAgnEntryStore* OwningEntryStore() const;
	TStreamId DoAddEntryL(CAgnEntry* aEntry,TStreamId& aCurrentStreamId,TStreamId& aNextAvailableStreamId,CBuffer* aBuffer,TBufferType aBufferType);
	TStreamId DoDeleteEntryL(CAgnEntry* aEntry,CBuffer* aBuffer,TInt& aNumEntriesToDelete,TStreamId& aNextAvailableStreamId,TStreamId aCurrentStreamId,TBufferType aBufferType,TInt aPos);
	void StoreAndMaybeFreeBuffersL(TBool aFreeBuffers);

	CBuffer*				iGeneralBuffer;
	CBuffer*				iTodoBuffer;
	CBuffer*				iRptBuffer;	
	TStreamId				iNextAvailableGeneralStreamId;
	TStreamId				iNextAvailableTodoStreamId;
	TStreamId				iNextAvailableRptStreamId;
	TStreamId				iCurrentGeneralStreamId;
	TStreamId				iCurrentTodoStreamId;
	TStreamId				iCurrentRptStreamId;
	TInt					iNumGeneralEntriesToDelete;
	TInt					iNumTodoEntriesToDelete;
	TInt					iNumRptEntriesToDelete;
	TBool					iGeneralBufferHasBeenStored;
	TBool					iTodoBufferHasBeenStored;
	TBool					iRptBufferHasBeenStored;
	TBool					iBufferHasBeenStored;
	CStreamStore*			iStore;
	const CAgnEntryStore*	iOwningEntryStore;	
	TBool					iBufferedStoring;
	TBool					iBufferedDeleting;
	TBufferType				iLastRestored;
	TBool					iUseExtended;
	};

#include "agmclust.inl"

#endif
