// CDBCOLS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// Comms Database Header File - table and column names

#ifndef __CDBCOLS_H__
#define __CDBCOLS_H__

#include <e32std.h>

// Public database table names

#define IAP												_S("IAP")
#define DIAL_OUT_ISP									_S("DialOutISP")
#define DIAL_IN_ISP										_S("DialInISP")
#define OUTGOING_GPRS									_S("OutgoingGPRS")
#define INCOMING_GPRS									_S("IncomingGPRS")
#define MODEM											_S("Modem")
#define LOCATION										_S("Location")
#define CHARGECARD										_S("Chargecard")
#define PROXIES											_S("Proxies")
#define WAP_ACCESS_POINT								_S("WAPAccessPoint")
#define WAP_IP_BEARER									_S("WAPIPBearer")
#define WAP_SMS_BEARER									_S("WAPSMSBearer")
#define DEFAULT_GPRS									_S("DefaultGPRS")
#define BT_DEVICE_TABLE									_S("BTDeviceTable")
#define BT_DEFAULT_TABLE								_S("BTDefaultTable")
#define BT_SECURITY_TABLE								_S("BTSecurityTable")
#define ACCESS_TYPE_TABLE								_S("AccessTypeTable")

// Global settings

#define DATABASE_TYPE									_S("DatabaseType")					// will be deprecated in 7.0
#define REDIAL_ATTEMPTS									_S("RedialAttempts")				// Number of times to retry dialling if the line is busy
#define SMS_BEARER										_S("SmsBearer")						// Takes the values of RGprs::TSmsBearer from ETEL
#define GPRS_ATTACH_MODE								_S("GPRSAttachMode")				// Takes the values of RGprs::TGprsAttachMode from ETEL
#define ACCEPT_INCOMING_GPRS							_S("AcceptIncomingGprs")			// Takes a TBool value - ETrue = accept incoming requests, EFalse = reject incoming requests
#define GPRS_CLASS_C_BEARER								_S("GPRSClassCBearer")				// Takes the values of TCommDbGprsClassCBearer
#define CONNECTION_ATTEMPTS								_S("ConnectionAttempts")			// Number of connection preferences, with incremental rank, to try
#define DEVICE_TYPE										_S("DeviceType")

// Deprecated names

#define ASK_USER_BEFORE_DIAL							_S("AskUserBeforeDial")				// Kept for backwards compatibility
#define DIAL_OUT_IAP									_S("DialOutIAP")
#define DIAL_IN_IAP										_S("DialInIAP")
#define IAP_ISP											_S("IAPISP")
#define IAP_MODEM										_S("Modem")
#define IAP_LOCATION									_S("Location")
#define WAP_LOCATION									_S("Location")
#define CLIENT_TIMEOUT									_S("ClientTimout")
#define ROUTE_TIMEOUT									_S("RouteTimeout")

// Columns common to all tables

#define COMMDB_ID										_S("Id")							// Id of the row
#define COMMDB_NAME										_S("Name")							// Name of the row

// Columns for IAP table

#define IAP_SERVICE										_S("IAPService")
#define IAP_SERVICE_TYPE								_S("IAPServiceType")
#define IAP_CHARGECARD									_S("Chargecard")

// Label for retrieving active isp service type

#define SERVICE_TYPE									_S("ServiceType")

// Columns for common to all service tables using IP/PPP

