// AGMUPACT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMUPACT_H__
#define __AGMUPACT_H__


enum TAgnWhichInstances  
// Indicates which instances of anentry are affected when an entry is deleted
// or updated in the store
		{			
		ECurrentInstance,			// Only the current instance
		EAllInstances,				// All instances
		ECurrentAndFutureInstances,	// The current and all future instances
		ECurrentAndPastInstances	// The current and all past instances
		};

#endif
