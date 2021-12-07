// BTManClient.h
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//


#ifndef BTMANCLIENT_H
#define BTMANCLIENT_H

#include <e32std.h>
#include <e32base.h>
#include <btdevice.h>
#include <btsdp.h>

/**
The access requirements set up by a bluetooth service.
An incoming connection must satisfy these criteria before the connection may proceed.
**/
class TBTAccessRequirements
	{
public:
	IMPORT_C TBTAccessRequirements();
	IMPORT_C void SetAuthentication(TBool aPreference);
	IMPORT_C void SetAuthorisation(TBool aPreference);
	IMPORT_C void SetEncryption(TBool aPreference);
	IMPORT_C void SetDenied(TBool aPreference);
	IMPORT_C TBool AuthenticationRequired() const;
	IMPORT_C TBool AuthorisationRequired() const;
	IMPORT_C TBool EncryptionRequired() const;
	IMPORT_C TBool Denied() const;
	IMPORT_C TBool operator==(const TBTAccessRequirements& aRequirements) const;
private:
	TInt iRequirements;
private:
	enum TBTServiceSecuritySettings
		{
		EAuthenticate = 0x01,
		EAuthorise = 0x02,
		EEncrypt = 0x04,
		EDenied = 0x08
		};
	};

/**
The security settings of a bluetooth service.
Contains information regarding the service UID, the protocol and channel IDs and the
access requirements.
**/
class TBTServiceSecurity
	{
public:
	IMPORT_C TBTServiceSecurity(TUid aUid, TInt aProtocolID, TInt aChannelID);
	IMPORT_C TBTServiceSecurity(const TBTServiceSecurity& aService);
	IMPORT_C TBTServiceSecurity();
	IMPORT_C void SetUid(TUid aUid);
	IMPORT_C void SetProtocolID(TInt aProtocolID);
	IMPORT_C void SetChannelID(TInt aChannelID);
	IMPORT_C void SetAuthentication(TBool aPreference);
	IMPORT_C void SetAuthorisation(TBool aPreference);
	IMPORT_C void SetEncryption(TBool aPreference);
	IMPORT_C void SetDenied(TBool aPreference);
	IMPORT_C TBool AuthorisationRequired() const;
	IMPORT_C TBool EncryptionRequired() const;
	IMPORT_C TBool AuthenticationRequired() const;
	IMPORT_C TBool Denied() const;
	IMPORT_C TUid Uid() const;
	IMPORT_C TInt ProtocolID() const;
	IMPORT_C TInt ChannelID() const;
private:
	TUid iUid;	///<The UID of the service.  Will be used by the UI to work out the name of the service when prompting the user.
	TInt iProtocolID;	///<The protocol layer below this service.
	TInt iChannelID;	///<The port number on which the service is sitting
	TBTAccessRequirements iSecurityRequirements;	///<Whether the service requires authentication, authorisation, or encryption.
	};

typedef TPckgBuf<TBTServiceSecurity> TBTServiceSecurityPckg;


/**
The main session class.
Used to create subsessions to access desired functionality.
**/
class RBTMan : public RSessionBase
	{
public:
	IMPORT_C RBTMan();
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;
	};

/**
Subsession base class.
Contains basic subssession functionality.
**/
class RBTManSubSession : public RSubSessionBase
	{
public:
	virtual TInt Open(RBTMan& aSession) = 0;
	virtual void Close() = 0;
	IMPORT_C void CancelRequest(TRequestStatus& aStatus);	//THIS IS NOT ASYNCHRONOUS!!!!
	void LocalComplete(TRequestStatus& aStatus, TInt aErr);
	};

/**
Security Settings Subsession.
Contains the functionality to allow a service to register its security settings with the security manager.
**/
class RBTSecuritySettings : public RBTManSubSession
	{
public:
	IMPORT_C TInt Open(RBTMan& aSession);
	IMPORT_C void Close();
	IMPORT_C void RegisterService(const TBTServiceSecurity& aService, TRequestStatus& aStatus);
	IMPORT_C void UnregisterService(const TBTServiceSecurity& aService, TRequestStatus& aStatus);
private:
	TBTServiceSecurityPckg iRegPckg;	///<Stores the parameters passed in during a service registration.
	TBTServiceSecurityPckg iUnregPckg;	///<Stores the parameters passed in during a service unregistration.
	};

/*
* RNotifier Plugin Utilities
*/

//UIDs of the RNotifier plugins
const TUid KBTManPinNotifierUid={0x100069c9};
const TUid KBTManAuthNotifierUid={0x100069cf};

/**
Struct to allow us to send params from the security manager to the Authorisation RNotifier plugin.
**/
class TBTAuthorisationParams
	{
public:
	TBTDevAddr iBDAddr;
	TUid iUid;
	};

/**
Struct to allow us to send a device name to the Passkey Entry and Authorisation RNotifier plugins.
**/
class TBTNotifierUpdateParams
	{
public:
	TBTDeviceName iName;
	TInt iResult;
	};

typedef TPckgBuf<TBTAuthorisationParams> TBTAuthorisationParamsPckg;
typedef TPckgBuf<TBTNotifierUpdateParams> TBTNotifierUpdateParamsPckg;
typedef TPckgBuf<TBTDevAddr> TBTDevAddrPckg;


/*
* Panic definitions
*/
_LIT(KBTManPanic,"BTManServer");
/// reasons for server panic
enum TBTManServerPanic
	{
	EBTManBadRequest,
	EBTManBadDescriptor,
	EBTManBadSubSessionHandle,
	EBTManBadSubSessionRemove,
	EBTManBadSubSessionType,
	EBTManBadHelper,
	EBTManPinRequesterAlreadyExists,
	EBTManBadBTManMessage,
	EBTManBadRegistryReplyArray,
	EBTManBadServiceArray,
	EBTManBadNotifierArray,
	EBTManBadSubscriberArray,
	EBTManBadConnectionArray,
	EBTManBadNotifierUpdate,
	EBTManBadAuthorisationRequest,
	EBTManBadHCIRequestRequest
	};



#endif
