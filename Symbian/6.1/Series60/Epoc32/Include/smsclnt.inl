///////////////////////////////////////////////////////////////////////////////
//
// SMSCLNT.H
//
// Copyright (c) 2000 Symbian Ltd. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////

#include <msvuids.h>
#include "smcmmain.h"

inline CSmsHeader& CSmsClientMtm::SmsHeader()
	{
	__ASSERT_DEBUG(iMsvEntry, Panic(ESmscEntryNotSet));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvMessageEntry, Panic(ESmscWrongContextType));
	return *iSmsHeader;
	}

inline const CSmsHeader& CSmsClientMtm::SmsHeader() const
	{
	__ASSERT_DEBUG(iMsvEntry, Panic(ESmscEntryNotSet));
	__ASSERT_DEBUG(iMsvEntry->Entry().iType==KUidMsvMessageEntry, Panic(ESmscWrongContextType));
	return *iSmsHeader;
	}

inline CSmsSettings& CSmsClientMtm::ServiceSettings()
	{
	__ASSERT_DEBUG(iMsvEntry, Panic(ESmscEntryNotSet));
	__ASSERT_DEBUG(iServiceSettings, Panic(ESmscSettingsNotSet));
	return *iServiceSettings;
	}

inline const CSmsSettings& CSmsClientMtm::ServiceSettings() const
	{	
	__ASSERT_DEBUG(iMsvEntry, Panic(ESmscEntryNotSet));
	__ASSERT_DEBUG(iServiceSettings, Panic(ESmscSettingsNotSet));
	return *iServiceSettings;
	}

inline TInt CSmsClientMtm::ServiceId() const
	{
	return iServiceId;
	}
