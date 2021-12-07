// ComplexServer.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

//needed for creating server thread.
const TUint KDefaultHeapSize=0x10000;

// panic reasons
enum TCountServPanic
	{
	EBadRequest,
	EBadDescriptor,
	EDescriptorNonNumeric,
	EMainSchedulerError,
	ESvrCreateServer,
	ECreateTrapCleanup,
	EBadCounterRemove, 
	EBadSubsessionHandle 
	};

//**********************************
// CCountServSession
//**********************************
//	Server class.
//	Contains an object container index which provides subsessions with object containers.


class CCountServServer : public CServer
	{
public:
	enum {ECountServerPriority=950};
public:
	static void PanicServer(TCountServPanic aPanic);
	static TInt ThreadFunction(TAny* aStarted);
	//construct/destruct
	static CCountServServer* NewL();
	CCountServServer();
	void ConstructL();
	~CCountServServer();
	//open/close a session
	CSharableSession* NewSessionL(const TVersion &aVersion) const;
	void CloseSession();
	// return a object container, guaranteed to produce object containers with unique ids within the server
	CObjectCon* NewContainerL();
private:
	//The server has an object container index which creates an object container for each session
	CObjectConIx *iContainerIndex; 
	};


//**********************************
// CCountServSession
//**********************************
// session for the count server, to a single client-side session
// a session may own any number of CCounter objects

class CCounter;
class CCountServSession : public CSession
	{
public:
	//construct/destruct/close session
	static CCountServSession* NewL(RThread& aClient, /*const */CCountServServer* aServer);
	CCountServSession(RThread& aClient);
	void ConstructL(CCountServServer* aServer);
	void CloseSession();
	//service request
	CCounter* CounterFromHandle(TUint aHandle);
	void ServiceL(const RMessage& aMessage);
	void DispatchMessageL(const RMessage& aMessage);
	//create/delete subsession
	void NewCounterL();
	void DeleteCounter(TUint aHandle); // can't fail - can panic client
	//resource counting
	void NumResources();
	TInt CountResources();
	//utility
	void Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset=0);
	void PanicClient(TInt aPanic) const;

private:
	CObjectCon *iContainer; // object container for this session
	CObjectIx* iCounters; // object index which stores objects (CCounter instances) for this session
	CCountServServer *iCountSvr; // pointer to owning server
		// this pointer has the right derived-class type, unlike CSession::Server() result
	TInt iResourceCount; // total number of resources allocated
	
	};

//**********************************
//CCounter
//**********************************
// CCounter represents a subsession object in the server.
// Each instance corresponds to a client subsession (class RCountSubSession)

class CCounter : public CObject
	{
public:
	static CCounter * NewL(CCountServSession* aSession);
	void ConstructL(CCountServSession *aSession);
	void SetFromString(const RMessage &aMessage);
	void Increase();
	void IncreaseBy();
	void Decrease();
	void DecreaseBy();
	void Reset();
	void CounterValue();
	void CloseCounter();
	const RMessage& Message() const;
protected:
	CCountServSession *iSession; // session owning us
private: // real object member data
 	TInt iCount; // the count we maintain
	};
