/*
* =============================================================================
*  Name     : CAknExQueryBaseListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

#ifndef AKNEXQUERYBASELISTEVENTHANDLER_H
#define AKNEXQUERYBASELISTEVENTHANDLER_H

// INCLUDES
#include <e32base.h>
#include <eiklbo.h> // For MEikListBoxObserver

// FORWARD DECLARATIONS
class CAknExQueryContainer;

// CLASS DECLARATION

/**
* CAknExQueryBaseListEventHandler class.
*/
class CAknExQueryBaseListEventHandler :
    public CBase,
    public MEikListBoxObserver
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aContainer Pointer to Container class object.
        */
        CAknExQueryBaseListEventHandler( CAknExQueryContainer* aContainer );

        /**
        * Destructor.
        */
        virtual ~CAknExQueryBaseListEventHandler();

    public: // New funcsion

        /**
        * Handles events that list item selected.
        * Pure virtual function.
        * @param aCommand Selected list item index
        */
        virtual void HandleSelectedListItemL( TInt aCommand ) = NULL;

    public: // From MEikListBoxObserver

        /**
        * From MEikListBoxObserver, Handle listbox event
        * Handles the list box events.
        * When list item is selected, HandleSelectedListItemL() is called.
        * @param aListBox Pointer to ListBox object.
        * @param aEventType.
        */
        void HandleListBoxEventL(
            CEikListBox* aListBox,
            TListBoxEvent aEventType );

    protected: //data

        CAknExQueryContainer* iContainer;

    };

#endif

// End of File