#define SERVICE_IF_NAME									_S("IfName")						// Interface name, e.g. "PPP" or "SLIP"
#define SERVICE_IF_PARAMS								_S("IfParams")						// Interface parameter string
#define SERVICE_IF_NETWORKS								_S("IfNetworks")					// Comma separated list of network protocols, e.g. "PPP"
#define SERVICE_IF_PROMPT_FOR_AUTH						_S("IfPromptForAuth")				// Prompt user for authentication name and password?
#define SERVICE_IF_AUTH_NAME							_S("IfAuthName")					// Authentication username used by PPP
#define SERVICE_IF_AUTH_PASS							_S("IfAuthPass")					// Authentication password used by PPP
#define SERVICE_IF_AUTH_RETRIES							_S("AuthRetries")					// No of times to retry authentication if it fails
#define SERVICE_IF_CALLBACK_ENABLED						_S("IfCallbackEnabled")				// Callback enabled?
#define SERVICE_IF_CALLBACK_TYPE						_S("IfCallbackType")				// Type of callback if enabled
#define SERVICE_IF_CALLBACK_INFO						_S("IfCallbackInfo")				// Info for callback request if enabled
#define SERVICE_CALLBACK_TIMEOUT						_S("CallbackTimeout")				// time to wait for callback
//				
#define SERVICE_IP_ADDR_FROM_SERVER						_S("IpAddrFromServer")				// Get IP address from server?
#define SERVICE_IP_ADDR									_S("IpAddr")						// IP Address of Interface
#define SERVICE_IP_NETMASK								_S("IpNetMask")						// IP Netmask of Interface
#define SERVICE_IP_GATEWAY								_S("IpGateway")						// IP Address of Gateway
#define SERVICE_IP_DNS_ADDR_FROM_SERVER					_S("IpDNSAddrFromServer")			// Get DNS addresses from server?
#define SERVICE_IP_NAME_SERVER1							_S("IpNameServer1")					// IP Address of primary name server reachable through this interface
#define SERVICE_IP_NAME_SERVER2							_S("IpNameServer2")					// IP Address of secondary name server reachable through this interface
//
#define SERVICE_ENABLE_IP_HEADER_COMP	 				_S("EnableIPHeaderComp")			// Enable IP header compression
#define SERVICE_ENABLE_LCP_EXTENSIONS					_S("EnableLCPExtension")			// Enable LCP extension
#define SERVICE_DISABLE_PLAIN_TEXT_AUTH					_S("DisablePlainTextAuth")			// Disable plain text authentication
#define SERVICE_ENABLE_SW_COMP							_S("EnableSWComp")					// Enable S/W compression

// Columns for ISP tables

#define ISP_DESCRIPTION									_S("Description")					// text field for app to use to describe ISP
#define ISP_TYPE										_S("Type")							// int field for ISP "type" e.g. Internet, LAN, etc
//
#define ISP_DEFAULT_TEL_NUM								_S("DefaultTelNum")					// The default telephone number to be used if the location does not match those below
#define ISP_DIAL_RESOLUTION								_S("DialResolution")				// Perform Dialing Resolution for default phone number?
#define ISP_USE_LOGIN_SCRIPT							_S("UseLoginScript")				// Use login script?
#define ISP_LOGIN_SCRIPT								_S("LoginScript")					// Login Script
#define ISP_PROMPT_FOR_LOGIN							_S("PromptForLogin")				// Prompt user for username and password?
#define ISP_LOGIN_NAME									_S("LoginName")						// Login name
#define ISP_LOGIN_PASS									_S("LoginPass")						// Login password
#define ISP_DISPLAY_PCT									_S("DisplayPCT")					// Display PCT (do not scan script for READ)?
//				
#define ISP_IF_NAME										SERVICE_IF_NAME
#define ISP_IF_PARAMS									SERVICE_IF_PARAMS
#define ISP_IF_NETWORKS									SERVICE_IF_NETWORKS
#define ISP_IF_PROMPT_FOR_AUTH							SERVICE_IF_PROMPT_FOR_AUTH
#define ISP_IF_AUTH_NAME								SERVICE_IF_AUTH_NAME
#define ISP_IF_AUTH_PASS								SERVICE_IF_AUTH_PASS
#define ISP_IF_AUTH_RETRIES								SERVICE_IF_AUTH_RETRIES
#define ISP_IF_CALLBACK_ENABLED							SERVICE_IF_CALLBACK_ENABLED
#define ISP_IF_CALLBACK_TYPE							SERVICE_IF_CALLBACK_TYPE
#define ISP_IF_CALLBACK_INFO							SERVICE_IF_CALLBACK_INFO
#define ISP_CALLBACK_TIMEOUT							SERVICE_CALLBACK_TIMEOUT
//				
#define ISP_IP_ADDR_FROM_SERVER							SERVICE_IP_ADDR_FROM_SERVER
#define ISP_IP_ADDR										SERVICE_IP_ADDR
#define ISP_IP_NETMASK									SERVICE_IP_NETMASK
#define ISP_IP_GATEWAY									SERVICE_IP_GATEWAY
#define ISP_IP_DNS_ADDR_FROM_SERVER						SERVICE_IP_DNS_ADDR_FROM_SERVER
#define ISP_IP_NAME_SERVER1								SERVICE_IP_NAME_SERVER1
#define ISP_IP_NAME_SERVER2								SERVICE_IP_NAME_SERVER2
//
#define ISP_ENABLE_IP_HEADER_COMP		 				SERVICE_ENABLE_IP_HEADER_COMP
#define ISP_ENABLE_LCP_EXTENSIONS						SERVICE_ENABLE_LCP_EXTENSIONS
#define ISP_DISABLE_PLAIN_TEXT_AUTH						SERVICE_DISABLE_PLAIN_TEXT_AUTH
#define ISP_ENABLE_SW_COMP								SERVICE_ENABLE_SW_COMP
//
#define ISP_BEARER_NAME									_S("BearerName")					// Bearer Name (for GSM)
#define ISP_BEARER_SPEED								_S("BearerSpeed")					// Bearer Speed (for GSM)
#define ISP_BEARER_CE									_S("BearerCE")						// Bearer CE (for GSM)
#define ISP_INIT_STRING									_S("InitString")					// Init string specific to ISP, to be written into the MODEM_ISP_INIT_STRING by NetDial
//
#define ISP_BEARER_TYPE									_S("BearerType")					// HSCSD or CSD?
#define ISP_CHANNEL_CODING								_S("ChannelCoding")					// Channel coding if HSCSD connection
#define ISP_AIUR										_S("AIUR")							// AIUR is HSCSD connection
#define ISP_REQUESTED_TIME_SLOTS						_S("RequestedTimeSlots")			// Requested time slots if HSCSD connection
#define ISP_MAXIMUM_TIME_SLOTS							_S("MaximumTimeSlots")				// Maximum time slots if HSCSD connection
//
#define ISP_AUTHENTICATION								_S("Authentication")				// Authentication table/group

