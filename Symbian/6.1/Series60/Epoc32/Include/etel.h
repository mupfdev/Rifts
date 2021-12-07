// ETEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__ETEL_H__)
#define __ETEL_H__

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

#if !defined (__C32COMM_H__)
#include <C32COMM.H>
#endif

#if !defined(__D32COMM_H__)
#include <D32COMM.H>
#endif

#if !defined(__FAXDEFN_H)
#include <FAXDEFN.H>
#endif

const TUint KEtelMajorVersionNumber=1;
const TUint KEtelMinorVersionNumber=0;
const TUint KEtelBuildVersionNumber=606;

IMPORT_C void PanicClient(TInt aFault);

//
// Etel Core Error Definitions
//
const TInt KErrEtelCoreBase = -2000;

const TInt KErrEtelNotCallOwner=KErrEtelCoreBase;
const TInt KErrEtelDuplicatePhoneName=KErrEtelCoreBase-1;
const TInt KErrEtelAlreadyCallOwner=KErrEtelCoreBase-2;
const TInt KErrEtelNoCarrier=KErrEtelCoreBase-3;
const TInt KErrEtelBusyDetected=KErrEtelCoreBase-4;
const TInt KErrEtelNoClientInterestedInThisCall=KErrEtelCoreBase-5;
const TInt KErrEtelInitialisationFailure=KErrEtelCoreBase-6;
const TInt KErrEtelCallNotActive=KErrEtelCoreBase-7;
const TInt KErrEtelNoAnswer=KErrEtelCoreBase-8;
const TInt KErrEtelNoDialTone=KErrEtelCoreBase-9;
const TInt KErrEtelConfigPortFailure=KErrEtelCoreBase-10;
const TInt KErrEtelFaxChunkNotCreated=KErrEtelCoreBase-11;
const TInt KErrEtelNotFaxOwner=KErrEtelCoreBase-12;
const TInt KErrEtelPortNotLoanedToClient=KErrEtelCoreBase-13;
const TInt KErrEtelWrongModemType=KErrEtelCoreBase-14;
const TInt KErrEtelUnknownModemCapability=KErrEtelCoreBase-15;
const TInt KErrEtelAnswerAlreadyOutstanding=KErrEtelCoreBase-16;
const TInt KErrEtelModemNotDetected=KErrEtelCoreBase-17;
const TInt KErrEtelModemSettingsCorrupt=KErrEtelCoreBase-18;
const TInt KErrEtelPortAlreadyLoaned=KErrEtelCoreBase-19;
const TInt KErrEtelCallAlreadyActive=KErrEtelCoreBase-20;

