// ET_PHONE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __ET_PHONE_H
#define __ET_PHONE_H

#include "ETEL.H"
#include "ET_TSY.H"

//
// The request with this handle should not be completed by TSY
//
#define TSY_HANDLE_INIT_VALUE (0)

//
// CReqEntry class
//
class CTelSession;
class CTelObject;
class CBuffer;
class CReqEntry : public CBase	
	{
friend class CPhoneBase;
public:
	static CReqEntry* NewL(TTsyReqHandle aTsyReqHandle,const RMessage& aMessage,CTelSession* aSession,CBuffer* aBuffer,const CTelObject* aTelObject,TInt aFunction,RHeap* aHeap);
	CReqEntry(TTsyReqHandle aTsyReqHandle,const RMessage& aMessage,CTelSession* aSession,CBuffer* aBuffer,const CTelObject* aTelObject,TInt aFunction,RHeap* aHeap);
	~CReqEntry();
	void Deque();
	void CompleteAndDeque(TInt aError);
//
	static TAny* operator new(TUint aSize);	
	static TAny* operator new(TUint aSize,TLeave aLeave);
	static TAny* operator new(TUint aSize,TUint anExtraSize);
	static TAny* operator new(TUint aSize,RHeap* aHeap);	// for a priority client request, the
													// objects created must all be taken from
												// the priority heap.
	static void operator delete(TAny* aPtr);

public:
	TTsyReqHandle iTsyReqHandle;
	RMessage iMessage;
	CTelSession* iSession;
	const CTelObject* iTelObject;
	TBool iClientInterested;
	TBool iCancelFnCalled;
	TInt iFunction;
	CBuffer* iBuffer;
	TBool iReadByClient;
	TBool iMessageNulled;
	TBool iPlacedRequest;
	MTelObjectTSY::TReqMode iReqMode;
private:
	TDblQueLink iLink;
public:
	RHeap* iHeap;	// a pointer to the priority heap, used during destruction
	};

//
// CBuffer class
//
class HEtelBufC8;
class HEtelBufC16;
class CBuffer : public CBase
	{
public:
	enum TWhichSlot
		{
		ESlotRead,
		ESlotWrite
		};
	static CBuffer* NewL(HEtelBufC8* aBuf8,HEtelBufC16* aBuf16,RHeap* aHeap,TInt aSizeOfData1,TInt aSizeOfData2,TInt aNoOfSlots);
	CBuffer(HEtelBufC8* aBuf8,HEtelBufC16* aBuf16,RHeap* aHeap,TInt aSizeOfData1,TInt aSizeOfData2,TInt aNoOfSlots);
	CBuffer(HEtelBufC16* aBuf,RHeap* aHeap,TInt aSizeOfData1,TInt aSizeOfData2,TInt aNoOfSlots);
	~CBuffer();
	TBool OverFlow() const;
	TBool BufferFull() const;
	TUint8* CurrentSlotData1(TWhichSlot aWhichSlot) const;
	TUint8* CurrentSlotData2(TWhichSlot aWhichSlot) const;
	TUint16* CurrentSlotData1u(TWhichSlot aWhichSlot) const;
	TUint16* CurrentSlotData2u(TWhichSlot aWhichSlot) const;
	void IncRead();
	void IncWrite();
	TInt CompareRWPtrs() const;
//
	static TAny* operator new(TUint aSize);
	static TAny* operator new(TUint aSize,TLeave aLeave);
	static TAny* operator new(TUint aSize,TUint anExtraSize);
	static TAny* operator new(TUint aSize,RHeap* aHeap);
	static void operator delete(TAny* aPtr);

public:
	HEtelBufC8* iBuf8;	// ptr to buffer if narrow
	HEtelBufC16* iBuf16;	// ptr to buffer if unicode
	RHeap* iHeap;	// a pointer to the priority heap, used during destruction
private:
	TInt iRead;
	TInt iWrite;
	TInt iNoOfSlots;
	TInt iSizeOfData1;
	TInt iSizeOfData2;
	TBool iOverFlow;
	TBool iBufferFull;
	};

const TInt KDeltaTimerInterval=100000;
const TInt KPhoneTimerPriority=50;

