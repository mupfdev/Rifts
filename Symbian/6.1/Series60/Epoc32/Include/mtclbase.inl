// MTCLBASE.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if defined(_DEBUG)
_LIT(KMtclPanicString, "MSGS");
#endif

inline TUid CBaseMtm::Type() const
	{
	return iRegisteredMtmDll.MtmTypeUid();
	}

inline CRichText& CBaseMtm::Body()
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275)); 
	return *iRichTextBody;
	}

inline const CRichText& CBaseMtm::Body() const
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275));
	return *iRichTextBody;
	}

inline CMsvEntry& CBaseMtm::Entry() const
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275));
	return *iMsvEntry;
	};

inline const CDesCArray& CBaseMtm::AddresseeList() const
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(KMtclPanicString, 275));
	return *iAddresseeList;
	}

inline TBool CBaseMtm::HasContext() const
	{
	return (iMsvEntry!=NULL);
	}

inline CMsvSession& CBaseMtm::Session()
	{
	return iSession;
	}
