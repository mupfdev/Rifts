/*
* ============================================================================
*  Name     : AknSliderSettingPage.h
*  Part of  : Avkon
*
*  Description: Slider Setting Page
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNSLIDERSETTINGPAGE__
#define __AKNSLIDERSETTINGPAGE__ 

// For coecontrol
#include <coecntrl.h>

#include <eikdef.h>
#include <eikbtgpc.h>
#include <aknslider.h>
#include <aknsettingpage.h>

class CAknSliderSettingPage : public CAknSettingPage
{
public:
	/**
	 * Simple constructor depending only on a single resource Id. Editor resource is given via
	 * the link in the setting page resource.
	 *
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aSliderValue					ref. to external slider value
	 */
	IMPORT_C CAknSliderSettingPage(TInt aResourceID, TInt& aSliderValue);

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
	 *
	 * @param aSettingTitleText		Text at top of setting pane (not copied to object until ExecuteLD is called)
	 * @param aSettingNumber		Number at top left (if present)
	 * @param aControlType			Determines the type constructed and how its resource is read
	 * @param aEditorResourceId	Editor resource to use in the setting page (if present)
	 * @param aSettingPageResourceId		Setting Page to use (if present)
	 * @param aSliderValue			Reference to integer holding the slider value
	 */

	IMPORT_C CAknSliderSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId,
								TInt& aSliderValue );
/**
 * Access method for the contained slider control. No transfer of ownership
 *
 * @return	Reference ptr to the contained CAknSlider object
 */
	IMPORT_C CAknSlider* SliderControl();

//
// From CAknSettingPage
//

/**
 * 2nd stage contructor
 *
 */
	IMPORT_C virtual void ConstructL();

//
// From CCoeControl
//
protected:
	IMPORT_C virtual void SizeChanged();
	IMPORT_C virtual void Draw(const TRect &aRect) const;

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

// 
// Framework methods derived from CAknSettingPage
//
protected:
/**
 * C++ destructor
 *
 */
	IMPORT_C virtual ~CAknSliderSettingPage();

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
 * New reserved methods for CAknSettingPage hierarchy
 */ 
private: 
	IMPORT_C virtual void CAknSettingPage_Reserved_1();
	IMPORT_C virtual void CAknSettingPage_Reserved_2();

private:
	TInt& iSliderValue;
	TInt iBackupSliderValue;
};

#endif 


