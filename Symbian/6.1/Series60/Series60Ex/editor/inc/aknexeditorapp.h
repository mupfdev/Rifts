/*
* ============================================================================
*  Name     : CAknExEditorApp from CAknApplicaton
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXEDITORAPP_H
#define AKNEXEDITORAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidAknExEditor = { 0x10005C34 };

// CLASS DECLARATION

/**
* CAknExEditorApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExEditorApp : public CAknApplication
    {
    
    private:

        /**
        * From CApaApplication, creates CAknExEditorDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidAknExEditor).
        * @return The value of KUidAknExEditor.
        */
        TUid AppDllUid() const;
    };

#endif

// End of File

