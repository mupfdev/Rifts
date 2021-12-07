// AGMXSORT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMXSORT_H__
#define __AGMXSORT_H__

#include <e32base.h>
#include "agmbasic.h"
#include "agmentry.h"

// -------------------------------------- Local classes ------------------------
class CAgnSortEntry;
class CAgnSortAppt;
class CAgnSortEvent;
class CAgnSortAnniv;
class CAgnSortTodo;
class CAgnMemPage;

// -------------------------------------- Referenced classes -------------------
class CAgnEntry;
class CAgnAppt;
class CAgnEvent;
class CAgnTodo;
class CAgnAnniv;
// -----------------------------------------------------------------------------

// ----------------------------TAgnSortInstance---------------------------------
class TAgnSortInstance
	{
public:
	TAgnSortInstance() {}
	TAgnSortInstance(CAgnSortEntry* aInfo,TAgnDate aStartDate);
	TAgnDate InstanceDate() const;
	TAgnInstanceId InstanceId() const;
	TTime /*TAgnDateTime*/ InstanceAlarmDateTime() const; 
	const CAgnSortEntry*	iInfo;		// info entry
	TAgnDate				iStartDate;	// instance  start date
	TAgnDate				iEndDate;	// instance end date
	};
// ----------------------------------- CAgnSortEntry ---------------------------
class CAgnSortEntry : public CAgnBasicEntry
	{
public:
	virtual CAgnEntry::TType Type() const=0; 
	void CopyL(const CAgnEntry* aEntry);
	void ReplaceWithL(CAgnSortEntry* aSortEntry);
	// Get and set Id
	void SetId(TAgnEntryId aId);
	IMPORT_C TAgnEntryId Id() const;
	// 
	TInt operator==(const CAgnEntry& aEntry) const;
	TInt operator!=(const CAgnEntry& aEntry) const;
	TInt operator==(const CAgnSortEntry& aEntry) const;
	TInt operator!=(const CAgnSortEntry& aEntry) const;
	//
	virtual TAgnDateTime StartDateTime() const = 0;
	virtual TAgnDateTime EndDateTime() const = 0;
	virtual TBool GetCrossedOutDate(TAgnDate& aDate) const;
	virtual TAgnTime DisplayTime() const = 0;
	IMPORT_C TAgnDate ValidFromDate() const;
	IMPORT_C TAgnDate ValidToDate() const;
	virtual TAgnTodoListId ListId() const;
	TAgnDurationDays Duration() const;
	TRgb SymbolColor() const;
	IMPORT_C virtual TUint Priority() const;
	virtual void ExternalizeL(RWriteStream& aStream);
	virtual void InternalizeL(RReadStream& aStream);
protected:
	virtual TBool Compare(const CAgnEntry* aEntry) const = 0;	
	virtual TBool Compare(const CAgnSortEntry* aEntry) const = 0;	
	virtual void UpdateDetails(const CAgnSortEntry* aSortEntry) = 0;
	virtual void UpdateDetails(const CAgnEntry* aEntry) = 0;
private:
	TAgnEntryId iId;
	TRgb iSymbolColor;
	};

// ----------------------------------- CAgnSortEntryAllocator ------------------
class CAgnSortEntryAllocator : public CBase
	{
public:
	static CAgnSortEntryAllocator* NewL();
	~CAgnSortEntryAllocator();
	CAgnSortEntry* NewL(TUint aSize);	
	void Delete(CAgnSortEntry* aEntry);	
private:
	CAgnSortEntryAllocator();
	void DeleteMemPage(CAgnMemPage* aPage);
	CAgnMemPage* iHeadPage;
	TInt iCount;
	};
// ----------------------------------- CAgnSortAppt ----------------------------
class CAgnSortAppt : public CAgnSortEntry
	{
public:
	IMPORT_C TAny* operator new(TUint aSize,TLeave aType,CAgnSortEntryAllocator* aAllocator);
	IMPORT_C static CAgnSortAppt* NewL(CAgnSortEntryAllocator* aAllocator);
	IMPORT_C static CAgnSortAppt* NewL(const CAgnAppt* aEntry,CAgnSortEntryAllocator* aAllocator);
	virtual CAgnEntry::TType Type() const;
	const TAgnBasicAppt& BasicAppt() const;
	void SetStartAndEndDateTime(TAgnDateTime aStart,TAgnDateTime aEnd);
	virtual TAgnDateTime StartDateTime() const;
	virtual TAgnDateTime EndDateTime() const;
	virtual TAgnTime DisplayTime() const;
protected:
	virtual TBool Compare(const CAgnEntry* aEntry) const; 	// compare info details
	virtual TBool Compare(const CAgnSortEntry* aEntry) const; 	// compare info details
	virtual void UpdateDetails(const CAgnSortEntry* aEntry);
	virtual void UpdateDetails(const CAgnEntry* aEntry);
	virtual void ExternalizeL(RWriteStream& aStream);
	virtual void InternalizeL(RReadStream& aStream);
private:
	TAny* operator new(TUint aSize,TLeave aType);
	TAgnBasicAppt iBasicAppt;
	CAgnSortAppt();
	};

