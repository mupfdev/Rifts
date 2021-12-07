// SMSULOG.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined (__SMSULOG_H__)
#define __SMSULOG_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined (__LOGWRAP_H__)
#include <logwrap.h>
#endif

class RFs;
class CSmsMessage;



class CSmsEventLogger : public CLogActive
	{
public:
	IMPORT_C static CSmsEventLogger* NewL(RFs& aFs,TInt aPriority=CActive::EPriorityStandard);
	IMPORT_C ~CSmsEventLogger();

	IMPORT_C void AddEvent(TRequestStatus& aStatus,const CSmsMessage& aSmsMessage,const TLogSmsPduData& aData,TInt* aStatusId=NULL);
	IMPORT_C void GetEvent(TRequestStatus& aStatus,TLogId aId);
	IMPORT_C void ChangeEvent(TRequestStatus& aStatus,const CSmsMessage& aSmsMessage,const TLogSmsPduData& aData,TInt* aStatusId=NULL);
	IMPORT_C void DeleteEvent(TRequestStatus& aStatus);

	inline TBool ClientAvailable() const;
	inline TInt GetString(TDes& aString,TInt aId) const;
	inline CLogEvent& Event();
	inline const CLogEvent& Event() const;
	inline const TLogSmsPduData& SmsPDUData() const;

protected:
	void DoCancel();
	
private:
	CSmsEventLogger(TInt aPriority);
	void ConstructL(RFs& aFs);
	void DoRunL();
	void DoAddEventL(const CSmsMessage& aSmsMessage,TInt* aStatusId);
	void SetDataL(const CSmsMessage& aSmsMessage,TInt* aStatusId);
	void DoComplete(TInt& aStatus);
	inline void GetStringL(TDes& aString,TInt aId) const;

private:
	enum TSmsEventLoggerState
		{
		ESmsEventLoggerIdle,
		ESmsEventLoggerGettingEvent,
		ESmsEventLoggerAddingEvent,
		ESmsEventLoggerChangingEvent,
		ESmsEventLoggerDeletingEvent
		};
private:
	TSmsEventLoggerState iState;

	CLogWrapper* iLogWrapper;
	CLogEvent* iLogEvent;

	TLogSmsPduData iSmsPDUData;
	};

#include "smsulog.inl"

#endif 
