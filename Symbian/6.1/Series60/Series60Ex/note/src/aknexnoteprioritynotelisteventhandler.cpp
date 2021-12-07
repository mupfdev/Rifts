/*
* =============================================================================
*  Name     : CAknExNotePriorityNoteListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include <eikenv.h>
#include "AknExNotePriorityNoteListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS
const TInt KAknExNoteTextBufLength = 256;
const TInt KAknExNotePriorityTimer = 0;
const TInt KAknExNoteDelayTime = 500 * 1000;
const TInt KAknExNoteIntervalTime = 0;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNotePriorityNoteListEventHandler::
//     CAknExNotePriorityNoteListEventHandler(
//     CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNotePriorityNoteListEventHandler::CAknExNotePriorityNoteListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNotePriorityNoteListEventHandler::
//     ~CAknExNotePriorityNoteListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------

//
CAknExNotePriorityNoteListEventHandler::
    ~CAknExNotePriorityNoteListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNotePriorityNoteListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNotePriorityNoteListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknExNoteListBoxCmdPriorityLocalLocal:
            {
            // Show the first note.
            iContainer->ShowGeneralNoteL(
                R_AKNEXNOTE_PRIORITY_LOCAL_ERROR_NOTE,
                CAknNoteDialog::ELongTimeout,
                CAknNoteDialog::EErrorTone );
            // Set call back function for showing the second note.
            TCallBack callBack( iContainer->CallbackShowPriorityLocalNoteL,
                                iContainer );
            // Show the second note.
            iContainer->CreateTimerL( callBack,
                                      KAknExNotePriorityTimer,
                                      KAknExNoteDelayTime,
                                      KAknExNoteIntervalTime );
            }
            break;
        case EAknExNoteListBoxCmdPriorityGlobalGlobal:
            {
            // Show the first note.
            TBuf<KAknExNoteTextBufLength> text( NULL );
            CEikonEnv::Static()->ReadResource(
                text, R_AKNEXNOTE_PRIORITY_GLOBAL_ERROR_TEXT );
            TPtrC noteText = text;
            iContainer->ShowGlobalNoteL( EAknGlobalErrorNote, noteText );
            // Set call back function for showing the second note.
            TCallBack callBack( iContainer->CallbackShowPriorityGlobalNoteL,
                                iContainer );
            // Show the second note.
            iContainer->CreateTimerL( callBack,
                                      KAknExNotePriorityTimer,
                                      KAknExNoteDelayTime,
                                      KAknExNoteIntervalTime );
            }
            break;
        case EAknExNoteListBoxCmdPriorityLocalGlobal:
            {
            // Show the first note.
            iContainer->ShowGeneralNoteL(
                R_AKNEXNOTE_PRIORITY_LOCAL_ERROR_NOTE,
                CAknNoteDialog::ELongTimeout,
                CAknNoteDialog::EErrorTone );
            // Set call back function for showing the second note.
            TCallBack callBack( iContainer->CallbackShowPriorityGlobalNoteL,
                                iContainer );
            // Show the second note.
            iContainer->CreateTimerL( callBack,
                                      KAknExNotePriorityTimer,
                                      KAknExNoteDelayTime,
                                      KAknExNoteIntervalTime );
            }
            break;
        case EAknExNoteListBoxCmdPriorityGlobalLocal:
            {
            // Show the first note.
            TBuf<KAknExNoteTextBufLength> text( NULL );
            CEikonEnv::Static()->ReadResource(
                text, R_AKNEXNOTE_PRIORITY_GLOBAL_ERROR_TEXT );
            TPtrC noteText = text;
            iContainer->ShowGlobalNoteL( EAknGlobalErrorNote, noteText );
            // Set call back function for showing the second note.
            TCallBack callBack( iContainer->CallbackShowPriorityLocalNoteL,
                                iContainer );
            // Show the second note.
            iContainer->CreateTimerL( callBack,
                                      KAknExNotePriorityTimer,
                                      KAknExNoteDelayTime,
                                      KAknExNoteIntervalTime );
            }
            break;
        default:
            break;
        }
    }

// End of File
