// F32FSYS.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__F32FSYS_H__)
#define __F32FSYS_H__
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
//
#if defined(_UNICODE)
#define KFileSystemUidValue KFileSystemUidValue16
#define KFileServerUidValue KFileServerUidValue16
#define KFileServerDllUidValue KFileServerDllUidValue16
#else
#define KFileSystemUidValue KFileSystemUidValue8
#define KFileServerUidValueKFileServerUidValue8
#define KFileServerDllUidValueKFileServerDllUidValue8
#endif
const TInt KFileSystemUidValue16=0x100039df;
const TInt KFileSystemUidValue8=0x1000008f;
const TInt KFileServerUidValue16=0x100039e3;
const TInt KFileServerUidValue8=0x100000bb;
const TInt KFileServerDllUidValue16=0x100039e4;
const TInt KFileServerDllUidValue8=0x100000bd;

const TInt KLocalFileSystemUidValue=0x100000d6;
//
const TInt KMaxVolumeNameLength=11;
const TInt KFirstLocalDrive=EDriveC;
//
_LIT(KMediaPWrdFile, "c:\\system\\mmcstore");
//
enum TFileOpen {EFileOpen,EFileCreate,EFileReplace};
typedef TFileMode TShare;
//
class CMountCB;
class CFileSystem;
class CFileCB;
class CDirCB;
class CFileShare;
class CSessionFs;
//
enum TNotifierType{ENotifierCritical,ENotifierNonCritical};
//
class CAsyncNotifier : public CActive
	{
public:
	static CAsyncNotifier* New();
	~CAsyncNotifier();
	IMPORT_C TInt Notify(const TDesC& aLine1,const TDesC& aLine2,const TDesC& aButton1,const TDesC& aButton2,TInt& aButtonVal,CSessionFs* aSession);
	IMPORT_C TInt StartNotifierAndGetResponse(TUid aNotifyUid,const TDesC8& aBuffer,TDes8& aResponse,CSessionFs* aSession);
protected:
	CAsyncNotifier();
	TInt Connect(); 
	void DoCancel();
	void RunL();
	void HandleNonCriticalNotifier();
private:
	RNotifier iNotifier;
	TBool iConnected;
	};

class CNonCriticalNotifier : public CActive
	{
public:
	static CNonCriticalNotifier* New();
	~CNonCriticalNotifier();
	TInt StartNotifierAndGetResponse(TUid aNotifyUid,const TDesC8& aBuffer,TDes8& aResponse,CSessionFs* aSession);
	void CancelNonCritical();
protected:
	CNonCriticalNotifier();
	TInt Connect(); 
	void DoCancel();
	void RunL();
private:
	RNotifier iNotifier;
	TBool iConnected;
	TUid iNotifyUid;
	};

