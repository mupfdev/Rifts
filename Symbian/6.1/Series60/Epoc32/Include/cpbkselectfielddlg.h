/*
* ============================================================================
*  Name     : CPbkSelectFieldDlg from CPbkSelectFieldDlg.h
*  Part of  : PbkView.dll
*
*  Description:
*     Phonebook field selection dialog.
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

#ifndef __CPbkSelectFieldDlg_H__
#define __CPbkSelectFieldDlg_H__

//  INCLUDES
#include <e32base.h>    // CBase

// FORWARD DECLARATIONS
class TPbkContactItemField;
class CPbkFieldArray;
class MPbkControlKeyObserver;


// CLASS DECLARATION
/**
 * Phonebook field selection dialog.
 */
class CPbkSelectFieldDlg : public CBase
    {
    public:  // Interface
        /**
         * Constructor.
         */
        IMPORT_C CPbkSelectFieldDlg();

        /**
         * Runs the dialog and returns selected field.
         * NOTE: this object is deleted when this function 
         * returns or leaves.
         *
         * @param aArray  Array of TPbkContactItemFields
         * @param aCbaResourceId Softkey buttons for the control.
         * @param aHeading Possible heading for the control.
         * @param aFocusIndex field index to focus initially.
         *
         * @return returns the selected contact item field or NULL.
         */
        IMPORT_C TPbkContactItemField* ExecuteLD
            (CPbkFieldArray& aArray, 
            TInt aCbaResourceId, 
            const TDesC& aHeading = KNullDesC, 
            TInt aFocusIndex=-1);

        /**
         * Destructor.
         */
        IMPORT_C ~CPbkSelectFieldDlg();

        /**
         * Registers aKeyObserver as a key event observer of this control.
         * Only one observer is supported and setting a new one removes the
         * previous setting. 
         *
         * @param aKeyObserver  a Phonebook control key observer.
         */
        IMPORT_C void SetObserver(MPbkControlKeyObserver* aKeyObserver);

        /**
         * Attempts to exit this dialog just like a soft button was pressed.
         * @see CAknPopupList::AttemptExitL(TBool).
         */
        IMPORT_C void AttemptExitL(TBool aAccept);

        /**
         * Sets aSelfPtr to NULL when this dialog is destroyed.
         * @precond !aSelfPtr || *aSelfPtr==this
         */
        IMPORT_C void ResetWhenDestroyed(CPbkSelectFieldDlg** aSelfPtr);

    private: // Data
        /// Specialized listbox class
        class CListBox;
        /// Own: ListBox inside the popuplist
        CListBox* iListBox;
        /// Specialized popup list class
        class CPopupList;
        /// Own: popup list query
        CPopupList* iPopupList;
        /// Ref: key event observer
        MPbkControlKeyObserver* iKeyObserver;
        /// Ref: Set to ETrue in destructor
        TBool* iDestroyedPtr;
        /// Ref: Set to NULL when this dialog is destroyed.
        CPbkSelectFieldDlg** iSelfPtr;
        /// Own: Spare data
        TInt32 iSpare1;
    }; 

#endif // __CPbkSelectFieldDlg_H__
            
// End of File
