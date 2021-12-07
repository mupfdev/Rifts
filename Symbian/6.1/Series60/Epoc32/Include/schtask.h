// SCHTASK.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//
// Representation of a task: 
// Includes both user-defined data (iInfo+iData) and data set by system
// construction from stream & accessors are exported for task executors

#if !defined(__SCHTASK_H__)
#define __SCHTASK_H__

#if !defined(__SCHINFO_H__)
#include "SCHINFO.H"
#endif 

#include <s32file.h>

class CScheduledTask : public CBase
	{
public:
	IMPORT_C static CScheduledTask* NewLC(RReadStream& aStream);
	CScheduledTask();
	IMPORT_C CScheduledTask(TTaskInfo& aInfo, HBufC* aData);
	~CScheduledTask();
	IMPORT_C const TTaskInfo& Info() const;
	IMPORT_C const HBufC& Data() const;
	IMPORT_C const TTime& ValidUntil() const;
	//
	TBool Due() const;
	//
	void SetDue(TBool aDue);
	void OnDue(const TTime& aValidUntil);
	void DecRepeat();
	void Remove();
	//
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	//
	TInt ScheduleId() const;
	void SetScheduleId(TInt aScheduleId);
	//
	static const TInt Offset();
	//
private:
	TPriQueLink iPLink;
	TTaskInfo iInfo;
	HBufC* iData;
	TTime iValidUntil;
	TBool iDue;
	TInt iScheduleId;
	};

#endif
