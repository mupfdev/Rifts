// AGMTODOS.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMTODOS_H__
#define __AGMTODOS_H__

#include <s32stor.h>
#include "agmdate.h"
#include "agmids.h"
#include "agmcomon.h"
#include "agmrepli.h"

class CAgnEntryModel;

class TAgnTodoDefaults
//
// Default settings given to a new todo entry
//
	{
public:
	IMPORT_C TAgnTodoDefaults();
	inline void SetIsDated(TBool aIsDated);
	inline void SetDaysWarning(TTimeIntervalDays aDaysWarning);
	inline void SetDisplayDueDateAs(CAgnTodo::TDisplayDueDateAs aDisplayAs);
	inline void SetAlarmDefaults(const TAgnAlarmDefaults& aAlarmDefaults);
	inline void SetEntrySymbol(TChar aEntrySymbol);
	inline void SetReplicationStatus(TAgnReplicationData::TStatus aStatus);
	inline TAgnReplicationData::TStatus ReplicationStatus() const;
	inline TBool IsDated() const;
	inline TTimeIntervalDays DaysWarning() const;
	inline CAgnTodo::TDisplayDueDateAs DisplayDueDateAs() const;
	inline const TAgnAlarmDefaults& AlarmDefaults() const;
	inline TChar EntrySymbol() const;
	inline TBool HasEntrySymbol() const;
	inline void SetHasEntrySymbol(TBool aSetting);
	inline void SetBackgroundColor(const TRgb& aColor);
	inline TRgb BackgroundColor() const;
	IMPORT_C TBool operator==(const TAgnTodoDefaults& aOther) const;

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
private:
	TBool						iIsDated;
	TTimeIntervalDays			iDaysWarning;
	CAgnTodo::TDisplayDueDateAs	iDisplayDueDateAs;
	TChar						iEntrySymbol;
	TAgnAlarmDefaults			iAlarmDefaults;
	TAgnReplicationData::TStatus iReplicationStatus;
	TBool						iHasEntrySymbol;
	TRgb						iBackgroundColor;
	};



class TAgnTodoDisplaySettings
//
// Contains the settings that determine how todos belonging to a particular todo list are 
// displayed in views other than the todo view
//
	{
public:
	inline TAgnTodoDisplaySettings();
	inline TBool DisplayEntries() const;
	inline TBool DisplayCrossedOutEntries() const;
	inline TTimeIntervalMinutes DefaultDisplayTime() const;
	IMPORT_C void SetDisplayEntries(TBool aSetting);
	IMPORT_C void SetDisplayCrossedOutEntries(TBool aSetting);
	IMPORT_C void SetDefaultDisplayTime(TTimeIntervalMinutes aTime);	
	inline void ClearAllSettings();
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;
	inline TBool operator==(const TAgnTodoDisplaySettings& aOther) const;
private:
	enum	{
			ETimeMask=0xFFFF,					// store the default time in the lowest 16 bits
			EPriorityMask=0xFF0000,				// store the max priority in the next 8 bits
			EPriorityShift=0x10,
			EDisplayInOtherViewsMask=0x1000000,	// store if entries should be displayed in other views
			EDisplayCrossedOutMask=0x2000000	// store if crossed out entries should be displayed in other views
			};
	TUint32	iSettings;
	};


