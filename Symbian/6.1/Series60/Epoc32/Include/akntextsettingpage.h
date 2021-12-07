/*
* ============================================================================
*  Name     : AknTextSettingPage.h
*  Part of  : Avkon
*
*  Description:
*     Interface for Setting page carrying CEikEdwin editors
*		- CAknTextSettingPage: 6 line text editor
*		- CAknIntegerSettingPage: 1 line integer editor
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNTEXTSETTINGPAGE_H__
#define __AKNTEXTSETTINGPAGE_H__ 

// For coecontrol and its observer
#include <coecntrl.h>
#include <coecobs.h>

#include <eikdef.h>
#include <eikedwin.h>
#include "aknsettingpage.h"
#include "aknnumedwin.h"

/**
* This class is an intermediate pure virtual class for all setting page classes that host 
* Edwins.
*
* It implements type-specific access to the hosted editor and common drawing code
*/
class CAknEdwinSettingPage : public CAknSettingPage
{

public:

	/**
	*	Common access to the edwin for descendant classes
	*
	* @return Pointer to contained edwin control
	*/
	IMPORT_C CEikEdwin* TextControl();

protected:
	/**
	 * Simple constructor depending only on a single resource Id.
	 *
	 * @param aSettingPageResourceId	Setting Page resource id to use 
	 */
	IMPORT_C CAknEdwinSettingPage( TInt ResourceId );
	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present					present				Both are used (but text & number overridden)
	 *			 = 0					present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present					= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0					= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	 * cannot initialize such a member without allocation or having an internal dummy buffer.  
	 * Note that this buffer must be owned by the client until ExecuteLD has been called.
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText	Text at top of setting pane; EXTERNALLY OWNED
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 */

	IMPORT_C CAknEdwinSettingPage(
								const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId );

//
// From CCoeControl
//
protected:
	/**
	* No implementation of SizeChanged is delivered with this class
	*
	*/
	IMPORT_C virtual void SizeChanged() = 0;

	/**
	* Common draw function for laid-out descendent setting pages. 
	* This should not need to be re-implemented as long as the rectangle members are
	* all that is needed
	*
	* @param	aRect	rectangle within which to perform the draw
	*/
	IMPORT_C void Draw(const TRect& aRect) const;

private:
/**
 * New reserved method with this class
 *
 */
	IMPORT_C virtual void CAknEdwinSettingPage_Reserved_1();

protected:
	/**
	* Rectangle within which to layout the edwin. Not drawn
	*/
	TAknLayoutRect iEdwinLayoutRect;

	/**
	* Horizontal shadow rectangle
	*/
	TAknLayoutRect iHorizontalShadow;
	
	/**
	* Vertical shadow rectangle
	*/
	TAknLayoutRect iVerticalShadow;

	/**
	* Rectangle drawn around the edwin
	*/
	TAknLayoutRect iOutlineFrame;
};


/**
* Implementation of the 6 line textual setting page. 
* A multi-line edwin is displayed when the setting page is executing.
* An externally held text descriptor is altered by user input
*/
class CAknTextSettingPage : public CAknEdwinSettingPage
{
public:

// Flags to modify the behaviour of the editor
	enum TAknTextSettingPageFlags
	{
	EZeroLengthNotOffered = 0x0,	// DEPRECATED. This enum preserved but with value 0
	EPutCursorAtEnd = 0x0,			// DEPRECATED. This is already default so putting flag at beginning is more useful
	EZeroLengthAllowed = 0x0000001,
	ENoInitialSelection = 0x0000004,	// DEPRECATED and no longer used
	EPutCursorAtBeginning = 0x0000008,	// DEPRECATED and no longer used
	// Instructs the TextSettingPage not to override any of the Edwin's cursor and selection flags
	EUseEdwinCursorAndSelectionFlags = 0x0000010, // DEPRECATED
	EPredictiveTextEntryPermitted = 0x0020
	};

public:
	/**
	 * Simple constructor depending only on a single resource Id. Editor resource is given via
	 * the link in the setting page resource.
	 *
	 * @param aSettingPageResourceId	Setting Page to use (if present)
	 * @param aText						Reference to text for editing
	 * @param aTextSettingPageFlags		option flags for miscellaneous things
	 */
	IMPORT_C CAknTextSettingPage(TInt aResourceID, TDes& aText, TInt aTextSettingPageFlags = 0 );
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
	 *			present					= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0					= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	 * cannot initialize such a member without allocation or having an internal dummy buffer.
	 * Note that this buffer must be owned by the client until ExecuteLD has been called.
	 *
	 * Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	 * than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	 * (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	 * specific API for setting them, WILL override resource.
	 * It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	 * 
	 * @param aSettingTitleText	Text at top of setting pane; OWNED EXTERNALLY
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aText					Reference to text for editing
	 * @param aTextSettingPageFlags option flags for miscellaneous things
	 */
	IMPORT_C CAknTextSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								TDes& aText, 
								TInt aTextSettingPageFlags = 0);

