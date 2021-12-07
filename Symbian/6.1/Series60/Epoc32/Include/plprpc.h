// PLPRPC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPRPC_H__)
#define __PLPRPC_H__

#if !defined (__PLPRFILE_H__)
#include <plprfile.h>
#endif

#if !defined (__PLPSESS_H__)
#include <plpsess.h>
#endif

#if !defined (__E32HAL_H__)
#include <e32hal.h>
#endif

#if !defined(__PLPVAR_H__)
#include <plpvar.h>
#endif

enum TRpcMachineType
    {

    EMachineUnknown,
    EMachinePc,
    EMachineMc,
    EMachineHc,
    EMachineS3,
    EMachineS3a,
    EMachineWorkabout,
    EMachineSienna,
    EMachineOak,
    EMachineProtea=32,
	EMachineWinc
    };

class TRpcTime
    {
public:
    TTime iHomeTime;
    TInt iCountryCode;
	TTimeIntervalSeconds iUniversalTimeOffset;
    TUint iDaylightSaving;
	TDaylightSavingZone iHomeDaylightSavingZone;
    };

class TRpcMachineInfo
    {
public:

    TRpcMachineType iMachineType;
// From TMachineInfoV1
    TVersion iRomVersion;
	TBuf<KMaxInfoName> iMachineName;
    TSize iDisplaySizeInPixels;
// Time
    TRpcTime iTime;
// From the E32Hal
    TMemoryInfoV1 iMemoryInfo;
// From User
    TLanguage iLanguage;
	TPlpVariantMachineId iMachineId;
    };

typedef TPckgBuf<TRpcMachineInfo> TRpcMachineInfoBuf;

const TInt KRpcMajorVersion     = 1;
const TInt KRpcMinorVersion     = 20;

const TInt KSiboMaxOwnerInfoSize = 50;
const TInt KSiboMaxOwnerInfoLines = 4;
const TInt KSiboMaxOwnerInfoSizeZ = KSiboMaxOwnerInfoSize+2;
const TInt KEraMaxOwnerInfoSize = 512;

typedef TBuf<KEraMaxOwnerInfoSize> TOwnerInfoBuf;

const TInt KMaxQueryDriveSize = MAX_DATACHUNK_SIZE;

class RRemoteRpc;
class TRemoteQueryDrive
    {
friend class RRemoteRpc;
public:
    inline TRemoteQueryDrive();
    IMPORT_C TInt Count() const;
    IMPORT_C TPtrC App(TInt aNo) const;
    IMPORT_C TPtrC Document(TInt aNo) const;
private:
    TInt iCount;
    TInt iIndex;
    TText* iPos;
    TBuf<KMaxQueryDriveSize*sizeof(TText)> iBuf;
    };

const TInt KMaxPlpRegistryItemName=0x20;
const TInt KMaxPlpRegistryItemValue=0x200;
const TInt KMaxPlpRegistryArraySize = MAX_DATACHUNK_SIZE;

class TRemoteRegArray;
class TRemoteRegEntry
    {
friend class TRemoteRegArray;

public:
    inline TUid Category() const;
    inline TPtrC8 Name() const;
    inline TPtrC8 Value() const;
    inline static TInt Size(const TRemoteRegEntry& aEntry);

private:
    inline TText8* ValueOffset() const;

    TUid iCategory;
    TInt iNameLength;
    TInt iValueLength;
    TText8 iName[__Align(KMaxPlpRegistryItemName)];
    TText8 iValuePadding[__Align(KMaxPlpRegistryItemValue)];
    };

typedef TPckgBuf<TRemoteRegEntry> TRemoteRegEntryBuf;

class TRemoteRegArray
	{
friend class RRemoteRpc;

public:
	inline TRemoteRegArray();
	IMPORT_C TInt Count() const;
	IMPORT_C const TRemoteRegEntry& operator[](TInt anIndex) const;

private:
	TInt iCount;
	TInt iIndex;
	const TRemoteRegEntry* iPos;
	TBuf8<KMaxPlpRegistryArraySize> iBuf;
    };

const TUint KDefaultRpcSlots=1;
#define KRemoteRegCategoryAny TUid::Uid(-1)

