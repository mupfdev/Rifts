/*
* ============================================================================
*  Name     : CAknExFormApplication
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXFORMAPP_H
#define AKNEXFORMAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidAknExForm = { 0x10005C33 }; // UID of the application

// CLASS DECLARATION

/**
* CAknExFormApplication application class.
* Provides factory to create concrete document object.
*/
class CAknExFormApplication : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CAknExFormDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID (KUidAknExForm).
        * @return The value of KUidAknExForm.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
