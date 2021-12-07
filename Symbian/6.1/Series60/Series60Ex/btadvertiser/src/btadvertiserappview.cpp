/* Copyright (c) 2002, Nokia. All rights reserved */

#include <bt_sock.h>
#include "BTAdvertiserAppView.h"
#include "BTAdvertiser.pan"

// See entry for SerialPort in table 4.4 "Service Classes"
// at the url http://www.bluetooth.org/assigned-numbers/sdp.htm
static const TInt KSerialClassID = 0x1101;

// UID for application
static const TInt KUidBTAdvertiserAppValue = {0x10005B8C};

// Channel
static const TInt KChannel = 1;

_LIT(KServiceName, "Serial");
_LIT(KServiceDescription, "Serial transfer");

// Standard Symbian OS construction sequence
CBTAdvertiserAppView* CBTAdvertiserAppView::NewL(const TRect& aRect)
    {
    CBTAdvertiserAppView* self = CBTAdvertiserAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CBTAdvertiserAppView* CBTAdvertiserAppView::NewLC(const TRect& aRect)
    {
    CBTAdvertiserAppView* self = new (ELeave) CBTAdvertiserAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CBTAdvertiserAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CBTAdvertiserAppView::CBTAdvertiserAppView()
:   iRecord(0), iIsConnected(EFalse)
    {
    // Add any construction code that can not leave here
    }


CBTAdvertiserAppView::~CBTAdvertiserAppView()
    {
    if (IsAdvertising()) 
        {
        StopAdvertiser();
        }

    iSdpDatabase.Close();
    iSdpSession.Close();
    }

void CBTAdvertiserAppView::Draw(const TRect& /*aRect*/) const
    {
    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());
    }

void CBTAdvertiserAppView::StartAdvertiserL()
    {
    if (!iIsConnected)
        {
        if (iSdpSession.Connect() != KErrNone)
            {
            Panic(EBTAdvertiserFailedToOpenSession);
            }
        if (iSdpDatabase.Open(iSdpSession) != KErrNone)
            {
            Panic(EBTAdvertiserFailedToOpenDatabase);
            }
        iIsConnected = ETrue;
        }
    
    // Create a record of the correct service class
    iSdpDatabase.CreateServiceRecordL(KSerialClassID, iRecord); // @anchor CreateServiceRecordL

    // Add a Protocol to the record
    CSdpAttrValueDES* protocolDescriptorList = CSdpAttrValueDES::NewDESL(NULL);
    CleanupStack::PushL(protocolDescriptorList);
 
    protocolDescriptorList
    ->StartListL()   //  List of protocols required for this method
        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KL2CAP)
        ->EndListL()

        ->BuildDESL()
        ->StartListL()
            ->BuildUUIDL(KRFCOMM)
            ->BuildUintL(TBuf8<1>(KChannel))
        ->EndListL()
    ->EndListL();

    iSdpDatabase.UpdateAttributeL(iRecord, KSdpAttrIdProtocolDescriptorList, *protocolDescriptorList);

    CleanupStack::PopAndDestroy(protocolDescriptorList);

    // Add a Unique ID to the record 
    iSdpDatabase.UpdateAttributeL(iRecord, 
                                  KSdpAttrIdServiceID, 
                                  KUidBTAdvertiserAppValue);

    // Add a name to the record
    iSdpDatabase.UpdateAttributeL(iRecord, 
                                  KSdpAttrIdBasePrimaryLanguage + KSdpAttrIdOffsetServiceName, 
                                  KServiceName);

    // Add a description to the record
    iSdpDatabase.UpdateAttributeL(iRecord, 
                                  KSdpAttrIdBasePrimaryLanguage + KSdpAttrIdOffsetServiceDescription,
                                  KServiceDescription);
    }

void CBTAdvertiserAppView::StopAdvertiser()
    {
    TRAPD(err,StopAdvertiserL());
    if (err != KErrNone)
        {
        Panic(EBTAdvertiserFailedToRemoveRecord);
        }
    }

void CBTAdvertiserAppView::StopAdvertiserL()
    {
    iSdpDatabase.DeleteRecordL(iRecord);
    iRecord = 0;
    }

TBool CBTAdvertiserAppView::IsAdvertising()
    {
    return iRecord != 0 ? ETrue : EFalse;
    }
