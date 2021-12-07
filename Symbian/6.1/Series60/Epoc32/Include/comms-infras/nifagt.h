// NIFAGT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//
// Agent APIs
//

#if !defined(__NIFAGT_H__)
#define __NIFAGT_H__

#ifndef __NIFMAN_H__
#include <nifman.h>
#endif

#ifndef __NIFPRVAR_H__
#include <comms-infras\nifprvar.h>
#endif

// Agent classes

class CNifAgentBase;
class CNifAgentRef;
class CNifAgentFactory : public CNifFactory
	{
friend class CNifAgentRef;
protected:
	virtual CNifAgentBase *NewAgentL(const TDesC& aName)=0;
	virtual TInt Info(TNifAgentInfo& aInfo, TInt aIndex) const =0;
	};

class MNifAgentNotify
	{
public:
	virtual void ConnectComplete(TInt aStatus)=0;
	virtual void ReconnectComplete(TInt aStatus)=0;
	virtual void AuthenticateComplete(TInt aStatus)=0;
	virtual void ServiceStarted()=0;
	virtual void ServiceClosed()=0;
	virtual void DisconnectComplete()=0;
	virtual void AgentProgress(TInt aStage, TInt aError)=0;
	virtual TInt Notification(TAgentToNifEventType aEvent, TAny* aInfo=NULL)=0;
	virtual TInt IncomingConnectionReceived() =0;		/* needs to be called by the agent when it gets 
	an incoming call so that agent can wait for an incoming and do an outgoing at the 
	same time, i.e. it waits for the incoming without NifMan's knowledge. */
	};

class CNifCompanionSession;
class CNifAgentBase : public CBase
	{
friend class CNifAgentRef;
public:
	IMPORT_C CNifAgentBase();

	virtual void Info(TNifAgentInfo& aInfo) const =0;
	virtual void Connect(TAgentConnectType aType)=0;
	virtual void Connect(TAgentConnectType aType, CCommDbOverrideSettings& aOverrideSettings)=0;
	virtual void CancelConnect()=0;
	virtual void Reconnect()=0;
	virtual void CancelReconnect()=0;
	virtual void Authenticate(TDes& aUsername, TDes& aPassword)=0;
	virtual void CancelAuthenticate()=0;
	virtual void Disconnect(TInt aReason)=0;
	virtual TInt GetExcessData(TDes8& aBuffer)=0;
	virtual TInt ReadInt(const TDesC& aField, TUint32& aValue)=0;						
	virtual TInt WriteInt(const TDesC& aField, TUint32 aValue)=0;						
	virtual TInt ReadDes(const TDesC& aField, TDes8& aValue)=0;						
	virtual TInt WriteDes(const TDesC& aField, const TDesC8& aValue)=0;			
	virtual TInt ReadDes(const TDesC& aField, TDes16& aValue)=0;						
	virtual TInt WriteDes(const TDesC& aField, const TDesC16& aValue)=0;			
	virtual TInt ReadBool(const TDesC& aField, TBool& aValue)=0;					
	virtual TInt WriteBool(const TDesC& aField, TBool aValue)=0;					
	virtual TInt Notification(TNifToAgentEventType aEvent, TAny* aInfo)=0;
	virtual TInt IncomingConnectionReceived() =0;
	virtual void GetLastError(TInt& aError) =0;
    virtual CNifCompanionSession *NewCompanionSessionL(CSession& aSession)=0;

protected:
	MNifAgentNotify* iNotify;
	};

class CNifCompanionSession : public CBase
	{
public:
	enum TCompanionFunction{ ENifStart, ECompanionFirst=100 };

	inline const CSession& Session() const;
	inline const RMessage& Message() const;
	virtual void ServiceL(const RMessage& aMessage) =0;
protected:
	IMPORT_C CNifCompanionSession(CSession& aSession);
private:
	CSession* iSession;
	};

// Inlines

inline const CSession& CNifCompanionSession::Session() const
	{ return *iSession; }
inline const RMessage& CNifCompanionSession::Message() const
	{ return iSession->Message(); }

#endif



