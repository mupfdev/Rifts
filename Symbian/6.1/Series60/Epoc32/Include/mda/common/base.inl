// Mda\Common\Base.inl
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Inline functions for package classes defined in MdaBase.h

inline TPtr8& TMdaRawPackage::Package()
	{ 
	((TMdaRawPackage*)this)->iThis.Set((TUint8*)this,iThis.Length(),iThis.MaxLength()); 
	return iThis; 
	}

inline const TPtr8& TMdaRawPackage::Package() const
	{ 
	((TMdaRawPackage*)this)->iThis.Set((TUint8*)this,iThis.Length(),iThis.MaxLength()); 
	return iThis; 
	}

inline void TMdaRawPackage::SetSize(TInt aDerivedSize)
	{ 
	iThis.Set((TUint8*)this,aDerivedSize,aDerivedSize);
	}

inline void TMdaOpenPackage::SetHandleAddress(TPckgBuf<TInt>* aHandle)
	{
	iHandle = aHandle;
	}

inline TPckgBuf<TInt>* TMdaOpenPackage::GetHandleAddress() const
	{
	return iHandle;
	}

inline TUid TMdaPackage::Type() const
	{ 
	return iType; 
	}

inline TUid TMdaPackage::Uid() const
	{ 
	return iUid;
	}

inline TBool TMdaPackage::operator==(const TMdaPackage& aPackage)
	{
	return ((aPackage.Type()==Type())&&(aPackage.Uid()==Uid()));
	}

inline void TMdaPackage::SetUid(TUid aUid)
	{
	iUid = aUid;
	}

inline TInt TMdaReturnPackage::ReturnSize() const
	{ 
	return iRetSize;
	}

inline void TMdaReturnPackage::SetReturnSize(TInt aReturnSize)
	{
	iRetSize = aReturnSize;
	}

inline TMdaRawPackage::TMdaRawPackage(TInt aDerivedSize)
#pragma warning( disable : 4355 )	// 'this' : used in base member initializer list
: iThis((TUint8*)this,aDerivedSize,aDerivedSize) 
#pragma warning( default : 4355 )
	{ 
	}

inline TMdaPackage::TMdaPackage(TUid aType, TUid aUid, TInt aDerivedSize)
: TMdaRawPackage(aDerivedSize),iType(aType),iUid(aUid)
	{ 
	}

inline TMdaOpenPackage::TMdaOpenPackage(TInt aDerivedSize) :
TMdaRawPackage(aDerivedSize)
	{
	}

inline TMdaReturnPackage::TMdaReturnPackage(TUid aType, TUid aUid, TInt aDerivedSize)
: TMdaPackage(aType,aUid,aDerivedSize)
	{ // Zero the package
	iRetSize = 0;
	}	

inline TMdaEventPackage::TMdaEventPackage()
#pragma warning( disable : 4355 )	// 'this' : used in base member initializer list
: TMdaRawPackage(sizeof(TMdaEventPackage)),iMaxEvents(1),iValidEvents(0)
#pragma warning( default : 4355 )
// For single events
	{
	}

inline TInt TMdaEventPackage::EventCount() const
	{
	return iValidEvents;
	}

inline TInt TMdaEventPackage::MaxEvents() const
	{
	return iMaxEvents;
	}

inline const TMdaEvent& TMdaEventPackage::Event()
	{ // First event
	ASSERT(iValidEvents>=1);
	return iFirstEvent.iEvent;
	}

inline const TMdaEvent& TMdaEventPackage::Event(TInt aIndex)
	{
	ASSERT(aIndex<iValidEvents);
	TMdaObjectEvent* ptr = &iFirstEvent;
	ptr += aIndex;
	return ptr->iEvent;
	}

inline TInt TMdaEventPackage::EventFrom()
	{ // First event
	ASSERT(iValidEvents>=1);
	return iFirstEvent.iHandle;
	}

inline TInt TMdaEventPackage::EventFrom(TInt aIndex)
	{
	ASSERT(aIndex<iValidEvents);
	TMdaObjectEvent* ptr = &iFirstEvent;
	ptr += aIndex;
	return ptr->iHandle;
	}



inline TMdaEventPackage::TMdaEventPackage(TInt aMaxEvents)
#pragma warning( disable : 4355 )	// 'this' : used in base member initializer list
: TMdaRawPackage(sizeof(TMdaEventPackage)+((aMaxEvents-1)*sizeof(TMdaObjectEvent))),iMaxEvents(aMaxEvents),iValidEvents(0)
#pragma warning( default : 4355 )
	{
	}

inline HMdaEventPackage::HMdaEventPackage(TInt aMaxEvents) :
TMdaEventPackage(aMaxEvents)
	{
	}

inline HMdaEventPackage* HMdaEventPackage::NewL(TInt aMaxEvents)
	{
	return new (sizeof(TMdaObjectEvent)*aMaxEvents) HMdaEventPackage(aMaxEvents);
	}

inline HMdaEventPackage* HMdaEventPackage::NewLC(TInt aMaxEvents)
	{
	HMdaEventPackage* self = HMdaEventPackage::NewL(aMaxEvents);
	CleanupDeletePushL(self);
	return self;
	}

template <TInt S>
inline TMdaEventPackageBuf<S>::TMdaEventPackageBuf() :
TMdaEventPackage(S)
	{
	}

inline TMdaRegistryEntryDetails::TMdaRegistryEntryDetails() :
TMdaReturnPackage(KNullUid,KNullUid,sizeof(TMdaRegistryEntryDetails))
	{
	}

inline TMdaRegistryEntryDetails::TMdaRegistryEntryDetails(TUid aType) :
TMdaReturnPackage(aType,KNullUid,sizeof(TMdaRegistryEntryDetails))
	{
	}

inline TMdaRegistryEntryDetails::TMdaRegistryEntryDetails(TUid aType,TUid aUid) :
TMdaReturnPackage(aType,aUid,sizeof(TMdaRegistryEntryDetails))
	{
	}

inline TMdaRegistryEntryDetails::TMdaRegistryEntryDetails(TUid aType, TUid aUid,TInt aDataSize) :
TMdaReturnPackage(aType,aUid,sizeof(TMdaRegistryEntryDetails))
	{
	SetReturnSize(aDataSize);
	}

inline TMdaRegistryEntryData::TMdaRegistryEntryData(TInt aDataSize) :
TMdaRawPackage(sizeof(TMdaRegistryEntryData)+aDataSize)
	{
	}

inline const TPtrC8 TMdaRegistryEntryData::Data()
	{
	TInt dataSize = Package().Length() - sizeof(TMdaRegistryEntryData);
	TUint8* ptrToData = ((TUint8*)this) + sizeof(TMdaRegistryEntryData);
	return TPtrC8(ptrToData,dataSize);
	}

inline TMdaTime::TMdaTime()
: TMdaRawPackage(sizeof(TMdaTime))
	{}

