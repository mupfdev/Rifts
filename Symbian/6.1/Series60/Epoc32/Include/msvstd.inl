// MSVSTD.INL
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

//**********************************
// TMsvEntry
//**********************************

inline TMsvId TMsvEntry::Id() const
	{
	return iId;
	}

inline void TMsvEntry::SetId(TMsvId aId)
	{
	iId = aId;
	}

inline TMsvId TMsvEntry::Parent() const
	{
	return iParentId;
	}

inline void TMsvEntry::SetParent(TMsvId aParentId)
	{
	iParentId = aParentId;
	}

inline TBool TMsvEntry::Complete () const
	{
	return !(iData&KMsvEntryNotCompleteFlag);
	}

inline void TMsvEntry::SetComplete(TBool aComplete)
	{
	iData = (iData & ~KMsvEntryNotCompleteFlag) | ((!aComplete)?KMsvEntryNotCompleteFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::New() const
	{
	return iData&KMsvEntryNewFlag;
	}

inline void TMsvEntry::SetNew(TBool aNew)
	{
	iData = (iData & ~KMsvEntryNewFlag) | (aNew?KMsvEntryNewFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Unread() const
	{
	return iData&KMsvEntryUnreadFlag;
	}

inline void TMsvEntry::SetUnread(TBool aUnread)
	{
	iData = (iData & ~KMsvEntryUnreadFlag) | (aUnread?KMsvEntryUnreadFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Failed() const
	{
	return iData&KMsvEntryFailedFlag;
	}

inline void TMsvEntry::SetFailed(TBool aFailed)
	{
	iData = (iData & ~KMsvEntryFailedFlag) | (aFailed?KMsvEntryFailedFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Operation() const
	{
	return iData&KMsvEntryOperationFlag;
	}

inline void TMsvEntry::SetOperation(TBool aOperation)
	{
	iData = (iData & ~KMsvEntryOperationFlag) | (aOperation?KMsvEntryOperationFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Owner() const
	{
	return iData&KMsvEntryOwnerFlag;
	}

inline void TMsvEntry::SetOwner(TBool aOwner)
	{
	iData = (iData & ~KMsvEntryOwnerFlag) | (aOwner?KMsvEntryOwnerFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Attachment() const
	{
	return iData&KMsvEntryAttachmentFlag;
	}

inline void TMsvEntry::SetAttachment(TBool aAttachmentFlag)
	{
	iData = (iData & ~KMsvEntryAttachmentFlag) | (aAttachmentFlag?KMsvEntryAttachmentFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Visible() const
	{
	return !(iData&KMsvEntryInvisibleFlag);
	}

inline void TMsvEntry::SetVisible(TBool aVisble)
	{
	iData = (iData & ~KMsvEntryInvisibleFlag) | ((!aVisble)?KMsvEntryInvisibleFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::MultipleRecipients() const
	{
	return iData&KMsvEntryMultipleRecipientFlag;
	}

inline void TMsvEntry::SetMultipleRecipients(TBool aMultipleRecipient)
	{
	iData = (iData & ~KMsvEntryMultipleRecipientFlag) | (aMultipleRecipient?KMsvEntryMultipleRecipientFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::ReadOnly() const
	{
	return iData&KMsvEntryReadOnlyFlag;
	}

inline void TMsvEntry::SetReadOnly(TBool aReadOnly)
	{
	iData = (iData & ~KMsvEntryReadOnlyFlag) | (aReadOnly?KMsvEntryReadOnlyFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Deleted() const
	{
	return iData&KMsvEntryDeletedFlag;
	}

inline void TMsvEntry::SetDeleted(TBool aDeletedFlag)
	{
	iData = (iData & ~KMsvEntryDeletedFlag) | (aDeletedFlag?KMsvEntryDeletedFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::StandardFolder() const
	{
	return iData&KMsvEntryStandardFolderFlag;
	}

inline void TMsvEntry::SetStandardFolder(TBool aStandardFolder)
	{
	iData = (iData & ~KMsvEntryStandardFolderFlag) | (aStandardFolder?KMsvEntryStandardFolderFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Connected() const
	{
	return iData&KMsvEntryConnectedFlag;
	}

inline void TMsvEntry::SetConnected(TBool aConnected)
	{
	iData = (iData & ~KMsvEntryConnectedFlag) | (aConnected?KMsvEntryConnectedFlag:KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::InPreparation() const
	{
	return iData&KMsvEntryInPreparationFlag;
	}

inline void TMsvEntry::SetInPreparation(TBool aInPreparation)
	{
	iData = (iData & ~KMsvEntryInPreparationFlag) | (aInPreparation?KMsvEntryInPreparationFlag:KMsvEntryClearFlag);
	}

inline TInt TMsvEntry::PcSyncCount() const
	{
	return iPcSyncCount;
	}

inline void TMsvEntry::IncPcSyncCount()
	{
	iPcSyncCount++;
	}

inline void TMsvEntry::DecPcSyncCount()
	{
	iPcSyncCount--;
	}

inline TUint TMsvEntry::PersistedFlags() const
	{
	return iData&KMsvEntryPersistedFlags;
	}

inline TUint TMsvEntry::TemporaryFlags() const
	{
	return iData&KMsvEntryTemporaryFlags;
	}

inline TBool TMsvEntry::OffPeak() const
	{
	return iData & KMsvOffPeakFlag;
	}

inline void TMsvEntry::SetOffPeak(TBool aOffPeak)
	{
	iData = (iData & ~KMsvOffPeakFlag) | (aOffPeak ? KMsvOffPeakFlag : KMsvEntryClearFlag);
	}

inline TBool TMsvEntry::Scheduled() const
	{
	return iData & KMsvScheduledFlag;
	}

inline void TMsvEntry::SetScheduled(TBool aScheduled)
	{
	iData = (iData & ~KMsvScheduledFlag) | (aScheduled ? KMsvScheduledFlag : KMsvEntryClearFlag);
	}

inline TUint TMsvEntry::SendingState() const
	{
	return (iData & KMsvSendingStateFlags) >> KMsvSendingStateShift;
	}

inline void TMsvEntry::SetSendingState(TUint aSendingState)
	{
	__ASSERT_DEBUG(aSendingState <= KMsvSendStateMax, User::Invariant());
	iData = iData & ~KMsvSendingStateFlags | aSendingState << KMsvSendingStateShift;
	}

//**********************************
// TMsvSelectionOrdering
//**********************************

inline TBool TMsvSelectionOrdering::GroupByType() const
	{
	return iGrouping&KMsvGroupByType;
	}

inline TBool TMsvSelectionOrdering::GroupStandardFolders() const
	{
	return iGrouping&KMsvStandardFolders;
	}

inline TBool TMsvSelectionOrdering::GroupByPriority() const
	{
	return iGrouping&KMsvGroupByPriority;
	}

inline TBool TMsvSelectionOrdering::GroupByMtm() const
	{
	return iGrouping&KMsvGroupByMtm;
	}

inline TBool TMsvSelectionOrdering::ShowInvisibleEntries() const
	{
	return iGrouping&KMsvInvisibleFlag;
	}

inline void TMsvSelectionOrdering::SetGroupByType(TBool aFlag)
	{
	iGrouping = (iGrouping & ~KMsvGroupByStandardFolders) | ((aFlag)?KMsvGroupByType:0);
	}

inline void TMsvSelectionOrdering::SetGroupStandardFolders(TBool aFlag)
	{
	iGrouping = (iGrouping & ~KMsvStandardFolders) | ((aFlag)?KMsvGroupByStandardFolders:0);
	}

inline void TMsvSelectionOrdering::SetGroupByPriority(TBool aFlag)
	{
	iGrouping = (iGrouping & ~KMsvGroupByPriority) | ((aFlag)?KMsvGroupByPriority:0);
	}

inline void TMsvSelectionOrdering::SetGroupByMtm(TBool aFlag)
	{
	iGrouping = (iGrouping & ~KMsvGroupByMtm) | ((aFlag)?KMsvGroupByMtm:0);
	}

inline void TMsvSelectionOrdering::SetShowInvisibleEntries(TBool aFlag)
	{
	iGrouping = (iGrouping & ~KMsvInvisibleFlag) | ((aFlag)?KMsvInvisibleFlag:0);
	}

inline TMsvSorting TMsvSelectionOrdering::Sorting() const
	{
	return iSortType;
	}

inline void TMsvSelectionOrdering::SetSorting(TMsvSorting aSortType)
	{
	iSortType=aSortType;
	}

inline TBool TMsvSelectionOrdering::GroupingOn() const
	{
	return iGrouping&KMsvAllGroupingFlags;
	}

//**********************************
// CMsvEntryFilter
//**********************************

inline TMsvId CMsvEntryFilter::Service() const
	{
	return iServiceId;
	}

inline void CMsvEntryFilter::SetService(TMsvId aServiceId)
	{
	iServiceId = aServiceId;
	}

inline TUid CMsvEntryFilter::Mtm() const
	{
	return iMtm;
	}

inline void CMsvEntryFilter::SetMtm(TUid aMtm)
	{
	iMtm = aMtm;
	}

inline TUid CMsvEntryFilter::Type() const
	{
	return iType;
	}

inline void CMsvEntryFilter::SetType(TUid aType)
	{
	iType = aType;
	}

inline const TTime& CMsvEntryFilter::LastChangeDate() const
	{
	return iLastChange;
	}

inline void CMsvEntryFilter::SetLastChangeDate(const TTime& aLastChange)
	{
	iLastChange = aLastChange;
	}

inline const TMsvSelectionOrdering& CMsvEntryFilter::Order() const
	{
	return iOrdering;
	}

inline void CMsvEntryFilter::SetOrder(const TMsvSelectionOrdering& aOrder)
	{
	iOrdering = aOrder;
	}

inline TUid CMsvEntryFilter::SortMtm() const
	{
	return iSortMtm;
	}

inline void CMsvEntryFilter::SetSortMtm(TUid aSortMtm)
	{
	iSortMtm = aSortMtm;
	}
