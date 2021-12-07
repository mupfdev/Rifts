// urlbase.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Purpose:		Definition of CUrl class - Url processor based on RFC2396.
//
// Comments:	CUrl encapsulates a url and provides access to its components. On creation, the contents of 
//				the url is in unescaped mode - excluded characters (as defined by RFC2396) have not been coded into their 
//				escape triples. Two NewL() functions are provided. The first takes any descriptor and encapsulates it into
//				the CUrl object, and leaves if the the url begins with a ':' (EWapErrCorruptUrl) or if the scheme is 
//				corrupted (EWapErrCorruptScheme). The second NewL() creates a url with a file scheme (file:///) from a 
//				TParseBase argument, and will leave if the url is invalid (EWapErrCorruptUrl). Two static functions have 
//				been provided that each take a descriptor argument which is then escape encoded/decoded.
//
//				NOTE - maintainer needs detailed knowledge of url parsing (RFC2396)
//

#if !defined(__URLBASE_H__)
#define __URLBASE_H__

// System includes
//
#include <e32base.h>
#include <f32file.h>
#include <wapengstd.h>


// Definition of CUrl
//
class CUrl : public CBase
	{
public:	// Type definitions

	//	Enum of component parts of the Url.
	//
	enum TComponent
		{	
		EUrlScheme = 0x01,
		EUrlLocation = 0x02,
		EUrlPath = 0x04,
		EUrlQuery = 0x08,
		EUrlFragment = 0x10,
		EUrlFileName = 0x20, // the end of the path
		EUrlUsername = 0x40,
		EUrlPassword = 0x80,
		EUrlAuthority = EUrlLocation | EUrlUsername | EUrlPassword,
		EUrlNoCredentials = EUrlScheme | EUrlLocation | EUrlPath | EUrlQuery |
			EUrlFragment,
		EUrlGenericCompare = EUrlScheme | EUrlAuthority | EUrlPath | EUrlQuery
		};

public:	// Methods

	// Static factory c'tor. Creates a CUrl object from a
	// descriptor. This can hold any kind of Url - local file or http,
	// full url with scheme, or a relative url. Leaves if scheme is
	// corrupted or url is invalid.
	//
	// In:
	// aUrl	- descriptor of URL
	//
	// Rtn: pointer to created CUrl object
	//
	IMPORT_C static CUrl* NewL(const TDesC& aUrl);

	// Static factory c'tor. Creates a CUrl objects from a TParseBase
	// that refers to a file in the local file system.  This function
	// will prefix path with file scheme - file:///. Leaves if url is
	// invalid.
	//
	// In:
	// aFileName	- path for a resource in local file system
	//
	// Rtn: pointer to created CUrl object
	//
	IMPORT_C static CUrl* NewL(const TParseBase& aFileName);

	// Resolves aRelativeUrl against aBaseUrl based on relative
	// parsing algorithm in RFC2396. Resolved url is returned Note -
	// if aBaseUrl is empty, the relative url aRelativeUrl is
	// returned.
	//
	// In:
	// aBaseUrl		- base url to resolve against
	// aRelativeUrl	- relative url
	//
	// Rtn: resolved url - owner is transfered to caller
	//
	IMPORT_C static CUrl* ResolveL(CUrl& aBaseUrl, CUrl& aRelativeUrl);

	// Sets current url to aUrl. If leave occurs, this object is unchanged.
	//
	// In:
	// aUrl	- the new url
	//
	IMPORT_C void SetL(CUrl& aUrl);

	// Returns a copy of itself.
	//
	// Rtn: copy of itself - ownership transfered to caller.
	//
	IMPORT_C CUrl* AllocL() const;

	// Returns a copy of one of its components.Currently any defined value of component
	// is supported, but the result may well not be a valid URL.
	//
	// In:
	// aComponent	- the desired component of the url
	//
	// Rtn: copy of the desired url component - ownership is transfered to caller.
	//
	IMPORT_C CUrl* AllocL(TComponent aComponent) const;

	// Returns a TPtrC to the specified component part of tbe Url.
	//
	// In:
	// aType	- the desired component of the url.
	//
	// Rtn: pointer to the component in the url
	//
	IMPORT_C virtual const TPtrC Component(TComponent aType) const;

	// Sets the specified component to the specified value. This function is not completely 
	// implemented - currently it will work in the following circumstances;
	// 1 - the desired component already exists in the URL 
	// 2 - it's the username or password and the location exists. 
	// In other cases the function will leave with KErrNotSupported.
	// 
	// In:
	// aComponent	- the component to be set.
	// aValue		- the new value. NB must already be escaped.
	//
	IMPORT_C void SetComponentL(TComponent aComponent, const TDesC& aValue);

	// Overloaded equality operator.
	//
	// In:
	// aUrl	- the Url to be compared against.
	//
	// Rtn: ETrue is returned if aUrl is the same as this url.
	//
	IMPORT_C TBool operator==(CUrl& aUrl) const;	

	// Compares the specified component part of two urls. 
	//
	// In:
	// aUrl				- the url to be compared against.
	// aCompareComps	- the component of the urls to be compared. Defaults to components defined by EUrlGenericCompare.
	//
	// Rtn: zero is returned for an exact match.
	//
	IMPORT_C TInt Compare(CUrl& aUrl, TInt aCompareComps = EUrlGenericCompare) const;

	// Returns TDesC to descriptor of entire url.
	//
	// Rtn: the descriptor to the url.
	//
	inline const TDesC& UrlDes() const;

	// THIS SHOULD NOT BE USED AS CAUSES PANIC - WILL BE REMOVED.
	//
	IMPORT_C CUrl* UrlEscapedL() const;

	// THIS SHOULD NOT BE USED AS CAUSES - WILL BE REMOVED.
	//
	IMPORT_C CUrl* UrlUnescapedL() const;

	// D'tor
	//
	IMPORT_C ~CUrl();

	// Encodes any excluded characters in input string as escape triples. Uses the overloaded
	// function.
	//
	// THIS SHOULD NOT BE USED - WILL BE REMOVED. USE NEW OVERLOAD FUNCTION.
	//
	// In:
	// aString	- descriptor with string to be encoded.
	//
	// Rtn: version of string with excluded characters converted to
	// escape triples - ownership transfered to caller.
	//
	IMPORT_C static HBufC* EscapeEncodeL(const TDesC& aString);

	// Encodes any excluded characters in input string as escape triples. The excluded characters
	// are set by the value or aEscapeMode. Control characters, space (ASCII 0x20) and characters
	// above 127 are always encoded as escape triples.
	//
	// In:
	// aString		- descriptor with string to be encoded.
	// aEscapeMode	- governs which chars are to excluded (and escaped)
	//
	// Rtn: version of string with excluded characters converted to
	// escape triples - ownership transfered to caller.
	//
	IMPORT_C static HBufC* EscapeEncodeL(const TDesC& aString, TInt aEscapeMode);

	// Decodes any escape triples in input string into original
	// excluded characters.
	//
	// In:
	// aString	- descriptor with string to be decoded.
	//
	// Rtn: version of string with escape triples converted back to
	// excluded characters - ownership transfered to caller.
	//
	IMPORT_C static HBufC* EscapeDecodeL(const TDesC& aString);

	// Convert a Unicode string into UTF8 format.
	// 
	// In:
	// aString	- the input Unicode string.
	//
	// Rtn: the converted string (UTF8 format) - ownership transfered to caller.
	//
	IMPORT_C static HBufC8* ConvertFromUnicodeToUtf8L(const TDesC& aString);

	// Convert a UTF8 string into Unicode format.
	// 
	// In:
	// aString	- the input UTF8 string.
	//
	// Rtn: the converted string (Unicode format) - ownership transfered to caller.
	//
	IMPORT_C static HBufC* ConvertToUnicodeFromUtf8L(const TDesC8& aString);

private:	// Type definitions

	// Helper class used to resolve a relative path against a base path.
	//
	class TRelativePaths;

	// Enumeration of panic codes for this class
	//
	enum TPanicCode
	{
	EInvalidUrl
	};

private:	// Methods

	// Normal c'tor - non-allocating creation of this class
	//
	CUrl();

	// Second-phase c'tor for general url - any allocation takes place here.
	//
	// In:
	// aUrl	- descriptor containing url.
	//
	void ConstructL(const TDesC& aUrl);

	// Second-phase c'tor for url with file scheme - any allocation
	// takes place here.
	//
	// In:
	// aFileName	- path to local file system resource.
	//
	void ConstructL(const TParseBase& aFileName);

	// Panic handler for ths class - kills the process in the event of
	// a panic
	//
	// In:
	// aPanicCode	- code enumerating the panic that has occured.
	//
	void Panic(TPanicCode aPanicCode) const;

	// Checks the scheme if present to ensure it is valid
	// Leaves with EWapErrCorruptScheme if not valid
	//
	// In:
	// aScheme - the scheme to be checked
	//
	void CheckSchemeValidL(const TDesC& aScheme) const;

	// Parses a url to find the start and end of a specified component
	// in the url.
	//
	// In:
	// aComponent	- the component sought.
	// aUrl			- descriptor of url to be parsed
	//
	// Out:
	// aStartPos - index of start of component; is KCUrlInvalidCharPos
	// if component not found.
	// aEndPos - index of end of component; is KCUrlInvalidCharPos if
	// component not found.
	//
	void Part(TComponent aComponent, const TDesC& aUrl, TInt& aStartPos, 
			  TInt& aEndPos) const;

	// Parses an identified authority to extract the location,
	// username or password.
	//
	// In:
	// aComponent - the component sought. (EUrlLocation, EUrlUsername
	// 										or EUrlPassword)
	// aUrl			- descriptor of url to be parsed
	//
	// In/Out:
	// aStartPos - index of start of component; is KCUrlInvalidCharPos
	// if component not found. Is the start of the authority on inupt.
	// aEndPos - index of end of component; is KCUrlInvalidCharPos if
	// component not found. End of authority on input.
	void PartOfAuthority(TComponent aComponent, const TDesC& aUrl, 
						 TInt& aStartPos, TInt& aEndPos) const;

private:	// Attributes

	// Pointer to buffer containing url. Owned by this class
	//
	HBufC*	iUrlDes;
	};

inline const TDesC& CUrl::UrlDes() const
//
//	Return descriptor to url
	{
	return *iUrlDes;
	}

class CUrl::TRelativePaths
//
//	Helper class used to resolve a relative path against a base path
	{
public:	// Methods

	// Normal c'tor
	//
	// In:
	// aBasePath		- base path to resolve against
	// aRelativePath	- relative path
	// aResolvedPath	- result of resolving relative path against base path
	//
	TRelativePaths(TPtrC aBasePath, TPtrC aRelativePath, TPtr aResolvedPath);

	// Does the path resolution
	//
	void ResolveRelativePaths();

	// Cleans resolved path, removing structures such as '/../'
	//
	void CleanResolvedPath();

public:	//	Attributes

	// Descriptor for base path
	//
	TPtrC iBasePath;

	// Descriptor for relative path
	//  
	TPtrC iRelativePath;

	// Modifiable descriptor to resolved path
	//
	TPtr iResolvedPath;
	};

#endif // __URLBASE_H__
