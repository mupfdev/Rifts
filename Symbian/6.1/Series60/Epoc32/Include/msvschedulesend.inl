/////////////////////////////////////////////////////////////////////////////
//
//	MsvScheduleSend.INL
//
//	Copyright (c) 1999 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

inline CMsvOffPeakTimes& CMsvScheduleSend::OffPeakTimes() const
	{
	return *iOffPeakTimes;
	}

inline CMsvScheduleSettings& CMsvScheduleSend::ScheduleSettings() const
	{
	return *iSettings;
	}

inline CMsvSendErrorActions& CMsvScheduleSend::SendErrorActions() const
	{
	return *iErrorActions;
	}

inline CMsvSysAgentActions& CMsvScheduleSend::AgentActions() const
	{
	return *iAgentActions;
	}
