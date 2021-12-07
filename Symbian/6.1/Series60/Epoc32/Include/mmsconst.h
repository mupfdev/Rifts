/*
* ============================================================================
*  Name     : MmsConst.h
*  Part of  : MmsEngine
*
*  Description:
*     Miscellaneous constants needed by MmsEngine and MmsUi
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

#ifndef MMSCONST_H
#define MMSCONST_H

//  INCLUDES
#include <msvuids.h>
#include <msvstd.hrh>
#include <e32std.h>

// variant specific flags
#include <bldvariant.hrh>

#ifdef __SERIES60_
#ifndef __Series60_
#define __Series60_
#endif
#endif

#define MTM_DATAFILE _L("c:\\system\\mtm\\MMSMTM.dat")
#define MTM_NAME _L("MMSMTM")
#define MTM_REGISTRY _L("c:\\system\\mtm\\MTM Registry")

// Temporary name, used only in test programs
#define MTM_READABLE_NAME _L("MmsClientSideComponent")

// Periods for waiting information from WAP GW
// These default values are used if shared data client is not available
#define KMmsWapConnectTimer 300*1000000     // 300 sec = 5 min
#define KMmsWapDisconnectTimer 300*1000000     // 300 sec = 5 min
#define KMmsWapTransactionTimer 1800*1000000 // 1800 sec = 30 min 
#define KMmsGprsSuspendTimer 900*1000000 // 900 sec = 15 min 

// Default value for how much data we are able to receive
#define KMmsWapMaxReceiveSize 300*1024  // 300 kbytes

// Default value for how much data we are able to send
#define KMmsWapMaxSendSize 300*1024 // 300 kbytes


// CONSTANTS

// This is the resource file that contains factory values
// for error actions (for scheduled sending and receiving)
// For systems where the MMS engine is not installed at the
// factory, the resource cannot reside on z: drive.
_LIT(KMmsResourceFile, "z:\\System\\Data\\MMSSERVER.RSC");
// In cases MMS is a plug-in, the resource might be elsewhere
//_LIT(KMmsResourceFile, "\\System\\Data\\MMSSERVER.RSC");

#define KNOTIFICATIONFOLDER
// Invisible local folder that contains MMS notifications
_LIT(KMMSNotificationFolder, "MMSNotifications");

// This is the extra amount of disk space that will be taken
// up by the index entry when creating new message entries.
// This is a crude estimate. It is defined here as a constant
// to allow it to be made more accurate by changing the value
// in only one place.
const TInt KMmsIndexEntryExtra = 80;

// This is the safety margin for fetching MMS messages.
// There should be at least this much extra disk space
// before a message can be fetched. A new message takes
// more disk space than the amount indicated in the 
// notification.
const TInt KMmsDiskSafetyMargin = 25000;

// dll uids
const TUid KUidMmsServerMtm={0x100058DB};
const TUid KUidMmsClientMtm={0x100058DC};
// uimtm and uidata mtm are in the same file
const TUid KUidMmsClientUIMtm={0x100058DD};
const TUid KUidMmsClientUIDataMtm={0x100058DD};
const TUid KUidMMsUtilityDll={0x100058E0};
// editor and viewer
const TInt KUidMsgMmsEditor={0x100058DE};
// Kidsgrove stuff uses viewer id
const TInt KUidMsgMmsViewer={0x100058DF};

// Documents folder
// In manual mode notifications can be moved to
// documents folder.
// This is defined in \mce\inc\mceids.h
const TUid KMceDocumentsEntryId={0x00001008};

// message types
const TUid KUidMsgTypeMultimedia={0x100058E1};
const TUid KUidMsvTechnologyGroupMMS={0x100058E2};
const TUid KUidMsgMMSNotification={0x100059C8};

// message stream uids
const TUid KUidMmsHeaderStream={0x01000030};
const TUid KUidMmsMimeHeaderStream={0x01000031};
const TUid KUidMmsAttachmentInfoStream={0x01000032};
// recipient scheduling info
const TUid KUidMmsRecipientStream={0x01000033};
const TUid KUidBinaryNotificationStream={0x01000034};

// Log entry event type uid
// Used unless Symbian allocates us an id
const TUid KLogMmsEventTypeUid = {0x1000595e};

// Currently only connection oriented unsecure port is supported
const TUint16 KSupportedWAPPort = 9201;

// maximum alias length
const TInt KMmsAliasLength = 128;

// Message types stored in iMtmData1
const TUint32 KMmsMessageTypeMask = 0x0000000F;
const TUint32 KMmsMessageMSendReq = 0x00000001;
const TUint32 KMmsMessageMSendConf = 0x00000002;
const TUint32 KMmsMessageMNotificationInd = 0x00000003;
const TUint32 KMmsMessageMNotifyRespInd = 0x00000004;
const TUint32 KMmsMessageMRetrieveConf = 0x00000005;
const TUint32 KMmsMessageAcknowledgeInd = 0x00000006;
const TUint32 KMmsMessageDeliveryInd = 0x00000007;
// this must be the last one to allow some expansion for known types
const TUint32 KMmsMessageUnrecognized = 0x0000000F;

// Message state stored in iMtmData1 (see TMmsMsvEntry class)
const TUint32 KMmsMessageEncrypted =        0x00000010;
const TUint32 KMmsMessageSigned =           0x00000020;
const TUint32 KMmsMessageForwarded =        0x00000040;
const TUint32 KMmsMessageMobileTerminated = 0x00000080;
const TUint32 KMmsMessageEditorOriented =   0x00000100;

// Message type flags (not in TMmsMsvEntry)
// 1 byte reserved (0x0000F000)
// If no flag is set, message is personal (default)
const TUint32 KMmsMessageAdvertisement =   0x00001000;
const TUint32 KMmsMessageInformational =   0x00002000;

// Message notification stuff stored in iMtmData2
// response already sent to MMSC?
const TUint32 KMmsNotifyResponseSent = 0x00000001;
// undecoded (binary) notification
const TUint32 KMmsNotificationBinary = 0x00000002;

// Unicode BOM
const TUint16 KMmsByteOrderMark = 0xFEFF;
const TUint16 KMmsReversedByteOrderMark = 0xFFFE;

// Maximum iDescription read from text/plain file in terms of characters. 
const TInt KMmsMaxDescription = 128;

// WSP assigned numbers
const TInt8 KUidMmsWSPMultiPartMixed = 0x23;
const TInt8 KUidMmsWSPMultiPartRelated = 0x33;

// MMS specific field assignments
// same values used for enum values in internal storage
const TUint8 KMmsMessageClassPersonal = 128;
const TUint8 KMmsMessageClassAdvertisement = 129;
const TUint8 KMmsMessageClassInformational = 130;
const TUint8 KMmsMessageClassAuto = 131;

const TUint8 KMmsMessageTypeMSendReq = 128;
const TUint8 KMmsMessageTypeMSendConf = 129;
const TUint8 KMmsMessageTypeMNotificationInd = 130;
const TUint8 KMmsMessageTypeMNotifyRespInd = 131;
const TUint8 KMmsMessageTypeMRetrieveConf = 132;
const TUint8 KMmsMessageTypeAcknowledgeInd = 133;
const TUint8 KMmsMessageTypeDeliveryInd = 134;

const TUint8 KMmsPriorityLow = 128;
const TUint8 KMmsPriorityNormal = 129;
const TUint8 KMmsPriorityHigh = 130;

const TUint8 KMmsYes = 128;
const TUint8 KMmsNo = 129;

const TUint8 KMmsSenderHide = 128;
const TUint8 KMmsSenderShow = 129;

const TUint8 KMmsMessageStatusExpired = 128;
const TUint8 KMmsMessageStatusRetrieved = 129;
const TUint8 KMmsMessageStatusRejected = 130;
const TUint8 KMmsMessageStatusDeferred = 131;
const TUint8 KMmsMessageStatusUnrecognized = 132;

// All content type strings are in KContentTypeTable
// some are defined here to be used separately
_LIT8( KMmsAny, "*/*" );
_LIT8( KMmsTextPlain, "text/plain" );
_LIT8( KMmsApplicationSmil, "application/smil" );

