/*
* ============================================================================
*  Name     : CPbkMultipleEntryFetchDlg from CPbkMultipleEntryFetchDlg.h
*  Part of  : PbkView.dll
*
*  Description:
*      Phonebook Multiple Entry Fetch API.
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

#ifndef __CPbkMultipleEntryFetchDlg_H__
#define __CPbkMultipleEntryFetchDlg_H__

//  INCLUDES
#include <e32base.h>    // CBase

//  FORWARD DECLARATIONS
class CPbkContactEngine;
class CContactViewBase;
class CContactIdArray;
class CPbkFetchDlg;
class MObjectProvider;


// CLASS DECLARATION

/**
 * Phonebook Multiple Entry Fetch API.
 */
class CPbkMultipleEntryFetchDlg : public CBase
    {
    public:  // Types
        /**
         * Fetch paramters class. 
         */
        class TParams
            {
            public:  // Input parameters
                /**
                 * Contact view to display. If NULL loads the default
                 * contact view containing all names in the contact
                 * database.
                 */
                CContactViewBase* iContactView;

            public:  // Output parameters
                /**
                 * Returns a array of ids of the selected entries, 
                 * undefined if the dialog is canceled.
                 * Caller must delete iMarkedEntries when no longer needed.
                 */
                CContactIdArray* iMarkedEntries;

            public: // Additional input parameters
                /**
                 * OPTIONAL: Fetch Softkey resource ID
                 * If 0, Default softkeys are used.
                 */
                TInt iCbaId;

            public:  // Interface
                /**
                 * C++ Constructor.
                 */
                IMPORT_C TParams();

                // Compiler-generated destructor is ok for this class

                /**
                 * Returns a cleanup item which will handle cleanup of this
                 * object in case of a leave.
                 */
                IMPORT_C operator TCleanupItem();

            private:  // Implementation
                static void Cleanup(TAny* aPtr);

            private:  // Unimplemented functions
                /// Unimplemented copy constructor
                TParams(const TParams&);
                /// Unimplemented assignment operator
                TParams& operator=(const TParams&);

            private:  // Spare data
                TInt32 iSpare1;
            };

    public:  // Interface
        /**
         * Creates a new multiple entry fetch dialog.
         *
         * @param aParams   fetch parameters, see TParams.
         * @param aEngine   Phonebook engine.
         * @return a new instance of this class.
         */
        IMPORT_C static CPbkMultipleEntryFetchDlg* NewL
            (TParams& aParams, CPbkContactEngine& aEngine);

        /**
         * See CCoeControl::SetMopParent(MObjectProvider* aParent)
         */
        IMPORT_C void SetMopParent(MObjectProvider* aParent);

        /**
         * Executes this dialog.
         * NOTE: this object is deleted when ExecuteLD returns or leaves!
         *
         * @return !=0 if accepted, 0 if canceled.
         */
        IMPORT_C TInt ExecuteLD();

        /**
         * Destructor. Also cancels this dialog and makes ExecuteLD return.
         */
        ~CPbkMultipleEntryFetchDlg();

    private:  // Implementation
        CPbkMultipleEntryFetchDlg(TParams& aParams, CPbkContactEngine& aEngine);
        void ConstructL();
        static void Panic(TInt aReason);

    private:  // Data
        /// Own: parameters
        TParams& iParams;
        /// Own: fetch dialog
        CPbkFetchDlg* iFetchDlg;
        /// Ref: Phonebook engine
        CPbkContactEngine& iPbkEngine;
        /// Ref: set to ETrue in destructor
        TBool* iDestroyedPtr;
        /// Own: Object Provider
        MObjectProvider* iObjectProvider;
    };

#endif // __CPbkMultipleEntryFetchDlg_H__

// End of File
