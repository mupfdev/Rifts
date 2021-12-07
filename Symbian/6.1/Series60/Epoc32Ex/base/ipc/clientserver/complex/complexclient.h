// ComplexClient.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#if !defined(__ComplexClient_H__)
#define __ComplexClient_H__

#include <e32base.h>


//**********************************
//RCountServ
//**********************************
// The client class. 
// The connect function starts the server, if it not already running.
// An RSessionBase sends messages to the server with the function RSessionBase::SendReceive(); 
// specifying an opcode (TCountServRqst) and and array of argument pointers. 
// Functions in derived subsession classes, such as RCounter::Increase(), are wrappers for different
// calls to SendReceive().
// Resource counting is implemented here.

class RCountServ : public RSessionBase
	{
public:
	RCountServ();
	TInt Connect();
	void ResourceCountMarkStart();
	void ResourceCountMarkEnd();
	TInt ResourceCount();
	TVersion Version() const;
	void Close();
	};


//**********************************
//RCounter
//**********************************
// This class represents a subsession with the server. Each RCounter corresponds to a
// specific CCounter (a CObject derived class) in the server. Messages are passed via the RCountServ;
// A RCounter stores a handle from it's server side CCounter, and uses this to identify the 
// CCounter during communication.

class RCounter : public RSubSessionBase
	{
public:
	TInt Open(RCountServ &aServer);
	TInt SetFromString(const TDesC& aString);
	void Close();
	void Increase();
	void Decrease();
	void IncreaseBy(TInt anInt);
	void DecreaseBy(TInt anInt);
	void Reset();
	TInt CounterValue();
	};


#endif

