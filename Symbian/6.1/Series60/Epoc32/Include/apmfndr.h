// APMFNDR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__APMFNDR_H__)
#define __APMFNDR_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif
#if !defined(__APMREC_H__)
#include <apmrec.h>
#endif

#include <babackup.h>

const TInt KMaxRecognizerNameLength=12; // max filename length, not including path or extension

// classes defined
class CApaRecognizerDll;

/**
 * @internal
 * Internal to Symbian
 */
class CApaScanningDataRecognizer : public CApaDataRecognizer
	{
public:
	typedef TBuf<KMaxRecognizerNameLength> TRecognizerName;
	class TRecognizer
		{
	public:
		TUid iUid;
		TInt iDrive;
		TRecognizerName iName;
		TTime iModified;
		};
	typedef CArrayFixFlat<TRecognizer> CRecognizerArray;

public:
	class CApaBackupObserver : public CBase, public MBackupObserver
		{
	public:
		// Construction / Destruction
		CApaBackupObserver( CApaScanningDataRecognizer& aRecognizer );
		~CApaBackupObserver();

	public:
		virtual void ChangeFileLockL(const TDesC& aFileName,TFileLockFlags aFlags);
		void AddFileL( const TDesC& aFileName );
		void RemoveFile( const TDesC& aFileName );
		TInt UpdateCounter() const;
		void SetUpdateCounter( TInt aValue );

	private:
		CBaBackupSessionWrapper* iSession;
		CApaScanningDataRecognizer& iRecognizer;
		TInt iUpdateCounter;
		};

	//
public:
	IMPORT_C static CApaScanningDataRecognizer* NewL(RFs& aFs);
	IMPORT_C ~CApaScanningDataRecognizer();
	IMPORT_C void ScanForRecognizersL();
	IMPORT_C TInt RecognizerCount();
	IMPORT_C void SetRecognizersFromList(const CRecognizerArray& aList);
	IMPORT_C CRecognizerArray* RecognizerListLC()const;
	IMPORT_C void SetRecognizerL(const TRecognizer& aRecognizer); 
	IMPORT_C TRecognizer operator[](TInt aIndex)const;
	IMPORT_C TInt UpdateCounter()const;
protected:
	IMPORT_C CApaScanningDataRecognizer(RFs& aFs);
	IMPORT_C void ConstructL();
private:
	void ScanDriveL(TInt aDriveNum);
	void LoadRecognizerL(const TDesC& aFullName,TUid aUid, const TTime& aTime);
	TInt RemoveRecognizer(CApaRecognizerDll* aDll);
private:
	friend class CApaBackupObserver;
	CArrayPtrFlat<CApaRecognizerDll> iRecognizerLib;
	//TInt iUpdateCounter;
	CApaBackupObserver* iObserver;
	};

class CApaRecognizerDll : public CBase
	{
public:
	~CApaRecognizerDll(); // closes lib and deletes next
public:
	enum TPresence { ENotPresent, EIsPresent, ESuperseded };
public:
	RLibrary iLibrary;
	CApaRecognizerDll* iNext;
	CApaScanningDataRecognizer::TRecognizer iId; // cached so that this data can be accessed from other threads (RLibrary cant be used in this case)
	CApaDataRecognizerType* iRec; // not ownership
	TPresence iPresent;
	};

#endif