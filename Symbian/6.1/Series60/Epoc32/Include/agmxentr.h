// AGMXENTR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#ifndef __AGMXENTR_H__
#define __AGMXENTR_H__

#include <e32base.h>
#include <s32std.h>
#include <gdi.h>
#include "agmdate.h"

const TInt KMaxGlobalIDLength = 32;


typedef TBuf<KMaxGlobalIDLength> TAgnGlobalId;

/////////////////////////
//// CAgnAttendee



class CAgnAttendee : public CBase
	{
public:
	// role : default is attendee
	enum TAgnRole {EAttendee, EOrganizer, EOwner, EDelegate};
	// status : default is needs action
	enum TAgnStatus {EAccepted, ENeedsAction, ESent, ETentative,
					 EConfirmed, EDeclined, ECompleted,
					 EDelegated, EReceived};
	// expect : a priority indication - default is FYI
	enum TAgnExpect {EFyi, ERequire, ERequest, EImmediate};

public:
	// construct / destruct functions
	CAgnAttendee();
	IMPORT_C static CAgnAttendee* NewL(const TDesC& aAddress);
	static CAgnAttendee* NewL(RReadStream& aStream);
	static CAgnAttendee* NewL();
	void ConstructL(const TDesC& aAddress);
	~CAgnAttendee();

	// Get functions
	inline TAgnRole Role() const;
	inline TAgnStatus Status() const;
	inline TBool ResponseRequested() const;
	inline TAgnExpect Expect() const;
	IMPORT_C TPtrC Address() const;

	// Set functions
	IMPORT_C void SetRole(TAgnRole aRole);
	IMPORT_C void SetStatus(TAgnStatus aStatus);
	IMPORT_C void SetResponseRequested(TBool aRsvp);	// default is no
	IMPORT_C void SetExpect(TAgnExpect aExpect);

	// Persistence
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	IMPORT_C void Copy(CAgnAttendee* aSource);
private:
	TAgnRole				iRole;
	TAgnStatus				iStatus;
	TAgnExpect				iExpect;
	TBool					iRsvp;
	HBufC*					iAddress;
	};


//
// CAgnCategory
//
class CAgnCategory: public CBase
	{
public:
	// 
	enum TAgnCategoryType {EAppointment, EBusiness, EEducation, EHoliday, EMeeting, EMiscellaneous, 
	EPersonal, EPhoneCall, ESickDay, ESpecialOccasion, 	ETravel, EVacation, EExtended};

public:
	// construct / destruct functions
	IMPORT_C static CAgnCategory* NewL(TAgnCategoryType aCategory);
	IMPORT_C static CAgnCategory* NewL(const TDesC& aExtendedName);
	static CAgnCategory* NewL(RReadStream& aStream);
	static CAgnCategory* NewL();
	~CAgnCategory();

	// Get functions
	inline TAgnCategoryType Category() const;
	IMPORT_C const TPtrC ExtendedCategoryName() const;

	// Persistence
	void InternalizeL(RReadStream& aStream);
	void ExternalizeL(RWriteStream& aStream) const;

	IMPORT_C void Copy(CAgnCategory* aSource);
	TInt SizeOfCategory();
private:
	CAgnCategory();
	void ConstructL(TAgnCategoryType aCategory,const TDesC& aExtendedName);
	static CAgnCategory* CreateCategoryL(TAgnCategoryType aCategory,const TDesC& aExtendedName);
private:
	HBufC*				iExtendedCategoryName;
	TAgnCategoryType	iCategoryType;
	};




/////////////////////////
/// CAgnExtendedEntry

class CAgnExtendedEntry : public CBase
	{
public:
	CAgnExtendedEntry();
	~CAgnExtendedEntry();
	static CAgnExtendedEntry* NewL();

	// Attendee functions
	TBool HasAttendees();
	TInt AttendeeCount();
	void AddAttendeeL(CAgnAttendee* aAttendee);
	CAgnAttendee* FetchAttendee(TInt aIndex);
	void DeleteAttendee(TInt aIndex);

	// Global ID functions
	void SetGlobalId(const TDesC& aGlobalId);
	TDesC& GlobalId();
	TBool HasGlobalId();

	// Location functions
	void SetLocationL(const TDesC& aLocation);
	TPtrC Location();


	// Persistence
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);
	void CopyL(CAgnExtendedEntry* aSource);
	void SetCreationDate(TAgnDate aCreationDate);
	inline TAgnDate CreationDate() const;

	// Category list
	TBool HasCategory();
	TInt CategoryCount();
	void AddCategoryL(CAgnCategory* aCategory);
	CAgnCategory* FetchCategory(TInt aIndex);
	void DeleteCategory(TInt aIndex);

	// Entry symbol color
	void SetBackgroundColor(const TRgb& aColor);
	TRgb GetBackgroundColor() const;
private:
	CArrayPtrFlat<CAgnAttendee>*	iAttendeeList;
	TAgnGlobalId					iGlobalId;
	HBufC*							iLocation;
	TAgnDate						iCreationDate;
	CArrayPtrFlat<CAgnCategory>*	iCategoryList;
	TRgb							iBackgroundSymbolColor;
	};



// Inline functions

CAgnAttendee::TAgnRole CAgnAttendee::Role() const
	{
	return iRole;
	}

CAgnAttendee::TAgnStatus CAgnAttendee::Status() const
	{
	return iStatus;
	}

TBool CAgnAttendee::ResponseRequested() const
	{
	return iRsvp;
	}

CAgnAttendee::TAgnExpect CAgnAttendee::Expect() const
	{
	return iExpect;
	}


TAgnDate CAgnExtendedEntry::CreationDate() const
	{
	return iCreationDate;
	}

CAgnCategory::TAgnCategoryType CAgnCategory::Category() const
	{
	return iCategoryType;
	}


#endif
