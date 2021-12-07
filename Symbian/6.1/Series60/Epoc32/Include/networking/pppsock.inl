// PPPSOCK.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

////////////////////////////////////////////////////////////////////////////////
// PPP Socket address - used by link protocols
////////////////////////////////////////////////////////////////////////////////

inline TPppAddr& TPppAddr::Cast(const TSockAddr& aAddr)
	{ return *((TPppAddr*)&aAddr); }

inline TPppAddr& TPppAddr::Cast(const TSockAddr* aAddr)
	{ return *((TPppAddr*)aAddr); }

inline SPppLinkAddr* TPppAddr::InfoPtr() const
	{ return (SPppLinkAddr*)UserPtr(); }

inline void TPppAddr::SetAddress(TUint aAddress)
	{ InfoPtr()->iAddress = aAddress; }

inline void TPppAddr::SetControl(TUint aControl)
	{ InfoPtr()->iControl = aControl; }

inline void TPppAddr::SetProtocol(TUint aProtocol)
	{ InfoPtr()->iProtocol = aProtocol; }

inline void TPppAddr::SetPhase(TPppPhase aPhase)
	{ InfoPtr()->iPhase = aPhase; }

inline void TPppAddr::SetCRCError(TBool anError)
	{ InfoPtr()->iCRCError = anError;}
inline TBool TPppAddr::CRCError()
	{ return InfoPtr()->iCRCError; }

inline TUint TPppAddr::GetAddress()
	{ return InfoPtr()->iAddress; }

inline TUint TPppAddr::GetControl()
	{ return InfoPtr()->iControl; }

inline TUint TPppAddr::GetProtocol()
	{ return InfoPtr()->iProtocol; }

inline TPppPhase TPppAddr::GetPhase()
	{ return InfoPtr()->iPhase; }

