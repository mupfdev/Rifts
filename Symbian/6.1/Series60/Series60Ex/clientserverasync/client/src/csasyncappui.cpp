/* Copyright (c) 2001, Nokia. All rights reserved */

#include <eikmenup.h>
#include <avkon.hrh>
#include <CSAsync.rsg>
#include "CSAsync.pan"
#include "CSAsyncAppUi.h"
#include "CSAsyncAppView.h"
#include "CSAsyncDocument.h"
#include "CSAsync.hrh"

// ConstructL is called by the application framework
void CCSAsyncAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CCSAsyncAppView::NewL(ClientRect(), *AsyncDocument());    

    AddToStackL(iAppView);
    }

CCSAsyncAppUi::CCSAsyncAppUi()                              
    {
    // No implementation required
    }

CCSAsyncAppUi::~CCSAsyncAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

CCSAsyncDocument* CCSAsyncAppUi::AsyncDocument() const 
    { 
    return static_cast<CCSAsyncDocument*>(iDocument); 
    }

// handle any menu commands
void CCSAsyncAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EStartClock:
	        AsyncDocument()->UpdateTime();
            break;

        case EStopClock:
            AsyncDocument()->StopClock() ;
            break ;

        default:
            User::Panic (KCSAsyncClient, ECSAsyncBasicUi);
            break;
        }
    }

void CCSAsyncAppUi::HandleTimeUpdate()
    {
    __ASSERT_ALWAYS(iAppView, User::Panic (KCSAsyncClient, ECSAsyncProgram));
    iAppView->DrawNow();
    }

void CCSAsyncAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
	if (aResourceId == R_CSASYNC_MENU)
        {
        if (AsyncDocument()->ClockActive())
            {
            aMenuPane->SetItemDimmed(EStartClock, ETrue);
            aMenuPane->SetItemDimmed(EStopClock, EFalse);
            }
        else
            {
            aMenuPane->SetItemDimmed(EStartClock, EFalse);
            aMenuPane->SetItemDimmed(EStopClock, ETrue);
            }
        }
    }

