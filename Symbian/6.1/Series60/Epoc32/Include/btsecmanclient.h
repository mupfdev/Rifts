// BTSecManClient.h
//
// Copyright (c) 1999-2001 Symbian Ltd.  All rights reserved.
//


#ifndef BTSECMANCLIENT_H
#define BTSECMANCLIENT_H

#include <btmanclient.h>

/**
Defines the address of the remote device and the HCI request to perform.
**/
class TBTSecurityHCIRequest
	{
public:
	enum THCIRequest{EAuthenticate, EEncrypt, ENameRequest};
public:
	IMPORT_C TBTSecurityHCIRequest(const TBTDevAddr& aBDAddr, THCIRequest aAction);
	IMPORT_C TBTSecurityHCIRequest();
	IMPORT_C const TBTDevAddr& BDAddr();
	IMPORT_C THCIRequest Action();
private:
	TBTDevAddr iBDAddr;
	THCIRequest iAction;
	};

/**
@internal
The state of a baseband link.
i.e. whether it is authenticated or encrypted, or whether either of these have failed.
**/
class TBTBasebandLinkState
	{
public:
	IMPORT_C TBTBasebandLinkState();
	IMPORT_C TBTBasebandLinkState(TInt aState);
	IMPORT_C void SetLinkUp(TBool aState);
	IMPORT_C void SetLinkDown(TBool aState);
	IMPORT_C void SetAuthenticated(TBool aState);
	IMPORT_C void SetEncrypted(TBool aState);
	IMPORT_C void SetAuthenticationFailed(TBool aState);
	IMPORT_C void SetEncryptionFailed(TBool aState);
	IMPORT_C TBool LinkUp() const;
	IMPORT_C TBool LinkDown() const;
	IMPORT_C TBool Authenticated() const;
	IMPORT_C TBool Encrypted() const;
	IMPORT_C TBool AuthenticationFailed() const;
	IMPORT_C TBool EncryptionFailed() const;
	IMPORT_C TInt Int() const;
protected:
	enum TBTAccReqState
		{
		EAuthenticated = 0x01,
		EAuthorised = 0x02,
		EEncrypted = 0x04,
		EAuthenticationFailed = 0x08,
		EAuthorisationFailed = 0x10,
		EEncryptionFailed = 0x20,
		ELinkUp = 0x40,
		ELinkDown = 0x80
		};
	TInt iState;
	};

/**
Adds the concept of authorisation to the baseband link state to fully describe the state of the link
during the access request.
**/
class TBTAccessRequestState : public TBTBasebandLinkState
	{
public:
	IMPORT_C void Update(TBTBasebandLinkState aState);
	IMPORT_C void SetAuthorisationFailed(TBool aState);
	IMPORT_C void SetAuthorised(TBool aState);
	IMPORT_C TBool Authorised() const;
	IMPORT_C TBool AuthorisationFailed() const;
	};

/**
Struct used to transfer access request params from client to server.
**/
class TBTSecManAccessRequestParams
	{
public:
	TInt iProtocolID;
	TInt iChannelID;
	TBTDevAddr iBDAddr;
	};

/// Possible answers to an access request made to the security manager.
enum TBTSecManAccReqAnswer
	{
	EBTSecManAccessGranted,
	EBTSecManAccessDenied
	};

/**
Struct used to transfer new link key event params from client to server.
**/
class TBTSecManNewLinkKeyParams
	{
public:
	TBTDevAddr iBDAddr;
	TBTLinkKey iLinkKey;
	};

/**
Struct used to transfer new link state event params from client to server.
**/
class TBTSecManNewLinkStateParams
	{
public:
	TBTDevAddr iBDAddr;
	TBTBasebandLinkState iLinkState;
	};

/**
Struct to allow the BT stack to send a device name and error code to the security manager
in response to a device name request.
**/
class TBTDeviceNameRequestResponseParams
	{
public:
	TBTDevAddr iBDAddr;
	TBTDeviceName iDeviceName;
	TInt iResult;
	};

typedef TPckgBuf<TBTSecManAccessRequestParams> TBTSecManAccessRequestParamsPckg;
typedef TPckgBuf<TBTSecManNewLinkKeyParams> TBTSecManNewLinkKeyParamsPckg;
typedef TPckgBuf<TBTSecManNewLinkStateParams> TBTSecManNewLinkStateParamsPckg;
typedef TPckgBuf<TBTSecurityHCIRequest> TBTSecurityHCIRequestPckg;
typedef TPckgBuf<TBTDeviceNameRequestResponseParams> TBTDeviceNameRequestResponseParamsPckg;



/**
Security Manager Subsession.
Contains the functionality specific to the security manager.
**/
class RBTSecMan : public RBTManSubSession
	{
public:
	IMPORT_C TInt Open(RBTMan& aSession);
	IMPORT_C void Close();
	IMPORT_C void AccessRequest(TInt aProtocolID, TInt aChannelID, const TBTDevAddr& aBDAddr,
								TRequestStatus& aStatus);
private:
	TBTSecManAccessRequestParamsPckg iAccReqPckg;	///<Stores the parameters passed in during an access request allowing the server to copy them over at will
	};

/**
Baseband security Subsession.
Provides link-layer services to the BT stack, for example link key and pin retrieval.
Notifies the security manager of any changes in link state, and allows the security manager
to authenticate and encrypt the link should that be necessary.
Allows the security manager to perform device name lookups.
**/
class RBTBasebandSecurity : public RBTManSubSession
	{
public:
	IMPORT_C TInt Open(RBTMan& aSession);
	IMPORT_C void Close();
	IMPORT_C void NewLinkState(const TBTDevAddr& aBDAddr, TBTBasebandLinkState aState, TRequestStatus& aStatus);
	IMPORT_C void HCIRequestHandler(TBTSecurityHCIRequestPckg& aRequest, TRequestStatus& aStatus);
	IMPORT_C void PinRequest(const TBTDevAddr& aBDAddr, TBTPinCode& aAnswer, TRequestStatus& aStatus);
	IMPORT_C void LinkKeyRequest(const TBTDevAddr& aBDAddr, TBTLinkKey& aAnswer, TRequestStatus& aStatus);
	IMPORT_C void NewLinkKey(const TBTDevAddr& aBDAddr, const TBTLinkKey& aLinkKey, TRequestStatus& aStatus);
	IMPORT_C void DeviceNameRequestResponse(const TBTDevAddr& aBDAddr, 
		const TDesC& aName, TInt aResult, TRequestStatus& aStatus);
private:
	TBTSecManNewLinkStateParamsPckg iNewLinkStatePckg;	///<Stores the parameters passed in during a new link state event allowing the server to copy them over at will
	TBTDevAddrPckg iPinReqPckg;	///<Stores the parameters passed in during a pin request allowing the server to copy them over at will
	TBTDevAddrPckg iKeyReqPckg;	///<Stores the parameters passed in during a link key request allowing the server to copy them over at will
	TBTSecManNewLinkKeyParamsPckg iNewKeyPckg;	///<Stores the parameters passed in during a new link key event allowing the server to copy them over at will
	TBTDeviceNameRequestResponseParamsPckg iDeviceNameRequestResponsePckg;	///<Stores the parameters passed in during a device name response.
	};

#endif
