/* Copyright (c) 2001, Nokia. All rights reserved */

#include <avkon.hrh>
#include <eikmenup.h>
#include <CameraServ.h>
#include <SnapShot.rsg>
#include "SnapShot.pan"
#include "SnapShotAppUi.h"
#include "SnapShotAppView.h"
#include "SnapShot.hrh"

void CSnapShotAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CSnapShotAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CSnapShotAppUi::CSnapShotAppUi()                              
    {
    // add any construction that cannot leave here
    }

CSnapShotAppUi::~CSnapShotAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        }

    delete iAppView;
    iAppView = NULL;
    }

void CSnapShotAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (aResourceId == R_SNAPSHOT_MENU)
        {
        if (iAppView->IsCameraReady())
            {
            aMenuPane->SetItemDimmed(ESnapShotTakePicture, EFalse);
            }
        else
            {
            aMenuPane->SetItemDimmed(ESnapShotTakePicture, ETrue);
            }
        }
    }

void CSnapShotAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
		case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case ESnapShotTakePicture:
            iAppView->Snap();
            break;

        default:
            User::Panic (_L("SnapShot"), ECameraBasicUi);
            break;
        }
    }



