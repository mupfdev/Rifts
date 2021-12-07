/*
* ============================================================================
*  Name     : AknSettingPage.h
*  Part of	: Avkon
*
*  Description:
*  Base class for setting page (setting item editing) UI
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNSETTINGPAGE_H__
#define __AKNSETTINGPAGE_H__ 

// For coecontrol
#include <coecntrl.h>
#include <eikdef.h>
#include <eikbtgpc.h>

// For menu support
#include <eikmenub.h>
#include <eikmenup.h>
#include <eikmobs.h>

// for layout support
#include <aknutils.h>

// for navipane support (hint text)
#include <aknnavi.h>

class CEikLabel;

// Used as the return value of SettingId() if not yet set.
// This because the Id might want to be the index of a 0-based array

const TInt KAknSettingPageNoIdSet = -1;

class CAknSettingPage;

// This class is used as a means of notifying change in settings.

class MAknSettingPageObserver 
{
public:
enum TAknSettingPageEvent
	{
	EEventSettingChanged,
	EEventSettingCancelled,
	EEventSettingOked
	};
public:

/**
 * Handles an event of type aEventType reported by the Setting Page to this observer.
 */
virtual void HandleSettingPageEventL(CAknSettingPage* aSettingPage,TAknSettingPageEvent aEventType )=0;

};


class CAknSettingPage : public CCoeControl, public MCoeControlObserver, public MEikMenuObserver
{
public:

/**
* This enumeration is passed in the ExecuteLD() method to control how often the setting page 
* updates the externally held client object
*/
	enum TAknSettingPageUpdateMode
		{
		EUpdateWhenChanged,
		EUpdateWhenAccepted
		};

/**
 * Simple contructor for using a single setting page resource which itself gives all 
 * the setup
 */
	IMPORT_C CAknSettingPage( TInt aSettingPageResourceId );
 /**
 * Constructor that allows separate setting page and editor resources
 *
 * In all cases the number (if supplied i.e. <> 0 ) is used.  
 *
 *		Editor Resource 	Setting Page Resource
 *			present 			present 			Both are used (but text & number overridden)
 *			 = 0				present 			Editor resource is used via SP resource
 *			present 			= 0 				Default Avkon SP resource if used
 *			 = 0				= 0 				Not permitted
 *
 * Note: The first argument is a TDesC* (rather than TDesC&) because the other constructor
 * cannot initialize such a member without allocation or having an internal dummy buffer.
 *
 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
 * specific API for setting them, WILL override resource.
 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
 * 
 * @param aSettingTitleText		Text at top of setting pane (not copied; must be owned externally until ExecuteLD is called)
 * @param aSettingNumber		Number at top left (if present)
 * @param aControlType			Determines the type constructed and how its resource is read
 * @param aEditorResourceId Editor resource to use in the setting page (if present)
 * @param aSettingPageResourceId		Setting Page to use (if present)
 */
	IMPORT_C CAknSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId = 0 );
/**
* C++ destructor
*/
	IMPORT_C virtual ~CAknSettingPage();

/**
 * Executes a waiting dialog-like setting page
 * 
 * The passed mode determines if the editor's value is updated continuously, or just
 * when it is accepted.
 * 
 * @param	aMode		The update mode of the class
 */
	IMPORT_C TBool ExecuteLD( enum CAknSettingPage::TAknSettingPageUpdateMode aMode=EUpdateWhenAccepted );

/**
 * public method for construction.	Only thing required to do in this class is to call the 
 * BaseConstructL(). Derived classes may be required to do more
 *
 */
	IMPORT_C virtual void ConstructL();

/**
 * Returns reference to the hosted "editor" control as a CCoeControl.
 * This routine is used in derived classes, which may then cast to the specific run-time type
 * Note also that derived classes may provide type-specific access that performs these casts already
 * 
 * @return CCoeControl* pointer to the hosted editor control
 */
	IMPORT_C CCoeControl* EditorControl() const;

/**
 * Returns the setting Id.
 *
 * @return TInt the setting Id
 */
	IMPORT_C TInt SettingId() const;

/**
 * Sets the setting Id.  The Id may be used to unabiguously number a setting in some context.
 * It would be useful to call SettingId() on aSettingPageControl in handling an observer
 * callback.  The Id is not used internally.
 *
 * @param	aSettingId		An id to provide to the observer in the callback 
 */
	IMPORT_C void SetSettingId( TInt aSettingId );
