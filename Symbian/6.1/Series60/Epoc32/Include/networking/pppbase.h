// PPPBASE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PPPBASE_H__)
#define __PPPBASE_H__

#include <nifvar.h>
#include <nifmbuf.h>
#include <nifutl.h>

#include <networking\pppdef.h>
#include <networking\pppsock.h>
#include <networking\pppcomp.h>

#include <ETelGprs.h> // don't link to ETelGPRS, just include for the data count structure
////////////////////////////////////////////////////////////////////////////////

_LIT(PPP_INI_FILE,"ppp.ini");

enum TPppPanic
	{
	EPppPanic_PPPHDLCIsAlreadyActive,
	EPppPanic_PPPDBReadCallback	// CSW
	};

void PppPanic(TPppPanic aPanic);

enum TPppFault
	{
	EPppPanic_PacketHeaderTooBig
	};

void PppFault(TPppFault aFault);

#if defined(_DEBUG)
#pragma warning( disable : 4710 )	// inline function not inlined
static inline void DBG_BREAK()	{ __DEBUGGER(); }
#else
#define	DBG_BREAK()	(void)0
#endif


////////////////////////////////////////////////////////////////////////////////
// PPP Internal LCP Constants
////////////////////////////////////////////////////////////////////////////////

const TInt KPppDefaultFrameSize = 1500;

enum TMSCBCPAction
	{
	EMSCBCPActionRequireClientSpecifiedNumber  = ECallbackActionMSCBCPRequireClientSpecifiedNumber,
	EMSCBCPActionAcceptServerSpecifiedNumber   = ECallbackActionMSCBCPAcceptServerSpecifiedNumber,
	EMSCBCPActionOverrideServerSpecifiedNumber = ECallbackActionMSCBCPOverrideServerSpecifiedNumber
	};

////////////////////////////////////////////////////////////////////////////////

class TPppFcs16;
class TPppFcs32;
class MPppRecvr;
class MPppFsm;
class CPppLcp;
class CPppLinkBase;
class CNifFactory;

////////////////////////////////////////////////////////////////////////////////
// Other simple PPP Frame Recveivers
////////////////////////////////////////////////////////////////////////////////

// Adds extra PPP Recv channels to a class T
template <class T>
class TPppExtraRecvr : public MPppRecvr
	{
public:
	TPppExtraRecvr<T>(T* aClass, void (T::*aRecvFn)(RMBufChain&), void (T::*aFlowFn)(), 
		CPppLcp* aLcp, TPppPhase aPhase, TUint aId, void (T::*aFrameErrFn)(), void (T::*aKillFn)())
		: MPppRecvr(aLcp, aPhase, aId), iClass(aClass), iRecvFn(aRecvFn), iFlowFn(aFlowFn), 
			iFrameErrFn(aFrameErrFn), iKillFn(aKillFn){}
		virtual void FrameError()
		{ (iClass->*iFrameErrFn)(); }
		virtual void KillProtocol()
		{ (iClass->*iKillFn)(); }

	virtual TBool RecvFrame(RMBufChain& aPacket)
		{ (iClass->*iRecvFn)(aPacket); return ETrue; };
	virtual void FlowOn()
		{ (iClass->*iFlowFn)(); }
private:
	T* iClass;
	void (T::*iRecvFn)(RMBufChain&);
	void (T::*iFlowFn)();
	void (T::*iFrameErrFn)();
	void (T::*iKillFn)();
	};

////////////////////////////////////////////////////////////////////////////////
// PPP Options
////////////////////////////////////////////////////////////////////////////////

class RPppOption : public RMBufChain
	{
public:
	RPppOption();
	RPppOption(RMBufChain& aChain);
	inline const RPppOption& operator=(const RMBufChain& aChain);
	void SetL(TUint8 aType, const TAny* aPtr, TInt aLen);
	TUint8 OptType() const;
	void SetType(const TUint8 aType);
	TInt ValueLength() const;
	void SetValueLength(TInt aLen);
	TUint8* ValuePtr();
	const TUint8* ValuePtr() const;
	inline static RPppOption& Cast(RMBufChain& aChain);
	inline static const RPppOption& Cast(const RMBufChain& aChain);
private:
	// These probably belong in the MBuf manager
	TInt MaxLength() const;
	TInt SetLength(TInt aLen);
	};

enum TPppOptResponse
	{
	EPppOptAck,
	EPppOptNak,
	EPppOptReject
	};

