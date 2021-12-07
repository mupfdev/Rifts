// DATASTOR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__DATASTOR_H__)
#define __DATASTOR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__S32FILE_H__)
#include <s32file.h>
#endif
#if !defined(__APMSTD_H__)
#include <apmstd.h>
#endif

class RReadStream;
class RWriteStream;

const TUid KUidDatastor = {0x1000071E};
const TUid KUidDatastorSettings = {0x10000790};
#define KDatastorIniFileName _L("c:\\System\\Data\\Dtstor.ini")

/**
 * @internal
 * Internal to Symbian
 */
class TMappingDataTypeToApp
	{
public:
	IMPORT_C TMappingDataTypeToApp();
	IMPORT_C TMappingDataTypeToApp(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
public:
	TDataType iDataType;
	TDataTypePriority iPriority;
	TUid iAppUid; // Uid [2] of the target application
	};

					   
/**
 * @internal
 * Internal to Symbian
 */
class CTypeStoreManager : public CBase
	{
public:
	IMPORT_C static CTypeStoreManager* NewL(RFs& aFs);
	IMPORT_C ~CTypeStoreManager();
	// Persistence
	IMPORT_C void StoreL();
	IMPORT_C void RestoreL();
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
	// Enquiry
	IMPORT_C void GetAppByDataType(const TDataType& aDataType, TUid& aUid) const;
	IMPORT_C void GetDataTypesByAppL(TUid aUid, CArrayFix<TDataType>* aTypeArray) const;
	IMPORT_C const CArrayFixFlat<TMappingDataTypeToApp>& MappingArray() const;
	// Management
	IMPORT_C void InsertDataMappingL(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C TBool InsertIfHigherL(const TDataType& aDataType, TDataTypePriority aPriority, TUid aUid);
	IMPORT_C void DeleteDataMapping(const TDataType& aDataType);
	inline TPtrC IniFileName() const;
private:
	CDictionaryStore* OpenIniFileLC() const;
	CTypeStoreManager(RFs& aFs);
	void ConstructL();
	TInt FindDataMapping(const TDataType& aDataType) const;
private:
	CArrayFixFlat<TMappingDataTypeToApp> iAppMappings;
	RFs& iFs;
	};


inline TPtrC CTypeStoreManager::IniFileName() const
//	return name of dtstor's ini file
	{
	return KDatastorIniFileName;
	}

#endif
