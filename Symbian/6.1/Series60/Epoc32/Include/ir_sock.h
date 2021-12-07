// IR_SOCK.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IR_SOCK_H__
#define __IR_SOCK_H__

#include "es_sock.h"

//################## EXPORTED CONSTANTS ########################

const TUint KIrdaAddrFamily=0x100;   // Address of Irda prot family
const TUint KIrmux=88;               // Protocol number for Irmux
const TUint KIrTinyTP=89;            // Protocol number for IrTinyTP

const TUint8 KIrPnPMask=0x01;	   /* PnP support - FIRST SERVICE HINT BYTE */
const TUint8 KPalmtopMask=0x02;    /* PDA/Palmtop - FIRST SERVICE HINT BYTE */
const TUint8 KComputerMask=0x04;   /* Computer - FIRST SERVICE HINT BYTE */
const TUint8 KPrinterMask=0x08;	   /* Printer - FIRST SERVICE HINT BYTE */
const TUint8 KModemMask=0x10;      /* IrModem - FIRST SERVICE HINT BYTE */
const TUint8 KFaxMask=0x20;        /* Fax - FIRST SERVICE HINT BYTE */
const TUint8 KLANAccessMask=0x40;  /* LAN Access - FIRST SERVICE HINT BYTE */
const TUint8 KExtensionMask=0x80;  /* Extension bit - FIRST SERVICE HINT BYTE */
const TUint8 KTelephonyMask=0x01;  /* Telephony - SECOND SERVICE HINT BYTE */
const TUint8 KFileServerMask=0x02; /* File Server - SECOND SERVICE HINT BYTE */
const TUint8 KIrCommMask=0x04;     /* IrCOMM support - SECOND SERVICE HINT BYTE */
const TUint8 KIrObexMask=0x20;     /* IrObex support - SECOND SERVICE HINT BYTE */

// IrDA Ioctls 
const TUint KDiscoveryIndicationIoctl=0;
const TUint KExclusiveModeIoctl=1;
const TUint KMultiplexModeIoctl=2;
const TUint KIrmuxStatusRequestIoctl=3;
const TUint KIrlapStatusRequestIoctl=4;
const TUint KIdleRequestIoctl=5;
const TUint KIdleClearRequestIoctl=6;
const TUint KDisconnectIndicationIoctl=7;
const TUint KIrlapStatusIndicationIoctl=8;
const TUint KIrmuxStatusIndicationIoctl=9;
const TUint KIrlapResetRequestIoctl=10;
const TUint KIrlapResetIndicationIoctl=11;
const TUint KIrlapDisconnectRequestIoctl=12;

const TUint KExclusiveMode=0;
const TUint KMultiplexMode=1;

//********************  Irda Set/GetOpts ******************************
// These two are done on Socket Write
const TUint KUnexpeditedDataOpt		= 0;		// Default
const TUint KExpeditedDataOpt		= 1;		// Urgent data transfer
// On KLevelIrlap
const TUint KDiscoverySlotsOpt		= 2;
const TUint KUserBaudOpt			= 3;
const TUint KHostMaxDataSizeOpt		= 4;
const TUint KRemoteMaxDataSizeOpt	= 6;	// Remote packet size
const TUint KHostMaxTATimeOpt		= 5;
const TUint KIrlapDisableResetOpt	= 9;	// This disables Irlap level reset_check/wait states.
const TUint KLocalBusyDetectedOpt	= 10;	// Client can set local busy in Irlap
const TUint KLocalBusyClearedOpt	= 11;	// Client can clear local busy in Irlap
const TUint KDiscoveryResponseDisableOpt = 12;
const TUint KFirstHintByteOpt		= 13;	// Hint Bytes
const TUint KSecondHintByteOpt		= 14;

// On KLevelIrmux
const TUint KTinyTPLocalSegSizeOpt=7;	// This value is advertised to the remote machine as the max amount of data we can reassemble
const TUint KTinyTPRemoteSegSizeOpt=8;	// Remote machine is unable to reassemble more data than this
const TUint KTinyTPDiasbledSegmentation=15; //Disbales TintTP reassembly of segmented packets
   
const TUint KLevelIrlap=4;
const TUint KLevelIrmux=5;

const TUint KIASClassNameMax=60;
const TUint KIASAttributeNameMax=60;
const TUint KMaxQueryStringLength=128;

//################# CLASS DEFINITIONS ########################

