/*
* ============================================================================
*  Name     : CAknExMenuApp from CAknApplication
*  Part of  : AknExMenu
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXMNEUAPP_H
#define AKNEXMNEUAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidAknExMenu = { 0x10005C30 };

// CLASS DECLARATION

/**
* CAknExMenuApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExMenuApp : public CAknApplication
    {
    
    private:

        /**
        * From CApaApplication, creates CAknExMenuDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidAknExMenu).
        * @return The value of KUidAknExMenu.
        */
        TUid AppDllUid() const;
    };

#endif    // AKNEXMNEUAPP_H

// End of File

