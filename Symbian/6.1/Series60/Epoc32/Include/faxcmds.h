// FAXCMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined (__FAXCMDS_H__)
#define __FAXCMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

// will be in <msvstd.hrh> in next release
#define KMtmFirstFreeMtmFunctionId 			0x100000 // MTM can use any value above this

enum TFaxCmds {
	KFaxMTMDialAndReceive = KMtmFirstFreeMtmFunctionId,
	KFaxMTMImmediateTransmitCopy,
	KFaxMTMImmediateReceive,
	KFaxMTMRingAndTransmitCopy,
	KFaxMTMImmediateTransmitMove,
	KFaxMTMRingAndTransmitMove,
	KFaxMtmPolledReceive,
	KFaxMTMRenderToFile,
	KFaxMTMScheduleCopy,
	KFaxMTMScheduleMove,
	KFaxMTMDeleteSchedule,
	KFaxMTMCheckSchedule,
	KFaxMTMSendScheduledCopy,
	KFaxMTMSendScheduledMove,
	KFaxMTMWatcherReceive
};

#endif