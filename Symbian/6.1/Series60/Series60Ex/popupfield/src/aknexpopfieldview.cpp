/*
* =============================================================================
*  Name     : CAknExPopFieldView
*  Part of  : AknExPopField
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <avkon.hrh>
#include <akntitle.h>
#include <aknviewappui.h>
#include <aknexpopfield.rsg>
#include "AknExPopField.hrh"
#include "AknExPopFieldView.h"
#include "AknExPopFieldContainer.h"

// CONSTANTS
const TUid KViewId = { 1 }; // UID of view
const TInt KAknExPopFieldResourceIdInitialize = 0;
const TInt KAknExPopFieldTitleBufLength = 256;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExPopFieldView::CAknExPopFieldView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldView::CAknExPopFieldView()
:   iContainer( NULL ),
    iCurrentOutline( EAknExPopFieldCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldView::ConstructL()
    {
    BaseConstructL( R_AKNEXPOPFIELD_VIEW );
    }

// ----------------------------------------------------------------------------
// CAknExPopFieldView::~CAknExPopFieldView()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExPopFieldView::~CAknExPopFieldView()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        // Removes container from view control stack.
        AppUi()->RemoveFromStack( iContainer );
        }
    delete iContainer;
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldView::DisplayNextOutlineL( TInt )
//
// ----------------------------------------------------------------------------
//
void CAknExPopFieldView::DisplayNextOutlineL()
    {
    switch ( iCurrentOutline )
        {
        case EAknExPopFieldCmdEmptyOutline:
            HandleCommandL( EAknExPopFieldCmdOutline01 );
            break;
        case EAknExPopFieldCmdOutline01:
            HandleCommandL( EAknExPopFieldCmdOutline02 );
            break;
        case EAknExPopFieldCmdOutline02:
            HandleCommandL( EAknExPopFieldCmdOutline03 );
            break;
        case EAknExPopFieldCmdOutline03:
            HandleCommandL( EAknExPopFieldCmdOutline04 );
            break;
        case EAknExPopFieldCmdOutline04:
            HandleCommandL( EAknExPopFieldCmdOutline05 );
            break;
        case EAknExPopFieldCmdOutline05:
            HandleCommandL( EAknExPopFieldCmdOutline06 );
            break;
        case EAknExPopFieldCmdOutline06:
            HandleCommandL( EAknExPopFieldCmdOutline07 );
            break;
        case EAknExPopFieldCmdOutline07:
            HandleCommandL( EAknExPopFieldCmdOutline08 );
            break;
        case EAknExPopFieldCmdOutline08:
            HandleCommandL( EAknExPopFieldCmdOutline09 );
            break;
        case EAknExPopFieldCmdOutline09:
            HandleCommandL( EAknExPopFieldCmdOutline10 );
            break;
        case EAknExPopFieldCmdOutline10:
            HandleCommandL( EAknExPopFieldCmdOutline11 );
            break;
        case EAknExPopFieldCmdOutline11:
            HandleCommandL( EAknExPopFieldCmdOutline12 );
            break;
        case EAknExPopFieldCmdOutline12:
            HandleCommandL( EAknExPopFieldCmdOutline13 );
            break;
        case EAknExPopFieldCmdOutline13:
            HandleCommandL( EAknExPopFieldCmdOutline14 );
            break;
        case EAknExPopFieldCmdOutline14:
            HandleCommandL( EAknExPopFieldCmdOutline15 );
            break;
        case EAknExPopFieldCmdOutline15:
            HandleCommandL( EAknExPopFieldCmdOutline16 );
            break;
        case EAknExPopFieldCmdOutline16:
            HandleCommandL( EAknExPopFieldCmdOutline17 );
            break;
        case EAknExPopFieldCmdOutline17:
            HandleCommandL( EAknExPopFieldCmdOutline18 );
            break;
        case EAknExPopFieldCmdOutline18:
            HandleCommandL( EAknExPopFieldCmdOutline19 );
            break;
        case EAknExPopFieldCmdOutline19:
            HandleCommandL( EAknExPopFieldCmdOutline20 );
            break;
        case EAknExPopFieldCmdOutline20:
            HandleCommandL( EAknExPopFieldCmdOutline21 );
            break;
        case EAknExPopFieldCmdOutline21:
            HandleCommandL( EAknExPopFieldCmdOutline22 );
            break;
        case EAknExPopFieldCmdOutline22:
            HandleCommandL( EAknExPopFieldCmdOutline23 );
            break;
        case EAknExPopFieldCmdOutline23:
            HandleCommandL( EAknExPopFieldCmdOutline24 );
            break;
        case EAknExPopFieldCmdOutline24:
            HandleCommandL( EAknExPopFieldCmdOutline25 );
            break;
        case EAknExPopFieldCmdOutline25:
            HandleCommandL( EAknExPopFieldCmdOutline26 );
            break;
        case EAknExPopFieldCmdOutline26:
            HandleCommandL( EAknExPopFieldCmdOutline27 );
            break;
        case EAknExPopFieldCmdOutline27:
            HandleCommandL( EAknExPopFieldCmdOutline28 );
            break;
        case EAknExPopFieldCmdOutline28:
            HandleCommandL( EAknExPopFieldCmdOutline30 );
            break;
        case EAknExPopFieldCmdOutline30:
            HandleCommandL( EAknExPopFieldCmdOutline31 );
            break;
        case EAknExPopFieldCmdOutline31:
            HandleCommandL( EAknExPopFieldCmdOutline32 );
            break;
        case EAknExPopFieldCmdOutline32:
            HandleCommandL( EAknExPopFieldCmdEmptyOutline );
            break;
        default:
            HandleCommandL( EAknExPopFieldCmdEmptyOutline );
            break;
        }
    }

// ----------------------------------------------------------------------------
// TUid CAknExPopFieldView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
//
TUid CAknExPopFieldView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ProcessCommandL( EAknCmdExit );
            break;
        case EAknCmdExit:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;
        case EAknExPopFieldCmdEmptyOutline:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXPOPFIELD_TEXT_LABEL_TITLE );
            break;
        case EAknExPopFieldCmdOutline01:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline02:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline03:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline04:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline05:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline06:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline07:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline08:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline09:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayOptionalTextPopFieldL(
                R_AKNEXPOPFIELD_THIRTEEN_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline10:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline11:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline12:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline13:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline14:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline15:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline16:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_FIVE_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline17:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_FIVE_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline18:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayManyLineTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline19:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline20:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_ALLOWS_USER_DEFINED_ENTRY_DIALOG );
            break;
        case EAknExPopFieldCmdOutline21:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_ALLOWS_USER_DEFINED_ENTRY_DIALOG );
            break;
        case EAknExPopFieldCmdOutline22:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_ALLOWS_USER_DEFINED_ENTRY_DIALOG );
            break;
        case EAknExPopFieldCmdOutline23:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_ALLOWS_USER_DEFINED_ENTRY_DIALOG );
            break;
        case EAknExPopFieldCmdOutline24:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_ALLOWS_USER_DEFINED_ENTRY_DIALOG );
            break;
        case EAknExPopFieldCmdOutline25:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayMultiPagePopFieldL(
                R_AKNEXPOPFIELD_DIFFERENT_DATA_TYPE_DIALOG );
            break;
        case EAknExPopFieldCmdOutline26:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayMultiPagePopFieldL(
                R_AKNEXPOPFIELD_DIFFERENT_DATA_TYPE_ENTER_DIALOG );
            break;
        case EAknExPopFieldCmdOutline27:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayMultiPagePopFieldL(
                R_AKNEXPOPFIELD_DIFFERENT_DATA_TYPE_ENTER_DIALOG );
            break;
        case EAknExPopFieldCmdOutline28:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_LIST_WITH_RADIO_BUTTON_DIALOG );
            break;
        case EAknExPopFieldCmdOutline30:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline31:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_TWO_TEXT_FIELD_DIALOG );
            break;
        case EAknExPopFieldCmdOutline32:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayMultiPagePopFieldL(
                R_AKNEXPOPFIELD_NAVIGATE_SIX_PAGES_DIALOG );
            break;
        case EAknExPopFieldCmdOutline33:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplayTextPopFieldL(
                R_AKNEXPOPFIELD_FIELD_TEXT_DIALOG );
            break;
        case EAknExPopFieldCmdOutline34:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL(
                R_AKNEXPOPFIELD_TEXT_LABEL_OPERATION );
            iContainer->DisplaySetAttribsPopFieldL(
                R_AKNEXPOPFIELD_ATTRIB_SET_DIALOG );
            break;
        case EAknExPopFieldCbaCmdNext:
            DisplayNextOutlineL();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldView::IndicateTitlePaneTextL( TInt )
// Set title text to status-pane
// ----------------------------------------------------------------------------
//
void CAknExPopFieldView::IndicateTitlePaneTextL( TInt aCommand )
    {
    TBool useDefaultText( EFalse );
    TInt resourceId( KAknExPopFieldResourceIdInitialize );
    switch ( aCommand )
        {
        case EAknExPopFieldCmdEmptyOutline:
            useDefaultText = ETrue;
            break;
        case EAknExPopFieldCmdOutline01:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE01;
            break;
        case EAknExPopFieldCmdOutline02:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE02;
            break;
        case EAknExPopFieldCmdOutline03:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE03;
            break;
        case EAknExPopFieldCmdOutline04:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE04;
            break;
        case EAknExPopFieldCmdOutline05:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE05;
            break;
        case EAknExPopFieldCmdOutline06:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE06;
            break;
        case EAknExPopFieldCmdOutline07:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE07;
            break;
        case EAknExPopFieldCmdOutline08:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE08;
            break;
        case EAknExPopFieldCmdOutline09:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE09;
            break;
        case EAknExPopFieldCmdOutline10:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE10;
            break;
        case EAknExPopFieldCmdOutline11:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE11;
            break;
        case EAknExPopFieldCmdOutline12:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE12;
            break;
        case EAknExPopFieldCmdOutline13:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE13;
            break;
        case EAknExPopFieldCmdOutline14:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE14;
            break;
        case EAknExPopFieldCmdOutline15:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE15;
            break;
        case EAknExPopFieldCmdOutline16:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE16;
            break;
        case EAknExPopFieldCmdOutline17:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE17;
            break;
        case EAknExPopFieldCmdOutline18:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE18;
            break;
        case EAknExPopFieldCmdOutline19:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE19;
            break;
        case EAknExPopFieldCmdOutline20:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE20;
            break;
        case EAknExPopFieldCmdOutline21:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE21;
            break;
        case EAknExPopFieldCmdOutline22:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE22;
            break;
        case EAknExPopFieldCmdOutline23:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE23;
            break;
        case EAknExPopFieldCmdOutline24:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE24;
            break;
        case EAknExPopFieldCmdOutline25:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE25;
            break;
        case EAknExPopFieldCmdOutline26:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE26;
            break;
        case EAknExPopFieldCmdOutline27:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE27;
            break;
        case EAknExPopFieldCmdOutline28:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE28;
            break;
        case EAknExPopFieldCmdOutline29:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE29;
            break;
        case EAknExPopFieldCmdOutline30:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE30;
            break;
        case EAknExPopFieldCmdOutline31:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE31;
            break;
        case EAknExPopFieldCmdOutline32:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE32;
            break;
        case EAknExPopFieldCmdOutline33:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE33;
            break;
        case EAknExPopFieldCmdOutline34:
            resourceId = R_AKNEXPOPFIELD_TEXT_STATUS_PANE_TITLE34;
            break;
        default:
            useDefaultText = ETrue;
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
        TBuf<KAknExPopFieldTitleBufLength> titleText( NULL );
        iEikonEnv->ReadResource( titleText, resourceId );
        titlePane->SetTextL( titleText );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldView::DoActivateL(const TVwsViewId&, TUid, const TDesC8&)
// Creates container class object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    // Creates container object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExPopFieldContainer( this );
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );
        // Adds container to view control stack.
        AppUi()->AddToStackL( *this, iContainer );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExPopFieldView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
//
void CAknExPopFieldView::DoDeactivate()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        // Removes container from view control stack.
        AppUi()->RemoveFromStack( iContainer );
        delete iContainer;
        iContainer = NULL;
        }
    }

// End of File
