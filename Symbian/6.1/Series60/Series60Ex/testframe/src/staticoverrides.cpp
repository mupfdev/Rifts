/* Copyright (c) 2001, Nokia. All rights reserved */


#include <e32std.h>
#include "staticoverrideaccess.h"
#include "staticoverridehandler.h"


//  We provide an alternative implementation of this function so that
//  the test framework can detect its call.
void User::Panic(const TDesC& aCategory, TInt aReason)
	{
	MStaticOverrideHandler* handler = NStaticOverrideAccess::GetHandler();
	if (handler)
		{
		//Panic() shouldn't leave, but we have to trap a call to it this way
		handler->OnPanicL(aCategory, aReason);
		}
	}


//  We provide an alternative implementation of this function so that
//  the test framework can detect its call.
void User::Invariant()
	{
	MStaticOverrideHandler* handler = NStaticOverrideAccess::GetHandler();
	if (handler)
		{
		//Invariant() shouldn't leave, but we have to trap a call to it this way
		handler->OnInvariantL();
		}
	}