class TDrive
	{
public:
	TDrive();
	void CreateL(TInt aDriveNumber);
	TInt CheckMount();
	TInt CheckMountAndEntryName(const TDesC& aName);
	TBool ReMount();
	void MountMedia(TBool aForceMount);
	CFileCB* LocateFile(const TDesC& aName);
	void FlushCachedFileInfoL();
	void DriveInfo(TDriveInfo& anInfo);
	TInt Volume(TVolumeInfo& aVolume);
	TInt SetVolume(const TDesC& aName);
	TInt MkDir(const TDesC& aName);
	TInt RmDir(const TDesC& aName);
	TInt Delete(const TDesC& aName);
	TInt Rename(const TDesC& anOldName,const TDesC& aNewName);
	TInt Replace(const TDesC& anOldName,const TDesC& aNewName);
	TInt Entry(const TDesC& aName,TEntry& anEntry);
	TInt SetEntry(const TDesC& aName,const TTime& aTime,TUint aMask,TUint aVal);
	TInt FileTemp(TInt& aHandle,const TDesC& aPath,TDes& aName,TUint aMode);
	TInt FileOpen(TInt& aHandle,const TDesC& aName,TUint aMode,TFileOpen anOpen);
	TInt DirOpen(TInt& aHandle,const TDesC& aName,TUint anAtt,const TUidType& aUidType);
	TInt CheckDisk();
	TInt ScanDrive();
	TInt ReadFileSection(TDes& aName,TInt aPos,TAny* aTrg,TInt aLength);
	TInt GetShortName(const TDesC& aLongName,TDes& aShortName);
	TInt GetLongName(const TDesC& aShortName,TDes& aLongName);
	TInt IsFileOpen(const TDesC& aFileName,TBool& anAnswer);
	TInt IsFileInRom(const TDesC& aFileName,TUint8*& aFileStart);
	TInt LockDevice(TMediaPassword& aOld,TMediaPassword& aNew,TBool aStore);
	TInt UnlockDevice(TMediaPassword& aPassword,TBool aStore);
	TInt ClearDevicePassword(TMediaPassword& aPassword);
	TInt FreeDiskSpace(TInt64& aFreeDiskSpace);
	TBool IsWriteProtected() const;
	inline TBool IsMounted() const;
	inline TBool IsLocal() const;
	inline TBool IsRom() const;
	inline TBool IsRemovable() const;
	inline TBool IsSubsted() const;
	inline CMountCB& CurrentMount() const;
	inline TDrive& SubstedDrive() const;
	inline void SetSubstedDrive(TDrive* aDrive);
	inline HBufC& Subst() const;
	inline void SetSubst(HBufC* aSubst);
	inline CObjectCon& Mount() const;
	inline CFileSystem& FSys() const;
	inline CFileSystem*& GetFSys();
	inline CSessionFs* CurrentSession() const;
	inline void SetSession(CSessionFs* aSession);
	IMPORT_C TBool GetNotifyUser();
	IMPORT_C void SetNotifyUser(TBool aValue);
	IMPORT_C void Dismount();
	IMPORT_C TBool GetPwAndUnlock(TNotifierType aNotifier);
	IMPORT_C TBool IsWriteableResource() const;
	IMPORT_C TBool IsCurrentWriteFunction() const;
	TInt ControlIO(TInt aThreadHandle,TInt aCommand,TAny* aParam1,TAny* aParam2);
private:
	void MountMediaL(TBool aForceMount,CMountCB*& aMount);
	void SetVolumeL(const TDesC& aName,HBufC*& aBuf);
	void DirOpenL(TInt& aHandle,const TDesC& aName,TUint anAtt,const TUidType& aUidType,CDirCB*& aDir);
	void FileOpenL(TInt& aHandle,const TDesC& aName,TUint aMode,TFileOpen anOpen,CFileCB*& aFileCB,CFileShare*& aFileShare);
	TInt CheckMountAndEntryNames(const TDesC& anOldName,const TDesC& aNewName);
	CFileCB* LocateFileByPath(const TDesC& aPath);
	TInt CheckDirectories(const TDesC& anOldName,const TDesC& aNewName);
	void DoEntryL(const TDesC& aName,TEntry& anEntry);
	void ReadSectionL(const TDesC& aName,TInt aPos,TAny* aTrg,TInt aLength);
	TInt ValidateShare(TShare aShare,TShare aReqShare);
	TInt CheckAttributes(const TDesC& aName,TUint& aSetAttMask,TUint& aClearAttMask);
public:
	TInt iDriveNumber;
	TUint iAtt;
	TBool iChanged;
	TInt iReason;
	TInt iMountNumber;
	RMutex iDriveMutex;
private:
	CFileSystem* iFSys;
	CMountCB* iCurrentMount;
	TDrive* iSubstedDrive;
	HBufC* iSubst;
	CObjectCon* iMount;
	CSessionFs* iCurrentSession;
	};

