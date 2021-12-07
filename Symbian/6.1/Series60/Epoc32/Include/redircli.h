// RedirCli.H
//
// Copyright (c) 1999-1999 Symbian Ltd.  All rights reserved.
//

// EPOC Server for redirecting stdin/stdout/stderr to a stream-like object 
// (console, file or serial port)
//
#ifndef _REDIRCLI_H_
#define _REDIRCLI_H_

#include <e32std.h>
#include <e32base.h>
#include <redirstr.h>

// functions suported by server
enum TRedirStream {
	ERedirRead,
	ERedirWrite,
	ERedirFlush
	};

// reasons for server panic
enum TRedirServPanic
	{
	EBadRequest,
	EBadDescriptor,
	EMainSchedulerError,
	ESvrCreateServer,
	ESvrStartServer,
	ECreateTrapCleanup,
	ENotImplementedYet,
	};

// server name
_LIT(KRedirServerName,"RedirServer");

// A version must be specified when creating a session with the server

const TUint KRedirServMajorVersionNumber=1;
const TUint KRedirServMinorVersionNumber=0;
const TUint KRedirServBuildVersionNumber=0;


//******************************************************************************************
// RRedirSession  
//***********************************************
// client side session for Redirection server

class RRedirSession : public RSessionBase
	{
public:
	IMPORT_C TInt Connect(); // connects to server
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes, TInt aLength);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes, TInt aLength);
	IMPORT_C void Flush(TRequestStatus& aStatus);
private:
//TODO: do we really need this function??
	TInt CheckEOF(TRequestStatus& aStatus);
	};
//

//************************************
// CRedirServer 
//***********************************
// This class represents the Redir server itself.
// It is created through the factory function
// two class declarations to break cyclic dependencies between classes  
class CStreamFactoryBase;
class CStreamBase;

class CRedirServer : public CServer
	{
public:
	enum {EPriority=950}; // mpt - need to explain the magic here!
public:
	IMPORT_C static CRedirServer* NewL(CStreamFactoryBase* aStreamFactory);
	IMPORT_C void SetStreamFactory(CStreamFactoryBase* aStreamFactory);
	virtual CSharableSession *NewSessionL(const TVersion &aVersion) const;
protected:
	CRedirServer(CStreamFactoryBase* aStreamFactory);
private:
	CStreamFactoryBase* iStreamFactory;
	};

//**********************************
// CRedirSession
//**********************************
// This class represents a session in the server.
// Functions are provided to respond appropriately to client messages.

class CRedirSession : public CSharableSession
	{
public:
	// construct/destruct
	CRedirSession(CStreamBase* aStream);
	~CRedirSession();
	static CRedirSession* NewL(CStreamBase* aStream);
	//service request
	virtual void ServiceL(const RMessage &aMessage);
private :
	//services available to handle read/write requests
//	TInt ReadStreamL(const RMessage& aMessage);
	TInt WriteStreamL(const RMessage& aMessage);
protected:
	// panic the client
	void PanicClient(TInt aPanic) const;
	// safewrite between client and server
	void Write(const TAny* aPtr,const TDesC8& aDes,TInt anOffset=0);
private:
	CStreamBase* iStream;
	};

#endif
