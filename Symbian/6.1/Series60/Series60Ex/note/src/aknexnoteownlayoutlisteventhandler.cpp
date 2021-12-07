/*
* =============================================================================
*  Name     : CAknExNoteOwnLayoutListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include "AknExNoteOwnLayoutListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteOwnLayoutListEventHandler::CAknExNoteOwnLayoutListEventHandler(
//  CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteOwnLayoutListEventHandler::CAknExNoteOwnLayoutListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteOwnLayoutListEventHandler::~CAknExNoteOwnLayoutListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteOwnLayoutListEventHandler::~CAknExNoteOwnLayoutListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteOwnLayoutListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteOwnLayoutListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExNoteListBoxCmdOwnLayoutCase1: // Case 1
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_OWNLAYOUT_CASE1,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EErrorTone );
            break;
        case EAknExNoteListBoxCmdOwnLayoutCase2: // Case 2
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_OWNLAYOUT_CASE2,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EErrorTone );
            break;
        case EAknExNoteListBoxCmdOwnLayoutCase3: // Case 3
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_OWNLAYOUT_CASE3,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EErrorTone );
            break;
        default:
            break;
        }
    }

// End of File
