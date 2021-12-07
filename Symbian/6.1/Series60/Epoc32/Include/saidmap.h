// File: SAIDMAP.H
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//
#if !defined(__SAIDMAP_H__)
#define __SAIDMAP_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__AGMIEDIT_H__)
#include <agmiedit.h>
#endif

#if !defined(__AGMMODEL_H__)
#include <agmmodel.h>
#endif

#if !defined(__AGMENTRY_H__)
#include <agmentry.h>
#endif

#if !defined(__AGMSETS_H__)
#include <agmsets.h>
#endif

#if !defined(__AGMUPACT_H__)
#include <agmupact.h>
#endif

#if !defined(__AGMSTORE_H__)
#include <agmstore.h>
#endif

#if !defined(__AGMFILTS_H__)
#include <agmfilts.h>
#endif

#if !defined(__AGMMITER_H__)
#include <agmmiter.h>
#endif

#if defined(_DEBUG)
#define DEBUG_PRINT(x) User::InfoPrint(x);
#else
#define DEBUG_PRINT(x)
#endif

class CSAUidIdMap;
template<class TypeId>
class TSAMapId
	{
public:
friend class CSAUidIdMap;
	inline TypeId AgmId() const;
	inline TAgnUniqueId UniqueId() const;
	inline void SetAgmId(TypeId id);
	inline void SetUniqueId(TAgnUniqueId uid);
	inline void SetType(TInt aType);
	inline TInt Type() const;
protected:
	TypeId				iAgmId;
	TAgnUniqueId		iUniqueId;
	TInt				iType;
	};

template<class TypeId>
inline TypeId TSAMapId<TypeId>::AgmId()	const
	{ return (iAgmId); }

template<class TypeId>
inline TAgnUniqueId TSAMapId<TypeId>::UniqueId() const
	{ return (iUniqueId); }

template<class TypeId>
inline void TSAMapId<TypeId>::SetAgmId(TypeId id)
	{ iAgmId=id; }

template<class TypeId>
inline void TSAMapId<TypeId>::SetUniqueId(TAgnUniqueId uid)
	{ iUniqueId=uid; }

template<class TypeId>
inline void TSAMapId<TypeId>::SetType(TInt aType)
	{ iType = aType; }

template<class TypeId>
inline TInt TSAMapId<TypeId>::Type() const
	{ return (iType);};

class RAgendaServ;
class CSAUidIdMap : public CBase

//
// The CSAUidIdMap object owns a model and builds indexes so the user of this class can use the model
// with UniqueId's for adding/deleting/updating and fetching entries and todolists.
//

	{
public:
	enum TMode {EUsingAgendaServer, EUsingAgendaModel}; // which verison of the agenda engine are we using
	enum {EGranularity=32}; // Indicates array granularity

	// Initalisation functions
	IMPORT_C static CSAUidIdMap* NewL(CAgnEntryModel* aModel, RAgendaServ* aServer, TMode aMode);
	virtual ~CSAUidIdMap();

	// Entry operations
	IMPORT_C virtual TAgnUniqueId AddEntryL(CAgnEntry* aEntry);	//Adds entry to model and returns UniqueId
	IMPORT_C virtual void DeleteEntryL(TAgnUniqueId aUniqueId);	//Deletes entry from model using UniqueId
	IMPORT_C CAgnEntry* FetchEntryL(TAgnUniqueId aUniqueId); //Returns entry from model using UniqueId
	IMPORT_C virtual void UpdateEntryL(CAgnEntry* aEntry); //Updates entry in model.	

	// TodoList operations
	IMPORT_C CAgnTodoList* FetchTodoListL(TAgnUniqueId aUniqueId); //Returns TodoList from model using UniqueId
	IMPORT_C virtual TAgnUniqueId AddTodoListL(CAgnTodoList* aTodoList); //Adds TodoList to model and returns UniqueId
	IMPORT_C virtual void DeleteTodoListL(TAgnUniqueId aUniqueId); //Deletes TodoList from model using UniqueId
	IMPORT_C virtual void UpdateTodoListL(CAgnTodoList* aTodoList);	 //Updates TodoList in model.

	IMPORT_C CAgnEntryModel* Model(); //Returns current EntryModel being used.

	IMPORT_C void BuildMapL(TStreamId aModelRootId);
	IMPORT_C void StartBuildingMapL(TStreamId aModelRootId);
	IMPORT_C TInt BuildMapPortionL();
	IMPORT_C virtual void CancelMapBuilding(); 

	IMPORT_C const CArrayFixSeg<TSAMapId<TAgnTodoListId> >* TodoListMapping() const; 

	IMPORT_C TInt EntryCount() const;
	IMPORT_C TInt TypeFromUId(TAgnUniqueId aUniqueId);
protected:
	CSAUidIdMap(CAgnEntryModel* aModel, RAgendaServ* aServer, TMode aMode);
	void ConstructL();
	void BuildEntryIndexL(TStreamId aModelRootId); //Builds array iEntryIdex of pairs (UniqueId->EntryId) to obtain EntryIds used in model from UniqueIds
	void BuildTodoListIndexL();	//Builds array iTodoListIndex of pairs (UniqueId->TodoListId) to obtain TodoListIds used in model from UniqueIds
	virtual void BuildEntryIndexExtraProcessingL(CAgnEntry* aEntry); 
	virtual void BuildEntryIndexExtraProcessingWithSortEntryL(const CAgnSortEntry* aEntry, TAgnUniqueId aUid, TBool aIsDated);
	virtual void FetchEntriesFromServerL();
	virtual void BuildTodoListIndexExtraProcessingL(CAgnTodoList* aTodoList);
	TAgnEntryId EntryId(TAgnUniqueId aUniqueId);  //Uses iEntryIndex to return EntryId corresponding to UniqueId
	TAgnTodoListId TodoListId(TAgnUniqueId aUniqueId); //Uses iTodoListIndex to return TodoListId corresponding to UniqueId

protected:
	CArrayFixSeg<TSAMapId<TAgnEntryId> >*		iEntryIndex; // array of pairs (UniqueId->EntryId) to obtain EntryIds used in model from UniqueIds
	TKeyArrayFix								iEntryKey;	 // Key to sort iEntryIndex by UniqueId

	CArrayFixSeg<TSAMapId<TAgnTodoListId> >*	iTodoListIndex;	// array of pairs (UniqueId->TodoListId) to obtain TodoListIds used in model from UniqueIds
	TKeyArrayFix								iTodoListKey;	// Key to sort iTodoListIndex by UniqueId

	CAgnEntryModel*								iModel; // Model used to build indexes and retrieve entries and todo lists.
	TInt										iNumStreamsRead; // hom many streams have had entries read from then during building the uid mappings
	TInt										iStreamCount;
	CAgnAppt*									iAppt;
	CAgnAnniv*									iAnniv;
	CAgnEvent*									iEvent;
	CAgnTodo*									iTodo;
	CArrayFixFlat<TStreamId>*					iStreamIdArray;
	TMode										iMode;
	RAgendaServ*								iAgendaServ;
	};


#endif
