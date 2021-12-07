/* Copyright (c) 2002, Nokia. All rights reserved */

#include <eiklabel.h>
#include <bt_sock.h>

#include "BTHCIUtility.h"
#include "BTHCI.pan"
#include "Reporter.h"

const TInt KInfoBufSize = 40;

CBTHCIUtility* CBTHCIUtility::NewL(MReporter& aReporter)
    {
    CBTHCIUtility* self = CBTHCIUtility::NewLC(aReporter);
    CleanupStack::Pop(self);
    return self;
    }

CBTHCIUtility* CBTHCIUtility::NewLC(MReporter& aReporter)
    {
    CBTHCIUtility* self = new (ELeave) CBTHCIUtility(aReporter);
    self->ConstructL();
    CleanupStack::PushL(self);
    return self;
    }

void CBTHCIUtility::ConstructL()
    {
    iInfoBuf = HBufC::NewL(KInfoBufSize);

    User::LeaveIfError(iSocketServer.Connect());

    TProtocolDesc protocolInfo;

    User::LeaveIfError(iSocketServer.FindProtocol(_L("BTLinkManager"), protocolInfo));

    User::LeaveIfError(iSock.Open(iSocketServer, KBTAddrFamily, KSockSeqPacket, KL2CAP));
    }

CBTHCIUtility::CBTHCIUtility(MReporter& aReporter)
:   CActive(CActive::EPriorityStandard),  
    iState(EIdle),
    iReporter(aReporter)
    {
        CActiveScheduler::Add(this);
    }

CBTHCIUtility::~CBTHCIUtility()
    {
    delete iInfoBuf;
    iInfoBuf = NULL;

    Cancel();

    iSock.Close();
    iSocketServer.Close();
    }

void CBTHCIUtility::LocalVersionHCICommand()
    {
    if (IsActive())
        {
        Panic(EBTHCIAlreadyActive);
        }

    iState = EGettingLocalVersion;
    iSock.Ioctl(KHCILocalVersionIoctl, iStatus, &iLocalVersionBuf, KSolBtHCI);
    SetActive();
    }

void CBTHCIUtility::LocalFeaturesHCICommand()
    {
    if (IsActive())
        {
        Panic(EBTHCIAlreadyActive);
        }

    iState = EGettingLocalFeatures;
    iSock.Ioctl(KHCILocalFeaturesIoctl, iStatus, &iLocalFeaturesBuf, KSolBtHCI);
    SetActive();
    }

void CBTHCIUtility::LocalAddressHCICommand()
    {
    if (IsActive())
        {
        Panic(EBTHCIAlreadyActive);
        }

    iState = EGettingLocalAddress;
    iSock.Ioctl(KHCILocalAddressIoctl, iStatus, &iDevAddrPckg, KSolBtHCI);
    SetActive();
    }

void CBTHCIUtility::DoCancel()
    {
    iSock.CancelAll();
    }

void CBTHCIUtility::RunL()
    {
    User::LeaveIfError(iStatus.Int());

    TPtr buf = iInfoBuf->Des();

    switch (iState)
        {
        case EGettingLocalVersion:
            iReporter.PrintLine(_L("Local Version:"));

            buf.Format(_L("HCI Version: %u"), iLocalVersionBuf().iHCIVersion);
            iReporter.PrintLine(buf);

            buf.Format(_L("HCI Revision: %u"), iLocalVersionBuf().iHCIRevision);
            iReporter.PrintLine(buf);

            buf.Format(_L("LMP Version: %u"), iLocalVersionBuf().iLMPVersion);
            iReporter.PrintLine(buf);

            buf.Format(_L("LMP Subversion: %u"), iLocalVersionBuf().iLMPSubversion);
            iReporter.PrintLine(buf);

            buf.Format(_L("Manufacturer: %u"), iLocalVersionBuf().iManufacturerName);
            iReporter.PrintLine(buf);
            break;

        case EGettingLocalFeatures:
            iReporter.PrintLine(_L("Local Features:"));
            buf.Format(_L("%x"), iLocalFeaturesBuf());
            iReporter.PrintLine(buf);
            break;

        case EGettingLocalAddress:
            iReporter.PrintLine(_L("Local Address:"));
            iDevAddrPckg().GetReadable(buf);
            iReporter.PrintLine(buf);
            break;

        case EIdle:
        default:
            Panic(EBTHCIInvalidState);
            break;
        }

    iState = EIdle;
    }
