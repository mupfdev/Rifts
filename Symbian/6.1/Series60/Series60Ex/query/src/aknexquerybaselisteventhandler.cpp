/*
* =============================================================================
*  Name     : CAknExQueryBaseListEventHandler
*  Part of  : AknExQuery
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikclb.h>   // For listbox
#include "AknExQueryBaseListEventHandler.h"

// MACROS

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExQueryBaseListEventHandler::CAknExQueryBaseListEventHandler()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExQueryBaseListEventHandler::CAknExQueryBaseListEventHandler(
    CAknExQueryContainer* aContainer )
:   iContainer( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryBaseListEventHandler::~CAknExQueryBaseListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExQueryBaseListEventHandler::~CAknExQueryBaseListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExQueryBaseListEventHandler::HandleListBoxEventL(
//     CEikListBox* TListBoxEvent,
//     TListBoxEvent aEventType )
// ----------------------------------------------------------------------------
//
void CAknExQueryBaseListEventHandler::HandleListBoxEventL(
    CEikListBox* aListBox,
    TListBoxEvent aEventType )
    {
    if ( ( aEventType == MEikListBoxObserver::EEventEnterKeyPressed ) ||
         ( aEventType == MEikListBoxObserver::EEventItemClicked ) )
        {
        HandleSelectedListItemL( aListBox->CurrentItemIndex() );
        }
    }

// End of File
