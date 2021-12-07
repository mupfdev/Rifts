// AGMENTRY.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __AGMENTRY_H__
#define __AGMENTRY_H__

#include <e32base.h>
#include "agmrptd.h"
#include "agmbasic.h"
#include "agmids.h"
#include "agmpanic.h"
#include <txtmrtsr.h>
#include "agmrepli.h"
#include "agmxentr.h"


// ------------------------------- Local classes ---------------------------
class TAgnRichTextStoreResolver;
class CAgnEntry;
class CAgnAppt;
class CAgnEvent;
class CAgnAnniv;
class CAgnTodo;
class TAgnEntryStorer;
class CAgnEntryServerData;

// ------------------------- Referenced clases ------------------------------
class CStreamStore;
class CAgnEntryManager;
class CParaFormatLayer;
class CCharFormatLayer;
class CRichText;
class MPictureFactory;
class MRichTextStoreResolver;
class RAgendaServ;
class CAgnExtendedEntry;


// -------------------------------------------------------------------------
class TAgnRichTextStoreResolver : public MRichTextStoreResolver
//
// Supplied to a rich text object prior to a restoration of pictures so that it knows
// which store to load them from
//
	{
public:
	inline TAgnRichTextStoreResolver(const CStreamStore& aStore) : iStore(aStore){};
	virtual const CStreamStore& StreamStoreL(TInt) const;
private:
	const CStreamStore& iStore;
	};


class CAgnEntry : public CAgnBasicEntry
//
// Abstract base class containing details common to all entries
// 
	{
public:
	friend class CAgnEntryManager;
	friend class AgnEntryStorer;
	friend class TAgnInstanceEditor;
	friend class AgnModel;	
	enum TType {EAppt,ETodo,EEvent,EAnniv};

	// following enums for internal use only: (public so test code can use them)
	enum TCopyHow {EDeepCopy,EShallowCopy};	
	enum TIncludeIdWhenComparing {ECompareId,EDontCompareId};
	enum TCreateHow {ECreateRichText,EDontCreateRichText};
	enum TMode {ENormal, EExtended, EClient, EClientAddEntry, EServer};

	IMPORT_C ~CAgnEntry();
	virtual TType Type() const=0;
	IMPORT_C const CAgnAppt* CastToAppt() const;
	IMPORT_C const CAgnTodo* CastToTodo() const;
	IMPORT_C const CAgnEvent* CastToEvent() const;
	IMPORT_C const CAgnAnniv* CastToAnniv() const;
	IMPORT_C CAgnAppt* CastToAppt();
	IMPORT_C CAgnTodo* CastToTodo();
	IMPORT_C CAgnEvent* CastToEvent();
	IMPORT_C CAgnAnniv* CastToAnniv();
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory)=0;  
	IMPORT_C TBool CompareL(CAgnEntry* aEntry,TIncludeIdWhenComparing aCompareId = ECompareId);

// alarm stuff
	IMPORT_C TPtrC AlarmSoundName() const;
	IMPORT_C void SetAlarmSoundNameL(const TDesC& aAlarmSoundName);
	IMPORT_C void ClearAlarm();

// Synchronisation stuff
	IMPORT_C virtual void SetLastChangedDate();	
	inline void SetUniqueId(TAgnUniqueId aUId);
	inline TAgnUniqueId UniqueId() const;
	inline const TAgnReplicationData& ReplicationData() const;
	inline TAgnReplicationData& ReplicationData();
	inline void SetReplicationData(const TAgnReplicationData& aReplicationData);
	
// Other common stuff
	IMPORT_C void SetRptDefL(const CAgnRptDef* aRptDef);
	IMPORT_C void MakeInstanceNonRepeating();
	IMPORT_C CRichText* RichTextL();
	IMPORT_C virtual TTime InstanceStartDate() const = 0; // includes time for appts/day notes
	IMPORT_C virtual TTime InstanceEndDate() const = 0;	  // includes time for appts/daynotes
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const = 0;

