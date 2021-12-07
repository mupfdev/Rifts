/*
* =============================================================================
*  Name     : CAknExListAppUi
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXLISTAPPUI_H
#define AKNEXLISTAPPUI_H

// INCLUDES
#include <aknviewappui.h>

// FORWARD DECLARATIONS

// CONSTANTS

// CLASS DECLARATION

/**
* Application UI class.
* Provides support for the following outlines:
* - EIKON control architecture
* - view architecture
* - status pane
*/
class CAknExListAppUi : public CAknViewAppUi
    {
    public: // Constructors and destructor

        /**
        * Default constructor.
        */
        CAknExListAppUi();

        /**
        * EPOC constructor.
        */
        void ConstructL();

        /**
        * Destructor.
        */
        virtual ~CAknExListAppUi();

    public: // New functions

        /**
        * Sets current outline ID.
        * @param aOutline outline ID.
        */
        void SetOutlineId( const TInt aOutlineId );

        /**
        * Returns current outline ID.
        * @return outline ID.
        */
        TInt OutlineId() const;

    private: // CEikAppUi

        /**
        * From CEikAppUi, HandleCommandL.
        * Handles the commands.
        * @param aCommand Command to be handled.
        */
        void HandleCommandL( TInt aCommand );

    private: // Data

        TInt iCurrentOutline;

    };

#endif

// End of File