// Assigned numbers for content types
// If new assignments are needed, check numbers from KContentTypeTable
const TUint8 KMmsAssignedAny = 0x00;
const TUint8 KMmsAssignedText = 0x01;
const TUint8 KMmsAssignedTextPlain = 0x03;
const TUint8 KMmsAssignedApplicationVndWapMultipart = 0x22;
const TUint8 KMmsAssignedApplicationVndWapMultipartMixed = 0x23;
const TUint8 KMmsAssignedApplicationVndWapMultipartAlternative = 0x26;
const TUint8 KMmsAssignedApplicationXml = 0x27;
const TUint8 KMmsAssignedApplicationVndWapWbxml = 0x29;
const TUint8 KMmsAssignedApplicationVndWapMultipartRelated = 0x33;

// Assigned numbers for WSP/HTTP status codes
// Informative 1xx
const TUint8 KMmsAssignedContinue = 0x10;
const TUint8 KMmsAssignedSwitchingProtocols = 0x11;
// Successful 2xx
const TUint8 KMmsAssignedOk = 0x20;
const TUint8 KMmsAssignedCreated = 0x21;
const TUint8 KMmsAssignedAccepted = 0x22;
const TUint8 KMmsAssignedNonAuthoritativeInformation = 0x23;
const TUint8 KMmsAssignedNoContent = 0x24;
const TUint8 KMmsAssignedResetContent = 0x25;
const TUint8 KMmsAssignedPartialContent = 0x26;
// MultipleChoices 3xx
const TUint8 KMmsAssignedMultipleChoices = 0x30;
const TUint8 KMmsAssignedMovedPermanently = 0x31;
const TUint8 KMmsAssignedMovedTemporarily = 0x32;
const TUint8 KMmsAssignedSeeOther = 0x33;
const TUint8 KMmsAssignedNotModified = 0x34;
const TUint8 KMmsAssignedUseProxy = 0x35;
// Client error 4xx
const TUint8 KMmsAssignedBadRequest = 0x40;
const TUint8 KMmsAssignedUnauthorized = 0x41;
const TUint8 KMmsAssignedPaymentRequired = 0x42;
const TUint8 KMmsAssignedForbidden = 0x43;
const TUint8 KMmsAssignedNotFound = 0x44;
const TUint8 KMmsAssignedMethodNotAllowed = 0x45;
const TUint8 KMmsAssignedNotAcceptable = 0x46;
const TUint8 KMmsAssignedProxyAuthenticationRequired = 0x47;
const TUint8 KMmsAssignedRequestTimeout = 0x48;
const TUint8 KMmsAssignedConflict = 0x49;
const TUint8 KMmsAssignedGone = 0x4A;
const TUint8 KMmsAssignedLengthRequired = 0x4B;
const TUint8 KMmsAssignedPreconditionFailed = 0x4C;
const TUint8 KMmsAssignedRequestEntityTooLarge = 0x4D;
const TUint8 KMmsAssignedRequestUriTooLarge = 0x4E;
const TUint8 KMmsAssignedUnsupportedMediaType = 0x4F;
// Server error 6xx
const TUint8 KMmsAssignedInternalServerError = 0x60;
const TUint8 KMmsAssignedNotImplemented = 0x61;
const TUint8 KMmsAssignedBadGateway = 0x62;
const TUint8 KMmsAssignedServiceUnavailable = 0x63;
const TUint8 KMmsAssignedGatewayTimeout = 0x64;
const TUint8 KMmsAssignedHttpVersionNotSupported = 0x65;


