// Mda\Server\Environment.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_ENVIRONMENT_H__
#define __MDA_SERVER_ENVIRONMENT_H__

/*
Notes:
Contains definitions of classes forming the Media Server framework environment

	CMdaActive->CActive
Abstract active object base class supporting error callback if RunL leaves.

	CTask->CMdaActive
A task is an operation that must be run in a seperate thread so as not to hold up the
main Media Server thread.

	CMdaProcessor, MMdaProcessor, CMdaMessageProcessor
Set of utility classes that can give objects the ability to perform work actively without
requriing derivation from CActive themselves. CMdaMessageProcessor supports serial
processing of messages.

	CMdaRegistry, CMdaRegistryIterator
The interface to the system object registry - used to scan for available objects 
and create instances of them.

	MdaManager
Static class for getting handles to static objects

*/

// Standard EPOC32 includes required by this header file
#include <E32Base.h>
#include <F32File.h>

// Public Media Server includes
#include <Mda\Server\Base.h>

class CMdaActiveScheduler;
// Internal to Symbian
class CMdaActive : public CActive
	{
public:
	enum TMdaPriorities
		{
		ESystemCriticalPriority = 2000,
		EHardwarePriorityBase = 1000,
		EControllerPriorityBase = 500,
		EServerPriority = 0,
		ENonCriticalTaskPriorityBase = -500,
		EShutdownPriority = -1000
		};
public:
	IMPORT_C CMdaActive(TInt aPriority);
	IMPORT_C void CanLeave();
	IMPORT_C void MdaDeque();
	IMPORT_C void QueueIdle();
	IMPORT_C void CancelIdle();
	virtual void Error(TInt aError)=0; // Must supply error handle
	inline void QueueActive();
private:
	friend class CMdaActiveScheduler;
	TSglQueLink iIdleLink;
	};

class CTaskThread;
// Internal to Symbian
class CTask : public CMdaActive
	{
public:
	IMPORT_C CTask(CTaskThread& iThread, TInt aPriority);
	IMPORT_C virtual void Queue();
protected:
	virtual TInt DoTask()=0; // Called from different thread
	IMPORT_C virtual void DoCancel();
	//
private:
	CTaskThread& iThread;
	TPriQueLink iTaskQueueLink;
	friend CTaskThread;
	};

// Internal to Symbian
class MMdaProcessor
	{
public:
	virtual void ProcessL()=0;
	virtual void ProcessFailed(TInt aError)=0;
	};

// Internal to Symbian
class CMdaProcessor : public CMdaActive
	{
public:
	inline CMdaProcessor(TInt aPriority, MMdaProcessor& aProcess);
	IMPORT_C void QueueProcess();
protected:
	IMPORT_C virtual void RunL();
	IMPORT_C virtual void DoCancel();
	IMPORT_C virtual void Error(TInt aError);
protected:
	MMdaProcessor& iProcess;
	};

// Internal to Symbian
class CMdaMessageProcessor : public CMdaProcessor
	{
public:
	IMPORT_C CMdaMessageProcessor(TInt aPriority, MMdaProcessor& aProcess);
	IMPORT_C ~CMdaMessageProcessor();
	inline CMdaMessage* Message();
	inline void AddMessage(CMdaMessage* aMessage);
	IMPORT_C void CompleteAndNextMessage(TInt aError);
	IMPORT_C void CancelMessage(CMdaMessage* aMessage);
	IMPORT_C void NextMessage();
	IMPORT_C TBool IsQueued(CMdaMessage* aMessage);
	inline TPriQue<CMdaMessage>& MessageQueue();
protected:
	IMPORT_C virtual void RunL();
protected:
	CMdaMessage* iCurrent;
	TPriQue<CMdaMessage> iMessages;
	};

// Internal to Symbian
class CMdaTargetedMessage : public CMdaMessage
	{
public:
	IMPORT_C CMdaTargetedMessage();
	IMPORT_C CMdaTargetedMessage(TInt aPriority);
	IMPORT_C CMdaTargetedMessage(MMdaMessage* aMessage);
	IMPORT_C CMdaTargetedMessage(TInt aPriority, MMdaMessage* aMessage);
	IMPORT_C ~CMdaTargetedMessage();
	//
	IMPORT_C virtual void Cancel();
	//
	inline CMdaObject* Target();
	//
	IMPORT_C virtual void Complete(TInt aVal);
protected:
	IMPORT_C virtual void DoPostL(CMdaObject* aTarget);
private:
	CMdaObject* iTarget;
	};

// Internal to Symbian
class TMdaRegistryEntry
	{
public:
	TUid iType;
	TUid iId;
	TInt8 iPreference;
	TUint8 iVersion;
	TPtrC8 iInfo;
	};

// Internal to Symbian
class CMdaRegistryIterator : public CBase
	{
public:
	inline void Lock();
	inline void Unlock();
	inline TBool IsLocked();
	//
	inline const TMdaRegistryEntry* operator++(TInt);
	inline operator const TMdaRegistryEntry*();
	virtual void Reset(TUid aUid=KNullUid)=0;
protected:
	virtual void DoLock()=0;
	virtual void DoUnlock()=0;
	//
	virtual const TMdaRegistryEntry* PostInc()=0;
	virtual const TMdaRegistryEntry* Current()=0;
	inline CMdaRegistryIterator();
protected:
	TBool iLocked;
	};

// Internal to Symbian
class CMdaRegistry : public CMdaLibrary
	{
public:
	inline static void Update(CMdaMessage* aMessage);
	virtual CMdaRegistryIterator* NewIteratorL(TUid aType)=0;
	//
	virtual void SetDefaultL(TUid aType, TUid aId)=0;
	virtual void GetDefault(TUid aType, TUid& aId)=0;
protected:
	virtual void OperationL(CMdaMessage* aMessage);
	virtual void UpdateL(CMdaMessage* aMessage)=0;
	};