class MPppOptionsExtender;
class MPppOptionHandler
	{
	friend class MPppOptionsExtender;
protected:
	MPppOptionHandler();
	void OptRegister(MPppOptionsExtender* aExtender, const TUint8* aOptList, TInt aNumOpts);
	virtual void OptNegotiationStarted();
	virtual void OptNegotiationAborted();
	virtual void OptNegotiationComplete();
	virtual void OptFillinConfigRequestL(RPppOptionList& aRequestList);
	virtual TPppOptResponse OptCheckConfigRequest(RPppOption& aOption);
	virtual void OptApplyConfigRequest(RPppOption& aOption);
	virtual void OptRecvConfigAck(RPppOption& aOption);
	virtual void OptRecvConfigNak(RPppOption& aOption, RPppOptionList& aReqList);
	virtual void OptRecvConfigReject(RPppOption& aOption, RPppOptionList& aReqList);
protected:
	TInt iNumOptions;
	const TUint8* iOptionList;
private:
	TDblQueLink iOptHandlerLink;
	};

////////////////////////////////////////////////////////////////////////////////
// PPP Finite State Machine
////////////////////////////////////////////////////////////////////////////////

const TInt KPppFsmTerminateTimeout = 2500;
const TInt KPppFsmLengthenedTerminateTimeout = 30000;		// 30 secs
const TInt KPppFsmTerminateRetries = 10;
const TInt KPppFsmRequestTimeout = 3000;
const TInt KPppFsmRequestMaxTimeout = 60000;
const TInt KPppFsmLengthenedRequestTimeout = 40000;			// 40 secs
const TInt KPppFsmRequestRetries = 10;
const TInt KPppFsmTimerPriority = 10;

#define __DECLARE_FSM_NAME(t) __iFsmName=t

const TInt KPppFsmNonConvergeLimit = 4;
const TUint KPppRequestIdAnswered = 0x80000000;

////////////////////////////////////////////////////////////////////////////////
// PPP Link Protocols
////////////////////////////////////////////////////////////////////////////////

// 16 Bit FCS
const TUint16 KPppInitFcs16 = 0xffff;	// Initial FCS value
const TUint16 KPppGoodFcs16 = 0xf0b8;	// Good final FCS value 

class TPppFcs16
	{
public:
	inline TPppFcs16();
	inline void Init();
	void Calc(const TUint8* aPtr, const TUint8* aEnd);
	inline void Compliment();
	inline TUint16 Fcs();
	inline TBool IsGood();
private:
	TUint16 iFcs;		
	};

// 32 Bit FCS
const TUint32 KPppInitFcs32 = 0xffffffff;	// Initial FCS value
const TUint32 KPppGoodFcs32 = 0xdebb20e3;	// Good final FCS value 

class TPppFcs32
	{
public:
	inline TPppFcs32();
	inline void Init();
	void Calc(const TUint8* aPtr, const TUint8* aEnd);
	inline void Compliment();
	inline TUint32 Fcs();
	inline TBool IsGood();
private:
	TUint32 iFcs;		
	};

CPppLinkBase* PppCreateLinkL(CPppLcp* aLcp);

/*
// Support for PPP components as external DLLs
class CPppExtDllRef : public CAsyncOneShot
	{
public:
	CPppDllRef();
	~CPppDllRef();
	void UnloadMe();
protected:
	virtual void RunL();
private:
	RLibrary iDll;
	TDblQueLink iLink;
	};

class MPppExtDll
	{
public:
	IMPORT_C virtual ~MPppExtDll();
	virtual void DllInstallL()=0;
	virtual void DllRemove()=0;
private:
	friend class CPppExtDllRef;
	CPppExtDllRef* iPppDllRef;
	};
*/

////////////////////////////////////////////////////////////////////////////////
// Other simple PPP Frame Recveivers
////////////////////////////////////////////////////////////////////////////////

// Base class for link protocols
class CPppLinkBase : public CBase
	{
public:
	virtual ~CPppLinkBase();
	// Implemented by link protocols
	virtual TInt Send(RMBufChain& aPacket, TUint aPppId=KPppIdAsIs)=0;
	virtual void OpenL()=0; // Open/Close from LCP
	virtual void Close()=0;
	virtual void StartL()=0;
	virtual void Stop(TInt aReason, TBool aLinkDown=ETrue)=0;
	virtual void GetSendRecvSize(TInt& aMaxRecvSize, TInt& aMaxSendSize)=0;
	virtual void GetDataTransfer(RGprsContext::TDataVolume&)=0;
	inline TPppLinkMode LinkMode();
	virtual TInt SpeedMetric()=0;
	inline void NewCompressor(const CPppCompressor* aCompressor);
	inline void NewDeCompressor(const CPppDeCompressor* aDeCompressor);
protected:
	CPppLinkBase(CPppLcp* aLcp);
	// Used by link protocols
	inline void NotifyLinkUp();
	inline void NotifyLinkDown(TInt aReason);
	inline void DeliverToLcp(RMBufChain& aPacket);
protected:
	CPppLcp* iPppLcp;
	TPppLinkMode iLinkMode;
	CPppCompressor* iPppCompressor;
	CPppDeCompressor* iPppDecompressor;
	};

#include <networking\pppbase.inl>

#endif
