/*
* =============================================================================
*  Name     : CAknExNotePriorityNoteListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEPRIORITYNOTELISTEVENTHANDLER_H
#define AKNEXNOTEPRIORITYNOTELISTEVENTHANDLER_H

// INCLUDES
#include "AknExNoteBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNotePriorityNoteListEventHandler container control class.
*/
class CAknExNotePriorityNoteListEventHandler :
    public CAknExNoteBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Overload constructors.
        * @param aContainer Pointer to CAknExNoteContainer class object.
        */
        CAknExNotePriorityNoteListEventHandler(
            CAknExNoteContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExNotePriorityNoteListEventHandler();

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
