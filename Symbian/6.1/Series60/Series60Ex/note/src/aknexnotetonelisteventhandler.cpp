/*
* =============================================================================
*  Name     : CAknExNoteToneListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include "AknExNoteToneListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteToneListEventHandler::CAknExNoteToneListEventHandler(
//  CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteToneListEventHandler::CAknExNoteToneListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteToneListEventHandler::~CAknExNoteToneListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteToneListEventHandler::~CAknExNoteToneListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteToneListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteToneListEventHandler::HandleSelectedListItemL( TInt aCommand )
    {
    switch( aCommand )
        {
        case EAknExNoteListBoxCmdErrorTone: // Error tone
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_ERROR_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EErrorTone );
            break;
        case EAknExNoteListBoxCmdWarningTone: // Warning Tone
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_WARNING_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EWarningTone );
            break;
        case EAknExNoteListBoxCmdConfirmationTone: // Confirmatino tone
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_CONFIRMATION_NOTE,
                                          CAknNoteDialog::EShortTimeout,
                                          CAknNoteDialog::EConfirmationTone );
            break;
        default:
            break;
        }
    }

// End of File
