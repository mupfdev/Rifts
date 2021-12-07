/*
* ============================================================================
*  Name     : CAknExPbar from CAknApplication
*  Part of  : AknExPbar
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXPBARAPP_H
#define AKNEXPBARAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidAknExPbar = { 0x10005C2E };

// CLASS DECLARATION

/**
* CAknExPbarApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExPbarApp : public CAknApplication
    {
    private:  // From CApaApplication

        /**
        * From CApaApplication,
        * creates CAknExPbarDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication,
        * returns application's UID ( KUidAknExPbar ).
        * @return The value of KUidAknExPbar.
        */
        TUid AppDllUid() const;
    };

#endif //AKNEXPBARAPP_H

// End of File

