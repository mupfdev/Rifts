// AGMREPLI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#ifndef __AGMREPLI_H__
#define __AGMREPLI_H__

#include "agmdate.h"

class TAgnReplicationData
	{
public:
	enum TStatus {EOpen, EPrivate, ERestricted};

	IMPORT_C TAgnReplicationData();
	inline TStatus Status() const;
	inline TBool HasBeenDeleted() const;
	IMPORT_C TTime LastChangedDate() const;
	inline void SetStatus(TStatus aStatus);
	inline void SetHasBeenDeleted(TBool aHasBeenDeleted);
	IMPORT_C void SetLastChangedDate();
	inline void IncCount();
	inline void DecCount();
	inline void SetCount(TUint aCount);
	inline TUint Count() const;
	IMPORT_C void Reset();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TStatus			iStatus;
	TBool			iHasBeenDeleted;
	TUint			iCount;
	TAgnDateTime	iLastChangedDate;
	};

#include "agmrepli.inl"

#endif
