// D_PCCDIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// This header provides the interface to PCCDIF.LDD, which provides a set of
// direct interface functions with the kernel PC Card Controller
//


#if !defined(__D_PCCDIF_H__)
#define __D_PCCDIF_H__
#include "e32svr.h" 

// Tuple codes
const TUint8 KCisTupleNull=0x00;
const TUint8 KCisTupleDevice=0x01;
const TUint8 KCisTupleLongLinkMfc=0x06;
const TUint8 KCisTupleCheckSum=0x10;
const TUint8 KCisTupleLongLinkA=0x11;
const TUint8 KCisTupleLongLinkC=0x12;
const TUint8 KCisTupleLinkTarget=0x13;
const TUint8 KCisTupleNoLink=0x14;
const TUint8 KCisTupleVers1=0x15;
const TUint8 KCisTupleAltStr=0x16;
const TUint8 KCisTupleDeviceA=0x17;
const TUint8 KCisTupleJedecC=0x18;
const TUint8 KCisTupleJedecA=0x19;
const TUint8 KCisTupleConfig=0x1A;
const TUint8 KCisTupleCfTableEntry=0x1B;
const TUint8 KCisTupleDeviceOC=0x1C;
const TUint8 KCisTupleDeviceOA=0x1D;
const TUint8 KCisTupleDeviceGeo=0x1E;
const TUint8 KCisTupleDeviceGeoA=0x1F;
const TUint8 KCisTupleManfId=0x20;
const TUint8 KCisTupleFuncId=0x21;
const TUint8 KCisTupleFunce=0x22;
const TUint8 KCisTupleSwIl=0x23;
const TUint8 KCisTupleVers2=0x40;
const TUint8 KCisTupleFormat=0x41;
const TUint8 KCisTupleGeometry=0x42;
const TUint8 KCisTupleByteOrder=0x43;
const TUint8 KCisTupleDate=0x44;
const TUint8 KCisTupleBattery=0x45;
const TUint8 KCisTupleOrg=0x46;
const TUint8 KCisTupleLongLinkCB=0x47;
const TUint8 KCisTupleVendorSpecific1=0x80;
const TUint8 KCisTupleVendorSpecific2=0x81;
const TUint8 KCisTupleVendorSpecific3=0x82;
const TUint8 KCisTupleEnd=0xFF;

const TUint8 KPccdNonSpecificTuple=0xff;
const TUint8 KInvalConfOpt=0xFF;

enum TPcCardFuncType {EFGlobalCard,EFVendorMultiFuncCard,EFMemoryCard,EFSerialCard,
					EFParallelCard,EFFixedDiskCard,EFVideoCard,EFNetworkCard,EFAimsCard,
					EFScsiCard,EFVendorSpecificCard,EFUnknownCard}; // Order important
enum TPcCardMemType {EPcCardAttribMem,EPcCardCommon8Mem,EPcCardCommon16Mem,EPcCardIo8Mem,EPcCardIo16Mem};
enum TPcCardStatus {EPcCardNotPresent,EPcCardNotReady,EPcCardBad,EPcCardReady};
enum TPcCardSocketVcc	{EPcCardSocket_Invalid=0,EPcCardSocket_5V0=0x01,EPcCardSocket_3V3=0x02,
					 	 EPcCardSocket_xVx=0x04,EPcCardSocket_yVy=0x08};
enum TPcCardAccessSpeed {EAccSpeed50nS,EAccSpeed100nS,EAccSpeed150nS,EAccSpeed200nS,
					   	 EAccSpeed250nS,EAccSpeed300nS,EAccSpeed450nS,EAccSpeed600nS,
					   	 EAccSpeed750nS,EAccSpeedExtended,EAccSpeedInValid};
