/*
* ============================================================================
*  Name     : MmsErrors.h
*  Part of  : MmsEngine
*
*  Description:
*     MmsEngine error codes
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef MMSERRORS_H
#define MMSERRORS_H

// INCLUDES

// CONSTANTS

// MACROS

// DATA TYPES

// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS


#define MMS_ERROR_BASE -11000

// error codes must be defined as enum so that they can be
// included by a source file that uses the error codes as ints,
// and mmsserver.rss file that needs the error numbers for defining
// error actions.

// All errors are define relative to MMS_ERROR_BASE
enum
    {
    // Unspecified error, used when no defined error matches.
    KMmsGeneralError = MMS_ERROR_BASE,
    // no access points defined
    KMmsErrorNoWAPAccessPoint = MMS_ERROR_BASE - 1,
    // Both WAP access points must have the same URI
    // (both must point to the same MMSC)
    KMmsErrorUrisDontMatch = MMS_ERROR_BASE - 2,
    // no IAP for WAP AP 1
    KMmsErrorNoIAP1 = MMS_ERROR_BASE - 3,
    // no IAP for WAP AP 2
    KMmsErrorNoIAP2 = MMS_ERROR_BASE - 4,
    // access point 1 not valid (something wrong with access point chain)
    // missing URI has own error code, see below
    KMmsErrorAP1Invalid = MMS_ERROR_BASE - 5,
    // access point 2 not valid (something wrong with access point chain)
    // missing URI has own error code, see below
    KMmsErrorAP2Invalid = MMS_ERROR_BASE - 6,
    // message is too big to be sent - cannot allocate encode buffer
    KMmsErrorMessageTooBig = MMS_ERROR_BASE - 7,
    // message type invalid - cannot encode
    KMmsErrorUnknownMessageType = MMS_ERROR_BASE - 8,
    // Disk space critical level check failed
    KMmsErrorDiskSpaceLow = MMS_ERROR_BASE - 9,

    // error codes that come from the X-mms-response status
    KMmsErrorStatusUnspecified = MMS_ERROR_BASE - 10,
    KMmsErrorStatusServiceDenied = MMS_ERROR_BASE - 11,
    KMmsErrorStatusMessageFormatCorrupt = MMS_ERROR_BASE - 12,
    KMmsErrorStatusMessageAddressUnresolved = MMS_ERROR_BASE - 13,
    KMmsErrorStatusMessageNotFound = MMS_ERROR_BASE - 14,
    KMmsErrorStatusNetworkProblem = MMS_ERROR_BASE - 15,
    KMmsErrorStatusContentNotAccepted = MMS_ERROR_BASE - 16,
    KMmsErrorStatusUnsupportedMessage = MMS_ERROR_BASE - 17,
    
    // Mapping of HTTP error codes. Rough categories only
    KMmsErrorHTTPConfiguration = MMS_ERROR_BASE - 18, // 1XX, 3XX
    KMmsErrorHTTPNotFound = MMS_ERROR_BASE - 19, // 4XX
    KMmsErrorHTTPServerDown = MMS_ERROR_BASE - 20, // 5XX

    // Errors from the MMS protocol to WAP mapping layer
    KMmsErrorWapStack = MMS_ERROR_BASE - 21,
    KMmsErrorSessionAlreadyOpen = MMS_ERROR_BASE - 22,
    KMmsErrorSessionNotOpen = MMS_ERROR_BASE - 23,
    KMmsErrorBearerSuspended = MMS_ERROR_BASE - 24,
    KMmsErrorTimeout = MMS_ERROR_BASE - 25,
    KMmsErrorSuspendTimeout = MMS_ERROR_BASE - 26,
    KMmsErrorUnknownRespFromGw = MMS_ERROR_BASE - 27,
    KMmsErrorTransferCancelled = MMS_ERROR_BASE - 28,
    KMmsErrorBufferEmpty = MMS_ERROR_BASE - 29,

    // Could not connect because connection already exists
    KMmsErrorConnectionAlreadyActive = MMS_ERROR_BASE - 30,
    // Access point #1 not defined
    KMmsErrorNoWapAp1 = MMS_ERROR_BASE - 31,
    // URI 1 missing
    KMmsErrorNoURI1 = MMS_ERROR_BASE - 32,
    // URI 2 missing
    KMmsErrorNoURI2 = MMS_ERROR_BASE - 33,

    // we cannot prove we are in home network and mode is "automatic at home"
    KMmsErrorNotHomeNetwork = MMS_ERROR_BASE - 34,

    // error returned by validate service if values are
    // outside limits
    KMmsErrorInvalidSettings = MMS_ERROR_BASE - 35,

    // We must have our own definitiion for MRUExceeded.
    // The actual error code depends on the transport used.
    // The tranport component must map the error and 
    // return it to us in this form
    KMmsErrorEMRUExceeded = MMS_ERROR_BASE - 36

    };

#endif      // MMSERRORS_H   
            
// End of File
