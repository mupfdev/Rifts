/*
* ============================================================================
*  Name     : CAknExPbarTimer from CTimer
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/


// INCLUDE FILES
#include "AknExPbarTimerModel.h"
#include "AknExPbarTimer.h"
#include "AknExPbarcontainer.h"


// CONSTANTS
const TInt KIntervalBaseTime = 10000;


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExPbarTimer::CAknExPbarTimer() 
                      : CTimer( EActivePriorityClockTimer )
    {
    }


// EPOC default constructor can leave.
void CAknExPbarTimer::ConstructL( TAknExPbarTimerModel* aModel,
                                        CAknExPbarContainer *aContainer )
    {
    CTimer::ConstructL();
    CActiveScheduler::Add( this );
    iModel = aModel;
    iContainer = aContainer;
    if ( iModel->iRunning )
        {
        Queue();
        }
    }

// Destructor
CAknExPbarTimer::~CAknExPbarTimer()
    {
    }


// ---------------------------------------------------------
// CAknExPbarTimer::RunL()
// Difinition of what to do, when timer event occurred.
// ---------------------------------------------------------
//
void CAknExPbarTimer::RunL()
    {
    iContainer->IncrementBarsAndDraw( iModel->iIncrement );
    Queue();
    }


// ---------------------------------------------------------
// CAknExPbarTimer::Queue()
// Set timer event interval
// ---------------------------------------------------------
//
void CAknExPbarTimer::Queue()
    {
    After( KIntervalBaseTime * iModel->iHundredths );
    }


// End of File
