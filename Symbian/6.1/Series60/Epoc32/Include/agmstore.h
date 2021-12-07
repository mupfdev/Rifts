// AGMSTORE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMSTORE_H__
#define __AGMSTORE_H__

#include "agmclust.h"

// ---------------------------- Referenced classes ---------------------------------
class CAgnEntry;
class CAgnEntryModel;
class CAgnStreamIdSet;
class CAgnTodoList;
class CAgnSortEntryTable;
class TAgnEntryIter;

class CAgnStore : public CBase
	{
public:
	inline void SetOwningModel(CAgnEntryModel* aOwningModel);
	inline void SetStreamIdSet(const CAgnStreamIdSet* aStreamIdSet);
	inline const CAgnStreamIdSet* StreamIdSet() const;
	inline CStreamStore& Store() const;
	virtual void SetStore(CStreamStore& aStore) = 0;
	inline CAgnStreamIdSet* StreamIdSet(); 
	inline CAgnEntryModel* OwningModel() const;
protected:
	const CAgnStreamIdSet*	iStreamIdSet; // this should be moved into CAgnEntryStore !!!
	CStreamStore*			iStore;
	CAgnEntryModel*			iOwningModel; // !!! why isn't it const
	};

class CAgnEntryStore : public CAgnStore
	{
public:
	friend class TAgnEntryIter;
	static CAgnEntryStore* NewL();
	virtual ~CAgnEntryStore();
	virtual void SetStore(CStreamStore& aStore);
	void SetStore(CAgnStore& aStore);
	TAgnEntryId UpdateEntryL(const CAgnEntry* aEntry,TBool& aHadAlarm);
	void DeleteEntryL(TAgnEntryId aEntryId);
	TAgnEntryId AddEntryL(CAgnEntry* aEntry);
	CAgnEntry* FetchEntryL(TAgnEntryId aEntryId);
	TBool BufferedStoring() const;
	void SetBufferedStoring(TBool aSetting);
	TBool BufferedDeleting() const;
	void SetBufferedDeleting(TBool aSetting);
	void FlushBuffersL();
	void StoreBuffersL();
	void Reset();
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	TAgnEntryId NextAvailableIdL(CAgnEntryManager::TBufferType aBufferType) const;
	TBool BufferHasBeenStored() const;
	inline CAgnEntryManager* EntryManager() const;
protected:
	inline CAgnEntryStore();
private:
	CAgnEntryManager*	iEntryManager;	
	};


class TAgnTodoListStore 
	{
public:	
	void UpdateTodoListL(const CAgnTodoList* aTodoList, const CAgnEntryModel& aModel);
	void DeleteTodoListL(CAgnTodoList* aTodoList);
	TAgnTodoListId AddTodoListL(const CAgnTodoList* aTodoList, const CAgnEntryModel& aModel);
	inline CStreamStore& Store() const;
	void SetStore(CStreamStore& aStore);
private:
	void WriteBackgroundColorL(RStoreWriteStream& aStream, const CAgnEntryModel& aModel, const CAgnTodoList& aTodoList);
private:
	CStreamStore* iStore;	
	};


#include "agmstore.inl"

#endif
