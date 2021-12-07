// GENCSIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__GENCSIF_H__)
#define __GENCSIF_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class MConnectivityGenericCallback
	{
public:
	IMPORT_C virtual void Callback(TInt aErrorCode) = 0;
	};

class CConnectivityGenericInterface : public CActive
	{
public:
	virtual void CallServiceL(TInt aServericeId, CBufBase& aBuffer) = 0;
	virtual void ConstructL(MConnectivityGenericCallback* aCallback) = 0;	
	CConnectivityGenericInterface();
	};


CConnectivityGenericInterface::CConnectivityGenericInterface()
	: CActive(EPriorityNormal)
	{}

#endif
