// bt_sock.h
//
// Copyright (c) 1999-2000 Symbian Ltd.  All rights reserved.
//

//
// BT socket interface types
//

#ifndef BT_SOCK_H
#define BT_SOCK_H

#include <es_sock.h>
#include <bttypes.h>
#include <d32comm.h>

//
// BT Protocol Family
//

const TUint KBTAddrFamily = 0x101;

const TUint KBTLinkManager = 0x0099;
const TUint KL2CAP = 0x0100;
const TUint KRFCOMM = 0x0003;
const TUint KSDP = 0x0001;

const TUint KTCIL2CAP = 0xF100;
//const TInt KTCIRFCOMM = 0xF003;
//const TInt KTCISDP = 0xF001;

const TInt KBTMajor = 0;
const TInt KBTMinor = 1;
const TInt KBTBuild = 1;

// Socket Options
const TUint	KSolBtBlog  =0x1000;
const TUint KSolBtHCI   =0x1010;
const TUint KSolBtLM    =0x1011;
const TUint KSolBtL2CAP =0x1012;
const TUint KSolBtRFCOMM=0x1013;

const static TUint8 KMinRfcommServerChannel = 1;
const static TUint8 KMaxRfcommServerChannel = 30;

class TBTSockAddr : public TSockAddr
	{
struct SBTAddr
	{		
	TBTDevAddr iAddress;
    };
public:
	IMPORT_C TBTSockAddr();
	IMPORT_C TBTSockAddr(const TSockAddr &aAddr);
	IMPORT_C TBTDevAddr BTAddr() const;
	IMPORT_C void SetBTAddr(const TBTDevAddr& aRemote);

protected:
	inline TAny *BTUserPtr() const;
private:
	inline SBTAddr& BTAddrStruct() const;
	inline TPtr8 AddressPtr() const;
	};

const static TInt KErrBtEskError = -6999;

//
// L2CAP
//

const static TInt KL2CAPErrBase = -6300;
const static TInt KErrBadAddress = KL2CAPErrBase;
const static TInt KErrSAPUnexpectedEvent = KL2CAPErrBase - 1;
const static TInt KErrBadPacketReceived = KL2CAPErrBase - 2;
const static TInt KErrL2CAPBadResponse = KL2CAPErrBase - 3;
const static TInt KErrHCIConnectFailed = KL2CAPErrBase - 4;
const static TInt KErrHCILinkDisconnection = KL2CAPErrBase - 5;
const static TInt KErrSAPNotConnected = KL2CAPErrBase - 6;
const static TInt KErrConfigBadParams = KL2CAPErrBase - 7;
const static TInt KErrConfigRejected = KL2CAPErrBase - 8;
const static TInt KErrConfigUnknownOptions = KL2CAPErrBase - 9;
const static TInt KErrL2PeerDisconnected = KL2CAPErrBase - 10;
const static TInt KErrL2CAPAccessRequestDenied = KL2CAPErrBase - 11;
const static TInt KErrL2CAPRequestTimeout = KL2CAPErrBase - 12;
const static TInt KErrL2PeerRejectedCommand = KL2CAPErrBase - 13;

const static TInt KErrHostResNameTooLong = KL2CAPErrBase - 14;

const static TInt KErrHostResNoMoreResults = KErrEof;  
const static TInt KErrL2HostResNoMoreResults = KErrEof;  ///< @deprecated 

const static TUint KInquiryNumResponsesOpt=1;
const static TUint KInquiryTimeOpt=2;

const static TUint KHostResInquiry = 1;
const static TUint KHostResName = 2;
const static TUint KHostResIgnoreCache = 16;

// L2CAP Ioctls

const static TInt KL2CAPEchoRequestIoctl	= 0;
const static TInt KL2CAPIncomingMTUIoctl	= 1;

// Link Manager stuff (used via L2CAP - that's why it's here)
enum TBTLMIoctls
	{
	KLMDisconnectACLIoctl,
	KLMSetPacketTypeIoctl,
    KLMWaitForSCONotificationIoctl
	};

struct TLMDisconnectACLIoctl
	{
	TBTDevAddr	iDevAddr;
	TUint8		iReason;
	};

typedef TPckgBuf<TLMPacketType> TLMPacketTypeBuf;

typedef TPckgBuf<TLMDisconnectACLIoctl> TLMDisconnectACLBuf;

// Enumeration for SCO link transaction type
enum TBTSCONotificationType
    {
    ESCOLinkUp,
    ESCOLinkDown
    };

