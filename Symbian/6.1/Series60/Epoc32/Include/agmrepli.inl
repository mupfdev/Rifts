// AGMREPLI.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TAgnReplicationData::TStatus TAgnReplicationData::Status() const
	{ return (iStatus); }

inline TBool TAgnReplicationData::HasBeenDeleted() const
	{ return (iHasBeenDeleted); }

inline void TAgnReplicationData::SetStatus(TStatus aStatus)
	{ 
	__ASSERT_DEBUG(aStatus == EOpen || aStatus == EPrivate || aStatus == ERestricted,
			Panic(_L("Invalud TStatus enum")));
	iStatus = aStatus; 
	}

inline void TAgnReplicationData::SetHasBeenDeleted(TBool aHasBeenDeleted)
	{ iHasBeenDeleted = aHasBeenDeleted; }

inline void TAgnReplicationData::IncCount()
	{ ++iCount; }

inline void TAgnReplicationData::DecCount()
	{ 
	__ASSERT_DEBUG(iCount,Panic(_L("Decrementing past 0")));
	--iCount;
	}

inline void TAgnReplicationData::SetCount(TUint aCount)
	{ iCount = aCount; }

inline TUint TAgnReplicationData::Count() const
	{ return (iCount); }
