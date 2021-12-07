/*
* ============================================================================
*  Name     : AknExSettingListAppUi.hrh
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/
#ifndef AKNEXSETTINGLISTAPPUI_H
#define AKNEXSETTINGLISTAPPUI_H

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
class CAknExSettingListAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExSettingListAppUi();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExSettingListAppUi();

    private: // From CEikAppUi

        /**
        * From CEikAppUi, HandleCommandL.
        * Takes care of command handling.
        * @param aCommand command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    };

#endif

// End of File
