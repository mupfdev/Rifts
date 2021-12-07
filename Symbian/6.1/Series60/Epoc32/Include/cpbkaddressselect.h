/*
* ============================================================================
*  Name     : CPbkAddressSelect from CPbkAddressSelect.h
*  Part of  : PbkView.dll
*
*  Description:
*       Generic Phonebook address selection dialog. Used for selecting recipient
*       address from a contact for Call, Send SMS, email and MMS.
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

#ifndef __CPbkAddressSelect_H__
#define __CPbkAddressSelect_H__

//  INCLUDES
#include <e32base.h>
#include <coedef.h> // TKeyResponse
#include <w32std.h> // TKeyEvent, TEventCode


// FORWARD DECLARATIONS
class CPbkContactItem;
class TPbkContactItemField;
class CPbkSelectFieldDlg;
class CPbkFieldArray;


// CLASS DECLARATION

/**
 * Generic Phonebook address selection dialog. Used for selecting recipient
 * address from a contact for Call, Send SMS, email and MMS.
 */
class CPbkAddressSelect : public CBase
    {
    public:  // Interface
        /**
         * Parameters for ExecuteLD(TBaseParams&).
         * @see ExecuteLD(TBaseParams&)
         */
        class TBaseParams
            {
            public:  // Interface
                /**
                 * Returns the contact supplied to constructor.
                 */
                IMPORT_C const CPbkContactItem& ContactItem();

                /**
                 * Sets the focused field of the contact item. If focused field
                 * is a non-empty address field it is returned directly by
                 * ExecuteLD.
                 * default = NULL
				 * @param aFocusedField the focused field to set
                 */
                IMPORT_C void SetFocusedField(const TPbkContactItemField* aFocusedField);
        
                /**
                 * Set to ETrue to use default address of the contact directly.
                 * Focused field overrides default address if both are
                 * available.
                 * default = EFalse
				 * @param aUseDefaultDirectly defines should the default address
				 * be used directly
                 */
                IMPORT_C void SetUseDefaultDirectly(TBool aUseDefaultDirectly);

                /**
                 * Returns the selected field or NULL if no selection was made.
                 */
                IMPORT_C const TPbkContactItemField* SelectedField() const;

            protected:  // Derived class interface
                /**
                 * Constructor.
                 *
                 * @param aContact      Contact where to select an address.
                 * @param aDefaultField field to use as the default. NULL if 
                 *                      no default is set for aContact.
                 */
                IMPORT_C TBaseParams
                    (const CPbkContactItem& aContact, 
                    const TPbkContactItemField* aDefaultField);

            private:  // Data
				/// Ref: the contact where to select an address
                const CPbkContactItem& iContact;
				/// Ref: the default field of the contact
                const TPbkContactItemField* iDefaultField;
				/// Ref: the focused field of the contact
                const TPbkContactItemField* iFocusedField;
				/// Own: is the default address to be used directly
                TBool iUseDefaultDirectly;
				/// Own: the selected field of the contact
                const TPbkContactItemField* iSelectedField;
				/// Spare data
                TInt32 iSpare1;
				/// Spare data
                TInt32 iSpare2;

            private:  // friends
                friend class CPbkAddressSelect;
            };

        /**
         * @deprecated Use ExecuteLD(TBaseParams&).
         *
         * Runs an address selection query (if necessary) and returns
         * textual contents of the selected address field. Selection query is
         * shown if there are multiple applicable address fields (see also
         * parameters aFocusedField, aDefaultField and aUseDefaultDirectly).
         *
		 * @param aItem Contact Item chosen as the recipient.
         *
         * @param aFocusedField the focused field of the contact item. If 
         *                      aFocusedField is a non-empty applicable field
         *                      it is returned directly. aFocusedField must be
         *                      a field of aItem. May be NULL if caller doesn't
         *                      have field-level focus.
         *
         * @param aDefaultField field of aItem to use as the default field.
         *                      If specified (not NULL) field's contents is
         *                      used as the default selection. See also 
         *                      parameter aUseDefaultDirectly.
         *
         * @param aUseDefaultDirectly   if ETrue returns directly the default 
         *                              address if present and non-empty. If
         *                              EFalse and multiple addresses, focuses 
         *                              the default address in adress selection 
         *                              dialog.
         *
         * @return  the selected address string. KNullDesC if canceled 
         *          or no phone number found. <b>NOTE:</b> return value is 
         *          a pointer to aItem's field contents so aItem must exist 
         *          as long as the return value is used. If it is necessary 
         *          to store return value longer than aItem, make a copy.
         */
        IMPORT_C TPtrC ExecuteLD
                (const CPbkContactItem& aItem, 
                const TPbkContactItemField* aFocusedField,
                const TPbkContactItemField* aDefaultField,
                TBool aUseDefaultDirectly);

        /**
         * Destructor. Cancels address selection query if active.
         */
        IMPORT_C ~CPbkAddressSelect();

    protected:  // Base class interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkAddressSelect();

        /**
         * Runs an address selection query (if necessary).
         *
         * @param aParams   see TBaseParams.
         * @return true if query was accepted, false if canceled.
         */
        IMPORT_C TBool ExecuteLD(TBaseParams& aParams);

        /**
         * Returns aItem passed to ExecuteLD.
         */
        IMPORT_C const CPbkContactItem& ContactItem() const;

        /**
         * Exit any address selection query. Makes ExecuteLD return which means
         * this object is destroyed after this function returns!
         * @param aAccept   ETrue means the query selection is accepted and
         *                  EFalse that query is canceled.
         */ 
	    IMPORT_C void AttemptExitL(TBool aAccept);

    private:    // Base class interface. Private because these functions are
                // only to be called from this classes implementation.
        /**
         * Returns true if aField is an applicable address field.
         */
        virtual TBool AddressField(const TPbkContactItemField& aField) const = 0;

        /**
         * Called if there are no applicable address fields in aItem passed
         * to ExecuteLD.
         */
        virtual void NoAddressesL() = 0;

        /**
         * Returns title to use for the address selection list query.
         */
        virtual const TDesC& QueryTitleL() = 0;

        /**
         * Returns a softkey resource id to use for the address selection list
         * query.
         */
        virtual TInt QuerySoftkeysResource() const = 0;

        /**
         * Override to handle key events in the list query.
         * The default implementation is empty.
         */
        IMPORT_C virtual TKeyResponse PbkControlKeyEventL
            (const TKeyEvent& aKeyEvent,TEventCode aType);

        // Spare virtual functions
        IMPORT_C virtual void Reserved_1();
        IMPORT_C virtual void Reserved_2();

    private: // data members
        /// Ref: aItem passed to ExecuteLD
        const CPbkContactItem* iContactItem;
        /// Field selection dialog for this class
        class CSelectFieldDlg;
        friend class CSelectFieldDlg;
        /// Own: field selection dialog
        CPbkSelectFieldDlg* iFieldDlg;
        /// Own: field array for iFieldDlg
        CPbkFieldArray* iFields;
        /// Ref: set to ETrue when exeuction enters destructor
        TBool* iDestroyedPtr;
        // Spare data
        TInt32 iSpare1;
    }; 


#endif // __CPbkAddressSelect_H__
            
// End of File
