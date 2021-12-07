/*
* ============================================================================
*  Name     : AknNumed.h
*  Part of  : EikCtl
*
*  Description:
*		Intermediate class for defining data shared between numeric edwins    
*     
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/

#if !defined(__AKNNUMED_H_)
#define __AKNNUMED_H_

#include <eikedwin.h>


/**
 * Intermediate class for defining data shared between numeric edwins
 *
 */
class CAknNumericEdwin : public CEikEdwin
	{
	public:
	enum TValidationStatus
		{
		EValueValid = KErrNone,
		EValueTooSmall,
		EValueTooLarge,
		EValueNotParsed,
		EEmpty
		};
	private: // from CEikEdwin
		IMPORT_C void Reserved_3();
	};

#endif
