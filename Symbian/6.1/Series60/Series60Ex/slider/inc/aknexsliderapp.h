/*
* ============================================================================
*  Name     : CAknExSliderApplication
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSLIDERAPP_H
#define AKNEXSLIDERAPP_H

// INCLUDES
#include <Aknapp.h>

// CONSTANTS
const TUid KUidAknExSlider = { 0x10005C28 }; // UID of the application.

// CLASS DECLARATION

/**
* CAknExSliderApplication application class.
* Provides factory to create concrete document object.
*/
class CAknExSliderApplication : public CAknApplication
    {
    private: // From CApaApplication

        /**
        * From CApaApplication, CreateDocumentL.
        * Creates CAknExSliderDocument document object.
        * @return A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();

        /**
        * From CApaApplication, AppDllUid.
        * Returns application's UID (KUidAknExSlider).
        * @return The value of KUidAknExSlider.
        */
        TUid AppDllUid() const;

    };

#endif

// End of File