class CAgnMemPage : public CBase
	{
public:
	CAgnMemPage(TUint aCellSize);
	~CAgnMemPage();
	static CAgnMemPage* NewL(TUint aCellSize);
	void ConstructL();
	TBool IsFull() const;
	TBool IsEmpty() const;
	CAgnMemPage* Next() const;
	void SetNext(CAgnMemPage* aNext);
	TAny* Alloc();
	void Free(CAgnSortEntry* aPtr);
	TBool Contains(TAny* aPtr) const;
	TUint CellSize() const;
private:
	CAgnMemPage* iNext;
	TInt8* iEntries;
	TInt8* iNextAvail;
	TInt8* iFirstFree;
	TInt iCount;
	TUint iCellSize;
	};

// ----------------------------------- CAgnSortEvent ---------------------------
class CAgnSortEvent : public CAgnSortEntry
	{
public:
	IMPORT_C TAny* operator new(TUint aSize,TLeave aType,CAgnSortEntryAllocator* aAllocator);
	static CAgnSortEvent* NewL(CAgnSortEntryAllocator* aAllocator);
	static CAgnSortEvent* NewL(const CAgnEvent* aEntry,CAgnSortEntryAllocator* aAllocator);
	const TAgnBasicEvent& BasicEvent() const;
	virtual CAgnEntry::TType Type() const;
	virtual TAgnDateTime StartDateTime() const;
	virtual TAgnDateTime EndDateTime() const;
	virtual TAgnTime DisplayTime() const;
protected:
	virtual TBool Compare(const CAgnEntry* aEntry) const; 	// compare info details
	virtual TBool Compare(const CAgnSortEntry* aEntry) const; 	// compare info details
	virtual void UpdateDetails(const CAgnSortEntry* aEntry);
	virtual void UpdateDetails(const CAgnEntry* aEntry);
	CAgnSortEvent();
	virtual void ExternalizeL(RWriteStream& aStream);
	virtual void InternalizeL(RReadStream& aStream);
private:
	TAny* operator new(TUint aSize,TLeave aType);
	TAgnBasicEvent iBasicEvent;
	};


// ----------------------------------- CAgnSortAnniv ---------------------------
class CAgnSortAnniv : public CAgnSortEvent
	{
public:
	IMPORT_C TAny* operator new(TUint aSize,TLeave aType,CAgnSortEntryAllocator* aAllocator);
	static CAgnSortAnniv* NewL(CAgnSortEntryAllocator* aAllocator);
	static CAgnSortAnniv* NewL(const CAgnAnniv* aEntry,CAgnSortEntryAllocator* aAllocator);
	virtual CAgnEntry::TType Type() const;
protected:
private:
	CAgnSortAnniv();
	};


// ----------------------------------- CAgnSortTodo ----------------------------
class CAgnSortTodo : public CAgnSortEntry
	{
public:
	IMPORT_C TAny* operator new(TUint aSize,TLeave aType,CAgnSortEntryAllocator* aAllocator);
	static CAgnSortTodo* NewL(CAgnSortEntryAllocator* aAllocator);
	static CAgnSortTodo* NewL(const CAgnTodo* aEntry,CAgnSortEntryAllocator* aAllocator);
	const TAgnBasicTodo& BasicTodo() const;
	virtual CAgnEntry::TType Type() const;
	virtual TAgnDateTime StartDateTime() const;
	virtual TAgnDateTime EndDateTime() const;
	virtual TBool GetCrossedOutDate(TAgnDate& aDate) const;
	virtual TAgnTime DisplayTime() const;
	static TAgnDurationDays MaxDuration();
	virtual TAgnTodoListId ListId() const;
	IMPORT_C virtual TUint Priority() const;
protected:
	virtual TBool Compare(const CAgnEntry* aEntry) const; 	// compare info details
	virtual TBool Compare(const CAgnSortEntry* aEntry) const; 	// compare info details
	virtual void UpdateDetails(const CAgnSortEntry* aEntry);
	virtual void UpdateDetails(const CAgnEntry* aEntry);
	virtual void ExternalizeL(RWriteStream& aStream);
	virtual void InternalizeL(RReadStream& aStream);
private:
	TAny* operator new(TUint aSize,TLeave aType);
	TAgnBasicTodo iBasicTodo;
	CAgnSortTodo();
	};

#endif
// -------------------------------- EOF ----------------------------------------
