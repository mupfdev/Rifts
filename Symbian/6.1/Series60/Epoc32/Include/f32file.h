// F32FILE.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__F32FILE_H__)
#define __F32FILE_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__E32SVR_H__)
#include <e32svr.h>
#endif
//
const TInt KDefaultDrive=KMaxTInt;
const TInt KDriveAbsent=0x00;
const TInt KFileServerDefaultMessageSlots=4;
const TInt KEntryArraySize=(0x200*sizeof(TText));
const TInt KPathDelimiter='\\';
const TInt KDriveDelimiter=':';
const TInt KExtDelimiter='.';
//
const TInt KMaxDrives=26;
typedef TBuf8<KMaxDrives> TDriveList;
const TInt KMaxDriveName=0x02;
typedef TBuf<KMaxDriveName> TDriveName;
//
const TUint KEntryAttNormal=0x0000;
const TUint KEntryAttReadOnly=0x0001;
const TUint KEntryAttHidden=0x0002;
const TUint KEntryAttSystem=0x0004;
const TUint KEntryAttVolume=0x0008;
const TUint KEntryAttDir=0x0010;
const TUint KEntryAttArchive=0x0020;
const TUint KEntryAttMatchMask=(KEntryAttHidden|KEntryAttSystem|KEntryAttDir);
const TUint KEntryAttMaskSupported=0x3f;
//
const TUint KEntryAttMatchExclusive=0x40000000;
const TUint KEntryAttMatchExclude=0x08000000;
const TUint KEntryAttAllowUid=0x10000000;
//
const TUint KDebugNotifyMask=0xFF000000; // Reserved for debug notification
enum TNotifyType {ENotifyEntry=0x00,ENotifyAll=0x01,ENotifyFile=0x04,ENotifyDir=0x08,
				  ENotifyAttributes=0x10,ENotifyWrite=0x20,ENotifyDisk=0x40};

//
enum TDriveNumber
	{
	EDriveA,   EDriveB,   EDriveC,   EDriveD,   EDriveE,
	EDriveF,   EDriveG,   EDriveH,   EDriveI,   EDriveJ,
	EDriveK,   EDriveL,   EDriveM,   EDriveN,   EDriveO, 
	EDriveP,   EDriveQ,   EDriveR,   EDriveS,   EDriveT,
	EDriveU,   EDriveV,   EDriveW,   EDriveX,   EDriveY,
	EDriveZ
	};
//
enum TEntryKey
	{
	ESortNone=0,ESortByName,ESortByExt,ESortBySize,ESortByDate,ESortByUid,
	EDirsAnyOrder=0,EDirsFirst=0x100,EDirsLast=0x200,
	EAscending=0,EDescending=0x400,EDirDescending=0x800
	};
//
enum TFileMode
	{
	EFileShareExclusive,EFileShareReadersOnly,EFileShareAny,
	EFileStream=0,EFileStreamText=0x100,
	EFileRead=0,EFileWrite=0x200
	};
//
const TUint KFileShareMask=0xff;
//
enum TFormatMode 
	{
	EHighDensity,ELowDensity,
	EFullFormat=0,EQuickFormat=0x100
	};
//
enum TSeek {ESeekAddress,ESeekStart,ESeekCurrent,ESeekEnd};
//
class TEntry
	{
public:
	IMPORT_C TEntry();
	IMPORT_C TEntry(const TEntry& aEntry);
	IMPORT_C TEntry& operator=(const TEntry& aEntry);
	IMPORT_C TBool IsReadOnly() const;
	IMPORT_C TBool IsHidden() const;
	IMPORT_C TBool IsSystem() const;
	IMPORT_C TBool IsDir() const;
	IMPORT_C TBool IsArchive() const;
	inline const TUid& operator[](TInt anIndex) const;
	inline TBool IsUidPresent(TUid aUid) const;
	inline TBool IsTypeValid() const;
	inline TUid MostDerivedUid() const;
public:
	TUint iAtt;
	TInt iSize;
	TTime iModified;
	TUidType iType;
	TBufC<KMaxFileName> iName;
	};
//
class TEntryArray
	{
public:
	IMPORT_C TEntryArray();
	IMPORT_C TInt Count() const;
	IMPORT_C const TEntry& operator[](TInt anIndex) const;
private:
	TInt iCount;
	TInt iIndex;
	const TEntry* iPos;
	TBuf8<KEntryArraySize> iBuf;
	friend class RDir;
	friend class RFs;
	};
