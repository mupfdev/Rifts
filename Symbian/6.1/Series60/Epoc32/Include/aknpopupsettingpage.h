/*
* ============================================================================
*  Name     : AknPopupSettingPage.h
*  Part of  : Avkon
*
*  Description: 
*
* Support for popup setting item lists.  THe MAknQueryValue abstract type is 
* used to carry the state of the selection. 
*
* This file also contains the definition for the contained editor of the setting page,
* CAknPopupSettingList  
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNPOPUPSETTINGPAGE_H__
#define __AKNPOPUPSETTINGPAGE_H__ 


#include <aknqueryvalue.h>
#include <aknqueryvaluetext.h>
#include <aknlistboxsettingpage.h>

#include <AknDesCArrayDecorator.h>
#include <AknListBoxLayoutDecorator.h>

class CAknPopupSettingList;

/** 
 * This interface should be implemented by classes that need to know
 * about events occurring in the popup field control
 */
class MAknPopupSettingListObserver
	{
public:
	/**
	* Event types
	*/
	enum TAknPopupSettingListEvent
		{
		EAknPopupSettingSelectionAndRequestAccept,
		EAknPopupSettingSelectionAndStayOpen
		};
public:
/**
 * Handle events from the popup field control, such as when it changes between
 * selection list mode and label mode.
 *
 * Implementations of this observer routine should perform a base call to this specific
 * method, in order to pick up any default re-layout actions.
 *
 * @param aPopupSettingList pointer to the popup field control that generated the event
 * @param aEventType the type of event
 * @param aHint for possible future use
 *
 */
	virtual void HandlePopupSettingListEventL(	CAknPopupSettingList* aPopupSettingList, 
												TAknPopupSettingListEvent aEventType, 
												TInt aHint)=0;
	};

/**
 *
 * Represents menu list that appears in a popped up setting item
 */
class CAknPopupSettingList :
	public CAknSetStyleListBox,
	public MEikListBoxObserver
	{

protected:


public:
 /** 
 * Standard constructor.
 */
	IMPORT_C CAknPopupSettingList();

/** 
 * Destructor.
 *
 */
	IMPORT_C ~CAknPopupSettingList();

/** 
 * 2nd phase construction
 *
 */
	IMPORT_C void ConstructL();

/**
 * Sets flag that enables user defined entry. Note that flag can also be set from resources, 
 * but this method allows behaviour to be changed at runtime.
 *
 * @param aAllows	if ETrue, set flag; if EFalse, clear flag.
 */
	IMPORT_C void SetAllowsUserDefinedEntry(TBool aAllows);


/**
 * Used by the client to set the query value used to represent the user defined 
 * value belonging to this popup field control.
 *
 * @param aValue	pointer to value, ownership is not passed
 *
 */
	IMPORT_C void SetQueryValueL(MAknQueryValue* aValue);


/**
 * Set the flag which determines whether the indicators are shown
 * In practice the indicators have the appearance of radio buttons
 *
 * @param aShowIndicators	
 *		If ETrue, indicators are displayed; 
 *		if EFalse, indicators are not displayed
 *
 */
	IMPORT_C void SetShowIndicators(TBool aShowIndicators);

/**
 * number of lines used
 *
 * @return number of lines being currently displayed by control, which is determined 
 *		by the number of entries on the selection list, and whether the selection list is active.
 *		NOTE that the number is limited by KAknMaxLinesOnOnePage
 *
 */
	IMPORT_C TInt NumLines() const;

/**
 * set an observer of this class to receive events from popup setting list
 * 
 * @param aObserver pointer to the class that implements the observer interface,
 *
 */
	IMPORT_C void SetPopupSettingListObserver(MAknPopupSettingListObserver* aObserver);

public: 
/** 
 * from CCoeControl
 * Construct from resources.
 * @param aReader	constucted and positioned TResourceReader&
 */
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

protected:

/**
 * Create the popup list. 
 *
 */
	IMPORT_C void CreateMenuListL();

/**
 * Causes the list of pre-defined values to appear. 
 * Use this method to activate the pop-up field from a menu option command. 
 * Note that the desired control must have the focus before it can be activated.
 *
 */
	IMPORT_C void ActivateMenuListL();

/**
 *
 * This routine sets up the text arrays for the menu list
 *
 */
	IMPORT_C void ConfigureMenuListL();

/**
 * All this does now is remove this from the stack
 *
 */
	IMPORT_C void DestroyMenuList();
protected: 
/**
 * From MEikListBoxObserver
 * Processes key events from the listbox. Responds to EEventEnterKeyPressed to accept
 * the pop-up.
 *
 * @param	aListBox	Listbox being observed
 * @param	aEventType	Event observed
 *
 *
 * This implementation is vestige of former implementation when the listbox was wrapped up,
 * not derived from. Currently observing itself..
 *
 */
	IMPORT_C void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);