class TIrdaSockAddr : public TSockAddr
	{
struct SIrdaAddr
	{	
	TUint iHostDevAddr;
	TUint iRemoteDevAddr;
	TBool iSniff;
	TBool iSolicited;
	TUint8 iIrlapVersion;
	TUint8 iFirstServiceHintByte;
	TUint8 iSecondServiceHintByte;
	TUint8 iCharacterSet;
	TUint8 iServiceHintByteCount;
	// Extra stuff for MUX
	TUint8 iHomePort;
	TUint8 iRemotePort;
	TUint8 iSpare;
    };
public:
	IMPORT_C TIrdaSockAddr();
	IMPORT_C TIrdaSockAddr(const TSockAddr &aAddr);
	inline static TIrdaSockAddr &Cast(const TSockAddr &aAddr);
	inline static TIrdaSockAddr &Cast(const TSockAddr *aAddr);
	inline TUint GetRemoteDevAddr() const;
	inline void SetRemoteDevAddr(const TUint aRemote);
	inline TUint GetHostDevAddr() const;
	inline void SetHostDevAddr(const TUint aHost);
	inline TBool GetSniffStatus() const;
	inline void SetSniffStatus(const TBool aSniff);
	inline TBool GetSolicitedStatus() const;
	inline void SetSolicitedStatus(const TBool aSolicited);
	inline TUint8 GetIrlapVersion() const;
	inline void SetIrlapVersion(const TUint8 aIrlapVersion);
	inline TUint8 GetCharacterSet() const;
	inline void SetCharacterSet(const TUint8 aCharacterSet);
	inline TUint8 GetFirstServiceHintByte() const;
	inline void SetFirstServiceHintByte(const TUint8 aFirstServiceHintByte);
	inline TUint8 GetSecondServiceHintByte() const;
	inline void SetSecondServiceHintByte(const TUint8 aSecondServiceHintByte);
	inline TUint8 GetServiceHintByteCount() const;
	inline void SetServiceHintByteCount(const TUint8 aServiceHintByteCount);
	inline TUint8 GetHomePort() const;
	inline void SetHomePort(const TUint8 aHomePort);
	inline TUint8 GetRemotePort() const;
	inline void SetRemotePort(const TUint8 aRemotePort);
private:
	inline SIrdaAddr *addrPtr() const
		{return (SIrdaAddr *)UserPtr();}
	};

enum TIASDataType {EIASDataMissing=0,EIASDataInteger=1,EIASDataOctetSequence=2,EIASDataUserString=3};
enum TIASCharSet
	{ 
	EIASCharSetUserStringASCII =0x00,
	EIASCharSetUserStringISO_8859_1=0x01,
	EIASCharSetUserStringISO_8859_2=0x02,
	EIASCharSetUserStringISO_8859_3=0x03,
	EIASCharSetUserStringISO_8859_4=0x04,
	EIASCharSetUserStringISO_8859_5=0x05,
	EIASCharSetUserStringISO_8859_6=0x06,
	EIASCharSetUserStringISO_8859_7=0x07,
	EIASCharSetUserStringISO_8859_8=0x08,
	EIASCharSetUserStringISO_8859_9=0x09,
	EIASCharSetUserStringUnicode=0xFF,
	};

class TIASQuery : public TBuf8<KMaxQueryStringLength>
	{
public:
	IMPORT_C TIASQuery(const TDesC8& aClass,const TDesC8& aAttribute,TUint aRemoteDevAddr);
	IMPORT_C TIASQuery();
	IMPORT_C void Set(const TDesC8& aClass,const TDesC8& aAttribute,TUint aRemoteDevAddr);
	IMPORT_C void Get(TDes8& aClass,TDes8& aAttribute,TUint& aRemoteDevAddr);
private:
	};

class TIASResponse : public TBuf8<KMaxQueryStringLength>
	{
public:		// But not exported :-)
	void SetToInteger(TUint anInteger);
	void SetToCharString(const TDesC8& aCharString);
	void SetToOctetSeq(const TDesC8& aData);
#ifdef _UNICODE
	void SetToCharString(const TDesC16& aWideString);
#endif

public:
	IMPORT_C TIASResponse();
	inline TBool IsList() const;
	inline TInt NumItems() const;
	inline TIASDataType Type() const;
	IMPORT_C TInt GetInteger(TInt &aResult,TInt anIndex=0) const;
	IMPORT_C TInt GetOctetSeq(TDes8 &aResult,TInt anIndex=0) const;
	IMPORT_C TInt GetCharString(TDes8 &aResult,TInt anIndex=0) const;
	IMPORT_C const TPtrC8 GetCharString8(TInt anIndex=0) const;
	IMPORT_C TInt GetCharString(TDes16 &aResult,TInt anIndex=0) const;
	IMPORT_C const TPtrC16 GetCharString16(TInt anIndex=0) const;

private:
	inline TInt IsValidType();
	};

class TIASDatabaseEntryV001
	{
public:
	IMPORT_C TIASDatabaseEntryV001();
	TBuf8<KIASClassNameMax> iClassName;
	TBuf8<KIASAttributeNameMax> iAttributeName;
	TIASResponse iData;
	};
	
class TIASDatabaseEntry : public TPckgBuf<TIASDatabaseEntryV001>
	{
public:
	IMPORT_C void SetClassName(const TDesC8& aClassName);
	IMPORT_C void SetAttributeName(const TDesC8& anAttributeName);
	IMPORT_C void SetToInteger(const TUint anInteger);
	IMPORT_C void SetToCharString(const TDesC8& aCharString);
	IMPORT_C void SetToOctetSeq(const TDesC8& aData);

#ifdef _UNICODE	//need to be able to enter wide entries in unicode builds
	IMPORT_C void SetToCharString(const TDesC16& aWideString);//new export
#endif
	};

#include "IR_SOCK.INL"

#endif // __IR_SOCK_H__
