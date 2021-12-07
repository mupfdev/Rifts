/*
* ============================================================================
*  Name     : CAknExSpaneApp from CEikApplication
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSPANEAPP_H
#define AKNEXSPANEAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
#ifdef _UNICODE
const TUid KUidAknExSpane = { 0x10005C27 };
#else
#endif

// CLASS DECLARATION

/**
* CAknExSpaneApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExSpaneApp : public CAknApplication
    {
    
    private:

        /**
        * From CApaApplication, creates CAknExSpaneDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidAknExSpane).
        * @return The value of KUidAknExSpane.
        */
        TUid AppDllUid() const;
    };

#endif  // AKNEXSPANEAPP_H

// End of File

