// ComplexClientAndServer.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include <e32base.h>

//server name

_LIT(KCountServerName,"MultiCountServer");

//the server version. A version must be specifyed when creating a session with the server
const TUint KCountServMajorVersionNumber=0;
const TUint KCountServMinorVersionNumber=1;
const TUint KCountServBuildVersionNumber=1;
//
IMPORT_C TInt StartThread();

//opcodes used in message passing between client and server
enum TCountServRqst
	{
	ECountServCreateSubSession,
	ECountServCloseSubSession,
	ECountServInitSubSession,
	ECountServCloseSession,
	ECountServIncrease,
	ECountServIncreaseBy,
	ECountServDecrease,
	ECountServDecreaseBy,
	ECountServValue,
	ECountServReset,
	ECountServResourceCountMarkStart,
	ECountServResourceCountMarkEnd,
	ECountServResourceCount
	};


enum TCountServLeave
{
	ENonNumericString
};