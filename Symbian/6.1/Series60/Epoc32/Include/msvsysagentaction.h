/////////////////////////////////////////////////////////////////////////////
//
//	MsvSysAgentCondAction.H
//
//	Copyright (c) 2000 Symbian Ltd.  All rights reserved. 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef SYS_AGENT_COND_ACTION_H_
#define	SYS_AGENT_COND_ACTION_H_

#include <sacls.h>
#include <saclient.h>
#include "MsvSendErrorAction.h"

/////////////////////////////////////////////////////////////////////////////
//
//	System Agent-related Class Declarations
//
/////////////////////////////////////////////////////////////////////////////

const TUid KUidMsvSysAgentActions			= {0x10005E4A};
const TInt16 KMsvSysAgentConditionActionVersion	= 1;

class TMsvSysAgentConditionAction
	{
public:
	IMPORT_C TMsvSysAgentConditionAction();

	IMPORT_C void ExternalizeL(RWriteStream&) const;
	IMPORT_C void InternalizeL(RReadStream&);

	TSysAgentCondition iCondition;
	TMsvSendErrorAction iErrorAction;
	TBool iUseDefaultSysAgentAction;

private:
	TInt16 iVersion;
	};

class CMsvSysAgentActions : public CArrayFixFlat<TMsvSysAgentConditionAction>
	{
public:
	IMPORT_C CMsvSysAgentActions();
	IMPORT_C ~CMsvSysAgentActions();

	IMPORT_C void StoreL(CMsvStore& aStore) const;
	IMPORT_C void RestoreL(CMsvStore& aStore);

	IMPORT_C TBool ConditionsMetL(TMsvSendErrorAction& aErrorAction);

	TMsvSendErrorAction iDefault;

private:

	void ExternalizeL(RWriteStream&) const;
	void InternalizeL(RReadStream&);

	void GetConditionVariablesL(CArrayFix<TUid>& aUids) const;
	TBool CheckStates(const CArrayFix<TInt>& aStates, TMsvSendErrorAction& aErrorAction) const;
	TBool ConditionOK(const TMsvSysAgentConditionAction& aCondAction, const TInt aState) const;


	RSystemAgent iAgent;
	TBool iAgentConnected;
	};

#endif