// IR_SOCK.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TIrdaSockAddr &TIrdaSockAddr::Cast(const TSockAddr &aAddr)
	{ return *((TIrdaSockAddr *)&aAddr); }

inline TIrdaSockAddr &TIrdaSockAddr::Cast(const TSockAddr *aAddr)
	{ return *((TIrdaSockAddr *)aAddr); }

inline TUint TIrdaSockAddr::GetRemoteDevAddr() const
	{ return addrPtr()->iRemoteDevAddr; }

inline void TIrdaSockAddr::SetRemoteDevAddr(const TUint aRemote)
	{ addrPtr()->iRemoteDevAddr=aRemote; }

inline TUint TIrdaSockAddr::GetHostDevAddr() const
	{ return addrPtr()->iHostDevAddr; }

inline void TIrdaSockAddr::SetHostDevAddr(const TUint aHost)
	{ addrPtr()->iHostDevAddr=aHost; }

inline TBool TIrdaSockAddr::GetSniffStatus() const
	{ return addrPtr()->iSniff; }

inline void TIrdaSockAddr::SetSniffStatus(const TBool aSniffStatus)
	{ addrPtr()->iSniff=aSniffStatus; }

inline TBool TIrdaSockAddr::GetSolicitedStatus() const
	{ return addrPtr()->iSolicited; }

inline void TIrdaSockAddr::SetSolicitedStatus(const TBool aSolicitedStatus)
	{ addrPtr()->iSolicited=aSolicitedStatus; }

inline TUint8 TIrdaSockAddr::GetIrlapVersion() const
	{ return addrPtr()->iIrlapVersion; }

inline void TIrdaSockAddr::SetIrlapVersion(const TUint8 aIrlapVersion)
	{ addrPtr()->iIrlapVersion=aIrlapVersion; }

inline TUint8 TIrdaSockAddr::GetCharacterSet() const
	{ return addrPtr()->iCharacterSet; }

inline void TIrdaSockAddr::SetCharacterSet(const TUint8 aCharacterSet)
	{ addrPtr()->iCharacterSet=aCharacterSet; }

inline TUint8 TIrdaSockAddr::GetFirstServiceHintByte() const
	{ return addrPtr()->iFirstServiceHintByte; }

inline void TIrdaSockAddr::SetFirstServiceHintByte(const TUint8 aFirstServiceHintByte)
	{ addrPtr()->iFirstServiceHintByte=aFirstServiceHintByte; }

inline TUint8 TIrdaSockAddr::GetSecondServiceHintByte() const
	{ return addrPtr()->iSecondServiceHintByte; }

inline void TIrdaSockAddr::SetSecondServiceHintByte(const TUint8 aSecondServiceHintByte)
	{ addrPtr()->iSecondServiceHintByte=aSecondServiceHintByte; }

inline TUint8 TIrdaSockAddr::GetServiceHintByteCount() const
	{ return addrPtr()->iServiceHintByteCount; }

inline void TIrdaSockAddr::SetServiceHintByteCount(const TUint8 aServiceHintByteCount)
	{ addrPtr()->iServiceHintByteCount=aServiceHintByteCount; }	

inline TUint8 TIrdaSockAddr::GetHomePort() const 
	{ return addrPtr()->iHomePort; }	

inline void TIrdaSockAddr::SetHomePort(const TUint8 aHomePort)
	{ addrPtr()->iHomePort=aHomePort; }	

inline TUint8 TIrdaSockAddr::GetRemotePort() const
	{ return addrPtr()->iRemotePort; }	

inline void TIrdaSockAddr::SetRemotePort(const TUint8 aRemotePort)
	{ addrPtr()->iRemotePort=aRemotePort; }	

inline TBool TIASResponse::IsList() const
	{return operator[](0)>0;}

inline TInt TIASResponse::NumItems() const
	{return operator[](0);}

inline TIASDataType TIASResponse::Type() const
	{
	if ((operator[](0)>EIASDataMissing)&&(operator[](0)<=EIASDataUserString))
		return  (TIASDataType)operator[](0);
	else
		return EIASDataMissing;
	}
