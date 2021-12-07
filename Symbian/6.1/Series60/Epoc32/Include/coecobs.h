// COECOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__COECOBS_H__)
#define __COECOBS_H__

class CCoeControl;

/**
 * The MCoeControlObserver class specifies the protocol for a control to send events to
 * another control.
 */
class MCoeControlObserver
	{
public:
	enum TCoeEvent
		{
		EEventRequestExit,
		EEventRequestCancel,
		EEventRequestFocus,
		EEventPrepareFocusTransition,
		EEventStateChanged,
		EEventInteractionRefused
		};
public:
	/**
	 * Handles an event of type aEventType reported by the control aControl to this observer.
	 */
	virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType)=0;
	};

#endif
