// IN_SOCK.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_SOCK_INL__
#define __IN_SOCK_INL__

inline SInetAddr* TInetAddr::AddrPtr() const
	{ return (SInetAddr*)UserPtr(); }

inline TInt TInetAddr::AddrLen()
	{ return sizeof(SInetAddr); }

inline TInetAddr& TInetAddr::Cast(const TSockAddr& anAddr)
	{ return *((TInetAddr*)&anAddr); }

inline TInetAddr& TInetAddr::Cast(const TSockAddr* anAddr)
	{ return *((TInetAddr*)anAddr); }

inline TBool TInetAddr::IsBroadcast()
	{ return Address()==KInetAddrBroadcast; }

inline TBool TInetAddr::IsWildPort()
	{ return Port()==KInetPortNone; }

inline TBool TInetAddr::IsWildAddr()
	{ return Address()==KInetAddrNone; }

inline TBool TInetAddr::IsClassA()
	{ return (Address() & KInetAddrIdMaskA) == KInetAddrIdValA; }

inline TBool TInetAddr::IsClassB()
	{ return (Address() & KInetAddrIdMaskB) == KInetAddrIdValB; }

inline TBool TInetAddr::IsClassC()
	{ return (Address() & KInetAddrIdMaskC) == KInetAddrIdValC; }

inline TBool TInetAddr::IsMulticast()
	{ return (Address() & KInetAddrIdMaskD) == KInetAddrIdValD; }

#endif
