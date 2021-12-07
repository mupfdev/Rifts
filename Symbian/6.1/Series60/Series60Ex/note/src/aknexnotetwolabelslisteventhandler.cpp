/*
* =============================================================================
*  Name     : CAknExNoteTwoLabelsListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include "AknExNoteTwoLabelsListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteTwoLabelsListEventHandler::CAknExNoteTwoLabelsListEventHandler(
//  CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteTwoLabelsListEventHandler::CAknExNoteTwoLabelsListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteTwoLabelsListEventHandler::~CAknExNoteTwoLabelsListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteTwoLabelsListEventHandler::~CAknExNoteTwoLabelsListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteTwoLabelsListEventHandler::HandleSelectedListItemL(
//  TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteTwoLabelsListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExNoteListBoxCmdSingularLabel: // Singular label
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_INFORMATION_NOTE,
                                          EAknExNoteCtrlIdInformationNote,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EConfirmationTone,
                                          EFalse );
            break;
        case EAknExNoteListBoxCmdPluralLabel: // Plural label
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_INFORMATION_NOTE,
                                          EAknExNoteCtrlIdInformationNote,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EConfirmationTone,
                                          ETrue );
            break;
        default:
            break;
        }
    }

// End of File
