/*
* ============================================================================
*  Name     : CPbkPhoneNumberSelectBase from CPbkPhoneNumberSelectBase.h
*  Part of  : PbkView.dll
*
*  Description:
*     Base class for Phonebook phone number selection queries.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __CPbkPhoneNumberSelectBase_H__
#define __CPbkPhoneNumberSelectBase_H__

//  INCLUDES
#include "CPbkAddressSelect.h"

// CLASS DECLARATION
/**
 * Base class for Phonebook phone number selection queries.
 */
class CPbkPhoneNumberSelectBase : public CPbkAddressSelect
    {
    protected:  // from CPbkAddressSelect
        /**
         * Common implementation of CPbkAddressSelect::AddressField for phone
         * number selection dialogs.
		 * @param aField the field to check
         */
        IMPORT_C TBool AddressField(const TPbkContactItemField& aField) const;

        /**
         * Common implementation of CPbkAddressSelect::NoAddressesL for phone
         * number selection dialogs.
         */
        IMPORT_C void NoAddressesL();
    }; 

#endif // __CPbkPhoneNumberSelectBase_H__
            
// End of File