//
class TDriveInfo
	{
public:
	TMediaType iType;
	TBatteryState iBattery;
	TUint iDriveAtt;
	TUint iMediaAtt;
	};
//
class TVolumeInfo
	{
public:
	IMPORT_C TVolumeInfo();
	TDriveInfo iDrive;
	TUint iUniqueID;
	TInt64 iSize;
	TInt64 iFree;
	TBufC<KMaxFileName> iName;
	};
//
class TDriveUnit
	{
public:
	inline TDriveUnit() {};
	IMPORT_C TDriveUnit(TInt aDrive);
	IMPORT_C TDriveUnit(const TDesC& aDrive);
	IMPORT_C TDriveUnit& operator=(TInt aDrive);
	IMPORT_C TDriveUnit& operator=(const TDesC& aDrive);
	inline operator TInt() const;
	IMPORT_C TDriveName Name() const;
private:
	TInt iDrive;
	};
//
class RFs;
//
class TParseBase
	{
private:
	struct SField {TUint8 pos;TUint8 len;TUint8 present;TUint8 filler;};
	enum TField {EDrive,EPath,EName,EExt,EMaxFields};
	enum TWild {EWildName=0x01,EWildExt=0x02,EWildEither=0x04,EIsRoot=0x08,EWildIsKMatchOne=0x10,EWildIsKMatchAny=0x20};
public:
	IMPORT_C TParseBase();
	IMPORT_C TInt PopDir();
	IMPORT_C TInt AddDir(const TDesC& aName);
	IMPORT_C const TDesC& FullName() const;
	IMPORT_C TPtrC Drive() const;
	IMPORT_C TPtrC Path() const;
	IMPORT_C TPtrC DriveAndPath() const;
	IMPORT_C TPtrC Name() const;
	IMPORT_C TPtrC Ext() const;
	IMPORT_C TPtrC NameAndExt() const;
	IMPORT_C TBool DrivePresent() const;
	IMPORT_C TBool PathPresent() const;
	IMPORT_C TBool NamePresent() const;
	IMPORT_C TBool ExtPresent() const;
	IMPORT_C TBool NameOrExtPresent() const;
	IMPORT_C TBool IsRoot() const;
	IMPORT_C TBool IsWild() const;
	IMPORT_C TBool IsKMatchOne() const;
	IMPORT_C TBool IsKMatchAny() const;
	IMPORT_C TBool IsNameWild() const;
	IMPORT_C TBool IsExtWild() const;
protected:
	virtual TDes& NameBuf() = 0;
	virtual const TDesC& NameBufC() const = 0;
	TInt Set(const TDesC* aName,const TDesC* aRelated,const TDesC* aDefault,TBool allowWild);
private:
	TInt ParseDrive(TLex& aName,TBool& aDone);
	TInt ParsePath(TLex& aName,TBool& aDone);
	TInt ParseName(TLex& aName,TBool& aDone);
	TInt ParseExt(TLex& aName,TBool& aDone);
private:
	TInt iWild;
	SField iField[EMaxFields];
	};
//
class TParsePtr : public TParseBase
	{
public:
	IMPORT_C TParsePtr(TDes& aName);
protected:
	IMPORT_C TDes& NameBuf();
	IMPORT_C const TDesC& NameBufC() const;
private:
	TPtr iNameBuf;
	};
//
class TParsePtrC : public TParseBase
	{
public:
	IMPORT_C TParsePtrC(const TDesC& aName);
protected:
	IMPORT_C TDes& NameBuf();
	IMPORT_C const TDesC& NameBufC() const;
private:
	TPtrC iNameBuf;
	};
//
class TParse : public TParseBase
	{
public:
	IMPORT_C TParse();
	IMPORT_C TInt Set(const TDesC& aName,const TDesC* aRelated,const TDesC* aDefault);
	IMPORT_C TInt SetNoWild(const TDesC& aName,const TDesC* aRelated,const TDesC* aDefault);
protected:
	IMPORT_C TDes& NameBuf();
	IMPORT_C const TDesC& NameBufC() const;
private:
	TFileName iNameBuf;
	};
