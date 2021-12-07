// Mda\Client\Controller.h 
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_CONTROLLER_H__
#define __MDA_CLIENT_CONTROLLER_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Client\Base.h>
#include <Mda\Client\Port.h>
#include <Mda\Common\Controller.h>


class RMdaController: public RMdaObject
	{
public:
	MDA_OBJECT_OPENREG(KUidMdaControllerValue)
	MDA_OBJECT_FUNCTION2(SetPriority,EMLbControllerPriority,TInt/*Priority*/,TMdaPriorityPreference)
	MDA_OBJECT_FUNCTIONPACK(GetState,EMLbControllerGetState,TMdaControllerStateQuery)
	MDA_OBJECT_FUNCTIONPACK(Connect,EMLbControllerConnect,TMdaRawConnection)
	MDA_OBJECT_FUNCTION(Disconnect,EMLbControllerDisconnect)
	MDA_OBJECT_FUNCTION(Prepare,EMLbControllerPrepare)
	MDA_OBJECT_FUNCTION1(PrepareEx,EMLbControllerPrepare,TInt /*ClientData*/)
	MDA_OBJECT_FUNCTION(Prime,EMLbControllerPrime)
	MDA_OBJECT_FUNCTION1(PrimeEx,EMLbControllerPrime,TInt /*ClientData*/)
	MDA_OBJECT_FUNCTION(Play,EMLbControllerPlay)
	MDA_OBJECT_FUNCTION1(PlayEx,EMLbControllerPlay,TInt /*ClientData*/)
	MDA_OBJECT_FUNCTION(Pause,EMLbControllerPause)
	MDA_OBJECT_FUNCTION1(PauseEx,EMLbControllerPause,TInt /*ClientData*/)
	MDA_OBJECT_FUNCTION(Stop,EMLbControllerStop)
	MDA_OBJECT_FUNCTION1(StopEx,EMLbControllerStop,TInt /*ClientData*/)
	MDA_OBJECT_FUNCTION(Unprepare,EMLbControllerUnprepare)
	MDA_OBJECT_FUNCTION1(UnprepareEx,EMLbControllerUnprepare,TInt /*ClientData*/)
	};

class TMdaConnection : public TMdaRawConnection
	{
public:
	inline TMdaConnection (const RMdaSrcPort& aSrc, const RMdaDstPort& aDst, TUid aMediaType);
	};

// Inlines

inline TMdaConnection::TMdaConnection(const RMdaSrcPort& aSrc, const RMdaDstPort& aDst, TUid aMediaType): 
TMdaRawConnection(sizeof(TMdaConnection)) 
	{
	iSrcHandle = aSrc.Handle();
	iDstHandle = aDst.Handle();
	iType = aMediaType.iUid;
	}

#endif
