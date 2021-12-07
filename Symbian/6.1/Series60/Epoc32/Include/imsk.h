// IMSK.H
// 
// Copyright (c) 1998 Symbian Ltd.  All rights reserved. 
//

#ifndef __IMSK_H__
#define __IMSK_H__

#ifndef __E32BASE_H__
#include <e32base.h>
#endif

#ifndef __ES_SOCK_H__
#include <es_sock.h>
#endif

#ifndef __IN_SOCK_H__
#include <in_sock.h>
#endif

#ifndef __F32FILE_H__
#include <f32file.h>
#endif

#ifndef __MENTACT_H__
#include <mentact.h>
#endif

#ifndef __MIUTLOG_H__
#include <miutlog.h>
#endif

#ifndef __MIUT_ERR_H__
#include <miut_err.h>
#endif

#ifndef __MIUTHDR_H__
#include <miuthdr.h>
#endif

#ifndef __AGENTCLIENT_H__
#include <agentclient.h>
#endif

#ifdef _DEBUG
#define __IMSK_SIMULATION
#endif

// we have scripting enabled in release builds so we can
// run our script based test on arm4 urel
#define __IMSK_SCRIPTING

const TInt EActivePriorityHigh = 1;
const TInt KCarriageLineFeedLength=2;
const TInt KImskIPAddressLen=15;				// Max numeric IP address len = "255.255.255.255" = 15 chars


typedef TBuf8<KImMailMaxBufferSize> TImMailBuffer;

enum TImLineType
	{ 
	ECRLFTerminated, 
	EBufferTooSmall, 
	EReceiveBufferFull,
	EReceiveBufferEmpty
	};


class CImLog;
class CImTextServerScript;
class CImskAutoDisconnectTimer;
class CImskErrorDialog;
class CImIAPPreferences;
class CImConnect;

