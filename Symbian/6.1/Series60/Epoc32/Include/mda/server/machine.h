// Mda\Server\Machine.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// *********** All classes Internal to Symbian *************//

#ifndef __MDA_SERVER_MACHINE_H__
#define __MDA_SERVER_MACHINE_H__

// Standard EPOC32 includes
#ifndef __E32BASE_H__
#include <e32base.h>
#endif

#include <Mda\Common\Controller.h>	// for Machine function codes
#include <Mda\Server\Base.h>

enum TMdaMachineState
	{
	// Stable states
	EMdaUnprepared,	// Not ready
	EMdaPrepared,	// Buffers allocated for every connection (Stopped)
	EMdaPrimed,		// Data loaded for primed position (Paused)
	EMdaPlaying,	// Playing, data in transit
	// Forward transitions, can fail/leave
	EMdaPreparing,
	EMdaPriming,
	EMdaPlay,
	// Backwards transitions, not allowed to fail
	EMdaPausing,
	EMdaStopping,
	EMdaUnpreparing
	};

enum TMdaMachinePanic
	{
	EMdaMachinePanicNoNextState=0,
	EMdaMachinePanicNoPreviousState=1,
	EMdaMachinePanicCancelPreviousState=2,
	EMdaMachinePanicUnexpectedStateComplete=3,
	EMdaMachinePanicUnexpectedStateFailed=4,
	EMdaMachinePanicInvalidRepeatCallRequested=5,
	EMdaMachinePanicInvalidMessageFunction=6,
	EMdaMachinePanicClosedWhileInUse=7,
	EMdaMachinePanicNoMessage=8
	};

enum TMdaMachineSlavePanic
	{
	EMdaMachineSlavePanicMachinePtrNotSet=0
	};

enum TMdaMachineSlaveParentPanic
	{
	EMdaMachineSlavePanicChildInBadState=0
	};

//////////////////////////////////////////////////////////////////////////////
//
//  CMdaMachine
//
//  Inherited by class controlling state changes
//
/////////////////////////////////////////////////////////////////////////////

class CMdaDispatchMessage;	// Forward definitions
class MMdaMachineMaster;
class MMdaMachineSlave;

// Internal to Symbian
class CMdaMachine : public CMdaObject, public MMdaMessage
	{
public:
	IMPORT_C CMdaMachine(MMdaMachineMaster& aMaster,MMdaMachineSlave& aSlave);
	IMPORT_C virtual ~CMdaMachine();

	IMPORT_C void SetMessage(CMdaDispatchMessage* aMessage);

	// Interface for master
	IMPORT_C void NextState(); // Asynchronous
	IMPORT_C void CancelStateChange();
	IMPORT_C void PreviousState(); // Synchronous

	// Interface for slave
	IMPORT_C void SlaveStateChangeComplete();
	IMPORT_C void SlaveStateChangeFailed(TInt aErr);
	IMPORT_C void SlaveNeedsRepeatCall();
	
	// Utility
	IMPORT_C TBool IsChangingState();
	inline TMdaMachineState State();
	inline TMdaMachineState OldState();
protected:
	// From CMdaObject
	IMPORT_C virtual void OperationL(CMdaMessage* aMessage);
	// From MMdaMessage
	IMPORT_C virtual void MessageDoComplete(TInt aVal);
	// New
	IMPORT_C void DoStateChange();
protected:
	TMdaMachineState iState;
	TMdaMachineState iOldState;
	MMdaMachineMaster& iMaster;
	MMdaMachineSlave& iSlave;
	CMdaDispatchMessage* iMessage;
	};

inline TMdaMachineState CMdaMachine::State()
	{
	return iState;
	}

inline TMdaMachineState CMdaMachine::OldState()
	{
	return iOldState;
	}

//////////////////////////////////////////////////////////////////////////////
//
//  MMdaMachineMaster
//
//  Inherited by class controlling state changes
//
/////////////////////////////////////////////////////////////////////////////

// Internal to Symbian
class MMdaMachineMaster
	{
public:
	virtual void MachineStateChangeCompleted(CMdaMachine* aMachine)=0;
	virtual void MachineStateChangeFailed(CMdaMachine* aMachine,TInt aErr)=0;
	};

//////////////////////////////////////////////////////////////////////////////
//
//  MMdaMachineSlave
//
//  Inherited by class implementing state changes
//	Forward function are asynch and machine must be notified of completion
//  Backward functions are synch and cannot fail
//
/////////////////////////////////////////////////////////////////////////////

// Internal to Symbian
class MMdaMachineSlave
	{
public:
	// Asynchronous functions
	IMPORT_C virtual void MachinePrepareL();	    // Allocate resources	
	IMPORT_C virtual void MachineCancelPrepare();	
	IMPORT_C virtual void MachinePrimeL();			// Get ready to play
	IMPORT_C virtual void MachineCancelPrime();	
	IMPORT_C virtual void MachinePlayL();			// Start playing
	IMPORT_C virtual void MachineCancelPlay();	
	// Synchronous functions
	IMPORT_C virtual void MachinePause();			// Pause playing
	IMPORT_C virtual void MachineStop();			// Reset the media
	IMPORT_C virtual void MachineUnprepare();		// Free resources
protected:
	// Utility functions
	IMPORT_C void MachineCompleted();
	IMPORT_C void MachineFailed(TInt aErr);
	IMPORT_C void MachineCompletedOrFailed(TInt aRet);
	IMPORT_C void MachineNeedsRepeatCall();
public:
	CMdaMachine* iMachine;
	};

//////////////////////////////////////////////////////////////////////////////
//
//  MMdaMachineSlaveParent
//
//	Specialised slave that broadcasts to other machines
//
/////////////////////////////////////////////////////////////////////////////

// Internal to Symbian
class MMdaMachineSlaveParent : public MMdaMachineSlave
	{
public:
	IMPORT_C virtual void MachinePrepareL();	    
	IMPORT_C virtual void MachineCancelPrepare();	
	IMPORT_C virtual void MachinePrimeL();			
	IMPORT_C virtual void MachineCancelPrime();	
	IMPORT_C virtual void MachinePlayL();			
	IMPORT_C virtual void MachineCancelPlay();	
	IMPORT_C virtual void MachinePause();			
	IMPORT_C virtual void MachineStop();			
	IMPORT_C virtual void MachineUnprepare();		
protected:
	// Utilities for default functions - to be supplied by derived class
	IMPORT_C virtual void MachineSetToFirstChild()=0;
	IMPORT_C virtual CMdaMachine* MachineNextChild()=0;
	// Utilities supplied
	IMPORT_C TInt MachineNext(TMdaMachineState aFrom);
	IMPORT_C void MachineCancelNext(TMdaMachineState aFrom,TMdaMachineState aDuring,TMdaMachineState aTo);
	IMPORT_C void MachinePrevious(TMdaMachineState aFrom);
	};

#endif
