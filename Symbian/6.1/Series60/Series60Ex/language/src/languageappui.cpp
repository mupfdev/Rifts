/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include <Language.rsg>
#include "Language.pan"
#include "LanguageAppUi.h"
#include "LanguageAppView.h"
#include "Language.hrh"
#include "EikonEnvironment.h"

// ConstructL is called by the application framework
void CLanguageAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CLanguageAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CLanguageAppUi::CLanguageAppUi()                              
    {
    // No implementation required
    }

CLanguageAppUi::~CLanguageAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

void CLanguageAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
		case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case ELanguageCommand1:
                {
                HBufC*  string;
                string = CCoeEnv::Static()->AllocReadResourceLC(R_LANGUAGE_STRING_COMMAND1);
                NEikonEnvironment::MessageBox(*string);
                CleanupStack::PopAndDestroy(string);
                }
            break;

        default:
            User::Panic (_L("Language"), ELanguageBasicUi);
            break;
        }
    }



