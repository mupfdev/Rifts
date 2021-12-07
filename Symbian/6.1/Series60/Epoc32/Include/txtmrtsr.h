// TXTMRTSR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTMRTSR_H__
#define __TXTMRTSR_H__

#include <e32std.h>

class CStreamStore;

//
// A call back for determining a store as a function of the document position.
// In practice, used in the potentially defered restoring of new pictures from a store.
// The store might not actually vary with document position, in which case the function is
// guaranteed not to leave.
class MRichTextStoreResolver
	{
public:
	virtual const CStreamStore& StreamStoreL(TInt aPos)const=0;
	};

#endif

