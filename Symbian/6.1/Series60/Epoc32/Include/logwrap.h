// LOGWRAP.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __LOGWRAP_H__
#define __LOGWRAP_H__

#include <e32base.h>
#include <f32file.h>
#include <barsc.h>
#include <cntdef.h>

#ifndef __WINC__
#include <logwrap.rsg>
#endif

// String lengths
const TInt KLogMaxRemotePartyLength = 64;
const TInt KLogMaxDirectionLength = 64;
const TInt KLogMaxStatusLength = 64;
const TInt KLogMaxSubjectLength = 64;
const TInt KLogMaxDescriptionLength = 64;
const TInt KLogMaxSharedStringLength = 64;
const TInt KLogMaxNumberLength = 32;

// Big enough to contain any of the above strings
typedef TBuf<64> TLogString;

// Type definitions
typedef TInt32	TLogId;
typedef TInt8	TLogDurationType;
typedef TInt8	TLogRecentList;
typedef TUint16 TLogSize;
typedef TUint8	TLogRecentSize;
typedef TUint32	TLogDuration;
typedef TUint32	TLogAge;
typedef TUint32	TLogLink;
typedef TInt16	TLogStringId;
typedef TInt16	TLogTypeId;
typedef TInt8	TLogDurationType;
typedef TUint8	TLogFlags;
typedef TUint32	TLogViewId;

// Limits
const TLogId KLogNullId = -1;
const TLogDurationType KLogNullDurationType = -1;
const TLogDuration KLogNullDuration = 0;
const TLogLink KLogNullLink = 0;
const TLogRecentList KLogNullRecentList = -1;
const TLogStringId KLogNullStringId = -1;
const TLogTypeId KLogNullTypeId = -1;
const TLogFlags KLogNullFlags = 0;
const TLogFlags KLogFlagsMask = 0xF;
const TInt KLogFlagsCount = 4;
const TInt KLogNeverUsedId = -2;

const TInt KLogActiveDoNotCompleteIfActive = KMaxTInt-1;

//**********************************
// CLogActive
//**********************************

class CLogActive : public CActive
	{
public:
	IMPORT_C ~CLogActive();
	//
protected:
	IMPORT_C CLogActive(TInt aPriority);
	IMPORT_C void Queue(TRequestStatus& aStatus);
	IMPORT_C void Complete(TInt aStatus);
	IMPORT_C void DoCancel();
	//
private:
	//
	IMPORT_C void RunL();
	virtual void DoRunL()=0;
	IMPORT_C virtual void DoComplete(TInt&);
	//
private:
	TRequestStatus* iReport;
	};

//**********************************
// CLogEvent
//**********************************

class CLogEvent : public CBase
	{
public:
	IMPORT_C static CLogEvent* NewL();
	IMPORT_C ~CLogEvent();
	//
public:
	inline TLogId Id() const;
	inline void SetId(TLogId aId);
	//
	inline TUid EventType() const;
	inline void SetEventType(TUid aId);
	//
	inline const TDesC& RemoteParty() const;
	inline void SetRemoteParty(const TDesC& aRemote);
	//
	inline const TDesC& Direction() const;
	inline void SetDirection(const TDesC& aDirection);
	//
	inline const TTime& Time() const;
	inline void SetTime(const TTime& aTime);
	//
	inline TLogDurationType DurationType() const;
	inline void SetDurationType(TLogDurationType aDurationType);
	//
	inline TLogDuration Duration() const;
	inline void SetDuration(TLogDuration aDuration);
	//
	inline const TDesC& Status() const;
	inline void SetStatus(const TDesC& aStatus);
	//
	inline const TDesC& Subject() const;
	inline void SetSubject(const TDesC& aSubject);
	//
	inline const TDesC& Number() const;
	inline void SetNumber(const TDesC& aNumber);
	//
	inline TContactItemId Contact() const;
	inline void SetContact(TContactItemId aContact);
	//
	inline TLogLink Link() const;
	inline void SetLink(TLogLink aLink);
	//
	inline const TDesC& Description() const;
	inline void SetDescription(const TDesC& aDescription);
	//
	inline TLogFlags Flags() const;
	inline void SetFlags(TLogFlags aFlags);
	inline void ClearFlags(TLogFlags aFlags);
	//
	inline const TDesC8& Data() const;
	IMPORT_C void SetDataL(RReadStream& aStream, TInt aLen);
	IMPORT_C void SetDataL(const TDesC8& aData);
	//
	IMPORT_C void CopyL(const CLogEvent& aEvent);

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

	//
private:
	CLogEvent();
	void ConstructL();
	void InternalizeBufL(RReadStream& aStream, HBufC*& aDes);
	//
private:
	TLogId iId;
	TUid iEventType;
	TTime iTime;
	TLogDurationType iDurationType;
	TLogDuration iDuration;
	TContactItemId iContact;
	TLogLink iLink;
	TLogFlags iFlags;
	HBufC* iDescription;
	HBufC* iRemoteParty;
	HBufC* iDirection;
	HBufC* iStatus;
	HBufC* iSubject;
	HBufC* iNumber;
	HBufC8* iData;
	};

//**********************************
// CLogBase
//**********************************

class CLogBase : public CLogActive
	{
public:
	IMPORT_C CLogBase(TInt aPriority);
	IMPORT_C ~CLogBase();
	//
	IMPORT_C virtual void GetEvent(CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C virtual void AddEvent(CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C virtual void ChangeEvent(const CLogEvent& aEvent, TRequestStatus& aStatus);
	IMPORT_C virtual void DeleteEvent(TLogId aId, TRequestStatus& aStatus);
	//
	IMPORT_C virtual TInt GetString(TDes& aString, TInt aId) const;
	//
protected:
	IMPORT_C void LoadResourcesL(RFs& aFs);
	inline const RResourceFile& ResourceFile() const;
	//
private:
	void DoRunL();
	//
private:
	RResourceFile iResourceFile;
	//
private:
	IMPORT_C virtual void CLogBase_Reserved1();
	TAny* CLogBase_Reserved;
	};

//**********************************
// CLogWrapper
//**********************************

class CLogWrapper : public CBase
	{
public:
	IMPORT_C static CLogWrapper* NewL(RFs& aFs, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogWrapper();
	//
	inline CLogBase& Log();
	IMPORT_C TBool ClientAvailable() const;
	//
private:
	CLogWrapper();
	void ConstructL(RFs& aFs, TInt aPriority);
	//
private:
	CLogBase* iBase;
	};

#include "logwrap.inl"
#include "logeng.h"

#endif
