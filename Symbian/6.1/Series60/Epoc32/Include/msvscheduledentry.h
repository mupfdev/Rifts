/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduledEntry.H
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef MSV_SCHEDULED_ENTRY_H_
#define MSV_SCHEDULED_ENTRY_H_

/////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
/////////////////////////////////////////////////////////////////////////////

#include "MsvSendErrorAction.h"
#include "MsvEntryScheduleData.h"

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvScheduledEntry Declaration
//
/////////////////////////////////////////////////////////////////////////////

class CMsvScheduledEntry : public CBase
	{
public:
	//Returns ETrue if can send to any of the recipients of iEntry
	//Otherwise returns EFalse
	//Called by CMsvScheduleSend::CanSchedule
	virtual TBool CanSendToAnyRecipients(const CMsvSendErrorActions& aErrorActions, TMsvSendErrorAction& aAction) = 0;
	virtual TBool CanSendToAnyRecipients(const TMsvSendErrorAction& aAction) = 0;
	virtual void RecipientsResetRetries() = 0;
	virtual void RecipientsIncreaseRetries() = 0;
	virtual void RecipientsSetFailed() = 0;
	virtual TBool RecipientsAllSent() const = 0;

	IMPORT_C virtual void StoreL(CMsvStore& aStore) const;
	IMPORT_C virtual void RestoreL(CMsvStore& aStore);

	virtual void RecipientsStoreL(CMsvStore& aStore) const = 0;
	virtual void RecipientsRestoreL(CMsvStore& aStore) = 0;

	inline const TTime& ScheduleDate() const;
	inline void SetScheduleDate(const TTime& aTime);

	inline const TBool Scheduled() const;
	inline void SetScheduled(const TBool aScheduled);

	inline const TInt SendingState() const;
	inline void SetSendingState(TInt aState);

	inline const TInt Error() const;
	inline const TMsvId Id() const;
	inline const TBool OffPeak() const;

	inline void SetFailed(const TBool aFail);
	inline const TBool Failed() const;

	inline const TUid Mtm() const;

//	inline TInt SendingState() const;
//	inline void SetSendingState(TInt aState);

	IMPORT_C void Entry(TMsvEntry& aEntry) const;

protected:

//	--- Construction ---

	IMPORT_C CMsvScheduledEntry(const TMsvEntry& aEntry);

public:

//	--- Public Members ---

	TMsvEntryScheduleData iData;

private:

//	--- Private Members ---

	TMsvEntry iEntry;
	};

/////////////////////////////////////////////////////////////////////////////
//
//	CMsvScheduledEntries Declaration
//
/////////////////////////////////////////////////////////////////////////////

typedef CArrayPtrFlat<CMsvScheduledEntry> CMsvScheduledEntries;

#include "MsvScheduledEntry.inl"

#endif