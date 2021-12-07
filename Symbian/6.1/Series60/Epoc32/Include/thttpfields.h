//
// THttpFields.h
// Copyright © 1998-2000 Symbian Ltd.  All rights reserved. 
//

//
// Purpose:  This file contains definitions of types THttpStatusCode,
//			 THttpParameter, THttpHeaderField, KHttpContentTypes,
//			 KHttpCharacterSetNames and KHttpCharacterSetCodes
//
// Comments: This header is a direct transcoding of [WSP] Appendix A - Assigned
//			 Numbers, which contains the following assignment tables:
//
//			 Table 34 : PDU Type Assignments
//				   35 : Abort Reason Code Assignments
//				   36 : Status Code Assignments
//				   37 : Capability Assignments
//				   38 : Well-Known Parameter Assignments
//				   39 : Header Field Name Assignments
//				   40 : Content-Type Assignments
//				   41 : ISO-639 Language Assignments
//				   42 : Character Set Assignments
//

#if !defined(__THTTPFIELDS_H__)
#define __THTTPFIELDS_H__

//
// Table 34 not implemented
//


//
// Table 35 not implemented
//


//
// HTTP/1.1 Status Codes: WSP Code Assignments
//
// (see [WSP] Appdx A Table 36)
// Codes from RFC-2616 added where necessary for HTTP Caching
//
enum THttpStatusCode
    {
    EHttpUnknown = 0, 
    EHttpContinue = 100, 
    EHttpSwitchingProtocols, 
	EHttpWarnStaleContent = 110, 		// From RFC-2616
	EHttpWarnRevalidationFailed, 		//		"
	EHttpWarnDisconnectedOperation, 	//		"
	EHttpWarnHeuristicExpiration, 		//		"
	EHttpWarnMiscellaneous, 			//		"
    EHttpOK = 200, 
    EHttpCreated, 
    EHttpAccepted, 
    EHttpNonAuthorativeInformation, 
    EHttpNoContent, 
    EHttpResetContent, 
    EHttpPartialContent, 
	EHttpWarnTransformationApplied, 	// From RFC-2616
	EHttpWarnPersistentMiscellanous, 	//		"
    EHttpMultipleChoices = 300, 
    EHttpMovedPermanently, 
    EHttpMovedTemporarily, 	
    EHttpSeeOther, 
    EHttpNotModified, 
    EHttpUseProxy,
	EHttpTemporaryRedirect = 307, 		// From RFC-2616
    EHttpBadRequest = 400, 
    EHttpUnauthorized, 
    EHttpPaymentRequired, 
    EHttpForbidden, 
    EHttpNotFound, 
    EHttpMethodNotAllowed, 
    EHttpNotAcceptable, 
    EHttpProxyAuthenticationRequired, 
    EHttpRequestTimeout, 
    EHttpConflict, 
    EHttpGone, 
    EHttpLengthRequired, 
    EHttpPreconditionFailed, 
    EHttpRequestEntityTooLarge, 
    EHttpRequestURITooLong, 
    EHttpUnsupportedMediaType, 
	EHttpRequestRangeNotSatisfiable, 	// From RFC-2616
	EHttpExpectationFailed, 			// From RFC-2616
    EHttpInternalServerError = 500, 
    EHttpNotImplemented, 
    EHttpBadGateway, 
    EHttpServiceUnavailable, 
    EHttpGatewayTimeout, 
    EHttpHTTPVersionNotSupported
	// All other codes are extension codes
    };


//
// Table 37 not implemented
//


//
// HTTP/1.1 Parameters: WSP Well-known Parameter Assignments
//
// (see [WSP] Appdx A Table 38)
//
enum THttpParameter
    {
    EHttpQ			= 0x00, 
	EHttpCharset	= 0x01, 
	EHttpLevel		= 0x02, 
	EHttpType		= 0x03, 
	EHttpName		= 0x04, 
	EHttpFilename	= 0x05, 
	EHttpDifferences = 0x06, 
	EHttpPadding	= 0x07
	};


