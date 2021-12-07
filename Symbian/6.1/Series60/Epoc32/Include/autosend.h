////////////////////////////////////////////////////////////////////////////////
//
//	AUTOSEND.H
//
//	Copyright © Symbian Limited 2001
//
////////////////////////////////////////////////////////////////////////////////

#ifndef AUTOSEND_H_
#define AUTOSEND_H_

const TInt KDefaultPriority = CActive::EPriorityStandard;

_LIT(KMsvWinsAutoSendThreadName, "AutoSend");

class CClientMtmRegistry;

////////////////////////////////////////////////////////////////////////////////
//
//	Local Function Declarations
//
////////////////////////////////////////////////////////////////////////////////

void Execute(const TMsvId aDestinationId);
void DoExecuteL(const TMsvId aDestinationId);

////////////////////////////////////////////////////////////////////////////////
//
//	CProgressTimer Declaration
//
////////////////////////////////////////////////////////////////////////////////

class CAutoSendProgressTimer : public CTimer
	{
public:
	static CAutoSendProgressTimer* NewL(CMsvOperation& aOperation, const TTimeIntervalMicroSeconds32& aPollInterval);
	void Start();
	~CAutoSendProgressTimer();
	
private:
	CAutoSendProgressTimer(CMsvOperation& aOperation, const TTimeIntervalMicroSeconds32& aPollInterval);
	void RunL();
	CMsvOperation& iOperation;
	TTimeIntervalMicroSeconds32 iPollInterval;
	};

////////////////////////////////////////////////////////////////////////////////
//
//	CAutoSend Declaration
//
////////////////////////////////////////////////////////////////////////////////

class CImAutoSend : public MMsvSessionObserver, CActive
	{
public:	
	static CImAutoSend* StartLC(const TMsvId aDestinationId);
	~CImAutoSend();

	void HandleSessionEventL(MMsvSessionObserver::TMsvSessionEvent /*aEvent*/, TAny* /*aArg1*/, TAny* /*aArg2*/, TAny* /*aArg3*/) {};
	TBool IsSendActive() {return IsActive();}

private:

	CImAutoSend(const TMsvId aDestinationId);
	void ConstructL();

	void DoCancel();
	void RunL();

	void CallMtmL();

#ifndef NO_AUTOSEND_LOGGING
	void FLog(const TDesC& buf);
	void FLog(TRefByValue<const TDesC> aFormat, ...);
#endif

private:
	CMsvSession*			iSession;
	CMsvOperation*			iOperation;
	CAutoSendProgressTimer*	iTimer;
	TMsvId					iDestinationId;
	};

#endif