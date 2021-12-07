/*
* =============================================================================
*  Name     : CAknExNoteApp
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEAPP_H
#define AKNEXNOTEAPP_H

// INCLUDES
#include <Aknapp.h>

// CONSTANTS
const TUid KUidAknExNote = { 0x10005C2F }; // UID of the application

// CLASS DECLARATION

/**
* CAknExNoteApp application class.
* Provides factory to create concrete document object.
*/
class CAknExNoteApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CAknExNoteDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID (KUidAknExNote).
        * @return The value of KUidAknExNote.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
