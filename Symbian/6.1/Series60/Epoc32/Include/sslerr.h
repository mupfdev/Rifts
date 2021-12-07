//
// SSLERR.H
// 
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//



#ifndef __SSLERR_H__
#define __SSLERR_H__

#define SSL_ERROR_BASE -7400
#define SSL_ALERT_BASE 100

/**
 * @file SSLErr.h
 * Error code definitions for TLS.
 */

/**
 * No shared cipher was found.
 * The handshake failed because there was no available shared cipher supported by both the client and the server.
 */
const TInt KErrSSLNoSharedCipher		= SSL_ERROR_BASE - 1;

/**
 * The socket already has recived data pending on it.
 * This error is seen when StartClientHandshake is called when
 * there is already data waiting to be read from the socket. */
const TInt KErrSSLSocketBusy			= SSL_ERROR_BASE - 2;

/** One or more cipher suites passed as an argument was invalid. */
const TInt KErrSSLInvalidCipherSuite	= SSL_ERROR_BASE - 3;

/**
 * The certificate that was passed as an argument was invalid. 
 * (this could be that actual certificate is not a valid certificate, or if 
 * certman handles are passed, it wasn't found in certman) */
const TInt KErrSSLInvalidCert			= SSL_ERROR_BASE - 4;

/** No client certificate was supplied. */
const TInt KErrSSLNoClientCert			= SSL_ERROR_BASE - 5;

/** The size of the key is too big. */
const TInt KErrSSLUnsupportedKeySize	= SSL_ERROR_BASE - 6;

/** General unsupported key error */
const TInt KErrSSLUnsupportedKey		= SSL_ERROR_BASE - 7;

/** An invalid record was recieved */
const TInt KErrSSLBadRecordHeader		= SSL_ERROR_BASE - 8; 

/////////////////////////////////////////////////////
// Handshake related errors

const TInt KErrSSLBadProtocolVersion	= SSL_ERROR_BASE - 9;

/** The server only supports the SSL2.0 protocol. */
const TInt KErrSSL2ServerOnly			= SSL_ERROR_BASE - 10;

const TInt KErrSSLUnexpectedMessage		= SSL_ERROR_BASE - 11;

const TInt KErrSSLUnsupportedCipher		= SSL_ERROR_BASE - 12;

const TInt KErrSSLBadMAC				= SSL_ERROR_BASE - 13;

/** An SLL alert was received from the remote end, which caused the connection to be terminated. */
const TInt KErrSSLRecivedAlert			= SSL_ERROR_BASE - 14;

/** An invalid handshake message was recvieved. */
const TInt KErrSSLRecvNotSupportedHS	= SSL_ERROR_BASE - 15;

/** A field in the handshake record being parsed was too big. */
const TInt KErrSSLHSRecordFieldTooBig	= SSL_ERROR_BASE - 16;

const TInt KErrSSLRecordHeaderTooBig	= SSL_ERROR_BASE - 17;

const TInt KErrSSLSendDataToBig			= SSL_ERROR_BASE - 18;

const TInt KErrSSLNoCertificate			= SSL_ERROR_BASE - 19;

const TInt KErrSSLInvalidHash			= SSL_ERROR_BASE - 20;

const TInt KErrSSLSendCanceled			= SSL_ERROR_BASE - 21;

const TInt KErrSSLRecvCanceled			= SSL_ERROR_BASE - 22;

/** CancelHandshake was called during one of the handshake methods. */
const TInt KErrSSLHandshakeCanceled		= SSL_ERROR_BASE - 23;

const TInt KErrSSLWriteFailed			= SSL_ERROR_BASE - 24;

/** The SSL.dll couldn't be loaded by the adaptor. */
const TInt KErrSSLFailedToLoad			= SSL_ERROR_BASE - 25;

/** An unspecified error was signaled from the SSL.dll to the adaptor. */
const TInt KErrSSLDisconnectIndication	= SSL_ERROR_BASE - 26;

/** A leave occured in the SSL.dll. */
const TInt KErrSSLDllLeave				= SSL_ERROR_BASE - 27;

/////////////////////////////////////////////////////
// These error codes are equivalent to the standard TLS protocol Alert message 
// errors as defined in the TLS RFC. They include all those defined in SSL3.0
// The end number of each error is the same as per the RFC, so by using the
// SSL_ERROR_BASE and SSL_ALERT_BASE defines, errors codes can be constructed
// directly from the field within an alert message.
const TInt KErrSSLAlertCloseNotify				= SSL_ERROR_BASE - SSL_ALERT_BASE - 0;
const TInt KErrSSLAlertUnexpectedMessage		= SSL_ERROR_BASE - SSL_ALERT_BASE - 10;
const TInt KErrSSLAlertBadReordMac				= SSL_ERROR_BASE - SSL_ALERT_BASE - 20;
const TInt KErrSSLAlertDecryptionFailed			= SSL_ERROR_BASE - SSL_ALERT_BASE - 21;
const TInt KErrSSLAlertRecordOverflow			= SSL_ERROR_BASE - SSL_ALERT_BASE - 22;
const TInt KErrSSLAlertDecompressionFailure		= SSL_ERROR_BASE - SSL_ALERT_BASE - 30;
const TInt KErrSSLAlertHandshakeFailure			= SSL_ERROR_BASE - SSL_ALERT_BASE - 40;
const TInt KErrSSLAlertNoCertificate			= SSL_ERROR_BASE - SSL_ALERT_BASE - 41;
const TInt KErrSSLAlertBadCertificate			= SSL_ERROR_BASE - SSL_ALERT_BASE - 42;
const TInt KErrSSLAlertUnsupportedCertificate	= SSL_ERROR_BASE - SSL_ALERT_BASE - 43;
const TInt KErrSSLAlertCertificateRevoked		= SSL_ERROR_BASE - SSL_ALERT_BASE - 44;
const TInt KErrSSLAlertCertificateExpired		= SSL_ERROR_BASE - SSL_ALERT_BASE - 45;
const TInt KErrSSLAlertCertificateUnknown		= SSL_ERROR_BASE - SSL_ALERT_BASE - 46;
const TInt KErrSSLAlertIllegalParameter			= SSL_ERROR_BASE - SSL_ALERT_BASE - 47;
const TInt KErrSSLAlertUnknownCA				= SSL_ERROR_BASE - SSL_ALERT_BASE - 48;
const TInt KErrSSLAlertAccessDenied				= SSL_ERROR_BASE - SSL_ALERT_BASE - 49;
const TInt KErrSSLAlertDecodeError				= SSL_ERROR_BASE - SSL_ALERT_BASE - 50;
const TInt KErrSSLAlertDecryptError				= SSL_ERROR_BASE - SSL_ALERT_BASE - 51;
const TInt KErrSSLAlertExportRestriction		= SSL_ERROR_BASE - SSL_ALERT_BASE - 60;
const TInt KErrSSLAlertProtocolVersion			= SSL_ERROR_BASE - SSL_ALERT_BASE - 70;
const TInt KErrSSLAlertInsufficientSecurity		= SSL_ERROR_BASE - SSL_ALERT_BASE - 71;
const TInt KErrSSLAlertInternalError			= SSL_ERROR_BASE - SSL_ALERT_BASE - 80;
const TInt KErrSSLAlertUserCanceled				= SSL_ERROR_BASE - SSL_ALERT_BASE - 90;
const TInt KErrSSLAlertNoRenegotiation			= SSL_ERROR_BASE - SSL_ALERT_BASE - 100;


#endif // __SSLERR_H__
