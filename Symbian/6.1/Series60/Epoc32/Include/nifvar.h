// NIFVAR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Interface Manager Standard Variable Names
//

#if !defined(__NIFVAR_H__)
#define __NIFVAR_H__

#ifndef __E32STD_H__
#include <e32std.h>
#endif

#ifndef __CDBCOLS_H__
#include <cdbcols.h>
#endif

const TInt KAgentUninitialised = 0;
const TInt KAgentUnconnected = 1;
const TInt KMaxAgentProgress = 999;
const TInt KMinInterfaceProgress = 1000;
const TInt KMaxInterfaceProgress = 1999;

enum TCallbackAction
	{
	ECallbackActionIETFType0	=0,
	ECallbackActionIETFType1	=1,
	ECallbackActionIETFType2	=2,
	ECallbackActionIETFType3	=3,
	ECallbackActionIETFType4	=4,
	ECallbackActionIETFType5	=5,
	//
	ECallbackActionMSCBCPRequireClientSpecifiedNumber	= 1001,
	ECallbackActionMSCBCPAcceptServerSpecifiedNumber	= 1002,
	ECallbackActionMSCBCPOverrideServerSpecifiedNumber	= 1003
	} ;

#endif