//
//	CTelObject
//
class CDestroyDummySubSession;
class CTelServer;
class CPhoneBase;
class CPhoneManager;
class CTelObject : public CObject, public MTelObjectTSY
	{
public:
	IMPORT_C CTelObject();
	IMPORT_C virtual ~CTelObject();
	IMPORT_C virtual void ReqCompleted(const TTsyReqHandle aTsyReqHandle,const TInt aError);
	IMPORT_C virtual void FlowControlSuspend();
	IMPORT_C virtual void FlowControlResume();
	IMPORT_C virtual TInt UpCallOption(const TInt aOptionNumber, TAny* aData);
	IMPORT_C virtual TInt DownCallOption(const TInt aOptionNumber, TAny* aData);	// so TSY doesn't have to implement it
	IMPORT_C virtual TInt ServerVersion() const;

	CPhoneBase* PhoneOwner() const;
	void SetPhoneOwner(CPhoneBase* aPhoneOwner);
	void FlushReqs(CTelSession* aSession,const TInt aSubSessionHandle);
	void GeneralReq(const RMessage& aMessage,CTelSession* aSession,CReqEntry* aNewReqEntry);
	void TelObjectClose();
	TDes8* BufferDes1(const CBuffer* aBuffer,CBuffer::TWhichSlot aWhichSlot) const;
	TDes8* BufferDes2(const CBuffer* aBuffer,CBuffer::TWhichSlot aWhichSlot) const;
	TDes16* BufferDes1u(const CBuffer* aBuffer,CBuffer::TWhichSlot aWhichSlot) const;
	TDes16* BufferDes2u(const CBuffer* aBuffer,CBuffer::TWhichSlot aWhichSlot) const;
	TUint8* Ptr1(const TDes8* aDes1) const;
	void WriteBackAndCompleteBufferedReq(const RMessage& aMessage,CReqEntry* aReqEntry,TInt aError) const;
	void WriteBackAndCompleteReq(CReqEntry* aReqEntry,const TInt aError) const;
	void UpdateAndCompleteIfNecessary(CReqEntry* aReqEntry,TInt aError) const;
	void CancelSubSession(CTelSession* aSession,const TInt aSubSessionHandle);
	void CreateDummySession(CTelSession* aSession,const TInt aSubSessionHandle, TBool aCreateDummy=EFalse);
	void CheckAndDestroyDummySubSession();
	void RemoveDummySubSessionDestroyer();
	TInt ResolveError(CTelSession* aSession, const TInt aError) const;

//
// Pure Virtual
//
	virtual void OpenPostProcessing(CTelSession* aSession,const TInt aSubSessionHandle)=0;
	virtual void CloseSubSessionPreProcessing(CTelSession* aSession,const TInt aSubSessionHandle)=0;
	virtual TInt Service(const RMessage& aMessage,CReqEntry* aReqEntry)=0;
protected:
	TBool IsPriorityClientReq(TInt aReq) const;
private:
	void CompleteAndDestroyReq(CReqEntry* aReqEntry,const TInt aStatus) const;
	void DestroyReq(CReqEntry* aReqEntry) const;
	CReqEntry* ReqAnalyserL(const RMessage& aMessage,CTelSession* aSession,TReqMode& aReqMode);
	CReqEntry* CheckForSimilarRequestAndCreateL(const RMessage& aMessage,CTelSession* aSession) const;
	void CompleteOrBufferRead(const RMessage& aMessage,CReqEntry* aReqEntry);
	TBool IsActiveReq(CTelSession* aSession,const TInt aSubSessionHandle);
	void CancelActiveReq(CTelSession* aSession,const TInt aSubSessionHandle);
	void CheckAndResize(TInt& aSizeOfData,const RMessage& aMessage) const;
	HEtelBufC8* CreateNarrowBufferLC(RHeap* aHeap,const RMessage& aMessage,const TAny* aClientPtr1,const TAny* aClientPtr2,TInt& aSize1,TInt& aSize2,TInt aNoOfSlots) const;
	HEtelBufC16* CreateUnicodeBufferLC(RHeap* aHeap,const RMessage& aMessage,const TAny* aClientPtr1,const TAny* aClientPtr2,TInt& aSize1,TInt& aSize2,TInt aNoOfSlots) const;
private:// data
	CPhoneBase* iPhoneOwner;
	TInt iActiveReqCount;
	CTelServer* iTelServer;
	CDestroyDummySubSession* iDestroyDummySubSession;
	TBool iCreateDummy;
	IMPORT_C virtual void CTelObject_Reserved1();
	TAny* iCTelObject_Reserved;
	};

//
// CSubSessionExtBase
//
class CSubSessionExtBase : public CTelObject, public MSubSessionExtBaseTSY
	{
public:
	IMPORT_C CSubSessionExtBase();
	IMPORT_C virtual ~CSubSessionExtBase();
	TInt ServiceExtFunc(const RMessage& aMessage,CReqEntry* aReqEntry);
protected:
	IMPORT_C virtual TInt Service(const RMessage& aMessage,CReqEntry* aReqEntry);
	IMPORT_C virtual void OpenPostProcessing(CTelSession*,const TInt);
	IMPORT_C virtual void CloseSubSessionPreProcessing(CTelSession* aSession,const TInt aSubSessionHandle);
	IMPORT_C void NullMethod1();
private:
	inline void Inc();
	};

