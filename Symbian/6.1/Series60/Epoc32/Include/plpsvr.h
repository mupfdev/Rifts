// PLPSVR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined (__PLPSVR_H__)
#define __PLPSVR_H__

// #if !defined (__SIBOUTIL_H__)
// #include <siboutil.h>
// #endif

#if !defined (__PLPSESS_H__)
#include <plpsess.h>
#endif

#if !defined (__PLPSOCK_H__)
#include <plpsock.h>
#endif

enum TPlpRequestType
    { 

    EReqNone, EReqCloseHandle, EReqIsConnected,
    EReqWaitForConnect, EReqCancel, EReqSetWatchDogTimer, EReqCancelAll,
    EReqReserved=15
    };

enum TPlpErrorEvent
    {

    EPlpEventCallReadL, EPlpEventReadComplete, EPlpEventCallReadCompleteL,
    EPlpEventWriteComplete, EPlpEventCallWriteCompleteL,
    EPlpEventNewSession,  EPlpEventTooMany,
    EPlpEventAcceptComplete, EPlpEventCallAcceptL,
    EPlpEventConnectComplete, EPlpEventCallConnectCompleteL,
    EPlpEventTimeout, EPlpEventReconnect,
    };

enum TPlpErrorResult
    { 
    EPlpResultObjectFatal, EPlpResultObjectOk
    };

class TPlpSockInfo
    {
public:
    inline TPlpSockInfo(TUint aAddrFamily, TUint aSockType, TUint aProtocol);
    inline TPlpSockInfo();

    TUint iAddrFamily;
    TUint iSockType;
    TUint iProtocol;
    };

const TUint KPlpServAndSocketDefaultMessageSlots = 3;

class RPlpServAndSocket
    {

public:
    IMPORT_C RPlpServAndSocket();  
    IMPORT_C void Close();
    IMPORT_C TInt Open(const TPlpSockInfo &aInfo, TUint aMessageSlots=KPlpServAndSocketDefaultMessageSlots);
   
public:
    RSocket iSocket;
    RSocketServ iServ;
    };

class CPlpSocketHandler : public CActive
    {
public:
    IMPORT_C ~CPlpSocketHandler();

protected:
    IMPORT_C CPlpSocketHandler(TInt aPriority);
    IMPORT_C void ConstructL(TInt aNumberSockets);
    IMPORT_C RSocket& Socket() const;
    IMPORT_C void CreateSocketL(const TPlpSockInfo &aInfo);

    virtual void DoCancel()=0;
    virtual void RunL()=0;

    inline TInt State() const;
    inline void SetState(TInt aState);        
    inline RSocketServ &SocketServ() const;
    inline TBool IsSocketValid() const;
    
	void ClearSocket();
    RSocket *TransferSocket();

private:

    TInt iState;
    RSocket *iSocket;
    RSocketServ iSS;
    };

class CPlpIo;
class CPlpIoWriter : public CActive
    {
friend class CPlpIo;

private:
    CPlpIoWriter(CPlpIo &aRW);
    ~CPlpIoWriter();
    virtual void RunL();
    virtual void DoCancel();
    CPlpIo *iIO;
    };


class MPlpIoNotifier;
typedef CPlpIo *(*TPlpIoNewL)(MPlpIoNotifier &aNotifier);

class MPlpIoNotifier
    {
private:
    CPlpIo *iIO;
protected:
    inline void Write(TDes8 *aDes);
    inline TBool IsWriting() const;
    inline void DeleteIo();
    inline void CancelIo();
    inline void ReadIoL();
	inline void SetIoSocketAndPriority(RSocket *aSocket,int aReaderPriority,int aWriterPriority);
	inline void NewIoL(TPlpIoNewL aNewL);
public:
    virtual void ReadCompleteL(TDes8 *aPdu)=0;
    virtual void WriteCompleteL(TDes8 *aPdu)=0;    
    virtual TDes8* AllocL(TInt aLen)=0;
    virtual void Free(TDes8 *aPdu)=0;
    virtual TPlpErrorResult Error(TInt aStatus, TInt aErrorEvent)=0;
    };

