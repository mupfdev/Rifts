/*
* ============================================================================
*  Name     : CAknExSpaneContextView from CAknView
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <eikfutil.h>
#include <aknconsts.h>
#include <akncontext.h>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneContextView.h"
#include "AknExSpaneContextViewContainer.h"


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneContextView::CAknExSpaneContextView() :
    iView(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneContextView::ConstructL()
    {
    BaseConstructL(R_AKNEXSPANE_CONTEXT_VIEW);
    }

// Destructor
CAknExSpaneContextView::~CAknExSpaneContextView()
    {
    if (iView)
        AppUi()->RemoveFromStack(iView);
    delete iView;
    }


// ---------------------------------------------------------
// TUid CAknExSpaneContextView::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExSpaneContextView::Id() const
    {
    return TUid::Uid(EAknExSpaneContextViewId);
    }

// ---------------------------------------------------------
// CAknExSpaneContextView::HandleCommandL(TInt aCommand)
// handles the commands
// ---------------------------------------------------------
//
void CAknExSpaneContextView::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EAknExSpaneCmdNextTest:
            {
            if (iView)
                {             
                iView->RunNextTestL();
                }
            break;
            }

        case EAknExSpaneCmdLastTest:
            {
            if (iView)
                {             
                iView->RunLastTestL();
                }
            break;
            }
         
        default:
            {
            AppUi()->HandleCommandL(aCommand);
            break;
            }
        }
    }

// ---------------------------------------------------------
// CAknExSpaneContextView::HandleStatusPaneSizeChange()
// Control of the size change event
// ---------------------------------------------------------
//
void CAknExSpaneContextView::HandleStatusPaneSizeChange()
    {
    if (iView)
        {
        // Main pane and status pane are partly overlapping is status pane has idle layout. 
        TRect cr = ClientRect();  
        if (cr.iTl.iY == Kqpn_height_status_pane_idle)
            {
            cr.iTl.iY = Kqpn_height_status_pane_usual;
            }
        iView->SetRect(cr);
        }
    }

// ---------------------------------------------------------
// CAknExSpaneContextView::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExSpaneContextView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iView = new(ELeave) CAknExSpaneContextViewContainer;
    iView->SetMopParent(this);
    TRect cr = ClientRect();

    if (cr.iTl.iY == Kqpn_height_status_pane_idle)
        {
        cr.iTl.iY = Kqpn_height_status_pane_usual;
        }
    iView->ConstructL(cr);
    AppUi()->AddToStackL(*this,iView);
    }

// ---------------------------------------------------------
// CAknExSpaneContextView::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExSpaneContextView::DoDeactivate()
    {
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    iView = NULL;
    }

// End of File
