// PLPRFILE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPRFILE_H__)
#define __PLPRFILE_H__


#if !defined (__PLPSVR_H__)
#include <plpsvr.h>
#endif

#include <f32file.h>
#include <plpsize.h>
#include <plpvar.h>
#include <apmstd.h>

const TInt KRemoteEntryArraySize = MAX_DATACHUNK_SIZE;
const TInt KMaxRFilePduSize = MAX_DATACHUNK_SIZE + 31;
const TInt KMaxRFilePduSize16 = 858;
//
const TInt KMaxShortName = 12;

class CRemFileSystem16;
class CRemOpenDir32;
class TRemoteEntry
    {

friend class CRemFileSystem16;
friend class CRemOpenDir32;

public:
    inline const TEntry& Entry() const;
    inline TPtrC ShortName() const;
    inline TBool HasShortName() const;
	inline TPtrC8 DataType() const;
	inline TBool HasDataType() const;
    inline static TInt Size(const TRemoteEntry &aEntry);
private:
    inline TText* ShortNameOffset() const;
	inline TText8* DataTypeOffset() const;
    TInt iShortNameLength;
	TInt iDataTypeLength;
    TEntry iEntry;
    TText __iShortNamePadding[__Align(KMaxShortName)];
	TText8 __iDataType[__Align(KMaxDataTypeLength)];
    };

class TPlpVolumeInfo : public TVolumeInfo
{
public:
	TPlpVariantDriveId iDriveId;
	TPlpVariantDriveAlias iDriveAlias;
};

class RRemoteFileSystem;
class TRemoteEntryArray
	{
friend class RRemoteFileSystem;

public:
	inline TRemoteEntryArray();
	IMPORT_C TInt Count() const;
	IMPORT_C const TRemoteEntry& operator[](TInt anIndex) const;
private:
	TInt iCount;
	TInt iIndex;
	const TRemoteEntry* iPos;
	TBuf8<KRemoteEntryArraySize*sizeof(TText)> iBuf;
    };

class RRemoteSessionBase : public RSessionBase
    {
    
public:
    IMPORT_C TInt IsConnected(TRemoteLinkStatus& aStatus);
    IMPORT_C void WaitForConnect(TRequestStatus &aStatus, TRemoteLinkStatusBuf& aBuf);
    IMPORT_C void Cancel(TRequestStatus &aStatus);
    IMPORT_C void CancelAll();
    IMPORT_C TInt SetWatchDogTimer(TTimeIntervalMicroSeconds32 aTime);
    IMPORT_C void CloseHandle(TRequestStatus &aStatus, TUint aHandle);
    };

class TQueryVersion
    {
public:
    inline TQueryVersion();
    inline TQueryVersion(TInt aMajor, TInt aMinor);
    inline TBool IsSupported();
public:
	TInt8 iMajor;
	TInt8 iMinor;
private:
	TInt16 iIsSupported;
    };

typedef TPckgBuf<TQueryVersion> TQueryVersionBuf;

const TInt KDefaultRemoteSlots = 1;

typedef TPckgBuf<TUidType> TUidTypeBuf;