class CPlpIo : public CActive
    {
friend class CPlpIoWriter;

public:
    IMPORT_C ~CPlpIo();
    IMPORT_C static CPlpIo *NewL(MPlpIoNotifier &aNotifier);
    IMPORT_C void ReadL();                   // read data
    IMPORT_C void Write(TDes8 *aPdu);        // write data
    IMPORT_C void CallError(TInt aStatus, TInt aErrorEvent);    
    IMPORT_C void SetPriorities(TInt aReaderPriority, TInt aWriterPriority);
    IMPORT_C void SetSocket(RSocket *aSocket);

    inline TBool IsWriting() const;
    inline TBool IsReading() const;

protected:
    enum TReadState { EReadAgain, EReadOnce, EReadPartial };
    IMPORT_C CPlpIo();
    IMPORT_C void ConstructL(MPlpIoNotifier &aNotifier);                  
    IMPORT_C TDes8* CallReadAllocL(TInt aLen=0);                                   
    IMPORT_C virtual TReadState DoReadL(TRequestStatus &aStatus);        // user method for reading
    IMPORT_C virtual void DoWrite(TDes8* aPdu, TRequestStatus &aStatus); // user method for writing

    IMPORT_C virtual void RunL();
    IMPORT_C virtual void DoCancel(); 

private:
    
    MPlpIoNotifier *iNotifier;
    RSocket *iSocket;
    CPlpIoWriter *iWriter;
    TDes8 *iReadPtr;
    TDes8 *iWritePtr;
    TReadState iReadState;
    };

class TPlpTimerEntry : public TDeltaTimerEntry
    {

public:
    inline TPlpTimerEntry(); 
    inline TBool IsQued() const;
    inline void Deque();
    inline void Enque(CDeltaTimer &aTimer, TTimeIntervalMicroSeconds32 aTimeInMicroSeconds);
    inline void Reset();
private:
    CDeltaTimer *iTimer;
    };

//
// Client classes
//

class TPlpClientInfo : public TPlpSockInfo
    {
public:
    TInt iConnectorPriority;
    TInt iReaderPriority;
    TInt iWriterPriority;
    TInt iMaxPduSize;
    TSockAddr iBindAddr;
    TSockAddr iConnectAddr;
    };

class CPlpClient;
class MPlpClientManager
    {
public:
    virtual void AddToClientList(CPlpClient &aClient)=0;
    virtual void FatalClientError(CPlpClient &aClient, TInt aError, TInt aErrorEvent)=0; 
    };

class CPlpClient : public CPlpSocketHandler, public MPlpIoNotifier
    {

public:
    IMPORT_C ~CPlpClient();
    IMPORT_C void ConnectL();
    IMPORT_C void Disconnect();
    inline TPlpClientInfo& Info() const;
    inline MPlpClientManager& Manager() const;
    IMPORT_C static TInt ReconnectClient(TAny* aClient);

protected:
    IMPORT_C CPlpClient();
    IMPORT_C void ConstructL(TPlpIoNewL aNewL, MPlpClientManager &aManager); 

    virtual void ConnectCompleteL(TVersion aVersion)=0;
    virtual void ReadCompleteL(TDes8 *aPdu)=0;
    virtual TDes8* AllocL(TInt aLen)=0;
    virtual TPlpClientInfo *NewInfoL()=0;

    IMPORT_C virtual void WriteCompleteL(TDes8 *aPdu);    
    IMPORT_C virtual TPlpErrorResult Error(TInt aStatus, TInt aRemErrorEvent);
    IMPORT_C virtual void CallConnectCompleteL();
    IMPORT_C virtual void Free(TDes8 *aPdu);
    IMPORT_C virtual void RunL();
    IMPORT_C virtual void DoCancel();
    IMPORT_C virtual void InitL();

    enum TState
        { 
        EStopped, ESyncInit, EASyncInit, EConnecting, EConnectComplete, EConnected
        };

public:
    TDblQueLink iDblLink;
    TPlpTimerEntry iTimerEntry;

private:

    TPlpClientInfo *iInfo;
    TPlpIoNewL iNewL;
    MPlpClientManager *iManager;
    };

//
// Server classes
//

class TPlpServInfo 
    {
public:
    TInt iDeleterPriority;
    TInt iReaderPriority;
    TInt iServerPriority;
    TInt iWriterPriority;
    TInt iMaxSessions;
    TInt iMaxPduSize;
    TPtrC8 iServerName;
    };