private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();
private: 
	void CommonConstructL();
	void SetUpSelectionListL();
/** 
 * Set up the bitmap array for the "not pushed" and "pushed in" states
 *
 */
	void InitialiseRadioButtonBitmapsL();
private: 
/**
 * Configures the decoration according to the currently set flags.
 * Should be called whenever the flags are changed. 
 *
 */
	void ConfigureDecorator();
/**
 * Configures the layout decoration according to the "has buttons" flag
 * Should be called whenever the flags are changed. 
 *
 */
	void ConstructLayoutDecoratorL();

private:
	// the following members are owned

	TAknDesCArrayDecorator iDecorator;
	CAknListBoxLayoutDecorator* iLayoutDecorator;

	// the following fields are reflected in the POPUP_SETTING_LIST resource structure
	TInt iFlags;
	HBufC* iOtherText;
	
	TInt iCurrentSelection;
	// elements to hold info regarding "new Item"- produced setting page
	TInt iNewItemSettingPageResourceId;
	TInt iNewItemEditorType;
	TInt iNewItemEditorControlResourceId;

	// the following members are not owned
	MAknQueryValue* iValue;
	MAknPopupSettingListObserver* iPopupSettingListObserver;

	TInt iSpare_1;

	};


/**
* Interface for the setting page containing a menu list with a Query value data model 
* This is the more generic of the list-style setting pages. 
*
*/
class CAknPopupSettingPage : 
	public CAknListBoxSettingPage, 
	public MAknPopupSettingListObserver
	{

public:
	/**
	* C++ constructor.  This constructor uses just the setting page resource Id to 
	* construct the setting page, using listbox resource contained in the setting page 
	* resource.
	* @param	aResourceId		a resource identifier for a AVKON_SETTING_PAGE resource
	* @param	aQueryValue		a reference to a query value object
	*/
	IMPORT_C CAknPopupSettingPage(TInt aResourceID, MAknQueryValue& aQueryValue );

	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0					= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
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
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aQueryValue			reference to a query value object
	 */
	IMPORT_C CAknPopupSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								MAknQueryValue& aQueryValue);

	/**
	* 2nd stage construction method.  Type specific work is done here; most of the setting
	* page constuction is performed in a call the base contstruction of CAknSettingPage
	*
	*/
	IMPORT_C virtual void ConstructL();

/**
 * Access to the contained listbox (inside popup setting list)
 *
 * @return	CAknSetStyleListBox* pointer to the listbox used in the setting page; Does not transfer ownership
 */
	IMPORT_C CAknSetStyleListBox* ListBoxControl() const;

/** 
 * Access to the editor control
 * 
 * @return	CAknPopupSettingList* a reference to the contained "editor" as a listbox; no ownership transferred
 */
	IMPORT_C CAknPopupSettingList* PopupSettingListBox() const;

/**
 *  From MAknPopupSettingListObserver
 * Handle events from the popup field control, such as when it changes between
 * selection list mode and label mode.
 *
 * @param aPopupSettingList pointer to the popup field control that generated the event
 * @param aEventType the type of event
 * @param aHint for possible future use
 *
 */
	IMPORT_C virtual void HandlePopupSettingListEventL(CAknPopupSettingList* aPopupSettingList, 
		TAknPopupSettingListEvent aEventType, TInt aHint);

/**
* Can be used dynamically to set a new query value.  This manages the setting up of the new
* PopupSettingList and its listbox, and also the resizing and redrawing of the setting page
* Note that all former query value objects and its associated arrays are owned by the client
* and if no longer used, should be deleted.
* 
* @param MAknQueryValue* aQueryValue - the new value; no transfer of ownership
*/
	IMPORT_C void UpdateQueryValueL( MAknQueryValue* aQueryValue );

protected:
/**
* C++ destructor
*/
	IMPORT_C virtual ~CAknPopupSettingPage();

/**
 * This is required to give access to the QueryValue data member from 
 * re-implementations of the popup setting page
 *
 * @return MAknQueryValue* a pointer to the query value object
 *
 */
	IMPORT_C MAknQueryValue* QueryValue() const;

/**
 * This method should be implemented in listbox classes to move the selection in 
 * listbox editors prior to exiting from the setting page
 *
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

	// The objects pointed to or referenced by this is not owned
	MAknQueryValue& iQueryValue;

	TInt iSpare_1;
	TInt iSpare_2;

};

#endif 
