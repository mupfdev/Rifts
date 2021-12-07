// AGMIDS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMIDS_H__
#define __AGMIDS_H__

#include <s32stor.h>
#include "agmdate.h"

class TAgnTodoListId;

//#pragma message("needs some reworking")
// !!! TAgnId should be a simple class without the partialid and stream id stuff (which
// should be moved to TAgnEntryId) - then TAgnUniqueId becomes redundant

class TAgnId
	{
public:
	IMPORT_C TAgnId();
	IMPORT_C TAgnId(TStreamId aId); 
	IMPORT_C TAgnId(TStreamId aStreamId,TUint aPartialId);
	inline TAgnId(TUint aId);
	IMPORT_C TBool operator==(TAgnId aId) const;
	IMPORT_C TBool operator!=(TAgnId aId) const;
	inline TBool operator<(TAgnId aId) const;
	inline TBool operator>(TAgnId aId) const;
	inline TAgnId Id() const;
	inline TStreamId StreamId() const;
	void SetStreamId(TStreamId aId);
	void SetPartialId(TUint aId);
	TUint PartialId() const;
	inline TUint Value() const;
	inline void SetId(TAgnId aId);
	IMPORT_C TBool IsNullId() const;
	IMPORT_C void SetNullId();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TUint32 iId;
	};


class TAgnEntryId : public TAgnId
//
// Uniquely identifies an entry
//
	{
public:
	IMPORT_C TAgnEntryId();
	IMPORT_C TAgnEntryId(TAgnId aId);	
	};


class TAgnInstanceId : public TAgnEntryId
//
// Identifies an *instance* of an entry, i.e. a Id and a date
//
	{
public:								
	IMPORT_C TAgnInstanceId();
	IMPORT_C TAgnInstanceId(TAgnEntryId aId,TAgnDate=AgnDateTime::NullDate());
	IMPORT_C TAgnInstanceId(TAgnEntryId aId,TTime aDate);
	IMPORT_C TBool operator==(TAgnInstanceId aId) const;
	IMPORT_C TBool operator!=(TAgnInstanceId aId) const;
	IMPORT_C void SetNullInstanceId();
	inline TAgnDate Date() const;
	inline void SetDate(TAgnDate aDate);
	inline void SetIdAndDate(TAgnEntryId aId,TAgnDate aDate);
	inline TBool IsNullInstanceId() const;
	
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TAgnDate 	iDate;
	TUint16		iFiller;
	};


class TAgnInstanceDateTimeId : public TAgnInstanceId
	{
public:
	IMPORT_C TTime StartDate() const;
	IMPORT_C TTime EndDate() const;
	IMPORT_C TTimeIntervalMinutes StartTime() const;
	IMPORT_C TTimeIntervalMinutes EndTime() const;
	IMPORT_C TBool HasNullStartTime() const;
	IMPORT_C TBool HasNullEndTime() const;
	inline void SetStartDate(TAgnDate aDate);
	inline void SetEndDate(TAgnDate aDate);
	inline void SetStartTime(TAgnTime aTime);
	inline void SetEndTime(TAgnTime aTime);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
private:
	TAgnDateTime iStartDateTime;
	TAgnDateTime iEndDateTime;
	};


class TAgnTodoListId : public TAgnId
//
// Identifies a todo list
//
	{
public:
	IMPORT_C TAgnTodoListId();
	IMPORT_C TAgnTodoListId(TAgnId aId);
	};

class TAgnUniqueId
	{
public:
	IMPORT_C TAgnUniqueId(); 
	IMPORT_C TAgnUniqueId(TUint aValue); 
	inline TBool operator==(TAgnUniqueId aUId) const;
	inline TBool operator!=(TAgnUniqueId aUId) const;
	inline TBool operator<(TAgnUniqueId aUId) const;
	inline TBool operator>(TAgnUniqueId aUId) const;
	inline TUint Id() const;
	inline void SetId(TUint aUId);
	inline void SetNullId();
	inline TBool IsNullId();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	TUint32 iUId;
	};


class CAgnUniqueView;
template<class TypeId>
class TAgnMapId
	{
public:
	friend CAgnUniqueView;
	inline TypeId AgmId() const;
	inline TAgnUniqueId UniqueId() const;
	inline void SetAgmId(TypeId id);
	inline void SetUniqueId(TAgnUniqueId uid);
protected:
	TypeId			iAgmId;
	TAgnUniqueId	iUniqueId;
	};


#include "agmids.inl"

#endif