// Structure for SCO link notification
struct TLMWaitForSCONotificationIoctl
    {
    TBTSCONotificationType  iSCONotificationType;   // SCO transaction type
    TBTDevAddr	            iDevAddr;               // Remote side BD Address
    THCIConnHandle          iSCOConnH;              // SCO connection handle
    };

// Package buffer for KLMWaitForSCONotificationIoctl
typedef TPckgBuf<TLMWaitForSCONotificationIoctl> TLMWaitForSCONotificationBuf;

enum TBTLMOptions
	{
	KLMGetACLLinkCount,
	KLMGetACLLinkArray
	};

static const TReal KBasebandSlotTime = 0.000625;		  // seconds
static const TUint KDefaultBasebandConnectionTimeout = 16; // seconds

// HCI stuff (used via L2CAP - that's why it's here)
const static TInt KHCIIoctlErrorBase = -6000;

static const TUint KHCIAddSCOConnIoctl			=0;
static const TUint KHCIRemoveSCOConnIoctl		=1;
static const TUint KHCIChangePacketTypeIoctl	=2;
static const TUint KHCIAuthRequestIoctl			=3;
static const TUint KHCIEncryptIoctl				=4;
static const TUint KHCIChangeLinkKeyIoctl		=5;
static const TUint KHCIMasterLinkKeyIoctl		=6;
static const TUint KHCIHoldModeIoctl			=7;
static const TUint KHCISniffModeIoctl			=8;
static const TUint KHCIExitSniffModeIoctl		=9;
static const TUint KHCIParkModeIoctl			=10;
static const TUint KHCIExitParkModeIoctl		=11;
static const TUint KHCIReadPageTimeoutIoctl		=12;
static const TUint KHCIWritePageTimeoutIoctl	=13;
static const TUint KHCIReadScanEnableIoctl		=14;
static const TUint KHCIWriteScanEnableIoctl		=15;
static const TUint KHCIReadDeviceClassIoctl		=16;
static const TUint KHCIWriteDeviceClassIoctl	=17;
static const TUint KHCIReadVoiceSettingIoctl	=18;
static const TUint KHCIWriteVoiceSettingIoctl	=19;
static const TUint KHCIReadHoldModeActivityIoctl=20;
static const TUint KHCIWriteHoldModeActivityIoctl=21;
static const TUint KHCILocalVersionIoctl		=22;
static const TUint KHCILocalFeaturesIoctl		=23;
static const TUint KHCICountryCodeIoctl			=24;
static const TUint KHCILocalAddressIoctl		=25;
static const TUint KHCIWriteDiscoverabilityIoctl=26;
static const TUint KHCIReadDiscoverabilityIoctl	=27;
static const TUint KHCIWriteVendorSpecificFrameIoctl=28; //writes a command to hci and completes on command complete event
static const TUint KHCIWriteVendorSpecificFrameNoEventExpectedIoctl=29;//writes a command to hci and completes immediately
static const TUint KHCIVendorSpecificRegistrationIoctl=30;//Shehla: registers a vendor specific sap
static const TUint KHCIVendorSpecificCancelRegistrationIoctl=31;//deregisters the vendor specific sap
static const TUint KHCIWaitForVendorSpecificDebugEventIoctl=32;//waits for a vendor debug event before completion

// Structs for ioctl parameters

enum THCIScanEnableIoctl 
    {
     EHCINoScansEnabled=0x00,          // 0x00
     EHCIInquiryScanOnly,              // 0x01
     EHCIPageScanOnly,                 // 0x02
     EHCIInquiryAndPageScan            // 0x03
    };
typedef TPckgBuf<THCIScanEnableIoctl> THCIScanEnableBuf;

struct THCIAddSCOConnectionIoctl
	{
	THCIConnHandle iConnH;
	TUint16        iPktType;
	};
typedef TPckgBuf<THCIAddSCOConnectionIoctl> THCIAddSCOConnectionBuf;

struct THCISetEncryptionIoctl
	{
//	THCIConnHandleBuf iConnH;
	TBool             iEncrypt;
	};
typedef TPckgBuf<THCISetEncryptionIoctl> THCISetEncryptionBuf;

struct THCIDeviceClassIoctl
	{
	TUint16    iMajorServiceClass;
	TUint8     iMajorDeviceClass;
	TUint8     iMinorDeviceClass;
	};
typedef TPckgBuf<THCIDeviceClassIoctl> THCIDeviceClassBuf;
	
