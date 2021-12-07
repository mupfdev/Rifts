// AKNEDSTSOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Epoc Editor State Object Observer


#if !defined(__AKNEDSTSOBS_H__)
#define __AKNEDSTSOBS_H__

class CAknEdwinState;

class MAknEdStateObserver
	{
public:
	enum EAknEdwinStateEvent
		{
		EAknEdwinStateEventStateUpdate
		};
public:
	virtual void HandleAknEdwinStateEventL(CAknEdwinState* aAknEdwinState, EAknEdwinStateEvent aEventType) = 0;
	};

#endif