/**
* Substitutes the new setting number. 
*
* @param	aSettingNumber	The new setting number to display
*/
	IMPORT_C void SetSettingNumberL( const TInt aSettingNumber );

/**
 * Substitutes the new setting text.  Memory is allocated for a copy.
 * If already constructed, the label is reformatted.  
 * 
 * Note that calling this will over-ride text in Setting Page resource
 * 
 * @param	aSettingText	The new setting text to display
 */
	IMPORT_C void SetSettingTextL( const TDesC& aSettingText );

/**
 * Sets the observer for the setting page.
 *
 * @param	aObserver	The observer for changes to the setting
 */
	IMPORT_C void SetSettingPageObserver( MAknSettingPageObserver* aObserver);

/**
 * Access method for the number of the setting page
 *
 */
	IMPORT_C TInt SettingNumber() const;

/**
 * Access method for whether the setting page is numbered or not
 *
 */
	IMPORT_C TBool IsNumbered() const;

/**
 * Set method for whether the setting page is numbered or not
 *
 */
	IMPORT_C void SetNumbered( TBool aNumbered );

/**
 * Reads the passed-in setting page resource in order to read the contained editor control
 * resource information
 * @param aSettingPageResoruceId	This is used to specifiy what resource to read
 * @param aControlType				Returns the control type (MAY return 0 - that's a valid control type!
 * @param aEditorResourceId 		Returns the setting page's LLINK editor resource, but returns 0 if not present
 * 
 * This will leave if an invalid resource ID is passed
 */
	IMPORT_C static void GetEditorResourceInfoL( 
		TInt aSettingPageResourceId, 
		TInt& aControlType, 
		TInt& aEditorResourceId );

protected:

/**
* From CCoeControl
* This routine is called as part of the set-up of the control.	It is the place to put
* layout code. 
*
*/
	IMPORT_C virtual void SizeChanged();


/**
* From CCoeControl
* Takes any action required when the control gains or loses focus e.g. to change its appearance.
* The control should be redrawn depending on the value of aDrawNow. Empty by default.
*/
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow); 
	
/**
 * From MEikCommandObserver
 * Processes events from the softkeys. Responds to EAknSoftkeyOk and EAknSoftkeyBack
 * to accept or cancel the pop-up.
 *
 * @param	aCommandId	Event Id from the soft-key
 */
	IMPORT_C virtual void ProcessCommandL(TInt aCommandId);

/**
 * From MCoeControlObserver:
 * Acts upon changes in the hosted control's state. 
 * 
 * This class's implementation is trivial and should be able to be
 * safely re-implemented in directly client-derived classes. 
 * For non-base setting page classes, a call to the base class should be made
 *
 * @param	aControl	The control changing its state (not used)
 * @param	aEventType	The type of control event 
 */
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

//
//
// Framework functions. New in this class
//
//
	/**
	* Framework method to determine if it OK to exit the setting page.
	* Derived classes may check for valid data before allowing the dismissal of the 
	* setting page.
	*
	* @param	aAccept ETrue if the user has indicated to accept the setting page; EFalse otherwise
	* @return	TBool	a value indicating whether the setting page should be dismissed
	*/
	IMPORT_C virtual TBool OkToExitL(TBool aAccept);
	
/**
* Called immediately prior to activation of the dialog.  Framework routine for derived
* classes.
*
*/
	IMPORT_C virtual void DynamicInitL();

/**
 * Called when something has changed and the client's object needs to have its value updated
 *
 */
	IMPORT_C virtual void UpdateSettingL();

/**
 * Called when the user accepts a setting and the setting page is about to be dismissed.  The latest value of the
 * setting is written to the client's object
 */
	IMPORT_C virtual void AcceptSettingL();

/**
 * Called when the user rejects the setting.  A backup copy may need to be restored if UpdateWhenChanged flag was set
 *
 */
	IMPORT_C virtual void RestoreOriginalSettingL();

/** 
 * Display the menu
 */
	IMPORT_C virtual void DisplayMenuL() ;

/**
 * Hide the menu
 */
	IMPORT_C virtual void HideMenu() ;

