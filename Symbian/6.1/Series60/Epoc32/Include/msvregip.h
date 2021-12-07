// MSVREGIP.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVREGIP_H__)
#define __MSVREGIP_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

class CMtmGroupData;
class CRegisteredMtmDllArray;
class MRegisteredMtmDllObserver;

class RFs;


class TMsvPackedMtmGroupData
	{
public:
	IMPORT_C TMsvPackedMtmGroupData(HBufC8*& aBuffer);
	IMPORT_C TInt PackMtmGroupData(const CMtmGroupData& aMtmGroupData);
	IMPORT_C CMtmGroupData* UnpackMtmGroupDataL() const;
private:
	HBufC8*& iBuffer;
	};


class TMsvPackedRegisteredMtmDllArray
	{
public:
	IMPORT_C TMsvPackedRegisteredMtmDllArray(HBufC8*& aBuffer);
	IMPORT_C TInt PackRegisteredMtmDllArray(const CRegisteredMtmDllArray& aRegisteredMtmDllArray);
	IMPORT_C void UnpackRegisteredMtmDllArrayL(CRegisteredMtmDllArray& aRegisteredMtmDllArray,const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
private:
	void DoUnpackRegisteredMtmDllArrayL(CRegisteredMtmDllArray& aRegisteredMtmDllArray,const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
private:
	HBufC8*& iBuffer;
	};

#endif

