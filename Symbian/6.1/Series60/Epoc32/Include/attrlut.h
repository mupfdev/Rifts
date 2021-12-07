// ATTRLUT.H
// Copyright (C) Symbian LTD, 2000
//
// Attribute Look-Up-Table header
//
// The Attribute Lookup Table maintains a global set of unique IDs to be defined for document
// node attributes and language tags. It does this by generating a unique ID for any descriptor
// passed to it. This descriptor is in fact a pointer to a copy of the string. Once a string
// has been seen once, any further references to it will map back to the same ID (pointer)
// value.
//

#if !defined(__CWAPENGINE_LUT_H__)
#define __CWAPENGINE_LUT_H__

#include <e32base.h>

class RTest;
class CAttributeLookupTableNode;

class CAttributeLookupTable : public CBase
{
public:
	IMPORT_C ~CAttributeLookupTable();
	IMPORT_C static CAttributeLookupTable* CAttributeLookupTable::NewL();
	IMPORT_C const HBufC* Des2IDL( const TDesC& ); // map descriptor to ID
	IMPORT_C const HBufC* KeyExists( const TDesC& ); // check to see if the given descriptor already exists
	IMPORT_C void Reset(); // clear the table

	// debug hook
	typedef enum{
		EPrint,
		EPrintWholeTable
	} TDebugSelectorType;
	IMPORT_C void Debug( TDebugSelectorType aSelector, TAny* aParam1, TAny* aParam2 );

private:
	CAttributeLookupTable();
	void ConstructL();
	CAttributeLookupTableNode* FindDes( const TDesC& );
	TUint Hash( const TDesC& );
	CArrayPtrFlat<CArrayPtrSeg<CAttributeLookupTableNode> >* iList;
};


#endif // __CWAPENGINE_LUT_H__