const TUint8 KMmsUnAssigned = 0x37;

const TInt KNumberContentTypes = KMmsUnAssigned;
// The following is a gapless table where the corresponding
// assigned numbers must run from 0 to KMmsUnAssigned - 1.
// If new content types are added to the table, and the assigned
// numbers are not contiguous dummy entries must be inserted, but
// if these would become too numerous, a two-table system must be
// constructed.
// At the moment one table is enough, as all well-known content types
// have contiguous assigned numbers. 
static const TText8* const KContentTypeTable[] = 
    {
    _S8( "*/*" ),                                       //0x00
    _S8( "text/*" ),                                    //0x01
    _S8( "text/html" ),                                 //0x02
    _S8( "text/plain" ),                                //0x03
    _S8( "text/x-hdml" ),                               //0x04
    _S8( "text/x-ttml" ),                               //0x05
    _S8( "text/x-vCalendar" ),                          //0x06
    _S8( "text/x-vCard" ),                              //0x07
    _S8( "text/vnd.wap.wml" ),                          //0x08
    _S8( "text/vnd.wap.wmlscript" ),                    //0x09
    _S8( "text/vnd.wap.channel" ),                      //0x0A
    _S8( "Multipart/*" ),                               //0x0B
    _S8( "Multipart/mixed" ),                           //0x0C
    _S8( "Multipart/form-data" ),                       //0x0D
    _S8( "Multipart/byteranges" ),                      //0x0E
    _S8( "multipart/alternative" ),                     //0x0F
    _S8( "application/*" ),                             //0x10
    _S8( "application/java-vm" ),                       //0x11    
    _S8( "application/x-www-form-urlencoded" ),         //0x12
    _S8( "application/x-hdmlc" ),                       //0x13
    _S8( "application/vnd.wap.wmlc" ),                  //0x14
    _S8( "application/vnd.wap.vmlscriptc" ),            //0x15
    _S8( "application/vnd.wap.channelc" ),              //0x16
    _S8( "application/vnd.wap.uaprof" ),                //0x17
    _S8( "application/vnd.wap.wtls-ca-certificate" ),   //0x18
    _S8( "application/vnd.wap.wtls-user-certificate" ), //0x19
    _S8( "application/x-x509-ca-cert" ),                //0x1A
    _S8( "application/x-x509-user-cert" ),              //0x1B
    _S8( "image/*" ),                                   //0x1C
    _S8( "image/gif" ),                                 //0x1D
    _S8( "image/jpeg"),                                 //0x1E
    _S8( "image/tiff" ),                                //0x1F
    _S8( "image/png" ),                                 //0x20
    _S8( "image/vnd.wap.wbmp" ),                        //0x21
    _S8( "application/vnd.wap.multipart.*" ),           //0x22
    _S8( "application/vnd.wap.multipart.mixed" ),       //0x23
    _S8( "application/vnd.wap.multipart.form-data" ),   //0x24
    _S8( "application/vnd.wap.multipart.byteranges" ),  //0x25
    _S8( "application/vnd.wap.multipart.alternative" ), //0x26
    _S8( "application/xml" ),                           //0x27
    _S8( "text/xml" ),                                  //0x28
    _S8( "application/vnd.wap.wbxml" ),                 //0x29
    _S8( "application/x-x968-cross-cert" ),             //0x2A
    _S8( "application/x-x968-ca-cert" ),                //0x2B
    _S8( "application/x-x968-user-cert" ),              //0x2C
    _S8( "text/vnd.wap.si" ),                           //0x2D
    _S8( "application/vnd.wap.sic" ),                   //0x2E
    _S8( "text/vnd.wap.sl" ),                           //0x2F
    _S8( "text/vnd.wap.slc" ),                          //0x30
    _S8( "text/vnd.wap.co" ),                           //0x31
    _S8( "application/vnd.wap.coc" ),                   //0x32
    _S8( "application/vnd.wap.multipart.related" ),     //0x33
    _S8( "application/vnd.wap.sia" ),                   //0x34
    _S8( "text/vnd.wap.connectivity-xml" ),             //0x35
    _S8( "application/vnd.wap.connectivity-wbxml" ),    //0x36
    // This must always be the last one.
    // This is the type that all unassigned numbers get:
    // Even if we have an actual assigned number for
    // application/octet-stream some day, there must be
    // this duplicate entry at the end of the table to
    // handle mapping of unknown assigned numbers
    _S8( "application/octet-stream" )                   //KMmsUnAssigned
    };