enum TMemoryDeviceType {EMDeviceNull,EMDeviceRom,EMDeviceOTP,EMDeviceEPROM,
					 	EMDeviceEEPROM,EMDeviceFlash,EMDeviceSRam,EMDeviceDRam,
					 	EMDeviceFunSpec,EMDeviceInvalid}; // Order important
const TInt KMaxPcCardEvents=7;
enum TPcCardEvent {EPcCardEvEmergencyPwrDown,EPcCardEvPwrDown,EPcCardEvPwrUp,EPcCardEvMediaChange,
				   EPcCardEvIReq,EPcCardEvIndChange,EPcCardEvRdyChange};
//
class TPcCardChnk
	{
public:
	inline TPcCardChnk()
		: iMemType(EPcCardAttribMem),iMemBaseAddr(0),iMemLen(0) {}
	inline TPcCardChnk(TPcCardMemType aType,TUint32 aBaseAddr,TUint32 aLen)
		: iMemType(aType),iMemBaseAddr(aBaseAddr),iMemLen(aLen) {}
public:
	TPcCardMemType iMemType;
	TUint32 iMemBaseAddr;
	TUint32 iMemLen;
	};
//
// Active signals 
const TUint KSignalBvdActive=0x00000010;	
const TUint KSignalWpActive=0x00000020;	
const TUint KSignalReadyActive=0x00000040;
const TUint KSignalWaitRequired=0x00000080;	
const TUint KSignalWaitSupported=KSignalWaitRequired;	
// Interrupt info 
const TUint KPcCardIntShare=0x00000080;	
const TUint KPcCardIntPulse=0x00000040;	
const TUint KPcCardIntLevel=0x00000020;	
//
const TInt KMaxChnksPerConfig=2;
class TPcCardConfigInfo 
	{
public:
	inline TPcCardConfigInfo()
		: iAccessSpeed(EAccSpeedInValid),iActiveSignals(0),iVccMaxInMilliVolts(0),
	  	  iVccMinInMilliVolts(0),iValidChunks(0),iIsIoAndMem(EFalse),iIsDefault(EFalse),
	      iPwrDown(EFalse),iVppMaxInMilliVolts(0),iVppMinInMilliVolts(0),iOperCurrentInMicroAmps(0),
	      iPwrDwnCurrentInMicroAmps(0),iInterruptInfo(0),iConfigOption(KInvalConfOpt),iConfigBaseAddr(0),
	      iRegPresent(0) {}
public:								 
	TPcCardAccessSpeed iAccessSpeed;
	TUint iActiveSignals;
	TInt iVccMaxInMilliVolts;			
	TInt iVccMinInMilliVolts;						
	TPcCardChnk iChnk[KMaxChnksPerConfig];
	TInt iValidChunks;
	TBool iIsIoAndMem;
	TBool iIsDefault;
	TBool iPwrDown;
	TInt iVppMaxInMilliVolts;						
	TInt iVppMinInMilliVolts;						
	TInt iOperCurrentInMicroAmps;				   
	TInt iPwrDwnCurrentInMicroAmps;				 
	TUint iInterruptInfo;
	TInt iConfigOption;
	TUint32 iConfigBaseAddr;
	TUint32 iRegPresent;	
	};
//
class TPcCardRegionInfo 
	{
public:
	inline TPcCardRegionInfo()
		: iAccessSpeed(EAccSpeedInValid),iActiveSignals(0),iVcc(EPcCardSocket_Invalid),
		  iDeviceType(EMDeviceInvalid),iExtendedAccSpeedInNanoSecs(0) {}
public:										
	TPcCardAccessSpeed iAccessSpeed;
	TUint iActiveSignals;
	TPcCardSocketVcc iVcc;
	TPcCardChnk iChnk;
	TMemoryDeviceType iDeviceType;
	TInt iExtendedAccSpeedInNanoSecs;
	};
//
const TUint KMaxCardFunc=8;
class TPcCardType
	{
public:
	inline TPcCardType()
		: iFuncCount(0) {iFuncType[0]=EFUnknownCard;}
public:
	TPcCardFuncType iFuncType[KMaxCardFunc];
	TInt iFuncCount;
	};
