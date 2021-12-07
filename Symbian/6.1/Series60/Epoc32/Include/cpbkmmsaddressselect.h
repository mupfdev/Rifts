/*
* ============================================================================
*  Name     : CPbkMmsAddressSelect from CPbkMmsAddressSelect.h
*  Part of  : PbkView.dll
*
*  Description:
*       Phonebook MMS number selection dialog. This dialog implements the 
*       MMS number selection logic of Phonebook.
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

#ifndef __CPbkMmsAddressSelect_H__
#define __CPbkMmsAddressSelect_H__

//  INCLUDES
#include "CPbkAddressSelect.h"

// CLASS DECLARATION

/**
 * Phonebook MMS number selection dialog. This dialog implements the 
 * MMS number selection logic of Phonebook.
 */
class CPbkMmsAddressSelect : public CPbkAddressSelect
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkMmsAddressSelect();

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
                 * @param aContactItem  contact where to select a MMS address.
                 */
                IMPORT_C TParams(const CPbkContactItem& aContact);

            private:  // Spare data
                TInt32 iSpare1;
            };

        /**
         * Runs the MMS address selection query (if necessary).
         *
         * @param aParams   parameters and return values object of the query.
         * @return  true if query was accepted, false if canceled.
         * @see TParams
         */
        IMPORT_C TBool ExecuteLD(TParams& aParams);

        /**
         * @deprecated Use ExecuteLD(TParams&).
         *
         * Runs MMS number selection dialog (if necessary) and returns 
         * selected MMS number string.
         *
		 * @param aItem Contact item to be called.
         *
         * @param aFocusedField the focused field of the contact item. If 
         *                      aFocusedField is a non-empty MMS number field
         *                      it is returned directly. aFocusedField must be
         *                      a field of aItem.
         *
         * @param aCallDefaultDirectly  if ETrue returns directly the default 
         *                              number if present and non-empty.
         *
         * @return  the selected MMS number string or KNullDesC if canceled 
         *          or no MMS number found. <b>NOTE:</b> return value is a pointer
         *          to aItem's field so aItem must exist as long as the return
         *          value is used. If it is necessary to store return value 
         *          longer than aItem, make a copy.
         */
        IMPORT_C TPtrC ExecuteLD
                (const CPbkContactItem& aItem, 
                const TPbkContactItemField* aFocusedField,
                TBool aCallDefaultDirectly);

        /**
         * Destructor.
         */
        IMPORT_C ~CPbkMmsAddressSelect();

    private:  // from CPbkAddressSelect
        IMPORT_C TBool AddressField(const TPbkContactItemField& aField) const;
        IMPORT_C void NoAddressesL();
        IMPORT_C const TDesC& QueryTitleL();
        IMPORT_C TInt QuerySoftkeysResource() const;

    private: // data members
        /// Own: Title for MMS number selection list
        HBufC* iQueryTitle;
        // Spare data
        TInt32 iSpare1;
    }; 


#endif // __CPbkMmsAddressSelect_H__
            
// End of File
