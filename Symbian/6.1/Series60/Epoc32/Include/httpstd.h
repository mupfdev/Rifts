//
// httpstd.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file sets the values for HTTP's return/error codes and
//			 panic codes.
//

#if !defined(__HTTPSTD_H__)
#define __HTTPSTD_H__

// System includes
//
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__WAPENGSTD_H__)
#include <WapEngStd.h>
#endif


// Base values of code ranges
//
enum{
	EHttpRetCodeBase     = -20000,
	EHttpPanicCodeBase   = EHttpRetCodeBase - 200
	};

// Return/leave codes for HTTPUTIL and HTTP plugins
//
typedef enum 
	{
	// Informational (+ve) status codes
	EHttp_401_Unauthorized		  = KHttpPluginStatusBase + 401,// occurs when HTTP authentication is used, username/password dialogs raised as a response. Need to consider how UI deals with authentication failures here.
	EHttpAuthenticationAborted	  = KHttpPluginStatusBase + 11,// The user cancelled the password box
	EHttpAuthenticationFailed	  = KHttpPluginStatusBase + 10,// The user's password was rejected by the origin server
	EHttpNoError				  = KErrNone,			  // No error
	// Error (-ve) status codes
	EHttpGeneralError			  = EHttpRetCodeBase,	  // Unspecified error condition
	EHttpCannotFindServer		  = EHttpRetCodeBase - 1, // URL specified a non-existent or inaccessible domain
	EHttpCannotFindPlugin		  = EHttpRetCodeBase - 2, // Plug-in server failed to create an HTTP plugin
	EHttpUnsupportedMethod		  = EHttpRetCodeBase - 3, // An HTTP method was specified that is not supported
	EHttpWapAPReadFailure		  = EHttpRetCodeBase - 4, // An error occurred when reading the WAP AP from CommsDB
	EHttpNetDialSetupFailed		  = EHttpRetCodeBase - 5, // Failed to configure Net Dial
	EHttpWtlsConfigFailed		  = EHttpRetCodeBase - 6, // Failed to configure the WTLS layer of the WAP Stack
	EHttpWtlsBadServerCert		  = EHttpRetCodeBase - 7, // WTLS rejected the certificate obtained from the WAP GW
	EHttpWtlsServerCertRejected	  = EHttpRetCodeBase - 8, // The user rejected the certificate from the WAP GW
	EHttpWtlsCipherRejected		  = EHttpRetCodeBase - 9, // The user rejected the cipher strength negotiated in WTLS
	EHttpGatewayCannotBeReached	  = EHttpRetCodeBase - 10,// A session could not be established with the WAP Gateway
	EHttpGatewayTransactionAbort  = EHttpRetCodeBase - 11,// A transaction was aborted by the gateway or the stack
	EHttpGatewaySessionDisconnect = EHttpRetCodeBase - 12,// The session was disconnected by the WAP Gateway
	EHttpCancellationAbort		  = EHttpRetCodeBase - 13,// Error code for leave when cancellation has occured during RunL()
	EHttpReceivingErrorDeck		  = EHttpRetCodeBase - 14 // Could not find document, so receiving an error deck
	} THttpReturnCode;

// Note that HTTP Status codes series 40x and 50x are error conditions. They
// will be added to the EHttpRetCodeBase to send to the HTTP Data Provider
// observer. e.g. HTTP/404 will become EHttpRetCodeBase-404 = -20404.  The
// exception to this rule is HTTP/401, which gets fully handled in HTTP and
// so is treated above as an informational status message.


// Panic codes for HTTPUTIL and HTTP plugins
//
typedef enum 
    {
	EHttpGeneralPanic				= EHttpPanicCodeBase,		// Unspecified panic condition
    EHttpDialInNotSupported			= EHttpPanicCodeBase - 1,	// The WAP Access Point specified a dial-in ISP!
	EHttpWapAccessPointInfoChanged	= EHttpPanicCodeBase - 2,	// The WAP AP info changed between initial read and
																// the subsequent NetDial override (debug only)
	EHttpCommDBContainsBadData		= EHttpPanicCodeBase - 3,	// Comms DB contains garbled/inconsistent WAP AP data
	EHttpConnectionLessNotSupported	= EHttpPanicCodeBase - 4,	// Comms DB specified a CL mode, which isn't available (yet)
	EHttpNoHandlerAvailable			= EHttpPanicCodeBase - 5,	// Very bad situation for HTTP Methods
	EHttpResourceFileLoadFailed		= EHttpPanicCodeBase - 6,	// Resource file missing or corrupt
	EHttpReservedForFutureExpansion	= EHttpPanicCodeBase - 7	// Feature not available - reserved for BC only
    } THttpPanicCode;


#endif // __HTTPSTD_H__
