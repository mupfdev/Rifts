/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include "BTDiscoveryAppUi.h"
#include "BTDiscoveryAppView.h"
#include "BTDiscovery.hrh"
#include "BTDiscovery.pan"

// ConstructL is called by the application framework
void CBTDiscoveryAppUi::ConstructL()
    {
    BaseConstructL();
    iAppView = CBTDiscoveryAppView::NewL(ClientRect());    
    iAppView->SetMopParent(this);
    AddToStackL(iAppView);
    }

CBTDiscoveryAppUi::CBTDiscoveryAppUi()                              
    {
    // No implementation required
    }

CBTDiscoveryAppUi::~CBTDiscoveryAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CBTDiscoveryAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EBTDiscoveryDiscover:
            iAppView->SelectDeviceAndListServicesL();
            break;

        case EBTDiscoveryClear:
            iAppView->ClearL();
            break;

        default:
            Panic(EBTDiscoveryUnrecognisedMenuCommand);
            break;      

        }
    }



