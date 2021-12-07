// SimpleServer.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include <e32base.h>

// needed for creating server thread.
const TUint KDefaultHeapSize=0x10000;

// reasons for server panic
enum TCountServPanic
	{
	EBadRequest,
	EBadDescriptor,
	EMainSchedulerError,
	ESvrCreateServer,
	ESvrStartServer,
	ECreateTrapCleanup,
	ENotImplementedYet,
	};


//**********************************
//CCountServServer
//**********************************
//The server class; an active object.
//Contains an instance of RServer; a handle to the kernel server representation which is used 
//to receive messages. 

class CCountServServer : public CServer
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	static void New();
	virtual CSharableSession *NewSessionL(const TVersion &aVersion) const;
static TInt ThreadFunction(TAny* aStarted);
protected:
	CCountServServer(TInt aPriority);
private:
	TInt				iActive;
	};


//**********************************
//CCountServSession
//**********************************
//This class represents a session in the server.
//CSession::Client() returns the client thread.
//Functions are provided to respond appropriately to client messages.


class CCountServSession : public CSession
	{
public:
	// construct/destruct
	CCountServSession(RThread &aClient, CCountServServer * aServer);
	static CCountServSession* NewL(RThread &aClient, CCountServServer * aServer);
	//service request
	virtual void ServiceL(const RMessage &aMessage);
	void DispatchMessageL(const RMessage &aMessage);

	//services available to initialize/increase/decrease/reset and return the counter value.
	void SetFromStringL();
	void Increase();
	void Decrease();
	void IncreaseBy();
	void DecreaseBy();
	void CounterValue();
	void Reset();
protected:
	// panic the client
	void PanicClient(TInt aPanic) const;
	// safewrite between client and server
	void Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset=0);
private:
	CCountServServer *iCountSvr;
	TInt iCount;
	};



//**********************************
//global functions
//**********************************

// function to panic the server
GLREF_C void PanicServer(TCountServPanic aPanic);
// thread function for server
GLREF_C TInt CountServerThread(TAny *);


