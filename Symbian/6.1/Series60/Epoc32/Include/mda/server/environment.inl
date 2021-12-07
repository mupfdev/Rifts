// Mda\Server\Environment.inl
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** Internal to Symbian *************//

inline void CMdaActive::QueueActive()
	{
	SetActive();
	}

inline CMdaMessage* CMdaMessageProcessor::Message()
	{ 
	return iCurrent; 
	}

inline CMdaProcessor::CMdaProcessor(TInt aPriority, MMdaProcessor& aProcess)
: CMdaActive(aPriority), iProcess(aProcess) 
	{
	}

inline void CMdaMessageProcessor::AddMessage(CMdaMessage* aMessage)
	{ 
	iMessages.Add(*aMessage); 
	if (Message()==NULL)
		QueueProcess(); 
	}

inline TPriQue<CMdaMessage>& CMdaMessageProcessor::MessageQueue()
	{
	return iMessages;
	}

inline CMdaObject* CMdaTargetedMessage::Target()
	{ 
	return iTarget;
	}

inline CMdaRegistryIterator::CMdaRegistryIterator() 
	{
	}

inline void CMdaRegistryIterator::Lock()
	{
	ASSERT(!iLocked);
	DoLock();
	iLocked = ETrue;
	}

inline void CMdaRegistryIterator::Unlock()
	{
	ASSERT(iLocked);
	DoUnlock();
	iLocked = EFalse;
	}

inline TBool CMdaRegistryIterator::IsLocked()
	{
	return iLocked;
	}

inline const TMdaRegistryEntry* CMdaRegistryIterator::operator++(TInt)
	{
	ASSERT(iLocked);
	return PostInc();
	}

inline CMdaRegistryIterator::operator const TMdaRegistryEntry*()
	{
	ASSERT(iLocked);
	return Current();
	}

inline void CMdaRegistry::Update(CMdaMessage* aMessage)
	{
	aMessage->iFunction = EMdaRegistryUpdate;
	}

inline void CMdaEventBroadcaster::AddListener(MMdaEventListener& aListener)
	{
	iListeners.AddLast(aListener);
	}

inline void CMdaEventBroadcaster::RemoveListener(MMdaEventListener& aListener)
	{
	iListeners.Remove(aListener);
	}

inline void CMdaTimer::At(CMdaMessage* aMessage,TTime aTime)
	{
	ASSERT(aMessage);
	aMessage->iFunction = EMLbTimerAt;
	aMessage->iArg[0] = aTime.Int64().High();
	aMessage->iArg[1] = aTime.Int64().Low();
	}

inline void CMdaTimer::After(CMdaMessage* aMessage,TTimeIntervalMicroSeconds32 aMicroSeconds)
	{
	ASSERT(aMessage);
	aMessage->iFunction = EMLbTimerAfter;
	aMessage->iArg[0] = aMicroSeconds.Int();
	}

inline void CMdaTimer::Now(CMdaMessage* aMessage,TMdaTime& aTime)
	{
	ASSERT(aMessage);
	aMessage->iFunction = EMLbTimerNow;
	aMessage->iArg[0] = (TInt)&aTime;
	aMessage->iArg[1] = sizeof(TMdaTime);
	}

inline TTime CMdaTimer::AtTime(CMdaMessage* aMessage)
	{
	ASSERT(aMessage);
	return TTime(TInt64(aMessage->iArg[0],aMessage->iArg[1]));
	}

inline TTimeIntervalMicroSeconds32 CMdaTimer::AfterTime(CMdaMessage* aMessage)
	{
	ASSERT(aMessage);
	return TTimeIntervalMicroSeconds32(aMessage->iArg[0]);
	}

inline void CMdaTimerFactory::NewTimer(CMdaMessage* aMessage)
	{
	ASSERT(aMessage);
	aMessage->iFunction = EMLbTimerFactoryNewTimer;
	}

inline const TUid CMdaObjectLoader::ObjectUid()
	{
	return iObjectUid;
	}

inline TInt CMdaCodec::OutputGranularity()
	{
	return 4;
	}
