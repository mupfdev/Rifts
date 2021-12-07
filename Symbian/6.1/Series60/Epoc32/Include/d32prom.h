// D32PROM.H
//
// Copyright (c) 1996-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __D32PROM_H__
#define __D32PROM_H__
#include <e32std.h>

// E2PROM capabilities.
const TUint KCapsE2PromWrite        =0x01;
const TUint KCapsE2PromRead         =0x02;
const TUint KCapsE2PromProtectLock  =0x04;
const TUint KCapsE2PromErase        =0x08;
//
class TE2PromCapsV01
	{
public:
    TVersion iVersion;
    TInt iWidth;
    TInt iLength;
    TUint iModes;
    };
typedef TPckgBuf<TE2PromCapsV01> TE2PromCapsBufV01;
//
class RDevE2Prom : public RBusLogicalChannel
	{
public:
	enum TRequest
		{
		ERequestDummy
		};
	enum TControl
		{
		EE2PromReadData,
		EE2PromWriteData,
        EE2PromWriteAll,
        EE2PromProtectSet,
        EE2PromProtectClear,
        EE2PromProtectRead,
        EE2PromProtectLock,
        EE2PromEnableProtectLock,
        EE2PromCapability
		};
public:
	inline TInt Open(TInt aUnit=KNullUnit);
	inline TInt ReadData(TDes16& aBuffer);
	inline TInt WriteData(TDesC16& aBuffer);
    inline TInt WriteAll(TInt aVal);
    inline TInt ProtectSet(TInt aAddr);
    inline TInt ProtectClear();
    inline TInt ProtectRead();
	inline TInt EnableProtectLock();
    inline TInt ProtectLock();
	inline TInt Caps(TDes8& aCaps);
	};
//
#include <d32prom.inl>
#endif