// Columns for GPRS table

#define GPRS_APN										_S("APN")
//
#define GPRS_PDP_TYPE									_S("PDPType")
#define GPRS_PDP_ADDRESS								_S("PDPAddress")				// Phone IP address
//
#define GPRS_REQ_PRECEDENCE								_S("ReqPrecedence")
#define GPRS_REQ_DELAY									_S("ReqDelay")
#define GPRS_REQ_RELIABILITY							_S("ReqReliability")
#define GPRS_REQ_PEAK_THROUGHPUT						_S("ReqPeakThroughput")
#define GPRS_REQ_MEAN_THROUGHPUT						_S("ReqMeanThroughput")
//
#define GPRS_MIN_PRECEDENCE								_S("MinPrecedence")
#define GPRS_MIN_DELAY									_S("MinDelay")
#define GPRS_MIN_RELIABILITY							_S("MinReliability")
#define GPRS_MIN_PEAK_THROUGHPUT						_S("MinPeakThroughput")
#define GPRS_MIN_MEAN_THROUGHPUT						_S("MinMeanThroughput")
//
#define GPRS_DATA_COMPRESSION							_S("DataCompression")
#define GPRS_HEADER_COMPRESSION							_S("HeaderCompression")
//
#define GPRS_ANONYMOUS_ACCESS							_S("AnonymousAccess")
//
#define GPRS_IF_NAME									SERVICE_IF_NAME				
#define GPRS_IF_PARAMS									SERVICE_IF_PARAMS			
#define GPRS_IF_NETWORKS								SERVICE_IF_NETWORKS			
#define GPRS_IF_PROMPT_FOR_AUTH							SERVICE_IF_PROMPT_FOR_AUTH	
#define GPRS_IF_AUTH_NAME								SERVICE_IF_AUTH_NAME		
#define GPRS_IF_AUTH_PASS								SERVICE_IF_AUTH_PASS		
#define GPRS_IF_AUTH_RETRIES							SERVICE_IF_AUTH_RETRIES
//
#define GPRS_IP_NETMASK									SERVICE_IP_NETMASK				
#define GPRS_IP_GATEWAY									SERVICE_IP_GATEWAY				
#define GPRS_IP_ADDR_FROM_SERVER						SERVICE_IP_ADDR_FROM_SERVER
#define GPRS_IP_ADDR									SERVICE_IP_ADDR						// EPOC IP address
#define GPRS_IP_DNS_ADDR_FROM_SERVER					SERVICE_IP_DNS_ADDR_FROM_SERVER	
#define GPRS_IP_NAME_SERVER1							SERVICE_IP_NAME_SERVER1			
#define GPRS_IP_NAME_SERVER2							SERVICE_IP_NAME_SERVER2			
//
#define GPRS_ENABLE_LCP_EXTENSIONS						SERVICE_ENABLE_LCP_EXTENSIONS
#define GPRS_DISABLE_PLAIN_TEXT_AUTH					SERVICE_DISABLE_PLAIN_TEXT_AUTH
//
#define	GPRS_AP_TYPE									_S("GprsAccessPointType")