class RRemoteFileSystem : public RRemoteSessionBase
    {
    
public:
    IMPORT_C TInt Open(TUint aInerface=KPlpInterfaceDevice0, TInt aMessageSlots=KDefaultRemoteSlots);
    IMPORT_C void OpenDir(TRequestStatus& aStatus,  TDes8& aHandle, const TDesC& aMatchName, TUint anEntryAttMask);
	IMPORT_C void OpenDir(TRequestStatus& aStatus, TDes8& aHandle, const TDesC& aMatchName, const TUidTypeBuf& aUidType);
    IMPORT_C void ReadDir(TRequestStatus& aStatus, TRemoteEntryArray& aArray, TUint aHandle);
    IMPORT_C void GetDriveList(TRequestStatus& aStatus, TDriveList &aDriveList);
	IMPORT_C void Volume(TRequestStatus& aStatus, TDes8& aVolInfo, TInt aDrive);
	IMPORT_C void SetVolumeLabel(TRequestStatus& aStatus, const TDesC& aName, TInt aDrive);
    IMPORT_C void OpenFile(TRequestStatus& aStatus, TDes8& aHandle, const TDesC& aName, TUint aFileMode);
    IMPORT_C void CreateFile(TRequestStatus& aStatus, TDes8& aHandle, const TDesC& aName, TUint aFileMode);
    IMPORT_C void ReplaceFile(TRequestStatus& aStatus, TDes8& aHandle, const TDesC& aName, TUint aFileMode);
    IMPORT_C void TempFile(TRequestStatus& aStatus, TDes8& aHandle, TDes& aName,  const TDesC& aPath, TUint aFileMode);
    IMPORT_C void ReadFile(TRequestStatus& aStatus, TDes8& aDes, TUint aHandle);
    IMPORT_C void WriteFile(TRequestStatus& aStatus, const TDesC8& aDes, TUint aHandle);
    IMPORT_C void SeekFile(TRequestStatus& aStatus, TDes8& aOffset, TSeek aMode, TUint aHandle); 
    IMPORT_C void Delete(TRequestStatus& aStatus, const TDesC& aName);
    IMPORT_C void RemoteEntry(TRequestStatus& aStatus, TDes8& aRemoteEntry, const TDesC& aName);
    IMPORT_C void Flush(TRequestStatus& aStatus, TUint aHandle);
    IMPORT_C void SetSize(TRequestStatus& aStatus, TInt aSize, TUint aHandle);
    IMPORT_C void Rename(TRequestStatus& aStatus, const TDesC& anOldName, const TDesC& aNewName);
    IMPORT_C void MkDirAll(TRequestStatus& aStatus, const TDesC& aPath);
	IMPORT_C void RmDir(TRequestStatus& aStatus, const TDesC& aPath);
	IMPORT_C void SetAtt(TRequestStatus& aStatus, const TDesC& aName,TUint aSetAttMask,TUint aClearAttMask);
    IMPORT_C void Att(TRequestStatus& aStatus, const TDesC& aName, TDes8& aAtt);
	IMPORT_C void SetModified(TRequestStatus& aStatus, const TDesC& aName, const TTime& aTime);
    IMPORT_C void Modified(TRequestStatus& aStatus, const TDesC& aName, TDes8& aTime);
    IMPORT_C void SetSessionPath(TRequestStatus& aStatus, const TDesC& aPath);
    IMPORT_C void SessionPath(TRequestStatus& aStatus, TDes& aPath);
    IMPORT_C void PathTest(TRequestStatus& aStatus, const TDesC& aPath);
    IMPORT_C void ReadWriteFile(TRequestStatus& aStatus, TDes8& aNumBytes, TUint aDst, TUint aSrc);
    IMPORT_C void Lock(TRequestStatus& aStatus, TInt aPos, TInt aLength, TUint aHandle);
    IMPORT_C void UnLock(TRequestStatus& aStatus, TInt aPos, TInt aLength, TUint aHandle);
	IMPORT_C void DriveName(TRequestStatus& aStatus, TDes& aDriveName, TInt aDrive);
	IMPORT_C void SetDriveName(TRequestStatus& aStatus, const TDesC& aDriveName, TInt aDrive);
	IMPORT_C void Replace(TRequestStatus& aStatus, const TDesC& anOldName, const TDesC& aNewName);
    IMPORT_C TVersion Version() const;
    };

class CPlpLinkMonitorClient : public CPlpClient
	{
public:
	enum TErrorEventEx { EPlpEventWaitForLink = EPlpEventReconnect+1 };
	IMPORT_C void WaitForLinkL();
	IMPORT_C virtual void InitL();
	IMPORT_C virtual void RunL();
	IMPORT_C virtual void DoCancel();
	IMPORT_C ~CPlpLinkMonitorClient();

protected:
	enum TStateEx { EWaitingForLink=EConnected+1 };
	IMPORT_C CPlpLinkMonitorClient();

private:

	RRemoteLink iRemoteLink;
	TRemoteLinkStatusBuf iBuf;
	};

#define REMOTEFILE_SERVERNAME _L("RemoteFileServer")

#include <plprfile.inl>

#endif
