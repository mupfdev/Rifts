// File: SASYNC.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__SASYNC_H__)
#define __SASYNC_H__

#if !defined(__SAIDMAP_H__)
#include "saidmap.h"
#endif


class TSAFilter
//
// The TSAFilter is a parameter for the constructor of the SyncAid object. It allows the synchroniser to
// specify the last date the model was synchronised and the date range of the entries the synchroniser is interesed in
//
	{
public:
	IMPORT_C void SetLastSyncDate(TTime aLastSyncDate);
	IMPORT_C void SetStartDate(TTime aStartDate);
	IMPORT_C void SetEndDate(TTime aEndDate);
	IMPORT_C void SetPrevEndDate(TTime aEndDate);
	IMPORT_C void SetRptStartDate(TTime aRptStartDate);

	IMPORT_C TTime LastSyncDate() const;
	IMPORT_C TTime StartDate() const;
	IMPORT_C TTime EndDate() const;
	IMPORT_C TTime PrevEndDate() const;
	IMPORT_C TTime RptStartDate() const;

	IMPORT_C TAgnDateTime LastSyncDateInAgnFormat() const;
	IMPORT_C TAgnDateTime StartDateInAgnFormat() const;
	IMPORT_C TAgnDateTime EndDateInAgnFormat() const;
	IMPORT_C TAgnDateTime PrevEndDateInAgnFormat() const;
	IMPORT_C TAgnDateTime RptStartDateInAgnFormat() const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	TTime iLastSyncDate;
	TTime iStartDate;
	TTime iEndDate;
	TTime iPrevEndDate;
	TTime iRptStartDate;

	TAgnDateTime iAgnFormatLastSyncDate;
	TAgnDateTime iAgnFormatStartDate;
	TAgnDateTime iAgnFormatEndDate;
	TAgnDateTime iAgnFormatPrevEndDate;
	TAgnDateTime iAgnFormatRptStartDate;
	};

class CSATodoListChanges  : public CBase
//
// A CSATodoListChanges is used to pass to the synchroniser to indicate changes in TodoLists in the model.
// It can contain a UniqueId of the TodoList and a list of UniqueIds. If the todolists settings have changed
// but none of the todos in the TodoList have changed the list of UniqueIds will be empty. UniqueIds of todos only
// get placed in the list when they have been changed.
//
// Note: Deleted TodoLists UniqueIds get placed in the DeletedTodoListArray.
//
	{
public:

	enum {EGranularity=32}; // Indicates array granularity

	IMPORT_C static CSATodoListChanges* NewL();
	IMPORT_C virtual ~CSATodoListChanges();
	IMPORT_C void SetTodoListUniqueId(TAgnUniqueId aUniqueId); // assign the UniqueId of TodoList to SyncTodoLIst
	IMPORT_C void AddTodoUniqueIdL(TAgnUniqueId aUniqueId);	 //add UniqueId of todo to SyncTodoList todo array
	IMPORT_C CArrayFixSeg<TUint32>* const TodoArray() const;   //return array of UniqueIds of changed todos.
	IMPORT_C TInt Count();	//returns number of changed todos in todo array.
	IMPORT_C TAgnUniqueId UniqueId(); // returns UniqueId of changed TodoList.
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	CSATodoListChanges();
	void ConstructL();
private:
	TAgnUniqueId				iTodoListUniqueId; //UniqueId of TodoList in model.
	CArrayFixSeg<TUint32>*	iTodoArray;	// array of UniqueIds of todos in the TodoList.
	};


