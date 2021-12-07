/*
* =============================================================================
*  Name     : AknExSettingListApp.h
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSETTINGLISTAPP_H
#define AKNEXSETTINGLISTAPP_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
const TUid KUidAknExSettingList = { 0x10005C29 }; // UID of the application.

// CLASS DECLARATION

/**
* CAknExSettingListApp application class.
* Provides factory to create concrete document object.
* 
*/
class CAknExSettingListApp : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CAknExSettingListDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID ( KUidAknExSettingList ).
        * @return The value of KUidAknExSettingList.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