class CPlpServer;
class MPlpServerManager
    {
public:
    virtual void AddToServerList(CPlpServer &aServer)=0;
    virtual void FatalServerError(CPlpServer &aServ, TInt aError, TInt aErrorEvent)=0; 
    };

class CPlpSession;
class CPlpServerDeleter;
class CPlpServer : public CPlpSocketHandler
    {
friend class CPlpSession;

public:
    IMPORT_C void StartL();
    IMPORT_C void Stop();
    IMPORT_C static void Delete(CPlpServer *aServ);

    inline TInt SessionCount() const;
    inline MPlpServerManager& Manager() const;
    inline void SetLib(const RLibrary &aLib);
    inline void DeferredDelete();
    inline TPlpServInfo& Info() const;
	inline RLibrary& Library() const;
    IMPORT_C RSocket& NewSocket() const;
    IMPORT_C virtual TPlpErrorResult Error(TInt aStatus, TInt aRemErrorEvent);
	IMPORT_C void ExecuteL(const TDesC& aFilename, const TDesC& aArgs);

protected:

    enum TState
        { 
        EStopped, ESyncInit, EASyncInit, EAccepting, EAcceptComplete
        };

    IMPORT_C void ConstructL(MPlpServerManager &aManager);
    IMPORT_C CPlpServer();
    IMPORT_C ~CPlpServer();
    IMPORT_C void AcceptL();

    IMPORT_C virtual void RunL();   
    IMPORT_C virtual void InitL();
    IMPORT_C virtual void DoCancel();
    IMPORT_C virtual void CallNewSessionL();
    
    virtual CPlpSession *NewSessionL(TVersion aVersion)=0;
    virtual TPlpServInfo *NewInfoL()=0;

private:
    RSocket *TransferNewSocket();
    void CreateNewSocketL();
    void ClearNewSocket();
    void ClearAllSessions();
    void DoStartL();

public:
    TDblQueLink iDblLink;

private:
    RSocket *iNewSocket;
    TDblQue<CPlpSession> iSessionList;
    TInt iSessionCount;
    TPlpServInfo *iInfo;
    MPlpServerManager *iManager;
    CPlpServerDeleter *iDeleter;
    RLibrary iLib;

protected:
	TDblQueIter<CPlpSession> iSessionIter;
    };

class CPlpSession : public CBase, public MPlpIoNotifier
    {

friend class CPlpServer;

public:    
    IMPORT_C ~CPlpSession();

protected:
    IMPORT_C void ConstructL(TPlpIoNewL aNewL, CPlpServer& aServ);
    IMPORT_C CPlpSession();
    IMPORT_C virtual void WriteCompleteL(TDes8 *aPdu);    
    IMPORT_C virtual void Free(TDes8 *aPdu);
    IMPORT_C virtual TPlpErrorResult Error(TInt aStatus, TInt aRemErrorEvent);

    inline CPlpServer &Server() const;
    inline void Cancel();

    virtual TDes8* AllocL(TInt aLen)=0;
private:   

    CPlpServer *iServer;
    TDblQueLink iDblLink;
    };

class CPlpServerDeleter : public CAsyncOneShot
    {
friend class CPlpServer;

private:
    CPlpServerDeleter(CPlpServer &aServ, TInt aPriority);
    CPlpServer *iServ;
    virtual void RunL();    
    }; 

class TRemSvPtr : public TPtr8
    {
public:

    inline TRemSvPtr();
    inline TRemSvPtr(TUint8* iBuf, TInt aLength);
	inline TUint32 GetLong(TInt anOffset) const;
	inline TUint16 GetWord(TInt anOffset) const;
	inline void PutLong(TInt anOffset, TUint32 aVal);
	inline void PutWord(TInt anOffset, TUint16 aVal);
    inline void WSet(TRemSvPtr& aPtr, TInt anOffset);
//
    inline void SetDesLength32(TInt aOffset, TInt aLength); 
    inline TInt64 GetInt64(TInt aOffset);
    inline void PutInt64(TInt aOffset, TInt64 aVal);
    IMPORT_C TPtrC8 GetDes32(TInt aOffset);
    IMPORT_C TPtrC16 GetDes16(TInt aOffset);
    IMPORT_C TBool VerifyLength32() const;
//    IMPORT_C TBool VerifyLength16() const;
    IMPORT_C void WSet(TRemSvPtr& aPtr, TInt anOffset, TInt aLength);
	};

