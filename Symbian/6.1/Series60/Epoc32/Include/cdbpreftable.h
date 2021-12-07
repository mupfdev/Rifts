// CDBPREFTABLE.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Comms Database Connection Preference Table header

#ifndef __CDBPREFTABLE_H__
#define	__CDBPREFTABLE_H__

#include <d32dbms.h>
#include <cdbcols.h>
#include <cdblen.h>

class CCommsDatabase;
class CCommsDbTableAccessView;	

// CCommsDbConnectionPrefTableView class
//
// Implements actions on rows in the Connection Preferences table in the database.
// Uses a CCommsDatabase and has an RDbView to read from and write to database.
// Created via the CCommsDatabase object OpenConnectionPrefTableLC() functions.

class TCommDbCommonBearerInfo;

class CCommsDbConnectionPrefTableView : public CBase
	{
friend class CTestProtectionOfSettings;
public:
	class TCommDbIapBearer
		{
	public:
		IMPORT_C TCommDbIapBearer();
	public:
		TUint32 iBearerSet;
		TUint32 iIapId;
		};
	//
	class TCommDbIapConnectionPref
		{
	public:
		IMPORT_C TCommDbIapConnectionPref();
		IMPORT_C TBool operator==(const TCommDbIapConnectionPref& aPref) const;
	public:
		TUint32 iRanking;
		TCommDbConnectionDirection iDirection;
		TCommDbDialogPref iDialogPref;
		TCommDbIapBearer iBearer;
		};
	//
	class TCommDbIspBearer	// will be deprecated in 7.0
		{
	public:
		IMPORT_C TCommDbIspBearer();
	public:
		TUint32 iBearerSet;
		TUint32 iServiceId;
		TBuf<KCommsDbSvrMaxColumnNameLength> iServiceType;
		TUint32 iChargeCardId;
		};
	//
	class TCommDbIspConnectionPref	// will be deprecated in 7.0
		{
	public:
		IMPORT_C TCommDbIspConnectionPref();
		IMPORT_C TBool operator==(const TCommDbIspConnectionPref& aPref) const;
	public:
		TUint32 iRanking;
		TCommDbConnectionDirection iDirection;
		TCommDbDialogPref iDialogPref;
		TCommDbIspBearer iBearer;
		};
public:
	static CCommsDbConnectionPrefTableView* NewLC(CCommsDatabase* aDb, const TDbQuery& aQuery, TCommDbDatabaseType aType);	// aType parameter will be removed in 7.0
	CCommsDbConnectionPrefTableView(CCommsDatabase* aDb, TCommDbDatabaseType aType);
	IMPORT_C virtual ~CCommsDbConnectionPrefTableView();
//
// IAP Connection Preference record operations
//
	IMPORT_C void InsertConnectionPreferenceL(const TCommDbIapConnectionPref& aPref, TBool aReadOnly = EFalse);
	IMPORT_C void UpdateBearerL(const TCommDbIapBearer& aUpdate, TBool aReadOnly = EFalse);
	IMPORT_C void ReadConnectionPreferenceL(TCommDbIapConnectionPref& aPref);
//
// ISP Connection Preference record operations 
// All these will be deprecated in 7.0
//
	IMPORT_C void InsertConnectionPreferenceL(const TCommDbIspConnectionPref& aPref, TBool aReadOnly = EFalse);
	IMPORT_C void UpdateBearerL(const TCommDbIspBearer& aUpdate, TBool aReadOnly = EFalse);
	IMPORT_C void ReadConnectionPreferenceL(TCommDbIspConnectionPref& aPref);
//
// Generic Connection Preference record operations
//
	IMPORT_C void UpdateDialogPrefL(const TCommDbDialogPref& aUpdate);
	IMPORT_C void SwapConnectionPreferencesL(TCommDbConnectionDirection aDirection, TUint32 aFirstRank, TUint32 aSecondRank);
	IMPORT_C void ChangeConnectionPreferenceRankL(TUint32 aNewRank);
	IMPORT_C void DeleteConnectionPreferenceL();
//
// Navigating records
//
	IMPORT_C TInt GotoFirstRecord();
	IMPORT_C TInt GotoNextRecord();
	IMPORT_C TInt GotoPreviousRecord();
protected:
	void ConstructL(const TDbQuery& aQuery);
	void Close();
	void  OpenL(const TDbQuery& aQuery);
	RDbRowSet::TAccess GetL();
	TDbColNo ColNum(const TDesC& aColumn) const;
	void GetUint32L(const TDesC& aColumnName, TUint32& aValue);

private:
	void RefreshL(TBool aMustBeWriteable);
	void SetRankL(TUint32 aNewRank, TBool aNotify = ETrue);
	void ValidateRankL(TUint32 aRank);
	void FindConnectionFromDirectionAndRankL(TCommDbConnectionDirection aDirection, TUint32 aRank, TDbBookmark& aBookmark);
	void DoReadBearerInfoL(TCommDbCommonBearerInfo& aInfo);
	void DoWriteBearerInfoL(const TCommDbCommonBearerInfo& aInfo);
	void DoSwapConnectionPreferencesL(TCommDbConnectionDirection aDirection, TUint32 aFirstRank, TUint32 aSecondRank);
	void CheckRankDoesNotExistL(TUint32 aRank, TCommDbConnectionDirection aDirection);
	void GetUint32OrNull(const TDesC& aColumnName, TUint32& aValue, TBool& aExists);
	void ValidateIapL(TUint32 aIapId, TCommDbConnectionDirection aDirection, TUint32 aBearerSet);
	void ValidateBearerAndDirectionL(const TDesC& aServiceType, TCommDbConnectionDirection aDirection, TUint32 aBearerSet);
	void ValidateDatabaseTypeL(TCommDbDatabaseType aDatabaseType);

protected:
//	CCommsDatabaseBase* iDb;
	RDbView iTableView; //?? Can't be right, surely?
	CCommsDbTableAccessView* iAccess;	
	HBufC* iQueryText;
	TBuf<KCommsDbSvrMaxColumnNameLength> iTableName;

private:
	CCommsDatabase* iDb;
	TCommDbDatabaseType iType;	// will be deprecated in 7.0
	CDbColSet* iColSet;
	};

#endif