//
// CFaxBase Object
//
class CFaxBase : public CTelObject, public MFaxBaseTSY
	{
public:
	IMPORT_C CFaxBase();
	IMPORT_C virtual ~CFaxBase();
	IMPORT_C virtual TReqMode ReqModeL(const TInt aIpc);
	IMPORT_C virtual TInt NumberOfSlotsL(const TInt aIpc);
	IMPORT_C virtual TInt CancelService(const TInt aIpc,const TTsyReqHandle aTsyReqHandle);
//
// Pure Virtual
//
private:
	IMPORT_C virtual CTelObject* OpenNewObjectByNameL(const TDesC& aName);
	IMPORT_C virtual CTelObject* OpenNewObjectL(TDes& aName);
	IMPORT_C virtual TInt Service(const RMessage& aMessage,CReqEntry* aReqEntry);
	IMPORT_C virtual void OpenPostProcessing(CTelSession*,const TInt);
	IMPORT_C virtual void CloseSubSessionPreProcessing(CTelSession* aSession,const TInt aSubSessionHandle);
	IMPORT_C virtual void Init();
	IMPORT_C void NullMethod2();	 
	};

//
// CCallBase
//
class CCallBase : public CSubSessionExtBase, public MCallBaseTSY
	{
public:
	IMPORT_C CCallBase();
	IMPORT_C virtual ~CCallBase();


	IMPORT_C TCallOwnership CheckOwnership(const TTsyReqHandle aTsyReqHandle) const;
	IMPORT_C TInt SetUnowned();
	IMPORT_C TInt SetOwnership(const TTsyReqHandle aTsyReqHandle);
	IMPORT_C TBool CheckPriorityClient(const TTsyReqHandle aTsyReqHandle) const;
	IMPORT_C CCallBase* ResolveSubSessionHandle(const TTsyReqHandle aTsyReqHandle,const TInt aSubSessionHandle);
	IMPORT_C void RelinquishOwnershipCompleted(const TInt aError);
	IMPORT_C void RecoverDataPortAndRelinquishOwnershipCompleted(const TInt aError);
	IMPORT_C RFax::TProgress* CreateFaxProgressChunk();
	IMPORT_C void DeleteFaxProgressChunk();
	IMPORT_C virtual TReqMode ReqModeL(const TInt aIpc);
	IMPORT_C virtual TInt NumberOfSlotsL(const TInt aIpc);
	IMPORT_C virtual TInt CancelService(const TInt aIpc,const TTsyReqHandle aTsyReqHandle);
private:
	IMPORT_C RCall::TOwnershipStatus CheckOwnershipBySession(CTelSession* aSession,const TInt aSubSession) const;
	IMPORT_C virtual TInt Service(const RMessage& aMessage,CReqEntry* aReqEntry);
	IMPORT_C virtual void Init();
	IMPORT_C virtual void OpenPostProcessing(CTelSession*,const TInt);
	IMPORT_C virtual void CloseSubSessionPreProcessing(CTelSession* aSession,const TInt aSubSessionHandle);
	TCallOwnership iOwnershipStatus;
	CTelSession* iOwnerSession;
	TInt iOwnerSubSessionHandle;
	TBool iLoanDataPort;
	RChunk iChunk;
	};

//
// CLineBase object
//
class CCallBase;
class CLineBase : public CSubSessionExtBase, public MLineBaseTSY
	{
public:
	IMPORT_C CLineBase();
	IMPORT_C virtual ~CLineBase();
	IMPORT_C virtual TReqMode ReqModeL(const TInt aIpc);
	IMPORT_C virtual TInt NumberOfSlotsL(const TInt aIpc);
	IMPORT_C virtual TInt CancelService(const TInt aIpc,const TTsyReqHandle aTsyReqHandle);
private:
	IMPORT_C virtual TInt Service(const RMessage& aMessage,CReqEntry* aReqEntry);
	IMPORT_C virtual void Init();
	IMPORT_C virtual void OpenPostProcessing(CTelSession*,const TInt);
	IMPORT_C virtual void CloseSubSessionPreProcessing(CTelSession* aSession,const TInt aSubSessionHandle);
	
	};

