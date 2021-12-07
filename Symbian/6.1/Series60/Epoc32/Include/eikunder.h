// EIKUNDER.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKUNDER_H__)
#define __EIKUNDER_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class RThread;

/**
 * @internal
 * Internal to Symbian
 */
class MEikUndertakerObserver
	{
public:
	virtual void HandleThreadExitL(RThread& aThread)=0;
	};

/**
 * @internal
 * Internal to Symbian
 */
class CEikUndertaker : public CActive
	{
public:
	IMPORT_C static CEikUndertaker* NewL(MEikUndertakerObserver& aObserver);
	IMPORT_C ~CEikUndertaker();
private:
	CEikUndertaker(MEikUndertakerObserver& aObserver);
	void ConstructL();
	void Request();
private: // from CActive
	virtual void DoCancel();
	virtual void RunL();
private:
	MEikUndertakerObserver& iObserver;
	RUndertaker iUndertaker;
	TInt iThreadHandle;
	};

#endif
