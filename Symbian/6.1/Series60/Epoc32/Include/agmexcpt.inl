// AGMEXCPT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//



// -------------------------- TAgnException ------------------------------
inline TAgnDate TAgnException::Date() const
	{ return (iDate); }

//inline TAgnEntryId TAgnException::Id() const
//	{ return (iEntryId); }

inline void TAgnException::SetDate(TAgnDate aDate)
	{ iDate=aDate; }

//inline void TAgnException::SetId(TAgnEntryId aId)
//	{ iEntryId=aId; }



// -------------------------- CAgnExceptionList -------------------------------------------
inline CAgnExceptionList::CAgnExceptionList()
	:CArrayFixFlat<TAgnException>(EGranularity),
	iDateKey(_FOFF(TAgnException,TAgnException::iDate),ECmpNormal8,sizeof(TAgnDate))
	{
	}

inline TInt CAgnExceptionList::InsertL(const TAgnException& aException)
	{	return (InsertIsqL(aException,iDateKey)); }

inline TInt CAgnExceptionList::Find(const TAgnException& aException,TInt& aPos)
	{ return (FindIsq(aException,iDateKey,aPos)); }

//------------------------ streaming operators for CAgnExceptionList ---------------------
inline RWriteStream& operator<<(RWriteStream& aStream,const CAgnExceptionList& aExceptions)
	{
	return (aStream << (const CArrayFix<TAgnException>&)aExceptions); 
	}

inline RReadStream& operator>>(RReadStream& aStream,CAgnExceptionList& aExceptions)
	{
	return (aStream >> (CArrayFix<TAgnException>&)aExceptions); 
	}
