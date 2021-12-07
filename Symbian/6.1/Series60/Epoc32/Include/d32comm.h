// D32COMM.H
//
// Copyright (c) 1995-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __D32COMM_H__
#define __D32COMM_H__
#include <e32std.h>
#include <e32ver.h>

enum TDataBits {EData5,EData6,EData7,EData8};
enum TStopBits {EStop1,EStop2};
enum TParity {EParityNone,EParityEven,EParityOdd,EParityMark,EParitySpace};
enum TBps
	{
	EBps50,EBps75,EBps110,EBps134,EBps150,EBps300,EBps600,EBps1200,
	EBps1800,EBps2000,EBps2400,EBps3600,EBps4800,EBps7200,EBps9600,
	EBps19200,EBps38400,EBps57600,EBps115200,EBps230400,EBps460800,
	EBps576000,EBps1152000,EBps4000000,
	EBpsAutobaud=0x40000000,EBpsSpecial=0x80000000
	};

enum TFifo
	{
	EFifoEnable,EFifoDisable,
	};

enum TSir 
	{
	ESIREnable,ESIRDisable,
	};

enum TFlowControl
	{
	EFlowControlOn,EFlowControlOff
	};
//

const TInt KConfigMaxTerminators=4;
// DTE Constants
const TUint KConfigObeyXoff=0x01;
const TUint KConfigSendXoff=0x02;
const TUint KConfigObeyCTS=0x04;
const TUint KConfigFailCTS=0x08;
const TUint KConfigObeyDSR=0x10;
const TUint KConfigFailDSR=0x20;
const TUint KConfigObeyDCD=0x40;
const TUint KConfigFailDCD=0x80;
const TUint KConfigFreeRTS=0x100;
const TUint KConfigFreeDTR=0x200;
// DCE Constants
const TUint KConfigObeyDTR=0x400;
const TUint KConfigFailDTR=0x800;
const TUint KConfigObeyRTS=0x1000;
const TUint KConfigFailRTS=0x2000;
const TUint KConfigFreeDSR=0x4000;
const TUint KConfigFreeCTS=0x8000;
const TUint KConfigFreeDCD=0x10000;
const TUint KConfigFreeRI=0x20000;
const TUint KConfigWriteBufferedComplete=0x80000000;
//
const TUint KConfigParityErrorFail=0;
const TUint KConfigParityErrorIgnore=0x01;
const TUint KConfigParityErrorReplaceChar=0x02;
const TUint KConfigXonXoffDebug=0x80000000;
//
const TUint KSignalCTS=0x01;
const TUint KSignalDSR=0x02;
const TUint KSignalDCD=0x04;
const TUint KSignalRNG=0x08;
const TUint KSignalRTS=0x10; 
const TUint KSignalDTR=0x20;
const TUint KSignalBreak=0x40;

const TUint KSignalChanged=0x1000;
const TUint KCTSChanged=KSignalCTS*KSignalChanged;
const TUint KDSRChanged=KSignalDSR*KSignalChanged;
const TUint KDCDChanged=KSignalDCD*KSignalChanged;
const TUint KRNGChanged=KSignalRNG*KSignalChanged;
const TUint KRTSChanged=KSignalRTS*KSignalChanged;
const TUint KDTRChanged=KSignalDTR*KSignalChanged;
const TUint KBreakChanged=KSignalBreak*KSignalChanged;

const TUint KSignalDTEOutputs=KSignalRTS|KSignalDTR;
const TUint KSignalDTEInputs=KSignalCTS|KSignalDSR|KSignalDCD|KSignalRNG;
const TUint KSignalDCEInputs=KSignalDTEOutputs;
const TUint KSignalDCEOutputs=KSignalDTEInputs;

