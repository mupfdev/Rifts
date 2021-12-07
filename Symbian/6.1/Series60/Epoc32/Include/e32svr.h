// E32SVR.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32SVR_H__
#define __E32SVR_H__
#include <e32std.h>
#include <e32keys.h>
#include <e32base.h>
#include <e32hal.h>
#include <e32pccd.h>

//
// Info to create a real time thread
//
class TRealTimeThreadCreate
	{
public:
	TThreadFunction iFunction;
	TInt iStackSize;
	TInt iHeapSize;
	TAny *iPtr;
	TInt iHandle;
	TInt iSpare;
	};
//
// Loader version number.
//
const TInt KLoaderMajorVersionNumber=1;
const TInt KLoaderMinorVersionNumber=0;
//
const TInt KFormatSectorSize=0x00000200;		// 512
const TInt KFormatSectorShift=9;	
const TUint KFormatSectorMask=0xFFFFFE00;
//
enum TBlockType {EBlocked,EUnBlocked,ERelease};
//
class TRawEvent
	{
public:
	enum TType
		{
		ENone,
		EPointerMove,
        EPointerSwitchOn,
		EKeyDown,EKeyUp,
		ERedraw,
		ESwitchOn,
        EActive,
		EInactive,
		EUpdateModifiers,
		EButton1Down,EButton1Up,
		EButton2Down,EButton2Up,
		EButton3Down,EButton3Up,
		ESwitchOff, EKeyRepeat,
		ECaseOpen, ECaseClose
		};
public:
	inline TRawEvent()
		: iType(ENone)
		{}
	inline TType Type() const
		{return iType;}
	IMPORT_C TPoint Pos() const;
	IMPORT_C TInt ScanCode() const;
    IMPORT_C TInt Modifiers() const;
	inline TUint Ticks() const
		{return iTicks;}
	IMPORT_C void Set(TType aType,TInt aScanCode);
	IMPORT_C void Set(TType aType,TInt aX,TInt aY);
	IMPORT_C void Set(TType aType);
protected:
	TType iType;
	TUint iTicks;
	union
		{
		struct {TInt x;TInt y;} pos;
		TInt scanCode;
		TInt modifiers;
		} iU;
	};
//
class TRawEventBuf : public TPckgBuf<TRawEvent>
	{
public:
	inline TRawEvent &Event() const {return(*((TRawEvent *)&iBuf[0]));}
	};
//
class TScreenInfoV01
	{
public:
	TBool iWindowHandleValid;
	TAny *iWindowHandle;
	TBool iScreenAddressValid;
	TAny *iScreenAddress;
	TSize iScreenSize;
	};
//
enum TLoaderMsg {ELoadProcess=1,ELoadLibrary=2};
//
class RLoader : public RSessionBase
	{
public:
	IMPORT_C TInt Connect();
	TVersion Version() const;
	TInt LoadProcess(TInt &aHandle,const TDesC &aFileName,const TDesC &aCommand,const TUidType &aUidType, TOwnerType aType);
	IMPORT_C TInt LoadLibrary(TInt &aHandle,const TDesC &aFileName,const TDesC &anExt, const TDesC &aPath, const TUidType &aType);
	};
//
class TLoaderInfo
	{
public:
	IMPORT_C TLoaderInfo();
public:
	TUidType iType;
	TUint32 iCheck;
	TUint32 iCheckSumCode;
	TInt iCodeSize;
	TInt iDataSize;
	TInt iHeapSizeMin;
	TInt iHeapSizeMax;
	TInt iStackSize;
	TInt iBssSize;
	TUint iEntryPoint;
	TDllRefTable* iDllRefTable;
	TInt iDllRefTableCount;
	TUint iExportDir;
	TInt iExportDirCount;
	TUint iTargetCodeAddress;
	TUint32 iTargetCodeBase;
	TUint iTargetDataAddress;
	TUint32 iTargetDataBase;
	TFileName iFileName;
	TFileName iRootName;
	TPath iPath;
	TBool isLoadedFromRam;
	TBool isDll;
	TBool isAlreadyLoaded;
	TInt iHandle;
	TInt iThreadHandle;
	TInt iProcessHandle; // used when loading on behalf of another process
	TInt iLibraryHandle; // used when loading on behalf of another library
	TUint iHandleMask;
	TProcessPriority iPriority;
	TInt iTextSize;
	TAny *iLibPtr;		// pointer to kernel-side DLibrary or DProcess object
	};