// Columns for modem table
				
#define MODEM_PORT_NAME									_S("PortName")
#define MODEM_TSY_NAME									_S("TSYName")
#define MODEM_CSY_NAME									_S("CSYName")
#define	MODEM_DATA_BITS									_S("DataBits")						// Data Bits to use for ISP or Modem
#define	MODEM_STOP_BITS									_S("StopBits")						// Stop Bits to use for ISP or Modem
#define	MODEM_PARITY									_S("Parity")						// Parity Type to use for ISP or Modem
#define MODEM_RATE										_S("Rate")
#define MODEM_HANDSHAKING								_S("Handshaking")
#define MODEM_SPECIAL_RATE								_S("SpecialRate")
#define MODEM_XON_CHAR									_S("XonChar")
#define MODEM_XOFF_CHAR									_S("XoffChar")
//
#define MODEM_FAX_CLASS_PREF							_S("FaxClassPref")
#define MODEM_SPEAKER_PREF								_S("SpeakerPref")
#define MODEM_SPEAKER_VOL_PREF							_S("SpeakerVolPref")
//
#define MODEM_MODEM_INIT_STRING							_S("ModemInitString")
#define MODEM_DATA_INIT_STRING							_S("DataInitString")
#define MODEM_FAX_INIT_STRING							_S("FaxInitString")
#define MODEM_ISP_INIT_STRING							_S("IspInitString")				// To be written by NetDial from ISP_INIT_STRING.  Should not be accessed by user.
//
#define MODEM_DIAL_PAUSE_LENGTH							_S("DialPauseLength")
#define MODEM_CARRIER_TIMEOUT							_S("CarrierTimeout")
#define MODEM_AUTO_ANSWER_RING_COUNT					_S("AutoAnswerRingCount")
#define MODEM_SPEAKER_VOL_CONTROL_LOW					_S("SpeakerVolContorlLow")
#define MODEM_SPEAKER_VOL_CONTROL_MEDIUM				_S("SpeakerVolControlMedium")
#define MODEM_SPEAKER_VOL_CONTROL_HIGH					_S("SpeakerVolControlHigh")
#define MODEM_SPEAKER_ALWAYS_OFF						_S("SpeakerAlwaysOff")
#define MODEM_SPEAKER_ON_UNTIL_CARRIER					_S("SpeakerOnUntilCarrier")
#define MODEM_SPEAKER_ALWAYS_ON							_S("SpeakerAlwaysOn")
#define MODEM_SPEAKER_ON_AFTER_DIAL_UNTIL_CARRIER		_S("SpeakerOnAfterUntilCarrier")
#define MODEM_DIAL_TONE_WAIT_MODIFIER					_S("DialToneWaitModifier")
#define MODEM_CALL_PROGRESS_1							_S("CallProgress1")					// Dialtone & busy detection disabled, result codes 0-5,10
#define MODEM_CALL_PROGRESS_2							_S("CallProgress2")					// Dialtone detection enabled & busy detection disabled, result codes 0-6,10
#define MODEM_CALL_PROGRESS_3							_S("CallProgress3")					// Dialtone detection disabled , but busy detection enabled, result codes 0-5,7,10
#define MODEM_CALL_PROGRESS_4							_S("CallProgress4")					// Dialtone detection & busy detection enabled, result codes 0-7,10
#define MODEM_ECHO_OFF									_S("EchoOff")
#define MODEM_VERBOSE_TEXT								_S("VerboseText")
#define MODEM_QUIET_ON									_S("QuietOn")
#define MODEM_QUIET_OFF									_S("QuietOff")
#define MODEM_DIAL_COMMAND_STATE_MODIFIER				_S("DialCommandStateModifier")
#define MODEM_ON_LINE									_S("OnLine")
#define MODEM_RESET_CONFIGURATION						_S("ResetConfiguration")
#define MODEM_RETURN_TO_FACTORY_DEFS					_S("ReturnToFactoryDefs")
#define MODEM_DCD_ON_DURING_LINK						_S("DCDOnDuringLink")
#define MODEM_DTR_HANG_UP								_S("DTRHangUp")
#define MODEM_DSR_ALWAYS_ON								_S("DSRAlwaysOn")
#define MODEM_RTS_CTS_HANDSHAKE							_S("RTSCTSHandshake")
#define MODEM_XON_XOFF_HANDSHAKE						_S("XonXoffHandshake")
#define MODEM_ESCAPE_CHARACTER							_S("EscapeCharacter")
#define MODEM_ESCAPE_GUARD_PERIOD						_S("EscapeGuardPeriod")
#define MODEM_FAX_CLASS_INTERROGATE						_S("FaxClassInterrogate")
#define MODEM_FAX_CLASS									_S("FaxClass")
//
#define MODEM_NO_DIAL_TONE								_S("NoDialTone")
#define MODEM_BUSY										_S("Busy")
#define MODEM_NO_ANSWER									_S("NoAnswer")
#define MODEM_CARRIER									_S("Carrier")
#define MODEM_CONNECT									_S("Connect")
#define MODEM_COMPRESSION_CLASS_5						_S("CompressionClass5")
#define MODEM_COMPRESSION_V42BIS						_S("CompressionV42bis")
#define MODEM_COMPRESSION_NONE							_S("CompressionNone")
#define MODEM_PROTOCOL_LAPD								_S("ProtocolLAPD")
#define MODEM_PROTOCOL_ALT								_S("ProtocolALT")
#define MODEM_PROTOCOL_ALTCELLULAR						_S("ProtocolALTCELLULAR")
#define MODEM_PROTOCOL_NONE								_S("ProtocolNone")
//
#define MODEM_MESSAGE_CENTRE_NUMBER						_S("MessageCentreNumber")
#define MODEM_MESSAGE_VALIDITY_PERIOD					_S("MessageValidityPeriod")
#define MODEM_MESSAGE_DELIVERY_REPORT					_S("MessageDeliveryReport")

