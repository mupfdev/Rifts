/*
* ============================================================================
*  Name     : CAknExScrollerApp from CAknApplication
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSCROLLERAPP_H
#define AKNEXSCROLLERAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidAknExScroller = { 0x10005C2A };

// CLASS DECLARATION

/**
* CAknExScrollerApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExScrollerApp : public CAknApplication
    {
    private:
        /**
        * From CApaApplication, returns application's UID (KUidAknExScroller).
        * @return The value of KUidAknExScroller.
        */
        TUid AppDllUid() const;

        /**
        * From CApaApplication, creates CAknExScrollerDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
    };

#endif // AKNEXSCROLLERAPP_H

// End of File

