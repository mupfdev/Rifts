/*
* =============================================================================
*  Name     : CAknExNoteAnimationListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXNOTEANIMATIONLISTEVENTHANDLER_H
#define AKNEXNOTEANIMATIONLISTEVENTHANDLER_H

// INCLUDES
#include "AknExNoteBaseListEventHandler.h"

// FORWARD DECLARATIONS
class CAknExNoteContainer;

// CONSTANTS

// CLASS DECLARATION

/**
* CAknExNoteAnimationListEventHandler container control class.
*/
class CAknExNoteAnimationListEventHandler :
    public CAknExNoteBaseListEventHandler
    {
    public: // Constructors and destructor

        /**
        * Overload constructors.
        * @param aContainer Pointer to CAknExNoteContainer class object.
        */
        CAknExNoteAnimationListEventHandler( CAknExNoteContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExNoteAnimationListEventHandler();

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