// Columns for location table

#define LOCATION_INTL_PREFIX_CODE						_S("IntlPrefixCode")
#define LOCATION_NAT_PREFIX_CODE						_S("NatPrefixCode")
#define LOCATION_NAT_CODE								_S("NatCode")
#define LOCATION_AREA_CODE								_S("AreaCode")
#define LOCATION_DIAL_OUT_CODE							_S("DialOutCode")
#define LOCATION_DISABLE_CALL_WAITING_CODE				_S("DisableCallWaitingCode")
#define LOCATION_MOBILE									_S("Mobile")
#define LOCATION_USE_PULSE_DIAL							_S("UsePulseDial")
#define LOCATION_WAIT_FOR_DIAL_TONE						_S("WaitForDialTone")
#define LOCATION_PAUSE_AFTER_DIAL_OUT					_S("PauseAfterDialout")

//	Columns for chargecard table

#define CHARGECARD_ACCOUNT_NUMBER						_S("AccountNumber")
#define CHARGECARD_PIN									_S("Pin")
#define CHARGECARD_LOCAL_RULE							_S("LocalRule")
#define CHARGECARD_NAT_RULE								_S("NatRule")
#define CHARGECARD_INTL_RULE							_S("IntlRule")

// Columns for proxies table

#define PROXY_ISP										_S("ISP")							// ISP with which these proxies are associated
#define PROXY_SERVICE_TYPE								_S("ProxyServiceType")
#define PROXY_USE_PROXY_SERVER							_S("UseProxyServer")				
#define PROXY_SERVER_NAME								_S("ProxyServerName")				// Name of the proxy server
#define PROXY_PROTOCOL_NAME								_S("ProtocolName")
#define PROXY_PORT_NUMBER								_S("PortNumber")
#define PROXY_EXCEPTIONS								_S("Exceptions")

