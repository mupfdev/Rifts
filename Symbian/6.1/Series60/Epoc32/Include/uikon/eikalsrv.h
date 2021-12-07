// EIKALSRV.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKALSRV_H__)
#define __EIKALSRV_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

//
// class CEikServAlarmAlertServer
//

class CEikServAppUi;
class MEikServAlarmFactory;
class MEikServAlarm;

class CEikServAlarmAlertSession;

/**
 * @internal
 */
class CEikServAlarmAlertServer : public CServer
	{
public:
	static CEikServAlarmAlertServer* NewL(MEikServAlarmFactory* aAlarmControl);
	~CEikServAlarmAlertServer();
public: // from CServer
	virtual CSharableSession* NewSessionL(const TVersion &aVersion) const;
public: // Internal to Symbian
	IMPORT_C void HandleSwitchOnEvent();
public:
	void TaskKeyPressed();
	inline TBool AlarmAlertIsVisible() const;
	inline void SessionDied();
private:
	CEikServAlarmAlertServer(TInt aPriority);
private:
	CEikServAlarmAlertSession* iSession;
	MEikServAlarmFactory* iAlarmControl;
	};

//
// class CEikServAlarmAlertSession
//

class CEikAlmControlSupervisor;

class CEikServAlarmAlertSession : public CSession
	{
public:
	CEikServAlarmAlertSession(RThread aClient);
	~CEikServAlarmAlertSession();
	void ConstructL(MEikServAlarmFactory* aAlarmControl);
	virtual void ServiceL(const RMessage &aMessage);
	void TaskKeyPressed();
	void HandleSwitchOnEvent();
	inline TBool AlarmAlertIsVisible() const;
private:
	CEikServAlarmAlertServer* AlarmAlertServer() const;
private:
	CEikAlmControlSupervisor* iAlarmSupervisor;
	TBool iVisible;
	};

inline TBool CEikServAlarmAlertServer::AlarmAlertIsVisible() const { return iSession->AlarmAlertIsVisible(); }
inline void CEikServAlarmAlertServer::SessionDied() { iSession=NULL; }
//
inline TBool CEikServAlarmAlertSession::AlarmAlertIsVisible() const { return iVisible; }

#endif
