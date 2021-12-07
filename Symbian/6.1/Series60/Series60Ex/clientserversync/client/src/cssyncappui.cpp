/* Copyright (c) 2001, Nokia. All rights reserved */
#include <eikmenup.h>
#include <avkon.hrh>
#include "CSSync.pan"
#include "CSSyncAppUi.h"
#include "CSSyncAppView.h"
#include "CSSyncDocument.h"
#include "CSSync.hrh"

void CCSSyncAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CCSSyncAppView::NewL(ClientRect(), *SyncDocument());    

    AddToStackL(iAppView);
    }

CCSSyncAppUi::CCSSyncAppUi()                              
    {
    // No implementation required
    }

CCSSyncAppUi::~CCSSyncAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

CCSSyncDocument* CCSSyncAppUi::SyncDocument() const 
    { 
    return static_cast<CCSSyncDocument*>(iDocument); 
    }

void CCSSyncAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EDisplayTime:
            // Pull the time from the server
            SyncDocument()->UpdateTime();

            // Get view to display the new time
            iAppView->DrawNow();
            break;
            
        default:
            User::Panic (KCSSyncClient, ECSSyncBasicUi);
            break;
        }
    }


