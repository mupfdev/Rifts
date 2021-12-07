// MClasses2.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

/*
	Demonstrate use of M classes, or mixins - the
	only use of multiple inheritance that has been
	sanctioned by the E32 architecture team

	This example shows how mixins can be used to
	pass some protocol, and an associated object, from
	a protocol provider to an protocol user.  The user
	is not supposed to know everything about the provider,
	only about the protocol it's interested in.

	In this specific example, the provider contains a pointer 
	to the _real provider_: the provider is derived
	from the protocol base class, but the real provider is not.
	The real provider may thus honour many protocols.
*/

#include "CommonFramework.h"

//////////////////////////////////////////////////////////////////////////////
//
// -----> CProtocol (definition)
//
// A protocol class for mixing in
//
//////////////////////////////////////////////////////////////////////////////
class TProtocol
	{
public:
	virtual void HandleEvent(TInt aEventCode)=0;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CProtocolUser (definition)
//
// Define a protocol user which uses this protocol
//
//////////////////////////////////////////////////////////////////////////////
class CProtocolUser : public CBase
	{
public:
	  // Construction
	static CProtocolUser* NewLC();
	static CProtocolUser* NewL();

	  // Destruction
	~CProtocolUser();

	  // Some function which uses a protocol
	void DoSomething(TProtocol* aProtocol);

protected:
	  // Construction assistance
	void ConstructL();
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CProtocolProvider (definition)
//
// A simple class which uses the mixin
//
//////////////////////////////////////////////////////////////////////////////
class TProtocolProvider;
class CProtocolProvider : public CBase
	{
public:
	  // Construction
	static CProtocolProvider* NewLC();

	  // Destruction
	~CProtocolProvider();

	  // Calls the protocol user
	void CallProtocolUser();

	  // Implement the protocol (handles the protocol)
	void HandleEvent(TInt aEventCode);

protected:
	  // Construction assistance
	void ConstructL();

private:
	  // data members defined by this class
	CProtocolUser*     iProtocolUser;
	TProtocolProvider* iProviderProtocol;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> TProtocolProvider (definition)
//
// Define protocol implementation which passes on the implementation
// to a real protocol provider
//
//////////////////////////////////////////////////////////////////////////////
class TProtocolProvider : public TProtocol
	{
public:
	  // Construction
	TProtocolProvider(CProtocolProvider* aProvider);

	  // The protocol itself
	void HandleEvent(TInt aEventCode);

private:
	  // The real provider
	CProtocolProvider* iProvider;
	};


//////////////////////////////////////////////////////////////////////////////
//
// -----> CProtocolUser (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CProtocolUser* CProtocolUser::NewLC()
	{
	CProtocolUser* self=new(ELeave) CProtocolUser;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CProtocolUser* CProtocolUser::NewL()
	{
	CProtocolUser* self=NewLC();
	CleanupStack::Pop();
	return self;
	}

CProtocolUser::~CProtocolUser()
	{
	}

void CProtocolUser::ConstructL()
	{
	}

void CProtocolUser::DoSomething(TProtocol* aProtocol)
	{
	  // Do something that requires a protocol
	_LIT(KTxtExtSystemDoing,"External system doing something\n");
	console->Printf(KTxtExtSystemDoing);
	_LIT(KTxtInvokingProtocol,"invoking protocol - event 3\n");
	console->Printf(KTxtInvokingProtocol);
	  // Handle an event
	aProtocol->HandleEvent(3);
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> TProtocolProvider (implementation)
//
//////////////////////////////////////////////////////////////////////////////
TProtocolProvider::TProtocolProvider(CProtocolProvider* aProvider)
		: iProvider(aProvider)
	{
	}

// see later for definition of HandleEvent()


//////////////////////////////////////////////////////////////////////////////
//
// -----> CProtocolProvider (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CProtocolProvider* CProtocolProvider::NewLC()
	{
	CProtocolProvider* self=new(ELeave) CProtocolProvider;
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	};

CProtocolProvider::~CProtocolProvider()
	{
	delete iProtocolUser;
	delete iProviderProtocol;
	}

void CProtocolProvider::ConstructL()
	{
	iProtocolUser=CProtocolUser::NewL();
	iProviderProtocol=new(ELeave) TProtocolProvider(this);
	}

void CProtocolProvider::CallProtocolUser()
	{ 
	  // Call the protocol user to do some work
	_LIT(KTxtCallProtUser,"CProtocolProvider calling protocol user\n");
	console->Printf(KTxtCallProtUser);
	iProtocolUser->DoSomething(iProviderProtocol);
			// pass the intermediary, which implements the
			// protocol by passing it on to us,
			// to the protocol user
	}

void CProtocolProvider::HandleEvent(TInt aEventCode)
	{ 
	  // A concrete implementation of the abstract protocol.
	  // Handle an event in the protocol user
	_LIT(KFormat1,"CProtocolProvider handling event %d\n");
	console->Printf(KFormat1,aEventCode);
	}

void TProtocolProvider::HandleEvent(TInt aEventCode)
	{
	  // A concrete definition of TProtocol::HandleEvent()
	_LIT(KTxtHandling,"Handling through intermediary\n");
	console->Printf(KTxtHandling);
	iProvider->HandleEvent(aEventCode);
	}


//////////////////////////////////////////////////////////////////////////////
//
// Do the example
//
//////////////////////////////////////////////////////////////////////////////
LOCAL_C void doExampleL()
    {
	  // show use of mixin with simple class
	CProtocolProvider* simpleProvider=CProtocolProvider::NewLC();
	  // call protocol user
	simpleProvider->CallProtocolUser();
	  // Remove simpleProvider from cleanup stack and destroy
	CleanupStack::PopAndDestroy();
	}
