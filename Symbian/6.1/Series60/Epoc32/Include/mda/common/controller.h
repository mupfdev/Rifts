// Mda\Common\Controller.h
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_COMMON_CONTROLLER_H__
#define __MDA_COMMON_CONTROLLER_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Common\Controller.hrh> // defines
#include <Mda\Common\Base.h>

MDA_UID(KUidMdaControllerType) 
MDA_UID(KUidMdaController) 
MDA_UID(KUidMdaDataTypeSettings) 
MDA_UID(KUidMdaElapsedTime) 

// Function numbers

enum //TMLbControllerFunctions
	{
	EMLbControllerConnect=0,
	EMLbControllerDisconnect,
	EMLbControllerPriority,
	EMLbControllerGetState,
	EMLbControllerPrepare,		
	EMLbControllerPrime,		
	EMLbControllerPlay,			
	EMLbControllerPause,			
	EMLbControllerStop,				
	EMLbControllerUnprepare
	};

enum //TMLbMachineFunctions
	{
	};

// Controller priority numbers

enum TMdaPriority
	{
	EMdaPriorityMin = -100,
	EMdaPriorityNormal = 0,
	EMdaPriorityMax = 100
	};

enum TMdaPriorityPreference
	{
	EMdaPriorityPreferenceNone =			0x00000000,
	EMdaPriorityPreferenceTime =			0x00000001,
	EMdaPriorityPreferenceQuality =			0x00000002,
	EMdaPriorityPreferenceTimeAndQuality = EMdaPriorityPreferenceTime|EMdaPriorityPreferenceQuality
	// Unused bits must be set to zero
	// Bits 16 to 31 (0x00010000 to 0x80000000) reserved for device specific use
	};

//
// Controller events
//

enum TMdaControllerEvent
	{
	EMdaControllerStateChangedEvent=0,
	EMdaControllerErrorEvent=1
	};

//
// Connection information
// 
class TMdaRawConnection : public TMdaOpenPackage
	{
public:
	inline TMdaRawConnection(TInt aDerivedSize);
public:
	TInt iSrcHandle;
	TInt iDstHandle;
	TInt iType;
	};

//
// Query the state of a controller
// 

enum TMdaControllerState
	{
	EMdaControllerStateUnprepared,	
	EMdaControllerStatePrepared,	
	EMdaControllerStatePrimed,		
	EMdaControllerStatePlaying,
	// Forward transitions
	EMdaControllerStatePreparing,
	EMdaControllerStatePriming,
	EMdaControllerStatePlay,
	// Backwards transitions
	EMdaControllerStatePausing,
	EMdaControllerStateStopping,
	EMdaControllerStateUnpreparing
	};

class TMdaControllerStateQuery : public TMdaRawPackage
	{
public:
	inline TMdaControllerStateQuery();
public:
	TMdaControllerState iState;
	};

//
// Controller events
//

class TMdaControllerStateChangeEvent
	{
public:
	inline TMdaControllerStateChangeEvent(const TMdaEvent& aEvent);
	inline void Set(const TMdaEvent& aEvent);
	inline TBool IsStateChangeEvent();
	inline TMdaControllerState NewState();
	inline TMdaControllerState OldState();
	inline TInt ClientData();
private:
	const TMdaEvent* iEvent;
	};
  
//
// Datatype parameters
// Base class for specific data type config packages
//
class TMdaDatatypeSettings : public TMdaPackage
	{
protected:
	inline TMdaDatatypeSettings(TUid aUid,TInt aDerivedSize);
	};


//
// Time parameters
// Used to query/set the time elapsed on a port
//
class TMdaElapsedTime : public TMdaDatatypeSettings
	{
public:
	enum TMode
		{
		EQuery=1,
		ESet=2
		};
public:
	inline TMdaElapsedTime(); // Query
	inline TMdaElapsedTime(TTimeIntervalMicroSeconds aElapsedTime); // Set
	inline void Query(); // Query by default
	inline void Set(TTimeIntervalMicroSeconds aElapsedTime);
	inline const TTimeIntervalMicroSeconds& Elapsed() const;
protected:
	TMode iMode;
	TTimeIntervalMicroSeconds iElapsed;
	};

// Inlines

inline TMdaRawConnection::TMdaRawConnection(TInt aDerivedSize) : 
TMdaOpenPackage(aDerivedSize) {}


inline TMdaDatatypeSettings::TMdaDatatypeSettings(TUid aUid,TInt aDerivedSize) :
TMdaPackage(KUidMdaDataTypeSettings,aUid,aDerivedSize) {}

inline TMdaElapsedTime::TMdaElapsedTime() :
TMdaDatatypeSettings(KUidMdaElapsedTime,sizeof(TMdaElapsedTime)), 
iMode(EQuery),
iElapsed(KMdaUnknown) {}

inline TMdaElapsedTime::TMdaElapsedTime(TTimeIntervalMicroSeconds aElapsedTime) :
TMdaDatatypeSettings(KUidMdaElapsedTime,sizeof(TMdaElapsedTime)), 
iMode(ESet),
iElapsed(aElapsedTime) {}

inline void TMdaElapsedTime::Query()
	{ iMode = EQuery; iElapsed = KMdaUnknown; }
inline void TMdaElapsedTime::Set(TTimeIntervalMicroSeconds aElapsedTime)
	{ iMode = ESet; iElapsed = aElapsedTime; }
inline const TTimeIntervalMicroSeconds& TMdaElapsedTime::Elapsed() const
	{ return iElapsed; }

inline TMdaControllerStateQuery::TMdaControllerStateQuery() :
TMdaRawPackage(sizeof(TMdaControllerStateQuery)) {}

inline TMdaControllerStateChangeEvent::TMdaControllerStateChangeEvent(const TMdaEvent& aEvent) :
iEvent(&aEvent) {}
inline void TMdaControllerStateChangeEvent::Set(const TMdaEvent& aEvent)
	{ iEvent = &aEvent; }
inline TBool TMdaControllerStateChangeEvent::IsStateChangeEvent()
	{ return (iEvent->iId == EMdaControllerStateChangedEvent); }
inline TMdaControllerState TMdaControllerStateChangeEvent::NewState()
	{ return STATIC_CAST(TMdaControllerState,iEvent->iArg[0]); }
inline TMdaControllerState TMdaControllerStateChangeEvent::OldState()
	{ return STATIC_CAST(TMdaControllerState,iEvent->iArg[1]); }
inline TInt TMdaControllerStateChangeEvent::ClientData()
	{ return STATIC_CAST(TInt,iEvent->iArg[2]); }

#endif