//
#define __NOTIFIER_NAME _L("Notifier")
enum TNotifierMessage 
	{
	ENotifierNotify,
	ENotifierInfoPrint,
	EStartNotifier,
	ECancelNotifier,
	EUpdateNotifier,
	EStartNotifierAndGetResponse,
	ELoadNotifier,
	EUnloadNotifier
	};
//
class TBusDevOpenModeData
   {
public:
   	inline TBusDevOpenModeData(const TDesC &aDeviceName,TInt aUnit) 
	: iDeviceName(aDeviceName), iUnit(aUnit) {}
public:
	const TDesC &iDeviceName;
	TInt iUnit;
   	};
//
class TLocalDriveCaps
	{
public:
	IMPORT_C TLocalDriveCaps();
public:
	TInt64 iSize;
	TMediaType iType;
	TBatteryState iBattery;
	TUint iDriveAtt;
	TUint iMediaAtt;
    TUint8* iBaseAddress;
	TUint iFileSystemId;
	};
typedef TPckgBuf<TLocalDriveCaps> TLocalDriveCapsBuf;
//
class TLocalDriveCapsV2 : public TLocalDriveCaps
	{
public:
	TUint iHiddenSectors;
	TUint iEraseBlockSize;
    };
typedef TPckgBuf<TLocalDriveCapsV2> TLocalDriveCapsV2Buf;
//
class TFormatInfo
	{
public:
	IMPORT_C TFormatInfo();
public:
	TBool iFormatIsCurrent;
	TInt i512ByteSectorsFormatted; 
	};
//
class TLocalDriveData
	{
public:
	TLocalDriveData(TInt64& aPos,TInt *aLength) : iPos(aPos), iLength(aLength) {}
public:
	TInt64 iPos;
	TInt *iLength;
	};
//
class TLocalDriveMessageData
	{
public:
	TLocalDriveMessageData(const TAny* aPtr,TInt aHandle,TInt anOffset) : iPtr(aPtr), iHandle(aHandle), iOffset(anOffset) {}
public:
	const TAny* iPtr;
	TInt iHandle;
	TInt iOffset;
	};
//
class TPBusPasswordData
	{
public:
	TDesC8 *iCurrentPassword;
	TDesC8 *iNewPassword;
	TBool iStorePassword;
	};
typedef TPckgBuf<TPBusPasswordData> TPBusPasswordDataPckg;
//
class TBusLocalDrive : public MBusDev
	{
public:
	IMPORT_C TBusLocalDrive();
	IMPORT_C TInt Connect(TInt aDriveNumber,TBool &aChangedFlag);
	IMPORT_C void Disconnect();
	IMPORT_C TInt Enlarge(TInt aLength);
	IMPORT_C TInt ReduceSize(TInt aPos,TInt aLength);
	IMPORT_C TInt Read(TInt64 aPos,TInt aLength,const TAny* aTrg,TInt aThreadHandle,TInt anOffset);
	IMPORT_C TInt Read(TInt64 aPos,TInt aLength,TDes8& aTrg);
	IMPORT_C TInt Write(TInt64 aPos,TInt aLength,const TAny* aSrc,TInt aThreadHandle,TInt anOffset);
	IMPORT_C TInt Write(TInt64 aPos,const TDesC8& aSrc);
	IMPORT_C TInt Caps(TDes8& anInfo);
	IMPORT_C TInt Format(TFormatInfo &anInfo);
	IMPORT_C TInt Format(TInt64 aPos,TInt aLength);

	IMPORT_C TInt Unlock(TMediaPassword &aPassword, TBool aStorePassword);
	IMPORT_C TInt Lock(TMediaPassword &aOldPassword, TMediaPassword &aNewPassword, TBool aStorePassword);
	IMPORT_C TInt Clear(TMediaPassword &aPassword);
	IMPORT_C static TInt ReadPasswordData(TDes8 &aBuf);
	IMPORT_C static TInt WritePasswordData(TDesC8 &aBuf);
	IMPORT_C static TInt PasswordStoreLengthInBytes();
private:
	TInt CheckMount(const TDesC8* aMountInfo=NULL);
    void Open(TInt aStartResult,const TDesC8* aMountInfo);
private:
	TAny *iDrive;
	};
