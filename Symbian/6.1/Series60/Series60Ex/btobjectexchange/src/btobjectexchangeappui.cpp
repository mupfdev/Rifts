/* Copyright (c) 2002, Nokia. All rights reserved */

#include <avkon.hrh>
#include <eikmenup.h>
#include <BTObjectExchange.rsg>

#include "BTObjectExchange.pan"
#include "BTObjectExchangeAppUi.h"
#include "BTObjectExchangeAppView.h"
#include "BTObjectExchange.hrh"
#include "ObjectExchangeClient.h"
#include "ObjectExchangeServer.h"

// ConstructL is called by the application framework
void CBTObjectExchangeAppUi::ConstructL()
    {
    BaseConstructL();

    iAppView = CBTObjectExchangeAppView::NewL(ClientRect());    

    iAppView->SetMopParent(this);   //  so view can update scroll bars

    AddToStackL(iAppView);

    iClient = CObjectExchangeClient::NewL(*iAppView);
    iServer = CObjectExchangeServer::NewL(*iAppView);
    }

CBTObjectExchangeAppUi::CBTObjectExchangeAppUi()                              
    {
    // no implementation required
    }

CBTObjectExchangeAppUi::~CBTObjectExchangeAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    delete iClient;
    iClient = NULL;
    delete iServer;
    iServer = NULL;
    }

// handle any menu commands
void CBTObjectExchangeAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EAknSoftkeyExit:
            iClient->StopL();
            iServer->DisconnectL();
            Exit();
            break;

        case EBTObjectExchangeStartServer:
            iServer->StartL();
            break;

        case EBTObjectExchangeStopServer:
            iServer->DisconnectL();
            break;

        case EBTObjectExchangeConnect:
            iClient->ConnectL();
            break;

        case EBTObjectExchangeSendMessage:
            iClient->SendObjectL();
            break;

        case EBTObjectExchangeDisconnect:
            iClient->DisconnectL();
            break;

        case EBTObjectExchangeClearList:
            iAppView->ClearMessageListL();
            break;

        default:
            Panic(EBTObjectExchangeBasicUi);
            break;
        }
    }

void CBTObjectExchangeAppUi::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (aResourceId == R_BTOBJECTEXCHANGE_MENU)
        {
        if (!iClient->IsConnected() && !iServer->IsConnected())
            {
            aMenuPane->SetItemDimmed(EBTObjectExchangeStartServer, EFalse);
            aMenuPane->SetItemDimmed(EBTObjectExchangeStopServer, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeConnect, EFalse);
            aMenuPane->SetItemDimmed(EBTObjectExchangeSendMessage, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeDisconnect, ETrue);
            }
        else if (iServer->IsConnected())
            {
            aMenuPane->SetItemDimmed(EBTObjectExchangeStartServer, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeStopServer, EFalse);
            aMenuPane->SetItemDimmed(EBTObjectExchangeConnect, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeSendMessage, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeDisconnect, ETrue);
            }
        else if (iClient->IsConnected())
            {
            aMenuPane->SetItemDimmed(EBTObjectExchangeStartServer, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeStopServer, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeConnect, ETrue);
            aMenuPane->SetItemDimmed(EBTObjectExchangeSendMessage, iClient->IsBusy());
            aMenuPane->SetItemDimmed(EBTObjectExchangeDisconnect, iClient->IsBusy());
            }
        aMenuPane->SetItemDimmed(EBTObjectExchangeClearList, !iAppView->ContainsEntries());
        }
    }