class CAgnModel;
class CAgnTodoInstanceList;
class CAgnTodoList : public CBase
//
// Contains the details for a todo list, including a manually ordered list of its todo entries
//
	{
public:
	enum {EAddTodoAtEnd=0xFFFF};// Indicates that a new todo should be added to the end of the todo list
	enum TSortOrder {EManual,EByDate,EByPriority};	// Note: this is NOT the sort order of the todos in this
											// object - it is the order they are displayed in the todo view		

	IMPORT_C static CAgnTodoList* NewL();
	IMPORT_C virtual ~CAgnTodoList();
	IMPORT_C void CopyBasicsFrom(const CAgnTodoList* aTodoList);

// accessing (proper)todo list properties:
	inline TPtrC Name() const;
	IMPORT_C void SetName(const TDesC& aName);
	inline TAgnTodoListId Id() const;
	inline TSortOrder SortOrder() const;
	IMPORT_C void SetSortOrder(TSortOrder aSortOrder);
	inline TBool DisplayCrossedOutEntries() const;
	IMPORT_C void SetDisplayCrossedOutEntries(TBool aDisplay);

// accessing defaults for todos belonging to the todo list:
	inline const TAgnTodoDefaults& TodoDefaults() const;
	IMPORT_C void SetTodoDefaults(const TAgnTodoDefaults& aTodoDefaults);
	
// accessing settings for how todos belonging to the todo list are displayed in views other than the todo view
	inline TBool DisplayEntriesInOtherViews() const;
	IMPORT_C void SetDisplayEntriesInOtherViews(TBool aSetting);
	inline TBool DisplayCrossedOutEntriesInOtherViews() const;
	IMPORT_C void SetDisplayCrossedOutEntriesInOtherViews(TBool aSetting);
	inline TTimeIntervalMinutes DefaultDisplayTimeInOtherViews() const;
	IMPORT_C void SetDefaultDisplayTimeInOtherViews(TTimeIntervalMinutes aTime);	
	inline const TAgnTodoDisplaySettings& TodoDisplaySettings() const;
	inline void SetTodoDisplaySettings(const TAgnTodoDisplaySettings& aSettings);
	IMPORT_C void ChangeTodoOrderL(TAgnEntryId aId,TAgnEntryId aTodoPositionReferenceId = AgnModel::NullId());
	inline TInt Count() const;

// The following are not intended to be called from outside the model:
	inline void SetId(TAgnTodoListId aId); 
	inline void Reset();
	inline void InsertL(TInt aPosition,TAgnEntryId aItem);
	inline void AppendL(TAgnEntryId aItem);
	inline void Delete(TInt aPos);
	void AddTodoIdL(TAgnEntryId aId,TAgnEntryId aTodoPositionReferenceId);
	void DeleteTodoId(TAgnEntryId aId);
	TInt Find(TAgnEntryId aId,TInt& aPos);
	inline TAgnEntryId& operator[](TInt aIndex) const; 
	inline const TAgnEntryId& At(TInt aIndex); 
	inline const TAgnReplicationData& ReplicationData() const;
	inline TAgnReplicationData& ReplicationData();
	inline void SetReplicationData(const TAgnReplicationData& aReplicationData);
	inline void SetUniqueId(TAgnUniqueId aUId);
	inline TAgnUniqueId UniqueId() const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;
protected:
	CAgnTodoList();
	void ConstructL();

private:
	CAgnTodoList(const CAgnTodoList&);			// not defined
	CAgnTodoList& operator=(const CAgnTodoList&);	// not defined
private:
	enum {EGranularity=8};
	CArrayFixFlat<TAgnEntryId>*	iTodos;
	TAgnTodoListId				iId;
	TAgnUniqueId				iUniqueId;
	TKeyArrayFix 				iKeyByEntryId;
	TBuf<KAgnMaxTodoListNameLength> iName;			
	TSortOrder					iSortOrder;														
	TBool						iDisplayCrossedOutEntries;
	TAgnTodoDefaults			iTodoDefaults;	
	TAgnTodoDisplaySettings		iHowTodosAreDisplayedInViewsOtherThanTheTodoView;
	TAgnReplicationData			iReplicationData;
	};


