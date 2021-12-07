/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include <eikmenup.h>
#include <BTAdvertiser.rsg>
#include "BTAdvertiser.pan"
#include "BTAdvertiserAppUi.h"
#include "BTAdvertiserAppView.h"
#include "BTAdvertiser.hrh"

// ConstructL is called by the application framework
void CBTAdvertiserAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CBTAdvertiserAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CBTAdvertiserAppUi::CBTAdvertiserAppUi()
    {
    // add any construction that cannot leave here
    }

CBTAdvertiserAppUi::~CBTAdvertiserAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

void CBTAdvertiserAppUi::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
    {
    if (aResourceId == R_BTADVERTISER_MENU)
        {
        if (iAppView->IsAdvertising())
            {
            aMenuPane->SetItemDimmed(EBTAdvertiserStartAdvertiser, ETrue);
            }
        else
            {
            aMenuPane->SetItemDimmed(EBTAdvertiserStopAdvertiser, ETrue);
            }
        }
    }

// handle any menu commands
void CBTAdvertiserAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EBTAdvertiserStartAdvertiser:
            iAppView->StartAdvertiserL();
            break;

        case EBTAdvertiserStopAdvertiser:
            iAppView->StopAdvertiserL();
            break;

        default:
            Panic(EBTAdvertiserCmdNotRecognised);
            break;
        }
    }
