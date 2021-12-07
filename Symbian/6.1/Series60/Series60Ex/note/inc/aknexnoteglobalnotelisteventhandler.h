/*
* =============================================================================
*  Name     : CAknExNoteGlobalNoteListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEGLOBALNOTELISTEVENTHANDLER_H
#define AKNEXNOTEGLOBALNOTELISTEVENTHANDLER_H

// INCLUDES
#include "AknExNoteBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNoteGlobalNoteListEventHandler container control class.
*/
class CAknExNoteGlobalNoteListEventHandler :
    public CAknExNoteBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Overload constructors.
        * @param aContainer Pointer to CAknExNoteContainer class object.
        */
        CAknExNoteGlobalNoteListEventHandler(
            CAknExNoteContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExNoteGlobalNoteListEventHandler();

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
