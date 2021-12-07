// APAFLREC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__APAFLREC_H__)
#define __APAFLREC_H__

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif
#if !defined(__APAID_H__)
#include <apaid.h>
#endif

// classes defined:
class MApaAppStarter;
class CApaAppLocator;
class CApaFileRecognizer;
class CApaFileRecognizerType;
//
// classes referenced:
class TApaAppEntry;
class CApaCommandLine;
class RFs;
//

// UID[1] for app recognizer dll's (UID[2] identifies a particular identifier)
#ifdef _UNICODE
#define KUidFileRecognizer KUidFileRecognizer16
#else
#define KUidFileRecognizer KUidFileRecognizer8
#endif
const TInt KFileRecognizerUidValue8=0x1000013E;
const TUid KUidFileRecognizer8={KFileRecognizerUidValue8};
const TUid KUidFileRecognizer16={0x10003A37};
//

class CApaAppLocator : public CBase
	{
public:
	virtual TInt GetAppEntryByUid(TApaAppEntry& aAppEntry,TUid aAppUid)=0;
	virtual TInt GetAppCapabilityByUid(TDes8& aCapabilityBuf,TUid aAppUid)=0;
	};


/**
 * @internal
 * Internal to Symbian
 */
class CApaFileRecognizer : public CBase
	{
public:
	//
	IMPORT_C CApaFileRecognizerType* RecognizeFileL(const TDesC& aFullFileName,const TUidType* aUidType=NULL);
	IMPORT_C CApaAppLocator* AppLocator() const;
	//
	IMPORT_C ~CApaFileRecognizer();
protected:
	IMPORT_C CApaFileRecognizer(RFs& aFs);
	IMPORT_C void AddFileRecognizerType(CApaFileRecognizerType* aFileRecognizerType);
	IMPORT_C TInt RemoveFileRecognizerType(const CApaFileRecognizerType* aFileRecognizerType);
	IMPORT_C void SetAppLocator(CApaAppLocator* aAppLocator); // should be called by child-classes eg during construction
	static inline void SetAppStarter(CApaFileRecognizerType* aRecognizer,MApaAppStarter* aAppStarter);
	IMPORT_C void DestroyRecognizerList();
protected:
	RFs& iFs;
	CApaAppLocator* iAppLocator;
private:
	CApaFileRecognizerType *iFileRecognizerList;
	};


class MApaAppStarter
	{
public:
	virtual TThreadId StartAppL(const CApaCommandLine& aCommandLine)=0;
	};


/**
 * @internal
 * Internal to Symbian
 */
class CApaFileRecognizerType : public CBase
	{
public:
	enum TRecognizedType {EProgram,EDoc,EOtherFile,ENotRecognized};
public:
	virtual TThreadId RunL(TApaCommand aCommand,const TDesC* aDocFileName=NULL,const TDesC8* aTailEnd=NULL) const=0;
	inline TUid AppUid()const;
	inline TUid TypeUid()const;
	inline TRecognizedType Type()const;
	IMPORT_C void Capability(TDes8& aCapabilityBuf)const;
	IMPORT_C void Lock();
	IMPORT_C void Unlock();
protected:
	IMPORT_C CApaFileRecognizerType();
	IMPORT_C ~CApaFileRecognizerType();
	IMPORT_C TThreadId AppRunL(const CApaCommandLine& aCommandLine) const;
private:
	inline void SetAppStarter(MApaAppStarter* aAppStarter); // must be called before AppRunL()
	virtual TRecognizedType DoRecognizeFileL(RFs& aFs,TUidType aUidType)=0;
	TRecognizedType RecognizeFileL(RFs& aFs,const TDesC& aFullFileName,TUidType aUidType);
	TBool Locked()const;
	IMPORT_C virtual void Reserved_1();
protected:
	CApaFileRecognizer* iFileRecognizer;
	MApaAppStarter* iAppStarter;
	HBufC* iFullFileName;
	TUid iFileType; // type UID of the recognizer file (ie UID[1])
	TUid iAppUid; // UID of the associated app (ie UID[2])
	TRecognizedType iRecognizedType;
	TApaAppCapabilityBuf* iCapabilityBuf;
private:
	CApaFileRecognizerType* iNext;
	TInt iLock;
	TInt iSpare;
private:
	friend class CApaFileRecognizer;
	};


//
// inlines
//

inline void CApaFileRecognizer::SetAppStarter(CApaFileRecognizerType* aRecognizer,MApaAppStarter* aAppStarter)
	{ aRecognizer->SetAppStarter(aAppStarter); }

inline void CApaFileRecognizerType::SetAppStarter(MApaAppStarter* aAppStarter)
	{ iAppStarter = aAppStarter; }

inline TUid CApaFileRecognizerType::AppUid() const
	{ return iAppUid; }

inline TUid CApaFileRecognizerType::TypeUid() const
	{ return iFileType; }

inline CApaFileRecognizerType::TRecognizedType CApaFileRecognizerType::Type()const
	{ return iRecognizedType; }

/*
inline CApaFileRecognizerType::TCapability::TCapability(TUint aCapabilities)
	{ iCapabilities = aCapabilities; }

inline TBool CApaFileRecognizerType::TCapability::IsProgram()const
	{ return iCapabilities&EIsProgram; }

inline TBool CApaFileRecognizerType::TCapability::IsFileBased()const
	{ return iCapabilities&EIsFileBased; }

inline TBool CApaFileRecognizerType::TCapability::IsEmbeddable()const
	{ return iCapabilities&EIsEmbeddable; }
*/
#endif
