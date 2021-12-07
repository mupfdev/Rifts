// MSVREG.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVREG_H__)
#define __MSVREG_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

enum TMtsrDllIndex    //  Used in CMtmGroupData
	{
	EMtsrServerComponentIndex,
	EMtsrClientComponentIndex,
	EMtsrUiComponentIndex,
	EMtsrUiDataComponentIndex
	};

const TInt KHumanReadableNameLength=50;
typedef TBuf<KHumanReadableNameLength> THumanReadableName;   //  could be used client side

#define KMsvDefaultTimeoutMicroSeconds32 30000000

// forward declarations
class RWriteStream;
class RReadStream;
class RFs;


class CMtmDllInfo : public CBase
	{
public:
	IMPORT_C static CMtmDllInfo* NewL(const TDesC& aHumanReadableName,const TUidType& aUidType,TInt aEntryPointOrdinalNumber,const TVersion aVersion);
	IMPORT_C static CMtmDllInfo* NewL(RReadStream& aStream);
	IMPORT_C ~CMtmDllInfo();
	IMPORT_C void SetHumanReadableNameL(const TDesC& aHumanReadableName);
	inline TPtrC HumanReadableName() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;  // not used but as it is exported it has been kept
	IMPORT_C TBool operator==(const CMtmDllInfo& aMtmDllInfo) const; 
private:
	CMtmDllInfo(const TUidType& aUidType=TUidType(),TInt aEntryPointOrdinalNumber=0,const TVersion aVersion=TVersion());
private:
	HBufC* iHumanReadableName;         //  Should be less than KHumanReadableNameLength
public:
	TUidType iUidType;                 //  Three uids
	TInt iEntryPointOrdinalNumber;
	TVersion iVersion;
	};


class CMtmDllInfoArray : public CArrayPtrFlat<CMtmDllInfo>
	{
public:
	IMPORT_C CMtmDllInfoArray();
	IMPORT_C ~CMtmDllInfoArray();
	IMPORT_C void AddMtmDllInfoL(CMtmDllInfo* aMtmDllInfo);
	};


class CMtmGroupData : public CBase
	{
public:
	IMPORT_C static CMtmGroupData* NewL(TUid aMtmTypeUid,TUid aTechnologyTypeUid,const CMtmDllInfoArray& aMtmDllInfoArray);
	IMPORT_C static CMtmGroupData* NewL(RReadStream& aStream);
	IMPORT_C ~CMtmGroupData();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;  // not used but as it is exported it has been kept
	inline TUid MtmTypeUid() const;
	inline TUid TechnologyTypeUid() const;
	inline const CMtmDllInfoArray& MtmDllInfoArray() const;
	IMPORT_C TBool operator==(const CMtmGroupData& aMtmGroupData) const; 
private:
	CMtmGroupData(TUid aMtmTypeUid=KNullUid,TUid aTechnologyTypeUid=KNullUid);
	void ConstructL(const CMtmDllInfoArray& aMtmDllInfoArray);  // Only used by first NewL()
	void AppendMtmDllInfoL(CMtmDllInfo* aMtmDllInfo);  // Leaves if second uid wrong
private:
	TUid iMtmTypeUid;
	TUid iTechnologyTypeUid;
	CMtmDllInfoArray iMtmDllInfoArray;    //  iTypeUids equal to KNullUid if DLL not present
	};                                    //  Inline because no NewL()


class MRegisteredMtmDllObserver
	{
public:
	virtual TInt UseMtmGroup(TUid aMtmTypeUid)=0;
	virtual TInt ReleaseMtmGroup(TUid aMtmTypeUid)=0;
	virtual TInt GetMtmPath(const TUidType& aType, TDes& aName) const=0;
	virtual TInt SetMtmPath(const TUidType& aType, const TDesC& aName)=0;
	virtual TInt DelMtmPath(const TUidType& aType)=0;
	};


//  Real non-derivable class