//
struct TFatUtilityFunctions; // defined in \epoc32\include\kernel\LS_STD.H
class UserExec
	{
public:
	IMPORT_C static const TFatUtilityFunctions* FatUtilityFunctions();
	};
//
class UserSvr
	{
public:
	IMPORT_C static void InitRegisterCallback(TCallBack aCallBack, TInt aPriority);
	IMPORT_C static void CaptureEventHook();
	IMPORT_C static void ReleaseEventHook();
	IMPORT_C static void RequestEvent(TRawEventBuf &anEvent,TRequestStatus &aStatus);
	IMPORT_C static void RequestEventCancel();
	IMPORT_C static TInt AddEvent(const TRawEvent& anEvent);
	IMPORT_C static void ScreenInfo(TDes8& anInfo);
//
	IMPORT_C static TInt DllGlobalAlloc(TInt aHandle,TInt aSize);
	IMPORT_C static TBool DllGlobalAllocated(TInt aHandle);
	IMPORT_C static TInt DllGlobalRead(TInt aHandle,TInt aPos,TInt aLength,TDes8 &aDes);
	IMPORT_C static TInt DllGlobalWrite(TInt aHandle,TInt aPos,const TDesC8 &aDes);
	IMPORT_C static TInt DllSetTls(TInt aHandle,TAny *aPtr);
	IMPORT_C static TAny *DllTls(TInt aHandle);
	IMPORT_C static void DllFreeTls(TInt aHandle);
	IMPORT_C static TInt DllInitialiseData(TInt aHandle);
	IMPORT_C static void DllFreeData(TInt aHandle);
	IMPORT_C static void DllFileName(TInt aHandle, TDes &aFileName);
//
	IMPORT_C static void KernelStartup(TThreadFunction aFunction);
	IMPORT_C static void FsRegisterThread(TThreadFunction aFileServer);
	IMPORT_C static void WsRegisterThread(TThreadFunction aWindowServer);
	IMPORT_C static void ServerStarted();
	IMPORT_C static void BlockThreads(TBlockType aType);
//
	IMPORT_C static TInt ProcessCreate(TLoaderInfo &anInfo, HBufC *aCommand);
	IMPORT_C static void ProcessLoaded(TLoaderInfo &anInfo);
	IMPORT_C static TInt LibraryCreateExact(TLoaderInfo &anInfo);
	IMPORT_C static void LibraryLoaded(TLoaderInfo &anInfo);
//
	static TInt StaticCallList(TInt aHandle, TInt& aCount, TUint*& aList);
	static TInt DynamicCallList(TInt aHandle, TInt& aCount, TUint*& aList);
//
    IMPORT_C static TBool TestBootSequence();
//
    IMPORT_C static void WsRegisterSwitchOnScreenHandling(TBool aState);
    IMPORT_C static void WsSwitchOnScreen();
//
    IMPORT_C static TInt ChangeLocale(RLibrary aLibrary);   
//
	IMPORT_C static TInt DllAddDependency(TAny *anImportingDll, TAny *anExportingDll);
	IMPORT_C static TInt ExeAddDependency(TAny *anImportingExe, TAny *anExportingDll);
	IMPORT_C static TInt ResetMachine(TMachineStartupType aType);
	IMPORT_C static void UnlockRamDrive();
	IMPORT_C static void LockRamDrive();
	IMPORT_C static TUint32 RomRootDirectoryAddress();

	IMPORT_C static void ForceRemountMedia(TMediaDevice aDevice);
	IMPORT_C static TInt MediaChangeNotify(TMediaDevice aDevice,TRequestStatus *aReqStat);
	IMPORT_C static TUint32 RomHeaderAddress();
	IMPORT_C static TUint32 DebugMask(); // Return the kernel debug mask

	IMPORT_C static TInt HalGet(TInt aFunction, TAny* aParam);
	IMPORT_C static TInt HalSet(TInt aFunction, TAny* aParam);

	IMPORT_C static TInt SetMemoryThresholds(TInt aLowThreshold, TInt aGoodThreshold);
	};
//
class TMaskedModifiers
	{
public:
	TUint iMask;
	TUint iValue;
	};
