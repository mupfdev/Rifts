// BTTypes.h
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//

//
// BT protocol wide types
//

#ifndef BTTYPES_H
#define BTTYPES_H

#include <e32std.h>

typedef TUint16 THCIConnHandle;
typedef TUint16 TLMPacketType;

// Common packet types
const TLMPacketType KDM1Packet=0x0008;
// ACL only packet types
const TLMPacketType KDH1Packet=0x0010;
const TLMPacketType KAUX1Packet=0x0200;
const TLMPacketType KDM3Packet=0x0400;
const TLMPacketType KDH3Packet=0x0800;
const TLMPacketType KDM5Packet=0x4000;
const TLMPacketType KDH5Packet=0x8000;
// SCO only packet types
const TLMPacketType KHV1Packet=0x0020;
const TLMPacketType KHV2Packet=0x0040;
const TLMPacketType KHV3Packet=0x0080;
const TLMPacketType KDVPacket=0x0100;


enum TBTHostMode
    {
    EActiveMode,        // 0x00 - this is the default
    EHoldMode,          // 0x01
    ESniffMode,         // 0x02
    EParkMode,          // 0x03
    };

static const TInt KSdpUUIDMaxLength			= 16;
const TInt KBTDevAddrSize=0x06;
const TInt KBTMaxDevAddrSize = KBTDevAddrSize;

/**
   48-bit bluetooth device address.
   Each bluetooth device has a unique address built into the hardware, which
   is represented by this class. Used for identifying remote addresses.
   The interface operates in a big-endian manner -- e.g. addr[0] refers
   to the most significant byte of the address. This is the same ordering
   as the addresses would naturally be written down on paper.
**/
class TBTDevAddr
    {
public:
    IMPORT_C TBTDevAddr();
    IMPORT_C TBTDevAddr(const TInt64 &aInt); ///< Construct from a TInt64
    IMPORT_C TBTDevAddr(const TDesC8 &aDes);  ///< Construct from a buffer
    inline TBool operator==(const TBTDevAddr& aAddr) const;
    inline TBool operator!=(const TBTDevAddr& aAddr) const;
	inline const TUint8 &operator[](TInt aIndex) const;
	inline TUint8 &operator[](TInt aIndex);
	inline void Reset(); ///< Zero fill
	inline TPtr8 Des();  ///< Access value as a bigendian descriptor
	inline const TPtrC8 Des() const;
	IMPORT_C TInt SetReadable(const TDesC& aSource);
	inline void GetReadable(TDes& aDest) const;
	IMPORT_C void GetReadable(TDes& aDest, const TDesC& aPrepend, const TDesC& aByteSeperator, const TDesC& aAppend) const;
private:
	TFixedArray<TUint8, KBTDevAddrSize> iAddr;
    };

/**
	A Bluetooth Universally Unique Identifier.

	This is a 128-bit quantity that can be created without a central registry 
	while still being globally unique.
	UUIDs are always held in full 128 bit format, however they can be set from 
	BT SIG short form (16 or 32 bit) addresses, and returned as down to their 
	shortest form using ShortestForm().
**/
class TUUID
	{
public:
	IMPORT_C TUUID();
	IMPORT_C TUUID(TUint32 aLong);
	IMPORT_C TUUID(TUint32 aHH, TUint32 aHL, TUint32 aLH, TUint32 aLL);
	IMPORT_C TUUID(const TUid& aUid);
	IMPORT_C void SetL(const TDesC8& aDes);
	IMPORT_C const TPtrC8 LongForm() const;
	IMPORT_C const TPtrC8 ShortestForm() const;
	IMPORT_C const TPtrC8 Des() const;
    inline TBool operator==(const TUUID& aUUID) const;
    inline TBool operator!=(const TUUID& aUUID) const;
	inline const TUint8 &operator[](TInt aIndex) const;
	inline TUint8 &operator[](TInt aIndex);
private:
	TFixedArray<TUint8, KSdpUUIDMaxLength> iUUID;
	};

const TUint8 KHCILinkKeySize=16;
const TUint8 KHCIPINCodeSize=16;

class TLinkKeyV10
    {
public:
    TUint8 iLinkKey[KHCILinkKeySize];
    };

typedef TPckgBuf<TLinkKeyV10> TBTLinkKey;

class TPINCodeV10
    {
public:
    TUint8 iLength; 
    TUint8 iPIN[KHCIPINCodeSize];
    };
typedef TPckgBuf<TPINCodeV10> TBTPinCode;

const TUint   KGIAC=0x9e8b33; // General Unlimited Inquiry Access Code
const TUint   KLIAC=0x9e8b00; // Limited Inquiry Access Code

#include <bttypes.inl>

#endif