const TUint KConfigSIRPulseWidthMaximum=0x01;
const TUint KConfigSIRPulseWidthMinimum=0x02;
//
class TCommConfigV01
    {
public:
	TBps iRate;
	TDataBits iDataBits;
	TStopBits iStopBits;
	TParity iParity;
	TUint iHandshake;
	TUint iParityError;
	TUint iFifo;
	TInt iSpecialRate;
	TInt iTerminatorCount;
	TText8 iTerminator[KConfigMaxTerminators];
	TText8 iXonChar;
	TText8 iXoffChar;
	TText8 iParityErrorChar;
	TSir iSIREnable;
	TUint iSIRSettings;
	};
typedef TPckgBuf<TCommConfigV01> TCommConfig;
//
const TUint KCapsBps50=0x00000001;
const TUint KCapsBps75=0x00000002;
const TUint KCapsBps110=0x00000004;
const TUint KCapsBps134=0x00000008;
const TUint KCapsBps150=0x00000010;
const TUint KCapsBps300=0x00000020;
const TUint KCapsBps600=0x00000040;
const TUint KCapsBps1200=0x00000080;
const TUint KCapsBps1800=0x00000100;
const TUint KCapsBps2000=0x00000200;
const TUint KCapsBps2400=0x00000400;
const TUint KCapsBps3600=0x00000800;
const TUint KCapsBps4800=0x00001000;
const TUint KCapsBps7200=0x00002000;
const TUint KCapsBps9600=0x00004000;
const TUint KCapsBps19200=0x00008000;
const TUint KCapsBps38400=0x00010000;
const TUint KCapsBps57600=0x00020000;
const TUint KCapsBps115200=0x00040000;
const TUint KCapsBps230400=0x00080000;
const TUint KCapsBps1152000=0x00100000;
const TUint KCapsBps4000000=0x00200000;
const TUint KCapsBps460800=0x00400000;
const TUint KCapsBps576000=0x00800000;
const TUint KCapsBpsSpecial=0x80000000;
//
const TUint KCapsData5=0x01;
const TUint KCapsData6=0x02;
const TUint KCapsData7=0x04;
const TUint KCapsData8=0x08;
//
const TUint KCapsStop1=0x01;
const TUint KCapsStop2=0x02;
//
const TUint KCapsParityNone=0x01;
const TUint KCapsParityEven=0x02;
const TUint KCapsParityOdd=0x04;
const TUint KCapsParityMark=0x08;
const TUint KCapsParitySpace=0x10;
//
const TUint KCapsSignalCTSSupported=0x01;
const TUint KCapsSignalDSRSupported=0x02;
const TUint KCapsSignalDCDSupported=0x04;
const TUint KCapsSignalRNGSupported=0x08;
const TUint KCapsSignalRTSSupported=0x10;
const TUint KCapsSignalDTRSupported=0x20;
//
const TUint KCapsObeyXoffSupported=0x01;
const TUint KCapsSendXoffSupported=0x02;
const TUint KCapsObeyCTSSupported=0x04;
const TUint KCapsFailCTSSupported=0x08;
const TUint KCapsObeyDSRSupported=0x10;
const TUint KCapsFailDSRSupported=0x20;
const TUint KCapsObeyDCDSupported=0x40;
const TUint KCapsFailDCDSupported=0x80;
const TUint KCapsFreeRTSSupported=0x100;
const TUint KCapsFreeDTRSupported=0x200;
// DCE Constants
const TUint KCapsObeyRTSSupported=0x400;
const TUint KCapsObeyDTRSupported=0x800;
//
const TUint KCapsHasFifo=0x01;
//
const TUint KCapsSIR115kbps=0x01;
const TUint KCapsSIR2400bpsOnly=0x02;
const TUint KCapsSIR4Mbs=0x04;
//
const TUint KNotifySignalsChangeSupported=0x01;
const TUint KNotifyRateChangeSupported=0x02;
const TUint KNotifyDataFormatChangeSupported=0x04;
const TUint KNotifyHandshakeChangeSupported=0x08;
const TUint KNotifyBreakSupported=0x10;
const TUint KNotifyFlowControlChangeSupported=0x20;
const TUint KNotifyDataAvailableSupported=0x40;
const TUint KNotifyOutputEmptySupported=0x80;
//
const TUint KCapsRoleSwitchSupported=0x01;
//
const TUint KCapsFlowControlStatusSupported=0x01;
//
const TUint KRateChanged=0x01;
const TUint KDataFormatChanged=0x02;
const TUint KHandshakeChanged=0x04;
//
class TCommCapsV01
	{
public:
	TUint iRate;
	TUint iDataBits;
	TUint iStopBits;
	TUint iParity;
	TUint iHandshake;
	TUint iSignals;
	TUint iFifo;
	TUint iSIR;
	};
