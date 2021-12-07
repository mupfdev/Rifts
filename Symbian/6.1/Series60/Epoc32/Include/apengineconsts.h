/*
* ============================================================================
*  Name     : ApEngineConsts.h
*  Part of  : Access Point Engine
*
*  Description: Used constants of the ApEngine.
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

#ifndef APENGINE_CONSTS_H
#define APENGINE_CONSTS_H

#include <ApEngineVer.h>


// ERROR CODES
// Used either as return values or leave codes. Apart from these, system error
// codes can also be returned or leaved with.

/// Attempting to read or write a column which does not exists.
const TInt  KErrInvalidColumn       = -300;

/// The given bearer is not valid.
const TInt  KErrInvalidBearer       = -301;

/// The type of the database is not valid
const TInt  KErrInvalidDatabaseType = -302;

/// The name of the AP is not valid (length = 0)
const TInt  KErrInvalidName         = -303;

const TInt  KErrDescOverflow        = -304;

/// The passed pointer was invalid = NULL
const TInt  KErrNullPointerPassed   = -305;

/// The filter is not valid
const TInt  KErrInvalidFilterType   = -310;

/// The bearer is not valid
const TInt  KErrInvalidBearerType   = -311;

/// The ISP type given is invalid
const TInt  KErrInvalidIspRequest   = -312;

/// Used when the requested value was not specified in the database
const TInt  KErrValueUnspecified    = -323;

const TInt  KApEngineMaxSql              = 255;



/// These constants are used to represent the sorting order used in CApSelect.
const TInt  KEApSortUidAscending         = 0x00000001;  ///< The sorting is
                                                        ///< done according to
                                                        ///< the ID of the
                                                        ///< access points in
                                                        ///< ascending order.
const TInt  KEApSortUidDescending        = 0x00000002;  ///< The sorting is
                                                        ///< done according to
                                                        ///< the ID of the
                                                        ///< access points in
                                                        ///< descending order.
const TInt  KEApSortNameAscending        = 0x00000003;  ///< The sorting is
                                                        ///< done according to
                                                        ///< the name of the
                                                        ///< access points in
                                                        ///< ascending order.
const TInt  KEApSortNameDescending       = 0x00000004;  ///< The sorting is
                                                        ///< done according to
                                                        ///< the name of the
                                                        ///< access points in
                                                        ///< descending order.


/// These enums are used to represent one the filtering criterias in CApSelect.
const TInt  KEApIspTypeInternetOnly     = 0x00000001;   ///< Filter allows only
                                                        ///< access points that
                                                        ///< are capable of
                                                        ///< only internet
                                                        ///< access.
const TInt  KEApIspTypeWAPOnly          = 0x00000002;   ///< Filter allows only
                                                        ///< access points that
                                                        ///< are capable of
                                                        ///< only WAP access.
const TInt  KEApIspTypeInternetAndWAP   = 0x00000004;   ///< Filter allows only
                                                        ///< access points that
                                                        ///< are capable of
                                                        ///< internet AND
                                                        ///< WAP access.
const TInt  KEApIspTypeWAPMandatory     = 0x00000008;   ///< Filter allows only
                                                        ///< access points that
                                                        ///< are capable of
                                                        ///< WAP access AND
                                                        ///< contain mandatory
                                                        ///< WAP settings.
const TInt  KEApIspTypeAll              = 0x00000010;   ///< No filtering is
                                                        ///< done, all access
                                                        ///< points are shown.



const TInt KModifiableTextLength        = 100;
const TInt KModifiableLongTextLength    = 1000;


// typedef
enum TApBearerType      /// These enums are used to represent the possible
                        /// bearer types and the filtering criteria
                        /// in CApSelect.
    {
    EApBearerTypeCSD    = 0x00000001,       ///< Filter allows only access
                                            ///< points that has CSD as bearer.
    EApBearerTypeGPRS   = 0x00000002,       ///< Filter allows only access
                                            ///< points that has GPRS as bearer
#ifdef USE_SMS
    EApBearerTypeSMS    = 0x00000004,       ///< Filter allows only access
                                            ///< points that has SMS as bearer.
    EApBearerTypeHSCSD  = 0x00000008,       ///< Filter allows only access
                                            ///< points that has
                                            ///< HSCSD as bearer.
    EApBearerTypeAll    = 0x00000010,       ///< No filtering is done,
                                            ///< all access points are shown.
#else
    EApBearerTypeHSCSD  = 0x00000004,       ///< Filter allows only access
                                            ///< points that has HSCSD
                                            ///< as bearer.
    EApBearerTypeAll    = 0x00000008,       ///< No filtering is done,
                                            ///< all access points are shown.
#endif
    };


enum TApCallSpeed       /// These enums are used to represent
                        /// the connection speed.
    {
    KSpeedAutobaud=0x00000000,          ///< Autodetect
    KSpeed9600=0x00000001,              ///< 9600
    KSpeed14400=0x00000002,             ///< 14400
    KSpeed19200=0x00000003,             ///< 19200
    KSpeed28800=0x00000004,             ///< 28800
    KSpeed38400=0x00000005,             ///< 38400
    KSpeed43200=0x00000006              ///< 43200
    };


enum TApCallType        /// These enums are used to represent
                        /// the conn. type Analogue/ISDNv110/ISDNv120
    {
    ECallTypeAnalogue,          ///< Analogue
    ECallTypeISDNv110,          ///< ISDN v. 110
    ECallTypeISDNv120           ///< ISDN v. 120
    };

const TUint32 KMaxAnalogueSpeed    = KSpeed28800;
const TUint32 KMaxIsdnSpeed        = KSpeed43200;



#define KApMaxConnNameLength            30

// The following constants are deprecated, DO NOT USE THEM!
// DO NOT USE STARTS
#define KApMaxGprsApNameLength          100
#define KApMaxLoginNameLength           32
#define KApMaxStartPageLength           1000
#define KApMaxAccessNumLength           21
#define KApCBInfoLength                 21
#define KApMaxServiceCentreAddrLength   21
#define KApMaxIpAddressLength           100
#define KApMaxLoginScriptLength         1000
#define KApMaxLoginPasswordLength       20
// DO NOT USE ENDS


_LIT( KSqlSelectNum, "SELECT %s from %s WHERE %s=%d" );
_LIT( KSqlSelectBaseNum, "SELECT * from %s WHERE %s=%d" );

/// 'Dynamic' IP address to use in comparisons
_LIT( KDynIpAddress, "0.0.0.0" );

/// A start page, which have to be considered as invalid.
_LIT( KInvStartPage, "http://" );

/// Number of retries that are used in database operations
const TInt KRetryCount              = 5;


/// Time to wait before retry database operation (==0.10 secs = 100000microsec.)
#define KRetryWait  100000 /* in TTimeIntervalMicroSeconds32 */

// callback timeout in microseconds
const TUint32 KCallBackTimeOut  = 60000000;
#endif

// End of File
