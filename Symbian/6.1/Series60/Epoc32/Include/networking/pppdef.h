// PPPDEF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __PPPDEF_H__
#define __PPPDEF_H__

#include <nifutl.h>
#include <nifmbuf.h>
#include <networking\pppsock.h>

#if !defined INLINE
#if defined( _DEBUG )
#define	INLINE
#else
#define	INLINE	inline
#endif
#endif

class CPppLcp;
class CNifFactory;
class RPppOptionList;

////////////////////////////////////////////////////////////////////////////////
// PPP Interface to Link protocols - accepts frames from Lcp's demux
////////////////////////////////////////////////////////////////////////////////

class MPppRecvr
	{
public:
	MPppRecvr(CPppLcp* aPppLcp, TPppPhase aPhase, TUint aPppId=KPppIdUnknown);
	virtual ~MPppRecvr();
	//
	inline TInt SendFrame(RMBufChain& aPacket);
	inline void SetId(TUint aPppId);
	inline void SetPhase(TPppPhase aPhase);
	void Register(TUint aPpdId=KPppIdAsIs);
	void Reregister(TUint aPpdId, TPppPhase aPhase);
	void Deregister();
	void Deque();
   virtual TBool RecvFrame(RMBufChain& aPacket)=0;

	virtual void FrameError()=0;
	virtual void KillProtocol()=0;

	virtual void FlowOn();
	virtual void LowerLayerUp();
	virtual void LowerLayerDown(TInt aStatus);
protected:
	CNifFactory* FindPppFactoryL(const TDesC& aFilename, TUid aUid2, CObjectCon& aCon);
//	virtual void PhaseChanged(TPppPhase aOldPhase, TPppPhase aNewPhase, TInt aReason)=0;
protected:
	TUint iPppId;
	TPppPhase iActivePhase;
	CPppLcp* iPppLcp;
	TInt iPppAbortCode;
private:
	friend class CPppLcp;
	TDblQueLink iPppRecvrListLink;
	};

class RPppOption;
class TPppFcs32;
class MPppOptionHandler;

////////////////////////////////////////////////////////////////////////////////
// PPP Options
////////////////////////////////////////////////////////////////////////////////

class RPppOptionList : public RMBufPktQ
	{
public:
	void SetL(RMBufChain& aList, TInt aLength=0);
	TInt CopyL(RMBufChain& aPacket, TInt aHdrLen=0) const;
	TInt RemoveOption(RPppOption& aOption);
	TInt ReplaceOption(RPppOption& aOption);
	TInt RemoveOptions(RPppOptionList& aRejectList);
	TInt ReplaceOptions(RPppOptionList& aReplaceList);
	void CreatePacketL(RMBufPacket& aPacket, TUint aPppId, TUint8 aType, TUint8 aId);
	void CreateAndAddL(TUint8 aType);
	void CreateAndAddL(TUint8 aType, TUint8 aValue);
	void CreateAndAddL(TUint8 aType, TUint16 aValue);
	void CreateAndAddL(TUint8 aType, TUint32 aValue);
	void CreateAndAddL(TUint8 aType, const TUint8 * aBuf, TInt aLen );	// CSW
	void CreateAndAddL(TUint8 aType, TPtrC8& aValue);
	void Crc32(TPppFcs32& aFcs, TBool aInitFcs=ETrue);
	};

class MPppOptionsExtender
	{
public:
	MPppOptionsExtender();
	void ExtOptRegister(MPppOptionHandler* aHandler);
	void ExtOptDeregister(MPppOptionHandler* aHandler);
	void ExtOptNegotiationStarted();
	void ExtOptNegotiationAborted();
	void ExtOptNegotiationComplete();
	void ExtOptFillinConfigRequestL(RPppOptionList& aRequestList);
	void ExtOptCheckConfigRequest(RPppOption& aOption, RPppOptionList &aAckList, RPppOptionList &aNakList, RPppOptionList &aRejList);
	void ExtOptApplyConfigRequest(RPppOption& aOption);
	void ExtOptRecvConfigAck(RPppOption& aOption);
	void ExtOptRecvConfigNak(RPppOption& aOption, RPppOptionList& aReqList);
	void ExtOptRecvConfigReject(RPppOption& aOption, RPppOptionList& aReqList);
	MPppOptionHandler* ExtOptLookup(TUint8 aOptId);
private:
	TDblQue<MPppOptionHandler> iExtOptHandlerList;
	};

