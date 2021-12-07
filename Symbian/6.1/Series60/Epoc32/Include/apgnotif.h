// APGNOTIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __APGNOTIF_H__
#define __APGNOTIF_H__

#include <apgcli.h>

class MApaAppListServObserver
	{
public:
	enum TApaAppListEvent
		{
		EAppListChanged=1
		};
	virtual void HandleAppListEvent(TInt aEvent)=0;
	};

class CApaAppListNotifier : public CActive
	{
public:
	IMPORT_C ~CApaAppListNotifier();
	IMPORT_C static CApaAppListNotifier* NewL(MApaAppListServObserver* aObserver, TPriority aPriority);
private: // from CActive
	void DoCancel();
	void RunL();
private:
	CApaAppListNotifier(MApaAppListServObserver* aObserver, TPriority aPriority);
	void ConstructL();
private:
	MApaAppListServObserver* iObserver;
	RApaLsSession iLsSession;
	};

#endif