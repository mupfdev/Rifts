// PPPLCP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__PPPLCP_H__)
#define __PPPLCP_H__

#include <networking\pppdef.h>

#if !defined(__NIFIF_H__)
#include <comms-infras\nifif.h>
#endif // __NIFIF_H__

////////////////////////////////////////////////////////////////////////////////
// PPP LCP - The heart of PPP
////////////////////////////////////////////////////////////////////////////////

//const TUint KPppIdEsocl = 0x10000; // outside PPP range and Esock forbids zero.

class CPppIfFactory : public CNifIfFactory
	{
protected:
	virtual void InstallL();
	virtual CNifIfBase* NewInterfaceL(const TDesC& aName);
	virtual TInt Info(TNifIfInfo& aInfo, TInt aIndex) const;
	};

class CPppAcp;
class CPppApBase;
class CPppMsCbcpClient;	// CSW


// Callback IETF request types (see draft RFC for PPP-callback)
typedef enum	// CSW
	{
	ECallbackIETFRequestType0=0,	// defined by IETF draft RFC
	ECallbackIETFRequestType1=1,
	ECallbackIETFRequestType2=2,
	ECallbackIETFRequestType3=3,
	ECallbackIETFRequestType4=4,
	ECallbackIETFRequestType5=5,
	// and also
	ECallbackIETFRequestTypeMSCBCP=6	// from MS rejected draft
	} TCallbackIETFRequestType;

class CPppCcp;
class CPppLrd;
class CPppLinkBase;
class MPppRecvr;
class CPppCompressor;
class CPppDeCompressor;
class RPppOptionList;