//
// HTTP/1.1 Headers: WSP Field Name Assignments
//
// (see [WSP] Appdx A Table 39)
//
enum THttpHeaderField
    {
    EHttpAccept	 			= 0x00,
    EHttpAcceptCharset, 
    EHttpAcceptEncoding, 
    EHttpAcceptLanguage, 
    EHttpAcceptRanges, 
    EHttpAge, 
    EHttpAllow, 
    EHttpAuthorization, 
    EHttpCacheControl 		= 0x08,
    EHttpConnection, 
    EHttpContentBase, 
    EHttpContentEncoding, 
    EHttpContentLanguage, 
    EHttpContentLength, 
    EHttpContentLocation, 
    EHttpContentMD5, 
    EHttpContentRange 		= 0x10,
    EHttpContentType, 
    EHttpDate, 
    EHttpETag, 
    EHttpExpires, 
    EHttpFrom, 
    EHttpHost, 
    EHttpIfModifiedSince, 
    EHttpIfMatch			= 0x18, 
    EHttpIfNoneMatch, 
    EHttpIfRange, 
    EHttpIfUnmodifiedSince, 
    EHttpLocation, 
    EHttpLastModified, 
    EHttpMaxForwards, 
    EHttpPragma, 
    EHttpProxyAuthenticate = 0x20, 
    EHttpProxyAuthorization, 
    EHttpPublic, 
    EHttpRange, 
    EHttpReferer, 
    EHttpRetryAfter, 
    EHttpServer, 
    EHttpTransferEncoding, 
    EHttpUpgrade			= 0x28, 
    EHttpUserAgent, 
    EHttpVary, 
    EHttpVia, 
    EHttpWarning, 
    EHttpWWWAuthenticate, 
    EHttpContentDisposition,
	EHttpXWapApplicationID	= 0x2F,  // Additional Enums required for WAP1.2 Push
	EHttpXWapContentURI,
	EHttpXWapInitiatorURI,
	EHttpAcceptApplication,
	EHttpBearerIndication,
	EHttpPushFlag,
	EHttpProfile,
	EHttpProfileDiff,
	EHttpProfileWarning
    };


//
// WSP Content-Type Assignments
//
// (see [WSP] Appdx A Table 40)
//
const TInt KHttpNumContentTypes = 53;	
const TInt KHttpMaxLenghtOfContentType = 42;
static const TText* const KHttpContentTypes[] = 
    {
    _S("*/*"),  //0x00
    _S("text/*"), 
    _S("text/html"), 
    _S("text/plain"), 
    _S("text/x-hdml"), 
    _S("text/x-ttml"), 
    _S("text/x-vCalendar"), 
    _S("text/x-vCard"), 
    _S("text/vnd.wap.wml"), // 0x08
    _S("text/vnd.wap.wmlscript"),
    _S("application/vnd.wap.catc"),
    _S("Multipart/*"),
    _S("Multipart/mixed"),
    _S("Multipart/form-data"),
    _S("Multipart/byteranges"),
    _S("multipart/alternative"),
	_S("application/*"), // 0x10
    _S("application/java-vm"),
    _S("application/x-www-form-urlencoded"),
    _S("application/x-hdmlc"),
    _S("application/vnd.wap.wmlc"),
    _S("application/vnd.wap.wmlscriptc"),
    _S("application/vnd.wap.wsic"),
    _S("application/vnd.wap.uaprof"),
    _S("application/vnd.wap.wtls-ca-certificate"), // 0x18
    _S("application/vnd.wap.wtls-user-certificate"),
    _S("application/x-x509-ca-cert"),
    _S("application/x-x509-user-cert"),
    _S("image/*"),
    _S("image/gif"),
    _S("image/jpeg"),
    _S("image/tiff"),
    _S("image/png"), // 0x20
    _S("image/vnd.wap.wbmp"),
    _S("application/vnd.wap.multipart.*"),
    _S("application/vnd.wap.multipart.mixed"),
    _S("application/vnd.wap.multipart.form-data"),
    _S("application/vnd.wap.multipart.byteranges"),
    _S("application/vnd.wap.multipart.alternative"),
    _S("application/xml"),
    _S("text/xml"), // 0x28
    _S("application/vnd.wap.wbxml"),
	_S("application/x-x968-cross-cert"),   //Additional C-Types in WAP 1.2
	_S("application/x-x968-ca-cert"),
	_S("application/x-x968-user-cert"),
	_S("text/vnd.wap.si"),
	_S("application/vnd.wap.sic"), 
	_S("text/vnd.wap.sl"),
	_S("application/vnd.wap.slc"),	//0x30
	_S("text/vnd.wap.co"),
	_S("application/vnd.wap.coc"),
	_S("application/vnd.wap.multipart.related"),
	_S("application/vnd.wap.sia")	//0x34  or 52 in decimal
    };


