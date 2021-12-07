/* Copyright (c) 2001, Nokia. All rights reserved */

#include <aknquerydialog.h>
#include <avkon.hrh>
#include <eikmenup.h>
#include <eikgted.h>
#include <Sockets.rsg>
#include "Sockets.pan"
#include "SocketsAppUi.h"
#include "SocketsAppView.h"
#include "Sockets.hrh"
#include "SocketsEngine.h"

// ConstructL is called by the application framework
void CSocketsAppUi::ConstructL()
    {
    BaseConstructL();

    // Create view
    iAppView = CSocketsAppView::NewL(ClientRect());    
    AddToStackL(iAppView);

    // Create engine
    iSocketsEngine = CSocketsEngine::NewL(*iAppView);
    }

CSocketsAppUi::CSocketsAppUi()                              
    {
    }

CSocketsAppUi::~CSocketsAppUi()
    {
    delete iSocketsEngine;
    iSocketsEngine = NULL;

    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CSocketsAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case ESocketsCmdConnect:
            {
            // Create dialog to allow user to view/edit connection details
            TBuf<KMaxServerNameLength> serverName(iSocketsEngine->ServerName());
            TInt port(iSocketsEngine->Port());

            CAknMultiLineDataQueryDialog* dialog =
                CAknMultiLineDataQueryDialog::NewL(serverName, port);

            // Display and execute dialog, and act according to return value
            if (dialog->ExecuteLD(R_SOCKETS_DIALOG_CONNECT))
                {
                iSocketsEngine->SetServerName(serverName);
                iSocketsEngine->SetPort(port);
                iSocketsEngine->ConnectL(); // Initiate connection
                }
            }
            break;

        case ESocketsCmdDisconnect:
            iSocketsEngine->Disconnect();
            break;
        case ESocketsCmdClear:
            iAppView->ClearTextL();
            break;
        default:
            User::Panic (KPanicSockets, ESocketsBasicUi);
            break;
        }
    }

void CSocketsAppUi::DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane)
    {
    if (aMenuId == R_SOCKETS_MENU)
        {
        // Grey-out 'Connect' menu item if already connected
        aMenuPane->SetItemDimmed(ESocketsCmdConnect, iSocketsEngine->Connected());

        // Grey-out 'Disconnect' menu item if not connected
        aMenuPane->SetItemDimmed(ESocketsCmdDisconnect, !iSocketsEngine->Connected());
        }
    }

TKeyResponse CSocketsAppUi::HandleKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
    {
    TChar theCharacter(aKeyEvent.iCode);
	if ((aType == EEventKey) && 
        (iSocketsEngine->Connected()) && 
        (theCharacter.IsPrint() ||
         theCharacter == EKeyEnter))
        {
        // This key event will end up as 'data' when written to the socket, so use TBuf8
        TBuf8<2> buf;

        // This will 'slice off' the higher order byte, OK for this example
        buf.Append(aKeyEvent.iCode);

        if (theCharacter == EKeyEnter)
            {
            buf.Append(EKeyLineFeed);
            }

        iSocketsEngine->WriteL(buf);
        iAppView->PrintNotify(buf, CEikGlobalTextEditor::EBold);

        return(EKeyWasConsumed);
        }
    
    return(EKeyWasNotConsumed);
    }

