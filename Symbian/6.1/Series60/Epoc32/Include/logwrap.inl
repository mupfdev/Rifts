// LOGWRAP.INL
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

//**********************************
// CLogEvent
//**********************************

inline TLogId CLogEvent::Id() const
	{
	return iId;
	}

inline void CLogEvent::SetId(TLogId aId)
	{
	iId = aId;
	}

inline TUid CLogEvent::EventType() const
	{
	return iEventType;
	}

inline void CLogEvent::SetEventType(TUid aId)
	{
	iEventType = aId;
	}

inline const TDesC& CLogEvent::RemoteParty() const
	{
	return *iRemoteParty;
	}

inline void CLogEvent::SetRemoteParty(const TDesC& aRemote)
	{
	TPtr ptr(iRemoteParty->Des());
	iRemoteParty->Des().Copy(aRemote.Ptr(), Min(aRemote.Length(), ptr.MaxLength()));
	}

inline const TDesC& CLogEvent::Direction() const
	{
	return *iDirection;
	}

inline void CLogEvent::SetDirection(const TDesC& aDirection)
	{
	TPtr ptr(iDirection->Des());
	ptr.Copy(aDirection.Ptr(), Min(aDirection.Length(), ptr.MaxLength()));
	}

inline const TTime& CLogEvent::Time() const
	{
	return iTime;
	}

inline void CLogEvent::SetTime(const TTime& aTime)
	{
	iTime = aTime;
	}

inline TLogDurationType CLogEvent::DurationType() const
	{
	return iDurationType;
	}

inline void CLogEvent::SetDurationType(TLogDurationType aDurationType)
	{
	iDurationType = aDurationType;
	}

inline TLogDuration CLogEvent::Duration() const
	{
	return iDuration;
	}

inline void CLogEvent::SetDuration(TLogDuration aDuration)
	{
	iDuration = aDuration;
	}

inline const TDesC& CLogEvent::Status() const
	{
	return *iStatus;
	}

inline void CLogEvent::SetStatus(const TDesC& aStatus)
	{
	TPtr ptr(iStatus->Des());
	ptr.Copy(aStatus.Ptr(), Min(aStatus.Length(), ptr.MaxLength()));
	}

inline const TDesC& CLogEvent::Subject() const
	{
	return *iSubject;
	}

inline void CLogEvent::SetSubject(const TDesC& aSubject)
	{
	TPtr ptr(iSubject->Des());
	ptr.Copy(aSubject.Ptr(), Min(aSubject.Length(), ptr.MaxLength()));
	}

inline const TDesC& CLogEvent::Number() const
	{
	return *iNumber;
	}

inline void CLogEvent::SetNumber(const TDesC& aNumber)
	{
	TPtr ptr(iNumber->Des());
	ptr.Copy(aNumber.Ptr(), Min(aNumber.Length(), ptr.MaxLength()));
	}

inline TContactItemId CLogEvent::Contact() const
	{
	return iContact;
	}

inline void CLogEvent::SetContact(TContactItemId aContact)
	{
	iContact = aContact;
	}

inline TLogLink CLogEvent::Link() const
	{
	return iLink;
	}

inline void CLogEvent::SetLink(TLogLink aLink)
	{
	iLink = aLink;
	}

inline const TDesC& CLogEvent::Description() const
	{
	return *iDescription;
	}

inline void CLogEvent::SetDescription(const TDesC& aDescription)
	{
	TPtr ptr(iDescription->Des());
	ptr.Copy(aDescription.Ptr(), Min(aDescription.Length(), ptr.MaxLength()));
	}

inline const TDesC8& CLogEvent::Data() const
	{
	if (iData)
		return *iData;
	else
		return KNullDesC8;
	}

inline TLogFlags CLogEvent::Flags() const
	{
	return iFlags;
	}

inline void CLogEvent::SetFlags(TLogFlags aFlags)
	{
	__ASSERT_DEBUG(aFlags <= KLogFlagsMask, User::Invariant());
	iFlags = (TLogFlags)(iFlags | aFlags);
	}

inline void CLogEvent::ClearFlags(TLogFlags aFlags)
	{
	__ASSERT_DEBUG(aFlags <= KLogFlagsMask, User::Invariant());
	iFlags = (TLogFlags)(iFlags & ~aFlags);
	}

//**********************************
// CLogBase
//**********************************

inline const RResourceFile& CLogBase::ResourceFile() const
	{
	return iResourceFile;
	}

inline CLogBase& CLogWrapper::Log()
	{
	return *iBase;
	}
