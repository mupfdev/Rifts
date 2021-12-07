/* Copyright (c) 2002, Nokia. All rights reserved */

#include <eiklabel.h>
#include <bt_sock.h>

#include "BTDiscoverer.h"
#include "BTAttributeValueLister.h"
#include "BTDiscovery.pan"

CBTDiscoverer* CBTDiscoverer::NewL(MReporter& aReporter)
    {
    CBTDiscoverer* self = CBTDiscoverer::NewLC(aReporter);
    CleanupStack::Pop(self);
    return self;
    }

CBTDiscoverer* CBTDiscoverer::NewLC(MReporter& aReporter)
    {
    CBTDiscoverer* self = new (ELeave) CBTDiscoverer(aReporter);
    self->ConstructL();
    CleanupStack::PushL(self);
    return self;
    }

void CBTDiscoverer::ConstructL()
    {
    iSdpSearchPattern = CSdpSearchPattern::NewL();
    iSdpSearchPattern->AddL(KL2CAP);

    iMatchList = CSdpAttrIdMatchList::NewL();
    iMatchList->AddL(TAttrRange(0x0000, 0xFFFF)); // get them all

    iAgent = NULL;
    }

CBTDiscoverer::CBTDiscoverer(MReporter& aReporter)
:   iReporter(aReporter),  
    iHasPrintedRecordNumber(EFalse), 
    iHasPrintedHandle(EFalse)
    {
    }

CBTDiscoverer::~CBTDiscoverer()
    {
    delete iAgent;
    iAgent = NULL;

    delete iMatchList;
    iMatchList = NULL;

    delete iSdpSearchPattern;
    iSdpSearchPattern = NULL;
    }

TBool CBTDiscoverer::SelectDeviceL(TBTDeviceResponseParamsPckg& aResponse)
    {
    iHasPrintedRecordNumber = EFalse;
    TBool success = EFalse;
    
    RNotifier not;
    User::LeaveIfError(not.Connect());
  
    TBTDeviceSelectionParamsPckg selectionFilter;

    TRequestStatus status;
    not.StartNotifierAndGetResponse(
        status,
        KDeviceSelectionNotifierUid,
        selectionFilter,
        aResponse
    );

    User::WaitForRequest(status);

    if (status.Int() == KErrNone)
        {
        if (aResponse().IsValidDeviceName())
            {
            success = ETrue;
            }
        else
            {
            iReporter.Error(_L("Failed to connect"));
            }
        }
    else
        {
        iReporter.Error(_L("No device selected"));
        }

    not.CancelNotifier(KDeviceSelectionNotifierUid);
    not.Close();

    return success;
    }

void CBTDiscoverer::ListServicesL(const TBTDevAddr& aAddress)
    {
    delete iAgent;

    iAgent = NULL;
    iAgent = CSdpAgent::NewL(*this, aAddress);

    iAgent->SetRecordFilterL(*iSdpSearchPattern);
    iAgent->NextRecordRequestL();
    }

void CBTDiscoverer::NextRecordRequestComplete(TInt aError, TSdpServRecordHandle aHandle, TInt aTotalRecordsCount)
    {
    if (aError == KErrEof)
        {
        iReporter.PrintLine(_L("-- Finished --"));
        }
    else if (aError != KErrNone)
        {
        PrintSDPError(aError);
        iReporter.PrintLine(_L("-- Record End --"));
        }
    else if (aTotalRecordsCount)
        {
        if (! iHasPrintedRecordNumber)
            {
            TBuf<64> buffer;
            buffer.Format(_L("%d records found"), aTotalRecordsCount);
            iReporter.PrintLine(buffer);
            iHasPrintedRecordNumber = ETrue;
            }
        iReporter.PrintLine(_L("-- Record Start --"));

        TRAPD(err, iAgent->AttributeRequestL(aHandle, *iMatchList));
        if (err != KErrNone)
            {
            Panic(EBTDiscoveryAttributeRequest);
            }
        }
    else
        {
        iReporter.PrintLine(KNullDesC);
        iReporter.PrintLine(_L("-- Finished --"));
        }
    }