class TPlpCharConv
	{
public:
#ifdef _UNICODE
	enum TBehaviour {EUnicodeAndEscape, EAnsiAndEscape, EAnsiOnly};
	IMPORT_C static TInt ConvertFromUnicodeToWire(const TDesC16& aSrc, TDes8& aTrg, TBehaviour aBehaviour);
	IMPORT_C static TInt ConvertFromWireToUnicode(const TDesC8& aSrc, TDes16& aTrg);
	IMPORT_C static void ConvertFromUnicodeToWireL(const TDesC16& aSrc, TDes8& aTrg, TBehaviour aBehaviour);
	IMPORT_C static void ConvertFromWireToUnicodeL(const TDesC8& aSrc, TDes16& aTrg);
	IMPORT_C static void CopyDes16ToDes8L(const TDesC16& aSrc, TDes8& aTrg);
	IMPORT_C static void CopyDes8ToDes16L(const TDesC8& aSrc, TDes16& aTrg);
	IMPORT_C static void AppendDes16ToDes8L(const TDesC16& aSrc, TDes8& aTrg);
	IMPORT_C static void AppendDes8ToDes16L(const TDesC8& aSrc, TDes16& aTrg);
#endif
    };

class CRexecPeer;
class CPlpServerManager : public CBase, public MPlpServerManager, public MPlpClientManager
    {

friend class CRexecPeer;

public:
    IMPORT_C static CPlpServerManager* NewL(RPlpServAndSocket& aSock);
    IMPORT_C ~CPlpServerManager();
    IMPORT_C CRexecPeer *FindLinkChannel(TUint aInterface);

    static void MapFileName(const TDesC& aRequested, TDes& aFileName);
    CPlpServer *FindServer(const TDesC &aFileName);
    void LoadCustomServerL(const TDesC &aName, const TDesC &aArgs, TDes8* aResult);

    virtual void AddToServerList(CPlpServer &aServer);
    virtual void FatalServerError(CPlpServer &aServer, TInt aError, TInt aErrorEvent);
    virtual void AddToClientList(CPlpClient &aClient);
    virtual void FatalClientError(CPlpClient &aClient, TInt aError, TInt aErrorEvent);
	static void ExecuteL(MPlpServerManager& aManger, const TDesC& aFilename, const TDesC& aArgs, TDes8* aResult);

protected:
    CPlpServerManager();
    void ConstructL(RPlpServAndSocket& aSock);

private:
    void StartRexecL(RPlpServAndSocket& aSock);

    TDblQue<CRexecPeer> iRexecList;
    TDblQue<CPlpServer> iServerList;
    CDeltaTimer* iTimer;
	RSemaphore iConfigSemaphore;
    };

class RExe : public RSessionBase
	{

public:
	static void ExecuteL(const TDesC& aFile, const TDesC& aArgs, TBool aDoc=ETrue);
	};

//
// Various priorities for remote services thread
//

enum TPlpServicesPriority
    {
    EPlpConnectPriority = CActive::EPriorityStandard,
    EPlpIpcPriority = CActive::EPriorityUserInput,
    EPlpTimerPriority = EPlpIpcPriority + 10,
    EPlpReadPriority = EPlpIpcPriority + 20, 
    EPlpWritePriority = EPlpIpcPriority + 30,
    EPlpLibDeleterPriority = EPlpIpcPriority + 40,
    };
//
const TInt KPlpStandardTick = 200000; // 1/5 of a second
const TUint KPlpMaxLinkId = 0x0000FFFF;
#ifdef _UNICODE
const TUint KPlpRemoteServerUnicodeUid = 0x10003d52;
#else
const TUint KPlpRemoteServerUid = 0x100000ED;
#endif
//

class SiboUtil
    {
public:
    IMPORT_C static void Put16(TUint8* aPtr, TUint16 aVal);
    IMPORT_C static void Put32(TUint8* aPtr, TUint32 aVal);
    IMPORT_C static TUint16 Get16(const TUint8* aPtr);
	IMPORT_C static TUint32 Get32(const TUint8* aPtr);
    IMPORT_C static void PutFloat(TAny* aPtr, const TReal64& aFloat);
    IMPORT_C static TReal64 GetFloat(TAny* aPtr);
  };

#include <plpsvr.inl>

#endif
