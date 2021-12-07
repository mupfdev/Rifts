// SAVENOTF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__SAVENOTF_H__)
#define __SAVENOTF_H__

#include <e32std.h>
#include <e32base.h>

class RSaveSession : public RSessionBase
	{
public:
	TInt Connect();
	void NotifySave(TRequestStatus& aStatus);
	void NotifySaveCancel();
	TInt HandleSaveError(TInt aError);
	};

class MSaveObserver
	{
public:
	enum TSaveType
		{
		ESaveNone,
		ESaveData,
		ESaveAll,
		ESaveQuick,
		EReleaseRAM,
		EReleaseDisk,
		};
public:
	virtual void SaveL(TSaveType aSaveType)=0;
	};

class CSaveNotifier : public CActive
	{
public:
	IMPORT_C static CSaveNotifier* NewL(MSaveObserver& aObserver);
	IMPORT_C ~CSaveNotifier();
	IMPORT_C void DelayRequeue();
	IMPORT_C void Queue();
	IMPORT_C void HandleError(TInt aError);
private:
	inline CSaveNotifier(MSaveObserver& aObserver);
	void ConstructL();
	void Start();
private: // from CActive
	void DoCancel();
	void RunL();
private:
	RSaveSession iSaveSession;
	MSaveObserver& iSaveObserver;
	TUint iFlags;
	};

#endif
