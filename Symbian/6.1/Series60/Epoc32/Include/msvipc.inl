// MSVIPC.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


//**********************************
// TMsvPackedChangeNotification
//**********************************

inline void TMsvPackedChangeNotification::Pack(TMsvServerChangeNotificationType aChangeType, const CMsvEntrySelection& aSelection, TInt aParameter1, TInt aParameter2)
//
// Packs all of the selection into the buffer
//
	{
	Pack(aChangeType, aSelection, aParameter1, aParameter2, 0, aSelection.Count()-1);
	}
