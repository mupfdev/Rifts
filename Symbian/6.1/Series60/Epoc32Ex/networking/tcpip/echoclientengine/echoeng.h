// ECHOENG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Declares MTimeOutNotify, MUINotify, CEchoEngine
// CEchoRead, CEchoWrite, CTimeOutTimer

#ifndef _ECHOENG_H_
#define _ECHOENG_H_

#include <e32cons.h>
#include <in_sock.h>
#include <nifman.h>

// MTimeOutNotify: used in conjunction with CTimeOutTimer class
class MTimeOutNotify
	{
public:
	virtual void TimerExpired() = 0;
	};

// MUINotify: implemented by user interfaces; engine up calls
class MUINotify
	{
public:
	virtual void PrintNotify(const TDesC& aMessage) = 0;
	virtual void PrintNotify(TInt aMessage) = 0;
	virtual void ErrorNotify(const TDesC& aErrMessage, TInt aErrCode) = 0;
	};

// CTimeOutTimer: timer for comms time-outs
class CTimeOutTimer: public CTimer
	{
public:
	static CTimeOutTimer* NewL(const TInt aPriority, MTimeOutNotify& aTimeOutNotify);
	~CTimeOutTimer();

protected:
    CTimeOutTimer(const TInt aPriority);
	void ConstructL(MTimeOutNotify& aTimeOutNotify);
    virtual void RunL();

private:
	MTimeOutNotify* iNotify;
	};

// CEchoRead: active object wrapping comms read requests
class CEchoRead : public CActive
	{
public:
	static CEchoRead* NewL(RSocket* aSocket, MUINotify* aConsole);
	static CEchoRead* NewLC(RSocket* aSocket, MUINotify* aConsole);
	void ConstructL(RSocket* aSocket, MUINotify* aConsole);
	void IssueRead();
	void IssueRecvFrom(TInetAddr &aAddr);

	//Implemented functions from CActive
	void DoCancel();
	void RunL();	
	
protected:
	CEchoRead();

private:
	MUINotify* iConsole;
	RSocket* iEchoSocket;
	TBuf8<1> iBuffer;
	};

// CEchoWrite: active object wrapping comms write requests
class CEchoWrite : public CActive, public MTimeOutNotify
	{
public:
	enum TWriteState 
		{
		ESending, EWaiting ,ETimedOut
		};

public:
	static CEchoWrite* NewL(RSocket* aSocket, MUINotify* aConsole);
	static CEchoWrite* NewLC(RSocket* aSocket, MUINotify* aConsole);
	~CEchoWrite();
	void ConstructL(RSocket* aSocket, MUINotify* aConsole);
	void IssueWrite(const TChar &aChar);
	void IssueSendTo(TInetAddr &aAddr, const TChar &aChar);

	//Implemented functions from CActive
	void DoCancel();  
	void RunL(); 

	//Implemented functions from MNTimeOutNotify
	void TimerExpired(); 
	
protected:
	CEchoWrite();

private:
	MUINotify* iConsole;
	RSocket* iEchoSocket;
	TBuf8<1> iBuffer;
	CTimeOutTimer* iTimer;
	TInt iTimeOut;
	TWriteState iWriteStatus;
	};

// CEchoEngine: main engine class for connection and shutdown
class CEchoEngine : public CActive, public MTimeOutNotify
	{
public:
	enum TEchoEngineState 
		{
		EComplete, EConnecting, EConnected, ETimedOut, 
		ELookingUp, ELookUpFailed, EConnectFailed,

		};
public:
	IMPORT_C CEchoEngine();
	IMPORT_C static CEchoEngine* NewL(MUINotify* aConsole);
	IMPORT_C static CEchoEngine* NewLC(MUINotify* aConsole);
	IMPORT_C void ConstructL(MUINotify* aConsole);
	IMPORT_C void Stop();
	IMPORT_C void ConnectL(TUint32 aAddr);
	IMPORT_C void ConnectL(const TDesC& aServerName);
	IMPORT_C void Write(TChar aChar);
	IMPORT_C void Read();
	IMPORT_C void TestGetByAddr(TUint32 aAddr);

	//Implemented functions from MTimeOutNotify
	void TimerExpired(); 

	//Implemented functions from CActive
	void DoCancel();
	void RunL();

	~CEchoEngine();
	
private:
	TEchoEngineState iEngineStatus;
	MUINotify* iConsole;
	CEchoRead* iEchoRead;
	CEchoWrite* iEchoWrite;
	RSocket iEchoSocket;
	RSocketServ iSocketServ;
	RHostResolver iResolver; 
	TNameEntry iNameEntry;
	TNameRecord iNameRecord;
	CTimeOutTimer* iTimer;
	TInt iTimeOut;
	TInetAddr iAddress;
	};

#endif