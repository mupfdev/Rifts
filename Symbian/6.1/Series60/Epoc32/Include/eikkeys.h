// EIKKEYS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKKEYS_H__)
#define __EIKKEYS_H__

#if !defined(__E32KEYS_H__)
#include <e32keys.h>
#endif

enum TEikSidebarKeys
	{
	EEikSidebarMenuKey=ESpecialKeyBase,
	EEikSidebarClipKey,
	EEikSidebarIrdaKey,
	EEikSidebarZoomInKey,
	EEikSidebarZoomOutKey
	};


enum TEikAppbarKeys
	{
	EEikAppbarSystemKey=ESpecialKeyBase+0x40,
	EEikAppbarApp1Key,
	EEikAppbarApp2Key,
	EEikAppbarApp3Key,
	EEikAppbarApp4Key,
	EEikAppbarApp5Key,
	EEikAppbarApp6Key,
	EEikAppbarApp7Key,
	EEikAppbarApp8Key
	};


#endif
