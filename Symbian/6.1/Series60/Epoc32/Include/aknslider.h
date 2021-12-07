/*
* ============================================================================
*  Name     : CAknSlider from Aknslider.h
*  Part of  : Avkon
*
*  Description:
*     Slider editor class
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef __AKNSLIDER_H__
#define __AKNSLIDER_H__

//  INCLUDES
#include <eikbctrl.h>
#include <eiklabel.h>
#include <eikimage.h>

// CONSTANTS
// This one is currently unused
const TInt KValueTextMaxLength_DEPRECATED=16;

// The following is max. length of the entire formatted value text including number, 
// special characters and supplied text.
const TInt KValueLabelTextMaxLength=30; 

// CLASS DECLARATION
class CAknSlider : public CEikBorderedControl
	{
private:

/** 
* Internal class to hold slider control data, primarily coming from resource
* It cannot be used by client code
*/
class CAknSliderData : public CBase
	{

public:
	/**
	* Combined constructor
	* Leaves the created object on the cleanup stack
	*
	* @param	aResourceId	resource Id to created the slider from
	*
	* @return	a fully constructed slider object.
	*/
	static CAknSliderData* NewLC( TInt aResourceId );
	/**
	* Destructor
	*
	*/
	~CAknSliderData();
	/**
	* From CCoeControl
	* 2nd stage contruction from resource.
	* Resource reader must be positioned at the beginning of a SLIDER resource structure
	*
	* @param aReader constructed and positioned resource reader	
	*/
	void ConstructFromResourceL( TResourceReader& aReader );

private:
	/**
	* From CCoeControl
	* 2nd stage construction for the object from resource Id.
	* Used internally by NewLC method
	*
	* @param aResourceId	Resource Id for a valie SLIDER resource structure
	*/
	void ConstructFromResourceL( TInt aResourceId );


public:

	/**
	* Sets the range of the slider control.
	*
	* @param aMinimumValue The minimum value of the slider control
	* @param aMaximumValue The maximum value of the slider control
	*/
	void SetRange(TInt aMinimumValue, TInt aMaximumValue);


	/**
	 *  Sets the value of decimal places.
	 *
	 * @param aDecimalPlaces The value of the decimal place
	 */
	void SetDecimalPlaces(TInt aDecimalPlaces);

    /**
    * Returns the value of decimal place.
	*
    * @return the value of decimal place.
    */
	TInt DecimalPlaces() const;

public: 
	TInt iValue;
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iRange;
	TInt iStepSize;
	TInt iValueType;
	TInt iLayout;
	HBufC* iText;
	TInt iDecimalPlaces;
	HBufC* iSingularText;
	HBufC* iMinimumLabelText;
	HBufC* iMaximumLabelText;
	TInt iDecoratorImageId;
	};

// End of CAknSliderData declaration

public:
	/**
	* Default Constructor.
	*/
	IMPORT_C CAknSlider();

	/**
	* Destructor.
    */
	IMPORT_C ~CAknSlider();

	/**
	* This function creates the bitmaps and labels. Also it sets the 
	* container window for the labels.
	*/
	void ConstructL();

	/**
	* Sets the value of the slider control and also updates the iValueLabel text.
	* There are the following constraints on the value: 
	*	it must be within the current range
	*	it must be at a value that is minimum + N * stepsize
	* If these are not both true, then the method will Panic
	*
	* @param aValue Sets the value of the slider.
	*/
	IMPORT_C void SetValueL(TInt aValue);

	/**
	* Returns the value of the slider control
	*
	* @return Slider value. 
	*/
	IMPORT_C TInt Value() const;

	/**
	* Sets the range of the slider control. 
	* Maximum value must be greater than the minimum value, or the method will Panic.
	*
	* @param aMinimumValue The minimum value of the slider control
	* @param aMaximumValue The maximum value of the slider control
	*/
	IMPORT_C void SetRange(TInt aMinimumValue, TInt aMaximumValue);

	/**
	* Sets the step size.
	* The step size must divide evenly into the Range.  This routine should be called 
	* after SetRange if either is called.
	*
	* @param aStepSize The value of the step size
	*/
	IMPORT_C void SetStepSize(TInt aStepSize);

	/**
	* Sets the text to the minimum label.
	*
	* @param aText The text passed is set to the minimum label
	*/
	IMPORT_C void SetMinimumTextL(const TDesC& aText);

	/**
	* Sets the text to the maximum label.
	*
	* @param aText The text passed is set to the maximum label
	*/
	IMPORT_C void SetMaximumTextL(const TDesC& aText);

	/**
	 *  Sets the value of decimal places.
	 *  The legal range is 0 - 9 inclusive
	 *
	 * @param aDecimalPlaces The value of the decimal place
	 */
	IMPORT_C void SetDecimalPlaces(TInt aDecimalPlaces);

    /**
    * Returns the value of decimal place.
	*
    * @return the value of decimal place.
    */
	IMPORT_C TInt DecimalPlaces() const;

	/**
	 *  Returns slider bitmap to "list pane for setting item" 
	 *  (setting option item slider graphic). Ownership of the returned bitmap
	 *  is transfered to the caller.
	 *
	 * @param  aValue Current value
	 * @param  aResourceId Slider resource that contains minimum and maximum values
	 * @return Slider bitmap. Ownership of the bitmap is transfered to the caller
	 */
    IMPORT_C static CFbsBitmap* CreateBitmapL(TInt aValue, TInt aResourceId);

	/**
	 *  Returns slider bitmap to "list pane for setting item" 
	 *  (setting option item slider graphic). Ownership of the returned bitmap
	 *  is transfered to the caller.
	 *
	 * @param  aValue Current value
	 * @param  aMinimumValue Slider minimum value
	 * @param  aMaximumValue Slider maximum value
	 * @return Slider bitmap. Ownership of the bitmap is transfered to the caller
	 */
    IMPORT_C static CFbsBitmap* CreateBitmapL(TInt aValue, TInt aMinimumValue, TInt aMaximumValue);

