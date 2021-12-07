/*
* ============================================================================
*  Name     : CAknExPopListApp from CeikApplication
*  Part of  : AknExPopList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPOPLISTAPP_H
#define AKNEXPOPLISTAPP_H

// INCLUDES
#include <AknApp.h>

// CONSTANTS
// UID of the application 
const TUid KUidAknExPopList = { 0x10005C2C };


// CLASS DECLARATION

/**
* CAknExPopListApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExPopListApp : public CAknApplication
    {
    
    private:

        /**
        * From CApaApplication, creates CAknExPopListDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidAknExPopList).
        * @return The value of KUidAknExPopList.
        */
        TUid AppDllUid() const;
    };

#endif // AKNEXPOPLISTAPP_H

// End of File