/** 
 * Puts the focus back on the editor. For complicated setting pages that have focus removed from them
 * at some point, then a re-implementation may have to do some work here.
 */
	IMPORT_C virtual void SetFocusToEditor();

/**
 * This method should be implemented in listbox classes to move the selection in 
 * listbox editors prior to exiting from the setting page. It is called on a 
 * CAknSettingPage* reference, and is therefore declared here.
 */
	IMPORT_C virtual void SelectCurrentItemL();

/**
 * Protected non-virtual base method for construction.	Only thing required to do in this class is 
 * call the ConstructFromResourceL routine and set the flag that says construction has occured
 *
 */
	IMPORT_C void BaseConstructL();

/**
 * Called to remove the setting page. Should not be called except from within re-implemented
 * AttemptExitL
 *
 * @param	aAccept ETrue to accept the current value; EFalse otherwise
 */
	IMPORT_C void DismissL( TBool aAccept );  

/**
 * This is used as a protected access function for the state of the menu bar
 *
 * @return TBool	ETrue if the menu is currently showing 
 */
	IMPORT_C TBool MenuShowing() const ;

/** 
* This constructs the control based upon the id passed
*
*/
	IMPORT_C void ConstructFromResourceL( TInt aResourceId);

/** 
* This constructs the control based upon a constructed and positioned reader
*
*/
	IMPORT_C void ConstructFromResourceL(TResourceReader& aRes);

 /**
 * Called when the user accepts or cancels the setting. Default implementation
 * sets the return value and exists. 
 * 
 * Re-implementations must call DismissL and StopActiveScheduler() if the setting is
 * to leave.
 *
 * @param	aAccept ETrue if the user accepted. EFalse if the user cancelled.
 */
	IMPORT_C void AttemptExitL(TBool aAccept);
/**
* Method to determine the current running state of the setting page's 
* ActiveScheduler level . 
*
* @return	EFalse only if the CActiveSheduler level is not running
*/
	IMPORT_C TBool Waiting(); 

/**
* Access method to the Command button array
*
* Must be called after full construction, or null reference will be returned.
*
* @return CEikButtonGroupContainer* a pointer to the cba owned by the setting page
*/
	IMPORT_C CEikButtonGroupContainer* Cba() const ;

/**
 * This is used to access the default resource id for the cba - the one used when 
 * data is valid.
 *
 * @return TInt 	the default resource Id 
 */
	IMPORT_C TInt DefaultCbaResourceId() const; 

/** 
* This routine routes the keys to the editor. 
* However, if the menu is showing, then events are sent to the menu. 
*
* @param	aKeyEvent	event information	
* @param	aType		type of event being handled
*
*/
	IMPORT_C TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

/**
* This routine is the base layout for CAknSettingPage. It lays out the labels and configures
* the drawing in general.
*/	
	IMPORT_C void StandardSettingPageLayout();

/**
 * This method can be used to test if BaseConstructL() has been called yet
 * successfully
 *
 * @return TBool	ETrue if BaseContructL has been called (and not left)
 */
	IMPORT_C TBool IsBaseConstructed();

/**
 * Access method for the internally held resource Id
 *
 */
	IMPORT_C TInt SettingPageResourceId();
/** 
* Perform the drawing of coded within CAknSettingPage
* 
*/
	IMPORT_C void BaseDraw(const TRect& aRect) const;

/**
* Set default construction values of internal state
*/
	IMPORT_C void ResetFlags();

/**
 * Framework method called as soon as the setting page is displayed, but before the new active sheduler level
 * is started.	Returning EFalse will dismiss the setting page right away
 *
 * @return TBool	ETrue if the setting page is to continue
 */
	IMPORT_C virtual TBool PostDisplayCheckL();

/** 
 * This framework method is used to update the contents of the CBA in a custom way.
 * Some setting page classes implement a degree of validation and will implement this.
 * Derived classes should ensure that this is being called frequently enough for their
 * purposes.
 */
	IMPORT_C virtual void UpdateCbaL();

/**
 * Called to access the valididty state of the data
 *
 * @return TBool ETRrue if the data is valid
 */
	IMPORT_C TBool DataValidity() const;

/**
 * used to set the validity of the data
 *
 * @param TBool aValid	Sets the validity true or false
 */
	IMPORT_C void SetDataValidity(TBool aValid);