//
enum TPcCardBatteryState {EPcCardBattZero,EPcCardBattVeryLow,EPcCardBattLow,EPcCardBattGood};
class TSocketSignals
	{
public:
	TBool iCardDetected;
	TInt iVoltSense;
	TBool iWriteProtected;
	TPcCardBatteryState iBatState;
	};
//
class TCapsPccdIfV01
	{
public:
	TVersion version;
	};
//
class TGetTuple
    {
public:
	inline TGetTuple()
        {}
	inline TGetTuple(TInt aFunc,TUint8 aDesiredTpl)
        : iFunc(aFunc),iDesiredTpl(aDesiredTpl)
		{}
public:
    TInt iFunc;
    TUint8 iDesiredTpl;
    };
//
class TReqMem
    {
public:
	inline TReqMem()
        {}
	inline TReqMem(TPcCardChnk aChnk,TPcCardAccessSpeed aSpeed,TUint aFlag)
        : iChnk(aChnk),iSpeed(aSpeed),iFlag(aFlag)
		{}
public:
    TPcCardChnk iChnk;
    TPcCardAccessSpeed iSpeed;
    TUint iFlag;
    };
//
class TReqConfig
    {
public:
	inline TReqConfig()
        {}
	inline TReqConfig(TInt aConfigOption,TUint aFlag)
        : iConfigOption(aConfigOption),iFlag(aFlag)
		{}
public:
	TInt iConfigOption;
    TUint iFlag;
    };
//
class TMemData
    {
public:
    inline TMemData(TInt aPos,TInt aLength,TDes8 *aDes) 
        : iPos(aPos), iLength(aLength), iDes(aDes) 
        {}
public:
    TInt iPos;
    TInt iLength;
    TDes8 *iDes;
    };
//
class TConfigRegData
    {
public:
    inline TConfigRegData(TInt aRegOffset,TInt *aVal) 
        : iRegOffset(aRegOffset), iVal(aVal) 
        {}
public:
    TInt iRegOffset;
    TInt *iVal;
    };
