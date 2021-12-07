/* Copyright (c) 2002, Nokia. All rights reserved */

#include <e32std.h>

#include "MultiViews.pan"
#include "MultiViewsAppUi.h"
#include "MultiViewsView1.h"
#include "MultiViewsView2.h"


// ConstructL is called by the application framework
void CMultiViewsAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView1 = CMultiViewsView1::NewL();
    iAppView2 = CMultiViewsView2::NewL();

    AddViewL(iAppView1); // transfer ownership to base class 
    AddViewL(iAppView2); // transfer ownership to base class 

    SetDefaultViewL(*iAppView1);
    }

// handle any menu commands
void CMultiViewsAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;
        default:
            Panic(EMultiViewsBasicUi);
            break;
        }
    }



