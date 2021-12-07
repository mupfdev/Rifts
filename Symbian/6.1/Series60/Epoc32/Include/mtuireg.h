// MTUIREG.H
//
// Copyright (C) Symbian Ltd 1998
//

// MTM client-side MTMUI registry class 

#if !defined __MTUIREG_H__
#define __MTUIREG_H__


#if !defined (__E32BASE_H__)
#include <e32base.h>		// CActive, TFileName etc.
#endif

#if !defined (__MTCLREG_H__)
#include <mtclreg.h>
#endif

class CBaseMtmUi;

typedef CBaseMtmUi* MtmUiFactoryFunctionL(CBaseMtm&, CRegisteredMtmDll&);

// Client side MTM registry

class CMtmUiRegistry : public CObserverRegistry
	{
public:
	IMPORT_C static CMtmUiRegistry* NewL(CMsvSession& aMsvSession,
		TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32=TTimeIntervalMicroSeconds32(30000000));
	virtual ~CMtmUiRegistry();
	IMPORT_C CBaseMtmUi* NewMtmUiL(CBaseMtm& aMtm);
	//
protected:
	CMtmUiRegistry(CMsvSession& aMsvSession, TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);
	//
private:
	CBaseMtmUi* NewMtmL(const RLibrary& aLib, CBaseMtm& aMtm, CRegisteredMtmDll& aReg) const;
	};



#endif // __MTUIREG_H__