class CFileCB;
class CDirCB;
class CMountCB : public CObject
	{
public:
	IMPORT_C CMountCB();
	IMPORT_C ~CMountCB();
	IMPORT_C TInt operator!=(const CMountCB& aMount) const;
	IMPORT_C TBool MatchEntryAtt(TUint anAtt,TUint aMatt) const;
	IMPORT_C void SetDiskSpaceChange(TInt64 aFreeDiskSpace);
	inline TDrive& Drive() const;
	inline void SetDrive(TDrive* aDrive);
	inline HBufC& VolumeName();
	inline void SetVolumeName(HBufC* aName);
	inline TBool GetNotifyUser() const;
	inline void SetNotifyUser(TBool aValue);
	inline void IncLock();
	inline void DecLock();
	inline TInt LockStatus();
	inline TBool IsCurrentMount();
	inline TBool Locked();
	inline TInt64 Size();
// Pure virtual
	virtual void MountL(TBool aForceMount) =0;
	virtual TInt ReMount() =0;
	virtual void Dismounted() =0;
	virtual void VolumeL(TVolumeInfo& aVolume) const =0;
	virtual void SetVolumeL(TDes& aName) =0;
	virtual void MkDirL(const TDesC& aName) =0;
	virtual void RmDirL(const TDesC& aName) =0;
	virtual void DeleteL(const TDesC& aName) =0;
	virtual void RenameL(const TDesC& anOldName,const TDesC& anNewName) =0;
	virtual void ReplaceL(const TDesC& anOldName,const TDesC& anNewName) =0;
	virtual void EntryL(const TDesC& aName,TEntry& anEntry) const =0;
	virtual void SetEntryL(const TDesC& aName,const TTime& aTime,TUint aSetAttMask,TUint aClearAttMask) =0;
	virtual void FileOpenL(const TDesC& aName,TUint aMode,TFileOpen anOpen,CFileCB* aFile) =0;
	virtual void DirOpenL(const TDesC& aName,CDirCB* aDir) =0;
	virtual void RawReadL(TInt aPos,TInt aLength,const TAny* aTrg,TInt aHandle,TInt anOffset) const = 0;
	virtual void RawWriteL(TInt aPos,TInt aLength,const TAny* aSrc,TInt aHandle,TInt anOffset) = 0;
	virtual void GetShortNameL(const TDesC& aLongName,TDes& aShortName) = 0;
	virtual void GetLongNameL(const TDesC& aShorName,TDes& aLongName) = 0;
	virtual void ReadSectionL(const TDesC& aName,TInt aPos,TAny* aTrg,TInt aLength,TInt aHandle)=0;
// virtual
	virtual TInt CheckDisk() {return(KErrNotSupported);}
	virtual TInt ScanDrive() {return(KErrNotSupported);}
	IMPORT_C virtual void IsFileInRom(const TDesC& aFileName,TUint8*& aFileStart);
	virtual TInt ControlIO(TInt /*aThreadHandle*/,TInt /*aCommand*/,TAny* /*aParam1*/,TAny* /*aParam2*/)  {return(KErrNotSupported);}
	virtual TInt Lock(TMediaPassword& /*aOld*/,TMediaPassword& /*aNew*/,TBool /*aStore*/) {return(KErrNotSupported);}
	virtual TInt Unlock(TMediaPassword& /*aPassword*/,TBool /*aStore*/) {return(KErrNotSupported);}
	virtual TInt ClearPassword(TMediaPassword& /*aPassword*/) {return(KErrNotSupported);}
//
	virtual void CMountCB_Reserved1(){};
protected:
	TInt iMountNumber;
	TUint iUniqueID;
	TInt64 iSize;
	TDblQue<CFileCB> iMountQ;
	friend class TDrive;
private:
	TInt iLockMount;
	TDrive* iDrive;
	HBufC* iVolumeName;
//
	TAny* CMountCB_Reserved;
	};
//
class CFileShare;
struct SFileShareLock
	{
	CFileShare* owner;
	TInt posLow;
	TInt posHigh;
	};
//
class CFileCB : public CObject
	{
public:
	IMPORT_C CFileCB();
	IMPORT_C ~CFileCB();
	inline TDrive& Drive();
	inline void SetDrive(TDrive* aDrive);
	inline TDrive& CreatedDrive();
	inline void SetCreatedDrive(TDrive* aDrive);
	inline CMountCB& Mount();
	inline void SetMount(CMountCB* aMount);
	inline HBufC& FileName();
	inline void SetFileName(HBufC* aName);
	inline RArray<SFileShareLock>& Lock();
	inline void SetLock(RArray<SFileShareLock>* aLock);	
	inline TInt UniqueID() const;
	TInt FindLock(TInt aPosLow,TInt aPosHigh);
	TInt AddLock(CFileShare* aFileShare,TInt aPos,TInt aLength);
	TInt RemoveLock(CFileShare* aFileShare,TInt aPos,TInt aLength);
	TInt CheckLock(CFileShare* aFileShare,TInt aPos,TInt aLength);
	void RemoveLocks(CFileShare* aFileShare);
	inline TShare Share();
	inline void SetShare(TShare aShare);
	inline TInt Size();
	inline void SetSize(TInt aSize);
	inline TInt Att();
	inline void SetAtt(TInt aAtt);
	inline TTime Modified();
	inline void SetModified(TTime aModified);
	inline TBool FileCorrupt();
	inline void SetFileCorrupt(TBool aFileCorrupt);
	inline TBool BadPower();
	inline void SetBadPower(TBool aBadPower);
// Pure virtual
	virtual void RenameL(const TDesC& aNewName) =0;
	virtual void ReadL(TInt aPos,TInt& aLength,const TAny* aDes,TInt aThreadHandle) =0;
	virtual void WriteL(TInt aPos,TInt& aLength,const TAny* aDes,TInt aThreadHandle) =0;
	virtual void SetSizeL(TInt aSize) =0;
	virtual void SetEntryL(const TTime& aTime,TUint aMask,TUint aVal) =0;
	virtual void FlushDataL() =0;
	virtual void FlushAllL() =0;
	IMPORT_C virtual TInt Address(TInt& aPos) const;
	IMPORT_C void SetArchiveAttribute();
protected:
	TShare iShare;
	TInt iSize;
	TInt iAtt;
	TTime iModified;
	TBool iFileCorrupt;
	TBool iBadPower;
	friend class TDrive;
public:
	HBufC* iFileName;
private:
	TDrive* iCreatedDrive;
	TDrive* iDrive;
	CMountCB* iMount;
	RArray<SFileShareLock>* iLock;
	TDblQueLink iMountLink;
	friend class CMountCB;
	};
