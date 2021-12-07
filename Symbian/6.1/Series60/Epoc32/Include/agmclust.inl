// AGMCLUST.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
inline CAgnEntryManager::TBufItem::TBufItem(CAgnEntry* aEntry,TBool aToBeDeleted)
	: iEntry(aEntry),iToBeDeleted(aToBeDeleted)
	{}

inline TBool CAgnEntryManager::TBufItem::ToBeDeleted() const
	{ return (iToBeDeleted); }

inline CAgnEntry* CAgnEntryManager::TBufItem::Entry() const
	{ return (iEntry); }

inline void CAgnEntryManager::TBufItem::SetToBeDeleted(TBool aSetting)
	{ iToBeDeleted = aSetting; }

inline void CAgnEntryManager::TBufItem::SetEntry(CAgnEntry* aEntry)
	{ iEntry = aEntry; }

inline TBool CAgnEntryManager::BufferHasBeenStored() const
	{ return (iBufferHasBeenStored); }

//inline void CAgnEntryManager::SetBufferHasBeenStored(TBool aHasBeenStored)
//	{ iBufferHasBeenStored = aHasBeenStored; }

//inline CArrayFixFlat<CAgnEntryManager::TBufItem>* CAgnEntryManager::Buffer() const
//	{ return (iBuffer); }

inline TBool CAgnEntryManager::BufferedStoring() const
	{ return iBufferedStoring; }

inline TBool CAgnEntryManager::BufferedDeleting() const
	{ return iBufferedDeleting; }

inline void CAgnEntryManager::SetStore(CStreamStore& aStore)
	{ iStore = &aStore; }

inline const CAgnEntryStore* CAgnEntryManager::OwningEntryStore() const
	{ return (iOwningEntryStore); }

inline TInt CAgnEntryManager::MaxNumEntriesPerStream() const
	{ return (EMaxNumEntriesPerStream); }

inline void CAgnEntryManager::SetNextAvailableGeneralStreamId(TStreamId aId)
	{ iNextAvailableGeneralStreamId = aId; }

inline void CAgnEntryManager::SetNextAvailableTodoStreamId(TStreamId aId)
	{ iNextAvailableTodoStreamId = aId; }

inline void CAgnEntryManager::SetNextAvailableRptStreamId(TStreamId aId)
	{ iNextAvailableRptStreamId = aId; }


inline void CAgnEntryManager::SetUseExtended(TBool aUseExtended)
	{ iUseExtended = aUseExtended; }

