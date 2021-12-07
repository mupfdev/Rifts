// AGMMITER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMMITER_H__
#define __AGMMITER_H__

#include <s32stor.h>
#include <s32cont.h>




// ------------------------- References classes -------------------------
class CAgnEntryModel;
class CAgnModelStreamIdSet;
class CAgnStreamIdSet;
class TAgnEntryId;
class CAgnEntryManager;
class CStreamStore;
class TStreamId;


class TAgnEntryIter
//
// Iterates over the entries in a model
//
	{
public:		 
	IMPORT_C TAgnEntryIter(const CAgnEntryModel* aModel);
	IMPORT_C TBool SetToFirstL();	// position to the first entry
	IMPORT_C TBool NextL();		// position to the next entry
	IMPORT_C TAgnEntryId At();	// return the entry id of the current entry
	inline TInt NumCurrentStream() const;	// returns which stream the iterator is currently positioned on
	inline TInt NumStreams() const;	// returns the total number of streams
	inline TInt NumCurrentEntry() const; // returns which entry within the current stream the iterator is positioned on
	IMPORT_C TInt NumEntriesForStream() const; // number of entries in the current stream
private:	
	CAgnStreamIdSet*			iStreamIdSet;
	const CAgnEntryManager*		iEntryManager;
	TInt						iEntryIter;
	TUint						iCurrentStream; 
	TUint						iStreamCount; 
TInt iEntryCount;
	};

inline TInt TAgnEntryIter::NumCurrentStream() const	{ return (iCurrentStream); }
inline TInt TAgnEntryIter::NumStreams() const  { return (iStreamCount); }
inline TInt TAgnEntryIter::NumCurrentEntry() const { return (iEntryIter); }
#endif