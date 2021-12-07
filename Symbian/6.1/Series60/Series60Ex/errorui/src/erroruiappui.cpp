/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>

#include <errorui.h>

#include "ErrorUi.pan"
#include "ErrorUiAppUi.h"
#include "ErrorUiAppView.h"
#include "ErrorUi.hrh"

// ConstructL is called by the application framework
void CErrorUiAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CErrorUiAppView::NewL(ClientRect());    
    AddToStackL(iAppView);

    iErrorUI = CErrorUI::NewL();
    }

CErrorUiAppUi::CErrorUiAppUi()                              
    {
	// no implementation required
    }

CErrorUiAppUi::~CErrorUiAppUi()
    {

	delete iErrorUI;
	iErrorUI = NULL;

    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CErrorUiAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        case EErrorUiNote:
                {
                TRAPD(err, iAppView->ThrowLeaveErrorL(KErrCancel));
                HandleLeaveErrorL(err, CErrorUiAppUi::EShowNote);
                }
            break;

        case EErrorUiQuery:
                {
                TRAPD(err, iAppView->ThrowLeaveErrorL(KErrNoMemory));
                HandleLeaveErrorL(err, CErrorUiAppUi::EShowQuery);
                }
            break;

        default:
            Panic(EErrorUiBasicUi);
            break;
        }
    }

// Check for errors, handle OOM or Cancel
void CErrorUiAppUi::HandleLeaveErrorL(TInt aError, TErrorDialogType aType)
    {
    if (!aError)
        {
        return;
        }

    if ((aError == KErrNoMemory) || (aError == KErrCancel))
        {
        // Only interested in handling OOM or Cancel errors
        if (aType == EShowQuery)
            {
            iErrorUI->ShowGlobalErrorQueryL(aError, CTextResolver::ECtxNoCtx);
            }
        else
            {
            iErrorUI->ShowGlobalErrorNoteL(aError);
            }
        }
    else
        {
        // Not OOM or Cancel error - pass onto higher levels to handle
        User::Leave(aError);
        }
    }

