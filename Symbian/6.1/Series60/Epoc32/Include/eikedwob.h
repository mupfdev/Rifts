// EIKEDWOB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKEDWOB_H__)
#define __EIKEDWOB_H__

class CEikEdwin;

class MEikEdwinObserver
	{
public:
	enum TEdwinEvent
		{
		EEventFormatChanged,
		EEventNavigation,
		EEventTextUpdate
		};
public:
	virtual void HandleEdwinEventL(CEikEdwin* aEdwin,TEdwinEvent aEventType)=0;
	};

class MEikEdwinSizeObserver
	{
public:
	enum TEdwinSizeEvent
		{
		EEventSizeChanging
		};
public:
	virtual TBool HandleEdwinSizeEventL(CEikEdwin* aEdwin, TEdwinSizeEvent aEventType, TSize aDesirableEdwinSize)=0;
	};

#endif
