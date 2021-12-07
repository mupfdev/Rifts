// POPS.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
// 

#if !defined(_IMPP_H__)
#define _IMPP_H__

#include <e32std.h>
#include <e32base.h>    // For CMsgActive, TFileName
#include <imsk.h>		// ImSockets interface - For CImTextServerSession() wrapper.

#include <msvstd.h>

const TInt KImPopSessionPriority = 1;

//
//
//
class CImPop3Settings;
class CPop3IdleTimer;
class CImIAPPreferences;
class CImPop3Session : public CMsgActive
    {
public:
	~CImPop3Session();		// destructor kills socket server
	static CImPop3Session* NewL();

	void Connect(CImPop3Settings* aPopSettings, const CImIAPPreferences& aPrefs,TRequestStatus& aStatus);
	void Quit(TRequestStatus&);
	void Waiting(TRequestStatus&);

	void SetMessageArray(TUint* aIdArray, TUint aNoMessages);
	TUint MessageNo(TMsvId);
	CImTextServerSession* TextServerSession();

	void SetPending();
	TBool IsPending();
	void SetOpNotPending();
	TBool IsConnectedToInternet();

private:
	CImPop3Session();	// constructor
	void ConstructL();

	void DoRunL();
	void DoCancel();
	void DoComplete(TInt&);

    void ChangeStateL();				// the state machine engine
	void ConstructApopL();
	void SetOpPending();
	TInt GetPopError();

private:
	enum				// States of "session" state machine
		{
		EConnectingToPop,
		EWaitingForReply,
		EAuthorisingUser,
		EAuthorisingPass,
		EAuthorisingApop,
		EPopConnected,
		EStopPop,
		ERequestingTLS,
		ESettingTLS,
		ELoggingEvent
		};
private:
	TInt				iState;
	TInt				iNextState;
	TInt				iCompleted;
	TBool				iOpPending;

	TBool				iSocketConnected;

	HBufC8*				iPopApop;
	TPtrC8				iConnectReply;

	CImPop3Settings*	iPopSettings;

	TInt				iNoMessages;
	TUint*				iIdTab;

    CImTextServerSession*			iSocket;
    };

#endif
