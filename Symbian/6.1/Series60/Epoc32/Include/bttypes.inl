// BTTypes.inl
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//

//
// BT protocol wide types
//

inline TBool TBTDevAddr::operator==(const TBTDevAddr& aAddr) const
	{
	return Mem::Compare(&iAddr[0],KBTDevAddrSize,&aAddr.iAddr[0],KBTDevAddrSize) == 0;
	}

inline TBool TBTDevAddr::operator!=(const TBTDevAddr& aAddr) const
	{
	return !(*this==aAddr);
	}

inline const TUint8 &TBTDevAddr::operator[](TInt aIndex) const
	{
	return iAddr[aIndex];
	}

inline TUint8 &TBTDevAddr::operator[](TInt aIndex)
	{
	return iAddr[aIndex];
	}

inline void TBTDevAddr::Reset()
	{
	iAddr.Reset();
	}

inline TPtr8 TBTDevAddr::Des()
	{
	return TPtr8(&iAddr[0], KBTDevAddrSize, KBTDevAddrSize);
	}

inline const TPtrC8 TBTDevAddr::Des() const
	{
	return TPtrC8(&iAddr[0], KBTDevAddrSize);
	}

inline void TBTDevAddr::GetReadable(TDes& aDest) const
	{
	GetReadable(aDest, KNullDesC, KNullDesC, KNullDesC);
	}

inline TBool TUUID::operator==(const TUUID& aUUID) const
	{
	return Mem::Compare(iUUID.Begin(), KSdpUUIDMaxLength, aUUID.iUUID.Begin(), KSdpUUIDMaxLength)==0;
	}

inline TBool TUUID::operator!=(const TUUID& aUUID) const
	{
	return !(*this==aUUID);
	}

inline const TUint8 &TUUID::operator[](TInt aIndex) const
	{
	return iUUID[aIndex];
	}

inline TUint8 &TUUID::operator[](TInt aIndex)
	{
	return iUUID[aIndex];
	}