//
class CDir : public CBase
	{
public:
	IMPORT_C virtual ~CDir();
	IMPORT_C TInt Count() const;
	IMPORT_C const TEntry& operator[](TInt anIndex) const;
	IMPORT_C TInt Sort(TUint aEntrySortKey);
protected:
	IMPORT_C CDir();
	IMPORT_C static CDir* NewL();
	IMPORT_C void AddL(const TEntry& anEntry);
	IMPORT_C void ExtractL(TBool aRemove,CDir*& aDir);
	IMPORT_C void Compress();
protected:
	CArrayPakFlat<TEntry>* iArray;
	friend class RFs;
	friend class TOpenFileScan;
	};
//
class RFs : public RSessionBase
	{
public:
	IMPORT_C TInt Connect(TInt aMessageSlots=KFileServerDefaultMessageSlots);
	IMPORT_C TVersion Version() const;
	IMPORT_C TInt AddFileSystem(const TDesC& aFileName) const;
	IMPORT_C TInt MountFileSystem(const TDesC& aFileSystemName,TInt aDrive) const;
	IMPORT_C TInt DismountFileSystem(const TDesC& aFileSystemName,TInt aDrive) const;
	IMPORT_C TInt RemoveFileSystem(const TDesC& aFileSystemName) const;
	IMPORT_C TInt FileSystemName(TDes& aName,TInt aDrive) const;
	IMPORT_C void NotifyChange(TNotifyType aType,TRequestStatus& aStat);
	IMPORT_C void NotifyChange(TNotifyType aType,TRequestStatus& aStat,const TDesC& aPathName);
	IMPORT_C void NotifyChangeCancel();
	IMPORT_C void NotifyChangeCancel(TRequestStatus& aStat);
	IMPORT_C void NotifyDiskSpace(TInt64 aThreshold,TInt aDrive,TRequestStatus& aStat);
	IMPORT_C void NotifyDiskSpaceCancel(TRequestStatus& aStat);
	IMPORT_C void NotifyDiskSpaceCancel();
	IMPORT_C TInt DriveList(TDriveList& aList) const;
	IMPORT_C TInt Drive(TDriveInfo& anInfo,TInt aDrive=KDefaultDrive) const;
	IMPORT_C TInt Volume(TVolumeInfo& aVol,TInt aDrive=KDefaultDrive) const;
	IMPORT_C TInt SetVolumeLabel(const TDesC& aName,TInt aDrive=KDefaultDrive);
	IMPORT_C TInt Subst(TDes& aPath,TInt aDrive=KDefaultDrive) const;
	IMPORT_C TInt SetSubst(const TDesC& aPath,TInt aDrive=KDefaultDrive);
	IMPORT_C TInt RealName(const TDesC& aName,TDes& aResult) const;
	IMPORT_C TInt DefaultPath(TDes& aPath) const;
	IMPORT_C TInt SetDefaultPath(const TDesC& aPath);
	IMPORT_C TInt SessionPath(TDes& aPath) const;
	IMPORT_C TInt SetSessionPath(const TDesC& aPath);
	IMPORT_C TInt Parse(const TDesC& aName,TParse& aParse) const;
	IMPORT_C TInt Parse(const TDesC& aName,const TDesC& aRelated,TParse& aParse) const;
	IMPORT_C TInt MkDir(const TDesC& aPath);
	IMPORT_C TInt MkDirAll(const TDesC& aPath);
	IMPORT_C TInt RmDir(const TDesC& aPath);
	IMPORT_C TInt GetDir(const TDesC& aName,TUint anEntryAttMask,TUint anEntrySortKey,CDir*& anEntryList) const;
	IMPORT_C TInt GetDir(const TDesC& aName,TUint anEntryAttMask,TUint anEntrySortKey,CDir*& anEntryList,CDir*& aDirList) const;
	IMPORT_C TInt GetDir(const TDesC& aName,const TUidType& anEntryUid,TUint anEntrySortKey,CDir*& aFileList) const;
	IMPORT_C TInt Delete(const TDesC& aName);
	IMPORT_C TInt Rename(const TDesC& anOldName,const TDesC& aNewName);
	IMPORT_C TInt Replace(const TDesC& anOldName,const TDesC& aNewName);
	IMPORT_C TInt Att(const TDesC& aName,TUint& aAttValue) const;
	IMPORT_C TInt SetAtt(const TDesC& aName,TUint aSetAttMask,TUint aClearAttMask);
	IMPORT_C TInt Modified(const TDesC& aName,TTime& aTime) const;
	IMPORT_C TInt SetModified(const TDesC& aName,const TTime& aTime);
	IMPORT_C TInt Entry(const TDesC& aName,TEntry& anEntry) const;
	IMPORT_C TInt SetEntry(const TDesC& aName,const TTime& aTime,TUint aSetAttMask,TUint aClearAttMask);
	IMPORT_C TInt ReadFileSection(const TDesC& aName,TInt aPos,TDes8& aDes,TInt aLength) const;
	IMPORT_C static TBool IsValidDrive(TInt aDrive);
	IMPORT_C static TInt CharToDrive(TChar aChar,TInt& aDrive);
	IMPORT_C static TInt DriveToChar(TInt aDrive,TChar& aChar);
	IMPORT_C static TBool IsRomAddress(TAny* aAny);
	IMPORT_C void ResourceCountMarkStart() const;
	IMPORT_C void ResourceCountMarkEnd() const;
	IMPORT_C TInt ResourceCount() const;
	IMPORT_C TInt IsFileOpen(const TDesC& aFile,TBool& anAnswer) const;
	IMPORT_C TInt CheckDisk(const TDesC& aDrive) const;
	IMPORT_C TInt ScanDrive(const TDesC& aDrive) const;
	IMPORT_C TInt GetShortName(const TDesC& aLongName,TDes& aShortName) const;
	IMPORT_C TInt GetLongName(const TDesC& aShortName,TDes& aLongName) const;
	IMPORT_C TBool GetNotifyUser();
	IMPORT_C void SetNotifyUser(TBool aValue);
	IMPORT_C TUint8* IsFileInRom(const TDesC& aFileName) const;
	IMPORT_C TBool IsValidName(const TDesC& anEntryName) const;
	IMPORT_C TBool IsValidName(const TDesC& aFileName,TText& aBadChar) const;
	IMPORT_C TInt GetDriveName(TInt aDrive,TDes& aDriveName) const;
	IMPORT_C TInt SetDriveName(TInt aDrive,const TDesC& aDriveName);
	IMPORT_C TInt LoaderHeapFunction(TInt aFunction, TAny *aArg1=NULL, TAny *aArg2=NULL);
	IMPORT_C TInt SetErrorCondition(TInt anError,TInt aCount=0);
	IMPORT_C TInt SetDebugRegister(TInt aVal);
	IMPORT_C TInt SetAllocFailure(TInt aAllocNum);
	IMPORT_C void DebugNotify(TInt aDrive,TUint aNotifyType,TRequestStatus& aStat);
	IMPORT_C TInt ControlIo(TInt aDrive,TInt aCommand,TAny* aParam1,TAny* aParam2);
	IMPORT_C TInt LockDrive(TInt aDrv, const TMediaPassword &aOld, const TMediaPassword &aNew, TBool aStr);
	IMPORT_C TInt UnlockDrive(TInt aDrv, const TMediaPassword &Pswd, TBool aStr);
	IMPORT_C TInt ClearPassword(TInt aDrv, const TMediaPassword &aPswd);
private:
	void GetDirL(const TDesC& aMatchName,TUint anEntryAttMask,TUint anEntrySortKey,CDir*& anEntryList,CDir*& aDirList,RDir& aDir) const;
	void GetDirL(const TDesC& aMatchName,TUint anEntryAttMask,TUint anEntrySortKey,CDir*& anEntryList,RDir& aDir) const;
	void GetDirL(const TDesC& aMatchName,const TUidType& aUidType,TUint anEntrySortKey,CDir*& anEntryList,RDir& aDir) const;
	void DoGetDirL(TUint anEntrySortKey,CDir*& anEntryList,RDir& aDir) const;
	TInt GetOpenFileList(TInt& aSessionNum,TInt& aLocalPos,TThreadId& aThreadId,TEntryArray& anArray) const;
	friend class TOpenFileScan;
	};
