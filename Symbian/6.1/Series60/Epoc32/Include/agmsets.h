// AGMSETS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMSETS_H__
#define __AGMSETS_H__

#include <s32stor.h>
#include "agmtodos.h"
#include "agmver.h"

//------------------------------ referenced classes --------------------------
class TAgnEntryIter;
class CParaFormatLayer;
class CCharFormatLayer;

class CAgnStreamIdSet : public CBase
	{
public:
	friend class TAgnEntryIter;

	static CAgnStreamIdSet* NewL();
	virtual ~CAgnStreamIdSet();
	void AddL(TStreamId aId);
	void DeleteL(TStreamId aId);
	inline TInt Count() const;
	TStreamId CreateL(CStreamStore& aStore);
	void CAgnStreamIdSet::LoadL(CStreamStore& aStore,TStreamId aStreamId);
	void CAgnStreamIdSet::SaveL() const;
	IMPORT_C TBool ResetIteratorToStart();
	IMPORT_C TBool Next();
	IMPORT_C TBool At(TStreamId& aItem) const;
	inline TStreamId At(TInt aPos) const;
	TInt Find(TStreamId aItem,TInt& aPos) const;
	void RollbackL();
	void Commit();
	void Reset();
private:
	enum {EGranularity = 16,ERollbackGranularity=2};
	CStreamStore*				iStore;
	TStreamId					iStreamId;
	CArrayFixFlat<TStreamId>*	iArray;
	TInt						iPos;
	CArrayFixFlat<TStreamId>*	iAddRollbackArray;
	CArrayFixFlat<TStreamId>*	iDeleteRollbackArray;
	};


class CAgnModelStreamIdSet : public CBase
	{
public:
	friend class TAgnEntryIter;

	static CAgnModelStreamIdSet* NewL();
	virtual ~CAgnModelStreamIdSet();										
	inline const CAgnStreamIdSet* EntryStreamIdSet() const;
	inline CAgnStreamIdSet* EntryStreamIdSet();
	inline TStreamId FormatLayerStreamId() const;
	inline TStreamId EntrySetStreamId() const;
	inline TStreamId TodoListListStreamId() const;
	inline TStreamId NextUniqueIdValueStreamId() const;
	inline TStreamId DeletedTodoListListStreamId() const;
	inline TStreamId ObserverControllerStreamId() const;
	inline TStreamId LastSynchronizedDateStreamId() const;
	inline TStreamId EntryStoreStreamId() const;
	inline TStreamId FileInformationStreamId() const;
	inline TAgnVersion Version() const;
	void SaveL(CStreamStore& aStore,TStreamId aStreamId) const;
	TStreamId CreateL(CStreamStore& aStore,const TAgnVersion& aVersion);
	void LoadL(CStreamStore& aStore,TStreamId aStreamId);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	void RollbackL();
	void Commit();
	void Reset();
protected:
	void ConstructL();
private:
	CAgnStreamIdSet*	iEntryStreamIdSet;	
	TAgnVersion			iVersion;				
	TStreamId			iEntrySetStreamId;		
	TStreamId			iTodoListListStreamId; 
	TStreamId			iFormatLayerStreamId;
	TStreamId			iNextUniqueIdValueStreamId; 
	TStreamId			iDeletedTodoListListStreamId;
	TStreamId			iObserverControllerStreamId;
	TStreamId			iLastSynchronizedDateStreamId;
	TStreamId			iEntryStoreStreamId;
	TStreamId			iFileInformationStreamId;
	};

#include "agmsets.inl"

#endif