/*
* =============================================================================
*  Name     : CAknExNoteGlobalNoteListEventHandler
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <AknExNote.rsg>
#include <eikenv.h>
#include "AknExNoteGlobalNoteListEventHandler.h"
#include "AknExNoteContainer.h"
#include "AknExNote.hrh"

// CONSTANTS
const TInt KAknExNotePriorityTimer = 0;
const TInt KAknExNoteDelayTime = 7 * 1000 * 1000;
const TInt KAknExNoteIntervalTime = 0;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteGlobalNoteListEventHandler::
//     CAknExNoteGlobalNoteListEventHandler(
//     CAknExNoteContainer* aContainer )
// Constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteGlobalNoteListEventHandler::CAknExNoteGlobalNoteListEventHandler(
    CAknExNoteContainer* aContainer )
:   CAknExNoteBaseListEventHandler( aContainer )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteGlobalNoteListEventHandler::
//     ~CAknExNoteGlobalNoteListEventHandler()
// Destructor.
// ----------------------------------------------------------------------------

//
CAknExNoteGlobalNoteListEventHandler::
    ~CAknExNoteGlobalNoteListEventHandler()
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteGlobalNoteListEventHandler::HandleSelectedListItemL(
//     TInt aCommand )
//
// ----------------------------------------------------------------------------
//
void CAknExNoteGlobalNoteListEventHandler::HandleSelectedListItemL(
    TInt aCommand )
    {
    TCallBack callBack( NULL );
    TInt priorityTimer( NULL );
    TInt delayTime( NULL );
    TInt intervalTime( NULL );
    switch ( aCommand )
        {
        case EAknExNoteListBoxCmdGlobalGeneralNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalGeneralNoteL,
                                  iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalWarningNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalWarningNoteL,
                                  iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalConfirmationNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack(
                iContainer->CallbackShowGlobalConfirmationNoteL, iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalErrorNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalErrorNoteL,
                                  iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalChargingNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalChargingNoteL,
                                  iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalNotChargingNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalNotChargingNoteL,
                                  iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalBatteryFullNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalBatteryFullNoteL,
                                   iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalBatteryLowNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack( iContainer->CallbackShowGlobalBatteryLowNoteL,
                                  iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        case EAknExNoteListBoxCmdGlobalRechargeBatteryNote:
            {
            // Set CreateTimerL() parameter.
            callBack = TCallBack(
                iContainer->CallbackShowGlobalRechargeBatteryNoteL,
                iContainer );
            priorityTimer = KAknExNotePriorityTimer;
            delayTime = KAknExNoteDelayTime;
            intervalTime = KAknExNoteIntervalTime;
            }
            break;
        default:
            return;
        }
    // Change application.
    TApaAppFileName applicationName( NULL );
    CEikonEnv::Static()->ReadResource( applicationName,
                                       R_AKNEXNOTE_OTHER_APPLICATION_NAME );
    iContainer->ForwardOtherApplicationL( applicationName );
    // Show global note.
    iContainer->CreateTimerL( callBack,
                              KAknExNotePriorityTimer,
                              KAknExNoteDelayTime,
                              KAknExNoteIntervalTime );
    }
// End of File