//
class RFsBase : public RSubSessionBase
	{
public:
	IMPORT_C void Close();
	};
//
class RFile : public RFsBase
	{
public:
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Create(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Replace(RFs& aFs,const TDesC& aName,TUint aFileMode);
	IMPORT_C TInt Temp(RFs& aFs,const TDesC& aPath,TFileName& aName,TUint aFileMode);
	IMPORT_C TInt Read(TDes8& aDes) const;
	IMPORT_C void Read(TDes8& aDes,TRequestStatus& aStatus) const;
	IMPORT_C TInt Read(TDes8& aDes,TInt aLength) const;
	IMPORT_C void Read(TDes8& aDes,TInt aLength,TRequestStatus& aStatus) const;
	IMPORT_C TInt Read(TInt aPos,TDes8& aDes) const;
	IMPORT_C void Read(TInt aPos,TDes8& aDes,TRequestStatus& aStatus) const;
	IMPORT_C TInt Read(TInt aPos,TDes8& aDes,TInt aLength) const;
	IMPORT_C void Read(TInt aPos,TDes8& aDes,TInt aLength,TRequestStatus& aStatus) const;
	IMPORT_C TInt Write(const TDesC8& aDes);
	IMPORT_C void Write(const TDesC8& aDes,TRequestStatus& aStatus);
	IMPORT_C TInt Write(const TDesC8& aDes,TInt aLength);
	IMPORT_C void Write(const TDesC8& aDes,TInt aLength,TRequestStatus& aStatus);
	IMPORT_C TInt Write(TInt aPos,const TDesC8& aDes);
	IMPORT_C void Write(TInt aPos,const TDesC8& aDes,TRequestStatus& aStatus);
	IMPORT_C TInt Write(TInt aPos,const TDesC8& aDes,TInt aLength);
	IMPORT_C void Write(TInt aPos,const TDesC8& aDes,TInt aLength,TRequestStatus& aStatus);
	IMPORT_C TInt Lock(TInt aPos,TInt aLength) const;
	IMPORT_C TInt UnLock(TInt aPos,TInt aLength) const;
	IMPORT_C TInt Seek(TSeek aMode,TInt& aPos) const;
	IMPORT_C TInt Flush();
	IMPORT_C TInt Size(TInt& aSize) const;
	IMPORT_C TInt SetSize(TInt aSize);
	IMPORT_C TInt Att(TUint& aAttValue) const;
	IMPORT_C TInt SetAtt(TUint aSetAttMask,TUint aClearAttMask);
	IMPORT_C TInt Modified(TTime& aTime) const;
	IMPORT_C TInt SetModified(const TTime& aTime);
	IMPORT_C TInt Set(const TTime& aTime,TUint aSetAttMask,TUint aClearAttMask);
	IMPORT_C TInt ChangeMode(TFileMode aNewMode);
	IMPORT_C TInt Rename(const TDesC& aNewName);
	IMPORT_C TInt Drive(TInt &aDriveNumber, TDriveInfo &aDriveInfo) const;
	};
//
class RDir : public RFsBase
	{
public:
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aMatchName,const TUidType& aUidType);
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aMatchName,TUint anEntryAttMask);
	IMPORT_C TInt Read(TEntryArray& anArray) const;
	IMPORT_C void Read(TEntryArray& anArray,TRequestStatus& aStatus) const;
	IMPORT_C TInt Read(TEntry& anEntry) const;
	IMPORT_C void Read(TPckg<TEntry>& anEntry,TRequestStatus& aStatus) const;
	};
