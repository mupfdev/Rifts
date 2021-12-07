/* Copyright (c) 2001, Nokia. All rights reserved */

#include <avkon.hrh>
#include "Graphics.pan"
#include "GraphicsAppUi.h"
#include "GraphicsAppView.h"
#include "Graphics.hrh"

// ConstructL is called by the application framework
void CGraphicsAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CGraphicsAppView::NewL(ApplicationRect());    

    AddToStackL(iAppView);
    }

CGraphicsAppUi::CGraphicsAppUi()                              
    {
    }

CGraphicsAppUi::~CGraphicsAppUi()
    {
	if (iAppView)
		{
	    RemoveFromStack(iAppView);

		delete iAppView;
	    iAppView = NULL;
		}
    }

// handle any menu commands
void CGraphicsAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

       	case EGaphicsNoOffScreenDemo:
			iAppView->StartNoOffScreenDemo();
			break;

		case EGaphicsOffScreenDemo:
			iAppView->StartOffScreenDemo();
			break;

		case EGaphicsStopDemo:
			iAppView->StopDemo();
			break;

        default:
            User::Panic (_L("Graphics"), EGraphicsBasicUi);
            break;
        }
    }



