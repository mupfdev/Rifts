/*
* ============================================================================
*  Name     : CAknExSpanePopupView from CAknView
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <aknconsts.h>
#include <akncontext.h>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpanePopupView.h"
#include "AknExSpanePopupViewContainer.h"

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpanePopupView::CAknExSpanePopupView():
    iView(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpanePopupView::ConstructL()
    {
    BaseConstructL(R_AKNEXSPANE_POPUP_VIEW);
    }

// Destructor
CAknExSpanePopupView::~CAknExSpanePopupView()
    {
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    }

// ---------------------------------------------------------
// TUid CAknExSpanePopupView::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExSpanePopupView::Id() const
    {
    return TUid::Uid(EAknExSpanePopUpViewId);
    }

// ---------------------------------------------------------
// CAknExSpanePopupView::HandleCommandL(TInt aCommand)
// handles the commands
// ---------------------------------------------------------
//
void CAknExSpanePopupView::HandleCommandL(TInt aCommand)
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
// CAknExSpanePopupView::HandleStatusPaneSizeChange()
// Control of the size change event
// ---------------------------------------------------------
//
void CAknExSpanePopupView::HandleStatusPaneSizeChange()
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
// CAknExSpanePopupView::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExSpanePopupView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iView = new(ELeave) CAknExSpanePopupViewContainer;
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
// CAknExSpanePopupView::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExSpanePopupView::DoDeactivate()
    {
    iView->ResetTestL();
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    iView = NULL;
    }

// End of File