public: 
	/**
	* From CCoeControl, Returns the size of the control.
	*
	* @return size of the control
	*/
	TSize MinimumSize();

	/**
	* From CCoeControl, Handles key event.
	*
    * @param aKeyEvent The key event.
    * @param aType The type of the event.
    * @return Indicates whether the key event was used by this control or not
    */
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);
	
	/**
	* From CCoeControl
	* Essential for Dialog/Form construction 
	*
	* @param aReader which reads the values specified in the resource file
	*/
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);  

	/**
	* This function is used for constructing the control. 
	*
	* @param aParent Pointer to the parent control.
	* @paran aValue Current value of the slider control. 
	* @param aReader which reads the values specified in the resource file.
	*/
    IMPORT_C void ConstructFromResourceL(CCoeControl* aParent, TInt aValue, TResourceReader& aReader);

	/**
	* This function toggles between edit and view modes  
	*
	* @param aType Specifies the mode.
	*/
    IMPORT_C void HandleResourceChange( TInt aType ); 

public: 
	/**
	* This function is used specifically in the forms.
	* (For Forms/Dialogs to use with LAF)
	* Returns the number of lines on the control
	*
	* @return Number of lines 
	*/
	IMPORT_C TInt NumberOfLines() const;

	/**
	* This routine can be used to combine the resource for a Slider with a value
	* to get the same value text that you would get if you had the instantiated
	* control
	*
	* @param aValue			the value to format
	* @param aResourceId	AKN_SLIDER resource id
	*
	* @return				transfer of ownership of descriptor containing the value text
	*/
	IMPORT_C static HBufC* CreateValueTextInHBufCL( TInt aValue, TInt aResourceId );

protected: 

	/**
    * From CCoeControl, Called by framework when the view size is changed.
    */
	void SizeChanged();
	
	/**
    * From CCoeControl, Drawing function which draws the control
	*
	* @param aRect Specified area to be drawn
	*/
	void Draw(const TRect& aRect) const;

   /**
    * From CCoeControl, Returns number of components.
	*
    * @return Number of component controls
    */
	IMPORT_C virtual TInt CountComponentControls() const;
	
	/**
    * From CCoeControl, Returns pointer to particular component
	*
    * @param aIndex Index whose control's pointer has to returned.
    * @return Pointer to component control
    */	
	IMPORT_C virtual CCoeControl* ComponentControl(TInt aIndex) const;

protected:
	/**
	* Sets the text to the value label
	*/
	IMPORT_C void SetValueTextL();

private:

	void InitializeBitmapsL();

	/**
	* static routine for setting the value text.
	* @param valueBuf	buffer to hold the result. Must be big enough to hold value label
	* as formatted from the resources and value provided, though it is protected from overflow.
	* Contained text will be truncated to KValueLabelTextMaxLength
	* @param aValue		Slider value to format
	* @param aResourceData	resource Id to read from 
	*/
	static void DoSetValueTextL( 
					TDes& valueBuf, 
					TInt aValue, 
					const CAknSliderData& aResourceData );
	/**
	* Routine to calculate the step size to use in a repeat key event
	*
	*/
	TInt RepeatStepSize() const;

	/**
	* This method is used to trap all the accesses to the internal data. 
	* It panics with EAknPanicObjectNotFullyConstructed if iSliderData is not constructed,
	* that is, if 2nd stage construction has not taken place (or has failed).
	*/
	CAknSliderData* SliderData() const;

	/**
	* This class is a utility to protect StringLoader::Format from being called without
	* a formatting token.
	*
	* StringLoader is used in current implementation. See StringLoader::Format for the 
	* semantics of the parameters.
	*
	* The other thing to note is that the output for descriptor must be able to accept 
	* up to KValueLabelTextMaxLength characters. 
	* 
	* @param aOutput	Output of format operation
	* @param aFormat	Formatting descriptor.  
	* @param aValue		Descriptor to substitute for the %U token potentially present
	*					in the formatting descriptor.
	*/
	static void FormatWithOrWithoutTokenL( TDes& aOutput, const TDesC& aFormat, const TDesC& aValue );


private: // layout methods
	void FormSliderLayout1();
	void FormSliderLayout2();
	void FormSliderLayout3();
	void SettingsItemSliderLayout();
	void CreateAndConstructDecoratorImageFromResourceL( TInt aImageResourceId );

	// Internal access methods
	TInt Layout() const;
	TInt StepSize() const;
	TInt MaximumValue() const;
	TInt MinimumValue() const;
	TInt Range() const;

private:	
	CEikImage* iImage;
	CEikLabel* iValueLabel;
	CEikLabel* iMinLabel;
	CEikLabel* iMaxLabel;
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMaskBitmap;
	TRect iMarkerRect;
	TPoint iLineStart;
	TPoint iLineEnd;
	TInt iValue;
    TBool iEditable;
	TRgb iColor;
	HBufC* iSingularText; // Text to be used for the singular label if needed. Owned
	CAknSliderData* iSliderData;
    TInt iSpare_1; // Not in use.
};

#endif	// __AKNSLIDER_H__
            
// End of File
