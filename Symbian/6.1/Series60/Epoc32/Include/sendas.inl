// SENDAS.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

inline const CDesCArray& CSendAs::AvailableMtms() const
	{
	return *iAvailNameArray;
	}

inline CClientMtmRegistry& CSendAs::ClientRegistry()
	{
	return *iClientRegistry;
	}

inline CBaseMtm& CSendAs::ClientMtm()
	{
	return *iClientMtm;
	}

inline const CDesCArray& CSendAs::AvailableServices() const
	{
	return *iServiceNameArray;
	}

inline TMsvId CSendAs::MessageId()
	{
	return iMessageId;
	}
