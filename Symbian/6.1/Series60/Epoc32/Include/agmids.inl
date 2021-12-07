// AGMIDS.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


// ----------------------------------- TAgnId ----------------------------------------------
inline TBool TAgnId::operator<(TAgnId aId) const
	{ return (iId < aId.iId);}

inline TBool TAgnId::operator>(TAgnId aId) const
	{ return (iId > aId.iId);}

inline TAgnId TAgnId::Id() const
	{ return (iId); }

inline void TAgnId::SetId(TAgnId aId)
	{ iId=aId.iId; }

inline TAgnId::TAgnId(TUint aId)
	{ iId = aId; }

inline TStreamId TAgnId::StreamId() const
	{ return (iId & KMaskStreamIdValue); }

inline TUint TAgnId::Value() const
	{ return (iId); }



// ------------------------------- TAgnInstanceId -----------------------------------------
inline TAgnDate TAgnInstanceId::Date() const
	{ return (iDate); }

inline void TAgnInstanceId::SetDate(TAgnDate aDate)
	{ iDate=aDate; }

inline TBool TAgnInstanceId::IsNullInstanceId() const
	{ return (iDate==AgnDateTime::NullDate()); }
	
inline void TAgnInstanceId::SetIdAndDate(TAgnEntryId aId,TAgnDate aDate)
	{ iId=aId.Value(); iDate=aDate; }




// ------------------------------- TAgnInstanceDateTimeId ------------------------
inline void TAgnInstanceDateTimeId::SetStartDate(TAgnDate aDate) 
	{ iStartDateTime.SetDate(aDate); }

inline void TAgnInstanceDateTimeId::SetEndDate(TAgnDate aDate)
	{ iEndDateTime.SetDate(aDate); }

inline void TAgnInstanceDateTimeId::SetStartTime(TAgnTime aTime)
	{ iStartDateTime.SetTime(aTime); }

inline void TAgnInstanceDateTimeId::SetEndTime(TAgnTime aTime) 
	{ iEndDateTime.SetTime(aTime); }


// ----------------------------------- TAgnUniqueId -------------------------------------------
//inline TUint TAgnUniqueId::operator++()
//	{ return (++iUId); } 

//inline TUint TAgnUniqueId::operator--() 
//	{ return (--iUId); } 

inline TBool TAgnUniqueId::operator==(TAgnUniqueId aUId) const
	{ return (iUId==aUId.iUId); }

inline TBool TAgnUniqueId::operator!=(TAgnUniqueId aUId) const
	{ return (iUId!=aUId.iUId); }

inline TBool TAgnUniqueId::operator<(TAgnUniqueId aUId) const
	{ return (iUId < aUId.iUId);}

inline TBool TAgnUniqueId::operator>(TAgnUniqueId aUId) const
	{ return (iUId > aUId.iUId);}

inline void TAgnUniqueId::SetId(TUint aUId)
	{ iUId=aUId; }

inline TUint TAgnUniqueId::Id() const
	{ return (iUId); }

inline void TAgnUniqueId::SetNullId()
	{ iUId=0; }

inline TBool TAgnUniqueId::IsNullId()
	{ return (iUId==0); }

// ----------------------------------- TAgnMapId ----------------------------------------------
template<class TypeId>
inline TypeId TAgnMapId<TypeId>::AgmId()	const
	{ return (iAgmId); }

template<class TypeId>
inline TAgnUniqueId TAgnMapId<TypeId>::UniqueId() const
	{ return (iUniqueId); }

template<class TypeId>
inline void TAgnMapId<TypeId>::SetAgmId(TypeId id)
	{ iAgmId=id; }

template<class TypeId>
inline void TAgnMapId<TypeId>::SetUniqueId(TAgnUniqueId uid)
	{ iUniqueId=uid; }