////////////////////////////////////////////////////////////////////////////////
// PPP Finite State Machine
////////////////////////////////////////////////////////////////////////////////

enum TPppFsmState
	{
	EPppFsmInitial, EPppFsmStarting,
	EPppFsmClosed, EPppFsmStopped,
	EPppFsmStopping, EPppFsmClosing,
	EPppFsmReqSent, EPppFsmAckRecvd,
	EPppFsmAckSent, EPppFsmOpened
	};

class MPppFsm : public MPppRecvr, public MTimer
	{
public:
	MPppFsm(CPppLcp* aPppLcp, TPppPhase aPhase, TUint aPppId);
	virtual ~MPppFsm();
	void FsmConstructL();
	// Open the state machine
	TInt FsmOpen();
	// Close the state machine
	void FsmClose(TInt aReason);
	// Abort, similar to close, but enters stopped/closed states
	void FsmAbort(TInt aReason);
	// Enquire if this layer is in the Opened state
	TBool FsmIsThisLayerOpen();
	TUint8 FsmNewId();
	void FsmRejectPacket(RMBufChain& aPacket, TUint aReason=KPppLcpCodeReject, TUint aPppId=KPppIdAsIs);
	void TerminateLink();
	void ChangeTimers(TBool aLengthen);

protected:
	// Open the layer below
	virtual TInt FsmLayerStarted()=0;
	// Close the layer below
	virtual void FsmLayerFinished(TInt aReason=KErrNone)=0;
	// Signal up event to next layer above
	virtual void FsmLayerUp()=0;
	// Signal down event to next layer above
	virtual void FsmLayerDown(TInt aReason=KErrNone)=0;
	// Fillin Config Request to be sent
	virtual void FsmFillinConfigRequestL(RPppOptionList& aRequestList)=0;
	// Check options in a recvd config request
	virtual void FsmCheckConfigRequest(RPppOptionList& aRequestList, RPppOptionList& aAckList, RPppOptionList& aNakList, RPppOptionList& aRejList)=0;
	// Apply options in a recvd config request - no-one has complained
	virtual void FsmApplyConfigRequest(RPppOptionList& aRequestList)=0;
	// Recvd a Config Ack
	virtual void FsmRecvConfigAck(RPppOptionList& aReplyList)=0;
	// Recvd a Config Nak - The associated original request is in aReqList
	virtual void FsmRecvConfigNak(RPppOptionList& aReplyList, RPppOptionList& aReqList)=0;
	// Recvd a Config Reject - The associated original request is in aReqList
	virtual void FsmRecvConfigReject(RPppOptionList& aReplyList, RPppOptionList& aReqList)=0;
	// Recvd an unrecognised opcode - has a default implementation
	virtual void FsmTerminationPhaseComplete()=0;
	virtual TBool FsmRecvUnknownCode(TUint8 aCode, TUint8 aId, TInt aLength, RMBufChain& aPacket);	
	virtual void KillProtocol();

	//PG Moved to protected so it can be called by CPppCcp::KillProtocol
	void SetState(TPppFsmState aState);

 	//SL Added to return current state for CPppLcp::LinkRecv
 	inline TPppFsmState FsmState() const { return iState; };
 
private:
	// MPppRecvr upcalls handled by FSM
	virtual TBool RecvFrame(RMBufChain& aPacket);
	virtual void FrameError();
  	virtual void LowerLayerUp();
	virtual void LowerLayerDown(TInt aStatus=KErrNone);
	// MTimer upcall
	virtual void TimerComplete(TInt aStatus);
	// Internal functions
	void InitRestartCountForConfig();
	void InitRestartCountForTerminate();
	void ZeroRestartCount();
	void SendConfigRequest();
	void SendInitialConfigRequest();
	void SendConfigRequestAfterNak(RPppOptionList& aOptList);
	void SendConfigRequestAfterReject(RPppOptionList& aOptList);
	void SendConfigReply(RPppOptionList& aOptList, TUint8 aType, TUint8 aId);
	void SendInitialTerminateRequest();
	void SendTerminateRequest();
	void SendTerminateAck(TUint8 aId);
	void ProcessConfig(TUint8 aCode, TUint8 aId, TInt aLength, RMBufChain& aPacket);
   TBool ProcessEmptyConfigReq();
	void ProcessReject(TUint8 aCode, TUint8 aId, TInt aLength, RMBufChain& aPacket);
	void ProcessTerminate(TUint8 aCode, TUint8 aId, TInt aLength, RMBufChain& aPacket);
	void ThisLayerUp();
	void ThisLayerDown();
	void ThisLayerStarted();
	void ThisLayerFinished();
	TInt InitialiseConfigRequest();

	// Bob Cripps September 1999=
	void ReadIniFileL();
	inline TBool MaxFailureExceeded(){return(iMaxFailureCount == 0);}
	inline void  DecrementMaxFailure(){iMaxFailureCount--;}
	inline void	 InitMaxFailure(){iMaxFailureCount = iMaxFailureConfig;}

public:
	const TText* __iFsmName;
private:
	TUint8 iCurrentId;
	TUint iTerminateId;
	TUint iRequestId;
	RPppOptionList iRequestList;
	// Added Bob Cripps September 1999
	// RFC 1661 4.6
	TInt iMaxRestartConfig;
	TInt iRestartCount;

	TPppFsmState iState;
	
	// Added Bob Cripps September 1999
	// RFC 1661 4.6
	TInt iWaitTimeConfig;
	TInt iWaitTime;
	TInt iConsecCfgReq;
	TUint32 iLastCfgReqFcs;

	// Added Bob Cripps September 1999
	// RFC 1661 4.6
	TInt iMaxFailureConfig;
	TInt iMaxFailureCount;
	
	TBool iLengthenTimers;
	};

