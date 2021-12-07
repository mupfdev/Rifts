/*
* =============================================================================
*  Name     : CAknExNoteBaseListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <eikclb.h> // For listbox
#include "AknExNoteBaseListEventHandler.h"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteBaseListEventHandler::CAknExNoteBaseListEventHandler(
//  CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteBaseListEventHandler::CAknExNoteBaseListEventHandler(
    CAknExNoteContainer* aContainer )
:   iContainer( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteBaseListEventHandler::~CAknExNoteBaseListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteBaseListEventHandler::~CAknExNoteBaseListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteBaseListEventHandler::HandleListBoxEventL(
//  CEikListBox* aListBox, TListBoxEvent aEventType )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteBaseListEventHandler::HandleListBoxEventL(
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
