// ES_SOCK.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

inline TSockIOBufC::TSockIOBufC()
	: TPckgC<TSockIO>(iArgs)
	{}

inline SSockAddr *TSockAddr::BasePtr() const
	{ return (SSockAddr*)iBuf; }

inline TUint8 *TSockAddr::UserPtr() const
	{ return (TUint8*)(BasePtr()+1); }

inline TUint16 ByteOrder::Swap16(TUint aVal)
	{ return ByteOrder::Swap16((TUint16)aVal); }

inline TNameRecord::TNameRecord()
	:iName(),iAddr(),iFlags(0)	
	{}