// Persistence
	IMPORT_C TStreamId StoreComponentsL(CStreamStore& aStore);
	IMPORT_C void RestoreComponentsL(const CStreamStore& aStore);
	void RestoreComponentsL(RReadStream& aReadStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C CStreamStore* OpenRichTextStoreL();
	IMPORT_C CStreamStore* OpenEmbeddedStoreL();
	IMPORT_C void CloseEmbeddedStore();
	IMPORT_C CStreamStore* EmbeddedStore() const;
	IMPORT_C void LoadAllComponentsL(const MPictureFactory* aPictureFactory);
	void SetOriginatingStore(const CStreamStore& aStore);
	const CStreamStore& OriginatingStore() const;
	inline void SetRichTextStreamId(TStreamId aId);	
	inline TStreamId RichTextStreamId() const;

// Ids
	inline TAgnDate InstanceDate() const;
	inline TAgnEntryId EntryId() const;
	inline TAgnInstanceId InstanceId() const;
	inline void SetId(TAgnEntryId aId);	 
	inline void SetInstanceDate(TAgnDate aDate); 
	inline void SetIdAndInstanceDate(TAgnEntryId aId,TAgnDate aDate); 
	inline void SetIdAndInstanceDate(const TAgnInstanceId& aInstanceId); 
	inline void SetInstanceId(const TAgnInstanceId& aInstanceId); 

	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow) = 0;
	void SetRichText(CRichText* aRichText);
	void SetServer(RAgendaServ* aServer, TBool aAddEntry=EFalse);
	void SetServer();
	void SetExtended();
	void SetHowRichTextIsStored(); 
	void ExternalizeToBufferL(RWriteStream& aStream,RWriteStream& aTextStream) const;
	void InternalizeFromBufferL(RReadStream& aStream, CBufFlat* aTextBuffer);


	// Extended Entry functions
	IMPORT_C void SetGlobalIdL(const TDesC& aGlobalId);
	IMPORT_C TDesC& GlobalId();
	IMPORT_C TBool HasGlobalId();

	IMPORT_C void SetLocationL(const TDesC& aLocation);
	IMPORT_C TPtrC Location();


	IMPORT_C TBool HasAttendees();
	IMPORT_C TInt AttendeeCount();
	IMPORT_C CAgnAttendee* FetchAttendee(TInt aIndex);
	IMPORT_C void AddAttendeeL(CAgnAttendee* aAttendee);
	IMPORT_C void DeleteAttendee(TInt aIndex);

	IMPORT_C void SetCreationDateL(TAgnDate aCreationDate);
	IMPORT_C TAgnDate CreationDate();
	
	void ExternalizeBCL(RWriteStream& aStream) const;
	void ExternalizeExtendedL(RWriteStream& aStream) const;
	void InternalizeBCL(RReadStream& aStream);
	void InternalizeExtendedL(RReadStream& aStream);
	
	// Category list
	IMPORT_C TBool HasCategory();
	IMPORT_C TInt CategoryCount();
	IMPORT_C void AddCategoryL(CAgnCategory* aCategory);
	IMPORT_C CAgnCategory* FetchCategory(TInt aIndex);
	IMPORT_C void DeleteCategory(TInt aIndex);

	IMPORT_C void SetBackgroundColorL(const TRgb& aColor);
	IMPORT_C TRgb GetBackgroundColor() const;
protected:	
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const = 0; // includes time for appts/day notes
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const = 0;	  // includes time for appts/daynotes
	void ConstructL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow);
	virtual void StoreSpecificsL(RWriteStream& aStream) const=0;
	virtual void RestoreSpecificsL(RReadStream& aStream)=0;
	void StoreShallowL(RWriteStream& aStream) const;
	void RestoreShallowL(RReadStream& aStream);
	void CopyBasicDetailsFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopy);
	void AdjustStartDateAccordingToRepeatStartDate(const TTime& aRptStartDate);
	void StoreToBufferL(RWriteStream& aStream, RWriteStream& aTextStream) const;
	void RestoreFromBufferL(RReadStream& aStream, CBufFlat* aTextBuffer);
