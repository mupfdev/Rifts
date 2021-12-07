// D_MMCIF.H
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//
// This header provides the interface to MMCIF.LDD, which provides a set of
// direct interface functions with the kernel MultiMediaCard Controller
//

#if !defined(__D_MMCIF_H__)
#define __D_MMCIF_H__
#include "e32svr.h" 
//
enum TMmcMediaType {EMmcROM,EMmcFlash,EMmcIO,EMmcOther,EMmcNotSupported};
//
const TInt KMaxCardsPerStack=2;
const TInt KSectorSizeInBytes=512;
const TInt KSectorSizeShift=9;
const TInt KDrvBufSizeInSectors=8;
const TInt KDrvBufSizeInBytes=(KDrvBufSizeInSectors<<KSectorSizeShift); // 4K
//
class TMmcCardInfo
	{
public:
	inline TMmcCardInfo()
		  {Mem::FillZ(this,sizeof(TMmcCardInfo)); iMediaType=EMmcNotSupported;}
public:
	TBool iIsReady;
	TBool iIsLocked;
	TUint8 iCID[16];
	TUint16 iRCA;
	TMmcMediaType iMediaType;
    TInt iCardSizeInBytes;
	TUint iReadBlLen;
	TUint iWriteBlLen;
	TBool iReadBlPartial;
	TBool iWriteBlPartial;
	TBool iReadBlkMisalign;
	TBool iWriteBlkMisalign;
    TInt iReadCurrentInMilliAmps;
    TInt iWriteCurrentInMilliAmps;
	TUint iSpecVers;
	TUint iTAAC;
	TUint iNSAC;
	TUint iTransferSpeed;
	TUint iCommandRegister;
	};
//
class TCapsMmcIfV01
	{
public:
	TVersion version;
	};
//
class RMmcCntrlIf : public RBusLogicalChannel
	{
public:
	enum {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=1};
	enum TRequest
		{EReqReadSect=0x0,EReqReadSectCancel=0x1,
		EReqWriteSect=0x1,EReqWriteSectCancel=0x2
		};
	enum TControl
        {ESvReset,ESvPwrUp,ESvPwrDown,ESvRegisterEvent,EExecSelectCard,EExecStackInfo,
        EExecCardInfo};
public:
	inline void Cancel();
	inline TInt Open(TInt aStack,const TVersion& aVer)
		{return(DoCreate(_L("MmcIf"),aVer,NULL,(TInt)aStack,NULL,NULL));}
	inline TVersion VersionRequired() const
		{return(TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber));}
	inline void Reset()
		{DoSvControl(ESvReset);}
	inline void PwrUpAndInitStack(TRequestStatus& aReqStat)
		{DoSvControl(ESvPwrUp,(TAny*)&aReqStat);}
	inline void PwrDownStack()
		{DoSvControl(ESvPwrDown);}
//	inline TInt StackInfo(TUint& aCardsPresentMask,TMMCStackConfig& aConfig) ???
//		{return(DoControl(EExecStackInfo,&aCardsPresentMask,&aConfig));}
	inline TInt StackInfo(TUint& aCardsPresentMask)
		{return(DoControl(EExecStackInfo,&aCardsPresentMask));}
	inline TInt SelectCard(TInt aCard)
		{return(DoControl(EExecSelectCard,(TAny*)aCard));}
	inline TInt CardInfo(TMmcCardInfo& anInfo)
		{return(DoControl(EExecCardInfo,&anInfo));}
	inline TInt RegisterEvent(TUint anEventMask,TRequestStatus *aReqStat)
		{return(DoSvControl(ESvRegisterEvent,(TAny*)anEventMask,(TAny*)aReqStat));}
	inline void ReadSector(TRequestStatus &aStatus,TInt aSectNum,TDes8 &aDes)
		{DoRequest(EReqReadSect,aStatus,(TAny*)aSectNum,(TAny*)&aDes);}
	inline void WriteSector(TRequestStatus &aStatus,TInt aSectNum,const TDesC8 &aDes)
		{DoRequest(EReqWriteSect,aStatus,(TAny*)aSectNum,(TAny*)&aDes);}
	};
//
#endif
