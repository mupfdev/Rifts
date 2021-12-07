// BIOSCMDS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined (__BIOSCMDS_H__)
#define __BIOSCMDS_H__

#if !defined (__MSVSTD_HRH__)
#include <msvstd.hrh>
#endif

enum TBiosCmds {
	KBiosMtmParse = KMtmFirstFreeMtmFunctionId,
	KBiosMtmParseThenProcess,
	KBiosMtmProcess
};

//
// progress class (just report a state and an error code)
// 
class TBioProgress
	{
public:
	enum TBioState 
		{
		EBiosWaiting,
		EBiosCreating,
		EBiosParsing,
		EBiosProcessing
		};

	TBioState			iBioState;
	TInt				iErrorCode; // client side needs to be informed of an error
	TInt				iPercentDone;
	};

#endif