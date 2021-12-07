/*
* ============================================================================
*  Name     : CAknExPbarView from CAknView
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/
// INCLUDE FILES

#include <Avkon.hrh>
#include <aknviewappui.h>
#include <akntabgrp.h>
#include <aknnavide.h>

#include <AknExPbar.rsg>
#include "AknExPbarView.h"
#include "AknExPbarContainer.h"
#include "AknExPbarTimer.h"

const TInt KInitIncrement = 0;
const TInt KStepBackValue = ( -8 );
const TInt KJumpBackValue = ( -15 );

const TInt KTimerModelHundredths = 10;
const TInt KTimerModelIncrement = 1;
const TBool KTimerModelRunning = ETrue;


// ================= MEMBER FUNCTIONS =======================

//----------------------------------------------------------
// C++ default constructor
// ---------------------------------------------------------
CAknExPbarView::CAknExPbarView()
                 : iContainer( NULL ),
                   iTimer( NULL )
    {
    }


// ---------------------------------------------------------
// CAknExPbarView::ConstructL( const TRect& aRect )
// EPOC two-phased constructor
// ---------------------------------------------------------
void CAknExPbarView::ConstructL()
    {
    BaseConstructL( R_AKNEXPBAR_VIEW1 );
    }

// ---------------------------------------------------------
// CAknExPbarView::~CAknExPbarView()
// Destructor.
// ---------------------------------------------------------
CAknExPbarView::~CAknExPbarView()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iTimer;
    iTimer = NULL;

    delete iContainer;
    iContainer = NULL;

    }

// ---------------------------------------------------------
// TUid CAknExPbarView::Id()
// returns view Id.
// ---------------------------------------------------------
TUid CAknExPbarView::Id() const
    {
    return KViewId;
    }

// ---------------------------------------------------------
// CAknExPbarView::HandleCommandL( TInt aCommand )
// handles commands.
// ---------------------------------------------------------
void CAknExPbarView::HandleCommandL( TInt aCommand )
    {   
    TInt increment = KInitIncrement;
    
    switch ( aCommand )
        {
        case EAknCmdExit:
        case EAknSoftkeyBack:
        case EEikCmdExit:
            // Timer object seems not to be destroied correctly
            // by destructor. 
            delete iTimer;
            iTimer = NULL;
            AppUi()->HandleCommandL( EEikCmdExit );
            return; // returns if exit

        case EProgCmdStepBackwards:
            iContainer->SetTestNumber(aCommand);
            increment = KStepBackValue;
            break;

        case EProgCmdReset:
            iContainer->SetTestNumber(aCommand);
            iContainer->ResetAllValues();
            break;

        case EProgCmdChangeSetFinalValue1:
            iContainer->SetTestNumber(aCommand);
            iContainer->SetFinalValue(EFalse);
            break;
        case EProgCmdChangeSetFinalValue2:
            iContainer->SetTestNumber(aCommand);
            iContainer->SetFinalValue(ETrue);
            break;
        case EProgCmdChangeShowInfo1:
            iContainer->SetTestNumber(aCommand);
            iContainer->ShowInfo(EAknExpBarBar1);
            break;
        case EProgCmdChangeShowInfo2:
            iContainer->SetTestNumber(aCommand);
            iContainer->ShowInfo(EAknExpBarBar2);
            break;
        case EProgCmdChangeShowInfo3:
            iContainer->SetTestNumber(aCommand);
            iContainer->ShowInfo(EAknExpBarBar3);
            break;
        case EProgCmdChangeShowInfo4:
            iContainer->SetTestNumber(aCommand);
            iContainer->ShowInfo(EAknExpBarBar4);
            break;
        case EProgSoftkeyNext:
            iContainer->AutoTest();
            break;
        default:
            AppUi()->HandleCommandL( aCommand );
            return; // returns if default

        } // End switch ( aCommand )
        
    if ( increment )
        {
        iContainer->IncrementBarsAndDraw( increment );
        }
        

   }

// ---------------------------------------------------------
// CAknExPbarView::HandleClientRectChange()
// 
// ---------------------------------------------------------
void CAknExPbarView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------
// CAknExPbarView::DoActivateL(...)
// 
// ---------------------------------------------------------
void CAknExPbarView::DoActivateL(
   const TVwsViewId& /*aPrevViewId*/, TUid /*aCustomMessageId*/,
   const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new( ELeave ) CAknExPbarContainer;
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );

    ConstructTimerModel();
    ConstructTimerL();
    }

// ---------------------------------------------------------
// CAknExPbarView::HandleCommandL( TInt aCommand )
// 
// ---------------------------------------------------------
void CAknExPbarView::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iTimer;
    iTimer = NULL;
    
    delete iContainer;
    iContainer = NULL;


    }

// ----------------------------------------------------
// CAknExPbarView::ConstructTimerModel()
// Set Timer Model
// ----------------------------------------------------
void CAknExPbarView::ConstructTimerModel()
    {
    iTimerModel.iHundredths = KTimerModelHundredths;
    iTimerModel.iIncrement = KTimerModelIncrement;
    iTimerModel.iRunning = KTimerModelRunning;
    }


// ----------------------------------------------------
// CAknExPbarView::ConstructTimerL()
// Set Timer
// ----------------------------------------------------
void CAknExPbarView::ConstructTimerL()
    {
    iTimer = new( ELeave ) CAknExPbarTimer;
    iTimer->ConstructL( &iTimerModel, iContainer );
    }

// End of File