class CAgnTodoListList : public CBase
//
// Contains an ordering of todo list ids.
// Note: The TAgnTodoDisplaySettings and replication status is present solely for implementation/efficiency reasons (so 
// other code doesn't have to fetch each individual todo list) and hence is not externalized/internalized.
// The display settings are set upon opening a model after the object has been internalized and are
// thereafter maintained as necessary
//
	{
public:
	struct TListItem
		{
		TAgnTodoListId					iTodoListId;
		TAgnTodoDisplaySettings			iDisplayInfo;
		TAgnReplicationData::TStatus	iReplicationStatus;
		void InternalizeL(RReadStream& aStream);	
		void ExternalizeL(RWriteStream& aStream) const;
		// These internalize and Externalize the whole information set
		// so that the client can see the settings without needing to
		// retrieve the to-do lists
		void InternalizeFullL(RReadStream& aStream);	
		void ExternalizeFullL(RWriteStream& aStream) const;
		};

	IMPORT_C static CAgnTodoListList* NewL();
	IMPORT_C virtual ~CAgnTodoListList();
	const CAgnTodoListList::TListItem& operator[](TInt aIndex) const;
	CAgnTodoListList::TListItem& operator[](TInt index);	
	
	IMPORT_C TAgnTodoListId TodoListId(TInt aIndex) const;
	IMPORT_C TAgnTodoDisplaySettings DisplayInfo(TInt aIndex) const;
	IMPORT_C TAgnReplicationData::TStatus ReplicationStatus(TInt aIndex) const;
	
	inline TInt Count() const;
	void Reset(); 
	IMPORT_C TInt Find(TAgnTodoListId aTodoListId,TInt& aPos) const; 
	inline void InsertL(TInt aPosition,const TListItem* aItem);
	inline void AppendL(const TListItem* aItem); 
	void Delete(TAgnTodoListId aTodoListId);  
	inline void Delete(TInt aPosition);

	void InternalizeL(RReadStream& aStream);	
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeFullL(RReadStream& aStream);	
	void ExternalizeFullL(RWriteStream& aStream) const;
protected:
	CAgnTodoListList();
	void ConstructL();

private:
	CAgnTodoListList(const CAgnTodoListList&);			// not defined
	CAgnTodoListList& operator=(const CAgnTodoListList&);	// not defined

private:
	enum {EGranularity=4};
	CArrayFixFlat<TListItem>*	iTodoLists;
	TKeyArrayFix 			iKeyByTodoListId;
	};


class CAgnDeletedTodoListList : public CBase
//
// If a todo list has been replicated then deleted it isn't deleted, howerver it mustn't be 
// available to views, so deleted todo list ids are stored in here
//
	{
public:
	static CAgnDeletedTodoListList* NewL();
	virtual ~CAgnDeletedTodoListList();

	inline TAgnTodoListId TodoListId(TInt aIndex) const;	
	inline TInt Count() const;
	void Reset(); 
	IMPORT_C TInt Find(TAgnTodoListId aTodoListId,TInt& aPos) const; 
	inline void AppendL(const TAgnTodoListId* aItem); 
	void Delete(TAgnTodoListId aTodoListId);  
	inline void Delete(TInt aPosition);

	void InternalizeL(RReadStream& aStream);	
	void ExternalizeL(RWriteStream& aStream) const;
protected:
	CAgnDeletedTodoListList();
private:
	CAgnDeletedTodoListList(const CAgnDeletedTodoListList&);			// not defined
	CAgnDeletedTodoListList& operator=(const CAgnDeletedTodoListList&);	// not defined
private:
	enum {EGranularity=2};
	CArrayFixFlat<TAgnTodoListId>*	iTodoListIds;
	};


class CAgnTodoListNames : public CBase
//
// Contains a list of todo list names and their ids.
//
	{
public:
	class TListItem
		{
	public:
		inline const TDesC& Name() const;
		inline void SetName(const TDesC& aName);  
		inline TAgnTodoListId TodoListId() const;
		inline void SetTodoListId(TAgnTodoListId aTodoListId); 
		inline CAgnTodoList::TSortOrder SortOrder() const;
		inline void SetSortOrder(CAgnTodoList::TSortOrder aSortOrder);
	private:
		TBuf<KAgnMaxTodoListNameLength>	iName;
		TAgnTodoListId					iTodoListId;
		CAgnTodoList::TSortOrder		iSortOrder;
		};

	IMPORT_C static CAgnTodoListNames* NewL();
	IMPORT_C virtual ~CAgnTodoListNames();
	inline void Reset(); 
	inline TInt Count() const;	
	IMPORT_C TAgnTodoListId TodoListId(TInt aIndex) const;
	IMPORT_C const TDesC& TodoListName(TInt aIndex) const;
	IMPORT_C CAgnTodoList::TSortOrder SortOrder(TInt aIndex) const;
	IMPORT_C const TListItem& operator[](TInt aIndex) const;
	inline void InsertL(TInt aPosition,const TListItem& aItem); 
	inline void AppendL(const TListItem& aItem); 
protected:
	void ConstructL();
	inline CAgnTodoListNames();
private:
	CAgnTodoListNames(const CAgnTodoListNames&);			// not defined
	CAgnTodoListNames& operator=(const CAgnTodoListNames&);	// not defined
private:
	enum {EGranularity=4};
	CArrayFixFlat<TListItem>*			iTodoNameList;
	};


#include "agmtodos.inl"

#endif
