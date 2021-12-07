// COMMDB.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Comms Database and Table header

#ifndef __COMMDB_H__
#define	__COMMDB_H__

#include <d32dbms.h>
#include <savarset.h>
#include <dial.h>
#include <cdbcols.h>
#include <cdblen.h>

const TUint32 KCommsDbMaxRank = 2; // Maximum allowed ranking for Connection Preferences

//
// Protection of settings: when the entire table is protected, write operations
// fail with KErrWrite. However KErrAccessDenied should be returned to client 
//
#define TRAPD_CONVERT(_r,_s)	TRAPD(_r,_s); if(ret == KErrWrite) ret = KErrAccessDenied;
#define  TRAP_CONVERT(_r,_s)	TRAP(_r,_s);  if(ret == KErrWrite) ret = KErrAccessDenied;

class TCommDbSystemAgentNotification
	{	
public:
	TCommDbSystemAgentNotification();
	void Set(TUid aUid, TInt aVal);
public:
	TUid iUid;
	TInt iValue;		// if it is an integer!
	};

class CCommsDbTableView;
class CCommsDbConnectionPrefTableView;

// CCommsDatabaseBase and CCommsDatabase class
//
// Controls access to the database and the DBMS server.  Also to the DBMS server
// notifier. One of these per client session.

class CCommsDatabaseBase : public CBase
	{
public:
	friend class CCommsDbTableView;
	friend class CCommsDbConnectionPrefTableView;
public:
	IMPORT_C CCommsDatabaseBase();
	IMPORT_C virtual ~CCommsDatabaseBase();
//
	IMPORT_C TVersion Version() const;
//
// Transactions
//
	IMPORT_C TInt BeginTransaction();
	IMPORT_C TInt CommitTransaction();
	IMPORT_C void RollbackTransaction();
	IMPORT_C TBool InTransaction();
	IMPORT_C TBool IsDatabaseWriteLockedL();
//
// Notification
//
	IMPORT_C TInt RequestNotification(TRequestStatus& aStatus);
	IMPORT_C void CancelRequestNotification();
//
// Opening views
//
	IMPORT_C CCommsDbTableView* OpenTableLC(const TDesC& aTableName);
	IMPORT_C CCommsDbTableView* OpenViewLC(const TDesC& aTableName, const TDesC& aSqlQuery);
	IMPORT_C CCommsDbTableView* OpenViewMatchingUintLC(const TDesC& aTableName, const TDesC& aColumnToMatch, TUint32 aValueToMatch);
	IMPORT_C CCommsDbTableView* OpenViewMatchingBoolLC(const TDesC& aTableName, const TDesC& aColumnToMatch, TBool aValueToMatch);
	IMPORT_C CCommsDbTableView* OpenViewMatchingTextLC(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC8& aValueToMatch);
	IMPORT_C CCommsDbTableView* OpenViewMatchingTextLC(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC16& aValueToMatch);
//
// Hidden records
//
	IMPORT_C void ShowHiddenRecords();
//
// Resolve phone number
//
	IMPORT_C static void ResolvePhoneNumberL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);
	IMPORT_C void ResolvePhoneNumberFromDatabaseL(TDesC& aNumber, TDes& aDialString, TParseMode aDialParseMode, TUint32 aLocationId, TUint32 aChargecardId);
//
	void DatabaseUpdateHasOccurred();
