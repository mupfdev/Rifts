// NIFPRVAR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Interface Manager Standard Variable Names
//

#if !defined(__NIFPRVAR_H__)
#define __NIFPRVAR_H__

#ifndef __NIFVAR_H__
#include <nifvar.h>
#endif

#define NIF_IFSERVERMODE            _L("Service\\IfServerMode")
#define NIF_CLIENTTIMEOUT			_L("Timeout\\Client")
#define NIF_ROUTETIMEOUT			_L("Timeout\\Route")
#define NIF_STOPIFNOCLIENT			_L("Timeout\\StopIfNoClient")
#define NIF_RECONNECTIFNOCLIENT     _L("Timeout\\ReconnectIfNoClient")

// Notification types from Nif to Agent
enum TNifToAgentEventType
	{
	ENifToAgentEventTypePPPCallbackGranted	= 1,
	ENifToAgentEventTypeQueryIsDialIn	= 2
	};

// Query is dial in responses from NetDial
enum TNDDialType
	{
	ENDDialTypeDialOut,
	ENDDialTypeDialIn,
	ENDDialTypeCallBackDialIn
	};

// Notifications from agent to Nif
enum TAgentToNifEventType
	{
	EAgentToNifEventTypeModifyInitialTimer,		// for GPRS context activation
	EAgentToNifEventTypeDisableTimers,			// for GPRS suspension
	EAgentToNifEventTypeEnableTimers,			// for GPRS resumption
	EAgentToNifEventTypeGetDataTransfer	
	};
	
#endif