typedef TPckgBuf<TCommCapsV01> TCommCaps;

class TCommCapsV02 : public TCommCapsV01
	{
public:
	TUint iNotificationCaps;
	TUint iRoleCaps;
	TUint iFlowControlCaps;
	};
typedef TPckgBuf<TCommCapsV02> TCommCaps2;
//
class TCapsDevCommV01
	{
public:
	TVersion version;
	};

class TCommNotificationV01
	{
public:
	TUint iChangedMembers;
	TBps iRate;
	TDataBits iDataBits;
	TStopBits iStopBits;
	TParity iParity;
	TUint iHandshake;
	};
typedef TPckgBuf<TCommNotificationV01> TCommNotificationPckg;
//
const TUint KDataAvailableNotifyFlag=0x80000000;
//
#ifdef _DEBUG_DEVCOMM
class TCommDebugInfo
	{
public:
	TBool iRxBusy;
	TBool iRxHeld;
	TInt iRxLength;
	TInt iRxOffset;
	TInt iRxIntCount;
	TInt iRxErrCount;
	TInt iRxBufCount;
	TBool iTxBusy;
	TBool iTxHeld;
	TInt iTxLength;
	TInt iTxOffset;
	TInt iTxIntCount;
	TInt iTxErrCount;
	TInt iTxBufCount;
	TBool iDrainingRxBuf;
	TBool iFillingTxBuf;
	TBool iRunningDfc;
	TInt iDfcCount;
	TInt iDfcReqSeq;
	TInt iDfcHandlerSeq;
	TInt iDoDrainSeq;
	TBool iTxDfcPend;
	TBool iRxDfcPend;
	TInt iTxChars, iRxChars;
	TInt iTxXon, iTxXoff, iRxXon, iRxXoff;
	};
typedef TPckgBuf<TCommDebugInfo> TCommDebugInfoPckg;
#endif
//
class RBusDevComm : public RBusLogicalChannel
	{
public:
	enum TVer {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=KE32BuildVersionNumber};
	enum TRequest
		{
		ERequestRead=0x0,ERequestReadCancel=0x1,
		ERequestWrite=0x1,ERequestWriteCancel=0x2,
		ERequestBreak=0x2,ERequestBreakCancel=0x4,
		ERequestNotifySignalChange=0x3,ERequestNotifySignalChangeCancel=0x8,
		};
	enum TControl
		{
		EControlConfig,EControlSetConfig,EControlCaps,
		EControlSignals,EControlSetSignals,
		EControlQueryReceiveBuffer,EControlResetBuffers,
		EControlReceiveBufferLength,EControlSetReceiveBufferLength,
#ifdef _DEBUG_DEVCOMM
		EControlDebugInfo
#endif
		};
public:
	inline TInt Open(TInt aUnit);
	inline TVersion VersionRequired() const;
	inline void Read(TRequestStatus &aStatus,TDes8 &aDes);
	inline void Read(TRequestStatus &aStatus,TDes8 &aDes,TInt aLength);
	inline void ReadOneOrMore(TRequestStatus &aStatus,TDes8 &aDes);
	inline void ReadCancel();
	inline void Write(TRequestStatus &aStatus,const TDesC8 &aDes);
	inline void Write(TRequestStatus &aStatus,const TDesC8 &aDes,TInt aLength);
	inline void WriteCancel();
	inline void Break(TRequestStatus &aStatus,TInt aTime);
	inline void BreakCancel();
	inline void Config(TDes8 &aConfig);
	inline TInt SetConfig(const TDesC8 &aConfig);
	inline void Caps(TDes8 &aCaps);
	inline TUint Signals();
	inline void SetSignals(TUint aSetMask,TUint aClearMask);
	inline TInt QueryReceiveBuffer();
	inline void ResetBuffers();
	inline TInt ReceiveBufferLength();
	inline TInt SetReceiveBufferLength(TInt aLength);
	inline void NotifySignalChange(TRequestStatus& aStatus,TUint& aSignals,TUint aSignalMask=0x3F);
	inline void NotifySignalChangeCancel();
	inline void NotifyReceiveDataAvailable(TRequestStatus& aStatus);
	inline void NotifyReceiveDataAvailableCancel();
#ifdef _DEBUG_DEVCOMM
	inline void DebugInfo(TDes8 &aInfo);
#endif
	};