// IANA / WSP numbers for character sets
const TUint8 KMmsUtf8 = 0x6A;
const TUint8 KMmsUsAscii = 0x03;
const TUint KMmsIso10646Ucs2 = 0x03E8; // 1000
const TUint KMmsUTF16 = 0x03F7; // 1015
const TUint KMmsUTF16BE = 0x03F5; // 1013
const TUint KMmsUTF16LE = 0x03F6; // 1014

// CR/LF definitions for removal...
_LIT ( KLf16, "\x00A" ); // 16 bit line feed
_LIT ( KCr16, "\x00D" ); // 16 bit carriage return
_LIT ( KSpace16, " " ); // 16 bit space
_LIT8 ( KLf8, "\x00A" ); // 8 bit line feed
_LIT8 ( KCr8, "\x00D" ); // 8 bit carriage return
_LIT8 ( KSpace8, " " ); // 8 bit space

// Validity limits for values that are not enums.
// If different products need different validity
// limits, differences are controlled by conditional
// compilation

// max expiry: 168 hours (one week) expressed in seconds
const TInt KMmsMaxExpiry = 168 * 3600;

#ifdef __Series60_
//160*120, default
const TInt KMmsImageMinWidth = 160;
const TInt KMmsImageMinHeight = 120;
//640*480
const TInt KMmsImageMaxWidth = 640;
const TInt KMmsImageMaxHeight = 480;
# else
// anything goes
const TInt KMmsImageMinWidth = 0;
const TInt KMmsImageMinHeight = 0;
const TInt KMmsImageMaxWidth = KMaxTInt32;
const TInt KMmsImageMaxHeight = KMaxTInt32;
#endif

