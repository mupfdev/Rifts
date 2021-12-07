/* Copyright (c) 2002, Nokia. All rights reserved */

#include <bt_sock.h>
#include "ObjectExchangeServiceAdvertiser.h"
#include "ObjectExchangeProtocolConstants.h"

CObjectExchangeServiceAdvertiser* CObjectExchangeServiceAdvertiser::NewL()
    {
    CObjectExchangeServiceAdvertiser* self = CObjectExchangeServiceAdvertiser::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

CObjectExchangeServiceAdvertiser* CObjectExchangeServiceAdvertiser::NewLC()
    {
    CObjectExchangeServiceAdvertiser* self = new (ELeave) CObjectExchangeServiceAdvertiser();
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CObjectExchangeServiceAdvertiser::ConstructL()
    {
    // no implementation required
    }    

CObjectExchangeServiceAdvertiser::CObjectExchangeServiceAdvertiser()
    {
    // no implementation required
    }

CObjectExchangeServiceAdvertiser::~CObjectExchangeServiceAdvertiser()
    {
    // no implementation required
    }

void CObjectExchangeServiceAdvertiser::BuildProtocolDescriptionL(CSdpAttrValueDES* aProtocolDescriptor, TInt aPort)
    {
    TBuf8<1> channel;
    channel.Append((TChar)aPort);

    aProtocolDescriptor
    ->StartListL()   //  List of protocols required for this method
        ->BuildDESL()
        ->StartListL()   //  Details of lowest level protocol
            ->BuildUUIDL(KL2CAP)
        ->EndListL()

        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KRFCOMM)
            ->BuildUintL(channel)
        ->EndListL()

        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KBtProtocolIdOBEX)
        ->EndListL()
    ->EndListL();
    }

const TDesC& CObjectExchangeServiceAdvertiser::ServiceName()
    {
    return KServiceName;
    }

const TDesC& CObjectExchangeServiceAdvertiser::ServiceDescription()
    {
    return KServiceDescription;
    }

const TInt CObjectExchangeServiceAdvertiser::ServiceClass()
    {
    return KServiceClass;
    }
