/*
* ============================================================================
*  Name     : AknSettingPage.h
*  Part of  : Avkon
*
*  Description:
*  Pure virtual class for a common ancestor for setting pages with listboxes
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNLISTBOXSETTINGPAGE_H__
#define __AKNLISTBOXSETTINGPAGE_H__ 

#include <aknsettingpage.h>

#include <aknutils.h>
#include <eikslb.h>
#include <eiklbo.h>
#include <eiklbx.h>
#include <eikclb.h>
#include <eikclbd.h>
#include <eiktxlbm.h>
#include <coecobs.h>
#include <aknlists.h>

/**
*
* Intermediate setting page class to soak up common listbox setting page code
* 
* This class has the responsibility of performing the listbox layout and setting
* out some  of the API for listbox setting pages.
*
*/
class CAknListBoxSettingPage : public CAknSettingPage, public MEikListBoxObserver
	{

public: 
	/**
	* Type-specific control access method with a null implementation
	*
	*/
	virtual CAknSetStyleListBox* ListBoxControl() const = 0;

	/**
	* Default empty implementation of the listbox observer handling routine
	*/
	IMPORT_C virtual void HandleListBoxEventL(CEikListBox* aListBox, TListBoxEvent aEventType);

protected:

	/**
	* Pass-through constructor
	* @param aSettingPageResourceId		resource id for CAknSettingPage::BaseConstructL()
	*
	*/
	CAknListBoxSettingPage( TInt aSettingPageResourceId );

	/**
	* Pass-through constructor 
	*
	* Generic constructor allowing either editor-resource constuction or setting page
	* resource based constuction
	* In all cases the number (if supplied i.e. <> 0 ) is used.  
	*
	*		Editor Resource 	Setting Page Resource
	*			present 			present 			Both are used (but text & number overridden)
	*			 = 0				present 			Editor resource is used via SP resource
	*			present 			= 0 				Default Avkon SP resource if used
	*			 = 0				= 0 				Not permitted 
	*
	* Note: THe first argument is a TDesC* (rather than TDesC&) because the other constructor
	* cannot initialize such a member without allocation or having an internal dummy buffer.
	* Note that the setting title provided here must be owned by the client.
	*
	* Rules for text and numbers: The rules are the same for both:  (non-zero length) text or number other 
	* than EAknSettingPageNoOrdinalDisplayed if given in this constructor will not override resource 
	* (unless that is zero length or EAknSettingPageNoOrdinalDisplayed).  Note, however, that text or number given via the 
	* specific API for setting them, WILL override resource.
	* It is assumed that number from resource is very rare.  Special text is somewhat more likely.
	* 
	* @param aSettingTitleText	externally-owned title text
	* @param aSettingNumber		the setting number to be displayed
	* @param aControlType		control type enumeration for the control to be constructed by type
	* @param aEditorResourceId	resource Id at which to read the control's resource
	* @param aSettingPageResourceId optional setting page resource Id; See notes above about resource combinations
	*/
	CAknListBoxSettingPage(	const TDesC* aSettingTitleText, 
								TInt aSettingNumber, 
								TInt aControlType,
								TInt aEditorResourceId, 
								TInt aSettingPageResourceId = 0 );


   /**
	* This standard implementation uses ListBoxControl to access the listbox and 
	* check the number of items.  If 0, validity is set to EFalse
	*
	*/
	IMPORT_C void CheckAndSetDataValidity();

	/**
	* Implementation to remove go to "invalid" cba when data is invalid
	*/
	IMPORT_C void UpdateCbaL();


	/**
	* From CCoeControl:
	* Routine called by Cone framework whenever there has been a size change on this 
	* control
	*/
	IMPORT_C void SizeChanged();

	/** 
	* From CCoeControl:
	* Common draw routine for the listboxes
	*
	* @param aRect	rectangle within which to draw
	*/
	IMPORT_C void Draw(const TRect& aRect) const;

private:
/**
 */
	IMPORT_C virtual void CAknListBoxSettingPage_Reserved_1();

protected:

	/**
	* Layout for the extra piece of white (sometimes) at the bottom of the listbox
	*
	*/
	TAknLayoutRect iAreaExtension;
private:
	TInt iSpare;
	};

#endif 
