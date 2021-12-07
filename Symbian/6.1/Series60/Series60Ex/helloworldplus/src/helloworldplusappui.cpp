/* Copyright (c) 2002, Nokia. All rights reserved */

#include <aknnotewrappers.h>
#include <avkon.hrh>

#include <stringloader.h>
#include <helloworldplus.rsg>

#include "HelloWorldPlus.pan"
#include "HelloWorldPlusAppUi.h"
#include "HelloWorldPlusAppView.h"
#include "HelloWorldPlus.hrh"

// ConstructL is called by the application framework
void CHelloWorldPlusAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CHelloWorldPlusAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CHelloWorldPlusAppUi::CHelloWorldPlusAppUi()                              
    {
    // add any construction that cannot leave here
    }

CHelloWorldPlusAppUi::~CHelloWorldPlusAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CHelloWorldPlusAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
		case EHelloWorldPlusCommand:
            {
			// load a string from the resource file and display it
			HBufC* textResource = StringLoader::LoadLC(R_NEW_STRING_RESOURCE);
            CAknInformationNote* informationNote;
			informationNote = new (ELeave) CAknInformationNote;
            informationNote->ExecuteLD(textResource->Des());
			CleanupStack::PopAndDestroy(textResource);
            }
            break;

		case EHelloWorldPlusDrawNow:
			{
            iAppView->DrawNow();
			break;
			}

		case EHelloWorldPlusUserDraw:
			{
			iAppView->UserDraw();
			break;
			}

        case EHelloWorldPlusCommand1:
            {
            _LIT(message,"Hello!");
            CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
            informationNote->ExecuteLD(message);
            }
            break;

		case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        default:
            User::Panic (_L("HelloWorldPlus"), EHelloWorldPlusBasicUi);
            break;
        }
    }



