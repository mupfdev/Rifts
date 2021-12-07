// C32COMM.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined(C32COMM_H__)
#define C32COMM_H__

/** @file c32comm.h
 *
 * C32 header file to be included by the clients.
 * Defines the main interface to C32, RCommServ and RComm
 */

#include <e32base.h>
#include <d32comm.h>


IMPORT_C TInt StartC32();

const TUint KEC32MajorVersionNumber = 1;   ///< C32 major version number 
const TUint KEC32MinorVersionNumber = 0;   ///< C32 minor version number 
const TUint KEC32BuildVersionNumber = 605; ///< C32 build version number


const TDesC& KCommServerName(void);



/** This enumeration specifies the mode in which a port is opened.
 *
 * We specify the mode when it is opened, and the mode cannot thereafter be
 * changed. If we open the port in Shared mode, other clients of the comms
 * server can use the same port while we have it open. If we open the port
 * in Exclusive mode, then it is locked for our own use and any attempt to
 * access it from another process will fail. Furthermore, our own attempt
 * to open a port in exclusive mode will fail if another process has already
 * opened the port in shared mode. 
 * Infra-red ports using IRCOMM.CSY are always opened in exclusive mode. 
 */
enum TCommAccess
    {
	ECommExclusive,   ///< Once open, the port cannot be used by any other RComm clients
	ECommShared,      ///< The port can be shared by other RComm clients who open in the same mode
	ECommPreemptable  ///< The port will be lost if other clients are trying to open it
    };

const TUint KCommBufferFull    = 0x0000; ///< used by RComm::SetMode - use full buffering
const TUint KCommBufferPartial = 0x0001; ///< used by RComm::SetMode - use partial buffering


/**
 * trace flags for debugging purposes
 */
enum TC32Trace 
	{
	ETraceC32Startup = 0x00000001,
	ETraceC32Panic   = 0x00000002,
	ETraceC32Request = 0x00000004,
	ETraceC32IPC     = 0x00000008,
	ETraceC32All     = 0xFFFFFFFF,
	};

/**
 * used by the package TCommServerConfig to configure the comm port
 */
struct TCommServerConfigV01
    {
	TUint iBufFlags; ///< contains buffer flags e.g for partial read/write
	TUint iBufSize;  ///< size of the Tx/Rx buffer
	};

typedef TPckgBuf<TCommServerConfigV01> TCommServerConfig;  ///< package used by RComm::Mode and RComm::SetMode


const TInt KMaxPortDescription = 0x30;  ///< max number of characters in TPortDescription
const TInt KMaxPortName = 0x10;         ///< max number of characters in TPortName

const TUint KCommResetRx = 0x00000001;  ///< to by used as flag by RComm::ResetBuffers
const TUint KCommResetTx = 0x00000002;  ///< to by used as flag by RComm::ResetBuffers

typedef TBuf<KMaxPortName> TPortName;                ///< name of the port, used by TSerialInfo
typedef TBuf<KMaxPortDescription> TPortDescription;  ///< description of the port, used by TSerialInfo

/**
 * used by RCommServ::GetPortInfo to retrieve information
 * about the commports and the CSY.
 */
class TSerialInfo
	{
public:
	TPortDescription iDescription; ///< description of the port (CSY)
	TPortName iName;               ///< name of the port
	TUint iLowUnit;                ///< the lowest number of the port available
	TUint iHighUnit;               ///< the highest number of the port available
	};

/**
 * Specifies the DTE/DCE role in which a port is opened.
 */
enum TCommRole
	{
		ECommRoleDTE,  ///< Port takes on role of DTE=computer (default)
		ECommRoleDCE   ///< Port takes on role of DCE=modem
	};

class RComm;

/**
 * This class represents a session with the comms server. Functions are provided
 * for connection to the server and for loading and unloading different comms
 * modules, and services for finding out the name and numbers of the available ports.
 *
 * @note This class is not intended for user derivation
 *
 */
class RCommServ : public RSessionBase
	{
public:
	IMPORT_C RCommServ();
	IMPORT_C TInt Connect();
	IMPORT_C TVersion Version() const;

	IMPORT_C TInt LoadCommModule(const TDesC& aFileName);
	IMPORT_C TInt UnloadCommModule(const TDesC& aName);

	IMPORT_C TInt NumPorts(TInt& aNum);
	IMPORT_C TInt GetPortInfo(const TDesC& aName, TSerialInfo& aInfo);
	IMPORT_C TInt GetPortInfo(TInt aIndex, TDes& aModuleName, TSerialInfo& aInfo);

	IMPORT_C TInt __DbgMarkHeap();
	IMPORT_C TInt __DbgCheckHeap(TInt aCount);
	IMPORT_C TInt __DbgMarkEnd(TInt aCount);
	IMPORT_C TInt __DbgFailNext(TInt aCount);
	IMPORT_C TInt __DbgSetTraceMask(TC32Trace aMask);

	IMPORT_C static TInt CreateThreadInCommProc(const TDesC& aLibraryName, const TDesC& aThreadName, TThreadFunction aFunction, TInt aStackSize, TInt aHeapMinSize, TInt aHeapMaxSize);
private:
	static TBool IsServerThreadL();
	};
