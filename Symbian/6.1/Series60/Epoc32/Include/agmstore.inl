// AGMSTORE.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
inline void CAgnStore::SetOwningModel(CAgnEntryModel* aOwningModel)
	{ iOwningModel=aOwningModel; }

inline CStreamStore& CAgnStore::Store() const
	{ return (*iStore); }

inline void CAgnStore::SetStreamIdSet(const CAgnStreamIdSet* aStreamIdSet)
	{ iStreamIdSet=aStreamIdSet; }

inline const CAgnStreamIdSet* CAgnStore::StreamIdSet() const
	{ return (iStreamIdSet); }

inline CAgnStreamIdSet* CAgnStore::StreamIdSet()
	{ return ((CAgnStreamIdSet*)iStreamIdSet); }

inline CAgnEntryModel* CAgnStore::OwningModel() const
	{  return (iOwningModel); }




// ----------------------------- CAgnEntryStore -------------------------------
inline CAgnEntryStore::CAgnEntryStore()
	{}

inline CAgnEntryManager* CAgnEntryStore::EntryManager() const
	{ return (iEntryManager); }

// ----------------------------- TAgnTodoListStore -------------------------------
inline CStreamStore& TAgnTodoListStore::Store() const
	{ return (*iStore); }

inline void TAgnTodoListStore::SetStore(CStreamStore& aStore) 
	{ iStore = &aStore; }



