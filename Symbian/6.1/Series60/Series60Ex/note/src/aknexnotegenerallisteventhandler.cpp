/*
* =============================================================================
*  Name     : CAknExNoteGeneralListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include "AknExNoteGeneralListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteGeneralListEventHandler::CAknExNoteGeneralListEventHandler(
//  CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteGeneralListEventHandler::CAknExNoteGeneralListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteGeneralListEventHandler::~CAknExNoteGeneralListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteGeneralListEventHandler::~CAknExNoteGeneralListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteGeneralListEventHandler::HandleSelectedListItemL( TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteGeneralListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExNoteListBoxCmdErrorNote: // Error note
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_ERROR_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EErrorTone );
            break;
        case EAknExNoteListBoxCmdWarningNote: // Warning note
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_WARNING_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EWarningTone );
            break;
        case EAknExNoteListBoxCmdInformationNote: // Information note
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_INFORMATION_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EConfirmationTone );
            break;
        case EAknExNoteListBoxCmdConfirmationNote: // Confirmatino note
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_CONFIRMATION_NOTE,
                                          CAknNoteDialog::EShortTimeout,
                                          CAknNoteDialog::EConfirmationTone );
            break;
        default:
            break;
        }
    }

// End of File