protected:
	virtual void CreateDatabaseL() =0;
	virtual TInt DoOpen() =0;
	//
	void DoClose();
	CCommsDbTableView* DoOpenViewMatchingUintL(const TDesC& aTableName, const TDesC& aColumnToMatch, TUint32 aValueToMatch);
	CCommsDbTableView* DoOpenViewMatchingTextL(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC8& aValueToMatch);
	CCommsDbTableView* DoOpenViewMatchingTextL(const TDesC& aTableName, const TDesC& aColumnToMatch, const TDesC16& aValueToMatch);
	CCommsDbTableView* DoOpenTableViewL(const TDesC& aTableName, const TDesC& aSqlQuery);
	CCommsDbTableView* DoOpenIAPTableViewL(const TDesC& aTableName,const TDesC& aSqlQuery);
	//
	void PopulateDialLocationL(TUint32 aId, TDialLocation& aLocation);
	void PopulateChargeCardL(TUint32 aId, TChargeCard& aChargeCard);
	void BeginInternalTransactionL();
	void CommitInternalTransactionL();
	void RollbackInternalTransaction();
	void NotifyChange(const TDesC& aSetting, TUint32 aVal);
	void ConvertToUidL(const TDesC& aSetting, TUint32 aVal,TCommDbSystemAgentNotification& aNotification);
	void NotifyAllChanges();
	inline RDbNamedDatabase* Database();
protected:	
	RDbs iDbs;
	RDbNamedDatabase iDatabase;
	RDbNotifier iNotifier;
	RSAVarChangeNotify iSystemAgentNotifier;
	TInt iNotifierOpenError;
	TBool iShowHiddenRecords;
	TBool iUpdateHasOccurred;
	TBool iInInternalTransaction;
	RArray<TCommDbSystemAgentNotification> iNotifications;
	};

