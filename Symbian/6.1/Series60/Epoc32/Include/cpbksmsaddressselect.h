/*
* ============================================================================
*  Name     : CPbkSmsAddressSelect from CPbkSmsAddressSelect.h
*  Part of  : PbkView.dll
*
*  Description:
*     Phonebook SMS address selection dialog.
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

#ifndef __CPbkSmsAddressSelect_H__
#define __CPbkSmsAddressSelect_H__

//  INCLUDES
#include "CPbkPhoneNumberSelectBase.h"

// CLASS DECLARATION

/**
 * Phonebook SMS address selection dialog.
 */
class CPbkSmsAddressSelect : public CPbkPhoneNumberSelectBase
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkSmsAddressSelect();

        /**
         * Parameters for ExecuteLD(TParams&).
         *
         * @see CPbkAddressSelect::TBaseParams
         * @see ExecuteLD(TParams&)
         */
        class TParams : public CPbkAddressSelect::TBaseParams
            {
            public:
                /**
                 * Constructor.
                 * @param aContact  contact where to select a phone number.
                 */
                IMPORT_C TParams(const CPbkContactItem& aContact);
            };

        /**
         * Runs the SMS address selection query (if necessary).
         *
         * @param aParams   parameters and return values object of the query.
         * @return  true if query was accepted, false if canceled.
         * @see TParams
         */
        inline TBool ExecuteLD(TParams& aParams);

        /**
         * @deprecated Use ExecuteLD(TParams&).
         *
         * Runs SMS address selection dialog (if necessary) and returns 
         * selected address string.
         *
		 * @param aItem Contact where the address is retrieved.
         *
         * @param aFocusedField the focused field of aItem. If 
         *                      aFocusedField is a non-empty phone number field
         *                      it is returned directly. aFocusedField must be
         *                      a field of aItem or NULL if caller doesn't have
         *                      field-level focus.
         *
         * @param aUseDefaultDirectly   if ETrue returns directly the default 
         *                              address if present and non-empty.
         *
         * @return  The selected address string. KNullDesC if canceled 
         *          or no address found. <b>NOTE:</b> return value is a pointer
         *          to aItem's field so aItem must exist as long as the return
         *          value is used. If it is necessary to store return value 
         *          longer than aItem, make a copy.
         */
        IMPORT_C TPtrC ExecuteLD
                (const CPbkContactItem& aItem, 
                const TPbkContactItemField* aFocusedField,
                TBool aUseDefaultDirectly);

        /**
         * Destructor.
         */
        IMPORT_C ~CPbkSmsAddressSelect();

    private:  // from CPbkAddressSelect
        IMPORT_C const TDesC& QueryTitleL();
        IMPORT_C TInt QuerySoftkeysResource() const;

    private: // Data
        /// Own: Title for phonenumber selection list
        HBufC* iQueryTitle;
    }; 


// INLINE FUNCTIONS
inline TBool CPbkSmsAddressSelect::ExecuteLD(TParams& aParams)
    {
    return CPbkAddressSelect::ExecuteLD(aParams);
    }

#endif // __CPbkSmsAddressSelect_H__
            
// End of File
