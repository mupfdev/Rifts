// AGMXSORT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

// ------------------------------------- TAgnSortInstance ----------------------

inline TAgnSortInstance::TAgnSortInstance(CAgnSortEntry* aInfo,TAgnDate aStartDate) 
	{ iInfo = aInfo; iStartDate = aStartDate; }

inline TAgnDate TAgnSortInstance::InstanceDate() 
	{	if (iInfo->Type() == CAgnEntry::ETodo) return iEndDate;
		return iStartDate;
	}

// ------------------------------------- CAgnSortEntry  ------------------------

TAgnEntryId CAgnSortEntry::Id() const
	{

	return iId;
	}

void CAgnSortEntry::SetId(TAgnEntryId aId)
	{

	iId = aId;
	}

// -------------------------------------- CAgnSortAppt -------------------------

const TAgnBasicAppt& CAgnSortAppt::BasicAppt() const
	{ return (iBasicAppt); }

void CAgnSortAppt::SetStartAndEndDateTime(TAgnDateTime aStart,TAgnDateTime aEnd)
	{ iBasicAppt.SetStartAndEndDateTime(aStart,aEnd); }

//inline TBool CAgnSortAppt::IsADayNote() const
//	{ return iBasicAppt.IsADayNote(); }

// -------------------------------------- CAgnSortEvent ------------------------

const TAgnBasicEvent& CAgnSortEvent::BasicEvent() const
	{ return (iBasicEvent); }

// -------------------------------------- CAgnSortAnniv ------------------------

//const TAgnBasicAnniv& CAgnSortAnniv::BasicAnniv() const
//	{ return (iBasicAnniv); }

inline CAgnEntry::TType CAgnSortAnniv::Type() const
	{ return (CAgnEntry::EAnniv); }

// -------------------------------------- CAgnSortTodo -------------------------

const TAgnBasicTodo& CAgnSortTodo::BasicTodo() const
	{ return (iBasicTodo); }

TAgnDurationDays CAgnSortTodo::MaxDuration()
// This is not true the max duration depends upon the due date
// i.e. it must be such that the start date is not before the
// min valid date
//
	{ return (25509); }
// -------------------------------- EOF ----------------------------------------
