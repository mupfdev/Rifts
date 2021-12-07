// ET_TSY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __ET_TSY_H
#define __ET_TSY_H

//
//	This header file makes it clearer to the TSY developer which functions are to be implemented
//	in the TSY and which are not. However these classes are not to be derived from in the TSY
//	but are inherited by base classes in the server. The TSY should derive from CPhoneBase,
//	CLineBase, CCallBase, CFaxBase, CPhoneFactoryBase and for extensions CSubSessionExtBase.
//

#include "ET_STRUC.H"

typedef TUint32 TTsyReqHandle;
const TUint KUidEtelServerModule = 0x100002A4;
const TUint KUidUnicodeEtelServerModule = 0x10003D3C;
const TInt KETelServerVersion = 1;

const TUint KReqModeMultipleCompletionEnabled=0x00000001;
const TUint KReqModeFlowControlObeyed=0x00000002;
const TUint KReqModeRePostImmediately=0x00000004;

class CTelObject;
class MTelObjectTSY
	{
public:
	typedef TUint TReqMode;
public:
	//
	//	Exported functions to be called by the TSY
	//
	IMPORT_C virtual void ReqCompleted(const TTsyReqHandle aTsyReqHandle,const TInt aError)=0;
	IMPORT_C virtual void FlowControlSuspend()=0;
	IMPORT_C virtual void FlowControlResume()=0;
	IMPORT_C virtual TInt UpCallOption(const TInt aOptionNumber, TAny* aData)=0;
	IMPORT_C virtual TInt ServerVersion() const=0;

	//
	//	Pure virtuals that only need to be implemented if writing extensions, as there are
	//	implementations in the base classes in the server
	//
	virtual TReqMode ReqModeL(const TInt aIpc)=0;
	virtual TInt NumberOfSlotsL(const TInt aIpc)=0;
	virtual TInt CancelService(const TInt aIpc,const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt DownCallOption(const TInt aOptionNumber, TAny* aData)=0;
	//
	//	Pure virtuals that must be implemented by the TSY 
	//
	virtual void Init()=0;
	virtual CTelObject* OpenNewObjectByNameL(const TDesC& aName)=0;
	virtual CTelObject* OpenNewObjectL(TDes& aName)=0;
	virtual TInt RegisterNotification(const TInt aIpc)=0;
	virtual TInt DeregisterNotification(const TInt aIpc)=0;
	
	};

class TDataPackage
	{
public:
	TDataPackage();
	TDataPackage(TDes8* aDes1, TDes8* aDes2);
	TDataPackage(TDes16* aDes1, TDes16* aDes2);
	TDataPackage(TDes8* aDes1, TDes16* aDes2);
public:
	IMPORT_C TAny* Ptr1() const; // used when accessing a structure which was packaged up on the client
								 // side as a descriptor
	IMPORT_C TAny* Ptr2() const; // functions will return NULL if the corresponding pointer is NULL

	IMPORT_C TDes8* Des1n() const;	// used when accessing a specific TDes8 descriptor
	IMPORT_C TDes8* Des2n() const;
	IMPORT_C TDes16* Des1u() const; // used when accessing a TDes16 descriptor (ie a TDes in
									// UNICODE builds)
	IMPORT_C TDes16* Des2u() const;
	
private:
	TDes8* iDes1; 
	TDes8* iDes2;
	TDes16* iDes1u;
	TDes16* iDes2u;
	};

class MSubSessionExtBaseTSY
	{
public:
	//
	//	Pure virtual to be implemented by the TSY
	//
	virtual TInt ExtFunc(const TTsyReqHandle aTsyReqHandle,const TInt aIpc,const TDataPackage& aDataPackage)=0;
	};

class MFaxBaseTSY
	{
public:
	//
	//	Pure virtuals to be implemented by the TSY
	//
	virtual TInt Read(const TTsyReqHandle aTsyReqHandle,TDes8* aFaxPage)=0;
	virtual TInt Write(const TTsyReqHandle aTsyReqHandle,TDesC8* aFaxPage)=0;
	virtual TInt WaitForEndOfPage(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt TerminateFaxSession(const TTsyReqHandle aTsyReqHandle)=0;
	};

class CCallBase;
class MCallBaseTSY
	{
public:
	typedef enum
		{
		EOwnedUnowned,
		EOwnedFalse,
		EOwnedTrue,
		EOwnedPriorityClient
		} TCallOwnership;

public:
	//
	//	Exported functions to be called by the TSY
	//
	IMPORT_C virtual TCallOwnership CheckOwnership(const TTsyReqHandle aTsyReqHandle) const=0;
	IMPORT_C virtual TInt SetUnowned()=0;
	IMPORT_C virtual TInt SetOwnership(const TTsyReqHandle aTsyReqHandle)=0;
	IMPORT_C virtual TBool CheckPriorityClient(const TTsyReqHandle aTsyReqHandle) const=0;
	IMPORT_C virtual CCallBase* ResolveSubSessionHandle(const TTsyReqHandle aTsyReqHandle,const TInt aSubSessionHandle)=0;
	IMPORT_C virtual void RelinquishOwnershipCompleted(const TInt aError)=0;
	IMPORT_C virtual void RecoverDataPortAndRelinquishOwnershipCompleted(const TInt aError)=0;
	IMPORT_C virtual RFax::TProgress* CreateFaxProgressChunk()=0;
	IMPORT_C virtual void DeleteFaxProgressChunk()=0;
	
	//
	//	Pure virtuals to be implemented by the TSY
	//
	virtual TInt GetInfo(const TTsyReqHandle aTsyReqHandle,RCall::TCallInfo* aCallInfo)=0;
	virtual TInt NotifyCapsChange(const TTsyReqHandle aTsyReqHandle,RCall::TCaps* aCaps)=0;
	virtual TInt NotifyCapsChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyHookChange(const TTsyReqHandle aTsyReqHandle,RCall::THookStatus* aHookStatus)=0;
	virtual TInt NotifyHookChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyStatusChange(const TTsyReqHandle aTsyReqHandle,RCall::TStatus* aStatus)=0;
	virtual TInt NotifyStatusChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyDurationChange(const TTsyReqHandle aTsyReqHandle,TTimeIntervalSeconds* aStatus)=0;
	virtual TInt NotifyDurationChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt LoanDataPort(const TTsyReqHandle aTsyReqHandle,RCall::TCommPort*)=0;
	virtual TInt LoanDataPortCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt RecoverDataPort(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt RecoverDataPortAndRelinquishOwnership()=0;
	virtual TInt GetStatus(const TTsyReqHandle aTsyReqHandle,RCall::TStatus* aStatus)=0;
	virtual TInt GetCaps(const TTsyReqHandle aTsyReqHandle,RCall::TCaps* aCaps)=0;
	virtual TInt Dial(const TTsyReqHandle aTsyReqHandle,const TDesC8* aCallParams,TDesC* aTelNumber)=0;
	virtual TInt DialCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt Connect(const TTsyReqHandle aTsyReqHandle,const TDesC8* aCallParams)=0;
	virtual TInt ConnectCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt AnswerIncomingCall(const TTsyReqHandle aTsyReqHandle,const TDesC8* aCallParams)=0;
	virtual TInt AnswerIncomingCallCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt HangUp(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt HangUpCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt TransferOwnership(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt AcquireOwnership(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt AcquireOwnershipCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt RelinquishOwnership()=0;
	virtual TInt GetBearerServiceInfo(const TTsyReqHandle aTsyReqHandle,RCall::TBearerService* aService)=0;
	virtual TInt GetCallParams(const TTsyReqHandle aTsyReqHandle,TDes8* aParams)=0;
	virtual TInt GetCallDuration(const TTsyReqHandle aTsyReqHandle,TTimeIntervalSeconds* aTime)=0;
	virtual TInt GetFaxSettings(const TTsyReqHandle aTsyReqHandle,RCall::TFaxSessionSettings* aSettings)=0;
	virtual TInt SetFaxSettings(const TTsyReqHandle aTsyReqHandle,const RCall::TFaxSessionSettings* aSettings)=0;
	};


class MLineBaseTSY
	{
public:
	//
	//	Pure virtuals to be implemented by the TSY
	//
	virtual TInt GetInfo(const TTsyReqHandle aTsyReqHandle,RLine::TLineInfo* aLineInfo)=0;
	virtual TInt NotifyCapsChange(const TTsyReqHandle aTsyReqHandle,RLine::TCaps* aCaps)=0;
	virtual TInt NotifyCapsChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyIncomingCall(const TTsyReqHandle aTsyReqHandle, TName* aName)=0;
	virtual TInt NotifyIncomingCallCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyHookChange(const TTsyReqHandle aTsyReqHandle,RCall::THookStatus* aHookStatus)=0;
	virtual TInt NotifyHookChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyStatusChange(const TTsyReqHandle aTsyReqHandle,RCall::TStatus* aLineStatus)=0;
	virtual TInt NotifyStatusChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyCallAdded(const TTsyReqHandle aTsyReqHandle,TName* aName)=0;
	virtual TInt NotifyCallAddedCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt GetCaps(const TTsyReqHandle aTsyReqHandle,RLine::TCaps* aCaps)=0;
	virtual TInt GetStatus(const TTsyReqHandle aTsyReqHandle,RCall::TStatus* aStatus)=0;
	virtual TInt GetHookStatus(const TTsyReqHandle aTsyReqHandle,RCall::THookStatus* aHookStatus)=0;
	virtual TInt EnumerateCall(const TTsyReqHandle aTsyReqHandle,TInt* aCount)=0;
	virtual TInt GetCallInfo(const TTsyReqHandle aTsyReqHandle,TCallInfoIndex* aCallInfo)=0;
	};

class MPhoneBaseTSY
	{
public:
	//
	//	Pure virtuals to be implemented by the TSY
	//
	virtual TInt GetInfo(const TTsyReqHandle aTsyReqHandle,RPhone::TPhoneInfo* aPhoneInfo)=0;
	virtual TInt NotifyCapsChange(const TTsyReqHandle aTsyReqHandle,RPhone::TCaps* aCaps)=0;
	virtual TInt NotifyCapsChangeCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt ControlledInitialisation(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt ControlledInitialisationCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt NotifyModemDetected(const TTsyReqHandle aTsyReqHandle,RPhone::TModemDetection* aDetection)=0;
	virtual TInt NotifyModemDetectedCancel(const TTsyReqHandle aTsyReqHandle)=0;
	virtual TInt GetCaps(const TTsyReqHandle aTsyReqHandle,RPhone::TCaps* aCap)=0;
	virtual TInt GetStatus(const TTsyReqHandle aTsyReqHandle,RPhone::TStatus* aStatus)=0;
	virtual TInt EnumerateLines(const TTsyReqHandle aTsyReqHandle,TInt* aCount)=0;
	virtual TInt GetLineInfo(const TTsyReqHandle aTsyReqHandle,TLineInfoIndex* aLineInfo)=0;
	};

class CPhoneBase;
class MPhoneFactoryBaseTSY
	{
public:
	//
	//	Exported functions to be called by the TSY
	//
	IMPORT_C virtual TBool QueryVersionSupported(TVersion const& aVersion) const=0;
	//
	//	Pure virtuals to be implemented by the TSY
	//
	virtual CPhoneBase* NewPhoneL(const TDesC& aName)=0;
	virtual TInt GetPhoneInfo(const TInt aIndex,RTelServer::TPhoneInfo& aInfo)=0;
	virtual TInt EnumeratePhones()=0;
	virtual TBool IsSupported(const TInt aMixin)=0;
	};

#endif