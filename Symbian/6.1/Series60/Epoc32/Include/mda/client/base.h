// Mda\Client\Base.h 
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_BASE_H__
#define __MDA_CLIENT_BASE_H__

/*
Notes:
Contains base classes for all Media Server client-side object handles

RMdaSession
Session to the Media Server. Can be made to listen for events from any other
object to which a handle is owned.

RMdaObject
Abstract class, must be derived from

RMdaRegistry
A handle to the server side registry of available object types. The registry
is always available after a session has been opened and does not need to be
opened or closed. It can be used as the source of new objects.
The handle can also be used to force the server to rebuild the registry list
to take account of any libraries that may have been added or removed from
the file system.

RMdaTimer
A Media Server timer (works to the highest resolution available on the current hardware)
*/

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Base.h>

enum TMdaClientBasePanic
	{
	EMdaClientBaseSessionHasOpenObjects=0
	};

IMPORT_C TInt StartMediaServer();
IMPORT_C void StartMediaServerL();
IMPORT_C void StartMediaServer(TRequestStatus& aStatus);

class RMdaObject;
class RMdaSession : public RSessionBase
	{
public:
	IMPORT_C TInt Connect(TInt aSlots=KMdaServerDefaultMessageSlots);
	IMPORT_C void ConnectL(TInt aSlots=KMdaServerDefaultMessageSlots);
	IMPORT_C void ConnectLC(TInt aSlots=KMdaServerDefaultMessageSlots);
	//
	IMPORT_C void Close();
	//
	inline TVersion Version() const;
	//
	IMPORT_C TInt ListenTo(const RMdaObject& aObject);
	IMPORT_C void ListenToL(const RMdaObject& aObject);
	IMPORT_C void StopListeningTo(const RMdaObject& aObject);
	//
	IMPORT_C TInt SetListenerParameters(TMdaEventPackage& aPackage,TInt aMaxPackages);
	IMPORT_C void SetListenerParametersL(TMdaEventPackage& aPackage,TInt aMaxPackages);
	//
	IMPORT_C void GetListenerEvents(TMdaEventPackage& aEvents, TRequestStatus& aStatus);
	IMPORT_C void CancelGetListenerEvents();
private:
	friend RMdaObject;
	};

