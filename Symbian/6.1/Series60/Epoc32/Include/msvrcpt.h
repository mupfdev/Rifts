// MSVRCPT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVRCPT_H__)
#define __MSVRCPT_H__

//**********************************
// CMsvRecipient
//**********************************
//
// Base class for  multiple recipients
//

class CMsvRecipient : public CBase
	{
public:
	enum TRecipientStatus {	ENotYetSent=0,
							ESentSuccessfully=1,
				 			EFailedToSend=2};
	IMPORT_C virtual void InternalizeL(RReadStream& aReadStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aWriteStream) const;
	inline TRecipientStatus Status() const;
	inline void SetStatus(TRecipientStatus aStatus);
	inline TInt Error() const;
	inline void SetError(TInt aError);
	inline const TTime& Time() const;
	inline TTime& Time();
	inline TInt Retries() const;
	inline void IncreaseRetries();
	inline void ResetRetries();
protected:
	IMPORT_C CMsvRecipient();
private:
	TRecipientStatus iStatus;
	TInt   iError;
	TInt   iRetries;
	TTime	 iTime;
	};

#include "msvrcpt.inl"

#endif