// AGNDASVR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
# if !defined(__AGNDASVR_H__)
#define __AGNDASVR_H__


enum TAgnDaSvrCommand
	{
	ECmdQueryVersion			= 0,
	ECmdOpenAgenda				= 1,
	ECmdFetchEntry				= 2,
	ECmdFetchTodoList			= 3,
	ECmdFetchDeletedIds			= 4,
	ECmdFetchDeletedTodoListIds	= 5,
	ECmdFetchDereferencedIds	= 6,
	ECmdFetchApptIds			= 7,
	ECmdFetchAnnivIds			= 8,
	ECmdFetchEventIds			= 9,
	ECmdFetchTodoListArray		= 10,
	ECmdAddEntry				= 11,
	ECmdDeleteEntry				= 12,
	ECmdUpdateEntry				= 13,
	ECmdAddTodoList				= 14,
	ECmdDeleteTodoList			= 15,
	ECmdUpdateTodoList			= 16,
	ECmdNumDeletedEntries		= 17,
	ECmdNumDeletedTodoLists		= 18,
	ECmdNumModifications		= 19,
	ECmdNumEntriesToDereference	= 20,
	ECmdGetLastSyncDate			= 21,
	ECmdSetLastSyncDate			= 22,
	ECmdStartSelectingEntries	= 23,
	ECmdSelectEntriesPortion	= 24,
	ECmdSelectEntries			= 25,
	ECmdCancelSelectEntries		= 26,
	ECmdFetchTodoListIdMap		= 27,
	ECmdCreateAgenda			= 28,
	ECmdCloseAgenda				= 29,
	ECmdCompact					= 30,
	ECmdGetTypeFromUid			= 31,
	ECmdWhichAgendaEngine		= 32,
	ECmdIsFileOpen				= 33,
	ECmdTidyAgenda				= 34,
	ECmdQuit					= 255
	};


const int KAgnDaSvrMajVer	= 2;
const int KAgnDaSvrMinVer	= 1;
const int KAgnDaSvrBldVer	= 1; // PRC ignores this hence set the min version to be the same
//
const int KMaxAgnDaSvrBufferSize = 2048;

enum TAgnDaSvrDataTransferStatus {EAgnDaSvrCompleteDataTransfer, EAgnDaSvrIncompleteDataTransfer};

#endif
 