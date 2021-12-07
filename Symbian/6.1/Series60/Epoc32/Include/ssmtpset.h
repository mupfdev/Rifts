// SSMTPSET.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#if !defined (__SSMTPSET_H__)
#define __SSMTPSET_H__

#if !defined (__MSVUIDS_H__)
#include <MSVUIDS.H>
#endif

#include "miutset.h"

class CMsvStore;
class RMsvWriteStream;
class RMsvReadStream;


const TUint16 KImSmtpServerSettingsVersion = 2;	// identify which version of this class has been stored
const TUint32 KSSMTPDefaultPortNumber = 25;

class TSSmtpProgress
	{
public:
	enum TSSmtpProgressType {
		EStarting,
		EListening,
		EAccepting,
		EAuthorising,
		EReceiving,
		EDisconnecting,
		EDisconnected,
		ESSmtpMaxProgressValue=EDisconnected
		};

	TSSmtpProgressType	iSmtpProgress;
	TInt				iNoBytesReceived;
	TInt				iTotalMsgs;
	TInt				iErrorCode; // client side needs to be informed of an error
	};

class CImSSmtpSettings : public CImBaseEmailSettings
	{
public:
	IMPORT_C CImSSmtpSettings();
	IMPORT_C ~CImSSmtpSettings();
	IMPORT_C void Reset();

	// streaming operations
	IMPORT_C void InternalizeL( RMsvReadStream&  );
	IMPORT_C void ExternalizeL( RMsvWriteStream& ) const;
	IMPORT_C void RestoreL( CMsvStore& aMessageStore );
	IMPORT_C void StoreL  ( CMsvStore& aMessageStore ) const;

	// EmailAddress
	IMPORT_C const TPtrC EmailAddress() const;
	IMPORT_C void SetEmailAddressL( const TDesC& );

	// PhoneNumber
	IMPORT_C const TPtrC PhoneNumber() const;
	IMPORT_C void SetPhoneNumberL( const TDesC& );

	IMPORT_C CImSSmtpSettings& CopyL(const CImSSmtpSettings& aCImSSmtpSettings);
	IMPORT_C TBool operator==(const CImSSmtpSettings& aCImSSmtpSettings) const;

private:
	HBufC*					iEmailAddress;  // local device user Email Address
	HBufC*					iPhoneNumber;   // local Phone Number
	};

#endif

