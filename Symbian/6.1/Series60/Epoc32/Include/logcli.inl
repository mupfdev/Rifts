// LOGCLI.INL
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

//**********************************
// CLogEventType
//**********************************

inline TUid CLogEventType::Uid() const
	{
	return iUid;
	}

inline void CLogEventType::SetUid(TUid aUid)
	{
	iUid = aUid;
	}

inline const TDesC& CLogEventType::Description() const
	{
	return *iDescription;
	}

inline void CLogEventType::SetDescription(const TDesC& aDescription)
	{
	iDescription->Des().Copy(aDescription);
	}

inline TBool CLogEventType::LoggingEnabled() const
	{
	return iLoggingEnabled;
	}

inline void CLogEventType::SetLoggingEnabled(TBool aEnable)
	{
	iLoggingEnabled = aEnable;
	}

//**********************************
// CLogFilter
//**********************************

inline TUid CLogFilter::EventType() const
	{
	return iEventType;
	}

inline void CLogFilter::SetEventType(TUid aType)
	{
	iEventType = aType;
	}

inline const TDesC& CLogFilter::RemoteParty() const
	{
	return *iRemoteParty;
	}

inline void CLogFilter::SetRemoteParty(const TDesC& aRemote)
	{
	iRemoteParty->Des().Copy(aRemote);
	}

inline const TDesC& CLogFilter::Direction() const
	{
	return *iDirection;
	}

inline void CLogFilter::SetDirection(const TDesC& aDirection)
	{
	iDirection->Des().Copy(aDirection);
	}

inline TLogDurationType CLogFilter::DurationType() const
	{
	return iDurationType;
	}

inline void CLogFilter::SetDurationType(TLogDurationType aType)
	{
	iDurationType = aType;
	}

inline const TDesC& CLogFilter::Status() const
	{
	return *iStatus;
	}

inline void CLogFilter::SetStatus(const TDesC& aStatus)
	{
	iStatus->Des().Copy(aStatus);
	}

inline TContactItemId CLogFilter::Contact() const
	{
	return iContact;
	}

inline void CLogFilter::SetContact(TContactItemId aContact)
	{
	iContact = aContact;
	}

inline const TDesC& CLogFilter::Number() const
	{
	return *iNumber;
	}

inline void CLogFilter::SetNumber(const TDesC& aNumber)
	{
	iNumber->Des().Copy(aNumber);
	}

inline TUint32 CLogFilter::NullFields() const
	{
	return iNullFields;
	}

inline void CLogFilter::SetNullFields(TUint32 aFields)
	{
	iNullFields = aFields;
	}

inline TLogFlags CLogFilter::Flags() const
	{
	return iFlags;
	}

inline void CLogFilter::SetFlags(TLogFlags aFlags)
	{
	__ASSERT_DEBUG(aFlags <= KLogFlagsMask, User::Invariant());
	iFlags = (TLogFlags)(iFlags | aFlags);
	}

inline void CLogFilter::ClearFlags(TLogFlags aFlags)
	{
	__ASSERT_DEBUG(aFlags <= KLogFlagsMask, User::Invariant());
	iFlags = (TLogFlags)(iFlags & ~aFlags);
	}
