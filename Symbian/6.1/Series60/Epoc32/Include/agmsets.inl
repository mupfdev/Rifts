// AGMSETS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ------------------------------------ CAgnStreamIdSet ----------------------------------
inline TInt CAgnStreamIdSet::Count() const
	{ return (iArray->Count()); }


inline TStreamId CAgnStreamIdSet::At(TInt aPos) const
	{
	__ASSERT_DEBUG(aPos < Count(),Panic(_L("Invalid indexing into stream id set")));
	return (iArray->At(aPos));
	}


// --------------------------- CAgnModelStreamIdSet------------------------------
inline const CAgnStreamIdSet* CAgnModelStreamIdSet::EntryStreamIdSet() const
	{ return (iEntryStreamIdSet); }

inline CAgnStreamIdSet* CAgnModelStreamIdSet::EntryStreamIdSet()
	{ return (iEntryStreamIdSet); }

inline TStreamId CAgnModelStreamIdSet::EntrySetStreamId() const
	{ return (iEntrySetStreamId); }

inline TStreamId CAgnModelStreamIdSet::TodoListListStreamId() const
	{ return (iTodoListListStreamId); }

inline TStreamId CAgnModelStreamIdSet::NextUniqueIdValueStreamId() const
	{ return (iNextUniqueIdValueStreamId); }

inline TStreamId CAgnModelStreamIdSet::DeletedTodoListListStreamId() const
	{ return (iDeletedTodoListListStreamId); }

inline TStreamId CAgnModelStreamIdSet::ObserverControllerStreamId() const
	{ return (iObserverControllerStreamId); }

inline TStreamId CAgnModelStreamIdSet::LastSynchronizedDateStreamId() const
	{ return (iLastSynchronizedDateStreamId); }

inline TStreamId CAgnModelStreamIdSet::EntryStoreStreamId() const
	{ return (iEntryStoreStreamId); }

inline TStreamId CAgnModelStreamIdSet::FileInformationStreamId() const
	{ return (iFileInformationStreamId); }

inline TStreamId CAgnModelStreamIdSet::FormatLayerStreamId() const
	{ return (iFormatLayerStreamId); }

inline TAgnVersion CAgnModelStreamIdSet::Version() const
	{ return (iVersion); }


