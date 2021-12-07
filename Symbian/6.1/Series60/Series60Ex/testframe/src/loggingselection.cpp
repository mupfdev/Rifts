/* Copyright (c) 2001, Nokia. All rights reserved */

#include "testlogger.h"

MTestLogger::TLoggingSelection::TLoggingSelection()
:	iFile(EFalse),
	iScreen(EFalse)
	{
	//	Implementation not required
	}


void MTestLogger::TLoggingSelection::TurnOn(TLogType aType)
	{
	switch(aType)
		{
	case ELogTypeFile:
		iFile = ETrue;
		break;
	case ELogTypeScreen:
		iScreen = ETrue;
		break;
	default:
		ASSERT(EFalse);
		}
	}


void MTestLogger::TLoggingSelection::TurnOff(TLogType aType)
	{
	switch(aType)
		{
	case ELogTypeFile:
		iFile = EFalse;
		break;
	case ELogTypeScreen:
		iScreen = EFalse;
		break;
	default:
		ASSERT(EFalse);
		}
	}


TBool MTestLogger::TLoggingSelection::Logging(TLogType aType) const
	{
	switch(aType)
		{
	case ELogTypeFile:
		return iFile;
	case ELogTypeScreen:
		return iScreen;
	default:
		ASSERT(EFalse);
		return EFalse;
		}
	}
