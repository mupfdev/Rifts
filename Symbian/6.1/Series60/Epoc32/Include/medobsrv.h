// MEDOBSRV.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MEDOBSRV_H__
#define __MEDOBSRV_H__

#include <e32def.h>

class MEditObserver
	{
public:
	// Observer function called by CRichText to signal changes to the text
	// buffer within it. A pointer to this function must be passed in to
	// a CRichText instance by <rich text instance>.SetEditObserver(<ptr>).
	// aStart is the start position of the edit and aExtent is the number
	// of characters added or, if negative, deleted after this position.
	virtual void EditObserver(TInt aStart, TInt aExtent) = 0;
	};

#endif
