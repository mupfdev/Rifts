/*
* ============================================================================
*  Name     : ApAccessPointItem.h
*  Part of  : Access Point Engine
*
*  Description: Declaration of the class CApAccessPointItem
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

#ifndef ACCESSPOINTITEM_H
#define ACCESSPOINTITEM_H

//  INCLUDES
#include <bldvariant.hrh>

#include <etelbgsm.h>
#include <nifvar.h>
#include <ApEngineVer.h>
#include <ApEngineConsts.h>


// DATA TYPES
/**
* This enum is used to identify the data when reading or writing
* CApAccessPointItem data.
* <br>Field types:
* <br>
*    8 - bit text:
* <br>ReadTextL( const TApMember aColumn, TDes8& aValue )
* <br>WriteTextL( const TApMember aColumn, const TDesC8& aValue )
* <br>  EApIspIfCallbackInfo
* <br>  EApIspInitString
* <br>
* <br>
*    16-bit text:
* <br>ReadTextL( const TApMember aColumn, TDes16& aValue )
* <br>WriteTextL( const TApMember aColumn, const TDesC16& aValue )
* <br>  EApWapAccessPointName
* <br>  EApWapCurrentBearer
* <br>  EApWapGatewayAddress
#ifdef USE_SMS
* <br>  EApSmsWapGatewayAddress
#endif
* <br>  EApWapServiceCentreAddress
* <br>  EApIapName
* <br>  EApIapServiceType
* <br>  EApIspName
* <br>  EApIspDescription
* <br>  EApIspDefaultTelNumber
* <br>  EApIspLoginName
* <br>  EApIspLoginPass
* <br>  EApIspIfName
* <br>  EApGprsIfName
* <br>  EApIspIfParams
* <br>  EApGprsIfParams
* <br>  EApIspIfNetworks
* <br>  EApGprsIfNetworks
* <br>  EApIspIfAuthName
* <br>  EApGprsIfAuthName
* <br>  EApIspIfAuthPass
* <br>  EApGprsIfAuthPassword
* <br>  EApIspIPAddr
* <br>  EApGprsIpAddr
* <br>  EApIspIPNetMask
* <br>  EApGprsIpNetMask
* <br>  EApIspIPGateway
* <br>  EApGprsIpGateway
* <br>  EApIspIPNameServer1
* <br>  EApGprsIPNameServer1
* <br>  EApIspIPNameServer2
* <br>  EApGprsIPNameServer2
* <br>  EApGprsPdpAddress
* <br>
* <br>Long text, 16 bit:
* <br>const HBufC* ReadConstLongTextL( const TApMember aColumn )
* <br>WriteLongTextL( const TApMember aColumn, const TDesC& aValue )
* <br>  EApWapStartPage
* <br>  EApIspLoginScript
* <br>  EApGprsAccessPointName
* <br>
* <br>Uint:
* <br>ReadUint( const TApMember aColumn, TUint32& aValue )
* <br>WriteUint( const TApMember aColumn, const TUint32& aValue )
* <br>  EApWapAccessPointID
* <br>  EApWapIsp
* <br>  EApWapChargecard
* <br>  EApWapIap
* <br>  EApWapIspType
* <br>  EApIapServiceId
* <br>  EApIapChargecard
* <br>  EApIspIspType
* <br>  EApIspAuthRetries
* <br>  EApGprsIfAuthRetries
* <br>  EApIspIfCallbackType
* <br>  EApIspCallBackTimeOut
* <br>  EApIspBearerName
* <br>  EApIspBearerSpeed
* <br>  EApIspBearerCE
* <br>  EApIspBearerType
* <br>  EApIspBearerCallTypeIsdn
* <br>  EApIspChannelCoding
* <br>  EApIspAIUR
* <br>  EApIspRequestedTimeSlots
* <br>  EApIspMaximumTimeSlots
* <br>  EApGprsPdpType
* <br>  EApGprsReqPrecedence
* <br>  EApGprsReqDelay
* <br>  EApGprsReqReliability
* <br>  EApGprsReqPeakThroughput
* <br>  EApGprsReqMeanPeakThroughput
* <br>  EApGprsMinPrecedence
* <br>  EApGprsMinDelay
* <br>  EApGprsMinReliability
* <br>  EApGprsMinPeakThroughput
* <br>  EApGprsMinMeanThroughput
* <br>  EApWapWspOption
* <br>  EApIspBearerCallTypeIsdn
* <br>
* <br>Bool:
* <br>ReadBool( const TApMember aColumn, TBool& aValue )
* <br>WriteBool( const TApMember aColumn, const TBool& aValue )
* <br>  EApWapSecurity
* <br>  EApIspDialResolution
* <br>  EApIspUseLoginScript
* <br>  EApIspPromptForLogin
* <br>  EApIspDisplayPCT
* <br>  EApIspIfPromptForAuth
* <br>  EApGprsIfPromptForAuth
* <br>  EApIspIfCallbackEnabled
* <br>  EApIspIPAddrFromServer
* <br>  EApGprsIpAddrFromServer
* <br>  EApIspIPDnsAddrFromServer
* <br>  EApGprsIpDnsAddrFromServer
* <br>  EApIspEnableIpHeaderComp
* <br>  EApGprsHeaderCompression
* <br>  EApIspEnableLCPExtensions
* <br>  EApGprsEnableLCPExtensions
* <br>  EApIspDisablePlainTextAuth
* <br>  EApGprsDisablePlainTextAuth
* <br>  EApIspEnableSWCompression
* <br>  EApGprsDataCompression
* <br>  EApGprsUseAnonymAccess
* <br>  EApIsReadOnly
*/
enum TApMember
    {
    // WAP Access Point Table
    EApWapAccessPointID,            ///< The Uid of the access point.
                                    ///< READ ONLY, assigned by the database.
    EApWapAccessPointName,          ///< The name of the access point
    EApWapCurrentBearer,            ///< Indicates the name of the table from
                                    ///< which to read the bearer information
    EApWapStartPage,                ///< WAP start page URL, LONG TEXT!

    // WAP Common (present in both tables)
    EApWapGatewayAddress,           ///< WAP gateway address (IP address)
    EApWapWspOption,                ///< Enum value indicating whether
                                    ///< connection-oriented or connectionless
                                    ///< API should be used.
                                    ///< Type is TCommsDbWapWspOption.
    EApWapSecurity,                 ///< Attepmt secure WTLS connection to
                                    ///< the gateway

    // WAP IP Bearer Table
    EApWapIsp,                      ///< Identifier of the ISP to use if this
                                    ///< is an ISP type database
    EApWapChargecard,               ///< Identifier for the chargecard to use
                                    ///< if this is an ISP type database
    EApWapIap,                      ///< Identifier of a record in the IAP
                                    ///< table to be used if this is an IAP
                                    ///< type database
    EApWapIspType,                  ///< Enum value indicating whether IAP/ISP
                                    ///< is a dial in or a dial out

    // WAP SMS Bearer Table
    // EApSmsWapGatewayAddress is mapped to EApWapGatewayAddress,
    // different enum needed only for being able to
    // distinguish when editing...
#ifdef USE_SMS
    // Note: SMS had been dropped
    EApSmsWapGatewayAddress,        ///< SMS Gateway Address (phone number)
    EApWapServiceCentreAddress,     ///< SMS Centre Address (phone number)
#endif

    // IAP Table
    EApIapName,                     ///< The name of this IAP
    EApIapServiceType,              ///< Name of service table in this IAP
    EApIapServiceId,                ///< Identifier of service in this IAP
    EApIapChargecard,               ///< Identifier of the chargecard in
                                    ///< this IAP

    // ISP table
    EApIspName,                     ///< The name of this ISP
    EApIspDescription,              ///< Application's description of this ISP
    EApIspIspType,                  ///< Enum value indicating ISP type, e.g.
                                    ///< Internet ISP, WAP Isp.TCommsDbIspType.
    EApIspDefaultTelNumber,         ///< Default phone number
    EApIspDialResolution,           ///< Perform dialing resolution for default
                                    ///< phone number?
    EApIspUseLoginScript,           ///< Use login script?
    EApIspLoginScript,              ///< Login script (used only if Use Login
                                    ///< Script is true), LONG TEXT.
    EApIspPromptForLogin,           ///< Prompt user for username and password?
    EApIspLoginName,                ///< Login name
    EApIspLoginPass,                ///< Login password
    EApIspDisplayPCT,               ///< Display PCT (without scanning script
                                    ///< for READ command) UNUSED, always FALSE
    EApIspIfName,                   ///< Interface name
    EApIspIfParams,                 ///< Interface parameter string
    EApIspIfNetworks,               ///< Comma separated list of network
                                    ///< protocols
    EApIspIfPromptForAuth,          ///< Prompt user for authentication
                                    ///< username and password?
    EApIspIfAuthName,               ///< Authentication username used by PPP
    EApIspIfAuthPass,               ///< Authentication password used by PPP
    EApIspAuthRetries,              ///< Number of times to retry
                                    ///< authentication if it fails
    EApIspIfCallbackEnabled,        ///< Is callback enabled?
    EApIspIfCallbackType,           ///< Enum value indicating the type of
                                    ///< callback (if enabled).
                                    ///< enum TCallbackAction.
    EApIspIfCallbackInfo,           ///< Info for callback request (if enabled)
                                    ///< 8-bit text field.
    EApIspCallBackTimeOut,          ///< Time to wait for callback in
                                    ///< microseconds (if enabled)
    EApIspIPAddrFromServer,         ///< Get IP address from server?
    EApIspIPAddr,                   ///< IP address of interface
    EApIspIPNetMask,                ///< IP net mask of interface
    EApIspIPGateway,                ///< IP address of gateway
    EApIspIPDnsAddrFromServer,      ///< Get DNS address from server?
    EApIspIPNameServer1,            ///< IP address of primary name server
    EApIspIPNameServer2,            ///< IP address of secondary name server
    EApIspEnableIpHeaderComp,       ///< Enable IP header compression?
    EApIspEnableLCPExtensions,      ///< Enable LCP extensions?
    EApIspDisablePlainTextAuth,     ///< Disable plain text authentication?
    EApIspEnableSWCompression,      ///< Enable software compression?
    EApIspBearerName,               ///< Enum value specifying the name of the
                                    ///< bearer, e.g. Asunchronous Modem,
                                    ///< RBasicGsmCall::TBearerName
    EApIspBearerSpeed,              ///< Enum value specifying the bearer speed
                                    ///< TApCallSpeed.
    EApIspBearerCallTypeIsdn,       ///< call type is ISDN or Analogue...
    EApIspBearerCE,                 ///< Enum value specifying the bearer CE,
                                    ///< RBasicGsmCall::TBearerCE
    EApIspInitString,               ///< Modem initialization string to be used
                                    ///< when this ISP is in use.This string
                                    ///< will be copied into the
                                    ///< MODEM_ISP_INIT_STRING field by
                                    ///< NetDial. 8-bit text field.
    EApIspBearerType,               ///< Enum value indicating connection type
                                    ///< (CSD or HSCSD), TCommsDbBearerType
    EApIspChannelCoding,            ///< Enum value specifying HSCSD channel
                                    ///< coding
    EApIspAIUR,                     ///< Enum value specifying AIUR for HSCSD
    EApIspRequestedTimeSlots,       ///< Requested number of time slots for
                                    ///< HSCSD
    EApIspMaximumTimeSlots,         ///< Maximum number of time slots for HSCSD
                                    ///< which could be requested during this
                                    ///< connection

    EApGprsAccessPointName,         ///< Access Point Name, LONG TEXT!
    EApGprsPdpType,                 ///< PDP type
    EApGprsPdpAddress,              ///< PDP address
    EApGprsReqPrecedence,           ///< Requested quality of service
                                    ///< precedence class
    EApGprsReqDelay,                ///< Requested quality of service
                                    ///< delay class
    EApGprsReqReliability,          ///< Requested quality of service
                                    ///< reliability class
    EApGprsReqPeakThroughput,       ///< Requested quality of service
                                    ///< peak throughput class
    EApGprsReqMeanPeakThroughput,   ///< Requested quality of service
                                    ///< mean throughput class
    EApGprsMinPrecedence,           ///< Minimum quality of service
                                    ///< precedence class
    EApGprsMinDelay,                ///< Minimum quality of service
                                    ///< delay class
    EApGprsMinReliability,          ///< Minimum quality of service
                                    ///< reliability class
    EApGprsMinPeakThroughput,       ///< Minimum quality of service
                                    ///< peak throughput class
    EApGprsMinMeanThroughput,       ///< Minimum quality of service
                                    ///< mean throughput class
    EApGprsUseAnonymAccess,         ///< Use anonymous access on?

    // followings are mapped to ISP... fields
    EApGprsDataCompression,         ///< Data compression on?
    EApGprsHeaderCompression,       ///< IP header compression on?
    EApGprsIfName,                  ///< Interface name
    EApGprsIfParams,                ///< Interface parameter string
    EApGprsIfNetworks,              ///< Comma separated list of network
                                    ///< protocols
    EApGprsIfPromptForAuth,         ///< Prompt user for authentication
                                    ///< username and password?
    EApGprsIfAuthName,              ///< Authentication username used by PPP
    EApGprsIfAuthPassword,          ///< Authentication password used by PPP
    EApGprsIfAuthRetries,           ///< Number of times to retry
                                    ///< authentication if it fails
    EApGprsIpNetMask,               ///< IP net mask of interface
    EApGprsIpGateway,               ///< IP address of gateway
    EApGprsIpAddrFromServer,        ///< Get IP adresses (for Symbian OS)
                                    ///< from server?
    EApGprsIpAddr,                  ///< IP address of Symbian OS
    EApGprsIpDnsAddrFromServer,     ///< Get DNS addresses from server?
    EApGprsIPNameServer1,           ///< IP address of primary name server
    EApGprsIPNameServer2,           ///< IP address of secondary name server
    EApGprsEnableLCPExtensions,     ///< Enable LCP extension?
    EApGprsDisablePlainTextAuth,    ///< Disable plain text authentication?
    EApIsReadOnly                   ///< Is the current record read only?
#ifdef __PROXY_SETTINGS
// expanding this enum is safe and will not cause any trouble as all public 
// part of this module uses it as a const parameter and NEVER as a return value,
// therefore non-aware clients will NEVER meet with the new ones, thus it can not
// cause any problems that they do not expect them...
    ,
    EApProxyServerAddress,          ///< Proxy server address, long text
    EApProxyProtocolName,           ///< Proxy protocol name, Text
    EApProxyPortNumber,             ///< Proxy port number,  TUint32
    EApProxyUseProxy,               ///< Use proxy server?, TBool 
    EApProxyExceptions,             ///< ';' separated list of addr. for wich 
                                    ///< the server should not be used. Long text
    EApHasProxySettings
#endif // __PROXY_SETTINGS
    };



