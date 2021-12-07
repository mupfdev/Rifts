/* Copyright (c) 2002, Nokia. All rights reserved */

#include <bt_sock.h>
#include "MessageServiceAdvertiser.h"
#include "MessageProtocolConstants.h"

CMessageServiceAdvertiser* CMessageServiceAdvertiser::NewL()
    {
    CMessageServiceAdvertiser* self = CMessageServiceAdvertiser::NewLC();
    CleanupStack::Pop(self);
    return self;
    }

CMessageServiceAdvertiser* CMessageServiceAdvertiser::NewLC()
    {
    CMessageServiceAdvertiser* self = new (ELeave) CMessageServiceAdvertiser();
    CleanupStack::PushL(self);
    return self;
    }

CMessageServiceAdvertiser::CMessageServiceAdvertiser()
    {
    // no implementation required
    }

CMessageServiceAdvertiser::~CMessageServiceAdvertiser()
    {
    // no implementation required
    }

void CMessageServiceAdvertiser::BuildProtocolDescriptionL(CSdpAttrValueDES* aProtocolDescriptor, TInt aPort)
    {
    TBuf8<1> channel;
    channel.Append((TChar)aPort);

    aProtocolDescriptor
    ->StartListL()
        ->BuildDESL()
        ->StartListL()   //  Details of lowest level protocol
            ->BuildUUIDL(KL2CAP)
        ->EndListL()

        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KRFCOMM)
            ->BuildUintL(channel)
        ->EndListL()
    ->EndListL();
    }

const TDesC& CMessageServiceAdvertiser::ServiceName()
    {
    return KServiceName;
    }

const TDesC& CMessageServiceAdvertiser::ServiceDescription()
    {
    return KServiceDescription;
    }

const TInt CMessageServiceAdvertiser::ServiceClass()
    {
    return KServiceClass;
    }
