/*
* ============================================================================
*  Name     : AknNumEdwin.h
*  Part of  : Avkon
*
*  Description:  Numeric Editor derived from Uikon's CEikEdwin
* These specializations of CEikEdwin maintain a numeric content, 
* access methods and validation.
*
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/


#if !defined(__AKNNUMEDWIN_H__)
#define __AKNNUMEDWIN_H__

// INCLUDES
#include <eikedwin.h>
#include <aknnumed.h> // CAknNumericEdwin


_LIT( KAknIntegerFormat, "%d" );

// CLASS DECLARATIONS


class CAknIntegerEdwin : public CAknNumericEdwin
	{
public:
	IMPORT_C static CAknIntegerEdwin* NewL(TInt aMin, TInt aMax, TInt aMaxChars);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C void ConstructL( TInt aMin, TInt aMax, TInt aMaxChars );

	// New methods
	IMPORT_C void SetValueL(TInt aValue);
	IMPORT_C void SetUnsetValue( TInt aUnsetValue);
	IMPORT_C TValidationStatus GetTextAsInteger( TInt& aValue );
	IMPORT_C void SetMinimumIntegerValue( TInt aMinimumValue );
	IMPORT_C void SetMaximumIntegerValue( TInt aMaximumValue );

	//CCoeControl
	IMPORT_C void PrepareForFocusLossL();

private:
	void CommonConstructL(TInt aMin, TInt aMax, TInt aMaxChars, TInt aFlags, TInt aUnset);

private: // from CEikEdwin
    IMPORT_C void Reserved_3();

private:
	TInt iMinimumValue;
	TInt iMaximumValue;
	TInt iUnsetValue;
	TAny* iUnsetText;
	TInt iSpare_Integer_1;
	TInt iSpare_Integer_2;
	};

#endif
