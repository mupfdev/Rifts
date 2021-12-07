// EIKLBO.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// MEikListBoxObserverClass
//

#if !defined(__EIKLBO_H__)
#define __EIKLBO_H__

class CEikListBox; 


class MEikListBoxObserver
	{
public:
	enum TListBoxEvent
		{
		EEventEnterKeyPressed,
		EEventItemClicked,
		EEventItemDoubleClicked,
		EEventItemActioned,	// reported by dir tree and dir contents listboxes
		EEventEditingStarted,
		EEventEditingStopped
		};
public:
	virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType)=0;
	};

#endif
