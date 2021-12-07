// AGMUTIL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMUTIL_H__
#define __AGMUTIL_H__

#include <e32std.h>
#include "agmpanic.h"

#if defined(_DEBUG)
#define AGNDEBUG(s) s
#define DBG_PANIC(m) Panic(m)
TBool SafeToCast(TUint aTrgSize,TInt aSourceSize);
TBool SafeToCast(TUint aTrgSize,TUint aSourceSize);
#else
#define AGNDEBUG(s)
#define DBG_PANIC(m)
#endif

IMPORT_C void Panic(const TDesC& aMessage);
IMPORT_C void Panic(TAgmPanic aPanic);

enum TBits 
	{ 
		EBit0=	0x00,
		EBit1=	0x01,
		EBit2=	0x02,
		EBit3=	0x04,
		EBit4=	0x08,
		EBit5=	0x10,
		EBit6=	0x20,
		EBit7=	0x40,
		EBit8=	0x80,
		EBit9=	0x100,
		EBit10=	0x200,
		EBit11=	0x400,
		EBit12=	0x800,
		EBit13=	0x1000,
		EBit14=	0x2000,
		EBit15=	0x4000,
		EBit16=	0x8000,
		EBit17=	0x10000,
		EBit18=	0x20000,
		EBit19=	0x40000,
		EBit20=	0x80000,
		EBit21=	0x100000,
		EBit22=	0x200000,
		EBit23=	0x400000,
		EBit24=	0x800000,
		EBit25=	0x1000000,
		EBit26=	0x2000000,
		EBit27=	0x4000000,
		EBit28=	0x8000000,
		EBit29=	0x10000000,
		EBit30=	0x20000000,
		EBit31=	0x40000000,
		EBit32=	0x80000000
	};


#endif
