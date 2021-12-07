// LOGVIEW.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//
#ifndef __LOGVIEW_H__
#define __LOGVIEW_H__

// System includes
#include <d32dbms.h>
#include <logwrap.h>

// User includes
#include "logcli.h"

// Classes referenced
class CLogClient;
class CLogGetEventClientOp;
class CLogPackage;
class CLogViewSetupClientOp;
class CLogMaintainClientOp;
class CLogViewObserver;
class CLogFilterList;
class CLogFilter;
class CLogViewDuplicate;
class CLogViewRemoveEventClientOp;
class MLogViewChangeObserver;
class CLogViewWindow;


//**********************************
// CLogView
//**********************************

class CLogView : public CLogActive
	{
public:
	IMPORT_C ~CLogView();
	//
public:
	inline const CLogEvent& Event() const;
	//
	IMPORT_C TBool FirstL(TRequestStatus& aStatus);
	IMPORT_C TBool LastL(TRequestStatus& aStatus);
	IMPORT_C TBool NextL(TRequestStatus& aStatus);
	IMPORT_C TBool PreviousL(TRequestStatus& aStatus);
	//
	IMPORT_C TInt CountL();
	//
	IMPORT_C void SetFlagsL(TLogFlags aFlags);
	//
protected:
	CLogView(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	void ConstructL(TInt aType, MLogViewChangeObserver* aObserver = NULL);
	//
	inline TBool IsValid() const;
	void DoCancel();
	void ReadEventFromWindowL();
	void ReawaitForChanges();
	//
private:
	TBool NavigateL(TInt aPosition, TRequestStatus& aStatus);
	void DoRunL();
	//
private:
	CLogEvent* iEvent;
	TAny* iSpare1;
	//
protected:
	CLogClient& iClient;
	CLogPackage* iPackage;
	TAny* iSpare2;
	CLogMaintainClientOp* iMaintain;
	TLogViewId iViewId;
	TDes8* iData;
	TBool iValid;
	CLogViewWindow* iWindow;
	//
private:
	CLogViewObserver* iLogViewObserver;
	};

//**********************************
// CLogViewEvent
//**********************************


class CLogViewEvent : public CLogView
	{
public:
	IMPORT_C static CLogViewEvent* NewL(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C static CLogViewEvent* NewL(CLogClient& aClient, MLogViewChangeObserver& aObserver, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogViewEvent();
	//
public:
	IMPORT_C TBool SetFilterL(const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	IMPORT_C TBool SetFilterL(const CLogFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C TBool SetFilterParseFilterByFilterL(const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	//
private:
	CLogViewEvent(CLogClient& aClient, TInt aPriority);
	void ConstructL(MLogViewChangeObserver* aObserver = NULL);
	};

//**********************************
// CLogViewRecent
//**********************************


class CLogViewRecent : public CLogView
	{
public:
	IMPORT_C static CLogViewRecent* NewL(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C static CLogViewRecent* NewL(CLogClient& aClient, MLogViewChangeObserver& aObserver, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogViewRecent();
	//
public:
	IMPORT_C TBool SetRecentListL(TLogRecentList aList, TRequestStatus& aStatus);
	IMPORT_C TBool SetRecentListL(TLogRecentList aList, const CLogFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C TBool SetRecentListL(TLogRecentList aList, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	//
	IMPORT_C TBool DuplicatesL(CLogViewDuplicate& aView, TRequestStatus& aStatus);
	IMPORT_C TBool DuplicatesL(CLogViewDuplicate& aView, const CLogFilter& aFilter, TRequestStatus& aStatus);
	IMPORT_C TBool DuplicatesL(CLogViewDuplicate& aView, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	IMPORT_C void ClearDuplicatesL();
	//
	IMPORT_C void RemoveL(TLogId aId);
	IMPORT_C TBool RemoveL(TRequestStatus& aStatus);
	//
	inline TLogRecentList RecentList() const;
	//
private:
	CLogViewRecent(CLogClient& aClient, TInt aPriority);
	void ConstructL(MLogViewChangeObserver* aObserver = NULL);
	void DoRunL();
	//
	TBool DoRemoveL(TRequestStatus& aStatus);
	//
private:
	TLogRecentList iRecentList;
	TLogRecentList iCurrentList;
	TPckgBuf<TLogRecentList> iCurrentListBuf;
	CLogViewRemoveEventClientOp* iRemove;
	};

//**********************************
// CLogViewDuplicate
//**********************************

class CLogViewDuplicate : public CLogView
	{
public:
	IMPORT_C static CLogViewDuplicate* NewL(CLogClient& aClient, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C static CLogViewDuplicate* NewL(CLogClient& aClient, MLogViewChangeObserver& aObserver, TInt aPriority = CActive::EPriorityStandard);
	IMPORT_C ~CLogViewDuplicate();
	//
	IMPORT_C void RemoveL(TLogId aId);
	IMPORT_C TBool RemoveL(TRequestStatus& aStatus);
	//
	inline TLogId Source() const;
	//
public:
	// The following are not exported, use CLogViewRecent::DuplicatesL to initialise this view
	TBool SetEventL(TLogId aId, TRequestStatus& aStatus);
	TBool SetEventL(TLogId aId, const CLogFilter& aFilter, TRequestStatus& aStatus);
	TBool SetEventL(TLogId aId, const CLogFilterList& aFilterList, TRequestStatus& aStatus);
	//
private:
	CLogViewDuplicate(CLogClient& aClient, TInt aPriority);
	void ConstructL(MLogViewChangeObserver* aObserver = NULL);
	//
	TBool DoRemoveL(TRequestStatus& aStatus);
	//
private:
	TLogId iSourceId;
	CLogViewRemoveEventClientOp* iRemove;
	};

#include "logview.inl"

#endif
