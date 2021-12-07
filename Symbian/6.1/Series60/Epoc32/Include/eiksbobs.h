// EIKSBOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// MEikScrollBarObserverClass
//
#if !defined(__EIKSBOBS_H__)
#define __EIKSBOBS_H__

enum TEikScrollEvent
	{
	EEikScrollLeft=1,
	EEikScrollUp,
	EEikScrollRight,
	EEikScrollDown,
	EEikScrollPageLeft,
	EEikScrollPageUp,
	EEikScrollPageRight,
	EEikScrollPageDown,
	EEikScrollHome,
	EEikScrollTop,
	EEikScrollEnd,
	EEikScrollBottom,
	EEikScrollThumbDragHoriz,
	EEikScrollThumbDragVert,
	EEikScrollThumbReleaseHoriz,
	EEikScrollThumbReleaseVert
	};

class CEikScrollBar;
class MEikScrollBarObserver
	{
public:
	virtual void HandleScrollEventL(CEikScrollBar* aScrollBar, TEikScrollEvent aEventType)=0;
	};

#endif
