// MENTACT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined (__MENTACT_H__)
#define __MENTACT_H__

#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif


class CMsgActive : public CActive
	{
public:
	IMPORT_C ~CMsgActive();
protected:
	IMPORT_C CMsgActive(TInt aPriority);
	IMPORT_C void Queue(TRequestStatus& aStatus);
	IMPORT_C void Complete(TInt aStatus);
	IMPORT_C void DoCancel();
private:
	IMPORT_C void RunL();
	virtual void DoRunL()=0;
	IMPORT_C virtual void DoComplete(TInt&);
private:
	TRequestStatus* iReport;
	};

#endif 