//
class RFormat : public RFsBase
	{
public:
	IMPORT_C TInt Open(RFs& aFs,const TDesC& aName,TUint aFormatMode,TInt& aCount);
	IMPORT_C TInt Next(TInt& aStep);
	IMPORT_C void Next(TPckgBuf<TInt>& aStep,TRequestStatus& aStatus);
	};
//
class RRawDisk : public RSubSessionBase
	{
public:
	IMPORT_C TInt Open(RFs& aFs,TInt aDrive);
	IMPORT_C void Close();
	IMPORT_C TInt Read(TInt aPos,TDes8& aDes);
	IMPORT_C TInt Write(TInt aPos,TDesC8& aDes);
private:
	TInt iDrive;
	};
//
class CDirStack;
class CDirScan : public CBase
    {
public:
	enum TScanDirection {EScanUpTree,EScanDownTree};
public:
	IMPORT_C static CDirScan* NewL(RFs& aFs);
	IMPORT_C static CDirScan* NewLC(RFs& aFs);
	IMPORT_C ~CDirScan();
	IMPORT_C void SetScanDataL(const TDesC& aMatchName,TUint anEntryAttMask,TUint anEntrySortMask,TScanDirection aScanDir=EScanDownTree);
	IMPORT_C void NextL(CDir*& aDirEntries);
	IMPORT_C TPtrC AbbreviatedPath();
	IMPORT_C TPtrC FullPath();
protected:
	CDirScan(RFs& aFs);
private:
	inline RFs& Fs();
	void UpdateAbbreviatedPath();
	void ScanUpTreeL(CDir*& aDirEntries);
	void ScanDownTreeL(CDir*& aDirEntries);
	void GetDirEntriesL(CDir*& aDirEntries);
private:
	RFs* const iFs;
	TParse iFullPath;
	TPtrC iAbbreviatedPath;
	TInt iAbbreviatedPathPos;
	TUint iEntryAttMask;
	TUint iEntrySortMask;
	TBool iScanning;
	TScanDirection iScanDir;
	CDirStack* iStack;
	};
