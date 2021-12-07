// LOGCLI.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//
#ifndef __LOGCLI_H__
#define __LOGCLI_H__

// System includes
#include <f32file.h>
#include <d32dbms.h>
#include <logwrap.h>
//
#include <logcli.rsg>

// Classes referenced
class CLogClientObserver;
class MLogClientChangeObserver;


//**********************************
// CLogEventType
//**********************************

class CLogEventType : public CBase
	{
public:
	IMPORT_C static CLogEventType* NewL();
	IMPORT_C ~CLogEventType();
	//
public:
	inline TUid Uid() const;
	inline void SetUid(TUid aUid);
	//
	inline const TDesC& Description() const;
	inline void SetDescription(const TDesC& aDescription);
	//
	inline TBool LoggingEnabled() const;
	inline void SetLoggingEnabled(TBool aEnable);
	//
	IMPORT_C void Copy(const CLogEventType& aType);

	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	//
private:
	CLogEventType();
	void ConstructL();
	void InternalizeBufL(RReadStream& aStream, HBufC*& aDes);
	//
private:
	TUid iUid;
	HBufC* iDescription;
	TBool iLoggingEnabled;
	};

//**********************************
// TLogConfig
//**********************************

class TLogConfig
	{
public:
	IMPORT_C TLogConfig();
	//
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	//
public:
	TLogSize iMaxLogSize;
	TLogRecentSize iMaxRecentLogSize;
	TLogAge iMaxEventAge;
	};

//**********************************
// CLogFilter
//**********************************

class CLogFilter : public CBase
	{
public:
	IMPORT_C static CLogFilter* NewL();
	IMPORT_C ~CLogFilter();
	//
public:
	inline TUid EventType() const;
	inline void SetEventType(TUid aType);
	//
	inline const TDesC& RemoteParty() const;
	inline void SetRemoteParty(const TDesC& aRemote);
	//
	inline const TDesC& Direction() const;
	inline void SetDirection(const TDesC& aDirection);
	//
	inline TLogDurationType DurationType() const;
	inline void SetDurationType(TLogDurationType aType);
	//
	inline const TDesC& Status() const;
	inline void SetStatus(const TDesC& aStatus);
	//
	inline TContactItemId Contact() const;
	inline void SetContact(TContactItemId aContact);
	//
	inline const TDesC& Number() const;
	inline void SetNumber(const TDesC& aNumber);
	//
	inline TLogFlags Flags() const;
	inline void SetFlags(TLogFlags aFlags);
	inline void ClearFlags(TLogFlags aFlags);
	//
	inline TUint32 NullFields() const;
	inline void SetNullFields(TUint32 aFields);
	//
	IMPORT_C void Copy(const CLogFilter& aFilter);
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	//
private:
	CLogFilter();
	void ConstructL();
	void InternalizeBufL(RReadStream& aStream, HBufC*& aDes);
	//
private:
	TUid iEventType;
	HBufC* iRemoteParty;
	HBufC* iDirection;
	TLogDurationType iDurationType;
	HBufC* iStatus;
	TContactItemId iContact;
	HBufC* iNumber;
	TLogFlags iFlags;
	TUint32 iNullFields;
	};

class CLogFilterList : public CArrayPtrFlat<const CLogFilter>
	{
public:
	IMPORT_C CLogFilterList();
	IMPORT_C CLogFilterList* CopyL() const;
	IMPORT_C CLogFilterList* CopyLC() const;
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	};

//**********************************
// CLogClient
//**********************************

class CLogView;
class RLogSession;
class CLogPackage;
class CLogAddEventClientOp;
class CLogChangeEventClientOp;
class CLogGetEventClientOp;
class CLogDeleteEventClientOp;
class CLogAddTypeClientOp;
class CLogChangeTypeClientOp;
class CLogGetTypeClientOp;
class CLogDeleteTypeClientOp;
class CLogGetConfigClientOp;
class CLogChangeConfigClientOp;
class CLogClearLogClientOp;
class CLogClearRecentClientOp;

class CLogClient : public CLogBase
	{
public:
	IMPORT_C static CLogClient* NewL(RFs& aFs, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogClient();
	//
public:
	IMPORT_C void AddEvent(CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C void GetEvent(CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C void ChangeEvent(const CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C void DeleteEvent(TLogId aId, TRequestStatus& aStatus);

	IMPORT_C void AddEventType(const CLogEventType& aType, TRequestStatus& aStatus);
	IMPORT_C void GetEventType(CLogEventType& aType, TRequestStatus& aStatus);
	IMPORT_C void ChangeEventType(const CLogEventType& aType, TRequestStatus& aStatus);
	IMPORT_C void DeleteEventType(TUid aId, TRequestStatus& aStatus);
	IMPORT_C void GetConfig(TLogConfig& aConfig, TRequestStatus& aStatus);
	IMPORT_C void ChangeConfig(const TLogConfig& aConfig, TRequestStatus& aStatus);
	IMPORT_C void ClearLog(const TTime& aDate, TRequestStatus& aStatus);
	IMPORT_C void ClearLog(TInt aRecentList, TRequestStatus& aStatus);
	//
	IMPORT_C void NotifyChange(TTimeIntervalMicroSeconds32 aDelay, TRequestStatus& aStatus);
	IMPORT_C void NotifyChangeCancel();
	//
	IMPORT_C void SetGlobalChangeObserverL(MLogClientChangeObserver* aObserver);
	//
	IMPORT_C TInt GetString(TDes& aString, TInt aId) const;
	RLogSession& Session() const;
	//
private:
	CLogClient(RFs& aFs, TInt aPriority);
	void ConstructL();
	void DoGetStringL(TDes& aString, TInt aId) const;
	//
	void DoRunL();
	void DoCancel();
	//
private:
	RLogSession* iSession;
	CLogPackage* iPackage;
	CLogAddEventClientOp* iAddEvent;
	CLogChangeEventClientOp* iChangeEvent;
	CLogGetEventClientOp* iGetEvent;
	CLogDeleteEventClientOp* iDeleteEvent;
	CLogAddTypeClientOp* iAddType;
	CLogChangeTypeClientOp* iChangeType;
	CLogGetTypeClientOp* iGetType;
	CLogDeleteTypeClientOp* iDeleteType;
	CLogGetConfigClientOp* iGetConfig;
	CLogChangeConfigClientOp* iChangeConfig;
	CLogClearLogClientOp* iClearLog;
	CLogClearRecentClientOp* iClearRecent;
	RFs& iFs;
	CLogClientObserver* iChangeObserver;
	//
private:
	IMPORT_C void CLogBase_Reserved1();
	};

#include "logcli.inl"

#endif