//
class CFileShare : public CObject
	{
public:
	CFileShare(CFileCB* aFileCB, CSessionFs* aSession);
	~CFileShare();
	TInt CheckMount();
	inline CFileCB& File();
	inline void SetFile(CFileCB* aFile);
public:
	TUint iMode;
	TInt iPos;
private:
	CFileCB* iFile;
	};
//
class CDirCB : public CObject
	{
public:
	IMPORT_C CDirCB();
	IMPORT_C ~CDirCB();
	TInt CheckMount();
	inline TDrive& Drive();
	inline void SetDrive(TDrive* aDrive);
	inline CMountCB& Mount();
	inline void SetMount(CMountCB* aMount);
	inline TBool Pending();
	inline void SetPending(TBool aPending);
// Pure virtual
	virtual void ReadL(TEntry& anEntry) =0;
public:
	IMPORT_C virtual void StoreLongEntryNameL(const TDesC& aName);
protected:
	TUint iAtt;
	TUidType iUidType;
	TBool iPending;
	friend class TDrive;
private:
	TDrive* iDrive;
	CMountCB* iMount;
	};
//
class CFormatCB : public CObject
	{
public:
	IMPORT_C CFormatCB();
	IMPORT_C ~CFormatCB();
	IMPORT_C TInt CheckMount();
	inline TDrive& Drive();
	inline void SetDrive(TDrive* aDrive);
	inline CMountCB& Mount();
	inline void SetMount(CMountCB* aMount);
	inline TFormatMode Mode();
	inline void SetMode(TFormatMode aMode);
	inline TInt& CurrentStep();
// Pure virtual
	virtual void DoFormatStepL() =0;
protected:
	TInt iCurrentStep;
	TFormatMode iMode;
private:
	TDrive* iDrive;
	CMountCB* iMount;
	};
//
class CRawDiskCB : public CObject
	{
public:
	CRawDiskCB(CMountCB* iMount,TBool aIsWriteProtected);
	~CRawDiskCB();
	inline CMountCB& Mount();
	inline TDrive& Drive();
	inline TBool IsWriteProtected() const;
private:
	CMountCB* iMount;
	TBool iIsWriteProtected;
	};
//
class CFileSystem : public CObject
	{
public:
	IMPORT_C CFileSystem();
	IMPORT_C ~CFileSystem();
	IMPORT_C virtual TInt Remove();
	IMPORT_C virtual TBool QueryVersionSupported(const TVersion& aVer) const;
	IMPORT_C void SetLibrary(RLibrary aLib);
// Pure virtual
	virtual TInt Install() =0;
	virtual CMountCB* NewMountL() const =0;
	virtual CFileCB* NewFileL() const =0;
	virtual CDirCB* NewDirL() const =0;
	virtual CFormatCB* NewFormatL() const =0;
	virtual void DriveInfo(TDriveInfo& anInfo,TInt aDriveNumber) const =0;
	virtual TInt DefaultPath(TDes& aPath) const;
	virtual TInt DriveList(TDriveList& aList) const;
protected:
	TVersion iVersion;
private:
	RLibrary iLibrary;
	};
//
IMPORT_C TBusLocalDrive& LocalDrive(TInt aLocalDrive);
IMPORT_C void AllocBufferL(HBufC*& aBuf,const TDesC& aDes);
IMPORT_C TBool FileNamesIdentical(const TDesC& aFileName1,const TDesC& aFileName2);
IMPORT_C CAsyncNotifier& TheNotifier();
IMPORT_C TBool FileServerIsHung();
IMPORT_C TBool IsDriveHung(const TDrive& aDrive);
IMPORT_C void DebugNotifySessions(TInt aFunction,TInt aDrive);
IMPORT_C void WriteToDisk(const TDesC& aFileName,const TDesC8& aBuf);
/** @deprecated 6.1 */
IMPORT_C TInt CompareFilenames(const TDesC& aFileName1,const TDesC& aFileName2);
//
#include <f32fsys.inl>
#endif