class CPppLcp : public CNifIfLink, public MPppFsm, public MPppOptionsExtender
	{
public:
	CPppLcp(CNifIfFactory& aFactory);
	~CPppLcp();
	void InitL();
	inline CPppLinkBase*  PppLink() { return iPppLink; }
	void RegisterRecvr(MPppRecvr* aRecvr);
	void ReregisterRecvr(MPppRecvr* aRecvr);
	void DeregisterRecvr(MPppRecvr* aRecvr);
	void LinkRecv(RMBufChain& aPacket);
	void LinkFlowOn();
	void LinkLayerUp();
	void LinkLayerDown(TInt aStatus);
	void PhaseComplete();
	void PhaseAborted(TInt aStatus);
	void PhaseAdvance(TPppPhase aNewPhase);
	void PhaseRetard(TPppPhase aNewPhase, TInt aReason);
	TUint8 SendEchoRequest();
	void SendIdentification();
	TPppLinkMode PppLinkMode();
	//
	TInt PppOpen();
	void PppClose(TInt aReason);

	void Authenticate(CPppApBase* aAp);
	void CancelAuthenticate(CPppApBase* aAp);
	inline const TDesC& PassWord() const { return iPassWord; }
	inline const TDesC& UserName() const { return iUserName; }

	virtual TInt Send(RMBufChain& aPdu, TAny* aSource=0);
    virtual void AuthenticateComplete(TInt aResult);
	virtual TInt Start();
	virtual void Stop(TInt aReason, MNifIfNotify::TAction aAction);
	virtual CNifIfBase* GetBinderL(const TDesC& aName);
	virtual void Info(TNifIfInfo& aInfo) const;
	static void FillInInfo(TNifIfInfo& aInfo);
	inline TBool DoLcpExts() const { return iDoLcpExts; }
	inline void CallbackRequestGranted();	// CSW
	void   TerminateLink(MNifIfNotify::TAction aAction, TInt aError=KErrNone);
	void PppNewCompressor(const CPppCompressor* aCompressor);
	void PppNewDeCompressor(const CPppDeCompressor* aDeCompressor);
	void StopProtocol(TUint aProtocol);
	inline void SetMaxTransferSize(TInt aLength);
	inline TInt MaxTransferSize();
	TBool DoesDllExist(const TDesC& aFilename);
	inline CObjectConIx*	ContainerForDlls() const { return iContainerForDlls; }

	// inherited from CNifIfLink, for GPRS
	virtual TInt Notification(TAgentToNifEventType aEvent, void * aInfo);
	
	// Added Bob Cripps for callback July 99
	inline TCallbackIETFRequestType CallbackRequestType(){return iCallbackIETFRequestType;}
	inline TBool CallbackEnabled(){return iCallbackEnabled;}

	// Added Bob Cripps September 1999 for ppp.ini config of MRU
	inline void SetMru(TInt aSize){iMaxRecvSize = aSize;}

	void CancelRead();
protected:
	// PPP FSM Upcalls
	virtual TInt FsmLayerStarted();
	virtual void FsmLayerFinished(TInt aReason=KErrNone);
	virtual void FsmLayerUp();
	virtual void FsmLayerDown(TInt aReason=KErrNone);
	virtual void FsmFillinConfigRequestL(RPppOptionList& aRequestList);
	virtual void FsmCheckConfigRequest(RPppOptionList& aRequestList, RPppOptionList& aAckList, RPppOptionList& aNakList, RPppOptionList& aRejList);
	virtual void FsmApplyConfigRequest(RPppOptionList& aRequestList);
	virtual void FsmRecvConfigAck(RPppOptionList& aReplyList);
	virtual void FsmRecvConfigNak(RPppOptionList& aReplyList, RPppOptionList& aReqList);
	virtual void FsmRecvConfigReject(RPppOptionList& aReplyList, RPppOptionList& aReqList);
	virtual void FsmTerminationPhaseComplete();
	virtual TBool FsmRecvUnknownCode(TUint8 aCode, TUint8 aId, TInt aLength, RMBufChain& aPacket);
private:
	static void NewMagicNumber(TUint& aMagicNumber);
	INLINE void AppendCallbackRequestL(RPppOptionList&  aRequestList );
	INLINE void InitCallbackInfoL();
	INLINE void PhaseAdvancesBeyondAuthenticate();
public:
	void CallbackGrantedAndAuthenticated();
private:
	INLINE TBool GetCallbackEnabledFromNetdial();
	INLINE TCallbackAction GetCallbackActionFromNetdialL();
	INLINE TInt GetCallbackRequestInfoFromNetdial( TDes8& aInfo );
	INLINE void GetCallbackInfoL();
	INLINE void NewCallbackRequestInfoL( TCallbackIETFRequestType aRequestType );	// CSW
	INLINE TBool QueryNetdialIsDialIn();
private:
	CPppCcp* iPppCcp;
	TInt iOpenCount;
	TPppPhase iPhase;
	CPppAcp* iPppAcp;
	CPppLrd* iPppLrd;

	CPppLinkBase* iPppLink;
	TDblQue<MPppRecvr> iRecvrList;
	TUint iLocMagicNumber;
	TUint iRemMagicNumber;	// Or last NAK sent to peer
	TInt iConsecMagic;
	TInt iMaxSendSize;
	TInt iMaxRecvSize;
	HBufC8* iRecvIdentification;
	TTimeIntervalSeconds iRecvTimeRemaining;
	TTime iRecvTimeNotification;
	HBufC8* iRecvTimeRemMessage;
	CPppApBase* iAuthenticate;

	TBool	iGotCallbackInfo;			
	TBool	iCallbackEnabled;			
	TCallbackAction iCallbackAction;	
	TCallbackIETFRequestType iCallbackIETFRequestType;	
	TUint8* iCallbackInfo;	
	TInt	iCallbackInfoLen;	
	TUint8* iCallbackIETFRequestPacket;	
	TInt	iCallbackIETFRequestPacketLen;	
	TBool	iCallbackRequestGranted;	
	CPppMsCbcpClient * iPppMsCbcp;		
	MNifIfNotify::TAction iTerminateAction;
	TInt	iError;

	TBool iDoLcpExts;
	TBool iRecursive;
	CObjectConIx*	iContainerForDlls;

	TBuf<50> iUserName;
	TBuf<50> iPassWord;
	TBool iAuthenticateDone;

	};

#include <networking\ppplcp.inl>
#endif