class CCommsDatabase : public CCommsDatabaseBase
	{
public:
	IMPORT_C static CCommsDatabase* NewL(TCommDbDatabaseType aType);	// parameter will be removed in 7.0
	IMPORT_C static CCommsDatabase* NewL(TCommDbDatabaseType aType, TCommDbOpeningMethod &aOpeningMethod);
	IMPORT_C ~CCommsDatabase();
//
// Global Settings records
//
	IMPORT_C void GetGlobalSettingL(const TDesC& aSetting, TUint32& aValue);
	IMPORT_C void GetGlobalSettingL(const TDesC& aSetting, TDes& aValue);
	IMPORT_C void SetGlobalSettingL(const TDesC& aSetting, TUint32 aValue);
	IMPORT_C void SetGlobalSettingL(const TDesC& aSetting, const TDesC& aValue);
	IMPORT_C void ClearGlobalSettingL(const TDesC& aSetting);
//
// Current Settings
//
	IMPORT_C void GetCurrentDialOutSettingL(const TDesC& aSetting, TUint32& aValue);
	IMPORT_C void GetCurrentDialInSettingL(const TDesC& aSetting, TUint32& aValue);
//
// Connection Preferences views
//
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableLC();
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableLC(TCommDbConnectionDirection aDirection);
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableInRankOrderLC(TCommDbConnectionDirection aDirection);
	IMPORT_C CCommsDbConnectionPrefTableView* OpenConnectionPrefTableViewOnRankLC(TCommDbConnectionDirection aDirection, TUint32 aRank);
//
// Current Agent
//
	IMPORT_C void SetAgentL(const TDesC& aService, const TDesC& aAgent);
	IMPORT_C void SetAgentExtL(const TDesC& aService, const TDesC& aAgentExt);
	IMPORT_C void SetAgentClientTimeoutL(const TDesC& aService, TInt aClientTimeout);
	IMPORT_C void SetAgentRouteTimeoutL(const TDesC& aService, TInt aRouteTimeout);
	IMPORT_C void GetAgentL(const TDesC& aService, TDes& aAgent);
	IMPORT_C void GetAgentExtL(const TDesC& aService, TDes& aAgentExt);
	IMPORT_C TInt GetAgentClientTimeoutL(const TDesC& aService);
	IMPORT_C TInt GetAgentRouteTimeoutL(const TDesC& aService);
	IMPORT_C void ClearAgentAndExtL(const TDesC& aService);
//
// Opening views by matching service type
//
	IMPORT_C CCommsDbTableView* OpenIAPTableViewMatchingBearerSetLC(TUint32 aBearerSet, TCommDbConnectionDirection aDirection);
	IMPORT_C CCommsDbTableView* OpenViewOnProxyRecordLC(TUint32 aServiceId, const TDesC& aServiceType);
//
	inline TCommDbDatabaseType Type() const;	// to be deprecated in 7.0
private:
	enum TGlobalSettingType
		{
		ENotASetting,
		EGlobalSetting,
		ECompatibilitySetting
		};
private:
	CCommsDatabase(TCommDbDatabaseType aType);	// parameter will be removed in 7.0
	// CCommsDatabaseBase pure virtuals
	virtual void CreateDatabaseL();
	virtual TInt DoOpen();
	//
	TInt DoOpen(TCommDbOpeningMethod& aOpeningMethod);
	CCommsDbTableView* OpenGlobalSettingsTableLC(const TDesC& aSetting, TBool& aExists);
	TGlobalSettingType KnownGlobalSetting(const TDesC& aSetting) const;
	void DoGetCurrentSettingL(const TDesC& aSetting, TUint32& aValue, TBool aDialOut);
	void DoSetGlobalSettingL(const TDesC& aSetting, TUint32 aVal);
	void DoSetGlobalSettingL(const TDesC& aSetting, const TDesC& aVal);
	void DoGetCompatibilitySettingL(const TDesC& aSetting, TUint32& aVal);
	void DoSetCompatibilitySettingL(const TDesC& aSetting, TUint32 aVal);
	void DoSetIAPCompatibilitySettingL(const TDesC& aSetting, TUint32 aVal, TCommDbConnectionDirection aDirection, CCommsDbConnectionPrefTableView* aView, TBool aExists);
	void DoSetISPCompatibilitySettingL(const TDesC& aSetting, TUint32 aVal, TCommDbConnectionDirection aDirection, CCommsDbConnectionPrefTableView* aView, TBool aExists);
	void DoClearCompatibilitySettingL(const TDesC& aSetting);
	CCommsDbConnectionPrefTableView* DoFindConnectionPrefLC(TCommDbConnectionDirection aDirection, TBool& aExists);
	CCommsDbConnectionPrefTableView* DoOpenConnectionPrefViewLC(TCommDbConnectionDirection aDirection, TBool aAllNonZeroRank, TUint32 aRankingToMatch = KMaxTUint32);
	CCommsDbTableView* DoOpenAgentTableLC(const TDesC& aService, TBool& aExists);
	void SetAgentDesL(const TDesC& aService, const TDesC& aField, const TDesC& aValue);
	void SetAgentTimeoutL(const TDesC& aService, const TDesC& aTimeoutType, TInt aTimeout);
	void GetAgentDesL(const TDesC& aService, const TDesC& aField, TDes& aValue);
	TInt GetAgentTimeoutL(const TDesC& aService, const TDesC& aTimeoutType);
	void ValidateServiceL(const TDesC& aService);
	void OpenDefaultDbL(RFs& aFs);
private:
	TCommDbDatabaseType iType;	// to be deprecated in 7.0
	};	

class CCommsDbTableAccessView : public CBase
	{
public:
	static CCommsDbTableAccessView* NewL(CCommsDatabaseBase& aDb,const TDesC& aTableName);
	~CCommsDbTableAccessView();

	void SetAccessL(TUint aAccessType);
	RDbRowSet::TAccess GetAccessL();

	CCommsDbTableAccessView(const TDesC& aTableName);
	void ConstructL(CCommsDatabaseBase& aDb);
	
private:
	const TDesC&       iTableName;
	CCommsDbTableView* iView;
	TBool              iTableFound;
	};

// CCommsDbTableView class
//
// Implements actions on tables and rows in the database.  Uses a CCommsDatabase 
// and has an RDbView to read from and write to database.  Created via the 
// CCommsDatabase object OpenTableLC() (to open a view on all the records in the table) 
// or one of the OpenViewLC() functions (to open a specific view on the table).

