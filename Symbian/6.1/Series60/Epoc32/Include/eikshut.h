// EIKSHUT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSHUT_H__)
#define __EIKSHUT_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CEikonEnv;
class CEikAppUi;

class CEikShutter : private CActive
	{
public:
	static void DeferredExecuteL(CEikonEnv& aEikEnv);
	static void DeferredExecuteL(CEikonEnv& aEikEnv, TUid aMessageUid, const TDesC8& aMessageParameters);
private: // virtual from CActive
	void DoCancel();
	void RunL();
	TInt RunError(TInt aError);
private:
	CEikShutter(CEikonEnv& aEikEnv, TUid aMessageUid, HBufC8* aMessageParameters);
	~CEikShutter();
	void Queue();
	static TInt StartLevel();
	void Terminate();
private:
	enum TFlags
		{ETriedDismissMenu=0x01, ETryingToTerminateApp=0x02};
private:
	CEikonEnv& iEikEnv;
	TUid iMessageUid;
	HBufC8* iMessageParameters;
	TInt iFlags;
	TInt iCount;
	TInt iStartLevel;
	};

#endif

