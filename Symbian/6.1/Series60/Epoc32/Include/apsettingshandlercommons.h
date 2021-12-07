/*
* ============================================================================
*  Name     : ApSettingsHandlerCommons.h 
*  Part of  : Access Point Settings Handler UI
*
*  Description:
*     Contains common consts, typedefs for the Access Point settings.
*  Version:
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
*
* ============================================================================
*/

#ifndef APSETTINGS_HANDLER_COMMONS_H
#define APSETTINGS_HANDLER_COMMONS_H

// INCLUDES
#include <ApEngineConsts.h>

#ifdef USE_SMS
    #define USE_SMS_IN_UI
#endif

//#define _OOMDEBUG


// CONSTANTS
_LIT( KEmpty, "");

_LIT( KTestFileName, "C:\\Data\\ApSetUiTest\\TestState.txt" );

const TInt  KApSelectionCanceled    = -350;
const TInt  KTxtNotOverriden        = -351;
const TInt  KErrInvalidTextId       = -355;

#ifdef _OOMDEBUG
    const TInt  KDialogListTest      = 1;   // Done
    const TInt  KPopupListTest       = 2;   // Done
    const TInt  KQueryTest           = 3;   // Done
    const TInt  KEditingTest         = 4;   // Done
    const TInt  KViewerTest          = 5;   // impl.
    const TInt  KCreateBlankTest     = 6;   // Impl
    const TInt  KCreateUseExistTest  = 7;   // Impl
    const TInt  KDeleteTest          = 8;   // N/I!

    const TUint32   KOOMRetryCount   = 10;
    const TUint32   KOOMRetryOffset  = 5;
#endif // _OOMDEBUG

// DATA TYPES
enum TTextID		            /// These enums are used to identify the 'overridable' text items in CApSettingsHandler.
    {
    EApSettingsSelStatusPaneText = 0x00,
    EApSettingsSelListEmptyText,
    EPopupPromptText            /// Only this last one is used & implemented.
    };


enum TTransactionResult
    {
    EOwnTransaction,
    EUsingAlreadyStarted,
    EFailedWithLocked
    };


enum TApUiExitReason
    {
    EExitNone,
    EExit,
    EShutDown
    };


// CONSTANTS
const TInt  KTTextIdMin             =  EApSettingsSelStatusPaneText;
const TInt  KTTextIdMax             =  EPopupPromptText;

const TInt  KMaxNumOfLockedDbRetries= 3;

/// Ui return code flags. They indicate what has happened inside the module. They can be combined.
/**
* Ui return code flags. They indicate what has happened inside the module. 
* They can be combined. The most important one is KApUiEventSelected & it indicates that the
* user has selected an access point (in case of selection...)
*/
const TInt  KApUiEventNone              = 0x00000000;
const TInt  KApUiEventSelected          = 0x00000001;
const TInt  KApUiEventCreatedBlank      = 0x00000002;
const TInt  KApUiEventCreatedUsedOld    = 0x00000004;
const TInt  KApUiEventEdited            = 0x00000008;
const TInt  KApUiEventDeleted           = 0x00000010;
const TInt  KApUiEventExitRequested     = 0x00000020;
const TInt  KApUiEventShutDownRequested = 0x00000040;


const TUint32  KApNoneUID               = 0x00000000;


enum TSelectionListType
    {
    EApSettingsSelListIsPopUp, 
    EApSettingsSelListIsListPane,
    EApSettingsSelListIsPopUpWithNone
    };


enum TSelectionMenuType 
    {
    EApSettingsSelMenuNormal, 
    EApSettingsSelMenuSelectOnly,
    EApSettingsSelMenuSelectNormal
    };



enum TApSettingsHandlerUiPanicCodes
	{
	EMenuCommandUnknown,
    EInvalidDbType,
    EInvalidBitmapType,
    EInvalidBearerType,
    EInvalidIspRequest,
    ENullPointer,
    EUnknownCase,
    EInvalidTextType,
    EInvalidState
	} ;

void Panic( TApSettingsHandlerUiPanicCodes aPanic );
TInt AskQueryL( TInt aResId, TDesC* aVar = NULL );
TInt ShowNoteL( TInt aResId, TDesC* aVar = NULL );


#ifdef _OOMDEBUG
    TInt GetTestState();
#endif // _OOMDEBUG

#endif


// End of File
