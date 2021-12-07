/*
* ============================================================================
*  Name     : AknDlgShut.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNDLGSHUT.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNDLGSHUT_H__)
#define __AKNDLGSHUT_H__

#include <e32std.h>

class CEikonEnv;

class AknDialogShutter
	{
public:
	IMPORT_C static void ShutDialogsL(CEikonEnv& aEikEnv);

private:
	static TInt StartLevel();
	};

#endif