//
enum TPattern
	{
	EAnyKey=0x00,
	EAnyAlphaNumeric,
	EAnyAlpha,
	EAnyAlphaLowerCase,
	EAnyAlphaUpperCase,
	EAnyDecimalDigit,
	EAnyDigitGivenRadix,
	EAnyModifierKey,
	EMatchKey=0x40,
	EMatchKeyCaseInsens,
	EMatchLeftOrRight
	};
//
class TKeyCodePattern
	{
public:
	TUint16 iKeyCode;
	TInt8   iPattern;
	TInt8   iFiller;
	};
//
class TCaptureKey
	{
public:
	TMaskedModifiers iModifiers;
	TKeyCodePattern  iKeyCodePattern;
	TUint iApp;
	TUint iHandle;
	};
//
class TKeyData
	{
public:
	TInt  iModifiers;
	TInt  iApp;
	TInt  iHandle;
	TBool iIsCaptureKey;
	TUint iKeyCode;
	};
//
class CCaptureKeys: public CBase
	{
public:
	IMPORT_C CCaptureKeys();
	IMPORT_C ~CCaptureKeys();
	IMPORT_C void Construct();
	IMPORT_C void AddCaptureKeyL(const TCaptureKey &aCaptureKey);
	IMPORT_C void SetCaptureKey(TUint32 aHandle, const TCaptureKey &aCaptureKey);
	IMPORT_C void CancelCaptureKey(TUint32 aHandle);
	IMPORT_C void CancelAllCaptureKeys(TUint32 aApp);
	IMPORT_C void ProcessCaptureKeys(TKeyData &aKeyData) const;
protected:
	void CheckCaptureKey(const TCaptureKey &aCaptureKey);
	void removeCaptureKey(TUint index);
protected:
	RArray<TCaptureKey> iCKarray;
	};
//
class CKeyTranslator: public CBase
	{
public:
	IMPORT_C static CKeyTranslator *New();
	virtual TInt GetModifierState()=0;
	virtual void SetModifierState(TEventModifier aModifier,TModifierState aState)=0;
	virtual TBool TranslateKey(TUint aScanCode,TBool aKeyUp,const CCaptureKeys &aCaptureKeys,TKeyData &aKeyData)=0;
    virtual void UpdateModifiers(TInt aModifiers)=0;
    virtual TInt ChangeKeyData(const TDesC& aLibraryName)=0;
	};
//
enum TDebugExceptionType
    {
    EPanic,
    EBreakPoint,
    EException,
	ENewThread
    };
//
class DThread;
//
const TInt KMaxProfiles=64;
//
class TProfile
    {
public:
    TInt iTime;
    TInt iCount;
    };
//
struct SDebugInfo
    {
    TBuf<0x20> iCategory;
    TFullName iName;
    TThreadId iId;
    TUint iCodeAddr;
	TUint iDataAddr;
    TUint iBssSize;
    TUint iCodeSize;
    TInt iPanicType;
    TDebugExceptionType iDebugType;
    };
//
struct SRegisterInfo
    {
    TInt iNumberOfPcRegister;
    TInt iNumberOfStatusRegister;
    TInt iNumberOfRegisters;
    TInt iThreadStartRegister;
    };
//
enum TDebugFunctionNo
    {
    EDebugFunctionContinue,
    EDebugFunctionSingleStep,
    EDebugFunctionGetRegister,
    EDebugFunctionSetRegister,
    EDebugFunctionSetBreakPoint,
    EDebugFunctionClrBreakPoint,
    EDebugFunctionSetWatchPoint,
    EDebugFunctionClrWatchPoint,
    EDebugFunctionReadMemory,
    EDebugFunctionWriteMemory,
    EDebugFunctionGetException,
    EDebugFunctionSuspendThread,
    EDebugFunctionRegisterInfo,
    EDebugFunctionSupervisorMode,
    EDebugFunctionPrint,
    EDebugFunctionProfileResult,
    EDebugFunctionProfileReset,
	EDebugFunctionFault,
	EDebugFunctionReadXtalError,
	EDebugFunctionSetXtalError,
    EDebugFunctionResumeThread,
    };
//
class TDebugFunction
    {
public:
    TDebugFunctionNo iFunction;		// function to perform
    TThreadId iThread;				// thread to debug
    };
