// APMSTD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__APMSTD_H__)
#define __APMSTD_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

const TInt KMaxDataTypeLength=256;

// classes referenced
class RReadStream;
class RWriteStream;

typedef TInt16 TDataTypePriority;

const TInt16 KDataTypePriorityUserSpecified=KMaxTInt16;
const TInt16 KDataTypePriorityHigh=10000;
const TInt16 KDataTypePriorityNormal=0;
const TInt16 KDataTypePriorityLow=-10000;
const TInt16 KDataTypePriorityLastResort=-20000;
const TInt16 KDataTypePriorityNotSupported=KMinTInt16;

class TDataType
	{
public:
	IMPORT_C TDataType();
	IMPORT_C TDataType(const TDataType& aDataType);
	IMPORT_C TDataType(const TDesC8& aDataType);
	IMPORT_C TDataType(TUid aUid);
	// enquiry
	IMPORT_C TInt operator==(const TDataType& aDataType) const;
	IMPORT_C TInt operator!=(const TDataType& aDataType) const;
	IMPORT_C TBool IsNative() const;
	// 
	IMPORT_C TBuf<KMaxDataTypeLength> Des() const;
	IMPORT_C TPtrC8 Des8() const;
	IMPORT_C TUid Uid() const;
	//
	IMPORT_C void InternalizeL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aWriteStream) const;
private:
	void ParseDes();
private:
	TBuf8<KMaxDataTypeLength> iDataType;
	TUid iUid;
	};

#define KApaAppTypeDes _L8("x-epoc/x-app")
_LIT8(KEpocUrlDataTypeHeader, "X-Epoc-Url/");

class TDataTypeWithPriority
	{
public:
	IMPORT_C TDataTypeWithPriority(const TDataType& aDataType, TDataTypePriority aPriority);
public:
	TDataType iDataType;
	TDataTypePriority iPriority;
	};

#endif