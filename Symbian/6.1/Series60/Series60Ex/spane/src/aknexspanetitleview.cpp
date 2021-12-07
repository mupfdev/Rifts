/*
* ============================================================================
*  Name     : CAknExSpaneTitleView from CAknView
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <eikfutil.h>
#include <aknconsts.h>
#include <akntitle.h>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneTitleView.h"
#include "AknExSpaneTitleViewContainer.h"

// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneTitleView::CAknExSpaneTitleView():
    iView(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneTitleView::ConstructL()
    {
    BaseConstructL(R_AKNEXSPANE_TITLE_VIEW);
    }

// Destructor
CAknExSpaneTitleView::~CAknExSpaneTitleView()
    {
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    }

// ---------------------------------------------------------
// TUid CAknExSpaneTitleView::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExSpaneTitleView::Id() const
    {
    return TUid::Uid(EAknExSpaneTitleViewId);
    }

// ---------------------------------------------------------
// CAknExSpaneTitleView::HandleCommandL(TInt aCommand)
// handles the commands
// ---------------------------------------------------------
//
void CAknExSpaneTitleView::HandleCommandL(TInt aCommand)
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
// CAknExSpaneTitleView::HandleStatusPaneSizeChange()
// Control of the size change event
// ---------------------------------------------------------
//
void CAknExSpaneTitleView::HandleStatusPaneSizeChange()
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
// CAknExSpaneTitleView::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExSpaneTitleView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iView = new(ELeave) CAknExSpaneTitleViewContainer;
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
// CAknExSpaneTitleView::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExSpaneTitleView::DoDeactivate()
    {
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    iView = NULL;
    }

// End of File
