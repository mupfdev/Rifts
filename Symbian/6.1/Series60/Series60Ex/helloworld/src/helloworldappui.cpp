/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include <aknnotewrappers.h> 

#include "HelloWorld.pan"
#include "HelloWorldAppUi.h"
#include "HelloWorldAppView.h"
#include "HelloWorld.hrh"

// ConstructL is called by the application framework
void CHelloWorldAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CHelloWorldAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CHelloWorldAppUi::CHelloWorldAppUi()                              
    {
	// no implementation required
    }

CHelloWorldAppUi::~CHelloWorldAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CHelloWorldAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case EHelloWorldCommand1:
            {
            _LIT(message,"Hello!");
            CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
            informationNote->ExecuteLD(message);
            }
            break;

        default:
            Panic(EHelloWorldBasicUi);
            break;
        }
    }



