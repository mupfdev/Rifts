/*
* ============================================================================
*  Name     : AknKeyLock.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNKEYLOCK.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

// Avkon KeyLock Client


#if !defined(__AKNKEYLOCK_H__)
#define __AKNKEYLOCK_H__

#include <e32base.h>

#include <aknnotifystd.h>

class RAknKeyLock : public RNotifier
	{
public:
	IMPORT_C void EnableKeyLock();
	IMPORT_C void DisableKeyLock();
	IMPORT_C TBool IsKeyLockEnabled();
	IMPORT_C void EnableSoftNotifications(TBool aEnable);
	IMPORT_C void OfferKeyLock();
	IMPORT_C void CancelAllNotifications();
private:
	void SendMessage(TKeyLockNotifierReason aMessage);
	};

#endif
