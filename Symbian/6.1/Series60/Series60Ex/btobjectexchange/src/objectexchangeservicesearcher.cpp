/* Copyright (c) 2002, Nokia. All rights reserved */

#include <bt_sock.h>
#include "ObjectExchangeServiceSearcher.h"
#include "BTObjectExchange.pan"
#include "ObjectExchangeProtocolConstants.h"

const TSdpAttributeParser::SSdpAttributeNode gObexProtocolListData[] = 
    {
        { TSdpAttributeParser::ECheckType, ETypeDES },
            { TSdpAttributeParser::ECheckType, ETypeDES },
                { TSdpAttributeParser::ECheckValue, ETypeUUID, KL2CAP },
            { TSdpAttributeParser::ECheckEnd },
            { TSdpAttributeParser::ECheckType, ETypeDES },
                { TSdpAttributeParser::ECheckValue, ETypeUUID, KRFCOMM },
                { TSdpAttributeParser::EReadValue, ETypeUint, KRfcommChannel },
            { TSdpAttributeParser::ECheckEnd },
            { TSdpAttributeParser::ECheckType, ETypeDES },
                { TSdpAttributeParser::ECheckValue, ETypeUUID, KBtProtocolIdOBEX },
            { TSdpAttributeParser::ECheckEnd },
        { TSdpAttributeParser::ECheckEnd },
    { TSdpAttributeParser::EFinished }
    };

const TStaticArrayC<TSdpAttributeParser::SSdpAttributeNode> gObexProtocolList =
CONSTRUCT_STATIC_ARRAY_C(
    gObexProtocolListData
);

CObjectExchangeServiceSearcher* CObjectExchangeServiceSearcher::NewL(MLog& aLog)
    {
    CObjectExchangeServiceSearcher* self = CObjectExchangeServiceSearcher::NewLC(aLog);
    CleanupStack::Pop(self);
    return self;
    }
    
CObjectExchangeServiceSearcher* CObjectExchangeServiceSearcher::NewLC(MLog& aLog)
    {
    CObjectExchangeServiceSearcher* self = new (ELeave) CObjectExchangeServiceSearcher(aLog);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CObjectExchangeServiceSearcher::CObjectExchangeServiceSearcher(MLog& aLog)
: CBTServiceSearcher(aLog),
  iServiceClass(KServiceClass),
  iPort(-1)
    {
    }

CObjectExchangeServiceSearcher::~CObjectExchangeServiceSearcher()
    {
    }

void CObjectExchangeServiceSearcher::ConstructL()
    {
    // no implementation required
    }

const TUUID& CObjectExchangeServiceSearcher::ServiceClass() const
    {
    return iServiceClass;
    }

const TSdpAttributeParser::TSdpAttributeList& CObjectExchangeServiceSearcher::ProtocolList() const
    {
    return gObexProtocolList;
    }

void CObjectExchangeServiceSearcher::FoundElementL(TInt aKey, CSdpAttrValue& aValue)
    {
    __ASSERT_ALWAYS(aKey == static_cast<TInt>(KRfcommChannel), Panic(EBTObjectExchangeProtocolRead));
    iPort = aValue.Uint();
    }

TInt CObjectExchangeServiceSearcher::Port()
    {
    return iPort;
    }
