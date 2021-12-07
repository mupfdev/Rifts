/*
* ============================================================================
*  Name     : AknKeys.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNKEYS.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNKEYS_H__)
#define __AKNKEYS_H__

#include <w32std.h>
#include <uikon.hrh>

/* Keyboard utilities
 */
class AknKeys 
    {
public:
    static TBool IsNumberKey(const TKeyEvent& aKeyEvent, TEventCode aType);
    };



#endif

