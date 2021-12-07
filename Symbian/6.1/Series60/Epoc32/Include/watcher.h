// WATCHER.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __WATCHER_H__
#define __WATCHER_H__

#include <e32base.h>
#include <f32file.h>

//**********************************
// Constants
//**********************************

const TInt KWatcherDelay = 10000000; // 10 seconds

//**********************************
// CWatcher
//**********************************

class CWatcher : public CActive
	{
public:
	IMPORT_C static CWatcher* NewL(TInt aPriority);
	IMPORT_C ~CWatcher();
	//
	IMPORT_C void Start(TRequestStatus& aStatus);
	//
private:
	CWatcher(TInt aPriority);
	void DoCancel();
	void RunL();
	//
private:
	TRequestStatus* iObserver;
	RThread iThread;
	};

//**********************************
// CWatcherLog
//**********************************

const TInt KWatcherLogBuffer = 256;
_LIT(KWatcherStringFormat, "%S");

class CWatcherLog : public CBase
	{
public:
	IMPORT_C static CWatcherLog* NewL(RFs& aFs);
	~CWatcherLog();
	//
	IMPORT_C void Printf(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void Printf(TRefByValue<const TDesC8> aFmt,...);
	IMPORT_C TBool IsLogging() const;
	//
private:
	CWatcherLog(RFs& aFs);
	void ConstructL();
	TBool IsConsole() const;

	//
private:
	CConsoleBase* iConsole;
	RFs& iFs;
	};

//**********************************
// CWatcherWait
//**********************************

class CWatcherWait: public CActive
	{
public:
	IMPORT_C static CWatcherWait* NewLC(TInt aPriority=EPriorityStandard);
	IMPORT_C ~CWatcherWait();
	IMPORT_C void Start();
	//
protected:
	CWatcherWait(TInt aPriority);
	void RunL();
	void DoCancel();
	};

//**********************************
// CWatcherDll
//**********************************

class CWatcherDll : public CActive
	{
public:
	static CWatcherDll* NewL(const TDesC& aDes, RFs& aFs, CWatcherLog& aLog);
	~CWatcherDll();
	//
private:
	CWatcherDll(RFs& aFs, CWatcherLog& aLog);
	void ConstructL(const TDesC& aName);
	void RunL();
	TInt RunError(TInt aError);
	void DoCancel();

	//
	CActive* iWatcher;
	RLibrary iLib;
	RFs& iFs;
	CWatcherLog& iLog;
	RTimer iTimer;
	TInt iStartCount;
	TParse* iFileName; //used for logging purposes only. Deleted at the end of RunL()
	};

//**********************************
// CWatcherArray
//**********************************

class CWatcherArray : public CArrayPtrFlat<CWatcherDll>
	{
public:
	IMPORT_C static CWatcherArray* NewL();
	IMPORT_C ~CWatcherArray();
	//
private:
	CWatcherArray();
	void ConstructL();
	void DoFindWatchersL();
	//
private:
	CWatcherLog* iLog;
	RFs iFs;
	};

#endif
