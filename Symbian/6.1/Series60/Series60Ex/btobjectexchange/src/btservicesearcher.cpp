/* Copyright (c) 2002, Nokia. All rights reserved */

#include "BTServiceSearcher.h"
#include "BTServiceSearcher.pan"

CBTServiceSearcher::CBTServiceSearcher(MLog& aLog)
:  iIsDeviceSelectorConnected(EFalse),
   iLog(aLog)
    {
    }

CBTServiceSearcher::~CBTServiceSearcher()
    {
    if (iIsDeviceSelectorConnected)
        {
        iDeviceSelector.CancelNotifier(KDeviceSelectionNotifierUid);
        iDeviceSelector.Close();
        }
    delete iSdpSearchPattern;
    iSdpSearchPattern = NULL;

    delete iAgent;
    iAgent = NULL;
    }

void CBTServiceSearcher::SelectDeviceByDiscoveryL(TRequestStatus& aObserverRequestStatus)
    {
    if (!iIsDeviceSelectorConnected)
        {
        User::LeaveIfError(iDeviceSelector.Connect());
        iIsDeviceSelectorConnected = ETrue;
        }

    //  Request a device selection 
    TBTDeviceSelectionParamsPckg selectionFilter;
    selectionFilter().SetUUID(ServiceClass());

    iDeviceSelector.StartNotifierAndGetResponse(
        aObserverRequestStatus, 
        KDeviceSelectionNotifierUid, 
        selectionFilter, 
        iResponse);
    }


void CBTServiceSearcher::FindServiceL(TRequestStatus& aObserverRequestStatus)
    {
    if (!iResponse().IsValidBDAddr())
        {
        User::Leave(KErrNotFound);
        }
    iHasFoundService = EFalse;

    // delete any existing agent and search pattern
    delete iSdpSearchPattern;
    iSdpSearchPattern = NULL;

    delete iAgent;
    iAgent = NULL;

    iAgent = CSdpAgent::NewL(*this, BTDevAddr());

    iSdpSearchPattern = CSdpSearchPattern::NewL();
   
    iSdpSearchPattern->AddL(ServiceClass()); 
    // return code is the position in the list that the UUID is inserted at 
    // and is intentionally ignored
  
    iAgent->SetRecordFilterL(*iSdpSearchPattern);

    iStatusObserver = &aObserverRequestStatus;

    iAgent->NextRecordRequestL();
    }

void CBTServiceSearcher::NextRecordRequestComplete(
    TInt aError, 
    TSdpServRecordHandle aHandle, 
    TInt aTotalRecordsCount)
    {
    TRAPD(error,
        NextRecordRequestCompleteL(aError, aHandle, aTotalRecordsCount);
    );

    if (error != KErrNone) 
        {
        Panic(EBTServiceSearcherNextRecordRequestComplete);
        }
    }

void CBTServiceSearcher::NextRecordRequestCompleteL(
    TInt aError, 
    TSdpServRecordHandle aHandle, 
    TInt aTotalRecordsCount
)
    {
    if (aError == KErrEof)
        {
        Finished();
        return;
        }

    if (aError != KErrNone)
        {
        iLog.LogL(_L("NRRC ERR"), aError);
        Finished(aError);
        return;
        }

    if (aTotalRecordsCount == 0)
        {
        iLog.LogL(_L("NRRC No records"));
        Finished(KErrNotFound);
        return;
        }

    //  Request its attributes
    iAgent->AttributeRequestL(aHandle, KSdpAttrIdProtocolDescriptorList);
    }

void CBTServiceSearcher::AttributeRequestResult(
    TSdpServRecordHandle aHandle, 
    TSdpAttributeID aAttrID, 
    CSdpAttrValue* aAttrValue
)
    {
    TRAPD(error,
        AttributeRequestResultL(aHandle, aAttrID, aAttrValue);
    );
    if (error != KErrNone)
        {
        Panic(EBTServiceSearcherAttributeRequestResult);
        }

    // Ownership has been transferred
    delete aAttrValue;
    }

void CBTServiceSearcher::AttributeRequestResultL(
    TSdpServRecordHandle /*aHandle*/, 
    TSdpAttributeID aAttrID, 
    CSdpAttrValue* aAttrValue
)
    {
    ASSERT(aAttrID == KSdpAttrIdProtocolDescriptorList);

    TSdpAttributeParser parser(ProtocolList(), *this);

    // Validate the attribute value, and extract the RFCOMM channel
    aAttrValue->AcceptVisitorL(parser);

    if (parser.HasFinished())
        {
        // Found a suitable record so change state
        iHasFoundService = ETrue;
        }
    }

void CBTServiceSearcher::AttributeRequestComplete(TSdpServRecordHandle aHandle, TInt aError)
    {
    TRAPD(error,
        AttributeRequestCompleteL(aHandle, aError);
    );
    if (error != KErrNone)
        {
        Panic(EBTServiceSearcherAttributeRequestComplete);
        }
    }

void CBTServiceSearcher::AttributeRequestCompleteL(TSdpServRecordHandle /*aHandle*/, TInt aError)
    {
    if (aError != KErrNone)
        {
        iLog.LogL(_L("Can't get attribute "), aError);
        }
    else if (!HasFinishedSearching())
        {
        // have not found a suitable record so request another
        iAgent->NextRecordRequestL();
        }
    else
        {
        iLog.LogL(_L("AttrReqCom"));
        Finished();
        }
    }

void CBTServiceSearcher::Finished(TInt aError /* default = KErrNone */)
    {
    if (aError == KErrNone && !HasFoundService())
        {
        aError = KErrNotFound;
        }
    User::RequestComplete(iStatusObserver, aError);
    }

TBool CBTServiceSearcher::HasFinishedSearching() const
    {
    return EFalse;
    }

const TBTDevAddr& CBTServiceSearcher::BTDevAddr()
    {
    return iResponse().BDAddr();
    }

const TBTDeviceResponseParams& CBTServiceSearcher::ResponseParams()
    {
    return iResponse();
    }

TBool CBTServiceSearcher::HasFoundService() const
    {
    return iHasFoundService;
    }
