// regpsdll.inl
//
// Copyright (c) 1999 Symbian Software plc.  All rights reserved.
//

inline TUidType CRegisteredParserDll::UidType() const
	{
	return iUidType;
	}

inline void CRegisteredParserDll::SetUidType(const TUidType& aUidType)
	{
	iUidType= aUidType;
	}


inline TInt CRegisteredParserDll::DllRefCount() const
	{
	return iDllRefCount;
	}