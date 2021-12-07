/*
* ============================================================================
*  Name     : AknMfneSettingPage.h
*  Part of  : Avkon
*
*  Description:
*     Header file for Setting page implementations for Date, Time, duration 
*		and IP addresses 
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNMFNESETTINGPAGE_H__
#define __AKNMFNESETTINGPAGE_H__ 

#include <eikdef.h>
#include <eikbtgpc.h>
#include <eikmfne.h>
#include <aknipfed.h>
#include <in_sock.h>
#include "aknsettingpage.h"

/** 
 *
 * This class is used as the base for the date, time, duration and Ip editor
 * setting page types.  It performs all the layout.
 *
 */
class CAknMfneSettingPage : public CAknSettingPage
{

protected:
	/**
	 * Constructor using purely Setting page resource
	 *
	 * @param	aResourceId		Setting page resource Id
	 */
	IMPORT_C CAknMfneSettingPage(TInt ResourceId );
	 /**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * @param aSettingTitleText	Text at top of setting pane ; Externally owned
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 */
	IMPORT_C CAknMfneSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId );

	/**
	*
	* Framework method called when the control needs to be re-laid out
	*
	*/
	IMPORT_C virtual void SizeChanged();
	
	/** 
	* Draws the control. Framework method
	*/
	IMPORT_C void Draw(const TRect& aRect) const;

	/**
	* Type-specific access to control
	*/
	IMPORT_C CEikMfne* Mfne() const;

	/**
	* Implementation of of validity framework method for mfnes.
	* Checks if the current focused field in the mfne is valid and sets the 
	* setting page validity accordingly.
	* 
	* This method is called in order for the softkeys to be updated
	*/
	IMPORT_C void CheckAndSetDataValidity();

	/**
	* From MCoeControlObserver:
	* Acts upon changes in the hosted control's state. 
	* 
	* This observer method performs
	*  - Updates the value if EUpdateWhenChanged is the setting page's update mode
	*  - updates CBA labels depending on the data validity
	*
	* @param	aControl	The control changing its state (not used)
	* @param	aEventType	The type of control event 
	*/
	IMPORT_C virtual void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);


private:
	// Layuout information is stored here and not in the derived classes
	TAknLayoutRect iMfneLayoutRect;
	TAknLayoutRect iHorizontalShadow;
	TAknLayoutRect iVerticalShadow;
	TAknLayoutRect iOutlineFrame;

	TInt iSpare_1;

};


/** 
*
* This class is used for entering Dates in a "Code" setting page
*
*/
class CAknDateSettingPage : public CAknMfneSettingPage
{
public:

	/**
	 * Constructor using purely Setting page resource
	 *
	 * @param	aResourceId		Setting page resource Id
	 * @param	aDateValue		Reference to a date value set to the initial date
	 */
	IMPORT_C CAknDateSettingPage(
		TInt aResourceID, 
		TTime& aDateValue);

	/**
	 * Constructor that allows separate setting page and editor resources
	 * 
	 * This constructor allows the use of setting page using only the editor resource.  Other combinations are also possible
	 *
	 * In all cases the number (if supplied i.e. <> 0 ) is used.  
	 *
	 *		Editor Resource		Setting Page Resource
	 *			present				present				Both are used (but text & number overridden)
	 *			 = 0				present				Editor resource is used via SP resource (Effectively like the other constructor)
	 *			present				= 0					Default Avkon SP resource if used + this editor resource
	 *			 = 0				= 0					uses default resource for both SP and editor. This is OK if:
	 *	 i) control type is present, 
	 *  ii) a default resource exists ( OK for text, integer, date, time, duration )
	 *
	 * Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	 * cannot initialize such a member without allocation or having an internal dummy buffer.
	 * Note that this descriptor must be owned by the client at least until the ExecuteLD().
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
	 * @param aDateValue				reference to date
	 */
	IMPORT_C CAknDateSettingPage(	
								const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TTime& aDateValue );


	/**
	*
	* 2nd stage construction.  This uses stored values from the conststuctor to allocate the 
	* required aggregate objects, and then set the Date value. 
	*
	*/
	IMPORT_C virtual void ConstructL();

	/**
	 * Type-specific access to the editor 
	 *
	 * @return the hosted editor
	 */
	IMPORT_C CEikDateEditor* DateEditor();

protected:
	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknDateSettingPage();

	/**
	* This framework method is called when the editor changes its value and the mode of 
	* execution of the setting page is a continuous update mode.
	*
	*/
	IMPORT_C virtual void UpdateSettingL();

	/**
	* Called when the user has accepted the value.
	* The external value is updated once again, in case we were not in
	* continuous update mode. 
	* A specific observer  event is generated for the observer to say that the
	* value is accepted.
	*/
	IMPORT_C virtual void AcceptSettingL();

	/**
	* The backup value, stored at construction time, is re-loaded into the referenced Date.
	* An event is sent to the observer saying that the event was dismissed.
	*/
	IMPORT_C virtual void RestoreOriginalSettingL();
	
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
	TTime& iDateValue;
	TTime iBackupDateValue;
};

/** 
 *
 * This class is used for entering Times in a "Code" setting page
 *
 */
