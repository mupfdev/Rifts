/*
* ============================================================================
*  Name     : AknCheckBoxSettingPage.h
*  Part of  : Avkon
*
*  Description:
*  Check box list support for setting page in editable state
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNCHECKBOXSETTINGPAGE_H__
#define __AKNCHECKBOXSETTINGPAGE_H__ 


#include <aknlistboxsettingpage.h>

/**
* Class to encapsulate text and Boolean status; An array of these provides the interface to the CheckBoxSettingPage
* The boolean status can be changed after construction, but the tect cannot be changed.
*
*
*/
class CSelectableItem : public CBase
{
public :
	/**
	* C++ constructor
	* @param	aItemText	text to go into the compound type
	* @param	aSelected	Pass ETrue to select the item; EFalse to deselected it.
	*/
	IMPORT_C CSelectableItem( TDesC& aItemText, TBool aSelected  );
	/**
	* C++ Destructor
	*/
	virtual ~CSelectableItem();

	/** 
	* 2nd stage construction
	*
	*/
	IMPORT_C void ConstructL();

	/**
	* Set the selection status to Ttrue or false
	* 
	* @param	aSelected	status that the selection status is to be set to.
	*/
	IMPORT_C void SetSelectionStatus( TBool aSelected );

	/**
	* Access the selection status
	* @return	EFalse if not selected; otherwise not EFalse
	*/
	IMPORT_C TBool SelectionStatus();

	/**
	* Access to the item text as TPtr
	* @return	TPtrC that points to items's text.
	*/
	IMPORT_C TPtrC ItemText();

private:
	TDesC& iDesC;	// Holds the reference to the descriptor prior to construction
	HBufC* iItem;	// This is on the heap and is used post constuction
	TBool iSelected;
};


/**
* Array type for holding selection items
*
*/
class CSelectionItemList : public CArrayPtrFlat<CSelectableItem>, public MDesCArray
	{
public:
	/**
	* Constructor
	*/
	IMPORT_C CSelectionItemList( TInt Granularity );
// from MDesCArray

	/**
	* From MDesCArray:
	*
	* @return number of items in the array
	*/
	IMPORT_C TInt MdcaCount() const;

	/**
	* Access to item text of the elements in the array
	* @return item text of aIndex'th element
	*/
	IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
	};



/**
* Setting Page class supporting multiple selection. 
*
* Interface is via a CSelectionItemList array
*
*/
class CAknCheckBoxSettingPage : public CAknListBoxSettingPage
{
public:
	IMPORT_C CAknCheckBoxSettingPage(TInt aResourceID, CSelectionItemList* aItemArray );
 /**
 * Constructor that allows separate setting page and editor resources
 *
 * In all cases the number (if supplied i.e. <> 0 ) is used.  
 *
 *		Editor Resource		Setting Page Resource
 *			present				present				Both are used (but text & number overridden)
 *			 = 0				present				Editor resource is used via SP resource
 *			present				= 0					Default Avkon SP resource if used (to no effect?)
 *			 = 0				= 0					Not permitted
 *
 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
 * cannot initialize such a member without allocation or having an internal dummy buffer.
 *
 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 * 
 * @param aSettingTitleText	Text at top of setting pane
 *	@param aSettingNumber		Number at top left (if present)
 * @param aControlType			Determines the type constructed and how its resource is read
 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId		Setting Page to use (if present)
 * @param aItemArray			List of option texts and their selection states
 */
	IMPORT_C CAknCheckBoxSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								CSelectionItemList* aItemArray );


	/**
	* 2nd phase constructor
	*
	*/
	IMPORT_C virtual void ConstructL();

	/** 
	*
	* Access to ListBoxControl
	*
	* @return pointer to listbox used by the setting page; No transfer of ownership
	*/
	IMPORT_C CAknSetStyleListBox* ListBoxControl() const;

	/**
	* Method to update the item array after a change in content 
	*
	* @param CSelectionItemList* aItemArray	The new array of selectable items
	*/
	IMPORT_C void SetSelectionItemArrayL( CSelectionItemList* aItemArray );

// From MEikListBoxObserver
	/**
	* Observer callback from the listbox 
	*
	* @param	aListBox	ptr to listbox that is calling the method
	* @param	aEventType	type of event; defined by MEikListBoxObserver
	*/
	IMPORT_C virtual void HandleListBoxEventL(CEikListBox* aListBox,
				 MEikListBoxObserver::TListBoxEvent aEventType);


protected:
	/**
	* Destructor
	*/ 
	IMPORT_C virtual ~CAknCheckBoxSettingPage();

	/**
	* Called when the setting is updated
	*
	*/
	IMPORT_C virtual void UpdateSettingL();

	/**
	* Called when the setting page is about to be displayed
	*
	*/
	IMPORT_C void DynamicInitL();

	// From MEikCommandObserver
	IMPORT_C virtual void ProcessCommandL(TInt aCommandId);
	/*
	* This method is called upon Select command id.  It should change the setting but not exit in
	* this case.
	*/
	IMPORT_C virtual void SelectCurrentItemL();

//
// CoeControl Framework and reserved methods
//
protected:

/**
 * Writes the internal state of the control and its components to aStream.
 * Does nothing in release mode.
 * Designed to be overidden and base called by subclasses.
 *
 * @param	aWriteSteam		A connected write stream
 */	
	IMPORT_C virtual void WriteInternalStateL(RWriteStream& aWriteStream) const;

private:
/**
 *	Reserved method derived from CCoeControl
 */
	IMPORT_C virtual void Reserved_2();

/**
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();

private:
/**
 * New reserved method from CAknListBoxSettingPage 
 *
 */
	IMPORT_C virtual void CAknListBoxSettingPage_Reserved_1();

private:
	void UpdateAllSelections();
	void SetAllSelectionsL();
	void ToggleSelectionL();

	/**
	* Internal method to re-generate the internal, "decorated" text array used in the
	* real listbox. 
	*/
	void GenerateInternalArrayAndGiveToListBoxL();

	CDesCArrayFlat* iInternalItemArray;	

	// the following are not owned
	CSelectionItemList* iItemArray; 

	// Spare data
	TInt iSpare_1;
};

#endif 
