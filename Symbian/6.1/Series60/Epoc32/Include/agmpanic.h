// AGMPANIC.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMPANIC_H__
#define __AGMPANIC_H__

enum TAgmPanic
	{
	EAgmErrBadModelState = 0, // the model was in a state inconsistent with an action being requested of it
	EAgmErrBadEntry = 1,	 // an entry contains bad or conflicting data
	EAgmErrBadTodoList = 2, // a todo list contains bad or conflicting data
	EAgmErrBadTodoDefaults = 3, // the todo defaults contain bad or conflicting data
	EAgmErrEntryDoesntHaveRichText = 4, 
	EAgmErrNullDate = 5,
	EAgmErrInvalidCastToAppt = 6, // attempted to cast an entry to an appt that wan't an appt
	EAgmErrInvalidCastToEvent = 7, // attempted to cast an entry to an event that wan't an event
	EAgmErrInvalidCastToAnniv = 8, // attempted to cast an entry to an anniv that wan't an anniv
	EAgmErrInvalidCastToTodo = 9, // attempted to cast an entry to a todo that wan't a todo
	EAgmErrDateOutsideOfValidRange = 10, // Attempting to set a date outside of the valid range for the agenda
	EAgmErrOutsideArrayRange = 11,	// attempted to access element of array out side range
	EAgmErrNullPtr = 12,				// null pointer
	EAgmErrDeleteItemNotFound = 13,	// attempting to delete an item that wasn't found
	EAgmErrIteratorNullIndex = 14,	
	EAgmErrCompoundIteratorOutOfRange = 15,
	EAgmErrEntryHasNullTime = 16,
	EAgmErrParamHasNullDate = 17,
	EAgmErrHasNoInstances = 18,		// all instances of a repeating entry are exceptions
	EAgmErrInvalidInstance = 19, // i.e. tried to fetch an instance that couldn't be generated from the repeat details
	EAgnErrEntryManagerInternalError = 20, //something has gone wrong with the entry cluster management i.e
									// when storing the buffer there are more entries in it then the allowable maximum
	EAgnErrEntryHasBeenDeleted = 21, // performing an operation on an entry that has been deleted
	EAgnErrSortEntryNotFound = 22,	// Sort entry not found in index
	EAgnErrInvalidIndexNumber = 23,	// Requested an index that doesn't exist
	EAgmWrongStore = 24, // i.e. the stream from which an entry originates isn't the same to which its now being updated/deleted
	EAgmErrAlarmRequestAlreadyRequested = 25, // calling CAgnAlarmServerTerminationActive::RequestServerTerminationNotification more than once
	EAgnErrAlarmRequestWithCallbackSet = 26,  //CAgnAlarmServerTerminationActive::RequestServerTerminationNotification with a callback set
	EAgmFilterInvalidPriority=27,
	EAgmFilterNoMaxPrioritySet=28,
	EAgmPanicTidyFilterCrossedOutNotIncluded=29,
	EAgmNotSupported=30
	};


#endif
