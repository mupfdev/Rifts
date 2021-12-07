/*
* ============================================================================
*  Name     : CAknExSpaneNaviViewContainer from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <eikfutil.h>
#include <aknconsts.h>
#include <aknnavi.h>
#include <akntabgrp.h>
#include <aknnavide.h>
#include <eikdialg.h>
#include <AknVolumeControl.h>
#include <avkon.rsg>

#include <AknExSpane.rsg>
#include <aknexspane.mbg>

#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneNaviView.h"
#include "AknExSpaneNaviViewContainer.h"
#include "AknExSpaneNaviTabDialog.h"


// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneNaviViewContainer::CAknExSpaneNaviViewContainer():
    iNaviLabel(NULL),
    iInfoLabel(NULL),
    iStLabel(NULL),
    iBitmap(NULL),
    iTestNumber(0),
    iNewTabFlag(EFalse),
    iNaviPane(NULL),
    iNaviDecorator(NULL),
    iNaviDecoratorForTabs(NULL),
    iItems(NULL)
    {
    }

// EPOC default constructor can leave.
void CAknExSpaneNaviViewContainer::ConstructL(const TRect& aRect)
    {
    CreateWindowL();

    // Make listitems. and PUSH it
    iItems = iCoeEnv->ReadDesCArrayResourceL(R_AKNEXSPANE_NAVI_ITEMS);

    iTestNumber = -1;


    TBuf< KLengthOfNaviTempString > titleLabel;
    iNaviLabel = new(ELeave) CEikLabel;
    iNaviLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(titleLabel, R_AKNEXSPANE_NAVI_TITLE);
    iNaviLabel->SetTextL(titleLabel);

    TBuf< KLengthOfNaviTempString > infoLabel;
    iInfoLabel = new(ELeave) CEikLabel;
    iInfoLabel->SetContainerWindowL(*this);
    iCoeEnv->ReadResource(infoLabel, R_AKNEXSPANE_NAVI_INFO);
    iInfoLabel->SetTextL(infoLabel);
    iInfoLabel->SetUnderlining(ETrue);
    iInfoLabel->SetAlignment(EHCenterVCenter);
 
    iStLabel = new(ELeave) CEikLabel;
    iStLabel->SetContainerWindowL(*this);
    iStLabel->SetTextL((*iItems)[ENumberOfNaviTests]);

    SetRect(aRect);
    ActivateL();
    }

// Destructor
CAknExSpaneNaviViewContainer::~CAknExSpaneNaviViewContainer()
    {
    if (iTestNumber >= 0)
        {
        if (!iNaviPane)
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            // Fetch pointer to the default navi pane control
            iNaviPane = (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
            }
        // Pop default navi pane contents. Popped after new navi pane content.
        iNaviPane->Pop(NULL); 
        }
    delete iNaviDecoratorForTabs;
    delete iNaviDecorator;
    delete iNaviLabel;
    delete iInfoLabel;
    delete iStLabel;
    delete iItems;
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::ResetTest()
// Reset the test progress
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::ResetTest()
    {
    iTestNumber = 0;
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::RunNextTestL()
// Run next test step
// ---------------------------------------------------------
//
TBool CAknExSpaneNaviViewContainer::RunNextTestL()
    {
    if (iTestNumber < 0)
        {
        iTestNumber = 0;
        }

    RunTestL(iTestNumber);

    iTestNumber++;
    if (iTestNumber >= ENumberOfNaviTests)
        {
        iTestNumber = 0;

        /*TBuf< KLengthOfNaviTempString > tempLabel;

        iTestNumber = -1;
        if (!iNaviPane)
            {
            CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
            // Fetch pointer to the default navi pane control
            iNaviPane = (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
            }
        iNaviPane->Pop();
        //display the " \n ";
        iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_ITEM_NO);
        iStLabel->SetTextL(tempLabel);
        // Pop default navi pane contents. Popped after new navi pane content.
        iNaviPane->Pop(NULL); 
        DrawNow();*/
        iTestNumber = 0;
        return EFalse;
        }


    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::RunLastTestL()
