// MSVREG.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//



inline TPtrC CMtmDllInfo::HumanReadableName() const
	{
	return iHumanReadableName->Des();
	}

inline TUid CMtmGroupData::MtmTypeUid() const
	{
	return iMtmTypeUid;
	}

inline TUid CMtmGroupData::TechnologyTypeUid() const
	{
	return iTechnologyTypeUid;
	}

inline const CMtmDllInfoArray& CMtmGroupData::MtmDllInfoArray() const
	{
	return iMtmDllInfoArray;
	}

inline TUid CRegisteredMtmDll::MtmTypeUid() const
	{
	return iMtmTypeUid;
	}

inline TUid CRegisteredMtmDll::TechnologyTypeUid() const
	{
	return iTechnologyTypeUid;
	}

inline const CMtmDllInfo& CRegisteredMtmDll::MtmDllInfo() const
	{
	return *iMtmDllInfo;
	}

inline TInt CRegisteredMtmDll::MtmDllRefCount() const
	{
	return iMtmDllRefCount;
	}

inline TInt CMtmDllRegistry::NumRegisteredMtmDlls() const
	{
	return iRegisteredMtmDllArray.Count();
	}

inline TBool CMtmDllRegistry::IsPresent(TUid aMtmTypeUid) const
	{
	return MtmTypeUidToIndex(aMtmTypeUid)<iRegisteredMtmDllArray.Count();
	}

