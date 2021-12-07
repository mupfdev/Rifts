// BACNTF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Started by BLB, October 1996
#if !defined(__BACNTF_H__)
#define __BACNTF_H__

#include <e32base.h>

class CEnvironmentChangeNotifier : public CActive
	{
public:
	IMPORT_C static CEnvironmentChangeNotifier* NewL(TInt aPriority,const TCallBack& aCallBack);
	IMPORT_C ~CEnvironmentChangeNotifier();
	IMPORT_C void Start();
	IMPORT_C TInt Set(const TCallBack& aCallBack);
	inline TInt Change() const;
private:
	inline CEnvironmentChangeNotifier(TInt aPriority);
	void RunL();
	void DoCancel();
private:
	TInt iChange;
	TCallBack iCallBack;
	RChangeNotifier iChangeNotifier;
	};

inline TInt CEnvironmentChangeNotifier::Change() const
	{return iChange;}

#endif