// Run last test step
// ---------------------------------------------------------
//
TBool CAknExSpaneNaviViewContainer::RunLastTestL()
    {
    if (iTestNumber < 0)
        {
        return EFalse;
        }

    iTestNumber = (iTestNumber + ENumberOfNaviTests - 2) % 
                  ENumberOfNaviTests;
    if (iTestNumber ==  ENumberOfNaviTests - 1) 
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
// CAknExSpaneNaviViewContainer::RunTestL(TInt aTestId)
// Run one test step
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::RunTestL(TInt aTestId)
    {
    //TBuf<KLengthOfTempString> number;
    //TBuf<KLengthOfTempString> format;
    //iCoeEnv->ReadResource(format, R_AKNEXSPANE_FORMATSTRING_CURRENTSTEP);
    //number.Format(format, aTestId+1);
    //iEikonEnv->InfoMsgWithAlignment(EHCenterVBottom,number);

    if (!iNaviPane)
        {
        CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
        // Fetch pointer to the default navi pane control
        iNaviPane = (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
        }

    // Is battery pane visible in current layout.
    CEikStatusPane* statusPane = ((CAknAppUi*)CEikonEnv::Static()->EikAppUi())->StatusPane();
    if (statusPane->PaneCapabilities(TUid::Uid(EEikStatusPaneUidBattery)).IsInCurrentLayout())
        {
        if ((aTestId >= ETwoTabs) && (aTestId <= ETabActiveByIdIllegal))
            {
            iEikonEnv->InfoMsgWithAlignment(EHCenterVCenter,R_AKNEXSPANE_TBUF_TABS_NOT_SHOW_MESSAGE);
            }
        }

    TBuf< KLengthOfNaviTempString > tempLabel;

    // refresh the test information
    iStLabel->SetTextL((*iItems)[aTestId]);

    switch (aTestId)
        {
        case EDefault:
            iNaviPane->PushDefaultL();
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            break;

        case ETwoTabs:
            {

            CAknTabGroup* tabGroup = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(EAknTabWidthWithTwoTabs);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber0);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            }
            break;

        case ETwoLongTabs:
            {
            CAknTabGroup* tabGroup = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(KTabWidthWithTwoLongTabs);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber1);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            }
            break;

        case EThreeTabs:
            {
            CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(KTabWidthWithThreeTabs);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber1);
            }
            break;

        case EThreeLongTabs:
            {
            CAknTabGroup* tabGroup = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(KTabWidthWithThreeLongTabs);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber2);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            }
            break;

        case ELongTabActive0:
            {
            CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber0);
            break;
            }

        case ELongTabActive1:
            {
            CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber1);
            break;
            }

        case ELongTabActive2:
            {
            CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber2);
            break;
            }

        case ELongTabActive3:
            {
            CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(KTabWidthWithThreeLongTabs);
            tabGroup->SetActiveTabByIndex(EAknExSpaneNaviNumber3);
            break;
            }

        case ETabOneTab:
            {
            CAknTabGroup* tabGroup = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(KTabWidthWithOneTab);
            tabGroup->SetActiveTabById(EAknExSpaneNaviNumber14);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            break;
            }

        case EFourTabs:
            {
            CAknTabGroup* tabGroupShort = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetTabFixedWidthL(KTabWidthWithFourTabs);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber8);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            break;
            }

        case ETabActiveIllegal1:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumberM1);
            break;
            }

        case ETabActive0:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber0);
            break;
            }

        case ETabActive1:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber1);
            break;
            }

        case ETabActive2:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber2);
            break;
            }

        case ETabActive3:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber3);
            break;
            }

        case ETabActive4:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber4);
            break;
            }

        case ETabActive5:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber5);
            break;
            }

        case ETabActiveIllegal2:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);

            if (iNewTabFlag)
                {
                tabGroupShort->DeleteTabL(KNaviNewTabId);
                iNewTabFlag = EFalse;
                tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber5);
                }

            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber9);
            break;
            }

        case ETabAddNew:
            {
            TBuf< KLengthOfNaviTempString > newTabtext;
            iCoeEnv->ReadResource(newTabtext, R_AKNEXSPANE_NAVI_NEW_TAB_STR);

            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);

            if (iNewTabFlag)
                {
                tabGroupShort->DeleteTabL(KNaviNewTabId);
                iNewTabFlag = EFalse;
                tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber5);
                }

            if (!iNewTabFlag)
                {
                tabGroupShort->AddTabL(KNaviNewTabId,newTabtext);
                iNewTabFlag = ETrue;
                }

            tabGroupShort->SetActiveTabById(KNaviNewTabId);
            break;
            }

        case ETabReplaceCurrent:
            {
            TBuf< KLengthOfNaviTempString > newTabtext;
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);

            iCoeEnv->ReadResource(newTabtext, R_AKNEXSPANE_NAVI_NEW_TAB_STR);
            if (!iNewTabFlag)
                {
                tabGroupShort->AddTabL(KNaviNewTabId,newTabtext);
                iNewTabFlag = ETrue;
                }

            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXSPANE_TAB_REPLACE);
            tabGroupShort->ReplaceTabL(reader);
            CleanupStack::PopAndDestroy();  // resource reader
            tabGroupShort->SetActiveTabById(KNaviNewTabId);
            break;
            }

        case ETabDeleteCurrent:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            if (iNewTabFlag)
                {
                tabGroupShort->DeleteTabL(KNaviNewTabId);
                iNewTabFlag = EFalse;
                }
            tabGroupShort->SetActiveTabByIndex(EAknExSpaneNaviNumber5);
            break;
            }

        case ETabActiveById:
            {
            CAknTabGroup* tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            tabGroupShort->SetActiveTabById(EAknExSpaneNaviNumberM2);
            break;
            }

        case ETabActiveByIdIllegal:
            {
            CAknTabGroup* tabGroupShort;
            if (!iNaviDecoratorForTabs)
                {
                tabGroupShort = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
                }
            else
                {
                tabGroupShort = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
                }
            tabGroupShort->SetTabFixedWidthL(KTabWidthWithFourTabs);
            tabGroupShort->SetActiveTabById(EAknExSpaneNaviNumber1);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            break;
            }

        case ENaviImage:
            {
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader, R_AKNEXSPANE_NAVIIMAGE_RESOURCE);
            iNaviDecorator = iNaviPane->CreateNavigationImageL(reader);
            CleanupStack::PopAndDestroy();  // resource reader
            iNaviPane->PushL(*iNaviDecorator);

            delete iNaviDecoratorForTabs;
            iNaviDecoratorForTabs = NULL;
            break;
            }

        case ENaviImageLeftArrow:
            iNaviDecorator->MakeScrollButtonVisible(ETrue);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, EFalse);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, ETrue);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviImageRightArrow:
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, ETrue);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviImageBothArrows:

            delete iNaviDecorator;
            iNaviDecorator = NULL;
            iBitmap = iEikonEnv->CreateBitmapL( KNaviBitMapFile, EMbmAknexspaneNavi );
            iNaviDecorator = iNaviPane->CreateNavigationImageL(iBitmap);
            iBitmap = NULL;  // Bitmap owned by navigation decorator

            iNaviDecorator->MakeScrollButtonVisible(ETrue);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, EFalse);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviLabel:
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            //iNaviDecorator = iNaviPane->CreateNavigationLabelL(_L("Add. info"));
            iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_ADD);
            iNaviDecorator = iNaviPane->CreateNavigationLabelL(tempLabel);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviLabelLong:
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            //iNaviDecorator = iNaviPane->CreateNavigationLabelL(_L("Long label text! This is longer that the field"));
            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC(reader,
                                            R_AKNEXSPANE_NAVI_LONG_LABEL);
            iNaviDecorator = iNaviPane->CreateNavigationLabelL(reader);
            CleanupStack::PopAndDestroy();  // resource reader
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviLabelLeftArrow:
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            //iNaviDecorator = iNaviPane->CreateNavigationLabelL(_L("Navi info"));
            iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_NAVI_INFO);
            iNaviDecorator = iNaviPane->CreateNavigationLabelL(tempLabel);
            iNaviDecorator->MakeScrollButtonVisible(ETrue);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, EFalse);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, ETrue);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviLabelRightArrow:
            if (!iNaviDecorator)
                {
                iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_NAVI_INFO);
                iNaviDecorator = iNaviPane->CreateNavigationLabelL(tempLabel);
                iNaviDecorator->MakeScrollButtonVisible(ETrue);
                }
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, ETrue);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviLabelBothArrows:
            delete iNaviDecorator;
            iNaviDecorator = NULL;

            iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_NAVI_INFO);
            iNaviDecorator = iNaviPane->CreateNavigationLabelL(tempLabel);
            iNaviDecorator->MakeScrollButtonVisible(ETrue);

            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, EFalse);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviLongLabelBothArrows:
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_LONG_NAVI);
            iNaviDecorator = iNaviPane->CreateNavigationLabelL(tempLabel);
            iNaviDecorator->MakeScrollButtonVisible(ETrue);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, EFalse);
            iNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviHintText:
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            TResourceReader resourceReader;
            iCoeEnv->CreateResourceReaderLC(resourceReader, R_AKNEXSPANE_NAVI_TEXT);
            iNaviDecorator = iNaviPane->CreateMessageLabelL(resourceReader);
            CleanupStack::PopAndDestroy();  // resource reader
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviHintTextLong:
            delete iNaviDecorator;
            iNaviDecorator = NULL;
            iCoeEnv->ReadResource(tempLabel, R_AKNEXSPANE_NAVI_LONG_TEXT);
            iNaviDecorator = iNaviPane->CreateMessageLabelL(tempLabel);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviVolumeIndicator:
            CreateNaviDecoratorForVolumeIndicatorL(ETrue);
            STATIC_CAST(CAknVolumeControl*,iNaviDecorator->DecoratedControl())->SetValue(3);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviVolumeIndicator2:
            CreateNaviDecoratorForVolumeIndicatorL(ETrue);
            STATIC_CAST(CAknVolumeControl*,iNaviDecorator->DecoratedControl())->SetValue(8);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviVolumeIndicator3:
            CreateNaviDecoratorForVolumeIndicatorL(EFalse);
            STATIC_CAST(CAknVolumeControl*,iNaviDecorator->DecoratedControl())->SetValue(10);
            iNaviPane->PushL(*iNaviDecorator);
            break;

        case ENaviVolumeIndicator4:
            {
            CEikStatusPane* sp = iEikonEnv->AppUiFactory()->StatusPane();
            sp->SwitchLayoutL(R_AVKON_STATUS_PANE_LAYOUT_USUAL);
            CreateNaviDecoratorForVolumeIndicatorL(EFalse);
            STATIC_CAST(CAknVolumeControl*,iNaviDecorator->DecoratedControl())->SetValue(1);
            iNaviPane->PushL(*iNaviDecorator);
            }
            break;

        case ESwitchLayoutOff:
            {
            iNaviPane->Pop();
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
// CAknExSpaneNaviViewContainer::NaviTabDlg(TInt aIndex)
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::OpenNaviTabDlg(TInt aIndex)
    {
    if (!IsTabBeDsiplayed())
        {
        // do nothing if current decorator is not tab decorator or current decorator is empty
        return;
        }

    CAknExSpaneNaviTabDialog *myDialog = 
                        new(ELeave) CAknExSpaneNaviTabDialog(this, aIndex);
    myDialog->ConstructL();
    //CEikDialog *myDialog = new(ELeave) CEikDialog;

    switch (aIndex)
        {
        case EAknExSpaneNaviTabAdd:
            myDialog->ExecuteLD(R_AKNEXSPANE_ADD_TAB_DLG);
            break;
        case EAknExSpaneNaviTabReplace:
            myDialog->ExecuteLD(R_AKNEXSPANE_REPLACE_TAB_DLG);
            break;
        case EAknExSpaneNaviTabSelect:
            myDialog->ExecuteLD(R_AKNEXSPANE_SELECT_TAB_DLG);
            break;
        default:
            // If the control comes to here, error
            delete myDialog;
            break;
        }
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::SetNaviIcon(TInt aIndex)
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::SetNaviIcon(TInt aIndex)
    {
    CAknNavigationDecorator* curNaviDecorator;

    if (!IsTabBeDsiplayed())
        {
        if (iNaviDecorator)
            {
            curNaviDecorator = iNaviDecorator;
            }
        else
            {
            // do nothing if current decorator is empty.
            return;
            }
        }
    else
        {
        curNaviDecorator = iNaviDecoratorForTabs;
        }

    TInt controlType = curNaviDecorator->ControlType();
    if ((controlType == curNaviDecorator->ENotSpecified)
        //|| (controlType==curNaviDecorator->ETabGroup)
        //|| (controlType==curNaviDecorator->ENaviLabel)
        //|| (controlType==curNaviDecorator->ENaviImage)
        //|| (controlType == curNaviDecorator->EHintText)
        //|| (controlType == curNaviDecorator->EEditorIndicator)
        )
        {
        // it the current decorator do not support navi icon, return
        return;
        }

    switch (aIndex)
        {
        case EAknExSpaneNaviArrayLeftOn:
            curNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, EFalse);
            iNaviPane->PushL(*curNaviDecorator);
            break;
        case EAknExSpaneNaviArrayLeftFade:
            curNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ELeftButton, ETrue);
            iNaviPane->PushL(*curNaviDecorator);
            break;
        case EAknExSpaneNaviArrayRightOn:
            curNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, EFalse);
            iNaviPane->PushL(*curNaviDecorator);
            break;
        case EAknExSpaneNaviArrayRightFade:
            curNaviDecorator->SetScrollButtonDimmed(CAknNavigationDecorator::ERightButton, ETrue);
            iNaviPane->PushL(*curNaviDecorator);
            break;
        case EAknExSpaneNaviArrayEnable:
            curNaviDecorator->MakeScrollButtonVisible(ETrue);
            iNaviPane->PushL(*curNaviDecorator);
            break;
        case EAknExSpaneNaviArrayDisable:
            curNaviDecorator->MakeScrollButtonVisible(EFalse);
            iNaviPane->PushL(*curNaviDecorator);
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::SetTabStyle(TInt aIndex)
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::SetTabStyle(TInt aIndex)
    {

    if (!IsTabBeDsiplayed())
        {
        // do nothing if current decorator is not tab decorator or current decorator is empty
        return;
        }


    switch (aIndex)
        {
        case EAknExSpaneNaviTabStyleOne:
            {
            TBuf< KLengthOfNaviTempString > titleLabel;
            iCoeEnv->ReadResource(titleLabel, R_AKNEXSPANE_NAVI_ONE);
            iStLabel->SetTextL(titleLabel);
            iStLabel->SetExtent(AKNEXSPANE_MID_POINT, iStLabel->MinimumSize());
            CAknTabGroup* tabGroup = CreateNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS);
            tabGroup->SetTabFixedWidthL(EAknTabWidthWithOneTab);
            iNaviPane->PushL(*iNaviDecoratorForTabs);
            }
            break;
        case EAknExSpaneNaviTabStyleTwoShort:
            RunTestL(ETwoTabs);
            break;
        case EAknExSpaneNaviTabStyleTwoLong:
            RunTestL(ETwoLongTabs);
            break;
        case EAknExSpaneNaviTabStyleThreeShort:
            RunTestL(EThreeTabs);
            break;
        case EAknExSpaneNaviTabStyleThreeLong:
            RunTestL(EThreeLongTabs);
            break;
        case EAknExSpaneNaviTabStyleFour:
            RunTestL(EFourTabs);
            break;
        default:
            break;
        }

    }


// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::SetTabOperate(
//  TInt aCommand, TInt aTabIndex, TDes& aTabTextDes, TInt aTabImageNumber)
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::SetTabOperate(TInt aCommand, 
    TInt aTabIndex, TDes& aTabTextDes, TInt aTabImageNumber)
    {
    CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
    TInt workTabId = tabGroup->ActiveTabId();
    // There total 9 predefine tabs in this tab group.
    // Because most of the id of the predefined tab is change from 31 to 65 and 12-18.
    // Only one predefined tab id is -2.
    // So we decide to use the id number from 10 to 30 for new user create tabs.
    // But when you add tab, sometime the id is duplicate, application will
    // try to create new tab with the duplicate id. We didn't forbit this operation
    // because we think maybe our user just want to check what will happen when create
    // new tab with duplicte ID.
    // ON THE OTHER HAND, we think the avkon allow duplicate tab id since we test it under R38.
    TInt newTabNumbers = tabGroup->TabCount()+1;
    CFbsBitmap* bitmap = NULL;
    CFbsBitmap* bitmapM = NULL;

    if (aTabImageNumber!=EAknExSpaneNaviTabNoImage)
        {
        // prepare the image resource for new tab
        switch (aTabImageNumber)
            {
            case EAknExSpaneNaviTabImage2:    // media size image
                bitmap = iEikonEnv->CreateBitmapL( KNaviBitMapFile, EMbmAknexspaneLshellicon );
                bitmapM = iEikonEnv->CreateBitmapL( KNaviBitMapFile, EMbmAknexspaneLshelliconm );
                break;
            case EAknExSpaneNaviTabImage3:    // big image
                bitmap = iEikonEnv->CreateBitmapL( KNaviBitMapFile, EMbmAknexspaneTitle );
                bitmapM = NULL;
                break;
            default:                     // small image
                bitmap = iEikonEnv->CreateBitmapL( KNaviBitMapFile, EMbmAknexspaneIndicato );
                bitmapM = iEikonEnv->CreateBitmapL( KNaviBitMapFile, EMbmAknexspaneIndicatom );
                break;
            }
        }

    switch (aCommand)
        {
        case EAknExSpaneNaviTabAdd:
            {
            if (aTabImageNumber==EAknExSpaneNaviTabNoImage)
                {
                // no image
                tabGroup->AddTabL(newTabNumbers,aTabTextDes);
                }
            else
                {
                // have image
                if (aTabTextDes.Length())
                    {
                    // no text
                    tabGroup->AddTabL(newTabNumbers, aTabTextDes, bitmap, bitmapM);
                    }
                else
                    {
                    // have text
                    tabGroup->AddTabL(newTabNumbers, bitmap, bitmapM);
                    }
                } // end of have_image process

            tabGroup->SetActiveTabById(newTabNumbers);
            break;
            }

        case EAknExSpaneNaviTabReplace:   // replace tab
            {
            workTabId = tabGroup->TabIdFromIndex(aTabIndex);

            if (aTabImageNumber==EAknExSpaneNaviTabNoImage)
                {
                // no image
                tabGroup->ReplaceTabL(workTabId,aTabTextDes);
                }
            else
                {
                // have image
                if (aTabTextDes.Length())
                    {
                    // no text
                    tabGroup->ReplaceTabL(workTabId, aTabTextDes, bitmap, bitmapM);
                    }
                else
                    {
                    // have text
                    tabGroup->ReplaceTabL(workTabId, bitmap, bitmapM);
                    }
                } // end of have_image process

            break;
            }

        case EAknExSpaneNaviTabDelete:    // delete current tab
            {
            if (workTabId > 0)
                {
                tabGroup->DeleteTabL(workTabId);
                tabGroup->SetActiveTabByIndex(tabGroup->TabCount()-1);
                }
            break;
            }

        case EAknExSpaneNaviTabSelect:    // select tab
            {
            tabGroup->SetActiveTabByIndex(aTabIndex);
            break;
            }

        default:
            break;
        }

    if (aTabImageNumber!=EAknExSpaneNaviTabNoImage)
        {
        bitmap = NULL;  // Bitmap owned by navigation decorator
        bitmapM = NULL;  // Bitmap owned by navigation decorator
        }

    DrawNow();
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::IsTabBeDsiplayed()
// 
// ---------------------------------------------------------
//
TBool CAknExSpaneNaviViewContainer::IsTabBeDsiplayed()
    {
    // get the StatusPane pointer
    if (!iNaviPane)
        {
        CEikStatusPane *sp = ((CAknAppUi*)iEikonEnv->EikAppUi())->StatusPane();
        // Fetch pointer to the default navi pane control
        iNaviPane = (CAknNavigationControlContainer *)sp->ControlL(TUid::Uid(EEikStatusPaneUidNavi));
        }

    // get current decorator
    CAknNavigationDecorator* curDecorator = iNaviPane->Top();

    if ((iNaviDecoratorForTabs != curDecorator) || 
        (!curDecorator))
        {
        // do nothing if current decorator is not tab decorator or current decorator is empty
        return EFalse;
        }

    TInt no=iTestNumber;
    if (no>0)
        no--;
    else
        no=EDefault;

    switch (no)
        {
        case EFourTabs:
        case ETabActiveIllegal1:
        case ETabActive0:
        case ETabActive1:
        case ETabActive2:
        case ETabActive3:
        case ETabActive4:
        case ETabActive5:
        case ETabActiveIllegal2:
        case ETabAddNew:
        case ETabReplaceCurrent:
        case ETabDeleteCurrent:
        case ETabActiveById:
        case ETabActiveByIdIllegal:
            return EFalse;

        default:
            break;
        }


    return ETrue;
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::GetTabIndexRange(TInt* aStartIndex, TInt* aEndIndex, TInt* aCurIndex)
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::GetTabIndexRange(TInt* aStartIndex, TInt* aEndIndex, TInt* aCurIndex)
    {
        *aStartIndex = 1;
        *aEndIndex = 0;
        *aCurIndex = 0;
        if (IsTabBeDsiplayed())
            {
            CAknTabGroup* tabGroup = GetNaviDecoratorsForTabGroupL(R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS);
            *aStartIndex = 0;
            *aEndIndex = tabGroup->TabCount()-1;
            *aCurIndex = tabGroup->ActiveTabIndex();
            }
    }
// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::CreateNaviDecoratorsForTabGroupL(TInt aResourceId)
// 
// ---------------------------------------------------------
//
CAknTabGroup* CAknExSpaneNaviViewContainer::CreateNaviDecoratorsForTabGroupL(TInt aResourceId)
    {
    CAknNavigationDecorator* iNaviDecoratorForTabsTemp;

    //R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS
    //R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS
    TResourceReader reader;
    iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
        
    iNaviDecoratorForTabsTemp = iNaviPane->CreateTabGroupL(reader); 
    CleanupStack::PopAndDestroy();  // resource reader

    delete iNaviDecoratorForTabs;
    iNaviDecoratorForTabs = NULL;

    iNaviDecoratorForTabs = iNaviDecoratorForTabsTemp;
    return STATIC_CAST(CAknTabGroup*, iNaviDecoratorForTabs->DecoratedControl());
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::GetNaviDecoratorsForTabGroupL(TInt aResourceId)
// 
// ---------------------------------------------------------
//
CAknTabGroup* CAknExSpaneNaviViewContainer::GetNaviDecoratorsForTabGroupL(TInt aResourceId)
    {
    if (!iNaviDecoratorForTabs)
        {
        TResourceReader reader;

        //R_AKNEXSPANE_NAVI_TAB_GROUP_LONG_LABELS
        //R_AKNEXSPANE_NAVI_TAB_GROUP_SHORT_LABELS
        iCoeEnv->CreateResourceReaderLC(reader,aResourceId);
        
        iNaviDecoratorForTabs = iNaviPane->CreateTabGroupL(reader); 
        CleanupStack::PopAndDestroy();  // resource reader
        }
    return STATIC_CAST(CAknTabGroup*, iNaviDecoratorForTabs->DecoratedControl());
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::CreateNaviDecoratorForEditorIndicatorContainerL()
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::CreateNaviDecoratorForEditorIndicatorContainerL()
    {
    delete iNaviDecorator;
    iNaviDecorator = NULL;
    iNaviDecorator = iNaviPane->CreateEditorIndicatorContainerL();
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::CreateNaviDecoratorForVolumeIndicatorL(TBool aType)
// 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::CreateNaviDecoratorForVolumeIndicatorL(TBool aType)
    {
    delete iNaviDecorator;
    iNaviDecorator = NULL;
    if (aType)
        iNaviDecorator = iNaviPane->CreateVolumeIndicatorL(R_AVKON_NAVI_PANE_VOLUME_INDICATOR);
    else
        iNaviDecorator = iNaviPane->CreateVolumeIndicatorL(R_AVKON_NAVI_PANE_RECORDER_VOLUME_INDICATOR);
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::SizeChanged()
// Called by framework when the view size is changed. 
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::SizeChanged()
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
        iNaviLabel->SetExtent(AKNEXSPANE_TOP_POINT_IDLE, iNaviLabel->MinimumSize());
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
        iNaviLabel->SetExtent(AKNEXSPANE_TOP_POINT, iNaviLabel->MinimumSize());
        iStLabel->SetExtent(AKNEXSPANE_MID_POINT, iStLabel->MinimumSize());
        iInfoLabel->SetExtent(AKNEXSPANE_LOW_POINT, iInfoLabel->MinimumSize());
        }
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::CountComponentControls() const
// Returns number of component. 
// ---------------------------------------------------------
//
TInt CAknExSpaneNaviViewContainer::CountComponentControls() const
    {
    return ENumberOfComponent;
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::ComponentControl(TInt aIndex) const
// Returns pointer to particular component.
// ---------------------------------------------------------
//
CCoeControl* CAknExSpaneNaviViewContainer::ComponentControl(TInt aIndex) const
    {
    switch (aIndex)
        {
        case ETitleLabel:
            return iNaviLabel;
        case EStLabel:
            return iStLabel;
        case EInfoLabel:
            return iInfoLabel;
        default:
            return NULL;
        } 
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::Draw(const TRect& aRect) const
// Draw function.
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushColor(AKNEXSPANE_KRGB_GREEN);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.DrawRect(aRect);
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::HandleControlEventL(
//     CCoeControl* aControl, TCoeEvent aEventType)
// Handles an event of type aEventType reported
// by the control aControl to this observer.
// ---------------------------------------------------------
//
void CAknExSpaneNaviViewContainer::HandleControlEventL(CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    }

// ---------------------------------------------------------
// CAknExSpaneNaviViewContainer::IsNaviIconMenu()
// 
// ---------------------------------------------------------
//
TBool CAknExSpaneNaviViewContainer::IsNaviIconMenu()
    {
    TInt no=iTestNumber;
    if (no>0)
        no--;
    else
        no=EDefault;

    switch (no)
        {
        case EDefault:
        case ENaviVolumeIndicator:
        case ENaviVolumeIndicator2:
        case ENaviVolumeIndicator3:
        case ENaviVolumeIndicator4:
        case ESwitchLayoutOff:
        case ESwitchLayoutOn:
        case ESwitchVisibilityOff:
        case ESwitchVisibilityOn:
            return EFalse;

        default:
            break;
        }

    return ETrue;
    }

// End of File
