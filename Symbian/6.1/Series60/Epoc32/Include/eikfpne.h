// EIKFPNE.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//
// Modified for Avkon project by R. DeWolf
//

#ifndef __EIKFPNE_H__
#define __EIKFPNE_H__

#ifndef __EIKEDWIN_H__
#include <eikedwin.h>
#endif

#ifndef __AKNNUMEDWIN_H__
#include <aknnumed.h>
#endif

/**
* This class presents an editor modifying a real. The decimal place can occur anywhere.
* Exponential notation is allowed. 
* 
* Validation, consisting of a check that the contents are parsable as a number 
* (using TLex::Val()) and a range check, is carried out when PrepareForFocusLossL is called.
* Invalid contents cause a leave of that method.
*
* Value() only returns a value corresponding reliably to the value in the editor after a 
* non-leaving call to PrepareForFocusLossL. 
*
*/
class CEikFloatingPointEditor : public CAknNumericEdwin
	{
public:
	/**
	* C++ constructor
	*/
	IMPORT_C CEikFloatingPointEditor();
	/**
	* 2nd stage constructor
	*/
	IMPORT_C void ConstructL(const TReal& aMin,const TReal& aMax,TInt aTextLimit);
	/**
	* Read out the value from the editor as a Real. Value can only be relied on after 
	* a non-leaving call to PrepareForFocusLossL().
	*
	* @return	Value in the editor	
	*/
	IMPORT_C TReal Value() const;
	/**
	* Read out the value from the editor as a Real. 
	* @return	Validation status of the current value
	*/
	IMPORT_C TValidationStatus GetValueAsReal( TReal& aValue );
	/**
	* Set the value in the editor. 
	*
	* @param aValue pointer to value to set 
	*/
	IMPORT_C void SetValueL(const TReal* aValue);
	/**
	* Set minimum and maximum valid values.
	*
	* @param aMin	TInt minimum value
	* @param aMax	TInt maximum value
	*/
	IMPORT_C void SetMinMax(TReal aMin,TReal aMax);
	/**
	* Get minimum and maximum valid values.
	*
	* @param aMin	TReal& minimum value
	* @param aMax	TReal& maximum value
	*/
	IMPORT_C void GetMinMax(TReal& aMin,TReal& aMax) const;
public: // framework
	/**
	* From resource constructor. Refer to eikon.rh for the FLPTED resource structure 
	*
	* @param	aReader		Resource reader positioned at a FLPTED resource location
	*/
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	/**
	* Called by framework when focus is being taken off editor. May be called
	* by client code.
	*/
	IMPORT_C virtual void PrepareForFocusLossL();
	/**
	* Sets the input capabilities of the editor
	*/
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;

private: // from CEikEdwin
		IMPORT_C void Reserved_3();

private:
	TReal iValue;
	TReal iMin;
	TReal iMax;
	TInt iSpare;
	};


/**
* This class presents an editor modifying a real. A fixed number of decimal places is 
* permitted, set by API. Exponential notation is not permitted.
* 
* Validation, consisting of a check that the contents are parsable as a number 
* (using TLex::Val()) and a range check, is carried out when PrepareForFocusLossL is called.
* Invalid contents cause a leave of that method.
*
* Value() only returns a value corresponding reliably to the value in the editor after a 
* non-leaving call to PrepareForFocusLossL. 
*
* All values, defaults, minima and maxima set by API or resource are TInts.  The Real value
* is obtained by dividing by 10^<number of decimal places>  
* 
* The number of characters in the editor is calculated from the number of allowed decimal places.
* TODO but there is a bug - cannot handle + or - signs in front, nor missing leading 0s 
* before the decimal place.
*/
class CEikFixedPointEditor : public CAknNumericEdwin
	{
public:
	/**
	* C++ constructor
	*/
	IMPORT_C CEikFixedPointEditor();
	/**
	* 2nd stage Constructor
	*/
	IMPORT_C void ConstructL(TInt aMin,TInt aMax);
	/**
	* Access the value in the editor. The returned value is multiplied by 10^(decimal places) 
	* before formatting to text in the editor.
	* 
	* The value is reliable only immediately after setting and after a non-leaving call to 
	* PrepareForFocusLossL
	*
	* @return TInt current value in the editor. 
	*/
	IMPORT_C TInt Value() const;
	/**
	* Read out the value from the editor as a integer.
    * @return	Validation status of the current value
	*/
    IMPORT_C TValidationStatus GetValueAsInteger( TInt& aValue );
	/**
	* Set the value in the editor. The passed value is divided by 10^(decimal places) 
	* before formatting to text in the editor.
	*
	* @param TInt* pointer to value to set 
	*/
	IMPORT_C void SetValueL(const TInt* aValue);
	/**
	* Set minimum and maximum valid values.
	*
	* @param aMin	TInt minimum value multiplied by 10^(number of decimal places)
	* @param aMax	TInt maximum value multiplied by 10^(number of decimal places)
	*/
	IMPORT_C void SetMinMax(TInt aMin, TInt aMax);
	/**
	* Get minimum and maximum valid values.
	*
	* @param aMin	TInt& minimum value multiplied by 10^(number of decimal places)
	* @param aMax	TInt& maximum value multiplied by 10^(number of decimal places)
	*/
	IMPORT_C void GetMinMax(TInt& aMin, TInt& aMax) const;
	/**
	* This sets the number of allowed decimal places in the displayed text. The number
	* is also used to set the power of 10 by which all integer values in the API are divided
	* by before use, and the power of 10 by which all displayed values are multiplied by 
	* when turning them into integers.
	* 
	* @param	TInt number of decimal places displayed
	*/
	IMPORT_C void SetDecimalPlaces(TInt aDecimalPlaces);
	/**
	* This returns the number of allowed decimal places in the displayed text. The number
	* is that used to set the power of 10 by which all integer values in the API are divided
	* by before use, and the power of 10 by which all displayed values are multiplied by 
	* when turning them into integers.
	* 
	* @return	TInt number of decimal places displayed
	*/
	IMPORT_C TInt DecimalPlaces() const;
public:	// framework
	/**
	* From resource constructor. Refer to eikon.rh for the FIXPTED resource structure 
	*
	* @param	aReader		Resource reader positioned at FIXPTED resource location
	*/
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	/**
	* Called by framework when focus is being taken off editor. May be called
	* by client code.
	*/
	IMPORT_C virtual void PrepareForFocusLossL();
	/**
	* Sets the input capabilities of the editor
	*/
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
private:
	/**
	* Calculates the maximum number of characters needed by the editor.  Returned values 
	* is used internally to set CEikEdwin::iTextLimit 
	*/
	TInt RequiredNumberOfCharacters() const;
private: // from CEikEdwin
		IMPORT_C void Reserved_3();
private:
	TInt iValue;
	TInt iMin;
	TInt iMax;
	TInt iDecimalPlaces;
	TInt iSpare;
	};
#endif
