/*
* =============================================================================
*  Name     : CAknExQueryApplication
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYAPP_H
#define AKNEXQUERYAPP_H

// INCLUDES
#include <Aknapp.h>

// CONSTANTS
const TUid KUidAknExQuery = { 0x10005C2B }; // UID of the application

// CLASS DECLARATION

/**
* CAknExQueryApp application class.
* Provides factory to create concrete document object.
*/
class CAknExQueryApp : public CAknApplication
    {
    private: // Form CApalication

        /**
        * From CApaApplication, creates CAknExQueryDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, returns application's UID (KUidAknExQuery).
        * @return The value of KUidAknExQuery.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
