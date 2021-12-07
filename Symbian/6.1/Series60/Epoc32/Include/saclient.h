// SACLIENT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SACLIENT_H__
#define __SACLIENT_H__

#include <e32base.h>
#include "sacls.h"

// Constants
const TInt KSysAgentDefaultBufferExpireTimeInSeconds = 10; // 10 seconds



// Encapsulates an asynchronous event with the System Agent.
class TSysAgentEvent
	{
public:
	IMPORT_C TSysAgentEvent();
	IMPORT_C TSysAgentEvent(TRequestStatus& aStatus);
public:
	IMPORT_C void SetRequestStatus(TRequestStatus& aStatus);
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C TInt State();
	IMPORT_C TUid Uid();
public:
	TRequestStatus& RequestStatus();
	void SetState(const TInt aState);
	TPckgBuf<TInt>& StatePckgBuf();
	TPckgBuf<TUid>& UidPckgBuf();
private:
	TPckgBuf<TInt> iRetStatePckg;
	TPckgBuf<TUid> iRetUidPckg;
	TRequestStatus* iStatus;
	};



// Common base class for RSystemAgent, RSAVarChangeNotify and RISANotify
class RSystemAgentBase : public RSessionBase
	{
public:
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	RSystemAgentBase();
protected:
	IMPORT_C TInt StartSystemAgentServer();
	};



// Note: using any TSysAgentEvent asynchronous method will panic if
// a valid TRequestStatus has not been initialised.
class RSystemAgent : public RSystemAgentBase
 	{
public:
	IMPORT_C RSystemAgent();
	IMPORT_C TInt GetState(TUid aUid);

	// aUids must contain at least one uid
	IMPORT_C TInt GetStates(const CArrayFixFlat<TUid>& aUids, CArrayFixFlat<TInt>& aStates);

	IMPORT_C void NotifyOnEvent(TSysAgentEvent& aEvent);
	IMPORT_C void NotifyOnAnyEvent(TSysAgentEvent& aEvent);

	// Returns an error code if aConditions does not contain at least one item, otherwise error code is returned through TRequestStatus
	IMPORT_C TInt NotifyOnCondition(CArrayFixFlat<TSysAgentCondition>& aConditions, TRequestStatus& aStatus);
	IMPORT_C void NotifyEventCancel();

	IMPORT_C void SetEventBufferEnabled(TBool aEnabled);
	IMPORT_C void SetEventBufferEnabled(TBool aEnabled, TTimeIntervalSeconds aExpireTime);

public: // do nothing in release builds
	IMPORT_C void __DbgShutDownServer();
	IMPORT_C void __DbgFailAlloc(TInt aCount);
	IMPORT_C void __DbgMarkHeap();
	IMPORT_C void __DbgMarkEnd();
	IMPORT_C void __DbgEventGenerator(TBool aEnableDisable);
	};



#endif