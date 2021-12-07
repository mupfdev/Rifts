/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduledEntry.INL
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

inline const TMsvId CMsvScheduledEntry::Id() const
	{
	return iEntry.Id();
	}

inline const TBool CMsvScheduledEntry::OffPeak() const
	{
	return iEntry.OffPeak();
	}

inline const TUid CMsvScheduledEntry::Mtm() const
	{
	return iEntry.iMtm;
	}

inline const TTime& CMsvScheduledEntry::ScheduleDate() const
	{
	return iEntry.iDate;
	}

inline void CMsvScheduledEntry::SetScheduleDate(const TTime& aDate)
	{
	iEntry.iDate = aDate;
	}

inline const TBool CMsvScheduledEntry::Scheduled() const
	{
	return iEntry.Scheduled();
	}

inline void CMsvScheduledEntry::SetScheduled(const TBool aScheduled)
	{
	iEntry.SetScheduled(aScheduled);
	}

inline const TInt CMsvScheduledEntry::Error() const
	{
	return iEntry.iError;
	}

inline const TInt CMsvScheduledEntry::SendingState() const
	{
	return iEntry.SendingState();
	}

inline void CMsvScheduledEntry::SetSendingState(TInt aState)
	{
	iEntry.SetSendingState(aState);
	}

inline void CMsvScheduledEntry::SetFailed(const TBool aFail)
	{
	iEntry.SetFailed(aFail);
	}

inline const TBool CMsvScheduledEntry::Failed() const
	{
	return iEntry.Failed();
	}
