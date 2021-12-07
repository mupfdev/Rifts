// CS_PORT.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
#if !defined (CS_PORT_H__)
#define CS_PORT_H__

#include <c32comm.h>

/** @file cs_port.h
 *
 * defines the classes CPort and CSerial. This file should be included by the CSY
 */

const TInt KDeltaTimerInterval = 100000;                ///< delta timer interval
const TInt KUidUnicodeCommServerModuleV02 = 0x10005054; ///< the UID for the CSY

/**
 * defines the internal port access mode
 *
 * @note Important! must have the same order as TCommAccess in c32comm.h
 */
enum TInternalCommAccess
	{
	EIntCommExclusive          = 0, ///< Exclusive mode. Must be first
	EIntCommShared             = 1, ///< Shared mode. Must be second
	EIntCommPreemptable        = 2, ///< Preemptable mode. Must be third
	EIntCommWaitUntilAvailable = 3  ///< Wait until the port is closed
	};

class CPortManager;


/**
 * static utility class for global timer handling
 */
class CommTimer 
	{
public:
	IMPORT_C static void Queue(TTimeIntervalMicroSeconds32 aTimeInMicroSeconds, TDeltaTimerEntry& aHandle);
	IMPORT_C static void Remove(TDeltaTimerEntry& aHandle);
	static CDeltaTimer* GetTimer();
	};

class CCommSession;
class CSerial;



/**
 * Base class for Serial Port (CSY) implementations.
 *
 * Created when the first client does an Open request passing its name.
 * Destroyed only when it deletes itself (following a call to Destruct).
 */
