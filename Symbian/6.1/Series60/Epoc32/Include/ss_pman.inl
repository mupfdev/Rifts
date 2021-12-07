// SS_PMAN.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline void CProtocolRef::LoadAndBindL()
	{LoadL(EFalse);}

inline CProtocolBase* CProtocolRef::Protocol()
	{ return iProtocol;}

inline void CProtocolRef::ProtocolClosed()
	{
	iProtocol=NULL;
	iFlags=0;
	iFamily->Close();
	}

void CProtocolRef::Close()
	{
	if (iProtocol)
		iProtocol->Close();
	}

inline TPtrC CProtocolRef::Tag()
	{ return iTag->Des();}

inline TServerProtocolDesc& CProtocolRef::Info()
	{ return iInfo; }
	
inline void CProtocolFamilyRef::Close()
	{
	if (iProtocolFamily)
		iProtocolFamily->Close();
	}

inline void CProtocolFamilyRef::FamilyClosed()
	{
	iProtocolFamily=NULL;
	iFlags=0;
	}

inline CProtocolFamilyBase* CProtocolRef::Family()
	{ return &(iFamily->ProtocolFamilyL()); }