//
//
// RTelSubSessionBase
//
//
class CPtrHolder;
class RTelSubSessionBase : public RSubSessionBase
	{
public:
	inline RSessionBase& SessionHandle() const;
	inline void SetSessionHandle(RSessionBase& aSession);
	inline TInt SubSessionHandle();

	enum TReqPriorityType
		{
		EIsNotaPriorityRequest,
		EIsaPriorityRequest
		};
protected:

	IMPORT_C RTelSubSessionBase();
	IMPORT_C TInt Blank(const TInt aIpc,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Blank(const TInt aIpc,TRequestStatus& aStatus,TReqPriorityType aType = EIsNotaPriorityRequest) const;

	IMPORT_C TInt Set(const TInt aIpc,const TDesC8& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Set(const TInt aIpc,TRequestStatus& aStatus,const TDesC8& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C TInt Get(const TInt aIpc,TDes8& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Get(const TInt aIpc,TRequestStatus& aStatus,TDes8& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;

	IMPORT_C TInt Set(const TInt aIpc,const TDesC8& aDes1,const TDesC8& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Set(const TInt aIpc,TRequestStatus& aStatus,const TDesC8& aDes1,const TDesC8& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C TInt Get(const TInt aIpc,TDes8& aDes1,TDes8& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Get(const TInt aIpc,TRequestStatus& aStatus,TDes8& aDes1,TDes8& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	
	IMPORT_C TInt Set(const TInt aIpc,const TDesC16& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Set(const TInt aIpc,TRequestStatus& aStatus,const TDesC16& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C TInt Get(const TInt aIpc,TDes16& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Get(const TInt aIpc,TRequestStatus& aStatus,TDes16& aDes,TReqPriorityType aType = EIsNotaPriorityRequest) const;

	IMPORT_C TInt Set(const TInt aIpc,const TDesC16& aDes1,const TDesC16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Set(const TInt aIpc,TRequestStatus& aStatus,const TDesC16& aDes1,const TDesC16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C TInt Set(const TInt aIpc,const TDesC8& aDes1,const TDesC16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Set(const TInt aIpc,TRequestStatus& aStatus,const TDesC8& aDes1,const TDesC16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;

	IMPORT_C TInt Get(const TInt aIpc,TDes16& aDes1,TDes16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Get(const TInt aIpc,TRequestStatus& aStatus,TDes16& aDes1,TDes16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C TInt Get(const TInt aIpc,TDes8& aDes1,TDes16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void Get(const TInt aIpc,TRequestStatus& aStatus,TDes8& aDes1,TDes16& aDes2,TReqPriorityType aType = EIsNotaPriorityRequest) const;

	IMPORT_C void SetAndGet(const TInt aIpc, TRequestStatus& aStatus, const TDesC8& aDes1, TDes8& aDes2, TReqPriorityType aType = EIsNotaPriorityRequest) const;
	IMPORT_C void SetAndGet(const TInt aIpc, TRequestStatus& aStatus, TDes8& aDes1, const TDesC16& aDes2, TReqPriorityType aType = EIsNotaPriorityRequest) const;

	IMPORT_C TInt CancelReq(const TInt aIpc,const TInt aIpcToCancel) const;
	IMPORT_C TInt CancelSubSession() const;
private:
	RTelSubSessionBase(const RTelSubSessionBase& aTelSubSessionBase);
	RSessionBase* iTelSession;
protected:
	CPtrHolder* iPtrHolder;
	};

//
//
// RFax
//
//
class RCall;
class RFax : public RTelSubSessionBase
	{
public:
	IMPORT_C RFax();
	IMPORT_C TInt Open(RCall& aCall);
	IMPORT_C void Close();

//
// Read,Write and Wait for Page End
//
	IMPORT_C void Read(TRequestStatus& aStatus,TDes8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus,const TDesC8& aDes);
	IMPORT_C void WaitForEndOfPage(TRequestStatus& aStatus) const;
	IMPORT_C TInt TerminateFaxSession() const;
//
// Progress Information
//
	struct TProgress
		{
		TTime iLastUpdateTime;
		TBuf<20> iAnswerback;

		TFaxPhase iPhase;
		TFaxResolution iResolution;
		TFaxCompression iCompression;
		TInt iECM;

		TInt iPage;
		TInt iLines;
		TInt iSpeed;
		};

	IMPORT_C TInt GetProgress(TProgress& aProgress);
private:
	TProgress* iProgressPtr;
	RChunk iChunk;
protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void Destruct();
	};

//
//
// RCall
//
//
class RTelServer;
class RPhone;
class RLine;
class RCall : public RTelSubSessionBase
	{
public:
	IMPORT_C RCall();
	IMPORT_C TInt OpenNewCall(RTelServer& aServer,const TDesC& aName,TDes& aNewName);
	IMPORT_C TInt OpenNewCall(RTelServer& aServer,const TDesC& aName);
	IMPORT_C TInt OpenNewCall(RPhone& aPhone,const TDesC& aName,TDes& aNewName);
	IMPORT_C TInt OpenNewCall(RPhone& aPhone,const TDesC& aName);
	IMPORT_C TInt OpenNewCall(RLine& aLine,TDes& aNewName);
	IMPORT_C TInt OpenNewCall(RLine& aLine);
	IMPORT_C TInt OpenExistingCall(RTelServer& aServer,const TDesC& aName);
	IMPORT_C TInt OpenExistingCall(RPhone& aPhone,const TDesC& aName);
	IMPORT_C TInt OpenExistingCall(RLine& aLine,const TDesC& aName);
	IMPORT_C void Close();

//
// Call Status
//
	enum TStatus
		{
		EStatusUnknown,
		EStatusIdle,
		EStatusDialling,
		EStatusRinging,
		EStatusAnswering,
		EStatusConnecting,
		EStatusConnected,
		EStatusHangingUp
		};

	IMPORT_C TInt GetStatus(TStatus& aStatus) const;

//
// Call Caps
//
	enum TCapsEnum
		{
		KCapsData=0x00000001,
		KCapsFax=0x00000002,
		KCapsVoice=0x00000004,
		KCapsDial=0x00000008,
		KCapsConnect=0x00000010,
		KCapsHangUp=0x00000020,
		KCapsAnswer=0x00000040,
		KCapsLoanDataPort=0x00000080,
		KCapsRecoverDataPort=0x00000100
		};

	struct TCaps
		{
		TUint iFlags;
		};

	IMPORT_C TInt GetCaps(TCaps& aCaps) const;
	IMPORT_C void NotifyCapsChange(TRequestStatus& aStatus, TCaps& aCaps);
	IMPORT_C void NotifyCapsChangeCancel() const;

//
// Bearer Service Information
//
	enum TBearerCaps
		{
		KBearerCapsCompressionV42bis=0x00000001,
		KBearerCapsCompressionMNP5=0x00000002,
		KBearerCapsCompressionNone=0x00000004,
		KBearerCapsProtocolLAPM=0x00000008,
		KBearerCapsProtocolALT_CELLULAR=0x00000010,
		KBearerCapsProtocolALT=0x00000020,
		KBearerCapsProtocolNone=0x00000040,
		KBearerCapsCompressionUnknown=0x00000080,
		KBearerCapsProtocolUnknown=0x00000100
		};

	enum TCallBearerSpeed
		{
		EBearerData57600,
		EBearerData33600,
		EBearerData31200,
		EBearerData19200,
		EBearerData14400,
		EBearerData12000,
		EBearerData9600,
		EBearerData7200,
		EBearerData4800,
		EBearerData2400,
		EBearerData1200,
		EBearerData75_1200,
		EBearerData1200_75,
		EBearerData300,
		EBearerDataUnknown
		};

	struct TBearerService
		{
		TUint32 iBearerCaps;
		TCallBearerSpeed iBearerSpeed;
		};

 	IMPORT_C TInt GetBearerServiceInfo(TBearerService& aBearerService) const;

//
// Notifications
//
	enum THookStatus
		{
		EHookStatusOff,
		EHookStatusOn,
		EHookStatusUnknown
		};

	class TCallInfo
		{
	public:
		IMPORT_C TCallInfo();
		TName iCallName;
		TName iLineName;
		THookStatus iHookStatus;
		TStatus iStatus;
		TTimeIntervalSeconds iDuration;
		};
	
	IMPORT_C TInt GetInfo(TCallInfo& aCallInfo) const;
	IMPORT_C void NotifyHookChange(TRequestStatus& aStatus,THookStatus& aHookStatus);
	IMPORT_C void NotifyHookChangeCancel() const;
	IMPORT_C void NotifyStatusChange(TRequestStatus& aStatus,TStatus& aCallStatus);
	IMPORT_C void NotifyStatusChangeCancel() const;
	IMPORT_C void NotifyCallDurationChange(TRequestStatus& aStatus,TTimeIntervalSeconds& aTime);
	IMPORT_C void NotifyCallDurationChangeCancel() const;

//
// Duration of call
//
	IMPORT_C TInt GetCallDuration(TTimeIntervalSeconds& aTime) const;
//
// Connecting and Disconnecting
//
	typedef TDesC TTelNumberC;
	IMPORT_C TInt Dial(const TTelNumberC& aTelNumber) const;
	IMPORT_C TInt Dial(const TDesC8& aCallParams,const TTelNumberC& aTelNumber) const;
	IMPORT_C void Dial(TRequestStatus& aStatus,const TTelNumberC& aTelNumber);
	IMPORT_C void Dial(TRequestStatus& aStatus,const TDesC8& aCallParams,const TTelNumberC& aTelNumber);
	IMPORT_C void DialCancel() const;
	IMPORT_C TInt Connect() const;
	IMPORT_C TInt Connect(const TDesC8& aCallParams) const;
	IMPORT_C void Connect(TRequestStatus& aStatus);
	IMPORT_C void Connect(TRequestStatus& aStatus,const TDesC8& aCallParams);
	IMPORT_C void ConnectCancel() const;
	IMPORT_C TInt AnswerIncomingCall() const;
	IMPORT_C TInt AnswerIncomingCall(const TDesC8& aCallParams) const;
	IMPORT_C void AnswerIncomingCall(TRequestStatus& aStatus);
	IMPORT_C void AnswerIncomingCall(TRequestStatus& aStatus,const TDesC8& aCallParams);
	IMPORT_C void AnswerIncomingCallCancel() const;
	IMPORT_C TInt HangUp() const;
	IMPORT_C void HangUp(TRequestStatus& aStatus) const;
	IMPORT_C void HangUpCancel() const;

//
// Call Data Access
//
	struct  TCommPort
		{
		TFileName iCsy;
		TName iPort;
		};

	IMPORT_C TInt LoanDataPort(TCommPort& aDataPort) const;
	IMPORT_C void LoanDataPort(TRequestStatus& aStatus,TCommPort& aDataPort);
	IMPORT_C void LoanDataPortCancel() const;
	IMPORT_C TInt RecoverDataPort() const;

//
// Call Ownership manipulation
//
	enum TOwnershipStatus
		{
		EOwnershipUnowned,
		EOwnershipOwnedByAnotherClient,		// not the priority client
		EOwnershipOwnedByThisClient,
		EOwnershipThisIsPriorityClient		// not owned by this (the priority) client
		};

	IMPORT_C TInt TransferOwnership() const;
	IMPORT_C void AcquireOwnership(TRequestStatus& aStatus) const;
	IMPORT_C void AcquireOwnershipCancel() const;
	IMPORT_C TInt GetOwnershipStatus(TOwnershipStatus& aOwnershipStatus) const;
	//
//
// Get and Set Call Parameters
//
	enum TMonitorSpeakerControl
		{
		EMonitorSpeakerControlAlwaysOff,
		EMonitorSpeakerControlOnUntilCarrier,
		EMonitorSpeakerControlAlwaysOn,
		EMonitorSpeakerControlOnExceptDuringDialling,
		EMonitorSpeakerControlUnknown
		};

	enum TMonitorSpeakerVolume
		{
		EMonitorSpeakerVolumeOff,
		EMonitorSpeakerVolumeLow,
		EMonitorSpeakerVolumeMedium,
		EMonitorSpeakerVolumeHigh,
		EMonitorSpeakerVolumeUnknown
		};

	enum TWaitForDialTone
		{
		EDialToneWait,
		EDialToneNoWait
		};

	class TCallParams
		{
	public:
		IMPORT_C TCallParams();
		IMPORT_C TCallParams(TMonitorSpeakerControl aSpeakerControl,
							 TMonitorSpeakerVolume aSpeakerVolume,
							 TUint aInterval,
							 TWaitForDialTone aWaitForDialTone);
		IMPORT_C TInt ExtensionId();
		IMPORT_C TBool IsDefault();
		TMonitorSpeakerControl iSpeakerControl;
		TMonitorSpeakerVolume iSpeakerVolume;
		TUint iInterval;
		TWaitForDialTone iWaitForDialTone;
	protected:
		TBool iIsDefault;
		TInt iExtensionId;
		};

	typedef TPckg<TCallParams> TCallParamsPckg;

	IMPORT_C TInt GetCallParams(TDes8& aParams) const;

//
// Fax Settings
//
	enum TFaxMode
		{
		ETransmit,
		EReceive
		};

	enum TFaxRetrieveType
		{
		EFaxOnDemand,
		EFaxPoll
		};

	enum TConstants
		{
		KFaxIdUserNameMaxSize=20
		};

	struct TFaxSessionSettings
		{
		TFaxMode iMode;
		TFaxRetrieveType iFaxRetrieveType;
		TFaxClass iFaxClass;
		TBuf<KFaxIdUserNameMaxSize> iFaxId;
		TInt iMaxSpeed;
		TInt iMinSpeed;
		TInt iPreferredECM;
		TInt iFaxOnDemandDelay;
		// Tx Settings
		TFaxResolution iTxResolution;
		TFaxCompression iTxCompression;
		TInt iTxPages;
		// Rx Settings
		TFaxResolution iRxResolution;
		TFaxCompression iRxCompression;
		};

	IMPORT_C TInt GetFaxSettings(TFaxSessionSettings& aSettings) const;
	IMPORT_C TInt SetFaxSettings(const TFaxSessionSettings& aSettings) const;

//
// Retrieval of call objects' reference count
//
	IMPORT_C TInt ReferenceCount() const;

protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void Destruct();
	};

//
//
// RLine
//
//
class RPhone;
class RLine : public RTelSubSessionBase
	{
public:
	IMPORT_C RLine();
	IMPORT_C TInt Open(RPhone& aPhone,const TDesC& aName);
	IMPORT_C TInt Open(RTelServer& aServer,const TDesC& aName);
	IMPORT_C void Close();

//
// Caps
//
	enum TCapsFlags
		{
		KCapsData=0x00000001,
		KCapsFax=0x00000002,
		KCapsVoice=0x00000004,
		KCapsEventIncomingCall=0x00010000,
		};

	struct TCaps
		{
		TUint iFlags;
		};

	IMPORT_C TInt GetCaps(TCaps& aCaps) const;
	IMPORT_C void NotifyCapsChange(TRequestStatus& aStatus, TCaps& aCaps);
	IMPORT_C void NotifyCapsChangeCancel() const;

//
// Line and Hook Status
//
	IMPORT_C TInt GetStatus(RCall::TStatus& aStatus) const;
	IMPORT_C TInt GetHookStatus(RCall::THookStatus& aHookStatus) const;

//
// Call enumeration and Information
//
	struct TCallInfo
		{
		TName iCallName;
		RCall::TStatus iStatus;
		TUint32 iCallCapsFlags;
		};

	IMPORT_C TInt EnumerateCall(TInt& aCount) const;
	IMPORT_C TInt GetCallInfo(TInt aIndex,TCallInfo& aCallInfo) const;
//
//	General line notification information
//
	class TLineInfo
		{
	public:
		IMPORT_C TLineInfo();
		RCall::THookStatus iHookStatus;
		RCall::TStatus iStatus;
		TName iNameOfLastCallAdded;
		TName iNameOfCallForAnswering;	// if an incoming call occurs, this contains the name
										// of the call to answer it on.
		};
	
//
// Notifications
//
	IMPORT_C TInt GetInfo(TLineInfo& aLineInfo) const;
	IMPORT_C void NotifyIncomingCall(TRequestStatus& aStatus, TName& aName);
	IMPORT_C void NotifyIncomingCallCancel() const;
	IMPORT_C void NotifyHookChange(TRequestStatus& aStatus,RCall::THookStatus& aHookStatus);
	IMPORT_C void NotifyHookChangeCancel() const;
	IMPORT_C void NotifyStatusChange(TRequestStatus& aStatus,RCall::TStatus& aLineStatus);
	IMPORT_C void NotifyStatusChangeCancel() const;
	IMPORT_C void NotifyCallAdded(TRequestStatus& aStatus,TName& aName);
	IMPORT_C void NotifyCallAddedCancel() const;
protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void Destruct();
	};

//
//
// RPhone
//
//
class RTelServer;
class RPhone : public RTelSubSessionBase
	{
public:
	IMPORT_C RPhone();
	IMPORT_C TInt Open(RTelServer& aSession,const TDesC& aName);
	IMPORT_C void Close();

//
// Initialisation
//
	IMPORT_C TInt Initialise();
	IMPORT_C void Initialise(TRequestStatus& aStatus);
	IMPORT_C void InitialiseCancel();

//
// Caps
//
	enum TCapsFlags
		{
		KCapsUnknown=0x00000001,
		KCapsData=0x00000002,
		KCapsFaxClassOne=0x0000004,
		KCapsFaxClassOnePointZero=0x0000008,
		KCapsFaxClassTwo=0x00000010,
		KCapsFaxClassTwoPointZero=0x00000020,
		KCapsFaxClassTwoPointOne=0x00000040,
		KCapsVoice=0x00000080,
		KCapsEventModemDetection=0x00010000,
		KCapsStealCommPort=0x00020000
		};

	struct TCaps
		{
		TUint iFlags;
		};

	IMPORT_C TInt GetCaps(TCaps& aCaps) const;
	IMPORT_C void NotifyCapsChange(TRequestStatus& aStatus, TCaps& aCaps);
	IMPORT_C void NotifyCapsChangeCancel() const;

//
// Status
//
	enum TMode
		{
		EModeUnknown,
		EModeIdle,
		EModeEstablishingLink,
		EModeOnlineData,
		EModeOnlineCommand
		};

	enum TModemDetection
		{
		EDetectedPresent,
		EDetectedNotPresent,
		EDetectedUnknown
		};

	struct TStatus
		{
		TModemDetection iModemDetected;
		TMode iMode;
		};

	IMPORT_C TInt GetStatus(TStatus& aStatus) const;

//
// Line Enumeration and Information
//
	struct TLineInfo
		{
		RCall::TStatus iStatus;
		TUint32 iLineCapsFlags;
		TName iName;
		};

	IMPORT_C TInt EnumerateLines(TInt& aCount) const;
	IMPORT_C TInt GetLineInfo(const TInt aIndex,TLineInfo& aLineInfo) const;

//
//	General phone notification information
//
	class TPhoneInfo
		{
	public:
		IMPORT_C TPhoneInfo();
		TModemDetection iDetection;
		};

	IMPORT_C TInt GetInfo(TPhoneInfo& aPhoneInfo) const;

//
// Notifications
//
	IMPORT_C void NotifyModemDetected(TRequestStatus& aStatus,TModemDetection& aDetection);
	IMPORT_C void NotifyModemDetectedCancel() const;
protected:
	IMPORT_C virtual void ConstructL();
	IMPORT_C virtual void Destruct();
	};

//
//
// RTelServer
//
//
class RTelServer : public RSessionBase
	{
public:
	enum { KDefaultMessageSlots=32 };

	IMPORT_C RTelServer();
	IMPORT_C TInt Connect(TInt aMessageSlots =KDefaultMessageSlots);
	inline TVersion Version() const;

//
// Enumeration and Information
//
	enum TNetworkType
		{
		ENetworkTypeWiredAnalog,
		ENetworkTypeWiredDigital,
		ENetworkTypeMobileAnalog,
		ENetworkTypeMobileDigital,
		ENetworkTypeUnknown
		};

	struct  TPhoneInfo
		{
		TNetworkType iNetworkType;
		TName iName;
		TUint iNumberOfLines;
		TUint iExtensions;
		};

	IMPORT_C TInt EnumeratePhones(TInt& aNoOfPhones) const;
	IMPORT_C TInt GetPhoneInfo(const TInt aIndex,TPhoneInfo& aInfo) const;
	IMPORT_C TInt GetTsyName(const TInt aIndexOfPhone, TDes& aTsyName) const;

//
// Load and Unload Phone modules
//
	IMPORT_C TInt LoadPhoneModule(const TDesC& aFileName) const;
	IMPORT_C TInt UnloadPhoneModule(const TDesC& aFileName) const;

//
// Check whether specified Phone module (TSY) supports certain functionality
//
		
	IMPORT_C TInt IsSupportedByModule(const TDesC& aTsyName, const TInt aMixin, TBool& aResult) const;
	IMPORT_C TInt GetTsyVersionNumber(const TDesC& aTsyName,TVersion& aVersion) const;
//
// Set this session as Priority client
//

	IMPORT_C TInt SetPriorityClient() const;

//
// Set this session to receive detailed errors
//

	enum TErrorGranularity
		{
		EErrorBasic,
		EErrorExtended
		};

	IMPORT_C TInt SetExtendedErrorGranularity(const TErrorGranularity aGranularity) const;

//
// Debug calls - stubbed in release builds
//
	IMPORT_C TInt __DbgMarkHeap();
	IMPORT_C TInt __DbgCheckHeap(TInt aCount);
	IMPORT_C TInt __DbgMarkEnd(TInt aCount);
	IMPORT_C TInt __DbgFailNext(TInt aCount);
	};


#include "ETEL.INL"
#endif
