/////////////////////////////////////////////////////////////////////////////
//
//	SCHEDULE_SEND_PANIC.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef SCHEDULE_SEND_PANIC_H_
#define SCHEDULE_SEND_PANIC_H_

enum TScheduleSendPanic
	{
	EMessageSelectionEmpty,
	EMessagesNotSameTime,
	EMessagesNotSameMtm,
	EMessagesNotSameOffPeak,
	EMessageNotScheduled,
	EScheduleNotCreated,
	ECannotScheduleInPast,
	EAttemptIntervalArrayEmpty,
	ETaskIdMsvIdMismatch,
	EInvalidAttemptInterval,
	EInvalidValidityPeriod,
	EInvalidMaxAttempts,
	EInvalidHour,
	EInvalidMinute,
	EInvalidSecond,
	EStartTimeTooEarly,
	EProgrammingBug,
	EVariableIntervalsNotFound,
	ELongIntervalOutOfRange,
	EShortIntervalOutOfRange,
	EVariableIntervalOutOfRange,
	EMaxRetriesMustBePositive,
	ERetryIntervalMustByPositive,
	EOffPeakTimesEmpty,
	EServerEntryNotSetToCorrectEntry,
	ELatencyOutOfRange,
	ESysAgentConditionOutOfSync,
	ESysAgentConditionTypeNotSupported,
	EReportNotNull
	};

GLREF_C void gPanic(TScheduleSendPanic aPanic);

#endif