// CONSTANTS
// D E P R E C A T E D,  please do not use it!!!!!!!!!!
// can not remove as it was part of the public API...
const TInt KApMemberNum = EApGprsDisablePlainTextAuth+1;


// CLASS DECLARATION

/**
* CApAccessPointItem is used to exchange data between engine and client.
* It holds the information for an access point including WAP, IAP, ISP
* (if present & applies).
* This class uses the same approach as CommDB to read and write data: it
* has functions for each data type implemented. To read or write the data,
* we have to know the data type and the enum name of the 'column'.
* The column values has the names of the database columns with the 'EAp'
* prefix. The reason for this (not using the database column descriptors)
* is performance. It is much faster to compare enum values than literals.
*/
class CApAccessPointItem :public CBase
    {

    public:  // Constructors and destructor
        /**
        * Two-phased constructor. Leaves on failure, places instance
        * on cleanup stack. Instance is initialised to default values.
        * The created instance is suitable for passing to CApDataHandler's
        * functions, contains all necessary information.
        * @return The constructed CApAccessPointItem.
        */
        IMPORT_C static CApAccessPointItem* NewLC();


        /**
        * Destructor.
        */
        IMPORT_C virtual ~CApAccessPointItem();


        /**
        * Copies the data from another CApAccessPointItem.
        * Substitute for the "assignment operator". It requires allocation
        * thus can leave.
        * Wap Access Point Uid is not copied.
        */
        IMPORT_C void CopyFromL( const CApAccessPointItem& aCopyFrom  );


        /**
        * Equality operator. Wap Access Point Uid is not counted.
        */
        IMPORT_C TBool operator==( const CApAccessPointItem& aitem ) const;


        /**
        * Inequality operator. Wap Access Point Uid is not counted.
        */
        IMPORT_C TBool operator!=( const CApAccessPointItem& aitem ) const;


    protected:      // Constructors

        /**
        * C++ default constructor.
        */
        IMPORT_C CApAccessPointItem();

        /**
        * Second-phase constructor.
        */
        IMPORT_C void ConstructL();




    public: // New functions


        /**
        * This function reads up an 8-bit text value from the specified column.
        * @param aColumn Enum value indicating the column to read.
        * @param aValue Reference to an 8-bit descriptor to hold the value
        * @return no return value
        */
        IMPORT_C void ReadTextL( const TApMember aColumn, TDes8& aValue );

        /**
        * This function reads up a 16-bit text value from the specified column.
        * @param aColumn Enum value indicating the column to read.
        * @param aValue Reference to a 16-bit descriptor to hold the value
        * @return no return value
        */
        IMPORT_C void ReadTextL( const TApMember aColumn, TDes16& aValue );

        /**
        * NOTE: This function is deprecated. Use ReadConstLongTextL!
        * This function reads up a long text value from the specified column.
        * The ownership is not passed to the caller. It means that the caller
        * should not delete the received value.
        * If the caller must take the ownership for any reason, must make a
        * copy and use that and delete the copy when no longer needed.
        * @param aColumn Enum value indicating the column to read.
        * @return A HBufC* to the value.
        */
        IMPORT_C HBufC* ReadLongTextL( const TApMember aColumn );


        /**
        * This function reads up a long text value from the specified column.
        * The ownership is not passed to the caller. It means that the caller
        * should not delete the received value.
        * If the caller must take the ownership for any reason, must make a
        * copy and use that and delete the copy when no longer needed.
        * @param aColumn Enum value indicating the column to read.
        * @return A const HBufC* to the value.
        */
        IMPORT_C const HBufC* ReadConstLongTextL( const TApMember aColumn );



        /**
        * This function reads the length of the text in the specified column.
        * @param aColumn Enum value indicating the column to read.
        * @return The length of the text in that column.
        */
        IMPORT_C TUint32 ReadTextLengthL( const TApMember aColumn );


        /**
        * This function reads up a TUint32 value from the specified column.
        * In case the given value was not written to the database,
        * it will return KErrValueUnspecified.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * @param aColumn Enum value indicating the column to read.
        * @param aValue A reference to a TUint32 to hold the value
        * @return Error code.
        */
        IMPORT_C TInt ReadUint( const TApMember aColumn, TUint32& aValue );

        /**
        * This function reads up a boolean value from the specified column.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * @param aColumn Enum value indicating the column to read.
        * @param aValue A reference to a boolean to hold the value
        * @return Error code.
        */
        IMPORT_C TInt ReadBool( const TApMember aColumn, TBool& aValue );


        // Update
        /**
        * This function writes an 8-bit text value to the specified column.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * This function can Leave if the copying of the text does not succeed.
        * Possible leave codes are the system leave codes.
        * @param aColumn Enum value indicating the column to write.
        * @param aValue Reference to an 8-bit text descriptor to the value
        * @return Error code.
        */
        IMPORT_C TInt WriteTextL( const TApMember aColumn,
                                const TDesC8& aValue );

        /**
        * This function writes a 16-bit text value to the specified column.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * This function can Leave if the copying of the text does not succeed.
        * @param aColumn Enum value indicating the column to write.
        * @param aValue Reference to a 16-bit text descriptor to the value
        * @return Error code.
        */
        IMPORT_C TInt WriteTextL( const TApMember aColumn,
                                const TDesC16& aValue );

        /**
        * This function writes a long text value to the specified column.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * This function can Leave if the copying of the text does not succeed.
        * @param aColumn Enum value indicating the column to write.
        * @param aValue Reference to a 16-bit text descriptor to the value
        * @return Error code.
        */
        IMPORT_C TInt WriteLongTextL( const TApMember aColumn,
                                    const TDesC& aValue );

        /**
        * This function writes a TUint32 value to the specified column.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * @param aColumn Enum value indicating the column to write.
        * @param aValue A const reference to a TUint32 value
        * @return Error code.
        */
        IMPORT_C TInt WriteUint( const TApMember aColumn,
                                const TUint32& aValue );

        /**
        * This function writes a boolean value to the specified column.
        * If the specified column does not exist (that is, not part of the
        * database structure), it will Panic in debug builds and it will
        * return KErrInvalidColumn in release builds without Panicking.
        * Panic is used in debug builds because it indicates a programming
        * error. In release, it 'notifies' the caller about the error through
        * the return value but enables system to continue operation.
        * @param aColumn Enum value indicating the column to write.
        * @param aValue A const reference to a boolean value
        * @return Error code.
        */
        IMPORT_C TInt WriteBool( const TApMember aColumn,
                                const TBool& aValue );


        // Query
        // COMMON
        /**
        * This function returns the ID of the access point
        * @return The ID of this access point
        */
        IMPORT_C const TUint32 WapUid() const;


        /**
        * This function returns the name of the connection
        * Ownership is not passed.
        * @return The name of the connection
        */
        IMPORT_C const TDesC& ConnectionName() const;


        // WAP-spec.
        /**
        * This function returns the current WAP bearer for the access point
        * Ownership is not passed.
        * @return The current WAP bearer for the access point
        */
        IMPORT_C const TDesC& WapBearer() const;


        /**
        * This function returns the bearer type for the current access point
        * @return The current bearer type for the access point
        */
        IMPORT_C const TApBearerType BearerTypeL();


        /**
        * This function sets the bearer type for the current access point
        * @param aBearer TApBearerType enum indicating the desired bearer type.
        * @return No return value.
        */
        IMPORT_C void SetBearerTypeL( TApBearerType aBearer );


        /**
        * This function writes a 16-bit text value to the 'name' fields
        * of the access point.
        * This includes: WAP_ACCESS_POINT, IAP, Dial/in/out/Gprs In/Out
        * table's COMM_DB_NAME fields.
        * These fields are (by TApMember): EApWapAccessPointName, EApIapName,
        * EApIspName.
        * It is useful if we need to use same names.
        * @param aValue A const reference to a 16-bit text descriptor to
        * the value.
        * @return No return value.
        */
        IMPORT_C void SetNamesL( const TDesC16& aValue );


        /**
        * This function checks the integrity of the CApAccessPointItem.
        * Currently checks:
        * IF WAP_IP_BEARER, WAP_ISP_TYPE conforms to IAP_SERVICE_TYPE
        * @return Boolean indicating whether the sanity check has
        * passed(ETrue) or not(EFalse)
        */
        IMPORT_C TBool SanityCheckOk();


        /**
        * This function compares this and the passed CApAccessPointItem
        * whether they have the same ISP and bearer
        * Returns true if the APs have the same phone number
        * @param aItem a CApAccessPointItem to compare with
        * @return whether the APs have the same isp and bearer
        */
        IMPORT_C TBool HasSameIspAndBearerL( CApAccessPointItem& aItem );

        /**
        * This function returns whether the access point is read-only or not.
        * @return Whether the current access point is read-only or not.
        */
        IMPORT_C const TBool IsReadOnly() const;

    private:
        /**
        * Returns whether a given member is specified (after reading it from
        * the DB) or not.
        */
        TBool Specified( TApMember aMember );

        /**
        * Sets a given member as specified or not
        */
        void Specify( TApMember aMember, TBool aOn );

        /**
        * Sets all WAP member as specified or not
        */
        void SpecifyWap( TBool aOn );

#ifdef USE_SMS
        /**
        * Sets all SMS member as specified or not
        */
        void SpecifySMSBearer( TBool aOn );
#endif
        /**
        * Sets all IP bearer member as specified or not
        */
        void SpecifyIpBearer( TBool aOn );

        /**
        * Sets all IAP member as specified or not
        */
        void SpecifyIAP( TBool aOn );

        /**
        * Sets all ISP member as specified or not
        */
        void SpecifyISP( TBool aOn );

        /**
        * Sets all GPRS member as specified or not
        */
        void SpecifyGPRS( TBool aOn );

        /**
        * Sets all member as specified or not
        */
        void SpecifyAll( TBool aOn );

        /**
        * Sets iGetDNSIPFromServer according the currently valid iPrimaryDNS
        * & iSecondaryDNS values. Called internally, after every setting of
        * the above two values
        */
        void SetDnsIpFromServer();

        /**
        * Sets iIspIPAddrFromServer according the currently valid iIspIPAddr
        * value. Called internally, after every setting of iIspIPAddr values
        */
        void SetIpFromServer();

        /**
        * Reallocates a passed 16-bit descriptor. Passed descriptor is deleted,
        * new one is AllocL-ed
        * Passed descriptor MUST NOT BE on the CleanupStack
        */
        void ReAllocL(HBufC*& aDes, const TDesC16& aValue);

        /**
        * Reallocates a passed 8-bit descriptor. Passed descriptor is deleted,
        * new one is AllocL-ed
        * Passed descriptor MUST NOT BE on the CleanupStack
        */
        void ReAllocL(HBufC8*& aDes, const TDesC8& aValue);


        /**
        * Compares THIS and the passed aItem.
        */
        TBool DoCompareApL( const CApAccessPointItem& aItem ) const;


        /**
        * Compares the WAP part of THIS and the passed aItem.
        * Does not compares IAP ID
        */
        TBool CompareWap( const CApAccessPointItem& aItem ) const;


        /**
        * Compares the IAP part of THIS and the passed aItem.
        */
        TBool CompareIap( const CApAccessPointItem& aItem ) const;


        /**
        * Compares the IsP part of THIS and the passed aItem.
        */
        TBool CompareIsp( const CApAccessPointItem& aItem ) const;


        /**
        * Compares the Gprs part of THIS and the passed aItem.
        */
        TBool CompareGprs( const CApAccessPointItem& aItem ) const;


        /**
        * Removes leading 0s from the passed IP address.
        * @param aValue A descriptor holding the IP address to remove
        * leading 0s from
        * @return A newly allocated HBufC holding the resulting string.
        */
        HBufC* GetCleanIpAddressLC( const TDesC& aValue );



        /**
        * Removes invalid chars e.g. space, () from the passed phone number.
        * (valid are 0,1,2,..9,p,w,+,*,#)
        * Strips pre- and postfixes, prefix separator is#,
        * postfix separators are p, w or +
        * @param aValue A descriptor holding the phone number
        * @return A newly allocated HBufC holding the resulting string.
        */
        HBufC* GetPlainPhoneNumberLC( const TDesC& aNumber );


        /**
        * Compares the 'default phone number' (ISP dial-in number) of this
        * and the passed CApAccessPointItem
        * @return a TBool indicating whether the phone numbers are
        * the same or not.
        */
        TBool IsSamePhoneNumberL( CApAccessPointItem& aItem );


        /**
        * Removes invalid vhars from the passed phone number
        * @return a HBufC holding the new text
        */
        HBufC* RemoveInvalidPhoneCharsLC( const TDesC16& aInText );


        /**
        * Removes invalid chars from the passed text
        * Invalid chars are: TAB
        * @return a HBufC16 holding the new text
        */
        HBufC* RemoveInvalidCharsLC( const TDesC16& aInText );


        /**
        * Removes invalid chars from the passed text
        * Invalid chars are: TAB
        * @return a HBufC8 holding the new text
        */
        HBufC8* RemoveInvalidCharsLC( const TDesC8& aInText );


#ifdef __PROXY_SETTINGS
        /**
        * Compares the proxy data of this and the passed CApAccessPointItem.
        * 
        */
        TBool CompareProxy( const CApAccessPointItem& aItem ) const;


        /**
        * Returns whether the Ap has proxy data or not.
        * 
        */
        TBool HasProxy() const;


        /**
        * Sets the proxy flag.
        * 
        */
        void SetProxyFlag();
#endif // __PROXY_SETTINGS


        /*
        * Gets the shareddata value whether HSCSD is enabled or not
        * @return A TInt stating if it is enabled (1) or not (0)
        */
        TInt IsHSCSDEnabled();

private:    // Data

        // member data
        // COMMON
        TUint32 iWapUid;        ///< The unique identifier of the AP record.
        HBufC* iWapAccessPointName;


        // WAP-spec.
        HBufC* iWapBearer;
        HBufC* iStartingPage;

        // common for bearers
        HBufC* iWapGatewayAddress;  ///< The WAP gateway address
        TBool iIsWTLSSecurityOn;
        TUint32 iIsConnectionTypeContinuous;

        // IP Bearer
        TUint32 iWapIsp;
        TUint32 iChargeCard;
        TUint32 iWapIap;
        TCommsDbWapIspType iWapIspType;

#ifdef USE_SMS
        // SMS bearer
        HBufC* iServiceAccessNumber;
#endif

        // IAP-part
        HBufC* iIapName;

        TUint32 iIapServiceId;
        HBufC* iIapServiceType;

        TUint32 iIapChargeCardId;

        // ISP-part
        HBufC* iIspName;
        HBufC* iIspDescription;
        TCommsDbIspType  iIspType;
        HBufC* iIspDefaultTelNumber;
        TBool iIspDialResolution;
        TBool iUseLoginScript;
        HBufC* iLoginScript;
        TBool iPromptPassword;
        HBufC* iUserName;
        HBufC* iPassword;
        TBool iDisplayTerminalWindow;
        HBufC* iIspIfName;
        HBufC* iIspIfParams;
        HBufC* iIspIfNetworks;
        TBool iIspIfPromptForAuth;
        HBufC* iIspIfAuthName;
        HBufC* iIspIfAuthPass;
        TUint32 iIspIfAuthRetries;
        TBool iUseCallBack;
        TCallbackAction iCallBackTypeIsServerNum;
        HBufC8* iIspIfCallbackInfo;
        TUint32 iIspCallbackTimeOut;
        TBool iIspIPAddrFromServer;
        HBufC* iIspIPAddr;
        HBufC* iIspIPNetMask;
        HBufC* iIspGateway;
        TBool iGetDNSIPFromServer;
        HBufC* iPrimaryDNS;
        HBufC* iSecondaryDNS;
        TBool iEnablePPPCompression;
        TBool iIspEnableLCPExtensions;
        TBool iIsPasswordAuthenticationSecure;
        TBool iIspEnableSwCompression;
		/*****************************************************
		*	Series 60 Customer / ETel
		*	Series 60  ETel API
		*****************************************************/
        RBasicGsmCall::TBearerName  iIspBearerName;
        TApCallSpeed iMaxConnSpeed;
        TApCallType iBearerCallTypeIsdn;
        RBasicGsmCall::TBearerCE iIspBearerCE;
        HBufC8* iIspInitString;
        TUint32 iIspBearerType;
        TUint32 iIspChannelCoding;
        TUint32 iIspAIUR;
        TUint32 iIspRequestedTimeSlots;
        TUint32 iIspMaximumTimeSlots;

        // GPRS part
        HBufC*  iGprsAccessPointName;
        TUint32 iGprsPdpType;
        HBufC*  iGprsPdpAddress;
        TUint32 iGprsReqPrecedence;
        TUint32 iGprsReqDelay;
        TUint32 iGprsReqReliability;
        TUint32 iGprsReqPeakThroughput;
        TUint32 iGprsReqMeanPeakThroughput;
        TUint32 iGprsMinPrecedence;

        TUint32 iGprsMinDelay;
        TUint32 iGprsMinReliability;
        TUint32 iGprsMinPeakThroughput;
        TUint32 iGprsMinMeanThroughput;
        TBool   iGprsUseAnonymAccess;

        CArrayFixFlat<TBool>    *iSpecified;
        TBool iIsReadOnly;

#ifdef __PROXY_SETTINGS
        HBufC*  iApProxyProtocolName;
        HBufC*  iApProxyServerAddress;
        TUint32 iApProxyPortNumber;
        TBool   iApProxyUseProxy;
        HBufC*  iApProxyExceptions;
        TBool   iApHasProxySettings;
#endif // __PROXY_SETTINGS


    protected:  // Friend classes
        friend class CApDataHandler;


    };

#endif      // ACCESSPOINTITEM_H

// End of File
