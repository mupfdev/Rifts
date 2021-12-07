// MSVAPI.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

//**********************************
// CMsvSession
//**********************************

inline RMsvServerSession& CMsvSession::Session() 
	{
	return iSession;
	};

inline RFs& CMsvSession::FileSession() 
	{
	return iFs;
	}

inline TInt CMsvSession::OperationId()
	{
	return iOperationId++;
	}

inline TInt CMsvSession::StopService(TMsvId aServiceId)
	{
	return iSession.StopService(aServiceId);
	}

inline TBool CMsvSession::ServiceActive(TMsvId aServiceId)
	{
	return iSession.ServiceActive(aServiceId);
	}

inline TInt CMsvSession::ServiceProgress(TMsvId aServiceId, TDes8& aProgress)
	{
	return iSession.ServiceProgress(aServiceId, aProgress);
	}

inline void CMsvSession::CloseMessageServer()
	{
	iSession.CloseMessageServer();
	}

inline void CMsvSession::RemoveEntry(TMsvId aId)
	{
	iSession.RemoveEntry(aId);
	}

inline TInt CMsvSession::InstallMtmGroup(const TDesC& aFullName)
	{
	return iSession.InstallMtmGroup(aFullName);
	}

inline TInt CMsvSession::DeInstallMtmGroup(const TDesC& aFullName)
	{
	return iSession.DeInstallMtmGroup(aFullName);
	}

inline CMsvEntry* CMsvSession::GetEntryL(TMsvId aId)
	{
	return CMsvEntry::NewL(*this, aId, TMsvSelectionOrdering());
	}

inline TInt CMsvSession::GetEntry(TMsvId aId, TMsvId& aService, TMsvEntry& aEntry)
	{
	return iSession.GetEntry(aId, aService, aEntry);
	}

//**********************************
// CMsvEntry
//**********************************

inline TMsvId CMsvEntry::EntryId() const
	{
	return iEntryPtr->Id();
	}

inline const TMsvEntry& CMsvEntry::Entry() const
	{
	return *iEntryPtr;
	}

inline CMsvSession& CMsvEntry::Session()
	{
	return iMsvSession;
	}

inline const TMsvSelectionOrdering& CMsvEntry::SortType() const
	{
	return iOrdering;
	}

inline TInt CMsvEntry::Count() const
	{
	return iSortedChildren->Count();
	}

inline TMsvId CMsvEntry::OwningService() const
	{
	return iOwningService;
	}


//**********************************
// CMsvOperation
//**********************************

inline TMsvOp CMsvOperation::Id() const
	{
	return iId;
	}

inline TMsvId CMsvOperation::Service() const
	{
	return iService;
	}
