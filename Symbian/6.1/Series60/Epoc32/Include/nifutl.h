// NIFUTL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__NIFUTL_H__)
#define __NIFUTL_H__

#ifndef __C32COMM_H__
#include <c32comm.h>
#endif

// Utility classes
class MTimer
	{
public:
	IMPORT_C MTimer();
	IMPORT_C void TimerDelete();
	IMPORT_C void TimerConstructL(TInt aPriority);
	IMPORT_C void TimerAt(const TTime& aTime);
	IMPORT_C void TimerAfter(TTimeIntervalMicroSeconds32 aInterval);
	IMPORT_C void TimerLock(TTimerLockSpec aLock);
	IMPORT_C void TimerCancel();

	virtual void TimerComplete(TInt aStatus)=0;

protected:
	CTimer* iTimer;
	};

class CCommReader;
class CCommWriter;
class CCommLinkStatus;
class MComm
	{

friend class CCommReader;
friend class CCommWriter;
friend class CCommLinkStatus;

public:
	IMPORT_C MComm();
	IMPORT_C void CommDelete();
	IMPORT_C void CommConstructL(TInt aReadPriority, TInt aWritePriority);
	IMPORT_C TInt CommOpen(const TDesC& aName, TCommAccess aAccess);
	IMPORT_C TInt CommOpen(const TDesC& aDll, const TDesC& aName, TCommAccess aAccess);
	IMPORT_C void CommClose();
	IMPORT_C void CommCancel();
	IMPORT_C void CommWrite(const TDesC8& aDes);
	IMPORT_C void CommWriteReady();
	IMPORT_C void CommWriteCancel();
	IMPORT_C TBool CommIsWriting() const;
	IMPORT_C void CommRead(TDes8& aDes);
	IMPORT_C void CommReadOneOrMore(TDes8& aDes);
	IMPORT_C void CommReadReady();
	IMPORT_C void CommReadCancel();
	IMPORT_C TBool CommIsReading() const;

	virtual void CommReadComplete(TInt aStatus)=0;
	virtual void CommWriteComplete(TInt aStatus)=0;

protected:
	RCommServ iCommServer;
	RComm iCommPort;
	CCommReader* iCommReader;
	CCommWriter* iCommWriter;
	CCommLinkStatus* iCommLinkStatus;
	};

#endif