// MACROS

// DATA TYPES

// Possible address types
enum TMmsAddressType
    {
    EMmsAddressTypeUnknown = 0,
    EMmsAddressTypeMobile,
    EMmsAddressTypeEmail, 
    EMmsAddressTypeIpv4,
    EMmsAddressTypeIpv6
    };

// These panics should only be used in ASSERT_DEBUGs
// (The user should not see these)
enum TMmsPanic // MMS error codes
    {
    EMmsBadMtmTypeUid = KErrNone+1,
    EMmsNoCMsvEntrySet,
    EMmsEntryTypeNotSupported,
    EMmsHeadersNotFound,
    EMmsAlreadyBusy,
    EMmsUnknownState,
    EMmsActiveInFinalProgress,
    EMmsFinalProgressFailed 
    };
 

// Values for recipient types 
enum TMmsRecipients
    {
    EMmsTo = 1, 
    EMmsCc,
    EMmsBcc
    };

// Values for message class 
enum TMmsMessageClass
    {
    EMmsMimimumMessageClass = KMmsMessageClassPersonal,
    EMmsClassPersonal = KMmsMessageClassPersonal, 
    EMmsClassAdvertisement = KMmsMessageClassAdvertisement,
    EMmsClassInformational = KMmsMessageClassInformational,
    EMmsClassAuto = KMmsMessageClassAuto,
    // change following if new message classes are added
    EMmsMaximumMessageClass = KMmsMessageClassAuto
    };

// Values for message priority
enum TMmsMessagePriority
    {
    EMmsMinimumPriority = KMmsPriorityLow,
    EMmsPriorityLow = KMmsPriorityLow, 
    EMmsPriorityNormal = KMmsPriorityNormal,
    EMmsPriorityHigh = KMmsPriorityHigh,
    // change following if new priorities added
    EMmsMaximumPriority = KMmsPriorityHigh
    };

// Values for message Sender-Visibility
enum TMmsMessageSenderVisibility
    {
    EMmsSenderVisibilityDefault = 0,
    EMmsMinimumSenderVisibility = KMmsSenderHide, // always minimum
    EMmsSenderVisibilityHide = KMmsSenderHide, 
    EMmsSenderVisibilityShow = KMmsSenderShow,
    EMmsMaximumSenderVisibility = KMmsSenderShow // change if new values added
    };

// Values for message Delivery-Report
enum TMmsMessageDeliveryReport
    {
    EMmsDeliveryReportYes = KMmsYes, 
    EMmsDeliveryReportNo = KMmsNo
    };

// Values for Delivery-Report allowed
enum TMmsSettingsDeliveryReportAllowed
    {
    EMmsDeliveryReportAllowedYes = KMmsYes, 
    EMmsDeliveryReportAllowedNo = KMmsNo
    };

// Values for message Read-Reply
enum TMmsMessageReadReply
    {
    EMmsReadReplyYes = KMmsYes, 
    EMmsReadreplyNo = KMmsNo
    };