class CMdaTimerFactory;
// Internal to Symbian
class MdaManager
	{
public:
	// Resources
	IMPORT_C static CActiveScheduler& Scheduler();
	IMPORT_C static RFs& Fs();
	IMPORT_C static CMdaRegistry& Registry();
	IMPORT_C static CTaskThread& TaskThread();
	IMPORT_C static CMdaTimerFactory& TimerFactory();
	// Object management
	IMPORT_C static void AddObjectL(CMdaObject* aObject);
	};

// Internal to Symbian
class TMdaPtr8 : public TPtr8
	{
public:
	TMdaPtr8()
		: TPtr8(0,0,0) {};
	inline void Set(const TDes8& aDes)
		{ TPtr8::Set((TUint8*)(aDes.Ptr()),aDes.Length(),aDes.MaxLength()); };
	inline void SetLengthOnly(const TDes8& aDes)
		{ TPtr8::Set((TUint8*)(aDes.Ptr()),aDes.Length(),aDes.Length()); };
	inline void Set(const TPtrC8& aDes)
		{ TPtr8::Set((TUint8*)(aDes.Ptr()),aDes.Length(),aDes.Length()); };
	inline void Shift(TInt aOffset)
		{ SetLength(Length()-aOffset); iMaxLength-=aOffset; iPtr+=aOffset; };
	};

// Internal to Symbian
class CMdaCodec : public CMdaObject
	{
public:
	virtual void Reset() {};
	virtual void ProcessL(TMdaPtr8* aSrc, TMdaPtr8* aDst)=0;
	inline virtual TInt OutputGranularity();
	};

// Internal to Symbian
class CMdaEventBroadcaster : public CBase
	{
public:
	IMPORT_C CMdaEventBroadcaster();
	IMPORT_C ~CMdaEventBroadcaster();
	inline void AddListener(MMdaEventListener& aListener);
	inline void RemoveListener(MMdaEventListener& aListener);
	IMPORT_C void BroadcastEvent(const TMdaEvent& aEvent);
private:
	TSglQue<MMdaEventListener> iListeners;
	};

// Internal to Symbian
class CMdaTimer : public CMdaObject
	{
public:
	static inline void At(CMdaMessage* aMessage,TTime aTime);
	static inline void After(CMdaMessage* aMessage,TTimeIntervalMicroSeconds32 aMicroSeconds);
	static inline void Now(CMdaMessage* aMessage,TMdaTime& aTime);
protected:
	static inline TTime AtTime(CMdaMessage* aMessage);
	static inline TTimeIntervalMicroSeconds32 AfterTime(CMdaMessage* aMessage);
private:
	virtual void AtL(CMdaMessage* aMessage)=0;
	virtual void AfterL(CMdaMessage* aMessage)=0;
	virtual void NowL(CMdaMessage* aMessage)=0;
	virtual void Cancel(CMdaMessage* aMessage)=0;
	// From CMdaObject
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	};

// Internal to Symbian
class CMdaTimerFactory : public CMdaObject
	{
public:
	static inline void NewTimer(CMdaMessage* aMessage);
private:
	// From CMdaObject
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	IMPORT_C virtual void OperationCancel(CMdaMessage* aMessage);
	// New functions
	virtual void NewTimerL(CMdaMessage* aMessage)=0;
	virtual void NewTimerCancel(CMdaMessage* aMessage)=0;
	};

class CMdaObjectLoader; // Forward reference
// Internal to Symbian
class MMdaObjectLoader
	{
public:
	virtual void ObjectLoaderReturn(CMdaObject* aObject, CMdaObjectLoader* aLoader, TInt aError)=0;
	};

// Internal to Symbian
class CMdaObjectLoader : public CMdaTargetedMessage, MMdaMessage
//
// Message that can load objects
//
	{
public:
	IMPORT_C static CMdaObjectLoader* NewL(MMdaObjectLoader& aLoader, TInt aPriority);
	IMPORT_C void LoadObjectL(TUid aObjectUid);
	IMPORT_C void CancelLoadObject();
	inline const TUid ObjectUid();
private:
	CMdaObjectLoader(MMdaObjectLoader& aLoader,TInt aPriority);
	// From MMdaMessage
	virtual void MessageDoComplete(TInt aVal);
	virtual void MessageDoReturnObjectL(TInt aArg, CMdaObject* aObject);
private:
	TUid iObjectUid;
	MMdaObjectLoader& iLoader;	
	CMdaObject* iObject;
	};

// Thread owning objects

// Internal to Symbian
class CMdaThreadObjectBase : public CMdaObject	
	{
protected:
	IMPORT_C CMdaThreadObjectBase();
	IMPORT_C virtual ~CMdaThreadObjectBase();
	// Functions to be called by derived classes
	IMPORT_C void CreateThreadL(TInt aStackSize);
	IMPORT_C void DestroyThread();
	IMPORT_C static CMdaThreadObjectBase* ThreadObject();
	// To be implemented by derived classes
	virtual TInt ThreadFunction()=0;
private:
	static TInt ThreadObjectFunction(TAny* aObject);
private:
	RThread iOwnedThread;
	TThreadId iOwnedThreadId;
	TBool iOwnsThread;
	TUint iThreadInstanceCount;
	TSglQueLink iThreadObjectListLink;
	friend class TMdaThreadObjectList;
	};

#include <Mda\Server\Environment.inl>

#endif