class CCommsDbTableView : public CBase
	{
public:
	friend class CCommsDatabaseBase;
	friend class CCommsDbTemplateRecord;
public:
	static CCommsDbTableView* NewL(CCommsDatabaseBase* aDb, const TDesC& aTableName, const TDbQuery& aQuery, TBool aUseTemplate =ETrue);
	
	CCommsDbTableView(CCommsDatabaseBase* aDb, const TDesC& aTableName);
	IMPORT_C virtual ~CCommsDbTableView();
//
// Record operations
//
	IMPORT_C TInt InsertRecord(TUint32& aId);
	IMPORT_C TInt UpdateRecord();
	IMPORT_C TInt DeleteRecord();
	IMPORT_C TInt PutRecordChanges(TBool aHidden = EFalse, TBool aReadOnly = EFalse);
	IMPORT_C void CancelRecordChanges();
//
// Navigating records
//
	IMPORT_C TInt GotoFirstRecord();
	IMPORT_C TInt GotoNextRecord();
	IMPORT_C TInt GotoPreviousRecord();
//
// Reads
//
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes8& aValue);
	IMPORT_C void ReadTextL(const TDesC& aColumn, TDes16& aValue);
	IMPORT_C HBufC* ReadLongTextLC(const TDesC& aColumn);
	IMPORT_C void ReadUintL(const TDesC& aColumn, TUint32& aValue);
	IMPORT_C void ReadBoolL(const TDesC& aColumn, TBool& aValue);
	IMPORT_C void ReadTypeAttribL(const TDesC& aColumn, TDbColType& aColType, TUint32& aAttrib);
	IMPORT_C void ReadColumnLengthL(const TDesC& aColumn, TInt& aLength);
//
// Writes
//
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC8& aValue);
	IMPORT_C void WriteTextL(const TDesC& aColumn, const TDesC16& aValue);
	IMPORT_C void WriteLongTextL(const TDesC& aColumn, const TDesC& aValue);
	IMPORT_C void WriteUintL(const TDesC& aColumn, const TUint32& aValue);
	IMPORT_C void WriteBoolL(const TDesC& aColumn, const TBool& aValue);
	IMPORT_C void SetNullL(const TDesC& aColumn);
//
// Get table name
//
	inline void GetTableName(TDes& aTableName) const;
//

	inline CCommsDatabaseBase* Database() const { return iDb; }

	void  OpenL(const TDbQuery& aQuery);

protected:
	TDbColNo ColNumL(const TDesC& aColumn) const;
	void Close();
	void ConstructL(const TDbQuery& aQuery, TBool aUseTemplate);
	RDbRowSet::TAccess GetL();

private:
	void ConstructL(const TDbQuery& aQuery,TBool aUseTemplate,const RDbRowSet::TAccess& aAccess);
	TInt InsertRecordWithThisId(TUint32 aId);
	TBool TableWithTemplateRecord() const;
	TBool EncryptedColumn(const TDesC& aColumn) const;
	void DoCheckRecordExistsL();
	void DoReadFirstRecordIdL(const TDesC& aTableName,TUint32& aValue);
	void DoReadIdAttribL(const TDesC& aTableName,TDbColType& aColType,TUint32& aAttrib);
	void DoReadIdColumnLengthL(const TDesC& aTableName,TInt& aLength);

private:
	CCommsDbTemplateRecord* iTemplate;
	TBool iTsyNameChanged;

protected:
	enum TTableState
		{
		EClosed,
		EOpenIdle,
		EInsert,
		EUpdate
		};
protected:
	CCommsDatabaseBase* iDb;
	RDbView iTableView;
	TTableState iState;
	CDbColSet* iColSet;
	TBuf<KCommsDbSvrMaxColumnNameLength> iTableName;
	HBufC* iQueryText;
	CCommsDbTableAccessView* iAccess;	
	};

#include <commdb.inl>

#endif