// Values for Read-Reply sending allowed
enum TMmsSettingsReadReplyAllowed
    {
    EMmsReadReplyAllowedYes = KMmsYes, 
    EMmsReadReplyAllowedNo = KMmsNo
    };

// Values for Message-Type field
// correspond to binary encoding!
enum TMmsMessageType
    {
    EMmsMSendReq = KMmsMessageTypeMSendReq,
    EMmsMSendConf = KMmsMessageTypeMSendConf,
    EMmsNotificationInd = KMmsMessageTypeMNotificationInd,
    EMmsNotifyRespInd = KMmsMessageTypeMNotifyRespInd,
    EMmsRetrieveConf = KMmsMessageTypeMRetrieveConf,
    EMmsAcknowledgeInd = KMmsMessageTypeAcknowledgeInd,
    EMmsDeliveryInd = KMmsMessageTypeDeliveryInd
    };

// Values for Status field
// correspond to binary encoding!
enum TMmsMessageStatus
    {
    EMmsStatusExpired = KMmsMessageStatusExpired,
    EMmsStatusRetrieved = KMmsMessageStatusRetrieved,
    EMmsStatusRejected = KMmsMessageStatusRejected,
    EMmsStatusDeferred = KMmsMessageStatusDeferred,
    EMmsStatusUnrecognized = KMmsMessageStatusUnrecognized
    };

// mms receiving mode
enum TMmsReceivingMode
    {
    // first mode is default, must be set to 0:
    // If mode is not specified, it must default to "always enabled"

    // These modes control if acknowledgements or fetch requests
    // are sent to MMSC when notifications about new messages arrive.

    EMmsMinimumReceivingMode = 0,
    EMmsReceivingAlwaysEnabled = EMmsMinimumReceivingMode,
    EMmsReceivingEnabledInHomeNetwork,
    EMmsReceivingDisabled,
    EMmsReceivingManual,
    // change following if new modes added
    EMmsMaximumReceivingMode = EMmsReceivingManual
    };

// message fetching state
enum TMmsSettingsFetchMode
    {
    // Modes that send acknowledgements to MMSC

    // Fetch everything that fits criteria, discard rest
    // (too big messages, advertisements etc.)
    // Fetching is tried until message expires.
    // Retry interval may be lengthened in some cases.
    EMmsMinimumFetchingMode = 1,
    EMmsFetchingOn = EMmsMinimumFetchingMode,

    // Send a reject response to everything
    EMmsFetchingOff,

    // Send a deferred response to everything until the
    // user switches fetching mode on again.
    // At that point fetch everything that has not expired
    EMmsFetchingDeferred,

    // change this is modes added
    EMmsMaximumFetchingMode = EMmsFetchingDeferred
    };

// Default speaker
enum TMmsSettingsDefaultSpeaker
    {
    EMmsMinimumDefaultSpeaker = 1,
    EMmsAudioSpeakerHandsfree = EMmsMinimumDefaultSpeaker,
    EMmsAudioSpeakerHandset = 2,
    // change following if new speakers added
    EMmsMaximumDefaultSpeaker = EMmsAudioSpeakerHandset
    };

// Factory settings
enum TMmsFactorySettingsLevel
    {
    EMmsFactorySettingsLevelNormal = 0x0,
    EMmsFactorySettingsLevelDeep 
    };

class TCommandParameters
    {
    public:
        inline TCommandParameters();
        // The delay to wait before operation is started.
        // if 0, delay is determined by hard-coded default value
        // (a small delay, for example 10 seconds, exact value must
        // be determined when hardware timing is better known)
        // This parameter is intended to be used to initiate
        // retry operation after a delay (for example 10 minutes)
        TTimeIntervalSeconds iInitialDelay;
        // only schedule entries that have failed because of following error
        // if iError == KErrNone, everything is rescheduled
        TInt iError; 
    };

typedef TPckgBuf<TCommandParameters> TCommandParametersBuf;

TCommandParameters::TCommandParameters():
iInitialDelay( 0 ),
iError( 0 )
    {
    }

#endif      // MMSCONST_H
            
// End of File
