// AGMEXCPT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMEXCPT_H__
#define __AGMEXCPT_H__

#include <e32base.h>
#include "agmids.h"
#include "agmdate.h"


// -------------------------- Local classes -----------------------------------
class TAgnException;
class CAgnExceptionList;


// ---------------------------- Referenced classes ------------------------------
class TStreamCArrayFix;



class TAgnException
//
// Stores the date of an exception (to a repeat entry) along with 
// the entry Id of any associated exception entry. 
// iEntryId has a null value for exceptions with no associated entry.
//
	{
public:
	IMPORT_C TAgnException();
	IMPORT_C TAgnException(TAgnDate aDate);
	inline void SetDate(TAgnDate aDate);
	inline TAgnDate Date() const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	friend class CAgnExceptionList;			// CAgnException requires access to the offset
											// of iDate when constructing key
private:									 
	TAgnDate 	iDate;
	};


class CAgnExceptionList : public CArrayFixFlat<TAgnException>
//
// A list of exception entrys
//
	{
public:
	enum {EGranularity=4};
	inline CAgnExceptionList();
	TBool Compare(const CAgnExceptionList* aExceptions) const;		
	inline TInt InsertL(const TAgnException& aException);
	inline TInt Find(const TAgnException& aException,TInt& aPos);
private:
	TKeyArrayFix iDateKey; // When searching etc. for exceptions in an exception list its done via the date field
	};


#include "agmexcpt.inl"

#endif
