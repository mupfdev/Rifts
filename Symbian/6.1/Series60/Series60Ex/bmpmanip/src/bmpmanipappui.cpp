/* Copyright (c) 2001, Nokia. All rights reserved */

#include <avkon.hrh>
#include "EikonEnvironment.h"
#include "Bmpmanip.pan"
#include "BmpmanipAppUi.h"
#include "BmpmanipAppView.h"
#include "Bmpmanip.hrh"



// ConstructL is called by the application framework
void CBmpmanipAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CBmpmanipAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CBmpmanipAppUi::CBmpmanipAppUi()                              
    {
    // add any construction that cannot leave here
    }

CBmpmanipAppUi::~CBmpmanipAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        }

    delete iAppView;
    iAppView = NULL;
    }

// handle any menu commands
void CBmpmanipAppUi::HandleCommandL(TInt aCommand)
    {
	
	//Generally, any command operation would just be allowed to leave directly, but here
	//we want to perform some error condition checking.  Rather than put the entire switch statement
	//inside the TRAPD macro, we create a helper function to make things clearer.

	TRAPD(err,CommandHandlerL(aCommand));

	//If we try and perform an action before the gif file is loaded
	if (err == KErrInUse)
		{
		NEikonEnvironment::MessageBox (_L("Waiting for gif file to load"));
		//CAknInformationNote* informationNote = new (ELeave) CAknInformationNote;
            //informationNote->ExecuteLD();
		}
	else if (err != KErrNone)
		{
		User::Leave(err);
		}

    }


//function encloses command-handling switch statement
void CBmpmanipAppUi::CommandHandlerL(TInt aCommand)
	{
	switch(aCommand)
		{
	case EAknSoftkeyExit:
		Exit();
		break;

	case EBmpmanipCmdRotate90:
		iAppView->RotateImageClockwiseL(CBmpmanipAppView::E90Degrees);
		break;

	case EBmpmanipCmdRotate180:
		iAppView->RotateImageClockwiseL(CBmpmanipAppView::E180Degrees);
		break;

	case EBmpmanipCmdRotate270:
		iAppView->RotateImageClockwiseL(CBmpmanipAppView::E270Degrees);
		break;

	case EBmpmanipCmdSave:
		iAppView->SaveL();
		break;

	default:
		User::Panic (_L("Bmpmanip"), EBmpmanipBasicUi);
		break;
		}
	}