class RRemoteRpc : public RRemoteSessionBase
    {
    
public:
    IMPORT_C TInt Open(TUint aInterface=KPlpInterfaceDevice0, TInt aMessageSlots=KDefaultRpcSlots);
    IMPORT_C TVersion Version() const;
    IMPORT_C void MachineType(TRequestStatus& aStatus, TDes8& aMachineType);
    IMPORT_C void QueryVersion(TRequestStatus& aStatus, TDes8& aQueryVersion);
    IMPORT_C void Quit(TRequestStatus& aStatus);
    IMPORT_C void UniqueID(TRequestStatus& aStatus, TDes8& aId, TInt aDrive);
    IMPORT_C void FormatOpen(TRequestStatus& aStatus, TDes8& aHandle, TDes8& aCount, TInt aDrive, TFormatMode aMode=EFullFormat);
    IMPORT_C void FormatStep(TRequestStatus& aStatus, TUint aHandle);
    IMPORT_C void OwnerInfo(TRequestStatus& aStatus, TDesC& aOwnerInfo);
    IMPORT_C void StopDocument(TRequestStatus& aStatus, const TDesC& aDocument);
    IMPORT_C void StartDocument(TRequestStatus& aStatus, const TDesC& aDocument, const TDesC& aArgs);
    IMPORT_C void DocumentRunning(TRequestStatus& aStatus, const TDesC& aDocument);
    IMPORT_C void RegOpenIter(TRequestStatus& aStatus, TDes8& aHandle, TUid aCategory, const TDesC8& aMatch);
    IMPORT_C void RegReadIter(TRequestStatus& aStatus, TRemoteRegArray& aArray, TUint aHandle);
    IMPORT_C void RegWrite(TRequestStatus& aStatus, TUid aCategory, const TDesC8& aName, const TDesC8& aValue);
    IMPORT_C void RegRead(TRequestStatus& aStatus, TDes8& aEntry, TUid aCategory, const TDesC8& aMatch);
    IMPORT_C void RegDelete(TRequestStatus& aStatus, TUid aCategory, const TDesC8& aMatch);
    IMPORT_C void MachineInfo(TRequestStatus& aStatus, TDes8& aMachineInfo);
    IMPORT_C void SetTime(TRequestStatus& aStatus, const TDesC8& aRpcTime);
	IMPORT_C void ConfigOpen(TRequestStatus& aStatus, TDes8& aHandle, TDes8& aSize);
    IMPORT_C void ConfigRead(TRequestStatus& aStatus, TDes8& aBuffer, TUint aHandle);
    IMPORT_C void ConfigWrite(TRequestStatus& aStatus, const TDesC8& aBuffer, TUint aHandle);
    IMPORT_C void QueryOpen(TRequestStatus& aStatus, TDes8& aHandle, TInt aDrive);
	IMPORT_C void QueryRead(TRequestStatus& aStatus, TRemoteQueryDrive& aQuery, TUint aHandle);
	IMPORT_C void CommandLine(TRequestStatus& aStatus, const TDesC& aApp, TDes& aCommandLine);
//
	IMPORT_C void GetRemoteConnectReason(TRequestStatus& aStatus, TPckgBuf<TRemoteLinkConnectReason>& aReason);
//
// PLP Variant DLL functions
//
	IMPORT_C void GetDriveAlias(TRequestStatus& aStatus, TDriveNumber aDrive, TPlpVariantDriveAlias& aAlias);
	IMPORT_C void GetDriveId(TRequestStatus& aStatus, TDriveNumber aDrive, TPlpVariantDriveId& aDriveId);
	IMPORT_C void GetDriveStatus(TRequestStatus& aStatus, TDriveNumber aDrive, TPckgBuf<TBool>& aDriveStatus);
	IMPORT_C void GetDriveLocked(TRequestStatus& aStatus, TDriveNumber aDrive, TPckgBuf<TBool>& aDriveLocked);
	IMPORT_C void GetProperty(TRequestStatus& aStatus, TUint32 uid, TDesC& aProperty);
	IMPORT_C void SetProperty(TRequestStatus& aStatus, TUint32 uid, TDes& aProperty);
	IMPORT_C void GetMachineId(TRequestStatus& aStatus, TPlpVariantMachineId& aMachineId);
	IMPORT_C void GetDefaultDocumentLocation(TRequestStatus& aStatus, TPath& aDriveAndPath);
    };

#define RPC_SHUTDOWN_STRING _L("$ShutDown")

#include <plprpc.inl>

#endif