protected:
	enum {ETextArrayGranularity = 32, ERichTextInlineThreshold = 128};
	TAgnInstanceId 				iInstanceId; // the entry's instance Id
	HBufC* 						iAlarmSoundName; // the alarm pre-time is stored in CAgnBasicEntry
	const CStreamStore*			iOriginatingStore;	// The store from which the entry was fetched
	CRichText*					iRichText;
	TStreamId					iRichTextStreamId;
	const CParaFormatLayer*		iParaFormatLayer;
	const CCharFormatLayer*		iCharFormatLayer;
	TAgnUniqueId				iUniqueId;	 // the entry's unique Id
	TAgnReplicationData			iReplicationData;
	CAgnEntryServerData*		iServerData;
private:
	IMPORT_C virtual void CAgnEntry_Reserved1();
	TAny* CAgnEntry_Reserved;
	};


class CAgnEntryServerData : public CBase
	{
public:
	CStreamStore*				iEmbeddedStore;
	RAgendaServ*				iServer;
	CBufFlat*					iTextBuffer;
	CAgnEntry::TMode			iEntryMode;
	CAgnExtendedEntry*			iExtended;	// Extended attributes
	};


class CAgnAppt : public CAgnEntry
	{
public:
	IMPORT_C static CAgnAppt* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText); 
	IMPORT_C static CAgnAppt* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText); 
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TType Type() const;
	IMPORT_C TTime StartDateTime() const;
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const; 
	IMPORT_C TTime EndDateTime() const; 
	IMPORT_C void SetStartAndEndDateTime(const TTime& aStartDateTime,const TTime& aEndDateTime=Time::NullTTime());
	IMPORT_C void SetDisplayTime(TTimeIntervalMinutes aDisplayTime);
	IMPORT_C virtual TTime InstanceStartDate() const;
	IMPORT_C virtual TTime InstanceEndDate() const;
	inline const TAgnBasicAppt& BasicAppt() const;
	void SetDisplayTimeOnly(TTimeIntervalMinutes aDisplayTime);
protected:
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const;
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const;
	virtual TAgnDateTime AlarmOrigin() const;
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	CAgnAppt();
	CAgnAppt(const CAgnAppt&);
	CAgnAppt& operator=(const CAgnAppt&);
private:
	TAgnBasicAppt iBasicAppt;
	};


class CAgnEvent	: public CAgnEntry
	{
public:
	IMPORT_C static CAgnEvent* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C static CAgnEvent* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const;
	IMPORT_C  void SetDisplayTime(TTimeIntervalMinutes aDisplayTime);
	IMPORT_C TTime StartDate() const;
	IMPORT_C TTime EndDate() const;
	IMPORT_C void SetStartAndEndDate(const TTime& aStartDate,const TTime& aEndDate=Time::NullTTime());
	IMPORT_C virtual TType Type() const;
	IMPORT_C virtual TTime InstanceStartDate() const;
	IMPORT_C virtual TTime InstanceEndDate() const;
	inline const TAgnBasicEvent& CAgnEvent::BasicEvent() const;
	void SetDisplayTimeOnly(TTimeIntervalMinutes aDisplayTime);
protected:
	CAgnEvent();
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const;
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const;
	virtual TAgnDateTime AlarmOrigin() const;
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:	
	CAgnEvent(const CAgnEvent&);
	CAgnEvent& operator=(const CAgnEvent&);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	TAgnBasicEvent iBasicEvent;
	};


class CAgnAnniv	: public CAgnEvent
	{
public:
	enum TDisplayAs 
			{
			ENone,			// none of the following
			EBaseYear,		// Display base year
			EElapsedYears,	// Display elapsed years
			EBaseAndElapsed	// Display both base and elapsed years
			};

	IMPORT_C static CAgnAnniv* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C static CAgnAnniv* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TType Type() const;
	inline TTimeIntervalYears BaseYear() const;
	inline TBool HasBaseYear() const;
	inline TDisplayAs DisplayAs() const;
	IMPORT_C void SetBaseYear(TTimeIntervalYears aBaseYear);
	IMPORT_C void SetDisplayAs(TDisplayAs aDisplayAs);
	inline void SetHasBaseYear(TBool aHasBaseYear);
protected:
	CAgnAnniv();
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:	
	CAgnAnniv(const CAgnAnniv&);
	CAgnAnniv& operator=(const CAgnAnniv&);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	TTimeIntervalYears 	iBaseYear;
	TDisplayAs 			iDisplayAs;
	TBool				iHasBaseYear;
	};