struct THCILocalVersionIoctl
	{
	TUint8   iHCIVersion;
	TUint16  iHCIRevision;
	TUint8   iLMPVersion;
	TUint16  iLMPSubversion;
	TUint16  iManufacturerName;
	};
typedef TPckgBuf<THCILocalVersionIoctl> THCILocalVersionBuf;

enum TBTL2CAPOptions
	{
	KL2CAPGetOutboundMTU,
	KL2CAPGetDebug1,
	KL2CAPInboundMTU,
	KL2CAPRTXTimer,
	KL2CAPERTXTimer
	};

typedef TUint16 TL2CAPPort;

/**
L2CAP Socket Address.
Use this class to specify a local or remote L2CAP connection end-point,
that is Device Address and PSM/CID.
When unconnected, the Port() specifies the PSM, once connected it refers to
the CID.
**/
class TL2CAPSockAddr : public TBTSockAddr
	{
public:
	IMPORT_C TL2CAPSockAddr();
	IMPORT_C TL2CAPSockAddr(const TSockAddr &aAddr);
	inline static TL2CAPSockAddr& Cast(const TSockAddr &aAddr);
	//
	inline TL2CAPPort Port() const;
	inline void SetPort(const TL2CAPPort aHomePort);
	};

/**
	Socket address class used for inquiries.
	Used to specify the inquiry request, and then filled with information
	about remote devices discovered through the inquiry process.
	Use the BTAddr() method to extract the device address to connect to.
**/
class TInquirySockAddr : public TBTSockAddr
	{
struct SInquiryAddr
	{		
	TUint8 iFormatTypeField;
	TUint16 iMajorServiceClass;
	TUint8 iMajorDeviceClass;
	TUint8 iMinorDeviceClass;
	TUint  iIAC;
	TUint8 iFlags;
    };
public:
	IMPORT_C TInquirySockAddr();
	IMPORT_C TInquirySockAddr(const TSockAddr &aAddr);

	inline static TInquirySockAddr& Cast(const TSockAddr &aAddr);
	inline TUint16 MajorServiceClass() const;
	inline void SetMajorServiceClass(TUint16 aClass);
	inline TUint8 MajorClassOfDevice() const;
	inline void SetMajorClassOfDevice(TUint8 aMajorClassOfDevice);
	inline TUint8 MinorClassOfDevice() const;
	inline void SetMinorClassOfDevice(TUint8 aMinorClassOfDevice);
	inline TUint IAC() const;
	inline void SetIAC(const TUint aIAC);
	inline TUint8 Action() const;
	inline void SetAction(TUint8 aFlags);
private:
	inline SInquiryAddr &InquiryAddrStruct() const;
	};


//
// RFCOMM
//

const static TInt KRFErrorBase = -6350;
const static TInt KErrRfcommSAPUnexpectedEvent = KRFErrorBase;
const static TInt KErrRfcommAlreadyBound = KRFErrorBase-1;
const static TInt KErrRfcommBadAddress = KRFErrorBase-2;
const static TInt KErrRfcommMTUSize = KRFErrorBase-3;
const static TInt KErrRfcommFrameResponseTimeout = KRFErrorBase-4;
const static TInt KErrRfcommMuxRemoteDisconnect = KRFErrorBase-5;
const static TInt KErrRfcommNotBound = KRFErrorBase-6;
const static TInt KErrRfcommParameterNegotiationFailure = KRFErrorBase-7;
const static TInt KErrRfcommNotListening = KRFErrorBase-8;

//RFCOMMIoctls

const static TInt KRFCOMMModemStatusCmdIoctl =0;
const static TInt KRFCOMMRemoteLineStatusCmdIoctl = 1;
const static TInt KRFCOMMRemotePortNegCmdIoctl = 2;
const static TInt KRFCOMMRemotePortNegRequestIoctl = 3;

// RFCOMM Options

const static TInt KRFCOMMLocalPortParameter = 0;   // Supports Get and Set
const static TInt KRFCOMMGetAvailableServerChannel = 1;	// Only supports Get
const static TInt KRFCOMMMaximumSupportedMTU = 2; // Supports Get and Set
const static TInt KRFCOMMGetDebug1 = 3;   // Only supports Get
const static TInt KRFCOMMGetRemoteModemStatus = 4; // Only supports Get (is set when MSC received)
//TRY_CBFC
const static TInt KRFCOMMGetTransmitCredit = 5;
const static TInt KRFCOMMGetReceiveCredit = 6;
const static TInt KRFCOMMGetReUsedCount = 7;
const static TInt KRFCOMMFlowTypeCBFC = 8; // get and set CBFC

