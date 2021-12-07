// BABACKUP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__BABACKUP_H__)
#define __BABACKUP_H__

#include <e32std.h>
#include <e32base.h>

/**
 * MBackupObserver defines the interface to be implemented by any code that will
 * hold file locks or may attempt to access files regardless of other device state
 * e.g. a phone app may always attempt to access the contacts database for caller id
 */
class MBackupObserver
	{
public:
	enum TFileLockFlags
		{
		ETakeLock				=0,
		EReleaseLockReadOnly	=0x01,
		EReleaseLockNoAccess	=0x02,
		};
public:
	virtual void ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags)=0;
	};

class TBackupOperationAttributes;

/**
 * MBackupOperationObserver defines the interface to be implemented by any code that will need a
 * notification when a backup or restore operatione either starts or ends.
 *
 * @since App-Framework_6.2
 */
class MBackupOperationObserver
	{
public:
	enum TOperationType
		{
		ENone		=0x00,
		EStart		=0x01,
		EEnd		=0x02,
		};
public:
	virtual void HandleBackupOperationEventL(const TBackupOperationAttributes& aBackupOperationAttributes)=0;
private:
	IMPORT_C virtual void Reserved1();
	};


class TBackupOperationAttributes
	{
public:
	inline TBackupOperationAttributes();
	inline TBackupOperationAttributes(MBackupObserver::TFileLockFlags aFileFlag, MBackupOperationObserver::TOperationType aOperation);
public:
	MBackupObserver::TFileLockFlags iFileFlag;
	MBackupOperationObserver::TOperationType iOperation;
	};


class RBaBackupSession;
class CBaLockChangeNotifier;
class CBaBackupOperationNotifier;

/**
 * CBaBackupSessionWrapper provides the APIs necessary to enable a backup or restore/install
 * by allowing broadcast requests for some or all files to either remain untouched or have
 * their locks released for an arbitrary period.
 *
 * The class should be used by both code driving a backup/install and any engines that will
 * hold files locks or may access files regardless of the presence of (non-system) client apps
 */
class CBaBackupSessionWrapper : public CBase
	{
public:
	IMPORT_C static CBaBackupSessionWrapper* NewL();
	IMPORT_C ~CBaBackupSessionWrapper();
	IMPORT_C void RegisterFileL(const TDesC& aFileName,MBackupObserver& aObserver);
	IMPORT_C void DeregisterFile(const TDesC& aFileName);
	IMPORT_C void CloseAll(MBackupObserver::TFileLockFlags aFlags,TRequestStatus& aStatus);
	IMPORT_C void RestartAll();
	IMPORT_C void CloseFileL(const TDesC& aFileName,MBackupObserver::TFileLockFlags aFlags);
	IMPORT_C void RestartFile(const TDesC& aFileName);
	IMPORT_C void RegisterBackupOperationObserverL(MBackupOperationObserver& aBackupOperationObserver);
	IMPORT_C void DeRegisterBackupOperationObserver(MBackupOperationObserver& aBackupOperationObserver);
	IMPORT_C TBool IsBackupOperationRunning() const;
	IMPORT_C void NotifyBackupOperationL(const TBackupOperationAttributes& aBackupOperationAttributes);
public: // Do not use
	IMPORT_C void CloseServer();
private:
	CBaBackupSessionWrapper();
	void ConstructL();
private:
	RBaBackupSession* iBackupSession;
	CBaLockChangeNotifier* iLockChangeNotifier;
	CBaBackupOperationNotifier* iBackupOperationNotifier;
	};


//
// TBackupOperationAttributes
//

inline TBackupOperationAttributes::TBackupOperationAttributes()
	: iFileFlag(MBackupObserver::ETakeLock), iOperation(MBackupOperationObserver::ENone)
	{
	}

inline TBackupOperationAttributes::TBackupOperationAttributes(MBackupObserver::TFileLockFlags aFileFlag, MBackupOperationObserver::TOperationType aOperation)
	: iFileFlag(aFileFlag), iOperation(aOperation)
	{
	}
#endif
