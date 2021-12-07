/*
* ============================================================================
*  Name     : CAknExFormAppUi
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXFORMAPPUI_H
#define AKNEXFORMAPPUI_H

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
class CAknExFormAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExFormAppUi();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExFormAppUi();

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