class CImTextServerSession : public CMsgActive
	{
public:
	enum TImOperationMode{
		EImServerMode,
		EImClientMode
	};

	IMPORT_C static CImTextServerSession *NewL();
	~CImTextServerSession();


	IMPORT_C void QueueConnectL(TRequestStatus &aStatus,const TDesC& anAddressDesc, TInt aPortNum, const CImIAPPreferences& aIAPPreferences, TBool aEnableTimeout = ETrue);

	IMPORT_C void Disconnect();
	IMPORT_C void Disconnect(TRequestStatus &aStatus);
	void TimeOut();


	IMPORT_C const TDesC& LocalName();
	IMPORT_C TInt SetSecurity(TBool aSecurityOn, TBool aUnattendedMode = FALSE);

	// Logging
	IMPORT_C void PerformLogging(TBool aLogging);

	//sends
	IMPORT_C void Send(TRequestStatus &aStatus, const TDesC8& aDesc);
	IMPORT_C void Send(TRequestStatus &aStatus, TRefByValue<const TDesC8> aFmt,...);
	IMPORT_C void SendQueueReceive(TRequestStatus &aStatus, const TDesC8& aDesc);
	IMPORT_C void SendQueueReceive(TRequestStatus &aStatus, TRefByValue<const TDesC8> aFmt,...);

    //receives
	IMPORT_C TImLineType GetCurrentTextLine(TDes8& aDesc);
	IMPORT_C void QueueReceiveNextTextLine(TRequestStatus &aStatus);
	IMPORT_C void ReceiveBinaryData(TRequestStatus &aStatus, TDes8& aDes,TInt aLen);

	IMPORT_C void LogText(const TDesC8& aString);						// write string into log file
	IMPORT_C void LogError(const TDesC8& aString,const TInt aError);		// write string and integer into log file


	IMPORT_C TInt GetIAPValue(TUint32 &aIAP);
	IMPORT_C TInt GetIAPBearer(TUint32 &aBearer);

// Depreciated functions - do not use.
	IMPORT_C void QueueConnect(TRequestStatus &aStatus,const TDesC& anAddressDesc, TInt aPortNum, TBool aEnableTimeout = ETrue);
	IMPORT_C void QueueConnect(TRequestStatus &aStatus,const TDesC& anAddressDesc, TInt aPortNum, const CImIAPPreferences& aIAPPreferences, TCommDbDatabaseType aType, TBool aEnableTimeout = ETrue);
	IMPORT_C void QueueConnect(TRequestStatus& aStatus,const TDesC& anAddressDesc, TInt aPortNum, TCallBack aDisconnectFunction,const TUint32 aIntraddress,TCommDbDatabaseType aType, TBool aEnableTimeout = ETrue);
	IMPORT_C void QueueConnect(TRequestStatus &aStatus,const TDesC& anAddressDesc, TInt aPortNum,const TUint32 aIAPaddress, TCommDbDatabaseType aType, TBool aEnableTimeout = ETrue);
	IMPORT_C void QueueConnect(TRequestStatus& aStatus,const TDesC& anAddressDesc, TInt aPortNum, TCallBack aDisconnectFunction, TBool aEnableTimeout = ETrue);
	IMPORT_C void QueueConnect(TRequestStatus& aStatus,const TDesC& anAddressDesc, TInt aPortNum, TCallBack aDisconnectFunction, const CImIAPPreferences& aIAPPreferences,TCommDbDatabaseType aType, TBool aEnableTimeout = ETrue);
	IMPORT_C TInt Send(const TDesC8& aDesc);
	IMPORT_C TInt Send(TRefByValue<const TDesC8> aFmt,...);
	IMPORT_C TInt SendReceive(const TDesC8& aDesc);
	IMPORT_C TInt Receive(TDes8& rDes);
	IMPORT_C void Receive(TRequestStatus &aStatus, TDes8& rDes);
	IMPORT_C static CImTextServerSession *NewLC (TImOperationMode aMode, RSocketServ &aServerServ);
	IMPORT_C static CImTextServerSession *NewL(RSocketServ &aServerServ);

private:
	CImTextServerSession();
	void ConstructL();

	TInt Open();
	void Close();

	void CreateLogFile(TInt aPortNum);
	void OpenScriptFile(TInt aPortNum);

	void DoRunL();
	void DoComplete(TInt& aStatusValue);						// Cleanup code
	void DoCancel();

	// these called from DoRunL;
	void SocketConnect();
	void DoConnectedToSocket();
	void DoQueueConnect();

	void RealReceive(TDes8& aDesc);
	void RealSend(const TDesC8& aDesc);


#if defined(__IMSK_SIMULATION)
	void ReadNextPeriod();
	TUint32 GetTokenValue(TInt aTokenLen, const TPtrC8& aBuffer);
	TBool IsSuspended();	
	TBool SuspendPeriodSet();
	void ResetSuspendPeriod();
	void SetAfterTimer();
	TInt ReadConfigNum(const TDesC& aName);
#endif

	enum TImSocketState
		{
		EImClosed, 
		EImResolve, 
		EImConnect,   
		EImSendReceive,
		EImDialUsingOverride
		};

	enum TImSendReceiveState
		{ 
		EImInactive, 
		EImSending,
		EImReceiving, 
		EImReceivingBinaryData,
		EImSendingQueueReceive,
		EImSuspended,          //used when we are in a simulated GPRS suspend.
		};

	enum TImSecurityState
		{
		EImSecurityStateOff,
		EImSecurityStateOn,
		EImSecurityStateFailed
		};
private:
	RSocket							iSocket;
	RSocketServ						iServ;
	RHostResolver					iHostResolver;

	TBool							iIAPCached;  // true if the above value can be used.

	TNameEntry						iHostent;
	TInt							iPortNum;
	TPtrC							iAddressDesc;

	TImMailBuffer					iReceive;
	TSockXfrLength					iLen;
	TImSocketState					iState;
	TImSendReceiveState				iSendReceive;

	HBufC8*							iBuffer;
	TImLineType						iCurrentLineType;

	CImLog*							iLog;
	TBuf<KImskIPAddressLen>			iLocalName;


	TImSecurityState				iSecurityState;
	const CImIAPPreferences*		iIAPPreferences;

	CImConnect*						iConnect;

	TDes8*							iReceiveData; // buffer we just recieved data into

	TUint32 iCurrentIAPcache;

	HBufC8*							iSentData;

	TBool							iPerformLogging;


#ifdef __IMSK_SCRIPTING
	CImTextServerScript*			iScript;
#endif

#if defined(__IMSK_SIMULATION)

	RFs								iFs;


	TUint32							iScriptedIAP; // value to return for iap when scripting
	TUint32							iBearerIAP; // value to return for bearer when scripting


	TImSendReceiveState             iSuspendedState;
	
	RTimer							iSuspendTimer;

	RFile							iGprsFile;

	TBool							iGprsConfigExists;

	TInt							iCfgFilePos;	

	TTime							iLastSuspend;	// time last suspension took place
													// in universal time

	TTimeIntervalSeconds 			iStart;		// number of seconds since last delay
												// before the following delay occurs.
												// if 0 no suspend is required.
	TTimeIntervalSeconds 			iDuration;	// how long to delay. If 0 no suspend is
												// required
	TBool							iRepeat;	// repeat the above delay for an 
												// infinite period

	HBufC8*							iSendData; // suspended data 

#endif // __IMSK_SIMULATION
	};


#endif
