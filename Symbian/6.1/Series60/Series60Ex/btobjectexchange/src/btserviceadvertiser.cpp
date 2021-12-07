/* Copyright (c) 2002, Nokia. All rights reserved */

#include <bt_sock.h>
#include "BTServiceAdvertiser.h"

CBTServiceAdvertiser::CBTServiceAdvertiser()
:   iRecord(0), 
    iIsConnected(EFalse)
    {
    // no implementation required
    }

CBTServiceAdvertiser::~CBTServiceAdvertiser()
    {
    if (IsAdvertising()) 
        {
        TRAPD(err,StopAdvertisingL());
        if (err != KErrNone)
            {
            User::Panic(_L("BTServiceAdvertiser"), err);
            }
        }

    iSdpDatabase.Close();
    iSdpSession.Close();
    }

void CBTServiceAdvertiser::ConnectL()
    {
    if (!iIsConnected)
        {
        User::LeaveIfError(iSdpSession.Connect());
        User::LeaveIfError(iSdpDatabase.Open(iSdpSession));
        iIsConnected = ETrue;
        }
    }

void CBTServiceAdvertiser::StartAdvertisingL(TInt aPort)
    {
    if (IsAdvertising())
        {
        // could be advertising on a different port
        StopAdvertisingL(); 
        }
    if (! iIsConnected)
        {
        ConnectL();
        }
    iSdpDatabase.CreateServiceRecordL(ServiceClass(), iRecord);

    // add a Protocol to the record
    CSdpAttrValueDES* vProtocolDescriptor = CSdpAttrValueDES::NewDESL(NULL);
    CleanupStack::PushL(vProtocolDescriptor);
 
    BuildProtocolDescriptionL(vProtocolDescriptor,aPort);

    iSdpDatabase.UpdateAttributeL(iRecord, KSdpAttrIdProtocolDescriptorList, *vProtocolDescriptor);

    CleanupStack::PopAndDestroy(vProtocolDescriptor);

    // Add a name to the record
    iSdpDatabase.UpdateAttributeL(iRecord, 
                                  KSdpAttrIdBasePrimaryLanguage+KSdpAttrIdOffsetServiceName, 
                                  ServiceName());

    // Add a description to the record
    iSdpDatabase.UpdateAttributeL(iRecord, 
                                  KSdpAttrIdBasePrimaryLanguage+KSdpAttrIdOffsetServiceDescription, 
                                  ServiceDescription());

    }

void CBTServiceAdvertiser::UpdateAvailabilityL(TBool aIsAvailable)
    {
    TUint state;
    if (aIsAvailable)
        {
        state = 0xFF;  //  Fully unused
        }
    else
        {
        state = 0x00;  //  Fully used -> can't connect
        }

    //  Update the availibility attribute field
    iSdpDatabase.UpdateAttributeL(iRecord, KSdpAttrIdServiceAvailability, state);

    //  Mark the record as changed - by increasing its state number (version)
    iSdpDatabase.UpdateAttributeL(iRecord, KSdpAttrIdServiceRecordState, ++iRecordState);
    }

void CBTServiceAdvertiser::StopAdvertisingL()
    {
    if (IsAdvertising())
        {
        iSdpDatabase.DeleteRecordL(iRecord);
        iRecord = 0;
        }
    }

TBool CBTServiceAdvertiser::IsAdvertising()
    {
    return iRecord != 0;
    }

