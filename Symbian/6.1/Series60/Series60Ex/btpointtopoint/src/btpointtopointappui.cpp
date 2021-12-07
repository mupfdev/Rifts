/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include <eikmenup.h>
#include <BtPointToPoint.rsg>
#include "BTPointToPoint.pan"
#include "BTPointToPointAppUi.h"
#include "BTPointToPointAppView.h"
#include "BTPointToPoint.hrh"
#include "MessageServer.h"
#include "MessageClient.h"

// ConstructL is called by the application framework
void CBTPointToPointAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CBTPointToPointAppView::NewL(ClientRect());    

    iAppView->SetMopParent(this);   //  so view can update scroll bars

    AddToStackL(iAppView);

    iServer = CMessageServer::NewL(*iAppView);
    iClient = CMessageClient::NewL(*iAppView);
    }

CBTPointToPointAppUi::CBTPointToPointAppUi()                              
    {
    // no implementation required
    }

CBTPointToPointAppUi::~CBTPointToPointAppUi()
    {
    delete iServer;
    iServer = NULL;

    delete iClient;
    iClient = NULL;

    if (iAppView)
        {
        RemoveFromStack(iAppView);

        delete iAppView;
        iAppView = NULL;
        }
    }

void CBTPointToPointAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (aResourceId == R_BTPOINTTOPOINT_MENU)
        {
        if (iClient->IsConnected())
            {
            aMenuPane->SetItemDimmed(EBTPointToPointStartReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointStopReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointConnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointDisconnect, EFalse);
            aMenuPane->SetItemDimmed(EBTPointToPointSendMessage, (!iClient->IsReadyToSendMessage()));
            }
		else if (iClient->IsConnecting())
            {
            aMenuPane->SetItemDimmed(EBTPointToPointStartReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointStopReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointConnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointDisconnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointSendMessage, ETrue);
            }
		else if (iClient->IsSendingMessage())
            {
            aMenuPane->SetItemDimmed(EBTPointToPointStartReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointStopReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointConnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointDisconnect, EFalse);
            aMenuPane->SetItemDimmed(EBTPointToPointSendMessage, ETrue);
            }
        else if (iServer->IsConnected())
            {
            aMenuPane->SetItemDimmed(EBTPointToPointStartReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointStopReceiver, EFalse);
            aMenuPane->SetItemDimmed(EBTPointToPointConnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointDisconnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointSendMessage, ETrue);
            }
        else // both the server and the client are not connected
            {
            aMenuPane->SetItemDimmed(EBTPointToPointStartReceiver, EFalse);
            aMenuPane->SetItemDimmed(EBTPointToPointStopReceiver, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointConnect, EFalse);
            aMenuPane->SetItemDimmed(EBTPointToPointDisconnect, ETrue);
            aMenuPane->SetItemDimmed(EBTPointToPointSendMessage, ETrue);
            }
        aMenuPane->SetItemDimmed(EBTPointToPointClearList, !iAppView->ContainsEntries());
        }
    }

// handle any menu commands
void CBTPointToPointAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            Exit();
            break;

        case EBTPointToPointStartReceiver:
            iServer->StartL();
            break;

        case EBTPointToPointStopReceiver:
            iServer->StopL();
            break;

        case EBTPointToPointConnect:
            iClient->ConnectL();
            break;

        case EBTPointToPointDisconnect:
            iClient->DisconnectL();
            break;

        case EBTPointToPointSendMessage:
            iClient->SendMessageL();
            break;

        case EBTPointToPointClearList:
            iAppView->ClearMessageListL();
            break;

        default:
            Panic(EBTPointToPointBasicUi);
            break;
        }
    }


