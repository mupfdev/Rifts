// SAIRAS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SAIRAS_H__
#define __SAIRAS_H__

#include <e32base.h>
#include "sacls.h"
#include "saclient.h"

enum TSAIrStatus
	{
	IrLoaded,
	IrDiscoveredPeer,
	IrLostPeer,
	IrConnected,
	IrBlocked,
	IrDisConnected,
	IrUnloaded
	};


class RISANotify : public RSystemAgentBase
 	{
public:
	IMPORT_C RISANotify();    
	IMPORT_C TInt NotifyIREvent(TSAIrStatus aIRStatus);
	IMPORT_C TInt NotifyIREventSynchronously(TSAIrStatus aIRStatus);
	};


#endif