//
class RDebug
	{
public:
    IMPORT_C static TInt Open(TInt aMaxBreak=16,TInt aMaxWatch=16,TInt aMaxPanic=16,TUint aDebugLimit=0x50000000);
    IMPORT_C static TInt Close();
    IMPORT_C static TInt SetBreakPoint(const TThreadId aId,TUint aAddr);
    IMPORT_C static TInt ClrBreakPoint(const TThreadId aId,TUint aAddr);
    IMPORT_C static TInt SetWatchPoint(const TThreadId aId,TUint aAddr,TInt aLength);
    IMPORT_C static TInt ClrWatchPoint(const TThreadId aId,TUint aAddr);
    IMPORT_C static TInt GetRegister(const TThreadId aId,TInt aReg,TUint& aValue);
    IMPORT_C static TInt SetRegister(const TThreadId aId,TInt aReg,TUint aValue);
    IMPORT_C static TInt Continue(const TThreadId aId);
    IMPORT_C static TInt SingleStep(const TThreadId aId);
    IMPORT_C static TInt GetException(SDebugInfo& aReason,TRequestStatus& aStatus);
    IMPORT_C static void CancelGetException();
    IMPORT_C static TInt ReadMemory(const TThreadId aId,TUint aAddr,TDes8& aDes,TInt aLength);
    IMPORT_C static TInt WriteMemory(const TThreadId aId,TUint aAddr,TDesC8& aDes,TInt aLength);
    IMPORT_C static TInt KillThread(const TThreadId aId);
    IMPORT_C static TInt RegisterInfo(SRegisterInfo& aInfo);
    IMPORT_C static TInt Print(TRefByValue<const TDesC> aFmt,...);
    IMPORT_C static TInt SupervisorMode(TBool aState);
    IMPORT_C static TInt Fault(TInt aFault);
    IMPORT_C static TInt ProfileResult(TProfile* aProfile,TInt aStart,TInt aCount);
    IMPORT_C static TInt ProfileReset(TInt aStart,TInt aCount);
    IMPORT_C static TInt ProfileStart(TInt aProfile);
    IMPORT_C static TInt ProfileEnd(TInt aProfile);
    IMPORT_C static TInt SuspendThread(const TThreadId aId);
	IMPORT_C static TInt ReadXtalError();
	IMPORT_C static void SetXtalError(TInt anError);
    IMPORT_C static TInt ResumeThread(const TThreadId aId);
};
//
const TInt KMaxLocaleMessageText=0x80;
//
enum TLocaleMessage
	{
	EFileServer_Button1,
	EFileServer_Button2,
	EFileServer_PutTheCardBackLine1,
	EFileServer_PutTheCardBackLine2,
	EFileServer_LowPowerLine1,
	EFileServer_LowPowerLine2,
	EFileServer_DiskErrorLine1,
	EFileServer_DiskErrorLine2,
	ESoundDriver_Chimes,
	ESoundDriver_Rings,
	ESoundDriver_Signal,
	EMediaDriver_DiskNameInternal,
	EMediaDriver_DiskNameExternal1,
	EMediaDriver_DiskNameExternal2,
	EMediaDriver_DiskNameExternal3,
	EMediaDriver_DiskNameExternal4,
	EMediaDriver_DiskNameExternal5,
	EMediaDriver_DiskNameExternal6,
	EMediaDriver_DiskNameExternal7,
	EMediaDriver_DiskNameExternal8,
	EMediaDriver_SocketName0,
	EMediaDriver_SocketName1,
	EMediaDriver_SocketName2,
	EMediaDriver_SocketName3,
	ELocaleMessages_LastMsg
	};

class TLocaleMessageText : public TBuf<KMaxLocaleMessageText>
	{
public:
	IMPORT_C TLocaleMessageText();
	IMPORT_C TLocaleMessageText(TLocaleMessage aMessageNo);
	IMPORT_C void Set(TLocaleMessage aMessageNo);
	};

class TModuleInfo
	{
public:
	TInt iCodeSize;
	TInt iConstDataSize;
	TInt iDataSize;
	TInt iBssSize;
	TUint8 *iCodeRunAddress;
	TUint8 *iCodeHomeAddress;
	TUint8 *iDataRunAddress;
	TUint8 *iDataHomeAddress;
	};

#define _LOCKABLE_MEDIA

#endif