	/**
	* 2nd stage construction for this specific type.  Calls BaseConstructL in 
	* CAknSettingPage, where the object is constructed from resource.
	* 
	* After calling this method, the contained editor is fully constructed and has its text set, 
	* copied from the aText parameter of the constructor. 
	* 
	* This constructor can be called prior to a call to ExecuteLD in order ensure 
	* construction of the editor if API needs to be called on it prior to setting page launch.
	* ExecuteLD will not attempt itself to do the construction a 2nd time.
	* 
	*/
	IMPORT_C virtual void ConstructL();

protected:
	/**
	* C++ destructor
	*
	*/ 
	IMPORT_C virtual ~CAknTextSettingPage();

//
// CAknSettingPage Framework implementations
//
protected:

/**
* Called immediately prior to activation of the dialog.  Framework routine for derived
* classes.
*
*/
	IMPORT_C virtual void DynamicInitL();

/**
* Called when something has changed and the client's object needs to have its text updated
*
*/
	IMPORT_C virtual void UpdateSettingL();

/**
* Called when the user accepts the text and the setting page is about to be dismissed.  The latest value of the
* text is written to the client's object
*/
	IMPORT_C virtual void AcceptSettingL();

/**
* Called when the user rejects the setting.  
* A backed up copy is used to restore the initial value
*
*/
	IMPORT_C virtual void RestoreOriginalSettingL();

/**
 * From MCoeControlObserver:
 * Acts upon changes in the hosted control's state. If the EUpdateWhenChanged
 * flag is set, this updates the setting text.
 * 
 * @param	aControl	The control changing its state (not used)
 * @param	aEventType	The type of control event 
 */
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType );	


/**
 * Framework method to set the validity of the data
 * This is called when the data changes.
 *
 */
	IMPORT_C virtual void CheckAndSetDataValidity();

/**
* This method copies out the text from the editor into the client's descriptor
*
*/
	IMPORT_C virtual void UpdateTextL();
	
/**
* Update the CBA. This should be called after a control state change in case 
* there has been a change in data validity.
*
*/
	IMPORT_C virtual void UpdateCbaL();

/**
 * Reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();

// 
// From CCoeControl
//

protected:

/**
* From CCoeControl
* This routine is called as part of the set-up of the control.  It is the place to put
* layout code. 
*
*/
	IMPORT_C virtual void SizeChanged();

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
 * Reserved method from CAknEdwinSettingPage
 *
 */
	IMPORT_C virtual void CAknEdwinSettingPage_Reserved_1();



private:
	HBufC* iBackupText;
	TDes& iText;
	TInt iTextSettingPageFlags;
	TInt iSpare_1; 
};


/**
 * Setting page specialized for display of CAknIntegerEdwin
 *
 */
class CAknIntegerSettingPage : public CAknEdwinSettingPage
{
public:

// Flags to modify the behaviour of the editor
	enum TAknIntegerSettingPageFlags
	{
	EInvalidValueNotOffered = 0x0,
	EEmptyValueAllowed = 0x0000001,
	EInvalidValueAllowed = 0x0000002,
	ENoInitialSelection = 0x0000004,
	EPutCursorAtBeginning = 0x0000008
	};

public:
	IMPORT_C CAknIntegerSettingPage(TInt aResourceID, TInt& aValue, TInt aTextSettingPageFlags = 0 );
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
	 * @param aSettingTitleText	Text at top of setting pane; OWNED EXTERNALLY
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aValue					Reference to integer value for editing
	 * @param aIntegerSettingPageFlags option flags for miscellaneous things
	 */
	IMPORT_C CAknIntegerSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								TInt& aValue, 
								TInt aIntegerSettingPageFlags = 0);

	/**
	* 2nd stage construction for this specific type.  Call BaseConstructL in 
	* CAknSettingPage, where the object is constructed from resource.
	*/
	IMPORT_C virtual void ConstructL();

	/** 
	* Type-specific access to the hosted editor
	*
	* @return CAknIntegerEdwin*		pointer to the current hosted editor
	*/
	IMPORT_C CAknIntegerEdwin* IntegerEditorControl();

//
// Framework methods from CAknSettingPage
//
protected:

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
* Called when the user rejects the setting.  A backup copy may need to be restored if UpdateWhenChanged flag was set
*
*/
	IMPORT_C virtual void RestoreOriginalSettingL();

/**
 * Framework method to set the validity of the data
 * This is called when the data changes.
 * May be over-ridden to change the validation rules.
 *
 */
	IMPORT_C virtual void CheckAndSetDataValidity();

/** 
 * This framework method is used to update the contents of the CBA in a custom way.
 * Some setting page classes implement a degree of validation and will implement this.
 * Derived classes should ensure that this is being called frequently enough for their
 * purposes.
 */
	IMPORT_C virtual void UpdateCbaL();

/**
 * Reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();



//
// From MEikControlObserver
//

protected:

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
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl, TCoeEvent aEventType );	

//
// From CCoeControl
//
protected:

/**
* From CCoeControl
* This routine is called as part of the set-up of the control.  It is the place to put
* layout code. 
*
*/
	IMPORT_C virtual void SizeChanged();


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
 * Reserved method from CAknEdwinSettingPage
 *
 */
	IMPORT_C virtual void CAknEdwinSettingPage_Reserved_1();

private:
	TInt iBackupValue;
	TInt& iValue;
	TInt iIntegerSettingPageFlags;
	TInt iSpare_1; 
};


#endif 