void CBTDiscoverer::AttributeRequestResult(
    TSdpServRecordHandle aHandle, 
    TSdpAttributeID aAttrID, 
    CSdpAttrValue* aAttrValue
)
    {
    if (! iHasPrintedHandle)
        {
        TBuf<40> handle;
        handle.Append(_L("Handle: 0x"));
        handle.AppendNumUC(static_cast<TUint>(aHandle), EHex);
        iHasPrintedHandle = ETrue;
        iReporter.PrintLine(handle);
        }
    //  Create a text value to identify the record & field
    TBuf<40> attrIDBuffer;
    attrIDBuffer.Append(_L("Attr Id: 0x"));
    attrIDBuffer.AppendNumUC(static_cast<TUint>(aAttrID), EHex);
    iReporter.PrintLine(attrIDBuffer);
    //  Create a text value of the AttributeValue
    TBTAttributeValueLister lister(iReporter);
    
    TRAPD(err,aAttrValue->AcceptVisitorL(lister));
    if (err != KErrNone)
        {
        Panic(EBTDiscoveryAttributeAcceptVisitor);
        }

    // Ownership has been transferred
    delete aAttrValue;
    }

void CBTDiscoverer::AttributeRequestComplete(TSdpServRecordHandle /*aHandle*/, TInt aError)
    {
    if (aError == KErrEof)
        {
        iReporter.PrintLine(_L("-- Finished --"));
        }
    else if (aError != KErrNone)
        {
        PrintSDPError(aError);
        iReporter.PrintLine(_L("-- Finished --"));
        }
    else
        {
        // Finished all attributes of this record - so request the next record
        iHasPrintedHandle = EFalse;
        TRAPD(err, iAgent->NextRecordRequestL());
        if (err != KErrNone)
            {
            Panic(EBTDiscoveryNextRecordRequest);
            }
        }
    }

void CBTDiscoverer::PrintSDPError(TInt aError)
    {
    switch (aError)
        {
        case KErrSdpAlreadyBound:
            iReporter.PrintLine(_L("SDP Error: AlreadyBound"));
            break;
        case KErrSdpPeerError:
            iReporter.PrintLine(_L("SDP Error: PeerError"));
            break;
        case KErrSdpClientNotConnected:
            iReporter.PrintLine(_L("SDP Error: ClientNotConnected"));
            break;
        case KErrSdpUnsupportedVersion:
            iReporter.PrintLine(_L("SDP Error: UnsupportedVersion"));
            break;
        case KErrSdpBadRecordHandle:
            iReporter.PrintLine(_L("SDP Error: BadRecordHandle"));
            break;
        case KErrSdpBadContinuationState:
            iReporter.PrintLine(_L("SDP Error: BadContinuationState"));
            break;
        case KErrSdpServerRejectedRequest:
            iReporter.PrintLine(_L("SDP Error: ServerRejectedRequest"));
            break;
        case KErrSdpBadRequestBufferLength:
            iReporter.PrintLine(_L("SDP Error: BadRequestBufferLength"));
            break;
        case KErrSdpBadResultBufferLength:
            iReporter.PrintLine(_L("SDP Error: BadResultBufferLength"));
            break;
        case KErrSdpBadUUIDLength:
            iReporter.PrintLine(_L("SDP Error: BadUUIDLength"));
            break;
        case KErrSdpBadResultData:
            iReporter.PrintLine(_L("SDP Error: BadResultData"));
            break;
        case KErrSdpDatabaseFull:
            iReporter.PrintLine(_L("SDP Error: DatabaseFull"));
            break;
        default:
            {
            TBuf<32> buffer;
            buffer.Format(_L("SDP Error: %d"), aError);
            iReporter.PrintLine(buffer);
            }
            break;
        }
    }