//
// Table 41. Languages 
//

const TInt KHttpNumLanguages = 0x8D;
static const TText8* const KHttpLanguages[] = 
	{
 	_S8("AFAR AA"),
	_S8("ABKHAZIAN AB"),
	_S8("AFRIKAANS AF"),
	_S8("AMHARIC AM"),
	_S8("ARABIC AR"),
	_S8("ASSAMESE AS"),
	_S8("AYMARA AY"),
	_S8("AZERBAIJANI AZ"),
	_S8("BASHKIR BA"),
	_S8("BYELORUSSIAN BE"),
	_S8("BULGARIAN BG"),
	_S8("BIHARI BH"),
	_S8("BISLAMA BI"),
	_S8("BENGALI BANGLA  BN"),
	_S8("TIBETAN BO"),
	_S8("BRETON BR"),
	_S8("CATALAN CA"),
	_S8("CORSICAN CO"),
	_S8("CZECH CS"),
	_S8("WELSH CY"),
	_S8("DANISH DA"),
	_S8("GERMAN DE"),
	_S8("BHUTANI DZ"),
	_S8("GREEK EL"),
	_S8("ENGLISH EN"),
	_S8("ESPERANTO EO"),
	_S8("SPANISH ES"),
	_S8("ESTONIAN ET"),
	_S8("BASQUE EU"),
	_S8("PERSIAN farsi FA"),
	_S8("FINNISH FI"),
	_S8("FIJI FJ"),
	_S8("URDU UR"),
	_S8("FRENCH FR"),
	_S8("UZBEK UZ"),
	_S8("IRISH GA"),
	_S8("SCOTS-GAELIC GD"),
	_S8("GALICIAN GL"),
	_S8("GUARANI GN"),
	_S8("GUJARATI GU"),
	_S8("HAUSA HA"),
	_S8("HEBREW HE"),
	_S8("HINDI HI"),
	_S8("CROATIAN HR"),
	_S8("HUNGARIAN HU"),
	_S8("ARMENIAN HY"),
	_S8("VIETNAMESE VI"),
	_S8("INDONESIAN ID"),
	_S8("WOLOF WO"),
	_S8("XHOSA XH"),
	_S8("ICELANDIC IS"),
	_S8("ITALIAN IT"),
	_S8("YORUBA YO"),
	_S8("JAPANESE JA"),
	_S8("JAVANESE JV"),
	_S8("GEORGIAN KA"),
	_S8("KAZAKH KK"),
	_S8("ZHUANG ZA"),
	_S8("CAMBODIAN KM"),
	_S8("KANNADA KN"),
	_S8("KOREAN KO"),
	_S8("KASHMIRI KS"),
	_S8("KURDISH KU"),
	_S8("KIRGHIZ KY"),
	_S8("CHINESE ZH"),
	_S8("LINGALA LN"),
	_S8("LAOTHIAN LO"),
	_S8("LITHUANIAN LT"),
	_S8("LATVIAN LETTISH LV"),
	_S8("MALAGASY MG"),
	_S8("MAORI MI"),
	_S8("MACEDONIAN MK"),
	_S8("MALAYALAM ML"),
	_S8("MONGOLIAN MN"),
	_S8("MOLDAVIAN MO"),
	_S8("MARATHI MR"),
	_S8("MALAY MS"),
	_S8("MALTESE MT"),
	_S8("BURMESE MY"),
	_S8("UKRAINIAN UK"),
	_S8("NEPALI NE"),
	_S8("DUTCH NL"),
	_S8("NORWEGIAN NO"),
	_S8("OCCITAN OC"),
	_S8("AFAN OROMO OM"),
	_S8("ORIYA OR"),
	_S8("PUNJABI PA"),
	_S8("POLISH PL"),
	_S8("PASHTO PUSHTO PS"),
	_S8("PORTUGUESE PT"),
	_S8("QUECHUA QU"),
	_S8("ZULU ZU"),
	_S8("KURUNDI RN"),
	_S8("ROMANIAN RO"),
	_S8("RUSSIAN RU"),
	_S8("KINYARWANDA RW"),
	_S8("SANSKRIT SA"),
	_S8("SINDHI SD"),
	_S8("SANGHO SG"),
	_S8("SERBO-CROATIAN SH"),
	_S8("SINGHALESE SI"),
	_S8("SLOVAK SK"),
	_S8("SLOVENIAN SL"),
	_S8("SAMOAN SM"),
	_S8("SHONA SN"),
	_S8("SOMALI SO"),
	_S8("ALBANIAN SQ"),
	_S8("SERBIAN SR"),
	_S8("SISWATI SS"),
	_S8("SESOTHO ST"),
	_S8("SUNDANESE SU"),
	_S8("SWEDISH SV"),
	_S8("SWAHILI SW"),
	_S8("TAMIL TA"),
	_S8("TELUGU TE"),
	_S8("TAJIK TG"),
	_S8("THAI TH"),
	_S8("TIGRINYA TI"),
	_S8("TURKMEN TK"),
	_S8("TAGALOG TL"),
	_S8("SETSWANA TN"),
	_S8("TONGA TO"),
	_S8("TURKISH TR"),
	_S8("TSONGA TS"),
	_S8("TATAR TT"),
	_S8("TWI TW"),
	_S8("UIGUR UG"),
	_S8(""),
	_S8("NAURU NA"),
	_S8("FAROESE FO"),
	_S8("FRISIAN FY"),
	_S8("INTERLINGUA IA"),
	_S8("VOLAPUK VO"),
	_S8("INTERLINGUE IE"),
	_S8("INUPIAK IK"),
	_S8("YIDDISH YI"),
	_S8("INUKTITUT IU"),
	_S8("GREENLANDIC KL"),
	_S8("LATIN LA"),
	_S8("RHAETO-ROMANCE RM")
	};

