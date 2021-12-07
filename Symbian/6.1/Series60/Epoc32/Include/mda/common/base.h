// Mda\Common\Base.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_BASE_H__
#define __MDA_COMMON_BASE_H__

/*
Notes:
Header file for information shared between client and server side
Contains UID definitions, function numbers
*/

// Standard EPOC32 includes
#include <e32base.h>
// Public Media Server includes
#include <Mda\Common\Base.hrh>

#ifdef ASSERT
#ifdef _DEBUG
#undef ASSERT

// Redefine assert to be a little more useful to us, i.e. to include file & line number
#define __ASSERT_FILE__(s) _LIT(KPanicFileName,s)
#define __ASSERT_PANIC__(l) User::Panic(KPanicFileName().Right(12),l)
#define ASSERT(x) { __ASSERT_FILE__(__FILE__); __ASSERT_DEBUG(x, __ASSERT_PANIC__(__LINE__) ); }
#endif
#endif

// Macro for producing different variants of Uids
#define MDA_UID(uid_name)	const TUint uid_name##Value = uid_name##Define; \
							const TUid uid_name = {uid_name##Value};

// Uids
#if defined(UNICODE)
const TInt KUidMediaServerLibraryValue = KUidMediaServerLibraryUnicodeDefine;
#else
const TInt KUidMediaServerLibraryValue = KUidMediaServerLibraryDefine;
#endif
const TUid KUidMediaServerLibrary = {KUidMediaServerLibraryValue};

MDA_UID(KUidMdaTimerFactory)

// Server name

_LIT(KMediaServerName,"MediaServer");

// Server version
const TUint KMdaServerMajorVersionNumber=0;
const TUint KMdaServerMinorVersionNumber=1;
const TUint KMdaServerBuildVersionNumber=1;

// Default number of message slots
const TInt KMdaServerDefaultMessageSlots=-1;	// Use global pool for messages

// Unknown value
const TInt KMdaUnknown = -1;

enum //TMSvFunctionFlags
	{	
	EMSvFunctionBlindFlag =		0x00000000,
	EMSvFunctionSynchFlag =		0x00010000,
	EMSvFunctionAsynchFlag =	0x00020000,
	EMSvFunctionCancelFlag =	0x00040000,
	EMSvFunctionCreateFlag =	0x00080000,
	EMSvFunctionDestroyFlag =	0x00100000,
	EMSvFunctionPendingFlag =	0x00200000,	// Debug builds only
	EMSvFunctionIsPackageFlag =	0x00400000,
	EMSvFunctionCancelingFlag =	0x00800000
	};

enum // Object Handles
	{
	EMSvUninitialisedObject=0,
	EMSvRegistryObject=-1,
	EMSvSessionObject=-2,
	EMSvTimerFactoryObject=-3
	};

enum // Session functions
	{
	EMSvSessionListenTo=0,
	EMSvSessionStopListeningTo=1,
	EMSvSessionSetListenerParams=2,
	EMSvSessionGetListenerEvents=3,
	EMSvSessionCancelGetListenerEvents=4,
	EMSvSessionCheckOkToClose=5
	};

enum // Library Functions
	{
	EMdaLibraryObjectOpen=1
	};

enum // Registry Functions
	{
	EMdaRegistryUpdate=2
	};

enum // Client Registry Object Functions
	{
	EMSvRegistryObjectOpen=EMdaLibraryObjectOpen,
	EMSvRegistryUpdate=EMdaRegistryUpdate,
	// Iterator functions
	EMSvRegistryIterLock=3,
	EMSvRegistryIterUnlock=4,
	EMSvRegistryIterReset=5,
	EMSvRegistryIterCurrent=6,
	EMSvRegistryIterPostInc=7,
	EMSvRegistryIterSet=8,
	EMSvRegistryIterGetData=9,
	// Default management functions
	EMSvRegistryDefaultSet=10,
	EMSvRegistryDefaultGet=11
	};

enum // Registry event ids
	{
	EMdaRegistryUpdateEvent=1
	};

enum // Event ids
	{
	EMdaEventMissed=-1
	};

// Timer functions
enum
	{
	EMLbTimerFactoryNewTimer
	};

enum
	{
	EMLbTimerAt,
	EMLbTimerAfter,
	EMLbTimerNow
	};

// Panics
enum //TMdaSvrPanic
	{
	EMdaBadRequest=1,
	EMdaBadDescriptor=2,
	EMdaBadObjectHandle=3,
	EMdaBadPackage=4,
	EMdaNotImplemented=5,
	EMdaMessageAlreadyCompleted=6,
	EMdaMessageStillPending=7,
	EMdaResourcesNotClosed=8
	};

// Package classes

class TMdaRawPackage
	{
public:
	inline TPtr8& Package();
	inline const TPtr8& Package() const;
protected:
	TMdaRawPackage(TInt aDerivedSize);
	inline void SetSize(TInt aDerivedSize);
protected:
	TPtr8 iThis;
	friend class RMdaObject;
	};

class TMdaOpenPackage : public TMdaRawPackage
	{
public:
	inline void SetHandleAddress(TPckgBuf<TInt>* aHandle);
	inline TPckgBuf<TInt>* GetHandleAddress() const;
	inline TMdaOpenPackage(TInt aDerivedSize);
private:
	TPckgBuf<TInt>* iHandle;
	};

class TMdaPackage : public TMdaRawPackage
	{
public:
	inline TUid Type() const;
	inline TUid Uid() const;
	inline void SetUid(TUid aUid);
	inline TBool operator==(const TMdaPackage& aPackage); // Type&Uid comparison
protected:
	inline TMdaPackage(TUid aType, TUid aUid, TInt aDerivedSize);
private:
	TUid iType;
	TUid iUid;
	};

class TMdaReturnPackage : public TMdaPackage
	{
public:
	inline TInt ReturnSize() const;
protected:
	inline TMdaReturnPackage(TUid aType, TUid aUid, TInt aDerivedSize);
	inline void SetReturnSize(TInt aReturnSize);
private:
	TInt iRetSize;
	friend class RMdaObject;
	};

// Events

class TMdaEvent
	{
public:
	TInt32 iId;
	TInt32 iArg[3];
	};

class TMdaObjectEvent
	{
public:
	TInt iHandle;
	TMdaEvent iEvent;
	};

class TMdaEventPackage : public TMdaRawPackage
	{
public:
	inline TMdaEventPackage(); // For single events
	//
	inline TInt EventCount() const;
	inline TInt MaxEvents() const;
	inline const TMdaEvent& Event(); // First event only
	inline const TMdaEvent& Event(TInt aIndex);
	inline TInt EventFrom(); // first event only
	inline TInt EventFrom(TInt aIndex);
protected:
	inline TMdaEventPackage(TInt aMaxEvents);
protected:
	TInt iMaxEvents;
	TInt iValidEvents;
	TMdaObjectEvent iFirstEvent;
	};

class HMdaEventPackage : public TMdaEventPackage
	{
public:
	inline static HMdaEventPackage* NewL(TInt aMaxEvents);
	inline static HMdaEventPackage* NewLC(TInt aMaxEvents);
protected:
	HMdaEventPackage(TInt aMaxEvents);
	};

template <TInt S>
class TMdaEventPackageBuf : public TMdaEventPackage
	{
public:
	inline TMdaEventPackageBuf();
private:
	TMdaObjectEvent iEvents[S];
	};

// Registry

class TMdaRegistryEntryDetails : public TMdaReturnPackage
	{
public:
	inline TMdaRegistryEntryDetails();
	inline TMdaRegistryEntryDetails(TUid aType);
	inline TMdaRegistryEntryDetails(TUid aType,TUid aUid);
protected:
	inline TMdaRegistryEntryDetails(TUid aType, TUid aUid, TInt aDataSize);
	};

class TMdaRegistryEntryData : public TMdaRawPackage
	{
public:
	inline TMdaRegistryEntryData(TInt aDataSize);
	inline const TPtrC8 Data();
	};

// Timers

class TMdaTime : public TMdaRawPackage
	{
public:
	inline TMdaTime();
public:
	TTime iTime;
	};

// Useful utilities

// 'Give' - Used to give control of an object to another object
// Ensures that the pointer is nulled before the object is returned
//
template <class T>
inline T* ObjectUtilGive(T*& aObject)
	{ 
	T* temp = aObject; 
	aObject = NULL; 
	return temp;
	}
// 'Take' - Used to take control of an object from another object
// ASSERTSs that the pointer is null before the object is kept to ensure
// that nothing is being orphaned
template <class T>
inline T* ObjectUtilTake(T* aObject, T*& aPointer)
	{
	ASSERT(!aPointer);
	aPointer = aObject;
	return aObject;
	}
// CloseIfExists - Used to free pointers to objects that must be closed
template <class T>
inline void ObjectUtilCloseIfExists(T*& aObject)
	{
	if (aObject)
		{
		aObject->Close();
		aObject = NULL;
		} 
	}
// ReleaseIfExists - Used to free pointers to objects that must be released
template <class T>
inline void ObjectUtilReleaseIfExists(T*& aObject)
	{
	if (aObject)
		{
		aObject->Release();
		aObject = NULL;
		}
	}

#include <Mda\Common\Base.inl>

#endif
