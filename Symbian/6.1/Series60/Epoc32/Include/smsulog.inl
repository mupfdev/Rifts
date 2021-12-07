// SMSULOG.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

inline TBool CSmsEventLogger::ClientAvailable() const
	{
	return iLogWrapper->ClientAvailable();
	}

inline TInt CSmsEventLogger::GetString(TDes& aString, TInt aId) const
	{
	return iLogWrapper->Log().GetString(aString,aId);
	}

inline CLogEvent& CSmsEventLogger::Event()
	{
	return *iLogEvent;
	}

inline const CLogEvent& CSmsEventLogger::Event() const
	{
	return *iLogEvent;
	}

inline const TLogSmsPduData& CSmsEventLogger::SmsPDUData() const
	{
	return iSmsPDUData;
	}

inline void CSmsEventLogger::GetStringL(TDes& aString, TInt aId) const
	{
	User::LeaveIfError(iLogWrapper->Log().GetString(aString,aId));
	}