//
enum TFileManError
	{
	ENoExtraInformation,
	EInitializationFailed,
	EScanNextDirectoryFailed,
	ESrcOpenFailed,
	ETrgOpenFailed,
	ENoFilesProcessed
	};

class MFileManObserver
	{
public:
	enum TControl {EContinue,ERetry,EAbort,ECancel};
public:
	IMPORT_C virtual TControl NotifyFileManStarted();
	IMPORT_C virtual TControl NotifyFileManOperation();
	IMPORT_C virtual TControl NotifyFileManEnded();
	};

class CFileBase : public CBase
	{
public:
	IMPORT_C void SetObserver(MFileManObserver* anObserver);
public:
	IMPORT_C const TEntry& CurrentEntry();
	IMPORT_C TPtrC AbbreviatedPath();
	IMPORT_C TPtrC FullPath();
	IMPORT_C TInt GetLastError();
	IMPORT_C TFileManError GetMoreInfoAboutError();
protected:
	IMPORT_C CFileBase(RFs& anFs);
	IMPORT_C void ConstructL();
	IMPORT_C ~CFileBase();
	IMPORT_C void RunL();
	IMPORT_C void RunInSeparateThreadL(TThreadFunction aThreadFunction);
// virtual
	virtual void CompleteOperationL() {};
	virtual void DoOperationL() = 0;
protected:
	RFs iFs;
	RFs iFsOld;
	RThread iFManThread;
	RSemaphore iSynchronizer;
	CDirScan* iScanner;
	CDir* iDirList;
	TInt iCurrentEntry;
	TUint iMatchEntry;
	TUint iSwitches;
	TParse iSrcFile;
	MFileManObserver* iObserver;
	TInt iLastError;
	TFileManError iErrorInfo;
	TRequestStatus* iStatus;
	HBufC* iSessionPath;
	TInt iNumberOfFilesProcessed;

friend void DoFManBaseOperationL(TAny* aPtr);
friend TInt FManBaseThreadFunction(TAny* aPtr);
	};

