/*
* ============================================================================
*  Name     : AknPopupFieldText.h
*  Part of  : Avkon
*
*  Description:
*     Represents a text combo box type control, used to implement the
*     Series 60 text pop-up field.
*     This control can be constructed directly from resource.
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#if !defined(__AKNPOPUPFIELDTEXT_H__)
#define __AKNPOPUPFIELDTEXT_H__

#include "AknPopupField.h"
#include "AknQueryValueText.h"


class CAknPopupFieldText : public CAknPopupField
	{
public: 
	/**
	* C++ constructor
	*/
	IMPORT_C CAknPopupFieldText();

	/**
	* C++ Destructor
	*/
	IMPORT_C ~CAknPopupFieldText();

	/**
	* Gets the Current Value Text from the CAknQueryValueText member
	*/
	IMPORT_C HBufC* CurrentValueTextLC();

	/**
	* Gets the Current Value index from the CAknQueryValueText member
	*/
	IMPORT_C TInt CurrentValueIndex() const;

	/**
	* Sets the Current Value index using the CAknQueryValueText member
	*/
	IMPORT_C void SetCurrentValueIndex(const TInt aIndex);

	/**
	* Gets the MdcArray from the CAknQueryValueText member
	*/
	IMPORT_C const MDesCArray* MdcArray() const;

	/**
	* Calls the SetAutoAppend method on the CAknQueryValueText member
	*/
	IMPORT_C void SetAutoAppend(TBool aAppend);

public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);

private: // Methods from CAknPopupField that were public
	/**
	* 2nd phase constructor
	*/
	void ConstructL();

	/**
	* This method should not be used. 
	* It is here to hide it from users, this will panic if you use it.
	*/
	void SetQueryValueL(MAknQueryValue* aValue);

private: // from CCoeControl
	IMPORT_C void Reserved_1();
	IMPORT_C void Reserved_2();

private: // personal
	void CommonConstructL(TInt aTextArrayResourceId, TInt aInitialIndex);

private:
	// the following members are owned
	CDesCArray* iArray;	// the array of text items
	CAknQueryValueTextArray* iTextArray;	
	CAknQueryValueText* iTextValue;
	};

#endif
