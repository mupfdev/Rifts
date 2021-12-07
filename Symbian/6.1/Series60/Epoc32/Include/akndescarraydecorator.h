/*
* ============================================================================
*  Name     : AknDesCArrayDecorator.h
*  Part of  : Avkon
*
*  Description:
*     Used to decorate an MDesCArray with an extra entry.
*     
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AknDesCArrayDecorator.h
//
// 2001 Symbian Ltd.  All rights reserved.
//

#ifndef __AKNDESCARRAYDECORATOR_H__
#define __AKNDESCARRAYDECORATOR_H__

#include <bamdesca.h>

class TAknDesCArrayDecorator : public MDesCArray
	{
public:
	/**
	 * Constructor
	 * 
	 */
	IMPORT_C TAknDesCArrayDecorator();
public:
	/**
	 * Set pointer to descriptor array that will be decorated. 
	 * 
	 * @param aArray	pointer to descriptor array, ownership is not passed
	 */
	IMPORT_C void SetArray(const MDesCArray* aArray);

	/**
	 * Set descriptor containing text that will be used as the extra entry in the descriptor array.
	 * The client retains ownership of the descriptor containing the decoration text, and therefore
	 * can use the same descriptor text for multiple decorator instances. The client must 
	 * maintain the descriptor for the lifetime of the decorator.
	 * 
	 * @param aText	descriptor, ownership is not passed
	 */
	IMPORT_C void SetDecorationText(const TDesC& aText);

	/**
	 * Set the decorator's activation state. If active, the decorator adds the decoration to 
	 * the array, otherwise it does not.
	 * 
	 * @param aActive	ETrue = active; EFalse = inactive
	 */
	IMPORT_C void SetActive(const TBool aActive);

	/**
	 * Reports whether the supplied index position corresponds to the decoration entry 
	 * in the array. 
	 * <p> Note that the client must call this method on each instance of 
	 * TAknDesCArrayDecorator in the recursive containment (if it is not part of the 
	 * MDesCArray interface). 
	 *
	 * @param aIndex		output parameter, contains index in array of the decorated 
	 *									position, only valid if return value is ETrue
	 * @return				ETrue if there is a decorated position, EFalse otherwise
	 */
	IMPORT_C TBool DecoratedIndex(TInt& aIndex) const;
public: // from MDesCArray
	/**
	 * Reports count of decorated array
	 *
	 * @return count of decorated array
	 */
    IMPORT_C virtual TInt MdcaCount() const;

	/**
	 * Returns array element. 
	 * Returns decoration text if the index is one off the end of the decorated array
	 *
	 * @param index of element to return
	 * @return descriptor representing array element
	 */
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
private:
	// the following members are not owned
	const MDesCArray* iArray;
	TPtrC iText;
	TBool iActive;
	
	__DECLARE_TEST;
	};

#endif //__AKNDESCARRAYDECORATOR_H__
