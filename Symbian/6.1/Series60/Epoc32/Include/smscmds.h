//////////////////////////////////////////////////////////////////////////
//
//	SmsCmds.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
//////////////////////////////////////////////////////////////////////////

#ifndef SMS_CMDS_H_
#define SMS_CMDS_H_

const TInt KMinCommandExpected = 10000;

enum TSmsMtmCommand 
	{
//  Asynchronous commands
	ESmsMtmCommandReadServiceCenter = KMinCommandExpected,
	ESmsMtmCommandWriteServiceCenter,
	ESmsMtmCommandScheduleCopy,
	ESmsMtmCommandScheduleMove,
	ESmsMtmCommandDeleteSchedule,
	ESmsMtmCommandCheckSchedule,
	ESmsMtmCommandSendScheduledCopy,
	ESmsMtmCommandSendScheduledMove,
	ESmsMtmCommandEnumerateSim,
	ESmsMtmCommandCopyFromSim,
	ESmsMtmCommandMoveFromSim,
	ESmsMtmCommandDeleteFromSim,
	ESmsMtmCommandReadSimParams,
	ESmsMtmCommandCopyToSim
	};

#endif
