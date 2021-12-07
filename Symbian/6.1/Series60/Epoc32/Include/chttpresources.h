//
// CHTTPResources.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file provides the definition of the CHTTPResources class.
//
// Comments: The HTTP Resources class reads the HTTPUTIL resources file and
//			 provides accessors to the resource values contained in it.
//

#if !defined(__CHTTPRESOURCES_H__)
#define __CHTTPRESOURCES_H__

// System includes
//
#if !defined(__HTTPSTD_H__)
#include <HttpStd.h>
#endif


// Class definition for CHTTPResources
//
class CHTTPResources : public CBase
	{
public:	// Methods

	// Factory method to construct this class.
	//
	// Rtn: a new CHTTPResources object, by ptr. Ownership is transferred to the
	//      caller.
	//
    IMPORT_C
	static CHTTPResources* NewL();

	// Destructor for this class. Removes this object and releases memory held
	// by it
	//
	IMPORT_C
	~CHTTPResources();

	//
	// Resource accessor methods. Note that where pointer-type descriptors are
	// returned for string resources, they must NOT be modified by the caller.
	//

	// Accessor for User Agent name
	//
    IMPORT_C
	TPtrC8 UserAgent() const;

	// Accessor for standard 'accept' string (content types)
	//
    IMPORT_C
	TPtrC8 AcceptContentTypes() const;

	// Accessor for standard Accept-Charset string
	//
    IMPORT_C
	TPtrC8 AcceptCharset() const;

	// Accessor for standard Accept-Language string
	//
    IMPORT_C
	TPtrC8 AcceptLanguage() const;

	// Accessor for Authentication Failed alert message
	//
    IMPORT_C
	TPtrC AuthFailedAlert() const;

	// Accessor for Authentication 'Enter User Name' prompt message
	//
    IMPORT_C
	TPtrC UserNamePrompt() const;

	// Accessor for Authentication default user name
	//
    IMPORT_C
	TPtrC DefaultUserName() const;

	// Accessor for Time-out confirmation prompt
	//
    IMPORT_C
	TPtrC TimeoutPrompt() const;

	// Accessor for Time-out confirmation retry button label
	//
    IMPORT_C
	TPtrC TimeoutRetryLabel() const;

	// Accessor for Time-out confirmation cancel button label
	//
    IMPORT_C
	TPtrC TimeoutCancelLabel() const;

	// Accessor for Degraded cipher strength confirmation prompt
	//
    IMPORT_C
	TPtrC DegCipherPrompt() const;

	// Accessor for Degraded cipher strength accept button label
	//
    IMPORT_C
	TPtrC DegCipherAcceptLabel() const;

	// Accessor for Degraded cipher strength cancel button label
	//
    IMPORT_C
	TPtrC DegCipherRejectLabel() const;

	// Accessor for Missing gateway certificate confirmation prompt
	//
    IMPORT_C
	TPtrC MissingGwCertPrompt() const;

	// Accessor for Missing gateway certificate accept button label
	//
    IMPORT_C
	TPtrC MissingGwCertAcceptLabel() const;

	// Accessor for Missing gateway certificate cancel button label
	//
    IMPORT_C
	TPtrC MissingGwCertRejectLabel() const;

	// Accessor for Size of server headers data buffer
	//
    IMPORT_C
	TInt SvrHdrsMaxDataLen() const;

	// Accessor for Size of negotiated capabilities data buffer
	//
    IMPORT_C
	TInt NegCapsMaxDataLen() const;

	// Accessor for Size of HTTP headers data buffer
	//
    IMPORT_C
	TInt HttpHdrsMaxDataLen() const;

	// Accessor for Size of HTTP body data buffer
	//
    IMPORT_C
	TInt HttpBodyMaxDataLen() const;

	// Accessor for size of transmitted packets in WDP - called Client SDU size
	// (bytes)
	//
    IMPORT_C
	TInt ClientSDUSize() const;

	// Accessor for maximum size of fields expected in WTLS certificates
	//
    IMPORT_C
	TInt CertificateFieldMaxSize() const;

	// Accessor for local port number used when making WAP Stack connections
	//
    IMPORT_C
	TInt LocalPortNumber() const;

	// Accessor for maximum cache size (kB)
	//
    IMPORT_C
	TInt HttpCacheMaxSize() const;

	// Accessor for strict HTTP/1.1 caching flag
	//
    IMPORT_C
	TBool HttpStrict1_1Caching() const;

	// Accessor for 'caching disabled' flag
	//
    IMPORT_C
	TBool HttpCachingDisabled() const;

	// Accessor for 'use acknowledgments capability' flag
	//
    IMPORT_C
	TBool UseAcknowledgmentsCapability() const;

	// Accessor for 'display error decks' flag
	//
    IMPORT_C
	TBool DisplayErrorDecks() const;

private:	// Methods

	// Normal constructor - do non-allocating creation of this class
	//
    IMPORT_C
	CHTTPResources();

	// Second phase construction - any allocation for this class must take place
	// here.
	//
	IMPORT_C
	void ConstructL();

	// Reads the resource file associated with HTTPUTIL and stores locally the
	// strings used for authentication/confirmation/alert dialogs by HTTP.
	//
	void LoadResourcesL();

 	// Panic handler for this class - kills the process in the event of a panic
	//
	// In:
	// aPanicCode - a code enumerating the panic that has occurred
	//
    void Panic(THttpPanicCode aPanicCode) const;

#if defined _DEBUG
	// Debug-only method to allow class invariant testing. Called by the
	// standard macro __TEST_INVARIANT
	//
	void __DbgTestInvariant() const;
#endif

private: // Attributes

//
// HTTP Configuration Settings read from the HTTP resource file
//

	// User agent name
	HBufC8* iUserAgentName;

	// Standard 'accept' string (content types)
	HBufC8* iAcceptContentTypes;

	// Standard 'accept-charset' string
	HBufC8* iAcceptCharset;

	// Standard 'accept-language' string
	HBufC8* iAcceptLanguage;

	// Authentication Failed alert message
	HBufC* iAuthFailedAlert;

	// Authentication 'Enter User Name' prompt message
	HBufC* iUserNamePrompt;
	
	// Authentication default user name
	HBufC* iDefaultUserName;
	
	// Time-out confirmation prompt
	HBufC* iTimeoutPrompt;
	
	// Time-out confirmation retry button label
	HBufC* iTimeoutRetryLabel;
	
	// Time-out confirmation cancel button label
	HBufC* iTimeoutCancelLabel;

	// Degraded cipher strength confirmation prompt
	HBufC* iDegCipherPrompt;
	
	// Degraded cipher strength accept button label
	HBufC* iDegCipherAcceptLabel;
	
	// Degraded cipher strength cancel button label
	HBufC* iDegCipherRejectLabel;

	// Missing gateway certificate confirmation prompt
	HBufC* iMissingGwCertPrompt;
	
	// Missing gateway certificate accept button label
	HBufC* iMissingGwCertAcceptLabel;
	
	// Missing gateway certificate cancel button label
	HBufC* iMissingGwCertRejectLabel;

	// Size of server headers data buffer
	TInt iSvrHdrsMaxDataLen;

	// Size of negotiated capabilities data buffer
	TInt iNegCapsMaxDataLen;

	// Size of HTTP headers data buffer
	TInt iHttpHdrsMaxDataLen;

	// Size of HTTP body data buffer
	TInt iHttpBodyMaxDataLen;

	// Size of Client SDU used in WAP Stack config
	TInt iClientSDUSize;

	// Max size of Client SDU used in WAP Stack config
	TInt iCertificateFieldMaxSize;

	// Local port number, used in WAP Stack config
	TInt iLocalPortNumber;

	// Maximum HTTP cache size (kB)
	TInt iHttpCacheMaxSize;

	// Strict HTTP/1.1 caching flag
	TBool iHttpStrict1_1Caching;

	// Caching disabled flag
	TBool iHttpCachingDisabled;

	// Use acknowledgements capability
	TBool iUseAcknowledgmentsCapability;

	// Display error decks flag
	TBool iDisplayErrorDecks;

//
// End of HTTP Configuration file settings
//
};


#endif // __CHTTPRESOURCES_H__
