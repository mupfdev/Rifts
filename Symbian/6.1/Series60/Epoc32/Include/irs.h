//	IrS.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__IRS_H__)
#define __IRS_H__

#include <obexServerMtm.h>

class CIrSrvMtm : public CObexSrvMtm
	{
public:
	IMPORT_C static CIrSrvMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry*  aEntry);

private:
	CIrSrvMtm::CIrSrvMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aEntry);
	};

#endif  // __IRS_H__