/**
 * Framework method to set the validity of the data
 * This is called when the data changes.
 *
 */
	IMPORT_C virtual void CheckAndSetDataValidity();

 /**
 * From MEikMenuObserver 
 * Called when menu is cancelled.
 */
	IMPORT_C virtual void SetEmphasis(CCoeControl* /*aMenuControl*/,TBool aEmphasis);

 /**
 * From MEikMenuObserver 
 * This function intialiases the items on the menu.  It's used to disable and enable menu items and may be
 * over ridden to add new ones.
 * In addition it adds menu items which have been provided in the ConstructL in the form of a Menu Bar resource.
 * Instead of using the Menu Bar directly it extracts the menu panes and adds them to it's own menu pane.
 * It must be called in the DynInitMenuPaneL() function of any derived class before anything else.
 */
	IMPORT_C virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ); 

private:
	IMPORT_C virtual void Reserved_MtsmPosition();
	IMPORT_C virtual void Reserved_MtsmObject();

protected:
/** 
*	Access method for the softkey resource used when there is invalid data
*
* @return TInt The resource Id of the softkey bindings. 
*/
	IMPORT_C TInt InvalidDataCbaResourceId() const; 

protected: // from MObjectProvider
	IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

protected:
	/**
	* Hold the update mode passed in the constructor
	*/
	TInt iUpdateMode;
	/** 
	* Deprecated
	*/
	TInt iAsyncEvent;

	// The following are not owned:

	/**
	* Pointer to setting page observer; may be NULL
	*/
	MAknSettingPageObserver* iSettingPageObserver;

private:
	//From CCoeControl
	IMPORT_C void Draw(const TRect& aRect) const;

/**
 * Standard CCoeControl routine to return the number of componentn controls
 *
 * @param	aIndex	index at which to return control
 */
	IMPORT_C TInt CountComponentControls() const;

/**
 * Standard CCoeControl routine to return the control at a given index
 *
 * @param	aIndex	index at which to return control
 */ 

	IMPORT_C CCoeControl* ComponentControl(TInt anIndex) const;

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
 * Activate another level on the active scheduler
 */ 
	void StartActiveScheduler();
 /** 
 * Stop current (additional) level on the active scheduler
 */ 
	void StopActiveScheduler();

/**
* Pop the navidecorator. The iNaviPane is used as a flag to show if popping is required to 
* be done or not.  It is zeroed by this method.
*
*/
	void PopNaviDecoratorIfRequired();

/**
* New reserved methods for CAknSettingPage hierarchy
*/ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();

private:
/** 
* This member points to the setting title text that is passed as part of its more complicated constructor.
* The descriptor pointed to is not owned, and therefor must be preserved in the client, at least until the 
* 2nd stage construction is performed (inside ExecuteLD). 
*
* Since, however, setting pages are all waiting, the descriptor can usually be on the stack in the client.
*
*/
	const TDesC* iSettingTextFromConstructor;
	TInt iResourceId;

	TInt iSettingNumber;
	TInt iSettingId;
	TInt iMenuBarId;
	TInt iControlType;
	TInt iEditorResourceId;
	TInt iExtensionId;
	TInt iCbaResourceId;

	TAknLayoutRect iShadow;
	TAknLayoutRect iHighlight;

// pointer to the return value from the setting page.  
// Needed when presented in waiting mode.  
	TBool* iReturn; 
	
// Internal flags
	TBitFlags iFlags ;

	enum TFlagIndices
		{
		EMenuShowingIndex = 0,
			ENumberedStyleIndex,
			EIsBaseConstructedIndex,
			EHasValidDataIndex
		};

// Heap objects pointed to here are owned:
	CCoeControl* iEditorControl;
	CEikLabel* iNumberLabel;
	CEikLabel* iTextLabel;
	CEikButtonGroupContainer* iCba;
	CEikMenuBar* iMenuBar ;
	HBufC* iHintText;
	HBufC* iSettingText; 
	CAknNavigationDecorator* iNaviDecorator;

	// The following are not owned:
	// For hint text support
	CAknNavigationControlContainer* iNaviPane;

	// Softkey resource when the data is invalid
	TInt iInvalidDataCbaResourceId;
	
	TAny* iExtraLayout;
	CActiveSchedulerWait iWait;		// owned, safe to use as direct member data.
	TInt iSpare_1;					// Spare data members
	TInt iSpare_2;
};

#endif 
