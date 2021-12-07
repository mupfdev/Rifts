// NTRAS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __NTRAS_H__
#define __NTRAS_H__

#ifndef __NIFMAN_H__
#include <nifman.h>
#endif


class RNtRas : public RNif
	{
public:
	enum TConnectType { EDefault, EClient, EServer };
	IMPORT_C TInt Open();
	IMPORT_C TInt Start(TConnectType aConnectType=EDefault);
	};

_LIT(RAS_COMMSPEED,"CommSpeed");
_LIT(RAS_COMMDATA,"CommData");
_LIT(RAS_COMMHANDSHAKE,"CommHandshake");
_LIT(RAS_AUTHENTICATENAME,"AuthenticateName");
_LIT(RAS_AUTHENTICATEPASSWORD,"AuthenticatePassword");

_LIT(RAS_YESTOCONNECT,"YesToConnect");
_LIT(RAS_YESTORECONNECT,"YesToReconnect");

enum ENtRasProgress
	{
	ERasUninitialised,          //0
	ERasNoConnection,           //1
	ERasStartingSelection,      //2
	ERasFinishedSelection,      //3
	ERasConnectionOpen=10,      //10
	ERasStartingHangUp,         //11
	};

#endif
