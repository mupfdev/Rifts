//
// CHTTPResponse.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file provides the definition of the CHTTPResponse class.
//
// Comments: The HTTP Response class encodes HTTP response headers only. It
//           contains the methods used to transcode from WSP->HTTP fields
//

#if !defined(__CHTTPRESPONSE_H__)
#define __CHTTPRESPONSE_H__

// System includes
//
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__LOGDEF_H__)
#include <LogDef.h>
#endif
#if !defined(__HTTPSTD_H__)
#include <HttpStd.h>
#endif

// Local includes
//
#if !defined(__THTTPFIELDS_H__)
#include "THttpFields.h"
#endif

// Forward class declarations
//

class CPushMessage;
// Class definition for CHTTPResponse
//
class CHTTPResponse : public CBase
    {
public:	// Methods

	// Factory method to construct this class.
	//
	// Rtn: a new CHTTPResponse object, by ptr. Ownership is transferred to the
	//      caller.
	//
	IMPORT_C
	static CHTTPResponse* NewL();

	// Destructor for this class. Removes this object and releases memory held
	// by it
	//
    IMPORT_C
	virtual ~CHTTPResponse();

	// Clean out the fields buffer
	//
    IMPORT_C
	void Reset();

	// Set the fields buffer with the response received from the WAP Stack
	//
	// In:
	//  aResponse - an 8-bit descriptor field containing the origin server's
	//				WSP-encoded response header. Ownership is transferred to
	//				this class.
	//
    IMPORT_C
	void AddResponse(HBufC8* aResponse);

	// Accessor to the HTTP response fields buffer
	//
	// Rtn: a reference to the response. Ownership is _NOT_ transferred
	//
	// NOTE THIS SHOULD RETURN CONST - BUT CAN'T BE CHANGED SINCE IT WOULD
	// BREAK BC.
    IMPORT_C
	HBufC8& Response() const;

 	// Accessor to the HTTP status code (e.g. 400, 300, 200, 500)
	//
	// Rtn: the status code - series number only.
	//
    IMPORT_C
	THttpStatusCode StatusCode() const;

 	// Accessor to the HTTP detailed status code (e.g. 404, 304, 200, 501)
	//
	// Rtn: the status code - series and specific code value
	//
    IMPORT_C
	THttpStatusCode DetailedStatusCode() const;

	// Accessor to set the HTTP response status.
	//
	// In:
	//  aCode - the WSP-encoded status code
	//
    IMPORT_C
	void SetStatusCode(TInt aCode);

	// Method to find a named field, that returns null terminated 
	// WSP text strings.
	//
	// In:
	//  aField		- the field type
	//  aStartIndex	- the index to search from (defaults to the buffer start)
	//
	// Out:
	//  aDesc - a pointer-type descriptor into the response buffer at the
	//			position where the field was located. The caller must NOT
	//			modify the descriptor contents
	//
	// Rtn: TBool - set to ETrue if the field was found, EFalse otherwise
	//
    IMPORT_C
	TBool FindField(THttpHeaderField aField
                             , TPtrC8& aDesc
                             , TInt aStartIndex = 0) const;

	// Method to find a named field, that returns 8-bit octet data (binary
	// or strings - not stipulated which).
	//
	// In:
	//  aField		- the field type
	//  aStartIndex	- the index to search from (defaults to the buffer start)
	//
	// Out:
	//  aDesc - a pointer-type descriptor into the response buffer at the
	//			position where the field was located. The caller must NOT
	//			modify the descriptor contents
	//
	// Rtn: TBool - set to ETrue if the field was found, EFalse otherwise
	//
	IMPORT_C 
	TBool FindBinaryDescField(THttpHeaderField aField 
							, TPtrC8& aDesc
							, TInt aStartIndex = 0) const;

	// Method to find a named field, that returns an EPOC date/time structure.
	//
	// In:
	//  aField		- the field type
	//  aStartIndex	- the index to search from (defaults to the buffer start)
	//
	// Out:
	//  aTime - a structure containing the time (and date) found in the header
	//
	// Rtn: TBool - set to ETrue if the field was found, EFalse otherwise
	//
    IMPORT_C
	TBool FindField(THttpHeaderField aField
                             , TTime& aTime
                             , TInt aStartIndex = 0) const;

	// Method to find a named field within the Cache Control header
	//
	// In:
	//  aField		- the field type
	//
	// Out:
	//
	// Rtn: TBool - set to ETrue if the field was found, EFalse otherwise
	//
	IMPORT_C
	TInt FindCacheControlFieldValue(TCacheControlFieldValue aField) const;

	// Method to find a named field within the Cache Control header, 
	// that returns an EPOC date/time structure.
	//
	// In:
	//  aField		- the field type
	//
	// Out:
	//  aTime - a structure containing the time (and date) found in the header field
	//
	// Rtn: TBool - set to ETrue if the field was found, EFalse otherwise
	//
    IMPORT_C
	TBool ExtractCacheControlTime(TCacheControlFieldValue aField, TTime& aTime) const;

	// Method to search for the content type encoded in the response header
	//
	// Out:
	//  aDesc - a pointer-type descriptor into the appropriate element of an
	//			array prefilled with all the content types that have WSP
	//			encodings. e.g. "text/vnd.wap.wml".  The contents of the
	//			descriptor must NOT be modified.
	//
    IMPORT_C
	void ContentType(TPtrC& aDesc) const;

	// Method to search for the realm encoded in the response header, when the
	// response challenges the client for HTTP authentication (code 401)
	//
	// Out:
	//  aDesc - a pointer-type descriptor into the response header buffer
	//			positioned at the realm string within the challenge. The
	//			contents of the descriptor must NOT be modified.
	//
	// Rtn: TBool - set to ETrue if a www-authenticate realm was found, EFalse
	//				otherwise
	//
	IMPORT_C
	TBool FindRealm(TPtrC8& aRealm) const;

	// Method to search for the character set encoded in the Content-Type
	// field ofthe response header
	//
	// Out:
	//  aDesc - a pointer-type descriptor into the appropriate element of an
	//			array prefilled with all the character sets that have WSP
	//			encodings. e.g. "utf-8".  The contents of the descriptor must
	//			NOT be modified.
	//
	// Rtn: TBool - set to ETrue if a character set was found, EFalse if not
	//
    IMPORT_C
	TBool CharSet(TPtrC8& aDesc) const;

protected: // Methods

	// Normal constructor - do non-allocating creation of this class
	//
    IMPORT_C
    CHTTPResponse();

	// Second phase construction - any allocation for this class must take place
	// here. Sets up the resources required by an HTTP Response.
	//
    IMPORT_C
	void ConstructL();

	//friend class declaration - only need the following function
	friend class CPushMessage;
	// Method to locate a named field in the response header, starting at the
	// specified index position.
	//
	// In:
	//  aField		- the header field type
	//  aStartIndex - the (optional) position in the header to start searching
	//
	// Rtn: TInt - the index position of the required field _value_ (not the
	//             field name), or KErrNotFound otherwise.
	//
    IMPORT_C
	TInt LocateField(THttpHeaderField aField, TInt aStartIndex = 0) const; 

	// Perform a look-up of content type given a WSP encoding value, used as
	// an index.
	//
	// In:
	//  aIndex - the WSP encoding value
	//
	// Rtn: const TText* - the required content type text - NOT to be changed
	//
    IMPORT_C
	const TText* ContentType(TInt aContentTypeCode) const;

 	// Perform a look-up of character set given a WSP encoding value, used as
	// an index.
	//
	// In:
	//  aCharsetCode - the index into the content types table/
	//
	// Rtn: const TText8* - the required 8-bit character set text - NOT to be
	//						changed by the caller
	//
    IMPORT_C
	const TText8* CharSet(TInt aCharsetCode) const;

private: // Attributes

	// The 8-bit buffer used to store the HTTP response fields
	//
    HBufC8* iResponse;

	// The HTTP Status code (coarse - ie. series only, e.g. 100, 200 etc.)
	//
    THttpStatusCode iStatusCode;

	// The detailed HTTP Status code (within series, e.g. 102, 204, 401 etc.)
	//
    THttpStatusCode iDetailedStatusCode;

	// Declare the CLogClient pointer
   	__DECLARE_LOG;

private: // Type definitions

	// The UIntVar type is defined in the WSP specs as a binary value upto
	// five octets in length. It is used as a variable-length encoding for
	// integer values
	//
	typedef TBuf8<5> TUIntVar;

private: // Methods

	// Do a conversion from 40-bit UIntVar encoding into 32-bit integer
	//
	// In:
	//  aUIntVar	- the 40-bit source UIntVar
	//
	// Out:
	//  aInt		- the 32-bit resulting integer
	//	aUivLength  - the number of bytes consumed by the UIntVar (1-5)
	//
	void UIntVarToInt(TUIntVar aUIntVar, TInt& aInt, TInt& aUivLength) const;

	// Extract a WSP encoded MultiOctet Integer encoding into 32-bit integer
	//
	// In:
	//  aSource	- the source Multi-Octet integer
	//
	// Out:
	//  aInt		- the 32-bit resulting integer
	//
	void ExtractMultiOctetInteger(TInt& aInt, const TPtrC8& aSource) const;

	// Method to find a named field within the Cache Control header
	//
	// In:
	//  aSource		- the descriptor containing the date value
	//	aFrom		- The position in the descriptor to start from
	//
	// Out:
	//  aTime - a structure containing the time (and date) found in the descriptor
	//
	// NOTE THIS METHOD WAS EXPORTED FOR TESTING OF THE CACHE. IT SHOULDN'T BE
	// NOW, BUT CAN'T BE CHANGED SINCE IT WOULD AFFECT BC.
	IMPORT_C
	void ExtractFieldDateValue(const TPtrC8& aSource, TInt aFrom, TTime& aTime) const;

	// Method to find a named field within the Cache Control header
	//
	// In:
	//  aField		- the field type
	//
	// Out:
	//	the found aCacheControl string
	//
	// Rtn: TInt - set to KErrNotFound if the field was not found,
	//		otherwise the position in the cache control descriptor that the field was found
	//
	TInt FindCacheControlFieldValue(TCacheControlFieldValue aField,TPtrC8& aCacheControl) const;

    void Panic(THttpPanicCode aPanicCode) const;

	// Spare methods for future BC. Const- and non-const versions to assist
	// the caller in preserving const-ness. IMPORT_C ensures they reserve a
	// slot in the vtbl, which is essential to preseve future BC.
	//
	IMPORT_C
	virtual TAny* Extend_CHTTPResponse(TAny* aArgs);
	IMPORT_C
	virtual TAny* Extend_CHTTPResponse_const(TAny* aArgs) const;

#if defined _DEBUG
	// Debug method definition to allow class invariant testing
	// Called by the standard macro __TEST_INVARIANT
	//
	void __DbgTestInvariant() const;

	void DumpToLog(const TDesC8& aData) const;
#endif

};

#endif // __CHTTPRESPONSE_H__

