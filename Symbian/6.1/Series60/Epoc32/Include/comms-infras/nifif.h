// NIFIF.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Interface APIs
//

#if !defined(__NIFIF_H__)
#define __NIFIF_H__

#ifndef __NIFMAN_H__
#include <nifman.h>
#endif

#ifndef __NIFPRVAR_H__
#include <comms-infras\nifprvar.h>
#endif

const TUint KNifIfIsBase           = 0x00000001;
const TUint KNifIfIsLink           = 0x00000002;
const TUint KNifIfUsesNotify       = 0x00000004;
const TUint KNifIfCreatedByFactory = 0x00000008;
const TUint KNifIfCreatedByLink    = 0x00000010;
const TUint KNifIfCreatedAlone     = 0x00000020;
const TUint KNifIfCreatesBinder    = 0x00000040;

// Interface classes

class TNifIfInfo
	{
public:
	TUint iProtocolSupported;
	TUint iFlags;
	TVersion iVersion;
	TName iName;
	};

class CNifIfFactory : public CNifFactory
	{
friend class CNifMan;
protected:
	virtual CNifIfBase *NewInterfaceL(const TDesC& aName)=0;
	virtual TInt Info(TNifIfInfo& aInfo, TInt aIndex) const=0;
	};

class MNifIfNotify
	{
public:
	enum TAction { EReconnect, ECallBack, EDisconnect };					

public:
//    virtual void LinkLayerDown(TInt aReason, TBool aReconnect)=0;
    virtual void LinkLayerDown(TInt aReason, TAction aAction)=0;		
	virtual void LinkLayerUp()=0;
    virtual void NegotiationFailed(CNifIfBase* aIf, TInt aReason)=0;
    virtual TInt Authenticate(TDes& aUsername, TDes& aPassword)=0;
    virtual void CancelAuthenticate()=0;
	virtual TInt GetExcessData(TDes8& aBuffer)=0;
	virtual TInt ReadInt(const TDesC& aField, TUint32& aValue)=0;				
    virtual TInt WriteInt(const TDesC& aField, TUint32 aValue)=0;				
    virtual TInt ReadDes(const TDesC& aField, TDes8& aValue)=0;				
    virtual TInt ReadDes(const TDesC& aField, TDes16& aValue)=0;				
    virtual TInt WriteDes(const TDesC& aField, const TDesC8& aValue)=0;	
	virtual TInt WriteDes(const TDesC& aField, const TDesC16& aValue)=0;	
	virtual TInt ReadBool(const TDesC& aField, TBool& aValue)=0;			
    virtual TInt WriteBool(const TDesC& aField, TBool aValue)=0;			
	virtual void IfProgress(TInt aStage, TInt aError)=0;
	virtual void OpenRoute()=0;
	virtual void CloseRoute()=0;
	virtual TInt Notification(TNifToAgentEventType aEvent, void * aInfo = NULL)=0;  
	};

class CNifAgentRef;
class CNifIfLink;
class CNifIfBase : public CBase
	{
friend class CNifAgentRef;
public:
	IMPORT_C CNifIfBase(CNifIfFactory& aFactory);
	IMPORT_C CNifIfBase();
	IMPORT_C ~CNifIfBase();
	IMPORT_C static void Cleanup(TAny* aIf);
	IMPORT_C virtual void Open();
	IMPORT_C virtual void Close();
	IMPORT_C virtual void BindL(TAny *aId);
	IMPORT_C virtual TInt State();
	IMPORT_C virtual TInt Control(TUint aLevel,TUint aName,TDes8& aOption, TAny* aSource=0);
	virtual void Info(TNifIfInfo& aInfo) const =0;
	virtual TInt Send(RMBufChain& aPdu, TAny* aSource=0)=0;
	virtual TInt Notification(TAgentToNifEventType aEvent, void * aInfo)=0;  
	inline MNifIfNotify* Notify() const;

protected:
	IMPORT_C CNifIfBase(CNifIfLink& aLink);
	TInt iRefCount;
	CNifIfFactory* iFactory;
	MNifIfNotify* iNotify;
	};

class CNifIfLink : public CNifIfBase
	{

public:
	IMPORT_C CNifIfLink(CNifIfFactory& aFactory);
	IMPORT_C virtual void AuthenticateComplete(TInt aResult);
	virtual TInt Start()=0;
//	virtual void Stop(TInt aReason)=0;
	virtual void Stop(TInt aReason, MNifIfNotify::TAction aAction)=0;		
	virtual CNifIfBase* GetBinderL(const TDesC& aName)=0;
	};

class MNifIfUser
	{
public:
	virtual void IfUserBindFailure(TInt aResult, TAny* aId)=0;
	virtual void IfUserNewInterfaceL(CNifIfBase* aIf, TAny* aId)=0;
	virtual void IfUserInterfaceDown(TInt aResult, CNifIfBase* aIf)=0;
	virtual void IfUserOpenNetworkLayer()=0;
	virtual void IfUserCloseNetworkLayer()=0;
	virtual CProtocolBase* IfUserProtocol()=0;

	// 22/5/02 - added argument to allow layer 3 protocol to distinguish between nifs when
	// receiving this upcall - needed for multihoming
	// Default value of NULL to maintain SC, and allow layer 3 protocol to distinguish new
	// and old versions of Nifman that do/don't support multihoming
	virtual TBool IfUserIsNetworkLayerActive(CNifIfBase* aIf=NULL)=0;
	};
const TUint KNifOptLevel = 0x191;
const TUint KNifOptGetNifIfUser = 1|KSocketInternalOptionBit;
const TUint KNifOptStartInterface = 1;
const TUint KNifOptStopInterface = 2;
const TUint KNifOptInterfaceProgress = 3;
typedef TPckgBuf<MNifIfUser*> TNifIfUser;

const TInt KUidNifmanAgent     = 0x10000388;
const TInt KUidUnicodeNifmanAgent = 0x10003d39;
const TInt KUidNifmanInterface = 0x10000389;
const TInt KUidUnicodeNifmanInterface = 0x10003d3a;
//const TInt KUidEsockIniCategory  = 0x1000047A;
//const TInt KUidUnicodeEsockIniCategory  = 0x10003d3b;

// Inlines

inline MNifIfNotify* CNifIfBase::Notify() const
	{ return iNotify; }

#endif
