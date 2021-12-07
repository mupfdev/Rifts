// EIKCMOBS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKCMOBS_H__)
#define __EIKCMOBS_H__

#if !defined(__E32DEF_H__)
#include <e32def.h>
#endif

class CCoeControl;

class MEikCommandObserver
	{
public:
	virtual void ProcessCommandL(TInt aCommandId)=0;
	IMPORT_C virtual CCoeControl* CreateCustomCommandControlL(TInt aControlType);
	};

#endif
