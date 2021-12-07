// AKNBORDERS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AKNBORDERS_H__
#define __AKNBORDERS_H__

#include <e32std.h>

class AknBorderId
	{
public:
	enum TAknBorderId
		{
		EAknBorderNotePopup = 0x800110,		// also valid for query, find?
		EAknBorderMenuPopup,
		EAknBorderMenuSubmenuPopup,
		EAknBorderNotificationPopup,
		EAknBorderGroupedNotificationsPopup,
		EAknBorderCharacterSelectionPopup,
		EAknBorderPopups, // for list queries (looks like the menu things DOES NOT work for dialogs, I dunno why...)
		EAknBorderPopupsWithHeading,
		EAknBorderMax			// End marker for avkon borders. Not a real border type.
		};
	};


#endif //__AKNBORDERS_H__
