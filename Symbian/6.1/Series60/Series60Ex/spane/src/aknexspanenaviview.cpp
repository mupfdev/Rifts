/*
* ============================================================================
*  Name     : CAknExSpaneNaviView from CAknView
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eikmenub.h>
#include <eiklabel.h>
#include <eikfutil.h>
#include <aknconsts.h>
#include <aknnavi.h>
#include <akntabgrp.h>
#include <aknnavide.h>
//#include <AknGridIndication.h>
#include <AknVolumeControl.h>
#include <avkon.rsg>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneNaviView.h"
#include "AknExSpaneNaviViewContainer.h"


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneNaviView::CAknExSpaneNaviView():
    iView(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneNaviView::ConstructL()
    {
    BaseConstructL(R_AKNEXSPANE_NAVI_VIEW);
    }

// Destructor
CAknExSpaneNaviView::~CAknExSpaneNaviView()
    {
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    }

// ---------------------------------------------------------
// TUid CAknExSpaneNaviView::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExSpaneNaviView::Id() const
    {
    return TUid::Uid(EAknExSpaneNaviViewId);
    }

// ---------------------------------------------------------
// CAknExSpaneNaviView::HandleCommandL(TInt aCommand)
// handles the commands
// ---------------------------------------------------------
//
void CAknExSpaneNaviView::HandleCommandL(TInt aCommand)
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

        // the following code is used by navi pane menu to add/delete/replace/select tab
        case EAknExSpaneNaviTabAdd:
        case EAknExSpaneNaviTabReplace:
        case EAknExSpaneNaviTabSelect:
            {
            iView->OpenNaviTabDlg(aCommand);
            break;
            }

        case EAknExSpaneNaviTabDelete:
            {
            TBuf<16> temp;
            iView->SetTabOperate(EAknExSpaneNaviTabDelete, 0, temp, 0);
            break;
            }

        // the following code is used by navi pane menu to control the Navi_Icon
        case EAknExSpaneNaviArrayLeftOn:  
        case EAknExSpaneNaviArrayLeftFade: 
        case EAknExSpaneNaviArrayEnable:  
        case EAknExSpaneNaviArrayRightOn:  
        case EAknExSpaneNaviArrayRightFade:
        case EAknExSpaneNaviArrayDisable:
            {
            iView->SetNaviIcon(aCommand);
            break;
            }
        
        // the following code is used by navi pane menu to control the navi tab style
        case EAknExSpaneNaviTabStyleOne:
        case EAknExSpaneNaviTabStyleTwoShort:
        case EAknExSpaneNaviTabStyleTwoLong:
        case EAknExSpaneNaviTabStyleThreeShort:
        case EAknExSpaneNaviTabStyleThreeLong:
        case EAknExSpaneNaviTabStyleFour:
            {
            iView->SetTabStyle(aCommand);
            break;
            }

        default:
            {
            AppUi()->HandleCommandL(aCommand);
            break;
            }
        }
    }
// ------------------------------------------------------------------------------
// CAknExSpaneNaviView::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
//
// ------------------------------------------------------------------------------
void CAknExSpaneNaviView::DynInitMenuPaneL(
    TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (aResourceId == R_AKNEXSPANE_NAVI_VIEW_OPMENU)
        {
        // check the tab status
        if (!iView->IsTabBeDsiplayed())
            {
            aMenuPane->SetItemDimmed(EAknExSpaneNaviTabSubStyle,ETrue);
            aMenuPane->SetItemDimmed(EAknExSpaneNaviTabSubEdit,ETrue);
            //aMenuPane->SetItemDimmed(EAknExSpaneNaviTabSub,ETrue);
            //aMenuPane->SetItemDimmed(EAknExSpaneNaviArraySub,ETrue);
            }
        else
            {
            aMenuPane->SetItemDimmed(EAknExSpaneNaviTabSubStyle,EFalse);
            aMenuPane->SetItemDimmed(EAknExSpaneNaviTabSubEdit,EFalse);
            //aMenuPane->SetItemDimmed(EAknExSpaneNaviTabSub,EFalse);
            //aMenuPane->SetItemDimmed(EAknExSpaneNaviArraySub,EFalse);
            }

        if (iView->IsNaviIconMenu())
            {
            aMenuPane->SetItemDimmed(EAknExSpaneNaviArraySub,EFalse);
            }
        else
            {
            aMenuPane->SetItemDimmed(EAknExSpaneNaviArraySub,ETrue);
            }
        }
    }

// ---------------------------------------------------------
// CAknExSpaneNaviView::HandleStatusPaneSizeChange()
// Control of the size change event
// ---------------------------------------------------------
//
void CAknExSpaneNaviView::HandleStatusPaneSizeChange()
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
// CAknExSpaneNaviView::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExSpaneNaviView::DoActivateL(const TVwsViewId& /*aPrevViewId*/,TUid /*aCustomMessageId*/,const TDesC8& /*aCustomMessage*/)
    {
    iView = new(ELeave) CAknExSpaneNaviViewContainer;
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
// CAknExSpaneNaviView::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExSpaneNaviView::DoDeactivate()
    {
    if (iView)
        {
        AppUi()->RemoveFromStack(iView);
        }
    delete iView;
    iView = NULL;
    }

// End of File
