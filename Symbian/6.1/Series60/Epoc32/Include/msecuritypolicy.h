// 
// MSecurityPolicy.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file provides a definition of the MSecurityPolicy interface.
//
// Comments: The MSecurityPolicy interface defines the API for an HTTP
//			 Security Policy.  It provides a hook for each point in the process
//			 of a WTLS handshake where HTTP needs to make some decision about
//			 what to request or how to progress.
//


#if !defined(__MSECURITYPOLICY_H__)
#define __MSECURITYPOLICY_H__

#if !defined(__WAPCLI_H__)
#include "WapCli.h"				// Definition of the WAP Server, client side
#endif

class MSecurityPolicy
//
// Interface base for a security policy provider
//
	{
public: // Types

	// An enumeration of actions to be taken in response to the negotiated
	// cipher, as obtained from the WTLS layer of the stack. In circumstances
	// where a lower cipher strength was obtained than requested, the policy
	// may choose to abandon connection or to ask the user if they wish to
	// continue.
	//
	enum TCipherResponse
		{
		ENeverConnect = 0,
		EAskToConnect = 1,
		EAlwaysConnect = 2
		};

public: // Methods

	// Is anonymous authentication allowed?
	//
	// Rtn: ETrue if anonymous authentication can be allowed
	//
	IMPORT_C
	virtual TBool AnonymousAuthenticationAllowed()=0;

	// Obtain the key exchange suite for WTLS, for a non-anonymous session (ie.
	// on in which the server-certificate is obtained and authenticated)
	//
	// Out:
	//  aSuite	- the key exchange suite desired for WTLS
	//  aIdType	- the ID type desired for WTLS
	//  aKeyId	- the key ID desired for WTLS
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetKeyExchangeSuiteNormal(
									RWTLS::TKeyExchangeSuite& aSuite,
									RWTLS::TIdType& aIdType,
									TDes8& aKeyId
									)=0;

	// Obtain the key exchange suite for WTLS, for an anonymous session (ie.
	// on in which no server-certificate is obtained)
	//
	// Out:
	//  aSuite	- the key exchange suite desired for WTLS
	//  aIdType	- the ID type desired for WTLS
	//  aKeyId	- the key ID desired for WTLS
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetKeyExchangeSuiteAnon(
									RWTLS::TKeyExchangeSuite& aSuite,
									RWTLS::TIdType& aIdType,
									TDes8& aKeyId
									)=0;

	// Obtain the number of cipher suites desired for WTLS
	//
	// Out:
	//  aNumCipherSuites - the number of cipher suites to be requested
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetNumCipherSuites(TInt& aNumCipherSuites)=0;

	// Obtain the cipher suites desired for WTLS - an array of TCipherSuite
	//
	// Out:
	//  aCipherSuites - the cipher suites to be requested
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetCipherSuitesL(RWTLS::CipherSuiteArray& aCipherSuites)=0;

	// Obtain the key refresh rate for WTLS
	//
	// Out:
	//  aRate - the rate value desired. Refreshing occurs every 2^aRate msgs
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetKeyRefreshRate(TUint8& aRate)=0;

	// Obtain the sequence number mode desired for WTLS
	//
	// Out:
	//  aMode - the desired mode
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetSequenceNumberMode(RWTLS::TSequenceNumberMode& aMode)=0;

	// Obtain the record length usage flag for WTLS
	//
	// Out:
	//  aUseRecordLengthFlag : ETrue if record length usage is desired for WTLS
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetRecordLengthUsage(TBool& aUseRecordLengthFlag)=0;

	// Obtain the shared secret used for WTLS
	//
	// Out:
	//  aSharedSecret - the shared secret data
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetSharedSecretLC(HBufC8*& aSharedSecret)=0;

	// Find out what action to take with the actual ciphers negotiated with
	// the stack
	//
	// In:
	//  aSuite	- the negotiated cipher suite, or NULL if none was reported by
	//            the stack
	//  aMode	- the negotiated mode, or NULL if none was reported by the stack
	//
	// Rtn: TCipherResponse enumerates the response to be taken
	//
	IMPORT_C
	virtual TCipherResponse GetNegotiatedCipherAction(
										RWTLS::TCipherSuite* aSuite,
										RWTLS::TSequenceNumberMode* aMode
										)=0;

private: // Methods

	// Exports required to preserve BC, by reserving slots in the vtbl. Two
	// variants provided - const and non-const - for caller convenience.
	// NB this are not pure virtual - an implementation will have to be
	// provided to ensure that linking succeeds.
	IMPORT_C
	virtual TAny* Extend_MSecurityPolicy(TAny* aArg);
	IMPORT_C
	virtual TAny* Extend_MSecurityPolicy(TAny* aArg) const;
	};

#endif
