// AGMSITER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMSITER_H__
#define __AGMSITER_H__

#include "agclient.h"



class CAgnSyncIter : public CBase
	{
	friend RAgendaServ;
public:
	IMPORT_C static CAgnSyncIter* NewL(RAgendaServ* aServ);
	IMPORT_C static CAgnSyncIter* NewL();

	// Navigation functions
	IMPORT_C void First();
	IMPORT_C void Next();

	// Query functions
	inline TBool Available();
	inline TAgnEntryId EntryId();
	inline TAgnUniqueId UniqueId();
	inline TBool HasBeenDeleted();
	inline CAgnEntry::TType Type();
	inline TAgnDateTime LastChangedDate();

	// Setter functions

	inline void SetAvailable(TBool aAvailable);
	inline void SetEntryId(TAgnEntryId aId);
	inline void SetUniqueId(TAgnUniqueId aId);
	inline void SetHasBeenDeleted(TBool aDeleted);
	inline void SetType(CAgnEntry::TType aType);
	inline void SetLastChangedDate(TAgnDateTime aDateTime);
	inline void SetPosition(TInt aPosition);

	CAgnSyncIter();

private:
	inline TInt Position();

private:
	RAgendaServ*	iServer;
	TBool			iAvailable;
	TInt			iPosition;
	TAgnEntryId		iEntryId;
	TAgnUniqueId	iUniqueId;
	TBool			iDeleted;
	CAgnEntry::TType iType;
	TAgnDateTime	iDate;
	};

// Inline functions

inline TBool CAgnSyncIter::Available()
	{
	return iAvailable;
	}

inline TAgnEntryId CAgnSyncIter::EntryId()
	{
	return iEntryId;
	}

inline TAgnUniqueId CAgnSyncIter::UniqueId()
	{
	return iUniqueId;
	}

inline TBool CAgnSyncIter::HasBeenDeleted()
	{
	return iDeleted;
	}

inline CAgnEntry::TType CAgnSyncIter::Type()
	{
	return iType;
	}

inline TAgnDateTime CAgnSyncIter::LastChangedDate()
	{
	return iDate;
	}

inline TInt CAgnSyncIter::Position()
	{
	return iPosition;
	}


// Setters

inline void CAgnSyncIter::SetAvailable(TBool aAvailable)
	{
	iAvailable = aAvailable;
	}


inline void CAgnSyncIter::SetEntryId(TAgnEntryId aId)
	{
	iEntryId = aId;
	}

inline void CAgnSyncIter::SetUniqueId(TAgnUniqueId aId)
	{
	iUniqueId = aId;
	}

inline void CAgnSyncIter::SetHasBeenDeleted(TBool aDeleted)
	{
	iDeleted = aDeleted;
	}

inline void CAgnSyncIter::SetType(CAgnEntry::TType aType)
	{
	iType = aType;
	}

inline void CAgnSyncIter::SetLastChangedDate(TAgnDateTime aDateTime)
	{
	iDate = aDateTime;
	}

inline void CAgnSyncIter::SetPosition(TInt aPosition)
	{
	iPosition = aPosition;
	}



#endif
