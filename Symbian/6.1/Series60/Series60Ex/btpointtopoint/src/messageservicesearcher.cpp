/* Copyright (c) 2002, Nokia. All rights reserved */

#include <bt_sock.h>
#include "MessageServiceSearcher.h"
#include "BTServiceSearcher.pan"
#include "MessageProtocolConstants.h"

static const TSdpAttributeParser::SSdpAttributeNode gSerialPortProtocolArray[] = 
    {
        { TSdpAttributeParser::ECheckType, ETypeDES },
            { TSdpAttributeParser::ECheckType, ETypeDES },
                { TSdpAttributeParser::ECheckValue, ETypeUUID, KL2CAP },
            { TSdpAttributeParser::ECheckEnd },
            { TSdpAttributeParser::ECheckType, ETypeDES },
                { TSdpAttributeParser::ECheckValue, ETypeUUID, KRFCOMM },
                { TSdpAttributeParser::EReadValue, ETypeUint, KRfcommChannel },
            { TSdpAttributeParser::ECheckEnd },
        { TSdpAttributeParser::ECheckEnd },
    { TSdpAttributeParser::EFinished }
    };


static const TStaticArrayC<TSdpAttributeParser::SSdpAttributeNode> gSerialPortProtocolList =
    CONSTRUCT_STATIC_ARRAY_C(
        gSerialPortProtocolArray
    );

CMessageServiceSearcher* CMessageServiceSearcher::NewL(MLog& aLog)
    {
    CMessageServiceSearcher* self = CMessageServiceSearcher::NewLC(aLog);
    CleanupStack::Pop(self);
    return self;
    }
    
CMessageServiceSearcher* CMessageServiceSearcher::NewLC(MLog& aLog)
    {
    CMessageServiceSearcher* self = new (ELeave) CMessageServiceSearcher(aLog);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

CMessageServiceSearcher::CMessageServiceSearcher(MLog& aLog)
: CBTServiceSearcher(aLog),
  iServiceClass(KServiceClass),
  iPort(-1)
    {
    }

CMessageServiceSearcher::~CMessageServiceSearcher()
    {
    // no implementation required
    }

void CMessageServiceSearcher::ConstructL()
    {
    // no implementation required
    }

const TUUID& CMessageServiceSearcher::ServiceClass() const
    {
    return iServiceClass;
    }

const TSdpAttributeParser::TSdpAttributeList& CMessageServiceSearcher::ProtocolList() const
    {
    return gSerialPortProtocolList;
    }

void CMessageServiceSearcher::FoundElementL(TInt aKey, CSdpAttrValue& aValue)
    {
    __ASSERT_ALWAYS(aKey == static_cast<TInt>(KRfcommChannel), Panic(EBTServiceSearcherProtocolRead));
    iPort = aValue.Uint();
    }

TInt CMessageServiceSearcher::Port()
    {
    return iPort;
    }
