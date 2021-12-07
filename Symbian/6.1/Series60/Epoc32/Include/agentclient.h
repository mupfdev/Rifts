// AGENTCLIENT.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

// Generic Connection Agent client interface

#ifndef __AGENTCLIENT_H__
#define __AGENTCLIENT_H__

#include <nifman.h>
#include <comms-infras\nifagt.h>
#include <cdbstore.h>

enum TGenericAgentOperation
	{
	EGenericAgentSetOutgoingOverrides = CNifCompanionSession::ECompanionFirst + 1,
	EGenericAgentOutgoingErrorNotification,
	EGenericAgentCancelOutgoingErrorNotification,
	EGenericAgentSetIncomingOverrides,
	EGenericAgentAcceptIncomingRequests,
	EGenericAgentAcceptIncomingRequestsCancel,
	EGenericAgentServiceChangeNotification,
	EGenericAgentCancelServiceChangeNotification,
	EGenericAgentGetActiveIntSetting,
	EGenericAgentGetActiveBoolSetting,
	EGenericAgentGetActiveDes8Setting,
	EGenericAgentGetActiveDes16Setting,
	EGenericAgentGetActiveLongDesSetting,
	EGenericAgentDebugMarkStart,
	EGenericAgentDebugMarkEnd,
	EGenericAgentDebugSetAllocFail,
	EGenericAgentConnectionError
	};

//
// RGenericAgent class
//
// Client interface class derived from RNif.  This can be used to start an
// agent for incoming or outgoing connections, with or without overrides.
// Also allows the client to ask what overrides are being used.
//

class RGenericAgent : public RNif
	{
public:
	IMPORT_C RGenericAgent();
	IMPORT_C ~RGenericAgent();
	IMPORT_C TInt Open();
	IMPORT_C TInt StartOutgoing();
	IMPORT_C TInt StartOutgoing(CStoreableOverrideSettings& aOverrides);
	IMPORT_C void StartOutgoing(TRequestStatus& aStatus);
	IMPORT_C void StartOutgoing(CStoreableOverrideSettings& aOverrides, TRequestStatus& aStatus);
	IMPORT_C void CancelOutgoingErrorNotification();
	IMPORT_C TInt AcceptIncomingRequests(TRequestStatus& aStatus);
	IMPORT_C TInt AcceptIncomingRequests(CStoreableOverrideSettings& aOverrides, TRequestStatus& aStatus);
	IMPORT_C void AcceptIncomingRequestsCancel();
	IMPORT_C void ServiceChangeNotification(TRequestStatus& aStatus, TUint32& aNewISPId, TDes& aNewServiceType);
	IMPORT_C void CancelServiceChangeNotification();
	IMPORT_C TInt GetActiveIntSetting(const TDesC& aTableName, const TDesC& aColumnName, TUint32& aValue);
	IMPORT_C TInt GetActiveBoolSetting(const TDesC& aTableName, const TDesC& aColumnName, TBool& aValue);
	IMPORT_C TInt GetActiveDesSetting(const TDesC& aTableName, const TDesC& aColumnName, TDes8& aValue);
	IMPORT_C TInt GetActiveDesSetting(const TDesC& aTableName, const TDesC& aColumnName, TDes16& aValue);
	IMPORT_C TInt GetActiveLongDesSetting(const TDesC& aTableName, const TDesC& aColumnName, TDes& aValue);
	IMPORT_C static void ResolveError(TInt &aError);
	IMPORT_C void ConnectionError(TInt& aError);
	IMPORT_C void DebugMarkStart();
	IMPORT_C void DebugMarkEnd(TInt aCount = 0);
	IMPORT_C void DebugSetAllocFail(TInt aValue = 0);
private:
	void PackageOverridesArray(TAny* aPtr,  TInt aPtrNum, CStoreableOverrideSettings& aOverrides);
	void DoStartOutgoingL(CStoreableOverrideSettings& aOverrides);
	void DoAcceptIncomingRequestsL(CStoreableOverrideSettings& aOverrides, TRequestStatus& aStatus);
private:
	TPckg<TUint32> iNewISPId;
	};	

#endif

