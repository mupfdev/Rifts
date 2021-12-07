// APSSERV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APSSERV_H__)
#define __APSSERV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__APMFNDR_H__)
#include <apmfndr.h>
#endif

#include "apgaplst.h"
#include <babackup.h>

// classes defined
class CApaAppListServer;
//
// classes referenced
class CApaAppList;
class CApaAppData;
class CApaFileRecognizer;
class CApaScanningAppFinder;
class CApaScanningFileRecognizer;
class CApaFsMonitor;
class CTypeStoreManager;
class MApaAppStarter;
//

// server name
#define KAppListServerName _L("AppListServer")

class CApaAppListServer : public CServer, public MApaAppListObserver, public MBackupOperationObserver
	{
public:
	IMPORT_C static CApaAppListServer* NewL(CApaAppList* aAppList,CApaFileRecognizer* aRecognizer);
	IMPORT_C static CApaAppListServer* NewL(MApaAppStarter& aAppStarter);
	inline CApaAppList* AppList();
	inline CApaFileRecognizer* FileRecognizer();
	inline CApaDataRecognizer* DataRecognizer();
	inline CTypeStoreManager*& TypeStoreManager();
	inline RFs& FsSession();
public: // from MApaAppListObserver
	void NotifyUpdate(TInt aReason);
	void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes);
	//
	IMPORT_C ~CApaAppListServer();
private:
	CApaAppListServer(TInt aPriority,CApaAppList* aAppList,CApaFileRecognizer* aRecognizer);
	void ConstructL(MApaAppStarter* aAppStarter);
	virtual CSharableSession* NewSessionL(const TVersion &aVersion) const;
	static TInt AppFsNotifyCallBack(TAny* aPtr);
	static TInt RecogFsNotifyCallBack(TAny* aPtr);
	static TInt TypeStoreNotifyCallback(TAny* aPtr);
	void UpdateApps();
	void UpdateRecogs();
	void UpdateTypeStore();
private:
	enum {
		EOwnsFileRecognizer=0x01,
		EOwnsAppList=0x02
		};
private:
	RFs iFs;
	CApaFileRecognizer* iFileRecognizer;
	CApaAppList* iAppList;
	TInt iActive;
	TInt iOwnsList;
	CApaScanningFileRecognizer* iScanningFileRecognizer;
	CApaScanningAppFinder* iScanningAppFinder;
	CApaScanningDataRecognizer* iDataRecognizer;
	CApaFsMonitor* iAppFsMonitor;
	CApaFsMonitor* iRecogFsMonitor;
	CApaFsMonitor* iTypeStoreMonitor;
	CTypeStoreManager* iTypeStoreManager;
	TTime iTypeStoreModified;
	CBaBackupSessionWrapper* iBaBackupSessionWrapper;
	};

/**
 * The TApaAppViewIconSizeData class encapsulates the attributes that specify how to identify an icon for a particular
 * application and view in a certain size.
 *
 * @internal
 * @since App-Framework_6.1
 */
class TApaAppViewIconSizeData
	{
public:
	inline TApaAppViewIconSizeData();
	inline TApaAppViewIconSizeData(TUid aAppUid,TUid aViewUid, const TSize& aSize);
public:
	TUid iAppUid;
	TUid iViewUid;
	TSize iSize;
	};

typedef TPckgBuf<TApaAppViewIconSizeData> TApaAppViewIconSizeDataBuf;

//
// inlines
//

inline TApaAppViewIconSizeData::TApaAppViewIconSizeData()
	: iAppUid(KNullUid), iViewUid(KNullUid), iSize(TSize(0,0))
	{}

inline TApaAppViewIconSizeData::TApaAppViewIconSizeData(TUid aAppUid,TUid aViewUid, const TSize& aSize)
	: iAppUid(aAppUid), iViewUid(aViewUid), iSize(aSize)
	{}

inline CApaAppList* CApaAppListServer::AppList()
	{ return iAppList; }

inline CApaFileRecognizer* CApaAppListServer::FileRecognizer()
	{ return iFileRecognizer; }

inline CApaDataRecognizer* CApaAppListServer::DataRecognizer()
	{ return iDataRecognizer; }

inline RFs& CApaAppListServer::FsSession()
	{ return iFs; }

inline CTypeStoreManager*& CApaAppListServer::TypeStoreManager()
	{ return iTypeStoreManager; }

#endif
