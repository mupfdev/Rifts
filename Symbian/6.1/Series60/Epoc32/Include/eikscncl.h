// EIKSCNCL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKSCNCL_H__)
#define __EIKSCNCL_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#include <eiksrvc.h>

/**
 * @internal
 * Internal to Symbian
 */
class CEikScreenClearerWin : public CCoeControl
	{
public:
	IMPORT_C static CEikScreenClearerWin* NewLC();
	~CEikScreenClearerWin();
private:
	inline CEikScreenClearerWin();
	void ConstructL();
private:
	REikAppUiSession iEikSrv;
	TInt iEikSrvStatus;
	};

#endif