// Columns for WAP Access Point Table

#define WAP_CURRENT_BEARER								_S("CurrentBearer")
#define WAP_START_PAGE									_S("StartPage")

// Columns for WAP IP Bearer Table (and SMS Bearer Table)

#define WAP_ACCESS_POINT_ID								_S("AccessPointId")
#define WAP_GATEWAY_ADDRESS								_S("GatewayAddress")
#define WAP_IAP											_S("IAP")								//
#define WAP_ISP											_S("ISP")								// (for ISP type database) or use IAP (for IAP type database).	- will be deprecated in 7.0
#define WAP_CHARGECARD									_S("Chargecard")						//
#define WAP_ISP_TYPE									_S("ISPType")							// Dial in or dial out type	- will be deprecated in 7.0
#define WAP_WSP_OPTION									_S("WSPOption")							// Connectionless or Connection-oriented
#define WAP_SECURITY									_S("Security")

// Columns for WAP SMS Bearer Table

#define WAP_SERVICE_CENTRE_ADDRESS						_S("ServiceCentreAddresss")

// Columns for Bluetooth tables  

#define BT_DEV_ADD				_S("DeviceAddress")
#define BT_DEV_DFLT_NAME		_S("DeviceDefaultName")
#define BT_DEV_FRIENDLY_NAME	_S("DeviceFriendlyName")
#define BT_DEVICE_CLASS			_S("DeviceClass")
#define BT_LINKKEY_SIZE			_S("DeviceLinkKeySize")
#define BT_LINKKEY				_S("DeviceLinkKey")
#define BT_DEV_STATE			_S("DeviceStatus")
#define BT_DEVICE_GLOBAL_SECURITY _S("DeviceGlobalSecurity")
//
#define BT_DFLT_SER_NAME		_S("DefaultServicename")
#define BT_DFLT_SER_UUID		_S("DefaultServiceUID")
#define BT_DFLT_DEV_ADD			_S("DefaultDeviceAddress")
#define BT_SEC_UID				_S("BTSecurityUID")
#define BT_SEC_DEVICE_SECURITY	_S("BTSecurityDevice")
#define BT_DFLT_VIRTUAL_PORT    _S("DefaultVirtualPort")
#define BT_DFLT_SECURITY_LEVEL  _S("DefaultSecurityLevel")


// Columns for Default GPRS table

#define DEFAULT_GPRS_USAGE								_S("Usage")
#define DEFAULT_GPRS_APN								_S("APN")
//
#define DEFAULT_GPRS_PDP_TYPE							_S("PDPType")
#define DEFAULT_GPRS_PDP_ADDRESS						_S("PDPAddress")
//
#define DEFAULT_GPRS_PRECEDENCE							_S("Precedence")
#define DEFAULT_GPRS_DELAY								_S("Delay")
#define DEFAULT_GPRS_RELIABILITY						_S("Reliability")
#define DEFAULT_GPRS_PEAK_THROUGHPUT					_S("PeakThroughut")
#define DEFAULT_GPRS_MEAN_THROUGHPUT					_S("MeanThroughput")
//
#define DEFAULT_GPRS_MIN_PRECEDENCE						_S("MinPrecedence")
#define DEFAULT_GPRS_MIN_DELAY							_S("MinDelay")
#define DEFAULT_GPRS_MIN_RELIABILITY					_S("MinReliability")
#define DEFAULT_GPRS_MIN_PEAK_THROUGHPUT				_S("MinPeakThroughput")
#define DEFAULT_GPRS_MIN_MEAN_THROUGHPUT				_S("MinMeanThroughput")
//
#define DEFAULT_GPRS_DATA_COMPRESSION					_S("DataCompression")
#define DEFAULT_GPRS_HEADER_COMPRESSION					_S("HeaderCompression")
//
#define DEFAULT_GPRS_ANONYMOUS_ACCESS					_S("AnonymousAccess")

