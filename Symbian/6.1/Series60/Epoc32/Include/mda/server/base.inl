// Mda\Server\Base.inl
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** Internal to Symbian *************//

inline TBool CMdaMessage::IsPackage()
	{
	return (iFlags&(EMSvFunctionIsPackageFlag>>16)?(TBool)ETrue:(TBool)EFalse);
	}

inline TInt CMdaMessage::PackageLength()
	{
	ASSERT(IsPackage()); // Debug only
	return iArg[1];
	}

inline MMdaMessage* CMdaMessage::Message(CMdaMessage* aMessage)
	{ 
	return aMessage->iMessage;
	}

inline void CMdaMessage::PostL(CMdaObject* aTarget)
	{ 
	DoPostL(aTarget);
	}

inline void CMdaMessage::DoOperationL(CMdaObject* aObject)
	{ 
	aObject->OperationL(this); 
	}

inline void CMdaMessage::DoCancel(CMdaObject* aObject)
	{ 
//	ASSERT(	iFlags&(EMSvFunctionPendingFlag>>16) );
	iFlags |= (EMSvFunctionCancelingFlag>>16);
	aObject->OperationCancel(this); 
	iFlags &= ~(EMSvFunctionCancelingFlag>>16);
	}

inline void CMdaObject::ReturnCreatedObjectL(CMdaObject* aObject, CMdaMessage* aMessage)
	{
	ReturnCreatedObjectArgL(aObject,aMessage,aMessage->iArg[1]);
	}

inline void CMdaLibrary::OpenObject(CMdaMessage* aMessage, TUid aObjectUid)
	{
	aMessage->iFunction = EMdaLibraryObjectOpen;
	aMessage->iArg[0] = aObjectUid.iUid;
	}

inline TUid CMdaLibrary::GetOpenObjectUid(CMdaMessage* aMessage)
	{
	return TUid::Uid(aMessage->iArg[0]);
	}

inline void CMdaMessage::SetPriority(TInt aPriority)
	{
	iLink.iPriority = aPriority;
	}

inline void CMdaMessage::Panic(const TDesC& aCategory, TInt aReason)
	{
	iMessage->MessageDoPanic(aCategory,aReason);
	}

inline CMdaObject* CMdaMessage::GetObjectL(TInt aArg)
	{
	return iMessage->MessageDoGetObjectL(aArg);
	}

inline void CMdaMessage::ReadDesL(TInt aArg, TDes8& aDes)
	{	
	iMessage->MessageDoReadDesL(aArg,aDes);
	}

inline void CMdaMessage::WriteDesL(TInt aArg, const TDesC8& aDes)
	{
	iMessage->MessageDoWriteDesL(aArg,aDes);
	}

inline void CMdaMessage::ReturnObjectL(TInt aArg, CMdaObject* aObject)
	{
	iMessage->MessageDoReturnObjectL(aArg,aObject);
	}

inline TBool CMdaMessage::IsCanceling()
	{
	return (iFlags&(EMSvFunctionCancelingFlag>>16));
	}

inline CMdaObject* CMdaObject::Cast(CObject* aObject)
	{
	return STATIC_CAST(CMdaObject*,aObject);
	}

// MDA_TODO macro

#define __MDATODO 1

#ifdef __MDATODO
#define __MDATODO_STR2__(x) #x
#define __MDATODO_STR1__(x) __MDATODO_STR2__(x)
#define __MDATODO_LOC__ __FILE__ "("__MDATODO_STR1__(__LINE__)") : "
#define MDA_TODO(T) message(__MDATODO_LOC__ T)
#else
#define MDA_TODO(T) 
#endif
