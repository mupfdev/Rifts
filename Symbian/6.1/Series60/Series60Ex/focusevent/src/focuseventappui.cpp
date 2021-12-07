/* Copyright (c) 2001, Nokia. All rights reserved */
#include <avkon.hrh>
#include "FocusEvent.pan"
#include "FocusEventAppUi.h"
#include "FocusEventAppView.h"


// Handle any change of focus
void CFocusEventAppUi::HandleForegroundEventL(TBool aForeground)
    {
	if(!aForeground)
	    {
#ifdef __WINS__
        User::InfoPrint(_L("Lost focus"));
#endif /* __WINS__ */
        iAppView->Print(_L("Lost focus"));
        iAppView->PrintNewLineL ();
	    }
    else
        {
#ifdef __WINS__
        User::InfoPrint(_L("Gained focus"));
#endif /* __WINS__ */
        iAppView->Print(_L("Gained focus"));
        iAppView->PrintNewLineL ();
        }

    CAknAppUi::HandleForegroundEventL(aForeground);
    }


// ConstructL is called by the application framework
void CFocusEventAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CFocusEventAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CFocusEventAppUi::CFocusEventAppUi()                              
    {
    // add any construction that cannot leave here
    }

CFocusEventAppUi::~CFocusEventAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        }

    delete iAppView;
    iAppView = NULL;
    }

// handle any menu commands
void CFocusEventAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        default:
            User::Panic (_L("FocusEvent"), EFocusEventBasicUi);
            break;
        }
    }
