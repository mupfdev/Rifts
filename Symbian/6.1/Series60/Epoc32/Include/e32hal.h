// E32HAL.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __E32HAL_H__
#define __E32HAL_H__
#include <e32std.h>

const TInt KMaxRomDevices=8;

enum TDigitizerCalibrationType
    {
    EFactory,
    ESaved
    };

class TDigitizerCalibration
    {
public:
    TPoint iTl;
    TPoint iBl;
    TPoint iTr;
    TPoint iBr;
    };

/**
 * The reason that the device last reset
 *
 * Note that not all reasons can occur on all devices.
 *
 * @public
 * @deprecated 6.0 Use HAL::Get() from the HAL library instead with attributes ESystemStartupReason
 */
enum TMachineStartupType
	{
	EStartupCold,EStartupColdReset,EStartupNewOs,
	EStartupPowerFail,EStartupWarmReset,EStartupKernelFault,
	EStartupSafeReset
	};

/**
 * The XY input method supported
 *
 * @public
 * @deprecated 6.0 Use HAL::Get() from the HAL library instead with attributes EPen or EMouse
 */
enum TXYInputType
	{
	EXYInputNone,
	EXYInputPointer,
	EXYInputMouse,
	EXYInputDeltaMouse
	};

/**
 * Miscellaneous machine info
 *
 * @public
 * @deprecated 6.0 Use the HAL class from the HAL library instead
 */
class TMachineInfoV1
	{
public:
	TVersion iRomVersion;
	TXYInputType iXYInputType;
	TBool iKeyboardPresent;
	TBool iBacklightPresent;
    TSize iDisplaySizeInPixels;
    TSize iXYInputSizeInPixels;
    TSize iPhysicalScreenSize;
	TPoint iOffsetToDisplayInPixels;
	TInt iKeyboardId;
	TInt iDisplayId;
	TInt64 iMachineUniqueId;
    TUint iLedCapabilities;
    TInt iProcessorClockInKHz;
    TInt iSpeedFactor;
    TInt iMaximumDisplayColors;
	};
typedef TPckgBuf<TMachineInfoV1> TMachineInfoV1Buf;

/**
 * Miscellaneous locale info
 *
 * @public
 * @deprecated 6.0 Use HAL::Get() from the HAL library instead with attributes ELanguageIndex or EKeyboardIndex
 */
class TMachineInfoV2 : public TMachineInfoV1
	{
public:
	TInt iLanguageIndex;
    TInt iKeyboardIndex;
    };
typedef TPckgBuf<TMachineInfoV2> TMachineInfoV2Buf;

/**
 * Miscellaneous memory info
 *
 * @public
 * @deprecated 6.0 Use HAL::Get() from the HAL library instead with attributes EMemoryRAM, EMemoryRAMFree or EMemoryROM
 */
class TMemoryInfoV1
    {
public:
    TInt iTotalRamInBytes;
    TInt iTotalRomInBytes;
    TInt iMaxFreeRamInBytes;
    TInt iFreeRamInBytes;
    TInt iInternalDiskRamInBytes;
    TBool iRomIsReprogrammable;
    };
typedef TPckgBuf<TMemoryInfoV1> TMemoryInfoV1Buf;

/**
 * Miscellaneous ROM info
 *
 * @public
 * @deprecated 6.0 No replacement
 */
class TRomInfoEntryV1
	{
public:
    enum TRomTypeV1
    	{
    	ERomTypeRom=0,
    	ERomTypeFlash=1
    	};
	TInt iSize;		    // size of ROM in bytes, 0=no ROM present
	TInt iWidth;		// bus width in bits
	TInt iSpeed;		// number of wait states
	TRomTypeV1 iType;	// 0=ROM, 1=FLASH
	};

/**
 * Miscellaneous ROM info
 *
 * @public
 * @deprecated 6.0 No replacement
 */
class TRomInfoV1
	{
public:
	TRomInfoEntryV1	iEntry[KMaxRomDevices];
	};
typedef TPckgBuf<TRomInfoV1> TRomInfoV1Buf;

const TUint KRuggedFileSystem=0x01;
class TDriveInfoV1
    {
public:
	TInt iTotalSupportedDrives;
	TInfoName iDriveName[KMaxLocalDrives];
	TInt iTotalSockets;
	TInfoName iSocketName[KMaxPBusSockets];
	TInt iRuggedFileSystem;
	};
typedef TPckgBuf<TDriveInfoV1> TDriveInfoV1Buf;

class TExcInfo
	{
public:
	TAny *iCodeAddress;
	TAny *iDataAddress;
	TInt iExtraData;
	};

/**
 * Miscellaneous system info
 *
 * @public
 * @deprecated 6.0 Use the HAL class from the HAL library instead
 */
class UserHal
	{
public:
	IMPORT_C static TInt MachineInfo(TDes8& anInfo);
	IMPORT_C static TInt MemoryInfo(TDes8& anInfo);
	IMPORT_C static TInt DriveInfo(TDes8& anInfo);
	IMPORT_C static TInt RomInfo(TDes8& anInfo);
	IMPORT_C static TInt StartupReason(TMachineStartupType& aReason);
	IMPORT_C static TInt FaultReason(TInt &aReason);
	IMPORT_C static TInt ExceptionId(TInt &anId);
	IMPORT_C static TInt ExceptionInfo(TExcInfo &aInfo);
	IMPORT_C static TInt PageSizeInBytes(TInt& aSize);
	IMPORT_C static TInt TickPeriod(TTimeIntervalMicroSeconds32& aPeriod);
   	IMPORT_C static TInt SwitchOff();
	IMPORT_C static TInt SetXYInputCalibration(const TDigitizerCalibration& aCalibration);
	IMPORT_C static TInt CalibrationPoints(TDigitizerCalibration& aCalibration);
	IMPORT_C static TInt SaveXYInputCalibration();
	IMPORT_C static TInt RestoreXYInputCalibration(TDigitizerCalibrationType aType);
	};
#endif

