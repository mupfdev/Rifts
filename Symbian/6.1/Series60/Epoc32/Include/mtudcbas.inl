// MTUDCBAS.INL
//
// Copyright (C) Symbian Ltd 1998
//

inline TUid CBaseMtmUiData::Type() const
	{ 
	return iRegisteredMtmDll.MtmTypeUid();
	}

inline const CArrayFix<CBaseMtmUiData::TMtmUiFunction>& CBaseMtmUiData::MtmSpecificFunctions() const
	{ 
	return *iMtmSpecificFunctions; 
	}

