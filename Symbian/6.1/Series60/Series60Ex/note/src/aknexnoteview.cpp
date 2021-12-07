/*
* =============================================================================
*  Name     : CAknExNoteView
*  Part of  : AknExNote
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <akntitle.h>
#include <avkon.hrh>
#include <AknExNote.rsg>
#include "AknExNoteView.h"
#include "AknExNoteContainer.h"
#include "aknexnote.hrh"
#include <AVKON.RSG>
#include <AVKON.MBG>
#include <AKNEXNOTE.MBG>


// CONSTANTS
const TUid KViewId = { 1 }; // UID of view
const TInt KAknExNoteTitleBufLength = 256;
const TInt KAknExNoteInitializeResourceId = 0;
const TInt KAknExNoteCancelGlonalNoteInterval(800000); // in microseconds

_LIT(KAknExNoteBmpFileName, "\\system\\apps\\aknexnote\\aknexnote.mbm");

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExNoteView::CAknExNoteView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExNoteView::CAknExNoteView()
:   iContainer( NULL ),
    iCurrentOutline( EAknExNoteCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// CAknExNoteView::~CAknExNoteView()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExNoteView::~CAknExNoteView()
    {
    delete iContainer;
    }

// ----------------------------------------------------------------------------
// void CAknExNoteView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExNoteView::ConstructL()
    {
    BaseConstructL( R_AKNEXNOTE_VIEW );
    }

// ----------------------------------------------------------------------------
// void CAknExNoteView::DisplayNextOutLineL()
//
// ----------------------------------------------------------------------------
//
void CAknExNoteView::DisplayNextOutlineL()
    {
    switch ( iCurrentOutline )
        {
        case EAknExNoteCmdEmptyOutline:
            HandleCommandL( EAknExNoteCmdOutline01 );
            break;
        case EAknExNoteCmdOutline01:
            HandleCommandL( EAknExNoteCmdOutline02 );
            break;
        case EAknExNoteCmdOutline02:
            HandleCommandL( EAknExNoteCmdOutline03 );
            break;
        case EAknExNoteCmdOutline03:
            HandleCommandL( EAknExNoteCmdOutline04 );
            break;
        case EAknExNoteCmdOutline04: 
            HandleCommandL( EAknExNoteCmdOutline05 );
            break;
        case EAknExNoteCmdOutline05:
            HandleCommandL( EAknExNoteCmdOutline07 );
            break;
        case EAknExNoteCmdOutline07:
            HandleCommandL( EAknExNoteCmdOutline08 );
            break;
        case EAknExNoteCmdOutline08:
            HandleCommandL( EAknExNoteCmdOutline31 );
            break;
        case EAknExNoteCmdOutline31:
            HandleCommandL( EAknExNoteCmdOutline32 );
            break;
        case EAknExNoteCmdOutline32:
            HandleCommandL( EAknExNoteCmdOutline33 );
            break;
        case EAknExNoteCmdOutline33:
            HandleCommandL( EAknExNoteCmdOutline34 );
            break;
        case EAknExNoteCmdOutline34:
            HandleCommandL( EAknExNoteCmdOutline35 );
            break;
        case EAknExNoteCmdOutline35:
            HandleCommandL( EAknExNoteCmdOutline51 );
            break;
        case EAknExNoteCmdOutline51:
            HandleCommandL( EAknExNoteCmdOutline52 );
            break;
        case EAknExNoteCmdOutline52:
            HandleCommandL( EAknExNoteCmdOutline53 );
            break;
        case EAknExNoteCmdOutline53:
            HandleCommandL( EAknExNoteCmdOutline54 );
            break;
        case EAknExNoteCmdOutline54:
            HandleCommandL( EAknExNoteCmdOutline55 );
            break;
        case EAknExNoteCmdOutline55:
            HandleCommandL( EAknExNoteCmdOutline56 );
            break;
        case EAknExNoteCmdOutline56:
            HandleCommandL( EAknExNoteCmdOutline57 );
            break;
        case EAknExNoteCmdOutline57:
            HandleCommandL( EAknExNoteCmdOutline58 );
            break;
        case EAknExNoteCmdOutline58:
            HandleCommandL( EAknExNoteCmdOutline59 );
            break;
        case EAknExNoteCmdOutline59:
            HandleCommandL( EAknExNoteCmdOutline60 );
            break;
        case EAknExNoteCmdOutline60: 
            HandleCommandL( EAknExNoteCmdOutline61 );
            break;
        case EAknExNoteCmdOutline61:
        default:
            HandleCommandL( EAknExNoteCmdEmptyOutline );
            break;
        }
    }

// ----------------------------------------------------------------------------
// TUid CAknExNoteView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
//
TUid CAknExNoteView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// void CAknExNoteView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExNoteView::HandleCommandL( TInt aCommand )
    {
    iContainer->DiscardListboxAndTimer();
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ProcessCommandL( EAknCmdExit );
            break;
        case EAknCmdExit:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;
        case EAknExNoteCmdEmptyOutline:
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_TITLE );
            IndicateTitlePaneTextL( aCommand );
            break;
        case EAknExNoteCmdOutline01: // Error Note
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_ERROR_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EErrorTone );
            break;
        case EAknExNoteCmdOutline02: // Warning Note
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_WARNING_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EWarningTone );
            break;
        case EAknExNoteCmdOutline03: // Information Note
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_INFORMATION_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EConfirmationTone );
            break;
        case EAknExNoteCmdOutline04: // Confirmation Note
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_CONFIRMATION_NOTE,
                                          CAknNoteDialog::EShortTimeout,
                                          CAknNoteDialog::EConfirmationTone );
            break;
        case EAknExNoteCmdOutline05: // Wait Note
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowWaitNoteL(R_AKNEXNOTE_WAIT_NOTE_SOFTKEY_CANCEL,
                                      EAknExNoteCtrlIdWaitNote);
            break;
        case EAknExNoteCmdOutline07: // Static text in note
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowGeneralNoteL( R_AKNEXNOTE_INFORMATION_NOTE,
                                          CAknNoteDialog::ELongTimeout,
                                          CAknNoteDialog::EConfirmationTone );
            break;
        case EAknExNoteCmdOutline08: // Dynamic text
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowDynamicNumberNoteL();
            break;
        case EAknExNoteCmdOutline31: // note wrappers
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowNoteWrappersConfirmationL();
            break;
        case EAknExNoteCmdOutline32: // note wrappers
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowNoteWrappersInformationL();
            break;
        case EAknExNoteCmdOutline33: // note wrappers
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowNoteWrappersWarningL();
            break;
        case EAknExNoteCmdOutline34: // note wrappers
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowNoteWrappersErrorL();
            break;
        case EAknExNoteCmdOutline35: // progress note 
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowProgressNoteUnderSingleProcessL( 
                                            R_AKNEXNOTE_PROGRESS_NOTE,
                                            EAknExNoteCtrlIdProgressNote );
            break;

        case EAknExNoteCmdOutline51: // ShowNoteL (EAknGlobalInformationNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalInformationNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALINFORMATIONNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline52: // ShowNoteL (EAknGlobalWarningNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalWarningNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALWARNINGNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline53: // ShowNoteL (EAknGlobalConfirmationNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalConfirmationNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALCONFIRMATIONNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline54: // ShowNoteL (EAknGlobalErrorNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalErrorNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALERRORNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline55: // ShowNoteL (EAknGlobalChargingNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalChargingNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALCHARGINGNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline56: // ShowNoteL (EAknGlobalWaitNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalWaitNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALWAITNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline57: // ShowNoteL (EAknGlobalPermanentNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalPermanentNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALPERMANENTNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline58: // ShowNoteL (EAknGlobalNotChargingNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalNotChargingNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALNOTCHARGINGNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline59: // ShowNoteL (EAknGlobalBatteryFullNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalBatteryFullNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALBATTERYFULLNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline60: // ShowNoteL (EAknGlobalBatteryLowNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalBatteryLowNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALBATTERYLOWNOTE_TEXT);
            break;
        case EAknExNoteCmdOutline61: // ShowNoteL (EAknGlobalRechargeBatteryNote)
            iCurrentOutline = aCommand;
            iContainer->SetTextToLabelL( R_AKNEXNOTE_TEXT_LABEL_OPERATION );
            IndicateTitlePaneTextL( aCommand );
            iContainer->ShowShowNoteL(EAknGlobalRechargeBatteryNote, R_AKNEXNOTE_SHOWNOTEL_GLOBALRECHARGEBATTERYNOTE_TEXT);
            break;
        case EAknExNoteCbaCmdNext:
            DisplayNextOutlineL();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExNoteView::IndicateTitlePaneTextL( TInt aCommand )
// Set title text to status-pane
// ----------------------------------------------------------------------------
//
void CAknExNoteView::IndicateTitlePaneTextL( TInt aCommand )
    {
    TBool useDefaultText( EFalse );
    TInt resourceId( KAknExNoteInitializeResourceId );
    switch ( aCommand )
        {
        case EAknExNoteCmdEmptyOutline:
            useDefaultText = ETrue;
            break;
        case EAknExNoteCmdOutline01:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE01;
            break;
        case EAknExNoteCmdOutline02:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE02;
            break;
        case EAknExNoteCmdOutline03:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE03;
            break;
        case EAknExNoteCmdOutline04:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE04;
            break;
        case EAknExNoteCmdOutline05:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE05;
            break;
        case EAknExNoteCmdOutline07:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE07;
            break;
        case EAknExNoteCmdOutline08:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE08;
            break;
        case EAknExNoteCmdOutline31:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE31;
            break;
        case EAknExNoteCmdOutline32:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE32;
            break;
        case EAknExNoteCmdOutline33:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE33;
            break;
        case EAknExNoteCmdOutline34:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE34;
            break;
        case EAknExNoteCmdOutline35:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE35;
            break;

        case EAknExNoteCmdOutline51:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE51;
            break;
        case EAknExNoteCmdOutline52:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE52;
            break;
        case EAknExNoteCmdOutline53:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE53;
            break;
        case EAknExNoteCmdOutline54:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE54;
            break;
        case EAknExNoteCmdOutline55:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE55;
            break;
        case EAknExNoteCmdOutline56:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE56;
            break;
        case EAknExNoteCmdOutline57:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE57;
            break;
        case EAknExNoteCmdOutline58:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE58;
            break;
        case EAknExNoteCmdOutline59:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE59;
            break;
        case EAknExNoteCmdOutline60:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE60;
            break;
        case EAknExNoteCmdOutline61:
            resourceId = R_AKNEXNOTE_TEXT_STATUS_PANE_TITLE61;
            break;
        default:
            break;
        }

    CAknTitlePane* titlePane = STATIC_CAST(
        CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
    if ( useDefaultText )
        {
        titlePane->SetTextToDefaultL();
        }
    else
        {
        TBuf<KAknExNoteTitleBufLength> titleText( NULL );
        iEikonEnv->ReadResource( titleText, resourceId );
        titlePane->SetTextL( titleText );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExNoteView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
//
void CAknExNoteView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    // Creates container object
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExNoteContainer( this );
        iContainer->ConstructL( ClientRect() );
        iContainer->SetMopParent(this);
        }
    // Adds container to view control stack.
    AppUi()->AddToStackL( *this, iContainer );
    iContainer->MakeVisible( ETrue );
    }

// ----------------------------------------------------------------------------
// void CAknExNoteView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
//
void CAknExNoteView::DoDeactivate()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        iContainer->MakeVisible( EFalse );
        // Removes container from view control stack.
        AppUi()->RemoveFromStack( iContainer );
        }
    }

// End of File