//
// CPhoneBase object
//
class CPhoneBase : public CSubSessionExtBase, public MPhoneBaseTSY
	{
public:
	IMPORT_C CPhoneBase();
	IMPORT_C virtual ~CPhoneBase();
	IMPORT_C virtual TReqMode ReqModeL(const TInt aIpc);
	IMPORT_C virtual TInt NumberOfSlotsL(const TInt aIpc);
	IMPORT_C virtual TInt CancelService(const TInt aIpc,const TTsyReqHandle aTsyReqHandle);
	
	void FlowControlInc();
	void FlowControlDec();
	TInt FlowControl() const;
	CReqEntry* ActivateNextWaitingReq();
	CReqEntry* FindByTsyHandle(const TTsyReqHandle aTsyReqHandle);
	CReqEntry* FindByTsyHandleAndPlacedRequest(const TTsyReqHandle aTsyReqHandle);
	void UpdateBuffer(CReqEntry* aUpdatedReqEntry,CReqEntry* aReqEntry);
	CReqEntry* FindClientInWaiting(CTelSession* aSession,const TInt aSubSessionHandle,const TInt aIpc);
	CReqEntry* FindClientInActive(CTelSession* aSession,const TInt aSubSessionHandle,const TInt aIpc);
	CReqEntry* FindByIpcAndTelObject(const TInt aIpc, const CTelObject* aTelObject);
	CReqEntry* FindByIpcAndTelObjectInWaiting(const TInt aIpc, const CTelObject* aTelObject);
	void AddReqToActive(CReqEntry* aReqEntry);
	void AddReqToWaiting(CReqEntry* aReqEntry);
	CReqEntry* NewReqL(const RMessage& aMessage,CTelSession* aSession,CBuffer* aBuffer,const CTelObject* aTelObject,TInt aFunction);
	CReqEntry* FindSameClientEntry(CTelSession* aSession,const TInt aSubSessionHandle,const TInt aIpc);
	CReqEntry* FindClientReqInWaitList(CTelSession* aSession,const TInt aSubSessionHandle);
	CReqEntry* FindThisReqByAnotherClient(CTelSession* aSession,const TInt aSubSessionHandle,const TInt aIpc,const CTelObject* aThisTelObject);
	CReqEntry* FindNonCancelledClientReq(CTelSession* aSession,const TInt aSubSessionHandle,const TInt aIpc);
	void CheckAndCompleteAllActive(CReqEntry* aUpdatedReqEntry,const TReqMode aReqMode,const TInt aIpc,const TInt aError);
	TDblQue<CReqEntry>& ReqActiveList();
private:
 	IMPORT_C virtual TInt Service(const RMessage& aMessage,CReqEntry* aReqEntry);
	IMPORT_C virtual void OpenPostProcessing(CTelSession* aSession,const TInt aSubSessionHandle);
	IMPORT_C virtual void CloseSubSessionPreProcessing(CTelSession* aSession,const TInt aSubSessionHandle);
	
	TTsyReqHandle TsyReqHandle();
	TInt iTsyReqHandleCnt;
	TInt iFlowControlCnt;
	TDblQue<CReqEntry> iReqWaitList;
	TDblQue<CReqEntry> iReqActiveList;
	};

//
// CLibUnloader class
//
class CPhoneFactoryBase;
class CLibUnloader : public CAsyncOneShot
	{
friend class CPhoneFactoryBase;
public:
	static CLibUnloader* NewL(RLibrary &aLib);
	~CLibUnloader();
protected:
	CLibUnloader();
	virtual void RunL();
private:
	RLibrary iLib;
	};

//
// CPhoneBase factory object
//
class CPhoneFactoryBase : public CObject, public MPhoneFactoryBaseTSY
	{
public:
	IMPORT_C CPhoneFactoryBase();
	IMPORT_C virtual ~CPhoneFactoryBase();

	IMPORT_C virtual TBool QueryVersionSupported(TVersion const& aVersion) const;
	void ConstructL(RLibrary& aLib);
	inline void Inc();
	inline TVersion TsyVersionNumber() const;
protected:
	TVersion iVersion;
private:
	CLibUnloader* iLibUnloader;
	IMPORT_C virtual void CPhoneFactoryBase_Reserved1();
	TAny* iCPhoneFactoryBase_Reserved;
	};

//
// HEtelBufC8 class - this is our version of HBufC8 which will allocate to the 
// priority client heap if aHeap is not NULL (i.e. this is a priority client 
// request)
//

class HEtelBufC8
	{
public:
	static HEtelBufC8* NewMaxLC(TInt aMaxLength,RHeap* aHeap);
	TPtr8 Des();
	const TUint8* Ptr() const;
	static void operator delete(TAny* aPtr);
protected:
	RHeap* iHeap;	// pointer to the priority heap. Used during destruction
	TInt iLength;
	};

//
// and the unicode version...
//							 

class HEtelBufC16
	{
public:
	static HEtelBufC16* NewMaxLC(TInt aMaxLength,RHeap* aHeap);
	TPtr16 Des();
	const TUint16* Ptr() const;
	static void operator delete(TAny* aPtr);
protected:
	RHeap* iHeap;
	TInt iLength;
	};

#include "ET_PHONE.INL"

#endif