class RBusDevCommDCE : public RBusLogicalChannel
	{
public:
	enum TVer {EMajorVersionNumber=1,EMinorVersionNumber=0,EBuildVersionNumber=KE32BuildVersionNumber};
	enum TRequest
		{
		ERequestRead=0x0,ERequestReadCancel=0x1,
		ERequestWrite=0x1,ERequestWriteCancel=0x2,
		ERequestBreak=0x2,ERequestBreakCancel=0x4,
		ERequestNotifySignalChange=0x3,ERequestNotifySignalChangeCancel=0x8,
		ERequestNotifyFlowControlChange=0x4,ERequestNotifyFlowControlChangeCancel=0x10,
		ERequestNotifyConfigChange=0x5,ERequestNotifyConfigChangeCancel=0x20
		};
	enum TControl
		{
		EControlConfig,EControlSetConfig,EControlCaps,
		EControlSignals,EControlSetSignals,
		EControlQueryReceiveBuffer,EControlResetBuffers,
		EControlReceiveBufferLength,EControlSetReceiveBufferLength,
		EControlFlowControlStatus,
#ifdef _DEBUG_DEVCOMM
		EControlDebugInfo
#endif
		};
public:
	inline TInt Open(TInt aUnit);
	inline TVersion VersionRequired() const;
	inline void Read(TRequestStatus &aStatus,TDes8 &aDes);
	inline void Read(TRequestStatus &aStatus,TDes8 &aDes,TInt aLength);
	inline void ReadOneOrMore(TRequestStatus &aStatus,TDes8 &aDes);
	inline void ReadCancel();
	inline void Write(TRequestStatus &aStatus,const TDesC8 &aDes);
	inline void Write(TRequestStatus &aStatus,const TDesC8 &aDes,TInt aLength);
	inline void WriteCancel();
	inline void Break(TRequestStatus &aStatus,TInt aTime);
	inline void BreakCancel();
	inline void Config(TDes8 &aConfig);
	inline TInt SetConfig(const TDesC8 &aConfig);
	inline void Caps(TDes8 &aCaps);
	inline TUint Signals();
	inline void SetSignals(TUint aSetMask,TUint aClearMask);
	inline TInt QueryReceiveBuffer();
	inline void ResetBuffers();
	inline TInt ReceiveBufferLength();
	inline TInt SetReceiveBufferLength(TInt aLength);
	inline void NotifySignalChange(TRequestStatus& aStatus,TUint& aSignals,TUint aSignalMask=0x3F);
	inline void NotifySignalChangeCancel();
	inline void NotifyReceiveDataAvailable(TRequestStatus& aStatus);
	inline void NotifyReceiveDataAvailableCancel();
	inline void NotifyFlowControlChange(TRequestStatus& aStatus);
	inline void NotifyFlowControlChangeCancel();
	inline void GetFlowControlStatus(TFlowControl& aFlowControl);
	inline void NotifyConfigChange(TRequestStatus& aStatus, TDes8& aNewConfig);
	inline void NotifyConfigChangeCancel();
#ifdef _DEBUG_DEVCOMM
	inline void DebugInfo(TDes8 &aInfo);
#endif
	};

#include <d32comm.inl>
#endif