//
// WSP Character Set Assignments
//
// (see [WSP] Appdx A Table 42)
//
// The following two arrays form a paired look-up table
//
const TInt KHttpNumCharacterSets = 15;
static const TText8* const KHttpCharacterSetNames[] = 
    {
    _S8("big5"),
    _S8("iso-10646-ucs-2"),
    _S8("iso-8859-1"),
    _S8("iso-8859-2"),
    _S8("iso-8859-3"),
    _S8("iso-8859-4"),
    _S8("iso-8859-5"),
    _S8("iso-8859-6"),
    _S8("iso-8859-7"),
    _S8("iso-8859-8"),
    _S8("iso-8859-9"),
    _S8("shift_JIS"),
    _S8("us-ascii"),
    _S8("utf-8"),
    _S8("gsm-default-alphabet") // (not yet assigned)
    };
static const TInt KHttpCharacterSetCodes[] = 
    {
    0x07ea,	// big5
	0x03e8,	// iso-10646-ucs-2
    0x04,	// iso-8859-1
    0x05,	// iso-8859-2
    0x06,	// iso-8859-3
    0x07,	// iso-8859-4
    0x08,	// iso-8859-5
    0x09,	// iso-8859-6
    0x0a,	// iso-8859-7
    0x0b,	// iso-8859-8
    0x0c,	// iso-8859-9
    0x11,	// shift_JIS
    0x03,	// us-ascii
    0x6a,	// utf-8
    0xffff	// gsm-default-alphabet (not yet assigned)
    };


// Additional enumeration implementations for well known field values
// that may be found in the Cache-Control header
// As described in section 14.9 of RFC-2616
// Assigned WSP encodings 
enum TCacheControlFieldValue
	{
	ECacheControlNoCache = 0x80,// "no-cache"
	ECacheCtrlNoStore,			// "no-store"
	ECacheCtrlMaxAge,			// "max-age"
	ECacheCtrlMaxStale,			// "max-stale"
	ECacheCtrlMinFresh,			// "min-fresh"
	ECacheCtrlOnlyIfCached,		// "only-if-cached"
	ECacheCtrlPublic,			// "public"
	ECacheCtrlPrivate,			// "private"
	ECacheCtrlNoTransform,		// "no-transform"
	ECacheCtrlMustRevalidate,	// "must-revalidate"
	ECacheCtrlProxyRevalidate,	// "proxy-revalidate"
	ECacheCtrlCacheExtension	// "cache-extension"
	};

#endif // __THTTPFIELDS_H__
