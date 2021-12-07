//
// in_hook.h
//
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
//	The base definitions for "pseudo protocols" which can do
//	transformations to the TCP/IP packets when called from
//	inside the standard DoSend or DoProcess methods. 
//
#ifndef __IN_HOOK_H__
#define __IN_HOOK_H__

#include "es_prot.h"
#include "es_mbuf.h"
#include "inet.h"

////////////////////////////////////////////////////////////////////////////////

const TUint KProtocolInetHook		= 0x103;	// a temp assignment

//
// CProtocolInetHookBase
//
//	This is really an interface definition, and it would be more clean
//	to define this as an interface without subclassing CProtocolBase.
//	However, as the "hook" is currently installed by BindL, it needs to
//	be a CProtocolBase (otherwise, installing would need a new method
//	into CProtocolBase, like InstallHook. This should be considered, if
//	one needs more complex hooking, like multiple hooks, which have to
//	have predefined execution order).
//
class CProtocolInetHookBase : public CProtocolBase
	{
public:
	virtual TInt ApplyL(RMBufSendPacket &aPacket, RMBufSendInfo &anInfo) = 0;
	virtual TInt ApplyL(RMBufRecvPacket &aPacket, RMBufRecvInfo &anInfo) = 0;
	};

#endif // __IN_HOOK_H__
