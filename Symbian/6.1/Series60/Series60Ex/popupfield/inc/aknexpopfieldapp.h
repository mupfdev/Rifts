/*
* =============================================================================
*  Name     : CAknExPopFieldApplication
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDAPP_H
#define AKNEXPOPFIELDAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidAknExPopField = { 0x10005C2D }; // UID of the application

// CLASS DECLARATION

/**
* CAknExPopFieldApplication application class.
* Provides factory to create concrete document object.
*/
class CAknExPopFieldApplication : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CAknExPopFieldDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID (KUidAknExPopField).
        * @return The value of KUidAknExPopField.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
