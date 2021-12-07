// MSVENTRY.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


//**********************************
// CMsvServerEntry
//**********************************

inline const TMsvEntry& CMsvServerEntry::Entry() const
	{
	return iEntry;
	}

inline const TMsvSelectionOrdering& CMsvServerEntry::Sort()
	{
	return iOrdering;
	}

inline void CMsvServerEntry::SetSort(TMsvSelectionOrdering& aOrdering)
	{
	iOrdering=aOrdering;
	}

inline void CMsvServerEntry::SetMtm(TUid aMtm)
	{
	iMtm=aMtm;
	}
