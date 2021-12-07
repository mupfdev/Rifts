// SACLS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __SACLS_H__
#define __SACLS_H__


// Constants
const TInt KNullState = 0;


// System agent maintained entries

const TInt KUidProfileValue		=0x100052D2;
const TUid KUidProfile			={KUidProfileValue};


const TInt KUidPhonePwrValue=0x100052C5;
const TUid KUidPhonePwr={KUidPhonePwrValue};
enum TSAPhoneStatus
	{
	ESAPhoneOff,
	ESAPhoneOn
	};

const TInt KUidSIMStatusValue	=0x100052C6;
const TUid KUidSIMStatus		={KUidSIMStatusValue};
enum TSASIMStatus
	{
	ESASimOk,
	ESASimNotPresent,
	ESASimRejected
	};

const TInt KUidNetworkStatusValue=0x100052C7;
const TUid KUidNetworkStatus	={KUidNetworkStatusValue};
enum TSANetworkStatus
	{
	ESANetworkAvailable,
	ESANetworkUnAvailable
	};

const TInt KUidNetworkStrengthValue  =0x100052C8;
const TUid KUidNetworkStrength  ={KUidNetworkStrengthValue};
enum TSANetworkStrength
	{
	ESANetworkStrengthNone,
	ESANetworkStrengthLow,
	ESANetworkStrengthMedium,
	ESANetworkStrengthHigh,
	ESANetworkStrengthUnknown
	};

const TInt KUidChargerStatusValue	=0x100052C9;
const TUid KUidChargerStatus	={KUidChargerStatusValue};
enum TSAChargerStatus
	{
	ESAChargerConnected,
	ESAChargerDisconnected,
	ESAChargerNotCharging
	};

const TInt KUidBatteryStrengthValue  =0x100052CA;
const TUid KUidBatteryStrength  ={KUidBatteryStrengthValue};
enum TSABatteryStrength
	{
	ESABatteryAlmostEmpty,
	ESABatteryLow,
	ESABatteryFull
	};

const TInt KUidCurrentCallValue	=0x100052CB;
const TUid KUidCurrentCall		={KUidCurrentCallValue};
enum TSACurrentCall
	{
	ESACallNone,
	ESACallVoice,
	ESACallFax,
	ESACallData,
	ESACallAlerting,
	ESACallRinging,
	ESACallAlternating
	};

const TInt KUidDataPortValue	=0x100052CC;
const TUid KUidDataPort			={KUidDataPortValue};
enum TSAPort
	{
	ESADataPortIdle,
	ESADataPortBusy	
	};


const TInt KUidInboxStatusValue	=0x100052CD;
const TUid KUidInboxStatus		={KUidInboxStatusValue};
enum TSAInboxStatus
	{
	ESAInboxEmpty,
	ESADocumentsInInbox
	};

const TInt KUidOutboxStatusValue=0x100052CE;
const TUid KUidOutboxStatus		={KUidOutboxStatusValue};
enum TSAOutboxStatus
	{
	ESAOutboxEmpty,
	ESADocumentsInOutbox
	};

const TInt KUidClockValue		=0x100052CF;
const TUid KUidClock			={KUidClockValue};
enum TSAClock
	{
	ESAAm,
	ESAPm
	};

// No longer used
const TInt KUidAlarmValue		=0x100052D0;
const TUid KUidAlarm			={KUidAlarmValue};
enum TSAAlarm
	{
	ESAAlarmOff,
	ESAAlarmOn,
	};

const TInt KUidIrdaStatusValue	=0x100052D1;
const TUid KUidIrdaStatus		={KUidIrdaStatusValue};
enum TSAIrdaStatus
	{
	ESAIrLoaded,		//IRDA Irlap layer loaded
	ESAIrDiscoveredPeer,//Discovery begin
	ESAIrLostPeer,		//Discovery end
	ESAIrConnected,		//IRDA Irlap layer connected
	ESAIrBlocked,		//IRDA Irlap layer blocked
	ESAIrDisConnected,	//IRDA Irlap layer disconnected
	ESAIrUnloaded		//IRDA Irlap layer unloaded
	};


enum TSysAgentConditionType
	{
	ESysAgentEquals=32,
	ESysAgentNotEquals,
	ESysAgentGreaterThan,
	ESysAgentLessThan
	};


class TSysAgentCondition
//
//	Simple class for data transfer from client process to 
//	system agent then across client/server boundary
//
	{
public:
	inline TSysAgentCondition();
	inline TSysAgentCondition(TUid aVariable, TInt aState, TSysAgentConditionType aType);

public:
	TUid iVariable;
	TInt iState;
	TSysAgentConditionType iType;
	};

inline TSysAgentCondition::TSysAgentCondition()
:	iVariable(KNullUid), iState(KNullState), iType(ESysAgentEquals)
	{
	}

inline TSysAgentCondition::TSysAgentCondition(TUid aVariable, TInt aState, TSysAgentConditionType aType)
:	iVariable(aVariable), iState(aState), iType(aType)
	{
	}


IMPORT_C TInt StartSystemAgent(TAny* aAny);

#endif