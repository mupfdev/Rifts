/*
* ============================================================================
*  Name     : CAknExQueryGlobalListObserver from %name%
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

//  INCLUDES
#include <eikenv.h>
#include <e32base.h>
#include <coemain.h>
#include <AknGlobalNote.h>
#include <aknnotewrappers.h>
#include <AknExQuery.rsg>
#include "AknExQuery.hrh"
#include "AknExQueryContainer.h"

//  CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// Two-phased constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryGlobalListObserver* CAknExQueryGlobalListObserver
                    ::NewL(CAknExQueryContainer* aContainer)  
    {
    CAknExQueryGlobalListObserver* active =
        new(ELeave) CAknExQueryGlobalListObserver(aContainer);
    CleanupStack::PushL(active);
    active->ConstructL();
    CleanupStack::Pop();        // active
    return active;
    }


// ----------------------------------------------------------------------------
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryGlobalListObserver::~CAknExQueryGlobalListObserver()
    {
    Cancel();
    }

// ----------------------------------------------------------------------------
// CAknExQueryGlobalListObserver::Start
// Start the activator.
// (other items were commented in a header).
// ----------------------------------------------------------------------------
//
void CAknExQueryGlobalListObserver::Start()
    {
    SetActive();
    }

// ----------------------------------------------------------------------------
// C++ default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryGlobalListObserver::CAknExQueryGlobalListObserver
                   (CAknExQueryContainer* aContainer) 
                        : CActive(EActivePriorityDefault)
                        , iContainer(aContainer)
    {
    }

// ----------------------------------------------------------------------------
// EPOC default constructor can leave.
// ----------------------------------------------------------------------------
//
void CAknExQueryGlobalListObserver::ConstructL()
    {
    CActiveScheduler::Add(this);
    }

// ----------------------------------------------------------------------------
// CAknExQueryGlobalListObserver::RunL
// Handle an event.
// ----------------------------------------------------------------------------
//
void CAknExQueryGlobalListObserver::RunL()
    {
    if (iSelectItemFlag)
        {
        TBuf<80> msg(NULL);
        CEikonEnv::Static()->ReadResource( msg, R_AKNEXQUERY_RECEIVED_MESSAGE );
        msg.AppendNum(iStatus.Int());
        CAknQueryDialog* dlg = new (ELeave) CAknQueryDialog(
            msg, 
            CAknQueryDialog::ENoTone);
        dlg->ExecuteLD( R_AKNEXQUERY_CONFIRMATION_QUERY2);
        }
        
    Cancel();
    }

// ----------------------------------------------------------------------------
// CAknExQueryGlobalListObserver::DoCancel
// Implement the Cancel protocol.
// ----------------------------------------------------------------------------
//
void CAknExQueryGlobalListObserver::DoCancel()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryGlobalListObserver::SetSelectItemFlag
// Set iSelectItemFlag.
// ----------------------------------------------------------------------------
//
void CAknExQueryGlobalListObserver::SetSelectItemFlag()
    {
    iSelectItemFlag = ETrue;
    }

// ----------------------------------------------------------------------------
// CAknExQueryGlobalListObserver::SetSelectItemFlag
// Set iSelectItemFlag.
// ----------------------------------------------------------------------------
//
void CAknExQueryGlobalListObserver::UnsetSelectItemFlag()
    {
    iSelectItemFlag = EFalse;
    }
