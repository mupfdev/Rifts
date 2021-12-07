/*
* =============================================================================
*  Name     : CAknExListApplication
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTAPP_H
#define AKNEXLISTAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidAknExList = { 0x10005C31 }; // UID of the application

// CLASS DECLARATION

/**
* CAknExListApp application class.
* Provides factory to create concrete document object.
*/
class CAknExListApp : public CAknApplication
    {

    private: // From CApaAppcication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CAknExListDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID (KUidAknExList).
        * @return The value of KUidAknExList.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
