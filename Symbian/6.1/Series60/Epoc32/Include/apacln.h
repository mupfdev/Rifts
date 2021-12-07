// APACLN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__APACLN_H__)
#define __APACLN_H__

#if !defined(__APPARC_H__)
#include <apparc.h>
#endif

// How to put CApaDocument's on the cleanupStack safely:
/*
		TApaDocCleanupItem cleanup(iApaProcess,doc);
		CleanupStack::PushL(cleanup);
		// do stuff...
		CleanupStack::Pop();
*/


class TApaDocCleanupItem
	{
public:
	inline TApaDocCleanupItem(CApaProcess* aProcess,CApaDocument* aDoc);
	inline operator TCleanupItem();
private:
	IMPORT_C static void DoCleanup(TAny* aPtr);
public:
	CApaProcess* iApaProcess;
	CApaDocument* iApaDoc;
	};


inline TApaDocCleanupItem::TApaDocCleanupItem(CApaProcess* aProcess,CApaDocument* aDoc)
	: iApaProcess(aProcess), iApaDoc(aDoc)
	{}
inline TApaDocCleanupItem::operator TCleanupItem()
	{return TCleanupItem(DoCleanup,this);}

#endif