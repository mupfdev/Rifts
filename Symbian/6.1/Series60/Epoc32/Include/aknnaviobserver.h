/*
* ============================================================================
*  Name     : AknNaviObserver.h
*  Part of  : Avkon
*
*  Description:
* 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNNAVIOBSERVER.H
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNNAVIOBSERVER_H__)
#define __AKNNAVIOBSERVER_H__

class MAknNavigationObserver
    {
public:
    enum TAknNavigationEvent
        {
        ENaviEventHandleNavigation = 0x0010,
        ENaviEventLeftMostItemReached,
        ENaviEventRightMostItemReached,
        ENaviEventOneItemExists,
        ENaviEventRedrawNeeded
        };
    };

#endif // __AKNNAVIOBSERVER_H__