// Columns for Access Type table

#define TABLE_ACC_NAME			_S("TableName")
#define TABLE_ACC_TYPE			_S("AccessType")

// Enum for MODEM_SPEAKER_PREF field

enum TCommsDbModemSpeakerSetting
	{
	EModemSpeakerSettingNever=0,
	EModemSpeakerSettingUntilCallAnswered,
	EModemSpeakerSettingAlways,
	EModemSpeakerSettingAfterDialUntilAnswer
	};

// Enum for MODEM_SPEAKER_VOL_PREF field

enum TCommsDbModemSpeakerVolume
	{
	EModemSpeakerVolumeQuiet=0,
	EModemSpeakerVolumeMedium,
	EModemSpeakerVolumeLoud
	};

// Enum for ISP_TYPE field

enum TCommsDbIspType
	{
	EIspTypeInternetOnly,
	EIspTypeWAPOnly,
	EIspTypeInternetAndWAP
	};	

// Enum for ISP_BEARER_TYPE field

enum TCommsDbBearerType
	{
	EBearerTypeCSD,
	EBearerTypeHSCSD
	};

// Enum for WAP_ISP_TYPE field

enum TCommsDbWapIspType
	{
	EWapIspTypeDialOut,
	EWapIspTypeDialIn,
	EWapIspTypeOutgoingGPRS,
	EWapIspTypeIncomingGPRS
	};

// Enum for WAP_WSP_OPTION field

enum TCommsDbWapWspOption
	{
	EWapWspOptionConnectionless,
	EWapWspOptionConnectionOriented
	};

// Enum for DATABASE_TYPE field
// Will be deprecated in 7.0

enum TCommDbDatabaseType
	{
	EDatabaseTypeUnspecified =0,		// not specifying which type it is - any type of database can be opened with this parameter
	EDatabaseTypeIAP,
	EDatabaseTypeISP
	};

// Enum for CONNECT_PREF_DIRECTION field

enum TCommDbConnectionDirection
	{
	ECommDbConnectionDirectionUnknown =0,
	ECommDbConnectionDirectionOutgoing,
	ECommDbConnectionDirectionIncoming
	};

// Enum for CONNECT_PREF_BEARER_SET field

enum TCommDbBearer
	{
	ECommDbBearerUnknown = 0x0,
	ECommDbBearerCSD = 0x1,
	ECommDbBearerGPRS = 0x2
	};

// Enum for CONNECT_PREF_DIALOG_PREF field

enum TCommDbDialogPref
	{
	ECommDbDialogPrefUnknown =0,
	ECommDbDialogPrefPrompt,
	ECommDbDialogPrefWarn,
	ECommDbDialogPrefDoNotPrompt
	};

// Enum for GPRS_CLASS_C_BEARER field

enum TCommDbGprsClassCBearer
	{
	ECommDbGprsClassCBearerGprs,
	ECommDbGprsClassCBearerGsm
	};

enum TCommDbDeviceType
	{
	ECommDbUnknownDeviceType =0,
	ECommDbOneBoxDeviceType,
	ECommDbTwoBoxDeviceType
	};

//Enum to indicate how the commdb was created
enum TCommDbOpeningMethod
	{
	ECommDbCreated = 0,
	ECommDbCopiedDefault,
	ECommDbOpened
	};

//Protection of settings: protected tables and records are read-only
enum TAccessType
	{
	EProtected = 0,
	EUnprotected
	};

// UIDs for system agent event notification

const TUid KUidCommDbSMSBearerChange = {0x10008F04};
const TUid KUidCommDbGPRSAttachModeChange = {0x100092BC};
const TUid KUidCommDbGPRSDefaultParamsChange = {0x10008F05};
const TUid KUidCommDbModemTsyNameChange = {0x1000947f};

const TUid KUidCommDbModemRecordChange =  {0x1000A43D} ;
const TUid KUidCommDbProxiesRecordChange = {0x1000A43E};

#endif
