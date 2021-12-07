/* Copyright (c) 2001, Nokia. All rights reserved */
#include <eiktbar.h>
#include <eikenv.h>
#include <w32adll.h>
#include <avkon.hrh>
#include "testframe.pan"
#include "TestframeDocument.h"
#include "TestframeAppUi.h"
#include "TestframeAppView.h"
#include "testframe.hrh"



CTestframeAppUi::CTestframeAppUi()
	{
	//	Implementation not required
	}


void CTestframeAppUi::ConstructL()
	{
    BaseConstructL();

    iAppView = CTestframeAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
	}


CTestframeAppUi::~CTestframeAppUi()
	{
    if (iAppView)
		{
		RemoveFromStack(iAppView);
		}

    delete iAppView;
    iAppView = NULL;
	}

void CTestframeAppUi::HandleCommandL(TInt aCommand)
	{
    switch(aCommand)
		{
        case EAknSoftkeyExit:
            Exit();
            break;
		case ETestFrameCmdRunTests:
			iAppView->RunTestsL();
			break;

        default:
            User::Panic(KTestFrameworkPanic, ETestframeBasicUi);
            break;
		}
    
	}

