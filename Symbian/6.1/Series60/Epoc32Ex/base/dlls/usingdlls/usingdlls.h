// UsingDLLs.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
// A program which uses dynamically linked DLLs.

	// standard example header
#include <e32cons.h>

#ifndef __UsingDLLs_H
#define __UsingDLLs_H

	// The UID for Messenger DLLs.
	// The client imposes this on DLLs which are required
	// to satisfy the protocol 

const TInt KMessengerUidValue=0x10004262;
const TUid KMessengerUid={KMessengerUidValue};

class CMessenger : public CBase
  	{
public:
	virtual void ConstructL(CConsoleBase* aConsole, const TDesC& aName)=0;
	virtual void ShowMessage()=0;
protected:
	CConsoleBase* iConsole;
	HBufC*        iName;
	};

#endif
