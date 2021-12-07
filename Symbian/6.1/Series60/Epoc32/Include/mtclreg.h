// MTCLREG.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//


#if !defined __MTCLREG_H__
#define __MTCLREG_H__

#include <e32base.h>		// CActive, TFileName etc.
#include "msvreg.h"
#include "msvapi.h"			// MMsvSessionObserver

// CObserverRegistry mixes in session notification API
// this allows run-time update of the registries on the client-side.
// the server registry should inherit from CMtmDllRegistry
class CObserverRegistry : public CMtmDllRegistry, public MMsvSessionObserver
	{
public:
	IMPORT_C virtual void HandleSessionEventL(TMsvSessionEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	IMPORT_C ~CObserverRegistry();

protected:
	IMPORT_C CObserverRegistry(CMsvSession& aMsvSession,TUid aDllTypeUid,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);
	IMPORT_C void ConstructL();

protected:
	CMsvSession& iMsvSession;
	TBool iIsAdded;
	};

// Client side MTM registry
class CClientMtmRegistry : public CObserverRegistry
	{
public:
	IMPORT_C static CClientMtmRegistry* NewL(CMsvSession& aMsvSession, TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32=TTimeIntervalMicroSeconds32(30000000));
	IMPORT_C ~CClientMtmRegistry();
	IMPORT_C CBaseMtm* NewMtmL(TUid aMtmTypeUid);
	//
protected:
	CClientMtmRegistry(CMsvSession& aMsvSession,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);
	void ConstructL();
	//
private:
	CBaseMtm* DoNewMtmL(const RLibrary& aLib, CRegisteredMtmDll& aReg) const;
	};

#endif // __MTCLREG_H__