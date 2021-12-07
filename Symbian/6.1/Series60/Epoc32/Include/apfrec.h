// APFREC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APFREC_H__)
#define __APFREC_H__

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif
#if !defined(__APAFLREC_H__)
#include <apaflrec.h>
#endif

#include <babackup.h>

// classes defined:
class CApaScanningFileRecognizer;
class CApaAppLocatorProxy;
//
// classes referenced:
class CApaAppFinder;
class TApaAppEntry;
class TEntry;
class RFs;
//

// dir in which app recognizers should live - this dir is scanned on all drives
_LIT(KAppRecognizerSearchPath,"\\System\\Recogs\\");
_LIT(KAppRecognizerSearchString,"?:\\System\\Recogs\\");

class CApaRecognizerDll; // private class
class CApaScanningFileRecognizer : public CApaFileRecognizer
	{
public:
	typedef TFileName TRecognizerName;
	class TRecognizer
		{
	public:
		TUid iUid;
		TInt iDrive;
		TRecognizerName iName;
		};
	typedef CArrayFixFlat<TRecognizer> CRecognizerArray;
	//
public:
	class CApaFileBackupObserver : public CBase, public MBackupObserver
		{
	public:
		// Construction / Destruction
		CApaFileBackupObserver( CApaScanningFileRecognizer& aRecognizer );
		~CApaFileBackupObserver();

	public:
		virtual void ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags);
		void AddFileL( const TDesC& aFileName );
		void RemoveFile( const TDesC& aFileName );
		TInt UpdateCounter() const;
		void SetUpdateCounter( TInt aValue );

	private:
		CBaBackupSessionWrapper* iSession;
		CApaScanningFileRecognizer& iRecognizer;
		TInt iUpdateCounter;
		};

	IMPORT_C static CApaScanningFileRecognizer* NewL(RFs& aFs,MApaAppStarter* aAppStarter);
	IMPORT_C ~CApaScanningFileRecognizer();
	IMPORT_C void ScanForRecognizersL();
	IMPORT_C TInt RecognizerCount();
	IMPORT_C void SetRecognizersFromListL(const CRecognizerArray& aList);
	IMPORT_C CRecognizerArray* RecognizerListLC()const;
	IMPORT_C void SetRecognizerL(const TRecognizer& aRecognizer); 
	IMPORT_C TRecognizer operator[](TInt aIndex)const; 
	IMPORT_C TInt UpdateCounter()const;
protected:
	IMPORT_C CApaScanningFileRecognizer(RFs& aFs,MApaAppStarter* aAppStarter);
	IMPORT_C void ConstructL();
	//
private:
	void ScanDriveL(TInt aDriveNum);
	void LoadRecognizerL(const TDesC& aFullName,TUid aUid);
	TInt RemoveRecognizer(CApaRecognizerDll* aDll);
private:
	friend class CApaFileBackupObserver;
	CApaRecognizerDll* iRecognizerLib;
	MApaAppStarter* iAppStarter;
	CApaFileBackupObserver* iObserver;
	};


class CApaAppLocatorProxy : public CApaAppLocator
	{
public:
	IMPORT_C static CApaAppLocatorProxy* NewL(RFs& aFs);
	IMPORT_C TInt GetAppEntryByUid(TApaAppEntry& aAppEntry,TUid aAppUid);
	IMPORT_C TInt GetAppCapabilityByUid(TDes8& aCapabilityBuf,TUid aAppUid);
	IMPORT_C ~CApaAppLocatorProxy();
private:
	CApaAppLocatorProxy(RFs& aFs);
	void ConstructL();
	void DoGetAppEntryByUidL(TApaAppEntry& aAppEntry,TUid aAppUid);
private:
	RFs& iFs;
	CApaAppFinder* iAppFinder;
	};


#endif