/*
* ============================================================================
*  Name     : CAknExSpaneContextViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <eikfutil.h>
#include <eikctl.rsg>
#include <aknconsts.h>
#include <akncontext.h>

#include <AknExSpane.rsg>
#include <aknexspane.mbg>

#include "AknExSpane.hrh"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneContextViewContainer.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneContextViewContainer::CAknExSpaneContextViewContainer():
    iContextLabel(NULL),
    iInfoLabel(NULL),
    iStLabel(NULL),
    iBitmap(NULL),
    iBitmapM(NULL),
    iTestNumber(0),
    iContextPane(NULL),
    iItems(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneContextViewContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();
    
    // Make listitems. and PUSH it
    iItems = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXSPANE_CONTEXT_ITEMS);

    iTestNumber = -1;

    // test title
    TBuf< KLengthOfContextTempString > titleLabel;
    iContextLabel = new(ELeave) CEikLabel;
    iContextLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(titleLabel, R_AKNEXSPANE_CONTEXT_TITLE);
    iContextLabel->SetTextL(titleLabel);

    // operate hint
    TBuf < KLengthOfContextTempString > infoLabel;
    iInfoLabel = new(ELeave) CEikLabel;
    iInfoLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(infoLabel, R_AKNEXSPANE_CONTEXT_INFO);
    iInfoLabel->SetTextL(infoLabel);
    iInfoLabel->SetUnderlining(ETrue);
    iInfoLabel->SetAlignment(EHCenterVCenter);

    // test information of each step
    iStLabel = new(ELeave) CEikLabel;
    iStLabel->SetContainerWindowL(*this);
    iStLabel->SetTextL((*iItems)[ENumberOfContextTests]);

    SetRect(aRect);
    ActivateL();

    CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
    
    // Fetch pointer to the default context pane control
    iContextPane = (CAknContextPane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidContext));

    }

// Destructor
CAknExSpaneContextViewContainer::~CAknExSpaneContextViewContainer()
    {
    delete iContextLabel;
    delete iInfoLabel;
    delete iStLabel;
    delete iItems;
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::ResetTest()
// Reset the test progress
// ---------------------------------------------------------
//
void CAknExSpaneContextViewContainer::ResetTest()
    {
    iTestNumber = 0;
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::RunNextTestL()
// Run next test step
// ---------------------------------------------------------
//
TBool CAknExSpaneContextViewContainer::RunNextTestL()
    {
    if (iTestNumber < 0)
        {
        iTestNumber = 0;
        }

    RunTestL(iTestNumber);
    iTestNumber++;

    if (iTestNumber >= ENumberOfContextTests)
        {
        iTestNumber = 0;
        return EFalse;
        }

    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::RunLastTestL()
// Run next test step
// ---------------------------------------------------------
//
TBool CAknExSpaneContextViewContainer::RunLastTestL()
    {
    if (iTestNumber < 0)
        {
        return EFalse;
        }

    iTestNumber = (iTestNumber + ENumberOfContextTests - 2) % 
                  ENumberOfContextTests;
    if (iTestNumber ==  ENumberOfContextTests-1) 
        {
        iEikonEnv->InfoMsgWithAlignment(EHCenterVBottom, R_AKNEXSPANE_GOBACK_NOWISFIRST);
        iTestNumber = 1;
        return EFalse;
        }
    RunTestL(iTestNumber);

    iTestNumber++;
    // The following process is not necessary because 
    // no matter the 'go back' can not jump from 0 to N-1
    //if (iTestNumber >= ENumberOfContextTests)
    //    {
    //    iTestNumber = 0;
    //    }

    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::RunTestL(TInt aTestId)
// Run one test step
// ---------------------------------------------------------
//
void CAknExSpaneContextViewContainer::RunTestL(TInt aTestId)
    {
    // refresh the test information displayed on screen
    iStLabel->SetTextL((*iItems)[aTestId]);

    //TBuf<KLengthOfTempString> number;
    //TBuf<KLengthOfTempString> format;
    //iCoeEnv->ReadResource(format, R_AKNEXSPANE_FORMATSTRING_CURRENTSTEP);
    //number.Format(format, aTestId+1);
    //iEikonEnv->InfoMsgWithAlignment(EHCenterVBottom,number);

    switch (aTestId)
        {
        case EDefault:
            {
            iContextPane->SetPictureToDefaultL();
            break;
            }

        case ESmallImage:
            {
            iBitmap = iEikonEnv->CreateBitmapL(KContextBitMapFile, EMbmAknexspaneIndicato );
            iContextPane->SetPicture(iBitmap);
            iBitmap = NULL;
            }
            break;

        case EMediumImage:
            iBitmap = iEikonEnv->CreateBitmapL(KContextBitMapFile, EMbmAknexspaneLshellicon );
            iBitmapM = iEikonEnv->CreateBitmapL(KContextBitMapFile, EMbmAknexspaneLshelliconm );
            iContextPane->SetPicture(iBitmap, iBitmapM);
            iBitmap = NULL;
            iBitmapM = NULL;
            break;

        case EBigImage:
            iBitmap = iEikonEnv->CreateBitmapL(KContextBitMapFile, EMbmAknexspaneTitle);
            iContextPane->SetPicture(iBitmap);
            iBitmap = NULL;
            break;

        case EMediumImageFromFile:
            iContextPane->SetPictureFromFileL(KContextBitMapFile, EMbmAknexspaneContext);
            break;

        case EImageFromResources:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            TResourceReader reader;
            //iCoeEnv->CreateResourceReaderLC(reader,R_EIK_DIGITAL_CLOCK);
            iCoeEnv->CreateResourceReaderLC(reader,R_AKNEXSPANE_IMAGE_RESOURCE);
            
            iContextPane->SetFromResourceL(reader);
            CleanupStack::PopAndDestroy();  // resource reader
            }
            break;
        case ESwitchLayoutOff:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_EMPTY);
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_IDLE);
            }
            break;
        
        case ESwitchLayoutOn:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
            sp->MakeVisible(ETrue);
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            }
            break;
        
        case ESwitchVisibilityOff:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
            sp->MakeVisible(EFalse);
            }
            break;
        
        case ESwitchVisibilityOn:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
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
// CAknExSpaneContextViewContainer::SizeChanged()
// Called by framework when the view size is changed. 
// ---------------------------------------------------------
//
void CAknExSpaneContextViewContainer::SizeChanged()
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
        iContextLabel->SetExtent(AKNEXSPANE_TOP_POINT_IDLE, iContextLabel->MinimumSize());
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
        iContextLabel->SetExtent(AKNEXSPANE_TOP_POINT, iContextLabel->MinimumSize());
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT, iStLabel->MinimumSize());
        iInfoLabel->SetExtent(AKNEXSPANE_LOW_POINT, iInfoLabel->MinimumSize());
        }
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::CountComponentControls() const
// Returns number of component. 
// ---------------------------------------------------------
//
TInt CAknExSpaneContextViewContainer::CountComponentControls() const
    {
    return ENumberOfComponent;
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::ComponentControl(TInt aIndex) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExSpaneContextViewContainer::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case ETitleLabel:
            return iContextLabel;
        case EStLabel:
            return iStLabel;
        case EInfoLabel:
            return iInfoLabel;
        default:
            return NULL;
        } 
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::Draw(const TRect& aRect) const
// Draw function.
// ---------------------------------------------------------
//
void CAknExSpaneContextViewContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(AKNEXSPANE_KRGB_GRAY);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExSpaneContextViewContainer::HandleControlEventL(
//     CCoeControl* aControl, TCoeEvent aEventType)
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExSpaneContextViewContainer::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// End of File
