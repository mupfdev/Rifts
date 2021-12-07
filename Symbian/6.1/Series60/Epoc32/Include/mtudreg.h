// MTUDREG.H
//
// Copyright (C) Symbian Ltd 1998
//

#if !defined __MTUDREG_H__
#define __MTUDREG_H__

#if !defined (__MTCLREG_H__)
#include <mtclreg.h>
#endif

class CBaseMtmUiData;

typedef CBaseMtmUiData* MtmUiDataFactoryFunctionL(CRegisteredMtmDll&);

// Client side MTM UI data registry

class CMtmUiDataRegistry : public CObserverRegistry
	{
public:
	IMPORT_C static CMtmUiDataRegistry* NewL(CMsvSession& aMsvSession,
		TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32=TTimeIntervalMicroSeconds32(30000000));
	virtual ~CMtmUiDataRegistry();
	IMPORT_C CBaseMtmUiData* NewMtmUiDataLayerL(const TUid& aMtmTypeUid);
	//
protected:
	CMtmUiDataRegistry(CMsvSession& aMsvSession, TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);
	//
private:
	CBaseMtmUiData* NewMtmL(const RLibrary& aLib, CRegisteredMtmDll& aReg) const;
	};



#endif // __MTUDREG_H__