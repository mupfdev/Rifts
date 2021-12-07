/* Copyright (c) 2001, Nokia. All rights reserved */
#include <w32std.h>
#include <e32cons.h>
#include <in_sock.h>
#include <nifman.h>

#include "servertimeoutnotify.h"
#include "servertimeouttimer.h"

//
// CTimeOutTimer: Timer for timing animation
//

// Call the base class constructor 
CTimeOutTimer::CTimeOutTimer(const TInt aPriority, MTimeoutNotify& aTimeOutNotify)
    : CTimer(aPriority), iNotify(aTimeOutNotify)
    {
    }


// Cancel any on going events before deleting the object
CTimeOutTimer::~CTimeOutTimer()
    {
    Cancel();
    }


// Standard Epoc construction method
CTimeOutTimer* CTimeOutTimer::NewL(const TInt aPriority, MTimeoutNotify& aTimeOutNotify)
    {
    CTimeOutTimer* self = CTimeOutTimer::NewLC(aPriority, aTimeOutNotify);
    CleanupStack::Pop(); // self
    return self;
    }

// Standard Epoc construction method
CTimeOutTimer* CTimeOutTimer::NewLC(const TInt aPriority, MTimeoutNotify& aTimeOutNotify)
    {
    CTimeOutTimer *self = new (ELeave) CTimeOutTimer(aPriority, aTimeOutNotify);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// Construct the actual timer
void CTimeOutTimer::ConstructL()
    {
    // Call the base class ConstructL
    CTimer::ConstructL();

    // Add this timer to the active scheduler
    CActiveScheduler::Add(this);
    }

void CTimeOutTimer::RunL()
    {
    // When the timer times out notify the object registered with this timer
    iNotify.TimedOut();
    }

