/*
* =============================================================================
*  Name     : CAknExNoteAnimationListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include "AknExNoteAnimationListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteAnimationListEventHandler::CAknExNoteAnimationListEventHandler(
//  CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteAnimationListEventHandler::CAknExNoteAnimationListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteAnimationListEventHandler::~CAknExNoteAnimationListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteAnimationListEventHandler::~CAknExNoteAnimationListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteAnimationListEventHandler::HandleSelectedListItemL(
//  TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteAnimationListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExNoteListBoxCmdWaitNote: // Wait note
            iContainer->ShowWaitNoteL(
                /*R_AKNEXNOTE_WAIT_NOTE*/ 
                R_AKNEXNOTE_WAIT_NOTE_SOFTKEY_CANCEL,
                EAknExNoteCtrlIdWaitNote);
            break;
        case EAknExNoteListBoxCmdProgressNote: // Progress note
            iContainer->ShowProgressNoteL( R_AKNEXNOTE_PROGRESS_NOTE,
                                           EAknExNoteCtrlIdProgressNote );
            break;
        default:
            break;
        }
    }

// End of File
