// 
// HttpSecurityS.h
// Copyright © 1997-2000 Symbian Ltd. All rights reserved.
//

// 
// Purpose : Defines all the plug-in classes contained within the HttpSecurity
//			 plug-in DLL.
// 
// Comments: The HTTP Security plug-in provides an implementation of security
//			 policy for use by HTTP when configuring WTLS in the WAP stack.
//
////////////////////////////////////////////////////////////////////////////////
// DISCLAIMER - THE IMPLEMENTATION FILE FOR THIS CLASS CONTAINS DUMMY         //
//              POLICIES FOR TESTING PURPOSES ONLY.  IT SHOULD NOT FORM PART  //
//              OF FINAL DELIVERABLE SOFTWARE.  IN REALITY, DELIVERABLE       //
//              SOFTWARE SHOULD REFLECT ACTUAL LICENSEE OR NETWORK PROVIDER   //
//              SECURITY POLICY.                                              //
////////////////////////////////////////////////////////////////////////////////
//

#ifndef __HTTPSECURITYS_H__
#define __HTTPSECURITYS_H__

// System includes
//
#if !defined (__E32DEF_H__)
#include <e32def.h>
#endif
#if !defined (__E32STD_H__)
#include <e32std.h>
#endif
#if !defined (__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined (__PI_H__)
#include <Pi.h>
#endif

// Local includes
//
#if !defined (__MSECURITYPOLICY_H__)
#include "MSecurityPolicy.h"
#endif

// Wap Logging
//
#if !defined(_LOGDEF_H__)
#include "LogDef.h"
#endif


//
// Enumerated types used by this class
//
enum HttpSecurityPluginIndex
	{
	EHttpSecurityIndex = KDefaultIndex
	};


//
// Constant definitions used by this class
//

// The count of the number of plugins defined for this DLL
//
#define KHttpSecurityPluginCount	EHttpSecurityIndex

// Literals defined for the plugin information
// Firstly define the HttpSecurity plugin's version numbers
//
const TInt KHttpSecurityMajorVN=1;
const TInt KHttpSecurityMinorVN=0;
const TInt KHttpSecurityBuildVN=0;

// HttpSecurity Plug-in name string
//
_LIT(KHttpSecurityName,"HttpSecurity||Implements a GT security policy for WAP HTTP Plug-in||Author : PaulHa.||Copyright © 1997-2000 Symbian Ltd. All rights reserved.");

// HttpSecurity Plug-in data type handled
//
_LIT(KHttpSecurityData,"WTLS/Security Policy");

// HttpSecurity Plug-in UID matched to by the plugin server
//
const TUid KUidHttpSecurityPlugin = {0x10005189};



//
// Class definition for CHttpSecurity
//
class CHttpSecurity : public CPluginBase, public MSecurityPolicy
	{
public: // Methods - for use only by Plug-in Manager - hence not EXPORTed

	// Create an instance of a CHttpSecurity on the heap
	// Leaving if the instance cannot be fully initialised.
	//
	// In:
	// aFs		- an connected file system handle for use by this plug-in.
	// aLibrary - a handle for the DLL in which this plug-in resides
	// aIndex	- the plug-in's DLL index number.
	//
	// Rtn: a new CHTTPManager object, by ptr. Ownership is transferred to the
	//      caller.
	//
	static CHttpSecurity* NewL(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Create an instance of a CHttpSecurity on the heap
	// Leaving if the instance cannot be fully initialised.
	// Post-Condition : The returned pointer remains upon the CleanupStack.
	//
	// In:
	// aFs		- an connected file system handle for use by this plug-in.
	// aLibrary - a handle for the DLL in which this plug-in resides
	// aIndex	- the plug-in's DLL index number.
	//
	// Rtn: a new CHTTPManager object, by ptr. Ownership is transferred to the
	//      caller.
	//
	static CHttpSecurity* NewLC(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Default d'tor. Removes this object and releases memory held by it
	//
	virtual ~CHttpSecurity();

public: // Methods inherited from CPluginBase (See Pi.h) - for use only by
		// Plug-in Manager - hence not EXPORTed

	// Return the version number of the plugin
	//
	TVersion Version() const;

	// Return a descriptor containing the 'name string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'name string' fails.
	//
	HBufC* NameL() const;

	// Return a descriptor containing the 'data string'
	// for this plugin.
	// The caller takes ownership of this descriptor and MUST delete it. 
	// May leave if creation/initialisation of the 'data string' fails.
	//
	HBufC* DataL() const;

public: // Methods inherited from MSecurityPolicy - EXPORTed for client use

	// Is anonymous authentication allowed?
	//
	// Rtn: ETrue if anonymous authentication can be allowed
	//
	IMPORT_C
	virtual TBool AnonymousAuthenticationAllowed();

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
									);

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
									);

	// Obtain the number of cipher suites desired for WTLS
	//
	// Out:
	//  aNumCipherSuites - the number of cipher suites to be requested
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetNumCipherSuites(TInt& aNumCipherSuites);

	// Obtain the cipher suites desired for WTLS - an array of TCipherSuite
	//
	// Out:
	//  aCipherSuites - the cipher suites to be requested
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetCipherSuitesL(RWTLS::CipherSuiteArray& aCipherSuites);

	// Obtain the key refresh rate for WTLS
	//
	// Out:
	//  aRate - the rate value desired. Refreshing occurs every 2^aRate msgs
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetKeyRefreshRate(TUint8& aRate);

	// Obtain the sequence number mode desired for WTLS
	//
	// Out:
	//  aMode - the desired mode
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetSequenceNumberMode(RWTLS::TSequenceNumberMode& aMode);

	// Obtain the record length usage flag for WTLS
	//
	// Out:
	//  aUseRecordLengthFlag : ETrue if record length usage is desired for WTLS
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetRecordLengthUsage(TBool& aUseRecordLengthFlag);

	// Obtain the shared secret used for WTLS
	//
	// Out:
	//  aSharedSecret - the shared secret data
	//
	// Rtn: ETrue if the default is to be overridden
	//
	IMPORT_C
	virtual TBool GetSharedSecretLC(HBufC8*& aSharedSecret);

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
										);
private: // Methods

	// Standard plugin constructor
	// Input				: initialised references to a file session, and library handle
	//						also CHttpSecurity's DLL plugin index number.
	// Return				: nothing
	// Error Behaviour		: none, cannot fail.
	// Post Conditions		: constructed class with partial initialisation.
	//
	CHttpSecurity(RFs& aFs, const RLibrary& aLibrary, TInt aIndex);

	// Complete the initialisation of the plugin
	// May leave if any part of initialisation fails
	// Post-Condition : Fully initialised class when successful.
	//
	void ConstructL();

	// Exports required to preserve BC, by reserving slots in the vtbl. Two
	// variants provided - const and non-const - for caller convenience.
	// NB this are not pure virtual - an implementation will have to be
	// provided to ensure that linking succeeds.
	IMPORT_C
	virtual TAny* Extend_CHttpSecurity(TAny* aArg);
	IMPORT_C
	virtual TAny* Extend_CHttpSecurity(TAny* aArg) const;

private:
	// Counter for the number of times that GetKeyExchangeSuiteXxx() has been called
	//
	TInt iKeyExchangeSuitesSet;

	// Declare the CLogClient pointer (debug only)
	//
	__DECLARE_LOG;

};

#endif    // __HTTPSECURITYS_H__




