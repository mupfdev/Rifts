// T32ALM.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// Written by BLB, June 1995
//

// Class TAlarmInfo
inline TInt TAlarmInfo::AlarmId() const
	{
	return(iAlarmId);
	}
inline TAlarmClockRepeat TAlarmInfo::Repeat() const
	{
	return(iRepeat);
	}
inline TAlarmType TAlarmInfo::Type() const
	{
	return(iType);
	}
inline TTime TAlarmInfo::DueTime() const
	{
	return(iDueTime);
	}
inline TTime TAlarmInfo::AlarmTime() const
	{
	return(iAlarmTime);
	}
inline TAlarmMessage TAlarmInfo::Message() const
	{
	return(iMessage);
	}
inline TAlarmSoundName TAlarmInfo::Sound() const
	{
	return(iSound);
	}

// 	class RAlarmServer
inline TVersion RAlarmServer::Version() const
	{
	return(TVersion(KAlarmServerMajVN,KAlarmServerMinVN,KAlarmServerBldVN));
	}