class CFileMan : public CFileBase
	{
public:
	enum TAction {ENone,EAttribs,ECopy,EDelete,EMove,ERename,ERmDir,ERenameInvalidEntry};
	enum TSwitch {EOverWrite=1,ERecurse=2};
public:
	IMPORT_C static CFileMan* NewL(RFs& aFs);
	IMPORT_C static CFileMan* NewL(RFs& aFs,MFileManObserver* anObserver);
	IMPORT_C TAction CurrentAction();
	IMPORT_C void GetCurrentTarget(TFileName& aFile);
	IMPORT_C void GetCurrentSource(TFileName& aFile);
	IMPORT_C TInt BytesTransferredByCopyStep();
public:
	IMPORT_C TInt Attribs(const TDesC& aName,TUint aSetMask,TUint aClearMask,const TTime& aTime,TUint aSwitch=0);
	IMPORT_C TInt Attribs(const TDesC& aName,TUint aSetMask,TUint aClearMask,const TTime& aTime,TUint aSwitch,TRequestStatus& aStatus);
	IMPORT_C TInt Copy(const TDesC& anOld,const TDesC& aNew,TUint aSwitch=EOverWrite);
	IMPORT_C TInt Copy(const TDesC& anOld,const TDesC& aNew,TUint aSwitch,TRequestStatus& aStatus);
	IMPORT_C TInt Delete(const TDesC& aName,TUint aSwitch=0);
	IMPORT_C TInt Delete(const TDesC& aName,TUint aSwitch,TRequestStatus& aStatus);
	IMPORT_C TInt Move(const TDesC& anOld,const TDesC& aNew,TUint aSwitch=EOverWrite);
	IMPORT_C TInt Move(const TDesC& anOld,const TDesC& aNew,TUint aSwitch,TRequestStatus& aStatus);
	IMPORT_C TInt Rename(const TDesC& anOld,const TDesC& aNew,TUint aSwitch=EOverWrite);
	IMPORT_C TInt Rename(const TDesC& anOld,const TDesC& aNew,TUint aSwitch,TRequestStatus& aStatus);
	IMPORT_C TInt RmDir(const TDesC& aDirName);
	IMPORT_C TInt RmDir(const TDesC& aDirName,TRequestStatus& aStatus);
protected:
	CFileMan(RFs& aFs);
	TInt RenameInvalidEntry(const TDesC& anOld,const TDesC& aNew,TUint aSwitch=EOverWrite);
private:
	void CompleteOperationL();
	void DoOperationL();
	void CheckForDirectory();
	void SetFlags(TBool aOverWrite,TBool aRecurse,TBool aScanDirection);
	void GetSrcAndTrg(TParse& aSrcName,TFileName& aTrgName);
	void DoSynchronize(TInt aRetVal);
	TInt CheckRenameAllowed(const TDesC& aSrcName,const TDesC& aTrgName);
private:
	void DoAttribsL();
	void DoCopyOrMoveL();
	void DoDeleteL();
	void DoRenameL();
	void DoRmDirL();
private:
	TParse iTrgFile;
	TAction iAction;
	TUint iSetMask;
	TUint iClearMask;
	TTime iTime;
	TInt iBytesTransferred;
friend void RenameInvalidEntryL(RFs& aFs,TParse& aSrcFile);
	};

class TFindFile
	{
public:
	IMPORT_C TFindFile(RFs& aFs);
	IMPORT_C TInt FindByPath(const TDesC& aFileName,const TDesC* aPathList);
	IMPORT_C TInt FindByDir(const TDesC& aFileName,const TDesC& aDirPath);
	IMPORT_C TInt Find();
	IMPORT_C TInt FindWildByPath(const TDesC& aFileName,const TDesC* aPathList,CDir*& aDirList);
	IMPORT_C TInt FindWildByDir(const TDesC& aFileName,const TDesC& aDirPath,CDir*& aDir);
	IMPORT_C TInt FindWild(CDir*& aDirList);
	inline const TDesC& File() const;
private:
	TInt DoFind();
	TInt DoFindByPath(const TDesC& aFileName,const TDesC* aPathList);
	TInt DoFindByDir(const TDesC& aFileName,const TDesC& aDir);
	TInt DoFindInDir();
	TInt DoFindNextInPath();
	TInt DoFindNextInDriveList();
private:
	RFs* const iFs;
	TParse iFile;
	TInt iPathPos;
	TInt iCurrentDrive;
	TInt iMode;
	const TDesC* iPath;
	TDriveList iDrvList;
	CDir** iDir;
	};
//
typedef CDir CFileList;
class TOpenFileScan
	{
public:
	IMPORT_C TOpenFileScan(RFs& aFs);
	IMPORT_C void NextL(CFileList*& aFileList);
	IMPORT_C TThreadId ThreadId() const;
private:
	RFs* iFs;
	TThreadId iThreadId;
	TInt iScanPos;
	TInt iEntryListPos;
	};
//
class TFileText
	{
public:
	enum TFileState{EStartOfFile,ENormal,EReverse};
public:
	IMPORT_C TFileText();
	IMPORT_C void Set(RFile& aFile);
	IMPORT_C TInt Read(TDes& aDes);
	IMPORT_C TInt Write(const TDesC& aDes);
	IMPORT_C TInt Seek(TSeek aMode);
private:
	void NextRecord();
	TInt CheckForTerminator(TBool& anAnswer);
	TInt FillBuffer();
private:
	const TText* iNext;
	const TText* iEnd;
	TFileState iState;
	RFile iFile;
	TBuf8<0x100> iReadBuf; 
	};
#include "f32file.inl"
#endif
