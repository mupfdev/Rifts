/*
* =============================================================================
*  Name     : CAknExPopFieldAppUi
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXPOPFIELDAPPUI_H
#define AKNEXPOPFIELDAPPUI_H

// INCLUDES
#include <aknviewappui.h>

// FORWARD DECLARATIONS

// CONSTANTS

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following features:
* - EIKON control architecture
* - view architecture
* - status pane
*/
class CAknExPopFieldAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExPopFieldAppUi();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExPopFieldAppUi();

    private: // From CEikAppUi

        /**
        * From CEikAppUi, HandleCommandL.
        * Handles the commands.
        * @param aCommand Command to be handled
        */
        void HandleCommandL( TInt aCommand );

    };

#endif

// End of File