enum TPppLinkMode
	{
	EPppLinkIsUnknown,
	EPppLinkIsAuto,
	EPppLinkIsClient,
	EPppLinkIsServer
	};

////////////////////////////////////////////////////////////////////////////////
// [lcp]
// PPPEnableMaxFailure = 0:disabled/1:enabled
// PPPMaxFailureCount = 5 default
_LIT(LCPSECTIONNAME,"lcp");
_LIT(PPPMAXFAILUREENTRYNAME_ENABLE,"PPPEnableMaxFailure");
_LIT(PPPMAXFAILUREENTRYNAME_COUNT,"PPPMaxFailureCount");
const TInt KPppMaxFailureDefault = 5;

// [lcp]
// PPPEnableMaxRestart = 0:disabled/1:enabled
// PPPMaxRestartCount = 20 default
_LIT(PPPMAXRESTARTENTRYNAME_ENABLE,"PPPEnableMaxRestart");
_LIT(PPPMAXRESTARTENTRYNAME_COUNT,"PPPMaxRestartCount");

// [lcp]
// PPPEnableRestartTimer = 0:disabled/1:enabled
// PPPRestartPeriod= 3000 default 3 Seconds
_LIT(PPPRESTARTTIMERENTRYNAME_ENABLE,"PPPEnableRestartTimer");
_LIT(PPPRESTARTTIMERENTRYNAME_PERIOD,"PPPRestartPeriod");// Disable plain text authentication


#endif