class CRegisteredMtmDll : public CTimer
	{
public:
	IMPORT_C static CRegisteredMtmDll* NewL(TUid aMtmTypeUid,TUid aTechnologyTypeUid,const CMtmDllInfo& aMtmDllInfo,const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
	IMPORT_C ~CRegisteredMtmDll();

	inline TUid MtmTypeUid() const;
	inline TUid TechnologyTypeUid() const;
	inline const CMtmDllInfo& MtmDllInfo() const;

	inline TInt MtmDllRefCount() const;

	IMPORT_C TInt GetLibrary(RFs& aFs,RLibrary& aMtmDllLibrary);   // Increments reference count if successful or returns error 
	IMPORT_C void ReleaseLibrary();                       // Decrements access count
	                                                      // Should be called from destructor of any objects created from the library 
private:
	CRegisteredMtmDll(TUid aMtmTypeUid,TUid aTechnologyTypeUid,const TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver);
	void ConstructL(const CMtmDllInfo& aMtmDllInfo);
	void LoadLibraryL(RFs& aFs);   
	TInt FindFullName(RFs& aFs,TDes& aFullName); 
	TInt DoFindFullName(RFs& aFs,TDes& aFullName, const TDriveList& aDriveList, const TUidType& aUidType);

	void RunL();

private:
	TUid iMtmTypeUid;
	TUid iTechnologyTypeUid;
	CMtmDllInfo* iMtmDllInfo;
	RLibrary iMtmDllLibrary;
	TInt iMtmDllRefCount;
	TTimeIntervalMicroSeconds32 iTimeoutMicroSeconds32;
	MRegisteredMtmDllObserver& iRegisteredMtmDllObserver;
	};



class CRegisteredMtmDllArray : public CArrayPtrFlat<CRegisteredMtmDll>
	{
public:
	IMPORT_C CRegisteredMtmDllArray();
	IMPORT_C ~CRegisteredMtmDllArray();
	IMPORT_C void AddRegisteredMtmDllL(CRegisteredMtmDll* aRegisteredMtmDll);
	};

//  Base class

class CMtmDllRegistry : public CBase
	{
public:
	IMPORT_C ~CMtmDllRegistry();

	inline TInt NumRegisteredMtmDlls() const;
	IMPORT_C TUid MtmTypeUid(TInt anIndex) const;                                

	inline TBool IsPresent(TUid aMtmTypeUid) const;
	IMPORT_C TUid TechnologyTypeUid(TUid aMtmTypeUid) const;
	IMPORT_C const CMtmDllInfo& RegisteredMtmDllInfo(TUid aMtmTypeUid) const;                                
	IMPORT_C TBool IsInUse(TUid aMtmTypeUid) const;        // returns true if specified DLL in use 
	IMPORT_C TBool IsInUse() const;                        // returns true if any DLL in use 

protected:
	IMPORT_C CMtmDllRegistry(RFs& aFs,TUid aMtmDllTypeUid,TTimeIntervalMicroSeconds32 aTimeoutMicroSeconds32=KMsvDefaultTimeoutMicroSeconds32); 

	IMPORT_C TInt MtmTypeUidToIndex(TUid anMtmTypeUid) const;

	IMPORT_C TInt AddRegisteredMtmDll(TUid aMtmTypeUid,TUid aTechnologyTypeUid,const CMtmDllInfo& aMtmDllInfo,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver); // returns error
	IMPORT_C void RemoveRegisteredMtmDll(TUid aMtmTypeUid);         
	IMPORT_C void RemoveAllRegisteredMtmDlls();                     

private:
	void DoAddRegisteredMtmDllL(TUid aMtmTypeUid,TUid aTechnologyTypeUid,const CMtmDllInfo& aMtmDllInfo,MRegisteredMtmDllObserver& aRegisteredMtmDllObserver); // returns error

protected:
	RFs& iFs;
	TUid iMtmDllTypeUid;  //  Second Uid in all Dlls
	CRegisteredMtmDllArray iRegisteredMtmDllArray;  // Inline CArray, OK because no NewL();
	TTimeIntervalMicroSeconds32 iTimeoutMicroSeconds32;
	};


#include "msvreg.inl"

#endif
