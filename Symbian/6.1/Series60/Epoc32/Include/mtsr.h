// MTSR.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#ifndef __MTSR_H__
#define __MTSR_H__

#include <e32base.h>
#include <badesca.h>
#include "msvstd.h"
#include "msvreg.h"

// forward declarations
class RWriteStream;
class RReadStream;
class RFs;
class CDictionaryFileStore;
class CInstalledMtmGroup;


class CBaseServerMtm : public CActive
	{
public:
	IMPORT_C ~CBaseServerMtm();
	//
	virtual void CopyToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus)=0;
	virtual void CopyFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus)=0;
	virtual void CopyWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus)=0;
	virtual void DeleteAllL(const CMsvEntrySelection& aSelection, TRequestStatus& aStatus)=0;
	virtual void CreateL(TMsvEntry aNewEntry, TRequestStatus& aStatus)=0;
	virtual void ChangeL(TMsvEntry aNewEntry, TRequestStatus& aStatus)=0;
	//
	virtual void StartCommandL(CMsvEntrySelection& aSelection, TInt aCommand, const TDesC8& aParameter, TRequestStatus& aStatus)=0;
	//
	virtual TBool CommandExpected()=0;
	//
	virtual const TDesC8& Progress()=0;
	//
	virtual void MoveToLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus)=0;
	virtual void MoveFromLocalL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus)=0;
	virtual void MoveWithinServiceL(const CMsvEntrySelection& aSelection,TMsvId aDestination, TRequestStatus& aStatus)=0;
	//
protected:
	IMPORT_C CBaseServerMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvServerEntry* aServerEntry);
	virtual void DoRunL()=0;
	virtual void DoComplete(TInt aError)=0;
	//
private:
	// from CActive
	IMPORT_C void RunL(); 
	//
protected:
	CMsvServerEntry* iServerEntry;
	//
private:
	CRegisteredMtmDll& iRegisteredMtmDll;
	};


class CServerMtmDllRegistry : public CMtmDllRegistry
	{
friend class CMtmRegistryControl;
public:
	IMPORT_C static CServerMtmDllRegistry* NewL(RFs& aFs,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32=KMsvDefaultTimeoutMicroSeconds32);
	IMPORT_C ~CServerMtmDllRegistry();
	IMPORT_C CBaseServerMtm* NewServerMtmL(TUid aMtmTypeUid, CMsvServerEntry* aInitialEntry);
	//
protected:
	CServerMtmDllRegistry(RFs& aFs,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32);
	//
private:
	CBaseServerMtm* NewMtmL(const RLibrary& aLib, CMsvServerEntry* aServerEntry, CRegisteredMtmDll& aReg) const;
	};


class CInstalledMtmGroupArray : public CArrayPtrFlat<CInstalledMtmGroup>
	{
public:
	CInstalledMtmGroupArray();
	~CInstalledMtmGroupArray();
	void AddInstalledMtmGroupL(CInstalledMtmGroup* aInstalledMtmGroup);
	};

//**********************************
// CMsvMtmCache
//**********************************

class CMsvMtmCache : public CBase
	{
public:
	static CMsvMtmCache* NewL();
	~CMsvMtmCache();
	//
	TInt GetMtmPath(const TUidType& aType, TPtrC& aName) const;
	TInt SetMtmPath(const TUidType& aType, const TDesC& aName);
	TInt DelMtmPath(const TUidType& aType);
	//
private:
	void ConstructL();
	CMsvMtmCache();
	//
	TInt FindMtm(const TUidType& aType) const;
	//
	CArrayFixFlat<TUidType>* iType;
	CDesCArrayFlat* iName;
	};

//**********************************
// CMtmRegistryControl
//**********************************

class CMtmRegistryControl : public CBase, public MRegisteredMtmDllObserver
	{
public:
	IMPORT_C static CMtmRegistryControl* NewL(RFs& anFs,CServerMtmDllRegistry& aServerMtmDllRegistry);
	IMPORT_C ~CMtmRegistryControl();

	IMPORT_C TInt InstallMtmGroup(const TDesC& aFullName,TUid& aMtmTypeUid);
	IMPORT_C TInt FullNameToMtmTypeUid(const TDesC& aFullName,TUid& aMtmTypeUid) const;
	IMPORT_C TInt DeInstallMtmGroup(TUid aMtmTypeUid);  //  returns error on storing registry

	IMPORT_C TInt UseMtmGroup(TUid aMtmTypeUid);
	IMPORT_C TInt ReleaseMtmGroup(TUid aMtmTypeUid);  
	IMPORT_C TBool IsInUse(TUid aMtmTypeUid) const;

	IMPORT_C TInt FillRegisteredMtmDllArray(TUid aMtmDllTypeUid,CRegisteredMtmDllArray& aRegisteredMtmDllArray,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32=0);  // Fill array with Dlls whose second uid is aMtmDllTypeUid
	IMPORT_C CMtmGroupData* GetMtmGroupDataL(TUid aMtmTypeUid) const;  

	IMPORT_C void StoreRegistryL() const;
	IMPORT_C void RestoreRegistryL();

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	CMtmRegistryControl(RFs& anFs,CServerMtmDllRegistry& aServerMtmDllRegistry);
	void ConstructL();
	TInt MtmTypeUidToIndex(TUid aMtmTypeUid) const;
	TInt UidTypeToIndex(TUidType aUidType) const;
	void DoInstallMtmGroupL(const TDesC& aFullName,TUid& aMtmTypeUid);
	CMtmGroupData* ReadDataFileStoreL(const TDesC& aFullName) const;
	void DoDeInstallMtmGroupL(TUid aMtmTypeUid);
	void DoInternalizeL(RReadStream& aStream);
	void AddInstalledMtmGroupL(CInstalledMtmGroup* aInstalledMtmGroup);
	void RemoveInstalledMtmGroup(TUid aMtmTypeUid);
	TInt GetMtmPath(const TUidType& aType, TDes& aName) const;
	TInt SetMtmPath(const TUidType& aType, const TDesC& aName);
	TInt DelMtmPath(const TUidType& aType);
	TBool IsResFileL(const TDesC& aFullName) const;
	TUid DoFindMtmTypeUidL(const TDesC& aFullName) const;
	
	CMtmGroupData *LoadMTMFileL(const TDesC& aFullName, TUid &aUid);
	CMtmGroupData *LoadDatFileL(const TDesC& aFullName, TUid &aUid);
	CMtmGroupData *LoadResFileL(const TDesC& aFullName, TUid &aUid);	
private:
	RFs& iFs;
	CInstalledMtmGroupArray iInstalledMtmGroupArray;
	CServerMtmDllRegistry& iServerMtmDllRegistry;
	CMsvMtmCache* iMtmCache;
	};


#endif
