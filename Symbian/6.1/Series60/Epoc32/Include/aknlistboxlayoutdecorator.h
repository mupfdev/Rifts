/*
* ============================================================================
*  Name     : AknListBoxLayoutDecorator.h
*  Part of  : Avkon
*
*  Description:
*     Decorates a descriptor array to include tabs suitable for list box formatting
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknListboxLayoutDecorator.h
//
// 1999-2001 Symbian Ltd.  All rights reserved.
//

#ifndef __AKNLISTBOXLAYOUTDECORATOR_H__
#define __AKNLISTBOXLAYOUTDECORATOR_H__

#include <bamdesca.h>

class CAknListBoxLayoutDecorator : public CBase, public MDesCArray
	{
public:
	/**
	 * Factory function
	 */
	IMPORT_C static CAknListBoxLayoutDecorator* NewL();

	/**
	 * Factory function
	 */
	IMPORT_C static CAknListBoxLayoutDecorator* NewLC();

	/**
	 * Destructor
	 */
	IMPORT_C ~CAknListBoxLayoutDecorator();

	/**
	 * get the array
	 *
	 * @return pointer to array - ownership is not passed
	 */
	IMPORT_C const MDesCArray* Array() const;

	/**
	 * set the array
	 *
	 * @param aArray pointer to array - ownership is not passed
	 */
	IMPORT_C void SetArray(const MDesCArray* aArray);

	/**
	 * set the text that will be inserted before the text from the descriptor array entry
	 *
	 * @param aText descriptor to insert before each entry
	 *
	 */
	IMPORT_C void SetLeadingDecorationTextL(const TDesC& aText);

	/**
	 * set the text that will be inserted after the text from the descriptor array entry
	 *
	 * @param aText descriptor to append after each entry
	 *
	 */
	IMPORT_C void SetTrailingDecorationTextL(const TDesC& aText);

	/**
	 * set the decoration to be active or inactive
	 *
	 * @param aActive if ETrue, decoration will be added; if EFalse, layout will be unchanged
	 *
	 */
	IMPORT_C void SetActive(const TBool aActive);
public:
	// from MDesCArray
	/**
	 * Pass count through straight from contained descriptor array
	 * 
	 * @return number of items in array
	 */
	IMPORT_C virtual TInt MdcaCount() const;

	/**
	 * Modify contents of descriptor to contain additional formatting for list box style. 
	 * Original string will be truncated in favour of formatting in low memory conditions.
	 * 
	 * @return descriptor pointer containing modified string - WARNING contents of
	 * this return value will be replaced next time this method is called!
	 */
	IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;		
private: // Reserved for future expansion
	/**
	 * Reserve slot in vtable for future use
	 */
	IMPORT_C virtual void CAknListBoxLayoutDecorator_Reserved1();

	/**
	 * Reserve slot in vtable for future use
	 */
	IMPORT_C virtual void CAknListBoxLayoutDecorator_Reserved1() const;
protected:
	/**
	 * Constructor, 1st phase of construction
	 */
	CAknListBoxLayoutDecorator();
	/**
	 * ConstructL, 2nd phase of construction
	 */
	void ConstructL();
protected:
	enum {KSafeSizeOfDescriptor = 32};
private:
	// owned
	mutable HBufC* iLastGeneratedTextValue;
	// not owned:
	const MDesCArray* iArray;
	TPtrC iLeadingDecorationText;
	TPtrC iTrailingDecorationText;
	TBool iActive;
private:
	__DECLARE_TEST;
	};

#endif //__AKNLISTBOXLAYOUTDECORATOR_H__
