//
// CHTTPHeader.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file provides the definition of the CHTTPHeader class.
//
// Comments: The HTTP Header class encodes HTTP request headers only. It
//           contains the methods used to transcode from HTTP->WSP fields.
//			 The header contains a buffer that will grow as needed when new
//			 header fields are added.
//
//			 - Note that not all the HTTP/1.1 headers are implemented here. A
//			   placeholder for each header is included for completeness and as a
//			   reminder.
//

#if !defined(__CHTTPHEADER_H__)
#define __CHTTPHEADER_H__

// System includes
//
#if !defined(__HTTPSTD_H__)
#include "HttpStd.h"
#endif

// Local includes
//
#if !defined(__THTTPFIELDS_H__)
#include "THTTPFields.h"
#endif

// Wap Logging
//
#if !defined(__WAPLOG_H__)
#include "WapLog.h"
#endif
#if !defined(__LOGDEF_H__)
#include "LogDef.h"
#endif


// Class definition for CHTTPHeader
//
class CHTTPHeader : public CBase
    {
public:	// Methods

	// Static factory method to create CHTTPHeader objects.
	//
	// Rtn: the new CHTTPHeader object. Ownership passed to the caller.
	//
    IMPORT_C
	static CHTTPHeader* NewL();

	// Destructor for this class. Removes this object and releases memory held
	// by it
	//
    IMPORT_C
	virtual ~CHTTPHeader();

	// Clean out the fields buffer. Reset it to a default single chunk in size.
	//
    IMPORT_C
	void ResetL();

	// Accessor to return the fields buffer
	//
	// Rtn: the buffer contents
	//
	// NOTE THAT SINCE THIS IS AN ACCESSOR IT SHOULD BE A CONST FUNCTION. THIS
	// CAN'T BE CHANGED THOUGH, SINCE IT WOULD BREAK BC.
    IMPORT_C
	const TDesC8& Header();

public: // Methods to set each HTTP field - Note that not all are implemented
		// Each can return the error code KErrNoMemory if the field cannot be
		// set, or KErrNone if the operation was successful.

	// Set the accept string - describes the content types the browser is
	// prepared to accept in this request (see THttpFields.h)
	//
	// In:
	//  aAccept - a list of comma-separated content types. 'q' values not yet
	//            supported
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetAccept(const TDesC8& aAccept);

	// Set the character set that the browser wishes the content to be encoded
	// with in the response to this request
	//
	// In:
	//  aAcceptCharset - the name of the desired character set (see
	//					 THttpFields.h)
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetAcceptCharset(const TDesC8& aAcceptCharset);

/*    IMPORT_C TInt SetAcceptEncoding(const TDesC8& aAcceptEncoding); Not implemented */

	// Set the language that the browser wishes the content to be returned in,
	// in the response to this request
	//
	// In:
	//  aAcceptLanguage - the name of the desired language (see THttpFields.h)
	//					  'q' values not yet supported.
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetAcceptLanguage(const TDesC8& aAcceptLanguage);

/*    IMPORT_C TInt SetAcceptRanges(const TDesC8& aAcceptRanges); Not implemented */
/*    IMPORT_C TInt SetAge(const TDesC8& aAge); Not implemented */
/*    IMPORT_C TInt SetAllow(const TDesC8& aAllow); Not implemented */

    IMPORT_C
	TInt SetAuthorization(const TDesC8& aAuthorization);
/*    IMPORT_C TInt SetCacheControl(const TDesC8& aCacheControl); Not implemented */
/*    IMPORT_C TInt SetConnection(const TDesC8& aConnection); Not implemented */
/*    IMPORT_C TInt SetContentBase(const TDesC8& aContentBase); Not implemented */
/*    IMPORT_C TInt SetContentEncoding(const TDesC8& aContentEncoding); Not implemented */
/*    IMPORT_C TInt SetContentLanguage(const TDesC8& aContentLanguage); Not implemented */
/*    IMPORT_C TInt SetContentLength(const TDesC8& aContentLength); Not implemented */
/*    IMPORT_C TInt SetContentLocation(const TDesC8& aContentLocation); Not implemented */
/*    IMPORT_C TInt SetContentMD5(const TDesC8& aContentMD5); Not implemented */
/*    IMPORT_C TInt SetContentRange(const TDesC8& aContentRange); Not implemented */

	// Set the Content Type/Charset header used for POST operations.  Note that the WSP Specs
	// mandate that HTTP POST uses application/x-www-form-urlencoded, so this is implied rather
	// than being a argument here.  However the caller can specify the CharSet parameter that
	// is used in the header.  Content-Type headers are not transmitted for GET operations at
	// all.
	//
	// In:
	//  aCharSet - the name of the desired language (see THttpFields.h)
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetPostContentTypeAndChSet(const TDesC8& aCharSet);

/*    IMPORT_C TInt SetDate(const TDesC8& aDate); Not implemented */

	// Set the 'etag' value used for cache control
	//
	// In:
	//  aEtag - the etag value
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetEtag(const TDesC8& aEtag);

/*    IMPORT_C TInt SetExpires(const TDesC8& aExpires); Not implemented */
/*    IMPORT_C TInt SetFrom(const TDesC8& aFrom); Not implemented */
/*    IMPORT_C TInt SetHost(const TDesC8& aHost); Not implemented */


    // Set the 'if-modified-since' value used for cache control
	//
	// In:
	//  aIfModifiedSince - the 'if-modified-since' value
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetIfModifiedSince(const TTime& aIfModifiedSince);

/*    IMPORT_C TInt SetIfMatch(const TDesC8& aIfMatch); Not implemented */

    // Set the 'if-none-match' value used for cache control
	//
	// In:
	//  aIfNoneMatch - the 'if-none-match' value
	//
	// Rtn: error code - KErrNone if successful
	//
	IMPORT_C
	TInt SetIfNoneMatch(const TDesC8& aIfNoneMatch);

/*    IMPORT_C TInt SetIfRange(const TDesC8& aIfRange); Not implemented */

    // Set the 'if-unmodified-since' value used for cache control
	//
	// In:
	//  aIfUnmodifiedSince - the 'if-unmodified-since' value
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetIfUnmodifiedSince(const TTime& aIfUnmodifiedSince);

/*    IMPORT_C TInt SetLocation(const TDesC8& aLocation); Not implemented */
/*    IMPORT_C TInt SetLastModified(const TDesC8& aLastModified); Not implemented */
/*    IMPORT_C TInt SetMaxForwards(const TDesC8& aMaxForwards); Not implemented */
/*    IMPORT_C TInt SetPragma(const TDesC8& aPragma); Not implemented */
/*    IMPORT_C TInt SetProxyAuthenticate(const TDesC8& aProxyAuthenticate); Not implemented */
/*    IMPORT_C TInt SetProxyAuthorization(const TDesC8& aProxyAuthorization); Not implemented */
/*    IMPORT_C TInt SetPublic(const TDesC8& aPublic); Not implemented */
/*    IMPORT_C TInt SetRange(const TDesC8& aRange); Not implemented */

    // Set the referer URL used to describe where the browser is navigating
	// from when fetching a new resource
	//
	// In:
	//  aReferer - the URL
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetReferer(const TDesC8& aReferer);

/*    IMPORT_C TInt SetRetryAfter(const TDesC8& aRetryAfter); Not implemented */
/*    IMPORT_C TInt SetServer(const TDesC8& aServer); Not implemented */
/*    IMPORT_C TInt SetTransferEncoding(const TDesC8& aTransferEncoding); Not implemented */
/*    IMPORT_C TInt SetUpgrade(const TDesC8& aUpgrade); Not implemented */

    // Set the User Agent name for this browser - required by origin servers
	// for logging purposes
	//
	// In:
	//  aUserAgent - the UA name
	//
	// Rtn: error code - KErrNone if successful
	//
    IMPORT_C
	TInt SetUserAgent(const TDesC8& aUserAgent);

/*    IMPORT_C TInt SetVary(const TDesC8& aVary); Not implemented */
/*    IMPORT_C TInt SetVia(const TDesC8& aVia); Not implemented */
/*    IMPORT_C TInt SetWarning(const TDesC8& aWarning); Not implemented */
/*    IMPORT_C TInt SetWWWAuthenticate(const TDesC8& aWWWAuthenticate); Not implemented */

protected: // Methods for header field manipulation

	// Default Constructor. Creates the header with a single chunk buffer.
	//
    IMPORT_C
	CHTTPHeader();

	// Second phase construction - creates the initial buffer, one chunk in size
	//
    IMPORT_C
	void ConstructL();

protected: // Attributes
    HBufC8* iBuffer;

private: // Type definitions

	// The UIntVar type is defined in the WSP specs as a binary value upto
	// five octets in length. It is used as a variable-length encoding for
	// integer values
	//
	typedef TBuf8<5> TUIntVar;

private: // Methods

	// Helper method for the SetAcceptCharSet method.
	//
	// In:
	//  aAcceptCharset - the name of the desired character set
	//
	void DoSetAcceptCharsetL(const TDesC8& aAcceptCharset);

	// Helper method for the DoSetAcceptCharSet method.  Performs a look-up of
	// the specified character set from the table of well-known charsets
	//
	// In:
	//  aCharset - the name of the desired character set
	//
	// Rtn: the character set ID (index in the charset table) or KErrNotFound if
	//		the charset is not one of the well-known set.
	//
	TInt LookUpWellKnownCharset(const TDesC8& aCharset);

	// Encodes one accept element
	//
	// In:
	//  aAccept - the acceptable content type
	//
	void EncodeAcceptElementL(const TDesC8& aAccept);

	void EncodeLanguageElementL(const TDesC8& aLanguage);

	// Splits a string of headers separated by spaces or commas into
	// its component parts and then calls aOperator on each
	// component. This function will only leave if aOperator does.
	void ParseCSVStringL(const TDesC8& aString, 
						 void (CHTTPHeader::* aOperator)(const TDesC8&));

	// These methods are in pairs - the Add...Field method writes a complete
	// field of a particular type into the header, with the correct field name
	// and an appropriate encoding of field value.
	// The Add...FieldValue method writes the encoded field value only.
	// Both methods return an integer for the number of new data bytes written
	// into the header buffer.
	// All can leave with KErrNoMemory, should the buffer need extending and
	// allocation fails.

	// Append a (binary) data header to the buffer, of the specified field type
	//
	// In:	aField - the header field enumeration for the data field being
	//				 added
	//		aDes   - the data to be added
	//
	// Rtn:	the number of new bytes appended to the header
	//
    TInt AddDataFieldL(THttpHeaderField aField, const TDesC8& aDes);
    TInt AddDataFieldValueL(const TDesC8& aDes);

    // Append a string header to the buffer, of the specified field type.
	//
	// In:	aField - the header field enumeration for the string field being
	//				 added
	//		aDes   - the string to be added
	//
	// Rtn:	the number of new bytes appended to the header
	//
	TInt AddStringFieldL(THttpHeaderField aField, const TDesC8& aDes);
    TInt AddStringFieldValueL(const TDesC8& aDes);

    // Append an integer header to the buffer, of the specified field type.
	//
	// In:	aField - the header field enumeration for the integer field being
	//				 added
	//		aInt   - the integer to be added
	//
	// Rtn:	the number of new bytes appended to the header
	//
    TInt AddIntegerFieldL(THttpHeaderField aField, TInt aInt);
    TInt AddIntegerFieldValueL(TInt aInt);

    // Append an integer header to the buffer, of the specified field type, and
	// with a parameter of the specified type and value.
	//
	// In:	aField		- the header field enumeration for the integer field being
	//					   added
	//		aInt		- the integer to be added
	//		aParam		- the encoding of the parameter to be added
	//		aParamVal	- the value of the parameter (as a string/data descriptor)
	//
	// Rtn:	the number of new bytes appended to the header
	//
    TInt AddIntegerFieldWithParamL(THttpHeaderField aField, TInt aInt,
								   TInt aParam, const TDesC8& aParamVal);
    TInt AddIntegerFieldWithParamValueL(TInt aInt, TInt aParam,
										const TDesC8& aParamVal);

	// Helper method for the DoSetAcceptCharSet method.  Adds the WSP encoding
	// for a well-known charset
	//
	// In:
	//	aField - the field type to be written/param type if a charset parameter
	//	aCharSetId - the index of the charset in the well-known charset table
	//
	// Rtn:	TInt - the number of new bytes written into the header buffer
	//
	TInt AddWellKnownCharsetFieldL(THttpHeaderField aField, TInt aCharSetId);
	TInt AddWellKnownCharsetFieldValueL(TInt aCharSetId);

    // Append a UIntVar header to the buffer, of the specified field type.
	//
	// In:	aField - the header field enumeration for the UIntVar field being
	//				 added
	//		aDes   - the integer to be encoded to a UIntVar in the header
	//
	// Rtn:	the number of new bytes appended to the header
	//
    TInt AddUIntVarFieldL(THttpHeaderField aField, TInt aInt);
    TInt AddUIntVarFieldValueL(TInt aInt);

    // Append a timestamp header to the buffer, of the specified field type.
	//
	// In:	aField - the header field enumeration for the date field being
	//				 added
	//		aDes   - the date to be added
	//
	// Rtn:	the number of new bytes appended to the header
	//
    TInt AddTimeDateFieldL(THttpHeaderField aField, TTime aTime);
    TInt AddTimeDateFieldValueL(TTime aTime);

	// Append a single character to the buffer; growing it if necessary. Leaves
	// with KErrNoMemory if allocation fails.
	//
	// In:
	//	aChar	- the character to append.
	//
	void AppendCharL(TChar aChar);

	// Append a sequence of octets to the buffer; growing it if necessary.
	// Leaves with KErrNoMemory if allocation fails.
	//
	// In:
	//	aDesc	- the descriptor to append.
	//
	void AppendDataL(const TDesC8& aDesc);

	// Do a conversion from 32-bit integer into 40-bit UIntVar encoding -
	// implements algorithm described in [WSP] sect. 8.1.2
	//
	// In:
	//  aInt		- the 32-bit source integer
	//
	// Out:
	//  aUIntVar	- the 40-bit resulting UIntVar
	//	aNumUIntVarBytes - the number of bytes in the resulting UIntVar (1-5)
	//
	void IntToUIntVar(TInt aInt, TUIntVar& aUIntVar, TInt& aNumUIntVarBytes);

	// Panic method
	//
	// In:
	//  aPanicCode - a standard HTTP panic code (see <HttpStd.h>)
	//
    void Panic(THttpPanicCode aPanicCode) const;

	// Spare methods for future BC. Const- and non-const versions to assist
	// the caller in preserving const-ness. IMPORT_C ensures they reserve a
	// slot in the vtbl, which is essential to preseve future BC.
	//
	IMPORT_C
	virtual TAny* Extend_CHTTPHeader(TAny* aArgs);
	IMPORT_C
	virtual TAny* Extend_CHTTPHeader_const(TAny* aArgs) const;

#if defined _DEBUG
	// Debug method definition to allow class invariant testing
	// Called by the standard macro __TEST_INVARIANT
	//
	void __DbgTestInvariant() const;

	// Debug method to dump to log the header's binary content
	void DumpToLog(HBufC8& aData) const;
#endif

private: // Attributes

	// Declare the CLogClient pointer
   	__DECLARE_LOG;

	// Number of fields in this header
	//
	TInt iNumHeaderFields;

	// Reserved for future expansion
	//
	TAny* iExpansionData;
};

#endif // __CHTTPHEADER_H__

