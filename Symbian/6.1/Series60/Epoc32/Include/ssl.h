// SSL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


/* Contains only the exported functions. */

#ifndef __TCPSSL_H__
#define __TCPSSL_H__

#include <in_sock.h>
#include <es_mbuf.h>
#include <sslerr.h>

// TcertInfo was originately part of certman.h

class TDNInfo
{
public:
	TBuf8<4> iCountry;
	TBuf8<64> iOrganizationUnit;
	TBuf8<64> iOrganization;
	TBuf8<64> iCommonName;
	TBuf8<128> iLocality;
};

class TCertInfo
{
public:
	TBuf8<20> iFingerprint;
	TBuf8<32> iSerialNo;
	TBuf8<300> iPublicKey;
	TInt iVersionNo;
	/*TPublicKeyAlg*/TInt iPkAlg;
	TTime iStartValDate;
	TTime iEndValDate;
	TDNInfo iSubjectDNInfo;
	TDNInfo iIssuerDNInfo;
	TBuf<128> iDNSName;
private:
	TBuf8<250> iSpare;
};

// next 3 lines xfer from ssldata.h
const TUint KSoCurrentConnectStatus =0x406;
enum TSSLConnectStatus {ESSLConnected, ESSLWaitingUserAnswer, ESSLConnectFailed};
const TUint KSSLUserDialogMode = 0x02;   // no dialogs

const TInt KUidSSLProtocolModule = 0x100011b2;
const TInt KUidUnicodeSSLProtocolModule = 0x1000183d;
const TInt KUidSSLv3ProtocolModule = 0x10001699;
const TUint KSockReadFromSSL = 0x10040000;
const TUint KSockWriteFromSSL = 0x10044000;

// A version must be specified when creating an SSL factory
const TUint KSSLMajorVersionNumber=1;
const TUint KSSLMinorVersionNumber=0;
const TUint KSSLBuildVersionNumber=500;

class CSSLSessionStore;
class CSSLSessionState;
class CNifFactory;
class CSSLProviderBase;
class CSymmetricCipher;
class CCryptoFactory;
class CCertFactory;
class CSSLTimers;
class MSSLSocketNotify 				
	{
public:
// NOTE: THESE ARE A SUBSET OF MSocketNotify
	enum TSSLDelete {EDelete,EDetach};
	virtual void SSLDeliver(const TDesC8 &aDesc)=0;
	virtual TUint SSLWrite(const TDesC8 &aDesc,TUint options, TSockAddr* aAddr=NULL)=0;
	virtual void SSLCanSend()=0;
	virtual void SSLConnectComplete()=0;
	virtual void SSLCanClose(TSSLDelete aDelete)=0;
	virtual void SSLError(TInt anError)=0;
	virtual void SSLDisconnectIndication(void)=0;
	virtual void SSLDisconnectIndication(TDesC8& aDisconnectData)=0;
	virtual void SSLDisconnectIndication(TInt aError)=0;
	virtual void SSLIoctlComplete(TDesC8 *aBuf)=0;
	};

class CSSLTimers : public CBase
	{
public:
	virtual ~CSSLTimers();
	static CSSLTimers *NewL();
	void StartSSLTimer(TCallBack aCallBack,TInt aTimeout);
	void StopSSLTimer();
	void DoSSLTimerExpired();
private:
	CSSLTimers();
private:
	TDeltaTimerEntry iSSLTimer;
	TDeltaTimerEntry *iSSLTimerH;
	};

class SSLGlobals
	{
public:
	CObjectConIx *iContainer;
	CObjectCon *iSSLFactories;
	TInt iSSLUnloadTimeout;
	TInt iSecureSocketCount;
	};

class RSSLDialogServer;
class CSSLFactory : public CObject
	{
// Factory base for creating a concrete instance of a CSSLBase
public:	
	CSSLFactory();
	virtual ~CSSLFactory();
	virtual CSSLProviderBase* NewSecureSocketL(MSSLSocketNotify* aParent);
	virtual TInt Open();
	virtual void Close();
	virtual void InitL(RLibrary& aLib, CObjectCon& aCon);
	virtual TVersion Version() const;
//	static void Cleanup(TAny* aObject);
//	static TInt ControlledDelete(TAny* aSSLFactory);
	void SecureSocketShutdown(CSSLProviderBase *aSecureSocket);
	// other public members
	void SetSessionStateL(CSSLSessionState* aState,const TDesC8&);//const TDesC8& aSessionID,const TDesC8& aMasterSecret);
	TPtrC8 GetSession(const TDesC8&,CSSLSessionState*);
	void ConstructL();
private:
	void InitCryptoL();
public:
	RLibrary iLib;
private:
//	RLibrary iCryptLibrary;
//	RLibrary iCertLibrary;
	TDblQue<CSSLProviderBase> iSecureSocketsList;
	TUint iSecureSocketsCount;
	CCryptoFactory *iCryptoF;
#ifdef __USELIBEAY32__
	CCertFactory *iCertF;
#endif
	CSSLSessionStore *iSessStore;
	};

class CSSLProviderBase : public CBase
	{
// ABSTRACT base class for all SSL protocol implementations.
public:
	friend class CSSLFactory;
	enum TCloseType {ENormal,EStopInput,EStopOutput,EImmediate};
	CSSLProviderBase(CSSLFactory& aFactory);
	virtual ~CSSLProviderBase();
	inline void SetNotify(MSSLSocketNotify* aNotify);
public:
// NOTE I'VE COPIED THESE DIRECTLY FROM CServProviderBase
	virtual const TInt GetOption(TUint level,TUint name,TDes8& anOption) =0;
	virtual void Ioctl(TUint level,TUint name,TDes8* anOption)=0;
	virtual void CancelIoctl(TUint aLevel,TUint aName)=0;
	virtual TInt SetOption(TUint level,TUint name,const TDesC8 &anOption)=0;
	virtual TUint Write(const TDesC8& aDesc,TUint options,TSockAddr* anAddr=NULL)=0;
	virtual void Process(RMBufChain& aBuf)=0;
	virtual void Process(const TDesC8 &aDesc)=0;
	virtual TInt ActiveOpen()=0;
	virtual TInt ActiveOpen(const TDesC8& aConnectionData)=0;
	virtual TInt PassiveOpen(TUint aQueSize)=0;
	virtual TInt PassiveOpen(TUint aQueSize,const TDesC8& aConnectionData)=0;
	virtual void Shutdown()=0;
	virtual void Close()=0;
#ifdef __USELIBEAY32__
	virtual void ConstructL(MSSLSocketNotify *aParent,CCryptoFactory *aCr,CCertFactory *aCe)=0;
#else
	virtual void ConstructL(MSSLSocketNotify *aParent)=0;
#endif
	virtual void ConnectCompleted()=0;
public:
	TDblQueLink iLink;
protected:
	CSSLFactory* iFactory;
private:
	MSSLSocketNotify* iSocket;
	};

#endif
