/*
* =============================================================================
*  Name     : CAknExNoteToneListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTETONELISTEVENTHANDLER_H
#define AKNEXNOTETONELISTEVENTHANDLER_H

// INCLUDES
#include "AknExNoteBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNoteToneListEventHandler container control class.
*/
class CAknExNoteToneListEventHandler : public CAknExNoteBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Overload constructors.
        * @param aContainer Pointer to CAknExNoteContainer class object.
        */
        CAknExNoteToneListEventHandler( CAknExNoteContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExNoteToneListEventHandler();

    private: // From CAknExNoteBaseListEventHandler

        /**
        * From CAknExNoteBaseListEventHandler, HandlerSelectedListItem.
        * Handles the event which list item selected.
        * @param aCommand Selected item index
        */
        void HandleSelectedListItemL( TInt aCommand );

    };

#endif

// End of File
