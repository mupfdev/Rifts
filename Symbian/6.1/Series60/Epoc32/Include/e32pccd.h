// E32PCCD.H
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __E32PCCD_H__
#define __E32PCCD_H__

typedef signed int TSocket;

// Local media enumerates
enum TMediaDevice
	{EFixedMedia0,EFixedMedia1,EFixedMedia2,EFixedMedia3,
	EFixedMedia4,EFixedMedia5,EFixedMedia6,EFixedMedia7,
	ERemovableMedia0,ERemovableMedia1,ERemovableMedia2,ERemovableMedia3,EInvalidMedia};
#define __IS_REMOVABLE(aDevice) (aDevice>=ERemovableMedia0 && aDevice<=ERemovableMedia3)
#define __IS_FIXED(aDevice) (aDevice<=EFixedMedia7)

class TLDriveAssignInfo
	{
public:
	TMediaDevice iDevice;
	TInt iPriority;
	};

class TMediaDeviceAssignInfo
	{
public:
	TInt iFirstMedia;
	TInt iLastMedia;	
	};

#endif

