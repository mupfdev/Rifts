// SimpleClient.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//
#if !defined(__COUNTSERV_H__)
#define __COUNTSERV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif


//**********************************
//RCountServ
//**********************************
// The client class. An RSessionBase sends messages to the server with the function 
// RSessionBase::SendReceive(); specifying an opcode (TCountServRqst) and and array of argument pointers. 
// Functions in derived classes, such as RCountServ::Increase(), are wrappers for different calls to 
// SendReceive().
// Most of the functions here return void because if they fail the server will panic the client.
// If they return it can be assumed that there is no error.

class RCountServ : public RSessionBase
	{
public:
	RCountServ();
	TInt Connect();
	TVersion Version() const;
	TInt Stop();
	TInt SetFromString(const TDesC& aString);
	void Increase();
	void Decrease();
	void IncreaseBy(TInt anInt);
	void DecreaseBy(TInt anInt);
	void Reset();
	TInt CounterValue();
	};


#endif

