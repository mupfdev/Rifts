/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include "BTHCIAppUi.h"
#include "BTHCIAppView.h"
#include "BTHCIUtility.h"
#include "BTHCI.hrh"
#include "BTHCI.pan"

// ConstructL is called by the application framework
void CBTHCIAppUi::ConstructL()
    {
    BaseConstructL();
    iAppView = CBTHCIAppView::NewL(ClientRect());    
    iAppView->SetMopParent(this);
    AddToStackL(iAppView);

    iBTHCIUtility = CBTHCIUtility::NewL(*iAppView);
    }

CBTHCIAppUi::CBTHCIAppUi()                              
    {
    // No implementation required
    }

CBTHCIAppUi::~CBTHCIAppUi()
    {
    delete iBTHCIUtility;
    iBTHCIUtility = NULL;

    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CBTHCIAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EBTHCILocalVersion:
            iBTHCIUtility->LocalVersionHCICommand();
            break;

        case EBTHCILocalFeatures:
            iBTHCIUtility->LocalFeaturesHCICommand();
            break;

        case EBTHCILocalAddress:
            iBTHCIUtility->LocalAddressHCICommand();
            break;

        case EBTHCIClear:
            iAppView->ClearL();
            break;

        default:
            Panic(EBTHCIUnrecognisedCommand);
            break;      

        }
    }