class CAknTimeSettingPage : public CAknMfneSettingPage
{
public:
	/**
	 * Constructor using purely Setting page resource
	 *
	 * @param	aResourceId		Setting page resource Id
	 * @param	aTimeValue		Reference to a time value for the initial time
	 */
	IMPORT_C CAknTimeSettingPage(
		TInt aResourceID, 
		TTime& aTimeValue);

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
	 * Note that this descriptor must be owned by the client at least until the ExecuteLD().
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
	 * @param aTimeValue				reference to a time
	 */
	IMPORT_C CAknTimeSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TTime& aTimeValue );

	/**
	* Specific 2nd stage contructor for this type. Construction is performed
	* according to the resources and parameters set in the C++ constructors
	*
	*/ 
	IMPORT_C virtual void ConstructL();

	/**
	 * Type-specific access to the editor 
	 */
	IMPORT_C CEikTimeEditor* TimeEditor();

protected:

	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknTimeSettingPage();

	/**
	* This framework method is called when the editor changes its value and the mode of 
	* execution of the setting page is a continuous update mode.
	*
	*/
	IMPORT_C virtual void UpdateSettingL();

	/**
	* Called when the user has accepted the value.
	* The external value is updated once again, in case we were not in
	* continuous update mode. 
	* A specific observer  event is generated for the observer to say that the
	* value is accepted.
	*/
	IMPORT_C virtual void AcceptSettingL();
	/**
	* The backup value, stored at construction time, is re-loaded into the referenced Date.
	* An event is sent to the observer saying that the event was dismissed.
	*/
	IMPORT_C virtual void RestoreOriginalSettingL();
	
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
	TTime& iTimeValue;
	TTime iBackupTimeValue;

};

/** 
 *
 * This class is used for entering duration in a "Code" setting page
 *
 */
class CAknDurationSettingPage : public CAknMfneSettingPage
{
public:
	/**
	 * Constructor using purely Setting page resource
	 *
	 * @param	aResourceId		Setting page resource Id
	 * @param	aDurationValue		Reference to the maintained duration value
	 */
	IMPORT_C CAknDurationSettingPage(
		TInt					aResourceID, 
		TTimeIntervalSeconds&	aDurationValue);
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
	 * Note that this descriptor must be owned by the client at least until the ExecuteLD().
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
	 * @param aDurationValue				reference to a duration
	 */
	IMPORT_C CAknDurationSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TTimeIntervalSeconds&	aDurationValue);

	/**
	* Specific 2nd stage contructor for this type. Construction is performed
	* according to the resources and parameters set in the C++ constructors
	*
	*/ 
	IMPORT_C virtual void ConstructL();
	/**
	 * Type-specific access to the editor 
	 */
	IMPORT_C CEikDurationEditor* DurationEditor();

protected:
	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknDurationSettingPage();

	/**
	* This framework method is called when the editor changes its value and the mode of 
	* execution of the setting page is a continuous update mode.
	*
	*/
	IMPORT_C virtual void UpdateSettingL();

	/**
	* Called when the user has accepted the value.
	* The external value is updated once again, in case we were not in
	* continuous update mode. 
	* A specific observer  event is generated for the observer to say that the
	* value is accepted.
	*/
	IMPORT_C virtual void AcceptSettingL();

	/**
	* The backup value, stored at construction time, is re-loaded into the referenced Date.
	* An event is sent to the observer saying that the event was dismissed.
	*/
	IMPORT_C virtual void RestoreOriginalSettingL();
	
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
	TTimeIntervalSeconds& iDurationValue;
	TTimeIntervalSeconds iBackupDurationValue;
};


/** 
 *
 * Setting page class for entering an IP Address
 *
 */
class CAknIpFieldSettingPage : public CAknMfneSettingPage
{
public:
	/**
	 * Constructor using purely Setting page resource
	 *
	 * @param	aResourceId		Setting page resource Id
	 * @param	aIpAddress		Reference to the maintained IP address
	 */
	IMPORT_C CAknIpFieldSettingPage(
		TInt					aResourceID, 
		TInetAddr&			aIpAddress);
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
	 * Note that this descriptor must be owned by the client at least until the ExecuteLD().
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
	 * @param aIpAddress				reference to a duration
	 */
	IMPORT_C CAknIpFieldSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,	
								TInetAddr&	aIpAddress);

	/**
	* Specific 2nd stage contructor for this type. Construction is performed
	* according to the resources and parameters set in the C++ constructors
	*
	*/ 
	IMPORT_C virtual void ConstructL();
	/**
	 * Type-specific access to the editor 
	 */
	IMPORT_C CAknIpFieldEditor* IpFieldEditor();

protected:
	/**
	* Destructor
	*/
	IMPORT_C virtual ~CAknIpFieldSettingPage();

	/**
	* This framework method is called when the editor changes its value and the mode of 
	* execution of the setting page is a continuous update mode.
	*
	*/
	IMPORT_C virtual void UpdateSettingL();

	/**
	* Called when the user has accepted the value.
	* The external value is updated once again, in case we were not in
	* continuous update mode. 
	* A specific observer  event is generated for the observer to say that the
	* value is accepted.
	*/
	IMPORT_C virtual void AcceptSettingL();

	/**
	* The backup value, stored at construction time, is re-loaded into the referenced Date.
	* An event is sent to the observer saying that the event was dismissed.
	*/
	IMPORT_C virtual void RestoreOriginalSettingL();

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
	TInetAddr& iIpAddress;
	TInetAddr iBackupIpAddress; // Not a reference

	};
#endif 
