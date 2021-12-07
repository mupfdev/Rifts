// CNTFILT.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __CNTFILT_H__
#define __CNTFILT_H__

#include <e32base.h>
#include <d32dbms.h>
#include <cntdb.h>

/** 
 * Contact database filter. 
 * Used to get a subset of the contact items contained in a contact database. 
 */
class CCntFilter : public CBase
	{
public:	
	/**
	  * Flags to set which contact items should be included in the filter.
	  *
	  * Only one of the following values can be set in the filter at a time.
	  * However the client may select to filter contacts in all states using
	  * <code>EIncludeAllContacts</code>.
	  */
	enum TInclude 
		{ 
		EIncludeAllContacts,		/** Contact items in all states should be included in the filter.*/
		EIncludeNewContacts,		/** Only contact items which have been added since the date/time should be included.*/
		EIncludeModifiedContacts,	/** Only contact items which have been modified since the date/time should be included.*/
		EIncludeDeletedContacts		/** Only contact items which have been deleted since the date/time should be included.*/
		};
	/** Contact item types.*/
	enum TContactType
		{
		EIncludeAllTypes = 0x01, /** All contact item types should be included in the filter.*/
		EContactCards = 0x02,	 /** Contact cards should be included in the filter.*/
		EContactGroups = 0x04,   /** Contact card groups should be included in the filter.*/
		EContactTemplates = 0x08,/** Contact card templates should be included in the filter.*/
		EContactOwnCard = 0x10   /** Own cards should be included in the filter.*/
		};

	IMPORT_C static CCntFilter* NewL();
	IMPORT_C static CCntFilter* NewLC();
	IMPORT_C static CCntFilter* NewL(const CCntFilter* aFilter);
	IMPORT_C static CCntFilter* NewLC(const CCntFilter* aFilter);
	IMPORT_C ~CCntFilter();
public:
	CContactIdArray* iIds;
//
	IMPORT_C void SetIncludeModifiedContacts(TBool aIncludeModified); 
	IMPORT_C void SetIncludeNewContacts(TBool aIncludeNew); 
	IMPORT_C void SetIncludeDeletedContacts(TBool aIncludeDeleted);
//
	IMPORT_C TBool TestContactFilterType(TUid aTypeUid);
	IMPORT_C void SetContactFilterTypeALL(TBool aFilterAllContacts);
	IMPORT_C void SetContactFilterTypeCard(TBool aFilterCards);
	IMPORT_C void SetContactFilterTypeGroup(TBool aFilterGroups);
	IMPORT_C void SetContactFilterTypeTemplate(TBool aFilterTemplates);
	IMPORT_C void SetContactFilterTypeOwnCard(TBool aFilterOwnCard);
//
	inline TBool ContactFilterTypeALL() const;
	inline TBool ContactFilterTypeCard() const;
	inline TBool ContactFilterTypeGroup() const;
	inline TBool ContactFilterTypeOwnCard() const;
	inline TBool ContactFilterTypeTemplate() const;
//
	inline TBool IncludeModifiedContacts();
	inline TBool IncludeNewContacts();
	inline TBool IncludeDeletedContacts();
//
	inline TTime GetFilterDateTime();
	inline void SetFilterDateTime(TTime aTime);
//
	IMPORT_C void Reset();
//
	IMPORT_C void Reserved1();
	IMPORT_C void Reserved2();

private:
	TTime            iSinceDateTime;
	TInclude		 iInclude;
	TInt32			 iContactType;
	TAny*	         iReserved1;
	TAny*			 iReserved2;
	CCntFilter();
	CCntFilter(const CCntFilter* aFilter);
	};


/**
 * Tests whether the filter includes only contacts modified since the
 * filter's date/time.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the filter only includes
 *            modified contacts. <code>EFalse</code> if not.
 */
inline TBool CCntFilter::IncludeModifiedContacts()
	{return iInclude == EIncludeModifiedContacts;};

/**
 * Tests whether the filter includes only contacts created since the
 * filter's date/time.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the filter only includes new
 *            contacts. <code>EFalse</code> if not.
 */
inline TBool CCntFilter::IncludeNewContacts()
	{return iInclude == EIncludeNewContacts;};

/**
 * Tests whether the filter includes only contacts deleted since the
 * filter's date/time.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if the filter only includes deleted
 *            contacts. <code>EFalse</code> if not.
 */
inline TBool CCntFilter::IncludeDeletedContacts()
	{return iInclude == EIncludeDeletedContacts;};

/**
 * Returns the date and time used by the filter, as set by
 * <code>SetFilterDateTime()</code>.
 *
 * @returns   "TTime"
 *            The filter's date and time value.
 */
inline TTime CCntFilter::GetFilterDateTime()
	{return iSinceDateTime;};

/**
 * Sets the date and time used by the filter in combination with the
 * <code>TInclude</code> value to test contact items against.
 *
 * @param     "TTime aTime"
 *            The new date and time value.
 */
inline void CCntFilter::SetFilterDateTime(TTime aTime)
	{iSinceDateTime = aTime;};

// CONTACT TYPE
/**
 * Tests whether all contact item types are included in the filter, as
 * set by <code>SetContactFilterTypeALL()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if all contact item types are
 *            included in the filter, <code>EFalse</code> if not.
 */
inline TBool CCntFilter::ContactFilterTypeALL() const
	{return iContactType & EIncludeAllTypes;}

/**
 * Tests whether contact cards are included in the filter, as set by
 * <code>SetContactFilterTypeCard()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if contact cards are included in
 *            the filter <code>EFalse</code> if not.
 */
inline TBool CCntFilter::ContactFilterTypeCard() const
	{return iContactType & EContactCards;}

/**
 * Tests whether contact card groups are included in the filter, as set
 * by <code>SetContactFilterTypeGroup()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if contact card groups are included
 *            in the filter, <code>EFalse</code> if not.
 */
inline TBool CCntFilter::ContactFilterTypeGroup() const
	{return iContactType & EContactGroups;}

/**
 * Tests whether own cards are included in the filter, as set by
 * <code>SetContactFilterTypeOwnCard()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if own cards are included in the
 *            filter <code>EFalse</code> if not.
 */
inline TBool CCntFilter::ContactFilterTypeOwnCard() const
	{return iContactType & EContactOwnCard;}

/**
 * Tests whether contact card templates are included in the filter, as
 * set by <code>SetContactFilterTypeTemplate()</code>.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if contact card templates are
 *            included in the filter, <code>EFalse</code> if not.
 */
inline TBool CCntFilter::ContactFilterTypeTemplate() const
	{return iContactType & EContactTemplates;}

#endif