class RMdaRegistry;
class RMdaObject
	{
public:
    IMPORT_C void Close();
	inline TInt Handle() const;
	inline operator TInt() const;
	inline const RMdaSession& Session() const;
protected:
	inline RMdaObject();
	// Object creation
	IMPORT_C TInt SynchCreateMessage(const RMdaObject& aParent,TInt16 aFunction,TAny* aArg=NULL);
	IMPORT_C void SynchCreateMessageL(const RMdaObject& aParent,TInt16 aFunction,TAny* aArg=NULL);
	IMPORT_C void SynchCreateMessageLC(const RMdaObject& aParent,TInt16 aFunction,TAny* aArg=NULL);
	IMPORT_C void AsynchCreateMessage(const RMdaObject& aParent,TInt16 aFunction,TRequestStatus &aStatus,TAny* aArg=NULL);
	IMPORT_C TInt SynchPackageCreateMessage(const RMdaObject& aParent,TInt16 aFunction,TMdaOpenPackage& aPackage);
	IMPORT_C void SynchPackageCreateMessageL(const RMdaObject& aParent,TInt16 aFunction,TMdaOpenPackage& aPackage);
	IMPORT_C void SynchPackageCreateMessageLC(const RMdaObject& aParent,TInt16 aFunction,TMdaOpenPackage& aPackage);
	IMPORT_C void AsynchPackageCreateMessage(const RMdaObject& aParent,TInt16 aFunction,TRequestStatus &aStatus,TMdaOpenPackage& aPackage);
	IMPORT_C void CancelCreateMessage(/*const RMdaObject& aParent,TInt16 aFunction,*/TRequestStatus &aStatus);
	// Message passing
	IMPORT_C TInt BlindMessage(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C void BlindMessageL(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C TInt SynchMessage(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C void SynchMessageL(TInt16 aFunction,const TAny* aArg1=NULL,const TAny* aArg2=NULL,const TAny* aArg3=NULL) const;
	IMPORT_C void AsynchMessage(TInt16 aFunction,TRequestStatus &aStatus,const TAny* aArg1=NULL,const TAny* aArg2=NULL) const;
	IMPORT_C void CancelMessage(/*TInt16 aFunction,*/TRequestStatus &aStatus) const;
	// Package passing
	IMPORT_C TInt SynchPackage(TInt16 aFunction,const TMdaRawPackage& aPackage) const;
	IMPORT_C void SynchPackageL(TInt16 aFunction,const TMdaRawPackage& aPackage) const;
	IMPORT_C void AsynchPackage(TInt16 aFunction,TRequestStatus &aStatus,const TMdaRawPackage& aPackage) const;
	IMPORT_C TInt SynchPackageReturn(TInt16 aFunction,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
	IMPORT_C void SynchPackageReturnL(TInt16 aFunction,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
	IMPORT_C void SynchPackageReturnLC(TInt16 aFunction,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
	IMPORT_C void AsynchPackageReturn(TInt16 aFunction,TRequestStatus &aStatus,const TMdaReturnPackage& aArgPackage,TMdaRawPackage*& aReturn) const;
private:
	RMdaSession iSession;
	TPckgBuf<TInt> iObjectHandle;
	friend RMdaRegistry;
	friend class RMdaTimer;
	friend class RMdaTimerFactory;
	};


/* 

Function definition macros
--------------------------

The following macros are for use within an RMdaObject derived class definintion
They are used to define a callable function and produce 4 variants of the function
e.g.

MDA_OBJECT_FUNCTION2(Prepare,KMdaPrepareFunction,TMdaPrepareArgType,TInt)

...produces...

inline TInt Prepare(TMdaPrepareArgType aArg1,TInt aArg2) const
	{ // Synchronous - returns error value
	return SynchMessage(KMdaPrepareFunction,(TAny*)aArg1,(TAny*)aArg2);
	}
inline void PrepareL(TMdaPrepareArgType aArg1,TInt aArg2) const
	{ // Synchronous - leaves
	SynchMessageL(KMdaPrepareFunction,(TAny*)aArg1,(TAny*)aArg2);
	}
inline void Prepare(TMdaPrepareArgType aArg1,TInt aArg2,TRequestStatus& aStatus) const
	{ // Asynchronous
	AsynchMessage(KMdaPrepareFunction,aStatus,(TAny*)aArg1,(TAny*)aArg2);
	}
inline void CancelPrepare(TRequestStatus& aStatus) const
	{ // Cancel previous asynchronous call
	return CancelMessage(aStatus);
	}

MDA_OBJECT_FUNCTION1 and MDA_OBJECT_FUNCTION are for functions with 1 or no arguments
MDA_OBJECT_FUNCTIONPACK is for functions taking/filling a fixed package
MDA_OBJECT_FUNCTIONPACKRET is for functions returning a package of variable size
MDA_OBJECT_OPENREG is for Open performed by the registry
MDA_OBJECT_OPEN is for Open performed by a specified object type 
MDA_OBJECT_OPENPACK is for Open performed by a specified object taking package argument
*/

#define MDA_OBJECT_FUNCTION2(NAME,FUNCTIONID,ARG1TYPE,ARG2TYPE)\
	inline TInt NAME(ARG1TYPE aArg1,ARG2TYPE aArg2) const\
		{ return SynchMessage(FUNCTIONID,(TAny*)aArg1,(TAny*)aArg2);}\
	inline void NAME##L(ARG1TYPE aArg1,ARG2TYPE aArg2) const\
		{ SynchMessageL(FUNCTIONID,(TAny*)aArg1,(TAny*)aArg2); }\
	inline void NAME(ARG1TYPE aArg1,ARG2TYPE aArg2,TRequestStatus& aStatus) const\
		{ AsynchMessage(FUNCTIONID,aStatus,(TAny*)aArg1,(TAny*)aArg2); }\
	inline void Cancel##NAME##(TRequestStatus& aStatus) const\
		{CancelMessage(aStatus);}

#define MDA_OBJECT_FUNCTION1(NAME,FUNCTIONID,ARGTYPE)\
	inline TInt NAME(ARGTYPE aArg) const\
		{return SynchMessage(FUNCTIONID,(TAny*)aArg);}\
	inline void NAME##L(ARGTYPE aArg) const\
		{SynchMessageL(FUNCTIONID,(TAny*)aArg);}\
	inline void NAME(ARGTYPE aArg,TRequestStatus& aStatus) const\
		{AsynchMessage(FUNCTIONID,aStatus,(TAny*)aArg);}\
	inline void Cancel##NAME##(TRequestStatus& aStatus) const\
		{CancelMessage(aStatus);}

#define MDA_OBJECT_FUNCTION(NAME,FUNCTIONID) \
	inline TInt NAME() const\
		{return SynchMessage(FUNCTIONID);}\
	inline void NAME##L() const\
		{SynchMessageL(FUNCTIONID);}\
	inline void NAME(TRequestStatus& aStatus) const\
		{AsynchMessage(FUNCTIONID,aStatus);}\
	inline void Cancel##NAME##(TRequestStatus& aStatus) const\
		{CancelMessage(aStatus);}

#define MDA_OBJECT_FUNCTIONPACK(NAME,FUNCTIONID,PACKTYPE) const\
	inline TInt NAME(PACKTYPE& aPack)\
		{return SynchPackage(FUNCTIONID,aPack);}\
	inline void NAME##L(PACKTYPE& aPack) const\
		{SynchPackageL(FUNCTIONID,aPack);}\
	inline void NAME(PACKTYPE& aPack,TRequestStatus& aStatus) const\
		{AsynchPackage(FUNCTIONID,aStatus,aPack);}\
	inline void Cancel##NAME##(TRequestStatus& aStatus) const\
		{CancelMessage(aStatus);}

#define MDA_OBJECT_FUNCTIONPACKRET(NAME,FUNCTIONID,PACKTYPEARG,PACKTYPERET)\
	inline TInt NAME(PACKTYPEARG& aPack,PACKTYPERET*& aRet) const\
		{return SynchPackageReturn(FUNCTIONID,aPack,REINTERPRET_CAST(TMdaRawPackage*&,aRet));}\
	inline void NAME##L(PACKTYPEARG& aPack,PACKTYPERET*& aRet) const\
		{SynchPackageReturnL(FUNCTIONID,aPack,REINTERPRET_CAST(TMdaRawPackage*&,aRet));}\
	inline void NAME##LC(PACKTYPEARG& aPack,PACKTYPERET*& aRet) const\
		{SynchPackageReturnLC(FUNCTIONID,aPack,REINTERPRET_CAST(TMdaRawPackage*&,aRet));}\
	inline void NAME(PACKTYPEARG& aPack,PACKTYPERET*& aRet,TRequestStatus& aStatus) const\
		{AsynchPackageReturn(FUNCTIONID,aStatus,aPack,REINTERPRET_CAST(TMdaRawPackage*&,aRet));}\
	inline void Cancel##NAME##(TRequestStatus& aStatus) const\
		{CancelMessage(aStatus);}

#define MDA_OBJECT_OPEN(PARENTCLASS,PARENTFUNC,ARG)\
	inline TInt Open(const PARENTCLASS& aParent)\
		{return SynchCreateMessage(aParent,PARENTFUNC,(TAny*)ARG);}\
	inline void OpenL(const PARENTCLASS& aParent)\
		{SynchCreateMessageL(aParent,PARENTFUNC,(TAny*)ARG);}\
	inline void OpenLC(const PARENTCLASS& aParent)\
		{SynchCreateMessageLC(aParent,PARENTFUNC,(TAny*)ARG);}\
	inline void Open(const PARENTCLASS& aParent,TRequestStatus& aStatus)\
		{AsynchCreateMessage(aParent,PARENTFUNC,aStatus,(TAny*)ARG);}\
	inline void CancelOpen(TRequestStatus& aStatus)\
		{CancelCreateMessage(aStatus);}

#define MDA_OBJECT_OPENREG(CLASSUIDVALUE) MDA_OBJECT_OPEN(RMdaRegistry,EMdaLibraryObjectOpen,CLASSUIDVALUE)

#define MDA_OBJECT_OPENPACK(PARENTCLASS,PARENTFUNC,PACK)\
	inline TInt Open(const PARENTCLASS& aParent,PACK& aArg)\
		{return SynchPackageCreateMessage(aParent,PARENTFUNC,aArg);}\
	inline void OpenL(const PARENTCLASS& aParent,PACK& aArg)\
		{SynchPackageCreateMessageL(aParent,PARENTFUNC,aArg);}\
	inline void OpenLC(const PARENTCLASS& aParent,PACK& aArg)\
		{SynchPackageCreateMessageLC(aParent,PARENTFUNC,aArg);}\
	inline void Open(const PARENTCLASS& aParent,PACK& aArg,TRequestStatus& aStatus)\
		{AsynchPackageCreateMessage(aParent,PARENTFUNC,aStatus,aArg);}\
	inline void CancelOpen(TRequestStatus& aStatus)\
		{CancelCreateMessage(aStatus);}

// End of function definition macros 
// ---------------------------------

class RMdaRegistry : public RMdaObject
	{
public:
	inline RMdaRegistry(RMdaSession& aSession); // Use if you have a connected session
	inline RMdaRegistry(); // Use if session will be connected later
	inline void SetSession(RMdaSession& aSession);
	MDA_OBJECT_FUNCTION(UpdateRegistry,EMdaRegistryUpdate)
	MDA_OBJECT_FUNCTION(Lock,EMSvRegistryIterLock)
//	inline void LockLC(); // Unlock on cleanup
	MDA_OBJECT_FUNCTION(Unlock,EMSvRegistryIterUnlock)
	MDA_OBJECT_FUNCTION1(Reset,EMSvRegistryIterReset,TInt)
	MDA_OBJECT_FUNCTIONPACK(Current,EMSvRegistryIterCurrent,TMdaRegistryEntryDetails)
	MDA_OBJECT_FUNCTIONPACK(PostInc,EMSvRegistryIterPostInc,TMdaRegistryEntryDetails)
	MDA_OBJECT_FUNCTIONPACK(Set,EMSvRegistryIterSet,TMdaRegistryEntryDetails)
	MDA_OBJECT_FUNCTIONPACKRET(GetData,EMSvRegistryIterGetData,TMdaRegistryEntryDetails,TMdaRegistryEntryData)
	// Default control
	MDA_OBJECT_FUNCTIONPACK(SetDefault,EMSvRegistryDefaultSet,TMdaRegistryEntryDetails)
	MDA_OBJECT_FUNCTIONPACK(GetDefault,EMSvRegistryDefaultGet,TMdaRegistryEntryDetails)
	};

inline RMdaRegistry::RMdaRegistry(RMdaSession& aSession)
	{
	iObjectHandle()=EMSvRegistryObject;
	iSession = aSession;
	}

inline RMdaRegistry::RMdaRegistry()
	{
	iObjectHandle()=EMSvRegistryObject;
	} 

inline void RMdaRegistry::SetSession(RMdaSession& aSession)
	{
	iSession = aSession;
	}

// Timers

class RMdaTimerFactory : public RMdaObject
	{
public:
	inline RMdaTimerFactory(RMdaSession& aSession);
	};

class RMdaTimer : public RMdaObject
	{
public:
	MDA_OBJECT_OPEN(RMdaTimerFactory,EMLbTimerFactoryNewTimer,NULL)
	MDA_OBJECT_FUNCTIONPACK(Now,EMLbTimerNow,TMdaTime)
	inline void At(TRequestStatus& aStatus,TTime aTime);
	inline void CancelAt(TRequestStatus& aStatus);
	inline void After(TRequestStatus& aStatus,TTimeIntervalMicroSeconds32 aMicroSeconds);
	inline void CancelAfter(TRequestStatus& aStatus);
	};

#include <Mda\Client\Base.inl>

#endif