class CAgnTodo	: public CAgnEntry
	{
public:
	enum TDisplayDueDateAs 
			{
			EAutomatic,		// Display as a date until within one week of the due date, then shown as, for example, "Next Wed"
			EDate,			// Always dsiplay as a date
			EDays,			// Display as the number of days until the due date
			EDontDisplay	// Never display the due date
			};

	IMPORT_C static CAgnTodo* NewL(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C static CAgnTodo* NewLC(const CParaFormatLayer* aParaFormatLayer,const CCharFormatLayer* aCharFormatLayer,TCreateHow aCreateHow = ECreateRichText);
	IMPORT_C virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory);
	IMPORT_C virtual TType Type() const;
	inline TAgnTodoListId TodoListId() const;
	IMPORT_C void SetTodoListId(TAgnTodoListId aTodoListId);
	inline TDisplayDueDateAs DisplayDueDateAs() const;
	IMPORT_C void SetDisplayDueDateAs(TDisplayDueDateAs aDisplayAs);
	inline TUint Priority() const;
	IMPORT_C void SetPriority(TUint aPriority);
	IMPORT_C virtual TTimeIntervalMinutes DisplayTime() const;
	IMPORT_C void SetDisplayTime(TTimeIntervalMinutes aDisplayTime);
	IMPORT_C TTime DueDate() const;
	IMPORT_C void SetDueDate(const TTime& aDate);
	IMPORT_C TTime CrossedOutDate() const;
	IMPORT_C void CrossOut(const TTime& aDate);
	IMPORT_C void CAgnTodo::UnCrossOut();
	inline TTimeIntervalDays Duration() const;
	IMPORT_C void SetDuration(TTimeIntervalDays aDuration);
	IMPORT_C void SetAlarmFromDueDate();
	IMPORT_C void SetAlarmFromStartDate();
	inline TBool IsAlarmSetFromDueDate() const;
	inline TBool IsAlarmSetFromStartDate() const;
	IMPORT_C TBool IsDated() const;
	IMPORT_C void MakeUndated();
	IMPORT_C virtual TTime InstanceStartDate() const;
	IMPORT_C virtual TTime InstanceEndDate() const;
	inline const TAgnBasicTodo& BasicTodo() const;
	void SetDisplayTimeOnly(TTimeIntervalMinutes aDisplayTime);
protected:
	virtual TAgnDateTime InstanceStartDateAsAgnDate() const;
	virtual TAgnDateTime InstanceEndDateAsAgnDate() const;
	virtual TAgnDateTime AlarmOrigin() const;
	CAgnTodo();
	virtual void CopyFromL(CAgnEntry* aSource,const MPictureFactory* aPictureFactory,TCopyHow aCopyHow);
private:
	CAgnTodo(const CAgnTodo&);
	CAgnTodo& operator=(const CAgnTodo&);
	virtual void StoreSpecificsL(RWriteStream& aStream) const;
	virtual void RestoreSpecificsL(RReadStream& aStream);
private:
	IMPORT_C /*virtual*/ void CAgnEntry_Reserved1();
private:
	TAgnBasicTodo 		iBasicTodo;
	TDisplayDueDateAs	iDisplayDueDateAs; // Indicates how the due date should be displayed
	};



class AgnEntryStorer
	{
public:
	IMPORT_C static TStreamId StoreEntryL(CStreamStore& aStore,CAgnEntry* aEntry);
	IMPORT_C static CAgnEntry* RestoreEntryL(const CStreamStore& aStore,TStreamId aStreamId,
							const CParaFormatLayer* aParaFormatLayer,
							const CCharFormatLayer* aCharFormatLayer);
	IMPORT_C static CAgnEntry* RestoreEntryL(RReadStream& aStream,
							const CParaFormatLayer* aParaFormatLayer,
							const CCharFormatLayer* aCharFormatLayer);
	};

#include "agmentry.inl"

#endif
