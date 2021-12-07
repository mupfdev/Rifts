// PLPLINK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPLINK_H__)
#define __PLPLINK_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__C32COMM_H__)
#include <c32comm.h>
#endif

#include <plpsize.h>

//
const TInt KMaxLinkPduSize = PLP_LINK_PDU_SIZE;
//
enum TPlpLinkConnectMode 
    { 
    EAcceptor, EInitiator
    };
//
class TPlpLinkTimerValues
    {
public:
    TUint iMinRtt;
    TUint iMaxRtt;
    TUint iDefaultSrtt;
    TUint iDefaultVrtt;
    };
//
class TPlpLinkOptions
    {

public:
    TPlpLinkTimerValues iTimerValues;
    TUint iCfgFlags;
    TUint iInactivityTimeout;
    TUint iWriteTimeout;
    TUint iMaxConnectRetries;
    TUint iMaxDataRetries;
    TUint iAbortLinger;
    TUint iExtTransmitWindow;
    TUint iExtReceiveWindow;
    TUint iSendFlowLowWater;
    TUint iSendFlowHighWater;
    TPlpLinkConnectMode iConnectMode;
	};

//
class TPlpHwConfig 
    {
public:
    TInt iBufferSize;
    TBps iRate;
    };

class TPlpLinkConfig : public TPlpLinkOptions, public TPlpHwConfig 
    {
    };
//
class TPlpLinkInfo
    {

public:
    enum TPeerType { ENoConnection, ENormal, EExtended };
    TUint iBrokenFrameTotal;
    TUint iRetransTotal;
    TPeerType iPeerType;
    };
//
const TUint KPlpLinkCfgNone						= 0x00000000;
const TUint KPlpLinkCfgExtSendMagicNumber		= 0x00000001;
const TUint KPlpLinkCfgExtUseMagicNumber		= 0x00000002;
const TUint KPlpLinkCfgExtUseWindowing			= 0x00000004;
const TUint KPlpLinkCfgUseBaudDefaultTimers		= 0x00000008;

const TUint KPlpLinkCfgUse						= KPlpLinkCfgExtSendMagicNumber | KPlpLinkCfgExtUseMagicNumber | KPlpLinkCfgExtUseWindowing | KPlpLinkCfgUseBaudDefaultTimers;
const TUint KPlpLinkCfgAll						= KPlpLinkCfgExtSendMagicNumber | KPlpLinkCfgExtUseMagicNumber | KPlpLinkCfgExtUseWindowing | KPlpLinkCfgUseBaudDefaultTimers;	// All used bits.

//

const TUint KPlpHwCfgNone						= 0x00000000;
const TUint KPlpHwCfgCtsRtsFlowControl			= 0x00100000;
const TUint KPlpHwCfgXonXoffFlowControl			= 0x00200000;
const TUint KPlpHwCfgMonitorDsrLine				= 0x01000000;
const TUint KPlpHwCfgMonitorCtsLine				= 0x02000000;
const TUint KPlpHwCfgMonitorByPolling			= 0x04000000;
const TUint KPlpHwCfgCheckDisconnectByPolling	= 0x10000000;

const TUint KPlpHwCfgMonitorLine				= KPlpHwCfgMonitorDsrLine | KPlpHwCfgMonitorCtsLine;

// const TUint KPlpHwCfgUse						= KPlpHwCfgCtsRtsFlowControl | KPlpHwCfgMonitorDsrLine; // Original
const TUint KPlpHwCfgUse						= KPlpHwCfgCheckDisconnectByPolling;

const TUint KPlpHwCfgAll						= KPlpHwCfgCtsRtsFlowControl | KPlpHwCfgXonXoffFlowControl| KPlpHwCfgMonitorDsrLine| KPlpHwCfgMonitorCtsLine | KPlpHwCfgMonitorByPolling | KPlpHwCfgCheckDisconnectByPolling; // All used bits.

//

#endif __PLPLINK_H__