enum TRPNParameterMask
	{
	EPMBitRate		= 0x0001,
	EPMDataBits		= 0x0002,
	EPMStopBit		= 0x0004,
	EPMParity		= 0x0008,
	EPMParityType	= 0x0010,
	EPMXOnChar		= 0x0020,
	EPMXOffChar		= 0x0040,
	// RESERVED		= 0x0080
	EPMXOnOffInput	= 0x0100,
	EPMXOnOffOutput	= 0x0200,
	EPMRTRInput		= 0x0400,
	EPMRTROutput	= 0x0800,
	EPMRTCInput		= 0x1000,
	EPMRTCOutput	= 0x2000
	// RESERVED		= 0x4000
	// RESERVED		= 0x8000
	};

enum TRPNFlowCtrlMask
	{
	EFCXOnOffInput	=0x01,
	EFCXOnOffOutput =0x02,
	EFCRTRInput		=0x04,
	EFCRTROutput	=0x08,
	EFCRTCInput		=0x10,
	EFCRTCOutput	=0x20
	};

enum TRPNValidityMask
	{
	EVMBitRate	= 0x01,
	EVMDataBits	= 0x02,
	EVMStopBit	= 0x04,
	EVMParity	= 0x08,
	EVMFlowCtrl	= 0x10,
	EVMXOnChar	= 0x20,
	EVMXOffChar	= 0x40
	};

// structs for RFCOMM Ioctls

class TRfcommRPNTransaction;

class TRfcommRemotePortParams
	{
public:
	inline TRfcommRemotePortParams();
	inline TUint8	IsValid() const;
	inline TBool	GetBitRate(TBps& aBitRate) const;
	inline TInt		SetBitRate(TBps  aBitRate);
	inline TBool	GetDataBits(TDataBits& aDataBits) const;
	inline TInt     SetDataBits(TDataBits  aDataBits);
	inline TBool	GetStopBit(TStopBits& aStopBit) const;
	inline TInt		SetStopBit(TStopBits  aStopBit);
	inline TBool	GetParity(TParity& aParity) const;
	inline TInt		SetParity(TParity  aParity);
	inline TBool    GetFlowCtrl(TUint8& aFlowCtrl) const;
	inline TInt     SetFlowCtrl(TUint8  aFlowCtrl);
	inline TBool    GetXOnChar(TUint8& aXOnChar) const;
	inline TInt     SetXOnChar(TUint8  aXOnChar);
	inline TBool    GetXOffChar(TUint8& aXOffChar) const;
	inline TInt     SetXOffChar(TUint8  aXOffChar);
	IMPORT_C void	UpdateFlowCtrlBit(TUint8 aFlowCtrl, TRPNFlowCtrlMask aFCMask);
	IMPORT_C void	UpdateWholeFlowCtrl(TUint16 aParamMask, TUint8 aFlowCtrl);
	IMPORT_C void	UpdateFromRPNTransaction(const TRfcommRPNTransaction& 
											aRPNTransaction);	
private:	
	TBps iBitRate;
	TDataBits iDataBits;
	TStopBits iStopBit; //It's really only one bit - ignore what the type implies...
	TParity iParity;
	TUint8 iFlowCtrl;
	TUint8 iXOnChar;
	TUint8 iXOffChar;
	TUint8 iValidMask;
	};

// structs for RFCOMM Ioctls

class TRfcommRPNTransaction
	{
public: // Functions
	inline TRfcommRPNTransaction();
public: // Variables
	TRfcommRemotePortParams iPortParams;
	TUint16 iParamMask;
	};

typedef TUint8 TRfcommChannel;

/**
   Defines the format of an Rfcomm address.
   
   This class uses the TSockAddr data area to hold the address so that
   it can be passed through the ESOCK boundary.
   Assumes that the remote RFCOMM instance is always bound to PSM 3 on
   L2CAP, so there is no way of specifying another remote PSM.
   
**/
class TRfcommSockAddr : public TBTSockAddr
	{
public:
	IMPORT_C TRfcommSockAddr();
	IMPORT_C TRfcommSockAddr(const TSockAddr &aAddr);
	inline static TRfcommSockAddr& Cast(const TSockAddr& aAddr);
	};



#include <bt_sock.inl>

#endif
