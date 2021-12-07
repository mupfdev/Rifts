// MIUTSET.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__MIUTSET_H__)
#define __MIUTSET_H__

#if !defined (__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif

#if !defined (__MIUTHDR_H__)
#include "miuthdr.h"
#endif

#include <msvstore.h>	// CMsvStore etc.

class CMsvStore;
class RMsvWriteStream;
class RMsvReadStream;

const TInt KMaxSettingStringLength = 1024;

const TUid KUidMsgTypeSMTP			= {0x10001028};	// 268439592
const TUid KUidMsgTypePOP3			= {0x10001029};	// 268439593
const TUid KUidMsgTypeIMAP4			= {0x1000102A};	// 268439594
const TUid KUidMsgTypeSMTPServer	= {0x10003923};	// 268450083

// Base class for storing and restoring email settings
class CImBaseEmailSettings : public CBase
	{
public:
	IMPORT_C CImBaseEmailSettings();
	IMPORT_C ~CImBaseEmailSettings();
	IMPORT_C void Reset();

	// streaming operations
	IMPORT_C void InternalizeL(RMsvReadStream& aWriteStream);
	IMPORT_C void ExternalizeL(RMsvWriteStream& aReadStream) const;
	IMPORT_C virtual void RestoreL(CMsvStore& aMessageStore);
	IMPORT_C virtual void StoreL(CMsvStore& aMessageStore) const;

	// Server Name -> post office name
	IMPORT_C const TPtrC ServerAddress() const;
	IMPORT_C void SetServerAddressL(const TDesC& aServerAddress);

	// User Name -> email address
	IMPORT_C const TPtrC UserAddress() const;
	IMPORT_C void SetUserAddressL(const TDesC& aUserAddress);

	// Port number
	IMPORT_C const TUint Port() const;
	IMPORT_C void SetPort(const TUint aPortNumber);

	// Version number of this stream (incremented when contents of class is altered)
	IMPORT_C const TUint16 Version() const;
	IMPORT_C void SetVersion(const TUint16 aVersion);

	// Secure sockets
	IMPORT_C const TBool SecureSockets() const;
	IMPORT_C void SetSecureSockets(TBool aFlag);

	// Copy and Equality constructors
	IMPORT_C CImBaseEmailSettings& CopyL(const CImBaseEmailSettings& aCImBaseEmailSettings);
	IMPORT_C TBool operator==(const CImBaseEmailSettings& aCImBaseEmailSettings) const;

protected:
	enum TImBaseEmailSettings
		{
		EBaseEmailSettingsClearFlag			= 0x00000000,
		EBaseEmailSettingsSecureSockets		= 0x00000001,
		EBaseEmailSettingsLastUsedFlag		= EBaseEmailSettingsSecureSockets << 1	//0x00000002
		};
	TUint16 iVersion;		// Version number for stream persisted in store
	TUint32 iPortNumber;	// the port the TCP/IP connection be made on

	TUint32 iFlags;			// space for flags info (now and for future)
	TUint32 iData;			// space for flags info (for future)
private:
	HBufC* iServerAddress;	// remote server's IP address
	HBufC* iUserAddress;	// my IP address
	};

#endif 