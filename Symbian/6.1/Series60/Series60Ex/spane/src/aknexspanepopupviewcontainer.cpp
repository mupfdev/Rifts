/*
* ============================================================================
*  Name     : CAknExSpanePopupViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <aknconsts.h>
#include <Avkon.rsg>
#include <akncontext.h>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpanePopupView.h"
#include "AknExSpanePopupViewContainer.h"
#include "AknExSpanePopupWindow.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpanePopupViewContainer::CAknExSpanePopupViewContainer():
    iPopupLabel(NULL),
    iInfoLabel(NULL),
    iStLabel(NULL),
    iBitmap(NULL),
    iTestNumber(0),
    iPopUpControl(NULL),
    iSpecialContentControl(NULL),
    iDefaultNaviControl(NULL),
    iItems(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpanePopupViewContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    SetCanDrawOutsideRect();
    
    // Make listitems. and PUSH it
    iItems = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXSPANE_POPUP_ITEMS);

    iTestNumber = -1;

    TBuf< KLengthOfPopupTempString > titleLabel;
    iPopupLabel = new(ELeave) CEikLabel;
    iPopupLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(titleLabel, R_AKNEXSPANE_POPUP_TITLE);
    iPopupLabel->SetTextL(titleLabel);

    TBuf< KLengthOfPopupTempString > infoLabel;
    iInfoLabel = new(ELeave) CEikLabel;
    iInfoLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(infoLabel, R_AKNEXSPANE_POPUP_INFO);
    iInfoLabel->SetTextL(infoLabel);

    iInfoLabel->SetUnderlining(ETrue);
    iInfoLabel->SetAlignment(EHCenterVCenter);

    iStLabel = new(ELeave) CEikLabel;
    iStLabel->SetContainerWindowL(*this);
    iStLabel->SetTextL((*iItems)[ENumberOfPopupTests]);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExSpanePopupViewContainer::~CAknExSpanePopupViewContainer()
    {
    delete iPopUpControl;
    delete iSpecialContentControl;
    delete iPopupLabel;
    delete iInfoLabel;
    delete iStLabel;
    delete iItems;
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::ResetTestL()
// Reset the test progress
// ---------------------------------------------------------
//
void CAknExSpanePopupViewContainer::ResetTestL()
    {
    iTestNumber = 0;
    
    if (iSpecialContentControl)
        {        
        CEikStatusPane* sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
        sp->SwapControlL(TUid::Uid(EEikStatusPaneUidNavi),iDefaultNaviControl);            
        delete (iSpecialContentControl);
        iSpecialContentControl = NULL;
        }
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::RunLastTestL()
// Run last test step
// ---------------------------------------------------------
//
TBool CAknExSpanePopupViewContainer::RunLastTestL()
    {
    if (iTestNumber < 0)
        {
        return EFalse;
        }

    iTestNumber = (iTestNumber + ENumberOfPopupTests - 2) % 
                   ENumberOfPopupTests;
    if (iTestNumber ==  ENumberOfPopupTests - 1) 
        {
        iEikonEnv->InfoMsgWithAlignment(EHCenterVBottom, R_AKNEXSPANE_GOBACK_NOWISFIRST);
        iTestNumber = 1;
        return EFalse;
        }
    RunTestL(iTestNumber);

    iTestNumber++;
    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::RunNextTestL()
// Run next test step
// ---------------------------------------------------------
//
TBool CAknExSpanePopupViewContainer::RunNextTestL()
    {
    if (iTestNumber < 0)
        {
        iTestNumber = 0;
        }
    
    RunTestL(iTestNumber);
    iTestNumber++;
    if (iTestNumber >= ENumberOfPopupTests)
        {
        iTestNumber = 0;
        return EFalse;
        }

    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::RunTestL(TInt aTestId)
// Run one test step
// ---------------------------------------------------------
//
void CAknExSpanePopupViewContainer::RunTestL(TInt aTestId)
    {
    
    CEikStatusPane* sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
    TRect paneRect;

    //TBuf<KLengthOfTempString> number;
    //TBuf<KLengthOfTempString> format;
    //iCoeEnv->ReadResource(format, R_AKNEXSPANE_FORMATSTRING_CURRENTSTEP);
    //number.Format(format, aTestId+1);
    //iEikonEnv->InfoMsgWithAlignment(EHCenterVBottom,number);
    
    if (!iPopUpControl)
        {
        iPopUpControl = new(ELeave) CAknExSpanePopUpWindow;
        iPopUpControl->ConstructL(AKNEXSPANE_ZERO_SIZE_AREA);
        }

    /* Is context or clock pane visible in the status pane */
    if (sp->PaneCapabilities(TUid::Uid(EEikStatusPaneUidContext)).IsInCurrentLayout())
        {
        paneRect = sp->PaneRectL(TUid::Uid(EEikStatusPaneUidContext));
        }
    else
        {
        paneRect = sp->PaneRectL(TUid::Uid(EEikStatusPaneUidClock));
        }
    
    // refresh test information
    iStLabel->SetTextL((*iItems)[aTestId]);
    switch (aTestId)
        {
        case EPopUpOverContextPane:
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            iPopUpControl->SetRect(paneRect);
            break;

        case EPopUpOverContextAndMainPane:
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_IDLE);
            paneRect.iBr.iY += Kqpn_height_status_pane_idle - Kqpn_height_status_pane_usual;
            iPopUpControl->SetRect(paneRect);
            break;
        
        case EPopUpOverSignaAndContextPane:
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            iPopUpControl->SetRect(TRect(0,0,paneRect.iBr.iX,paneRect.iBr.iY));
            break;
        
        case EPopUpOverTitleAndNaviPane:
            iPopUpControl->SetRect(TRect(paneRect.iBr.iX,0,AKNEXSPANE_SCREEN_WIDTH,paneRect.iBr.iY));
            delete (iSpecialContentControl);
            iSpecialContentControl = NULL;
            if (iDefaultNaviControl)
                {
                sp->SwapControlL(TUid::Uid(EEikStatusPaneUidNavi),iDefaultNaviControl);
                iDefaultNaviControl = NULL;
                }
            break;
            
        case ENaviSpecialContents:
            {
            iPopUpControl->SetRect(AKNEXSPANE_ZERO_SIZE_AREA);
            if (!iSpecialContentControl)
                {
                iSpecialContentControl = new(ELeave) CAknExSpanePopUpWindow;
                iSpecialContentControl->ConstructL(sp->PaneRectL(TUid::Uid(EEikStatusPaneUidNavi)));
                }
            iDefaultNaviControl = sp->SwapControlL(TUid::Uid(EEikStatusPaneUidNavi),iSpecialContentControl);
            }
            break;
        
        case ENaviNormalContents:
            {
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            sp->SwapControlL(TUid::Uid(EEikStatusPaneUidNavi),iDefaultNaviControl);
            iDefaultNaviControl = NULL;
            delete (iSpecialContentControl);
            iSpecialContentControl = NULL;
            }
            break;
            
        case ESwitchLayoutOff:
            {
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_EMPTY);
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_IDLE);
            }
            break;
        
        case ESwitchLayoutOn:
            {
            sp->MakeVisible(ETrue);
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            }
            break;
        
        case ESwitchVisibilityOff:
            {
            sp->MakeVisible(EFalse);
            }
            break;
        
        case ESwitchVisibilityOn:
            {
            sp->MakeVisible(ETrue);
            }
            break;
        
        default:
            break;
        }

    // changed the size of the test information displayed on screen
    if (iEikonEnv->AppUiFactory()->StatusPane()->IsVisible() &&
        iEikonEnv->AppUiFactory()->StatusPane()->PaneCapabilities(
           TUid::Uid(EEikStatusPaneUidBattery)).IsInCurrentLayout() &&
        iEikonEnv->AppUiFactory()->StatusPane()->PaneCapabilities(
           TUid::Uid(EEikStatusPaneUidSignal)).IsInCurrentLayout())
        {
        //Set proper size and position in the idle layout.
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT_IDLE, iStLabel->MinimumSize());
        }
    else
        {
        //Set proper size and position in the usual layout.
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT, iStLabel->MinimumSize());
        }

    DrawNow();
    }

    
// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::SizeChanged()
// Called by framework when the view size is changed. 
// ---------------------------------------------------------
//
void CAknExSpanePopupViewContainer::SizeChanged()
    {
    TRect rect(Rect());
    if (iEikonEnv->AppUiFactory()->StatusPane()->IsVisible() &&
        iEikonEnv->AppUiFactory()->StatusPane()->PaneCapabilities(
           TUid::Uid(EEikStatusPaneUidBattery)).IsInCurrentLayout() &&
        iEikonEnv->AppUiFactory()->StatusPane()->PaneCapabilities(
           TUid::Uid(EEikStatusPaneUidSignal)).IsInCurrentLayout())
        {
        //Set proper shape to window in the idle layout.
        RRegion reg;
        reg.AddRect(TRect(TPoint(rect.iTl.iX, rect.iTl.iY), TPoint(12, 12)));
        reg.AddRect(TRect(TPoint(rect.iTl.iX + 12, rect.iTl.iY + 6), TPoint(19, 12)));
        reg.AddRect(TRect(TPoint(rect.iTl.iX, 12), TPoint(rect.iBr.iX, rect.iBr.iY)));
        Window().SetShape(reg);
        reg.Close();
        iPopupLabel->SetExtent(AKNEXSPANE_TOP_POINT_IDLE, iPopupLabel->MinimumSize());
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT_IDLE, iStLabel->MinimumSize());
        iInfoLabel->SetExtent(AKNEXSPANE_LOW_POINT_IDLE, iInfoLabel->MinimumSize());
        }
    else
        {
        //Set proper shape to window in the usual layout.
        RRegion reg;
        reg.AddRect( rect );
        Window().SetShape(reg);
        reg.Close();
        iPopupLabel->SetExtent(AKNEXSPANE_TOP_POINT, iPopupLabel->MinimumSize());
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT, iStLabel->MinimumSize());
        iInfoLabel->SetExtent(AKNEXSPANE_LOW_POINT, iInfoLabel->MinimumSize());
        }
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::CountComponentControls() const
// Returns number of component. 
// ---------------------------------------------------------
//
TInt CAknExSpanePopupViewContainer::CountComponentControls() const
    {
    return ENumberOfComponent;
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::ComponentControl(TInt aIndex) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExSpanePopupViewContainer::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case ETitleLabel:
            return iPopupLabel;
        case EStLabel:
            return iStLabel;
        case EInfoLabel:
            return iInfoLabel;
        default:
            return NULL;
        } 
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::Draw(const TRect& aRect) const
// Draw function.
// ---------------------------------------------------------
//
void CAknExSpanePopupViewContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(AKNEXSPANE_KRGB_YELLOW);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExSpanePopupViewContainer::HandleControlEventL(
//     CCoeControl* aControl, TCoeEvent aEventType)
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExSpanePopupViewContainer::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File