//
typedef TPckgBuf<TGetTuple> TGetTuplePckg;
typedef TPckgBuf<TReqMem> TReqMemPckg;
typedef TPckgBuf<TReqConfig> TReqConfigPckg;
typedef TPckgBuf<TPcCardChnk> TPcCardChnkPckg;
typedef TPckgBuf<TPcCardConfigInfo> TPcCardConfigInfoPckg;
typedef TPckgBuf<TPcCardRegionInfo> TPcCardRegionInfoPckg;
typedef TPckgBuf<TPcCardType> TPcCardTypePckg;
//
class RPcCardCntrlIf : public RBusLogicalChannel
	{
public:
	enum {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=1};
    enum {ESvReset,ESvResetCis,ESvGetTuple,ESvGetRegion,ESvGetConfig,ESvPwrUp,
          ESvPwrDown,ESvReqMem,ESvReqConfig,ESvCardInfo,ESvRegisterEvent,
          ESvRelMem,EExecSocketInfo,EExecMemRead,EExecMemWrite,EExecReadConfigReg,
          EExecWriteConfigReg,ESvReqConfigWithFlags};
public:
	inline void Cancel();
	inline TInt Open(TSocket aSocket,const TVersion& aVer)
		{return(DoCreate(_L("PccdIf"),aVer,NULL,(TInt)aSocket,NULL,NULL));}
	inline TVersion VersionRequired() const
		{return(TVersion(EMajorVersionNumber,EMinorVersionNumber,EBuildVersionNumber));}
	inline void Reset()
		{DoSvControl(ESvReset);}
	inline void PwrUp(TRequestStatus *aReqStat)
		{DoSvControl(ESvPwrUp,(TAny*)aReqStat);}
	inline void PwrDown()
		{DoSvControl(ESvPwrDown);}
	inline TInt CardInfo(TPcCardTypePckg *aType)
		{return(DoSvControl(ESvCardInfo,(TAny*)aType));}
	inline TInt GetTuple(TInt aFunc,TUint8 aDesiredTpl,TDes8 *aTpl)
		{
		TGetTuplePckg gt(TGetTuple(aFunc,aDesiredTpl));
		return(DoSvControl(ESvGetTuple,(TAny*)&gt,(TAny*)aTpl));
		}
	inline TInt GetRegion(TInt aFunc,TPcCardRegionInfoPckg *anInfo)
		{return(DoSvControl(ESvGetRegion,(TAny*)aFunc,(TAny*)anInfo));}
	inline TInt GetConfig(TInt aFunc,TPcCardConfigInfoPckg *anInfo)
		{return(DoSvControl(ESvGetConfig,(TAny*)aFunc,(TAny*)anInfo));}
	inline TInt ReqMem(TPcCardChnk aChnk,TPcCardAccessSpeed aSpeed,TInt &aWindow,TUint aFlag=0)
		{
		TReqMemPckg rm(TReqMem(aChnk,aSpeed,aFlag));
		return(DoSvControl(ESvReqMem,(TAny*)&rm,(TAny*)&aWindow));
		}
	inline void RelMem(TInt aWindow)
		{DoSvControl(ESvRelMem,(TAny*)aWindow);}
	inline TInt ReqConfig(TInt aFunc,TInt aConfigOption)
		{return(DoSvControl(ESvReqConfig,(TAny*)aFunc,(TAny*)aConfigOption));}
	inline TInt ReqConfig(TInt aFunc,TInt aConfigOption,TUint aFlag)
		{
		TReqConfigPckg rc(TReqConfig(aConfigOption,aFlag));
		return(DoSvControl(ESvReqConfigWithFlags,(TAny*)aFunc,(TAny*)&rc));
		}
	inline TInt RegisterEvent(TPcCardEvent anEvent,TRequestStatus *aReqStat)
		{return(DoSvControl(ESvRegisterEvent,(TAny*)anEvent,(TAny*)aReqStat));}
	inline TInt ResetCis(TInt aFunc)
		{return(DoSvControl(ESvResetCis,(TAny*)aFunc));}
	inline TInt SocketInfo(TPcCardStatus &aStatus,TSocketSignals &anIndicator)
		{return(DoControl(EExecSocketInfo,&aStatus,&anIndicator));}
	inline TInt ReadMem(TInt aWindow,TInt aPos,TInt aLength,TDes8 &aDes)
//		{return(DoControl(EExecMemRead,(TAny*)aWindow,&TMemData(aPos,aLength,&aDes)));}
		{
		TMemData md(aPos,aLength,&aDes);
		return(DoControl(EExecMemRead,(TAny*)aWindow,&md));
		}
	inline TInt WriteMem(TInt aWindow,TInt aPos,const TDesC8 &aDes)
//		{return(DoControl(EExecMemWrite,(TAny*)aWindow,&TMemData(aPos,0,&aDes)));}
		{
		TMemData md(aPos,0,(TDes8*)&aDes);
		return(DoControl(EExecMemWrite,(TAny*)aWindow,&md));
		}
	inline TInt ReadConfigReg(TInt aFunc,TInt aRegOffset,TInt &aVal)
		{
        TConfigRegData crd(aRegOffset,&aVal);
		return(DoControl(EExecReadConfigReg,(TAny*)aFunc,&crd));
		}
	inline TInt WriteConfigReg(TInt aFunc,TInt aRegOffset,TInt &aVal)
		{
        TConfigRegData crd(aRegOffset,&aVal);
		return(DoControl(EExecWriteConfigReg,(TAny*)aFunc,&crd));
		}
	};
//
#endif