class CPort : public CObject
	{
	// Warning:  No CPort::ConstructL, so can't use iExtra members until after construction.
private:
	class CExtra : public CBase
		{
	public:
		CCommSession* iBreakOwner;
		CCommSession* iPreemptableOwner;
		CCommSession* iPreemptedSession;
		CCommSession* iWaitAvailableOwner;  // Also the SetAccess owner.
	    RMessagePtr   iBlockedSetAccess; 
		};

friend class CPortManager;

public:
	typedef TCommAccess TAccess;

	void CommRead(const RMessage &aMessage,CCommSession* aClient); // Start read operation
	void CommReadCancel(TInt aHandle, CCommSession* aClient);
	void CommWrite(const RMessage &aMessage,CCommSession* aClient); // Start Write opneration
	void CommWriteCancel(TInt aHandle, CCommSession* aClient);
	void CommBreak(const RMessage &aMessage,CCommSession* aClient);	// Start Break operation
	void CommBreakCancel(TInt aHandle, CCommSession* aClient);
	void CommCancel(TInt aHandle, CCommSession* aClient); // Cancel all blocked operation.

	void CommConfig(const RMessage& aMessage, CCommSession& aSession) const;
	void CommSetConfig(const RMessage& aMessage, CCommSession& aSession);
	void CommSetServerConfig(const RMessage& aMessage, CCommSession& aSession);
	void CommGetServerConfig(const RMessage& aMessage, CCommSession& aSession);
	void CommCaps(const RMessage& aMessage, CCommSession& aSession);
	void CommSignals(const RMessage& aMessage, CCommSession& aSession);
	void CommSetSignalsToMark(const RMessage& aMessage, CCommSession& aSession);
	void CommSetSignalsToSpace(const RMessage& aMessage, CCommSession& aSession);
	void CommReceiveBufferLength(const RMessage& aMessage, CCommSession& aSession) const;
	void CommSetReceiveBufferLength(const RMessage& aMessage, CCommSession& aSession);
	void CommQueryReceiveBuffer(const RMessage& aMessage, CCommSession& aSession) const;
	void CommResetBuffers(const RMessage& aMessage, CCommSession& aSession);
	void CommSetAccess(const RMessage& aMessage, CCommSession& aSession);
	void CommSetAccessCancel(TInt aHandle, CCommSession* aClient);
	void CommDebugState(const RMessage& aMessage, CCommSession& aSession);

	TBool TakeOwnershipForReading(CCommSession* aClient);		// Check if a read request is valid and take ownership of port
	TBool TakeOwnershipForWriting(CCommSession* aClient);		// Check if a Write request is valid and take ownership of port
	TBool TakeOwnershipForBreaking(CCommSession* aClient);		// Check if a Break request is valid and take ownership of port

	void InitL(TDesC8 &aName); ///< @todo remove InitL not used
	static TInt WriteTimerExpiredHandler(TAny* aPtr);
	static TInt ReadTimerExpiredHandler(TAny* aPtr);
	TBool AreAnyPending();

	void CommGetRole(const RMessage &aMessage, CCommSession* aClient);
	void CommGetFlowControlStatus(const RMessage &aMessage, CCommSession* aClient);

	void CommNotifySignalChange(const RMessage &aMessage, CCommSession* aClient);
	TBool TakeOwnershipForSignals(CCommSession* aClient);
	void CommNotifyFlowControlChange(const RMessage &aMessage, CCommSession* aClient);
	TBool TakeOwnershipForFlowControl(CCommSession* aClient);
	void CommNotifyConfigChange(const RMessage &aMessage, CCommSession* aClient);
	TBool TakeOwnershipForConfig(CCommSession* aClient);
	void CommNotifyBreak(const RMessage &aMessage, CCommSession* aClient);
	TBool TakeOwnershipForBreak(CCommSession* aClient);
	void CommNotifyDataAvailable(const RMessage &aMessage, CCommSession* aClient);
	TBool TakeOwnershipForNotifyDataAvailable(CCommSession* aClient);
	void CommNotifyOutputEmpty(const RMessage &aMessage, CCommSession* aClient);
	TBool TakeOwnershipForNotifyOutputEmpty(CCommSession* aClient);

	void CommNotifySignalChangeCancel(TInt aHandle, CCommSession* aClient);
	void CommNotifyConfigChangeCancel(TInt aHandle, CCommSession* aClient);
	void CommNotifyFlowControlChangeCancel(TInt aHandle, CCommSession* aClient);
	void CommNotifyBreakCancel(TInt aHandle, CCommSession* aClient);
	void CommNotifyDataAvailableCancel(TInt aHandle, CCommSession* aClient);
	void CommNotifyOutputEmptyCancel(TInt aHandle, CCommSession* aClient);

	TBool SessionHasBeenPreempted(CCommSession* aSession);
	TBool SessionIsAwaitingOpen(CCommSession* aSession);
	void FreeSession(CCommSession* aSession);

public:
	IMPORT_C TInt IPCRead(const TAny* aPtr, TDes8& aDes, TInt aOffset=0) const;
	IMPORT_C TInt IPCWrite(const TAny* aPtr, const TDesC8& aDes, TInt aOffset=0) const;
	IMPORT_C CPort();
	IMPORT_C void ReadCompleted(TInt anError);		// Called by a CPort to complete a read.
	IMPORT_C void WriteCompleted(TInt anError);		// Called by a CPort to complete a write
	IMPORT_C void BreakCompleted(TInt anError);		// Called by a CPort to complete a break
	IMPORT_C virtual ~CPort();
	IMPORT_C void Close();
	IMPORT_C void SignalChangeCompleted(const TUint& aSignals, TInt anError);					// Called by a CPort to complete a signal notify
	IMPORT_C void ConfigChangeCompleted(const TDesC8& aNewConfig, TInt anError);				// Called by a CPort to complete a config notify.
	IMPORT_C void FlowControlChangeCompleted(const TFlowControl& aFlowControl, TInt anError);	// Called by a CPort to complete a flow control notify
	IMPORT_C void BreakNotifyCompleted(TInt anError);			// Called by a CPort to complete a break signal notify
	IMPORT_C void NotifyDataAvailableCompleted(TInt anError);	// Called by a CPort to complete a break signal notify
	IMPORT_C void NotifyOutputEmptyCompleted(TInt anError);		// Called by a CPort to complete a break signal notify

public:
	//
	// Pure virtual methods - to be implemented by the CSY
	//

	/// Called by manager when access count is 0 - CSY port must call 'delete this'
	virtual void Destruct()=0;
	/// Queue a read - called by CPort when client wants to read
	/// @note If the value in aLength is negative, this means
	///       ReadOneOrMore and the CSY must invert the number
	virtual void StartRead(const TAny* aClientBuffer, TInt aLength)=0;
	/// Cancel a pending read
	virtual void ReadCancel()=0;
	/// Get the size of the receive buffer from the real serial port
	virtual TInt QueryReceiveBuffer(TInt& aLength) const=0;
	/// reset Tx and Rx buffers
	virtual void ResetBuffers(TUint aFlags)=0;
	/// Queue a write - called by CPort when client wants to write
	virtual void StartWrite(const TAny* aClientBuffer, TInt aLength)=0;
	/// Cancel a pending write
	virtual void WriteCancel()=0;
	/// Queue a break
	virtual void Break(TInt aTime)=0;
	/// Cancel a pending break
	virtual void BreakCancel()=0;
	/// Pass a config request - return in descriptor
	virtual TInt GetConfig(TDes8& aPackage) const=0;
	/// Set config with package in the descriptor
	virtual TInt SetConfig(const TDesC8& aPackage)=0;
	/// Set the port to use partial reads/writes
	virtual TInt SetServerConfig(const TDesC8& aPackage)=0;
	/// Get the server configs from the CSY
	virtual TInt GetServerConfig(TDes8& aPackage)=0;
	/// Read capabilities from the driver
	virtual TInt GetCaps(TDes8& aPackage)=0;
	/// Get the status of the signal pins
	virtual TInt GetSignals(TUint& aSignals)=0;
	/// Set selected signals to high (logical 1)
	virtual TInt SetSignalsToMark(TUint aSignals)=0;
	/// Set selected signals to low (logical 0)
	virtual TInt SetSignalsToSpace(TUint aSignals)=0;
	/// Get size of Tx and Rx buffer
	virtual TInt GetReceiveBufferLength(TInt& aLength) const=0;
	/// Set size of Tx and Rx buffer
	virtual TInt SetReceiveBufferLength(TInt aLength)=0;
	virtual void FreeMemory(); /// @todo this is not pure virtual. What is the purpose of this?
	/// Notify client when the signals change
	virtual void NotifySignalChange(TUint aSignalMask)=0;
	/// Cancel an outstanding signal change notification
	virtual void NotifySignalChangeCancel()=0;
	/// Notify client when the configation changes
	virtual void NotifyConfigChange()=0;
	/// Cancel an outstanding config change notification
	virtual void NotifyConfigChangeCancel()=0;
	/// Notify client when the flow control changes
	virtual void NotifyFlowControlChange()=0;
	/// Cancel an outstanding flow control change notification
	virtual void NotifyFlowControlChangeCancel()=0;
	/// Notify client when a break occurs
	virtual void NotifyBreak()=0;
	/// Cancel an outstanding break notification
	virtual void NotifyBreakCancel()=0;
	/// Notify client when data is available
	virtual void NotifyDataAvailable()=0;
	/// Cancel an outstanding data availalbe notification
	virtual void NotifyDataAvailableCancel()=0;
	/// Notify client when output buffer is empty
	virtual void NotifyOutputEmpty()=0;
	/// Cancel an outstanding output empty notification
	virtual void NotifyOutputEmptyCancel()=0;
	/// Get the flow control status
	virtual TInt GetFlowControlStatus(TFlowControl& aFlowControl)=0;
	/// Get the role of this port unit
	virtual TInt GetRole(TCommRole& aRole)=0;
	/// Set the role of this port unit
	virtual TInt SetRole(TCommRole aRole)=0;

// Accessors
#ifdef _DEBUG_DEVCOMM
	virtual void DoDumpDebugInfo(const RMessage &aMessage)=0;
#endif
private:
	void DoOpenL(CCommSession* aSession, TInternalCommAccess aMode, TCommRole aRole,TBool aIsNew);
	void DoPreemption();

	TDeltaTimerEntry iReadTimer;  ///< delta timer entry for read timeouts
	TBool iReadTimerPending;      ///< true if a read timer is pending
	TDeltaTimerEntry iWriteTimer; ///< delta timer entry for write timeouts
	TBool iWriteTimerPending;     ///< true if a write timer is pending
	TInternalCommAccess iMode;    ///< access mode for this port
	CCommSession* iReadOwner;     ///< pointer to the read session
	TInt iReadOwnerHandle;        ///< handle to the read session
	CCommSession* iWriteOwner;    ///< pointer to the write session
	TInt iWriteOwnerHandle;       ///< handle to the write session
	// Binary compatible
	// Was: CCommSession* iBreakOwner;  Replace with:
	CExtra* iExtra;               ///< pointer to the CExtra object for pre-emptable handling
#define iBreakOwner (iExtra->iBreakOwner) ///< forwards iBreakOwner to iExtra->iBreakOwner

	TInt iBreakOwnerHandle;                  ///< handle to the break owner
	CCommSession* iSignalOwner;              ///< pointer to the signal session
	TInt iSignalOwnerHandle;                 ///< handle to the signal session
	CCommSession* iFlowControlOwner;         ///< pointer to the flow control session
	TInt iFlowControlOwnerHandle;            ///< handle to the flow control session
	CCommSession* iConfigOwner;              ///< pointer to the config session
	TInt iConfigOwnerHandle;                 ///< handle to the config session
	CCommSession* iBreakNotifyOwner;         ///< pointer to the break notify session
	TInt iBreakNotifyOwnerHandle;            ///< handle to the break notify session
	CCommSession* iNotifyDataAvailableOwner; ///< pointer to the data available session
	TInt iNotifyDataAvailableOwnerHandle;    ///< handle to the data available session
	CCommSession* iNotifyOutputEmptyOwner;   ///< pointer to the output empty session
	TInt iNotifyOutputEmptyOwnerHandle;      ///< handle to the output empty session

	RMessagePtr iBlockedRead;                ///< pointer to the read request message
	RMessagePtr iBlockedWrite;               ///< pointer to the write request message
	RMessagePtr iBlockedBreak;               ///< pointer to the break request message
	RMessage iBlockedSignalChange;           ///< holds the notify signal change message
	RMessage iBlockedConfigChange;           ///< holds the notify config change message
	RMessage iBlockedFlowControlChange;      ///< holds the notify flow control change message
	RMessagePtr iBlockedBreakNotify;         ///< pointer to the notify break request message
	RMessagePtr iBlockedNotifyDataAvailable; ///< pointer to the notify data available request message
	RMessagePtr iBlockedNotifyOutputEmpty;   ///< pointer to the notify output empty request message

	CPortManager* iPortManager;              ///< pointer to CPortManager, owned by CCommServer
	IMPORT_C virtual void CPort_Reserved1();
	TAny* iCPort_Reserved;                   ///< reserved pointer
	};


//
// forward declaration
//
class CLibUnloader;

/**
 * Factory for a single CPort object.
 * Owned by the CPort object it creates. 
 */
class CSerial : public CObject
	{
public:
	IMPORT_C CSerial();
	IMPORT_C ~CSerial();
	IMPORT_C virtual TBool QueryVersionSupported(const TVersion& aVersion) const;
	void ConstructL(RLibrary& aLib);
public:
	//
	// pure virtuals to be implemented by the CSY
	//

	/// Create a new port for the supplied unit number
	virtual CPort* NewPortL(const TUint aUnit)=0;
	/// Get info about this CSY, fill in the supplied structure.
	virtual void Info(TSerialInfo &aSerialInfo)=0;

	void ModuleName(TDes& aName);
protected:
	TVersion iVersion;                         ///< holds the version of the CSY
private:
	CLibUnloader* iLibUnloader;                ///< pointer to the library unloader
	IMPORT_C virtual void CSerial_Reserved1();
	TAny* iCSerial_Reserved;                   ///< reserved pointer for future BC
	};

typedef CSerial *(*TSerialNewL)(); ///< function type of CSY module entry point

#endif // CS_PORT_H__
