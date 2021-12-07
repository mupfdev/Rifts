// FLDBASE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLDBASE_H__
#define __FLDBASE_H__

#include <e32std.h>
#include <e32base.h>
#include <s32stor.h>

// Classes defined:
class CTextField;
class MTextFieldFactory;


class CTextField : public CBase
// Abstract class: derive from this to instantiate a particular type of field (eg date etc)
	{
public:
	IMPORT_C virtual TStreamId StoreL(CStreamStore& aStore)const; // calls ExternalizeL()
	IMPORT_C virtual void RestoreL(const CStreamStore& aStore,TStreamId aId); // calls InternalizeL()
	//
	// Should be replaced by concrete derived classes.
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const; // Externalize state info for the field
	virtual void InternalizeL(RReadStream& aStream)=0;
	//
	// sets aValueText to the current value of the field if the buffer is large enough, else returns the required length
	virtual TInt Value(TPtr& aValueText)=0; 
	//
	// return the uid type of the concrete field
	virtual TUid Type()const=0;
	};


class MTextFieldFactory
// Abstract class that should be derived from by any application that wishes to support fields
	{
public:
	virtual CTextField* NewFieldL(TUid aFieldType)=0; 
	// Creates a field of the type specified
	// Returns NULL if it does not recognise/support the field type
	};


#endif
