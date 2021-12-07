// MSVRCPT.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


inline CMsvRecipient::TRecipientStatus CMsvRecipient::Status() const
	{
	return iStatus;
	}

inline void CMsvRecipient::SetStatus(TRecipientStatus aStatus)
	{
	iStatus=aStatus;
	}

inline TInt CMsvRecipient::Error() const
	{
	return iError;
	}

inline void CMsvRecipient::SetError(TInt aError)
	{
	iError=aError;
	}

inline const TTime& CMsvRecipient::Time() const
	{
	return iTime;
	}

inline TTime& CMsvRecipient::Time()
	{
	return iTime;
	}

inline TInt CMsvRecipient::Retries() const
	{
	return iRetries;
	}

inline void CMsvRecipient::IncreaseRetries()
	{
	iRetries++;
	}

inline void CMsvRecipient::ResetRetries()
	{
	iRetries=0;
	}