//

struct TCommDebugInfo; // defined in d32comm.h


/**
 * This class implements a sub-session serial port
 *
 * RComm represents a serial port. It provides all the necessary functions for
 * communicating via a port, including functions for opening, closing, reading,
 * writing, together with port configuration and capability checking.
 */
class RComm : public RSubSessionBase
	{
public:
	IMPORT_C RComm();
	IMPORT_C TInt Open(RCommServ& aServer, const TDesC& aName, TCommAccess aMode);
	IMPORT_C TInt Open(RCommServ& aServer, const TDesC& aName, TCommAccess aMode, TCommRole aRole);
	IMPORT_C void OpenWhenAvailable(TRequestStatus& aStatus, RCommServ& aServer, const TDesC& aName);
	IMPORT_C void OpenWhenAvailable(TRequestStatus& aStatus, RCommServ& aServer, const TDesC& aName, TCommRole aRole);
	IMPORT_C void OpenWhenAvailableCancel();
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TDes8& aDes, TInt aLength);
	IMPORT_C void Read(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, TDes8& aDes);
	IMPORT_C void Read(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, TDes8& aDes, TInt aLength);
	IMPORT_C void ReadOneOrMore(TRequestStatus& aStatus, TDes8& aDes);
	IMPORT_C void ReadCancel();
	IMPORT_C TInt QueryReceiveBuffer() const;
	IMPORT_C void ResetBuffers(TUint aFlags=(KCommResetRx|KCommResetTx));
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, const TDesC8& aDes, TInt aLength);
	IMPORT_C void Write(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, const TDesC8& aDes);
	IMPORT_C void Write(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTimeOut, const TDesC8& aDes, TInt aLength);
	IMPORT_C void WriteCancel();
	IMPORT_C void Break(TRequestStatus& aStatus, TTimeIntervalMicroSeconds32 aTime);
	IMPORT_C void BreakCancel();
	IMPORT_C void Cancel();
	IMPORT_C void Config(TDes8& aConfig) const;
	IMPORT_C TInt SetConfig(const TDesC8& aConfig);
	IMPORT_C void Caps(TDes8& aCaps) const;
	IMPORT_C TInt SetMode(const TCommServerConfig& aConfig);
	IMPORT_C void Mode(TCommServerConfig& aConfig) const;
	IMPORT_C TUint Signals(TUint aSignalMask = 0x3F) const;
	IMPORT_C void SetSignalsToMark(TUint aSignalMask);
	IMPORT_C void SetSignalsToSpace(TUint aSignalMask);
	IMPORT_C TInt ReceiveBufferLength() const;
	IMPORT_C void SetReceiveBufferLength(TInt aLength);
	IMPORT_C void Close();
	inline void SetSignals(TUint aSetMask, TUint aClearMask);
	IMPORT_C void NotifySignalChange(TRequestStatus& aStatus, TUint& aSignals, TUint aSignalMask=0x3F);
	IMPORT_C void NotifySignalChangeCancel() const;
	IMPORT_C void NotifyConfigChange(TRequestStatus& aStatus, TDes8& aNewConfig) const;
	IMPORT_C void NotifyConfigChangeCancel() const;
	IMPORT_C void NotifyFlowControlChange(TRequestStatus& aStatus, TFlowControl& aFlowControl);
	IMPORT_C void NotifyFlowControlChangeCancel() const;	  
	IMPORT_C void NotifyBreak(TRequestStatus& aStatus) const;
	IMPORT_C void NotifyBreakCancel() const;
	IMPORT_C void NotifyDataAvailable(TRequestStatus& aStatus) const;
	IMPORT_C void NotifyDataAvailableCancel() const;
	IMPORT_C void NotifyOutputEmpty(TRequestStatus& aStatus) const;
	IMPORT_C void NotifyOutputEmptyCancel() const;
	IMPORT_C TInt GetFlowControlStatus(TFlowControl& aFlowControl) const;
	IMPORT_C TInt GetRole(TCommRole& aRole) const;

	IMPORT_C TInt SetAccessMode(TCommAccess aNewMode);
	IMPORT_C void DebugState(TCommDebugInfo&);

#ifdef _DEBUG_DEVCOMM
	IMPORT_C void RComm::DebugInfo(TDes8& aDes);
#endif
private:
	TPtr8 iSignalsNotification; ///< pointer to the signals to be changed during notification
	TPtr8 iFlowNotification;    ///< pointer to the flow control to be changed during notification
	};

#include <C32COMM.INL>

#endif // C32COMM_H__
