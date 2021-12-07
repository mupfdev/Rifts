/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTADVERTISER_PAN__
#define __BTADVERTISER_PAN__

/** BTAdvertiser application panic codes */
enum TBTAdvertiserPanics 
    {
    EBTAdvertiserCmdNotRecognised = 1,
	EBTAdvertiserFailedToOpenSession,
	EBTAdvertiserFailedToOpenDatabase,
	EBTAdvertiserFailedToRemoveRecord
    };

inline void Panic(TBTAdvertiserPanics aReason)
	{ 
	User::Panic(_L("BTAdvertiser"), aReason);
	}
#endif // __BTADVERTISER_PAN__