class CSASyncAid : public CSAUidIdMap
//
// The purpose of the CSASyncAid class is to give a synchroniser access to information from the model about
// how it has changed since a given date (LastSyncDate - see TSAFilter). A CSASyncAid	is a CSAUidIdMap
// with extended functionality, as the synchroniser will need access to entries and TodoLists by UniqueId.
// CSASyncAid builds six arrays. There is an array for each entry type, which contains UniqueIds of entrys/TodoLists
// which have changed since the LastSyncDate. As well as an array of UniqueIds for deleted entries. And an array of
// UniqueIds of entries which have been deleted outside of the date range. 
//
	{
public:
	// Initalisation functions
	IMPORT_C static CSASyncAid* NewL(CAgnEntryModel* aModel, RAgendaServ* aServer, TSAFilter aFilter, TMode aMode);
	virtual ~CSASyncAid();
	
	// Retrieval functions used to return arrays needed by synchroniser.
	IMPORT_C CArrayFixSeg<TAgnUniqueId>* const DeletedEntryArray() const;
	IMPORT_C CArrayFixSeg<TAgnUniqueId>* const DeletedTodoListArray() const;
	IMPORT_C CArrayFixSeg<TAgnUniqueId>* const DereferenceArray() const;
	IMPORT_C CArrayFixSeg<TAgnUniqueId>* const ApptArray() const;
	IMPORT_C CArrayFixSeg<TAgnUniqueId>* const AnnivArray() const;
 	IMPORT_C CArrayFixSeg<TAgnUniqueId>* const EventArray() const;
	IMPORT_C CArrayFixSeg<CSATodoListChanges*>* const TodoListArray() const;

	// Statistical functions used to estimate how long synchronisation will take.
	IMPORT_C TInt NumberOfDeletedEntries() const;
	IMPORT_C TInt NumberOfDeletedTodoLists() const;
	IMPORT_C TInt NumberOfModifications() const;
	IMPORT_C TInt NumberOfEntriesToDereference() const;

	IMPORT_C virtual void CancelMapBuilding(); 
protected:
	CSASyncAid(CAgnEntryModel* aModel, RAgendaServ* aServer, TSAFilter aFilter, TMode aMode);
	void ConstructL();
	virtual void BuildEntryIndexExtraProcessingL(CAgnEntry* aEntry); // build Deleted/Dereference/Appt/Anniv and Event arrays.
	virtual void BuildTodoListIndexExtraProcessingL(CAgnTodoList* aTodoList); // build TodoList array.
	virtual void FetchEntriesFromServerL();
	TBool LastChangeDateAfterLastSynchDate(TAgnReplicationData aRepData);	
	TBool EntryIsInRange(const CAgnEntry* aEntry, const TTime& aStart, const TTime& aEnd);
	TBool EntryIsInRange_AgnFormat(const TAgnDateTime& aEntryStart, const TAgnDateTime& aEntryEnd, 
									const TAgnDateTime& aStart, const TAgnDateTime& aEnd);
	TBool AddTodo(const CAgnEntry* aTodo);
	void DoAddEntryToArraysL(CAgnEntry* aEntry);

	TBool EntryIsInRange(const TTime& aEntryStart, const TTime& aEntryEnd, const TTime& aStart, const TTime& aEnd);
	virtual void BuildEntryIndexExtraProcessingWithSortEntryL(const CAgnSortEntry* aEntry, TAgnUniqueId aUid,  TBool aIsDated, 
																TBool aHasBeenDeleted, const TAgnDateTime& aLastChangedDate);
	void DoAddEntryToArraysL(CAgnEntry::TType aType, TAgnUniqueId aUid, TBool aHasBeenDeleted);

	TBool AgnDateTimeGreaterThan(const TAgnDateTime& aLhs, const TAgnDateTime& aRhs);
	TBool AgnDateTimeGreaterOrEqualThan(const TAgnDateTime& aLhs, const TAgnDateTime& aRhs);
	TBool AgnDateTimeLessOrEqualThan(const TAgnDateTime& aLhs, const TAgnDateTime& aRhs);

private:
	TSAFilter							iFilter; // Holds LastSyncDate and Date range for current synchronisation.
	TInt								iNumberOfModifications;
	CArrayFixSeg<TAgnUniqueId>*			iDeletedEntryArray; // Holds UniqueIds of deleted entries.
	CArrayFixSeg<TAgnUniqueId>*			iDeletedTodoListArray; // Holds UniqueIds of deleted todolists.
	CArrayFixSeg<TAgnUniqueId>*			iDereferenceArray; // Holds UniqueIds of deleted entries outside date range.
	CArrayFixSeg<TAgnUniqueId>*			iApptArray;	// Holds UniqueIds of Appts changed since last synchronisation.
	CArrayFixSeg<TAgnUniqueId>*			iAnnivArray; // Holds UniqueIds of Annivs changed since last synchronisation.
 	CArrayFixSeg<TAgnUniqueId>*			iEventArray; // Holds UniqueIds of Events changed since last synchronisation.
	CArrayFixSeg<CSATodoListChanges*>*	iTodoListArray;	// Holds UniqueIds of TodoLists and todos changed since last synchronisation.
	};


#endif



