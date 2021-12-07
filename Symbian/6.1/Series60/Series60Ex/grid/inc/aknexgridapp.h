/*
* ============================================================================
*  Name     : CAknExGridApp from CAknApplication
*  Part of  : AknExGrid
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXGRIDAPP_H
#define AKNEXGRIDAPP_H

// INCLUDES
//#include <eikapp.h>
#include <aknapp.h>

// CONSTANTS
// UID of the application
#ifdef _UNICODE
const TUid KUidAknExGrid = { 0x10005C32 };
#else
#endif

// CLASS DECLARATION

/**
* CAknExGridApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExGridApp : public CAknApplication
    {
    
    private:  // from CApaApplication
        /**
        * From CApaApplication
        * creates CAknExGridDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication
        * returns application's UID (KUidAknExGrid).
        * @return The value of KUidAknExGrid.
        */
        TUid AppDllUid() const;
    };

#endif      // AKNEXGRIDAPP_H

// End of File

