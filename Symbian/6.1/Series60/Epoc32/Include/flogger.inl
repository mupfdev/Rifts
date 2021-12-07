// FLOGGER.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLOGGER_INL__
#define __FLOGGER_INL__

#include <flogger.h>

//
// TSignal inline functions
//

inline FLogger::TSignal::TSignal(TRequestStatus& aStatus)
	:iStatus(&aStatus),iId(RThread().Id())
	{
	aStatus=KRequestPending;
	}

inline TPtrC FLogger::TSignal::Command() const
	{
	return TPtrC((const TText*)this,sizeof(*this)/sizeof(TText));
	}

inline TInt FLogger::TSignal::Set(const TDesC& aCommand)
	{
	if (aCommand.Size()!=sizeof(*this))
		return KErrGeneral;
	
	return (Mem::Copy(this,aCommand.Ptr(),sizeof(*this)),KErrNone);
	}

//
// TLogFile inline functions
//

inline TBool TLogFile::Valid() const
	{
	return iValid;
	}

inline TFileName TLogFile::Directory() const
	{
	return iDirectory;
	}
	
inline TFileName TLogFile::Name() const
	{
	return iName;
	}

inline TFileLoggingMode TLogFile::Mode() const
	{
	return iMode;
	}	

inline void TLogFile::SetValid(TBool aValid)
	{
	iValid=aValid;
	}

#endif