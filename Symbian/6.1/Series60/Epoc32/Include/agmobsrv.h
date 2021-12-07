// AGMOBSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMOBSRV_H__
#define __AGMOBSRV_H__

#include <s32file.h>
#include <txtrich.h>
#include "agmentry.h"
#include "agmtodos.h"


#define KUidAgnObserver 0x10000135

class CAgnObserver : public CBase
//
// The end of observer marker MUST be the last thing to be externalized by deriving objects,
// whose responsibility it is to ensure that the marker is unique within their other data
//
  	{
public:
	enum TFunction {ENotifyAddEntry=1,ENotifyDeleteEntry=2,ENotifyUpdateEntry=3,
					ENotifyFetchEntry=4,ENotifyAddTodoList=5,ENotifyDeleteTodoList=6,
					ENotifyUpdateTodoList=7,ENotifyFetchTodoList=8};  

	enum {EEooByte1 = 0x55, EEooByte2 = 0xCC,EEooByte3 = 0xAA,EEooByte4 = 0x33};	// Eoo == end Of Observer

	// interface functions
	virtual void StartObserving()=0;
	virtual void StopObserving()=0;
	virtual CAgnObserver* CloneL()=0;
	virtual void Send(TInt aFunction,CAgnEntry* aEntry)=0;
	virtual void Send(TInt aFunction,CAgnTodoList* aTodoList)=0;
	virtual void ExternalizeL(RWriteStream& aStream) const=0;
	virtual void InternalizeL(RReadStream& aStream)=0;
	IMPORT_C void WriteEndMarkerL(RWriteStream& aStream) const; // MUST be written as the LAST thing in Externalize
	IMPORT_C void ReadEndMarkerL(RReadStream& aStream) const;
	};


#endif
