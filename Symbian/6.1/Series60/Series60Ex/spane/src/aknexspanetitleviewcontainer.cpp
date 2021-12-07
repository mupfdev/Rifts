/*
* ============================================================================
*  Name     : CAknExSpaneTitleViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <eikfutil.h>
#include <avkon.rsg>
#include <aknconsts.h>
#include <akntitle.h>

#include <AknExSpane.rsg>
#include <aknexspane.mbg>

#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneTitleView.h"
#include "AknExSpaneTitleViewContainer.h"


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneTitleViewContainer::CAknExSpaneTitleViewContainer():
    iTitleLabel(NULL),
    iInfoLabel(NULL),
    iStLabel(NULL),
    iBitmap(NULL),
    iTestNumber(0),
    iTitlePane(NULL),
    iItems(NULL),
    iTitles(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneTitleViewContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    // Make listitems. and PUSH it
    iItems = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXSPANE_TITLE_ITEMS);
    iTitles = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXSPANE_TITLE_TITLES);

    iTestNumber = -1;

    TBuf< KLengthOfTitleTempString > titleLabel;
    iTitleLabel = new(ELeave) CEikLabel;
    iTitleLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(titleLabel, R_AKNEXSPANE_TITLE_TITLE);
    iTitleLabel->SetTextL(titleLabel);

    TBuf< KLengthOfTitleTempString > infoLabel;
    iInfoLabel = new(ELeave) CEikLabel;
    iInfoLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(infoLabel, R_AKNEXSPANE_TITLE_INFO);
    iInfoLabel->SetTextL(infoLabel);

    iInfoLabel->SetUnderlining(ETrue);
    iInfoLabel->SetAlignment(EHCenterVCenter);

    iStLabel = new(ELeave) CEikLabel;
    iStLabel->SetContainerWindowL(*this);
    iStLabel->SetTextL((*iItems)[ENumberOfTitleTests]);

    SetRect(aRect);
    ActivateL();

    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
    // Fetch pointer to the default title pane control
    iTitlePane = (CAknTitlePane *)sp->ControlL(TUid::Uid(EEikStatusPaneUidTitle));
    }

// Destructor
CAknExSpaneTitleViewContainer::~CAknExSpaneTitleViewContainer()
    {
    delete iTitleLabel;
    delete iInfoLabel;
    delete iStLabel;
    delete iItems;
    delete iTitles;
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::ResetTest()
// Reset the test progress
// ---------------------------------------------------------
//
void CAknExSpaneTitleViewContainer::ResetTest()
    {
    iTestNumber = 0;
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::RunLastTestL()
// Run last test step
// ---------------------------------------------------------
//
TBool CAknExSpaneTitleViewContainer::RunLastTestL()
    {
    if (iTestNumber < 0)
        {
        return EFalse;
        }

    iTestNumber = (iTestNumber + ENumberOfTitleTests - 2) %
                   ENumberOfTitleTests;
    if (iTestNumber ==  ENumberOfTitleTests - 1) 
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
// CAknExSpaneTitleViewContainer::RunNextTestL()
// Run next test step
// ---------------------------------------------------------
//
TBool CAknExSpaneTitleViewContainer::RunNextTestL()
    {
    if (iTestNumber < 0)
        {
        iTestNumber = 0;
        }
    
    RunTestL(iTestNumber);

    iTestNumber++;
    if (iTestNumber >= ENumberOfTitleTests)
        {
        iTestNumber = 0;
        return EFalse;
        }


    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::RunTestL(TInt aTestId)
// Run one test step
// ---------------------------------------------------------
//
void CAknExSpaneTitleViewContainer::RunTestL(TInt aTestId)
    {
    CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();

    //TBuf<KLengthOfTempString> number;
    //TBuf<KLengthOfTempString> format;
    //iCoeEnv->ReadResource(format, R_AKNEXSPANE_FORMATSTRING_CURRENTSTEP);
    //number.Format(format, aTestId+1);
    //iEikonEnv->InfoMsgWithAlignment(EHCenterVBottom,number);

    // refresh test information
    iStLabel->SetTextL((*iItems)[aTestId]);
    switch (aTestId)
        {
        case EDefault:
            sp->SetDimmed(EFalse);
            iTitlePane->SetTextToDefaultL();
            break;
        
        case EEmptyText:
            //iTitlePane->SetTextL(_L(""));
            iTitlePane->SetTextL((*iTitles)[EEmptyText]);
            break;
        
        case EShortText:
            //iTitlePane->SetTextL(_L("T"));
            //iTitlePane->SetTextL((*iTitles)[EShortText]);
            iTitlePane->SetTextL((*iTitles)[EShortText]);
            break;
        
        case EOneLineText:
            //iTitlePane->SetTextL(_L("Test text"));
            iTitlePane->SetTextL((*iTitles)[EOneLineText]);
            break;
        
        case EOneLineText2:
            //iTitlePane->SetTextL(_L("iiiiiiiiiiiiiiiiiiii"));
            iTitlePane->SetTextL((*iTitles)[EOneLineText2]);
            break;
        
        case EOneLineText3:
            //iTitlePane->SetTextL(_L("iiiiiiiiiiiiiiiiiiiii"));
            iTitlePane->SetTextL((*iTitles)[EOneLineText3]);
            break;
        
        case ETwoLineText:
            //iTitlePane->SetTextL(_L("iiiiiiiiiiiiiiiiiiiiiiiiiii"));
            iTitlePane->SetTextL((*iTitles)[ETwoLineText]);
            break;
        
        case ETwoLineText2:
            //iTitlePane->SetTextL(_L("Little longer two line text"));
            iTitlePane->SetTextL((*iTitles)[ETwoLineText2]);
            break;
        
        case ETextInTitlePane:
            //iTitlePane->SetTextL(_L("Featire No.38 Text to the label"));
            iTitlePane->SetTextL((*iTitles)[ETextInTitlePane]);
            break;
        
        case ETwoLineText3:
            //iTitlePane->SetTextL(_L("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"));
            iTitlePane->SetTextL((*iTitles)[ETwoLineText3]);
            break;
        
        case ETwoLineText4:
            //iTitlePane->SetTextL(_L("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"));
            iTitlePane->SetTextL((*iTitles)[ETwoLineText4]);
            break;
        
        case ETwoLineText5:
            //iTitlePane->SetTextL(_L("iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"));
            iTitlePane->SetTextL((*iTitles)[ETwoLineText5]);
            break;
        
        case ELongTest:
            //iTitlePane->SetTextL(_L("A long test text to the title pane"));
            iTitlePane->SetTextL((*iTitles)[ELongTest]);
            break;
        
        case EExtraLongTest:
            //iTitlePane->SetTextL(_L("Extra long text text that does't fit to the title pane, This text even exceed the buffer size in the implementation"));
            iTitlePane->SetTextL((*iTitles)[EExtraLongTest]);
            break;

        case EAllTextLengthTest:
            {
            DrawNow();
            for (TInt ii = 0; ii < (*iTitles)[EAllTextLengthTest].Length(); ii++)
                {
                iTitlePane->SetTextL((*iTitles)[EAllTextLengthTest].Left(ii));
                iTitlePane->DrawNow();
                }
            }
            break;
        
        case ESmallImage:
            iBitmap = iEikonEnv->CreateBitmapL( KTitleBitMapFile, EMbmAknexspaneIndicato );
            iTitlePane->SetPicture(iBitmap);
            break;
        
        case EMediumImage:
            iBitmap = iEikonEnv->CreateBitmapL( KTitleBitMapFile, EMbmAknexspaneNavi );
            iTitlePane->SetPicture(iBitmap);
            break;

        case EBigImage:
            iBitmap = iEikonEnv->CreateBitmapL( KTitleBitMapFile, EMbmAknexspaneContext );
            iTitlePane->SetPicture(iBitmap);
            break;
        
        case EMediumImageFromFile:
            iTitlePane->SetPictureFromFileL(KTitleBitMapFile, EMbmAknexspaneTitle);
            break;
        
        case ETextFromResources:
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader,R_AKNEXSPANE_TITLE_PANE_TEXT);
            iTitlePane->SetFromResourceL(reader);
            CleanupStack::PopAndDestroy();  // resource reader
            break;
        
        case EImageFromResources:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader,R_AVKON_STATUS_PANE_CLOCK);
            iTitlePane->SetFromResourceL(reader);
            CleanupStack::PopAndDestroy();  // resource reader
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
// CAknExSpaneTitleViewContainer::SizeChanged()
// Called by framework when the view size is changed. 
// ---------------------------------------------------------
//
void CAknExSpaneTitleViewContainer::SizeChanged()
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

        iTitleLabel->SetExtent(AKNEXSPANE_TOP_POINT_IDLE, iTitleLabel->MinimumSize());
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
        iTitleLabel->SetExtent(AKNEXSPANE_TOP_POINT, iTitleLabel->MinimumSize());
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT, iStLabel->MinimumSize());
        iInfoLabel->SetExtent(AKNEXSPANE_LOW_POINT, iInfoLabel->MinimumSize());
        }
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::CountComponentControls() const
// Returns number of component. 
// ---------------------------------------------------------
//
TInt CAknExSpaneTitleViewContainer::CountComponentControls() const
    {
    return ENumberOfComponent;
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::ComponentControl(TInt aIndex) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExSpaneTitleViewContainer::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case ETitleLabel:
            return iTitleLabel;
        case EStLabel:
            return iStLabel;
        case EInfoLabel:
            return iInfoLabel;
        default:
            return NULL;
        } 
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::Draw(const TRect& aRect) const
// Draw function.
// ---------------------------------------------------------
//
void CAknExSpaneTitleViewContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(AKNEXSPANE_KRGB_RED);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExSpaneTitleViewContainer::HandleControlEventL(
//     CCoeControl* aControl, TCoeEvent aEventType)
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExSpaneTitleViewContainer::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }


// End of File