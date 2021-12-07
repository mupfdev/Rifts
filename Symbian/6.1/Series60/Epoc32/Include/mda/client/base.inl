// Mda\Client\Base.inl
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Inline function definitions for Mda\Client\Base

inline TVersion RMdaSession::Version() const
	{
	return TVersion(KMdaServerMajorVersionNumber,KMdaServerMinorVersionNumber,KMdaServerBuildVersionNumber);
	}

inline RMdaObject::RMdaObject()
	{
	iObjectHandle()=EMSvUninitialisedObject;
	}

inline TInt RMdaObject::Handle() const
	{
	return (((RMdaObject*)this)->iObjectHandle());
	}

inline RMdaObject::operator TInt() const
	{
	return (((RMdaObject*)this)->iObjectHandle());
	}

inline const RMdaSession& RMdaObject::Session() const
	{
	return iSession;
	}

inline RMdaTimerFactory::RMdaTimerFactory(RMdaSession& aSession)
	{
	iObjectHandle()=EMSvTimerFactoryObject;
	iSession = aSession;
	}

inline void RMdaTimer::At(TRequestStatus& aStatus,TTime aTime)
	{
	AsynchMessage(EMLbTimerAt,aStatus,(TAny*)aTime.Int64().High(),(TAny*)aTime.Int64().Low());
	}

inline void RMdaTimer::After(TRequestStatus& aStatus,TTimeIntervalMicroSeconds32 aMicroSeconds)
	{
	AsynchMessage(EMLbTimerAfter,aStatus,(TAny*)aMicroSeconds.Int());
	}

inline void RMdaTimer::CancelAt(TRequestStatus& aStatus)
	{
	CancelMessage(aStatus);
	}

inline void RMdaTimer::CancelAfter(TRequestStatus& aStatus)
	{
	CancelMessage(aStatus);
	}
