/*
* ============================================================================
*  Name     : CAknExSliderAppUi
*  Part of  : AknExSlider
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

#ifndef AKNEXSLIDERAPPUI_H
#define AKNEXSLIDERAPPUI_H

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
class CAknExSliderAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExSliderAppUi();

        /**
        * EPOC constructor.
        * Creates the view class object.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExSliderAppUi();

    private: // From CEikAppUi

        /**
        * From CEikAppUi, HandleCommandL.
        * Handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    };

#endif

// End of File
