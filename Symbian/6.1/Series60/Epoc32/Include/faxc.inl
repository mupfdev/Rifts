// FAXC.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

inline CFaxHeader& CFaxMtmClient::FaxHeader()
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvMessageEntry, User::Panic(_L("FAXC"), 1));
	return *iFaxHeader;
	}

inline const CFaxHeader& CFaxMtmClient::FaxHeader() const
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvMessageEntry, User::Panic(_L("FAXC"), 1));
	return *iFaxHeader;
	}

inline TMTMFaxSettings& CFaxMtmClient::FaxSettings()
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvServiceEntry, User::Panic(_L("FAXC"), 1));
	return iFaxSettings;
	}

inline const TMTMFaxSettings& CFaxMtmClient::FaxSettings() const
	{
	__ASSERT_DEBUG(iMsvEntry!=NULL, User::Panic(_L("FAXC"), 2));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvServiceEntry, User::Panic(_L("FAXC"), 1));
	return iFaxSettings;
	}
