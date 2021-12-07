/*
* ============================================================================
*  Name     : CAknExFormView
*  Part of  : AknExForm
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <avkon.hrh>
#include <akntitle.h>
#include <aknviewappui.h>
#include <aknexform.rsg>

#include <eikmfne.h>
#include <eikedwin.h>
#include <eikcapc.h>

#include "AknExForm.hrh"
#include "AknExFormView.h"
#include "AknExFormContainer.h"

// CONSTANTS
const TUid KViewId = { 1 }; // UID of view
const TInt KAknExFormTitleBufLength = 256;
const TInt KAknExFormResourceIdInitialize = 0;
const TInt KAknExFormLabelBufLength = 256;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExFormView::CAknExFormView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExFormView::CAknExFormView()
:   iContainer( NULL ),
    iCurrentOutline( EAknExFormCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// void CAknExFormView::ConstructL()
// EPOC constructor.
// ----------------------------------------------------------------------------
//
void CAknExFormView::ConstructL()
    {
    BaseConstructL( R_AKNEXFORM_VIEW );
    }

// ----------------------------------------------------------------------------
// CAknExFormView::~CAknExFormView()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExFormView::~CAknExFormView()
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
// void CAknExFormView::DisplayNextOutlineL()
//
// ----------------------------------------------------------------------------
//
void CAknExFormView::DisplayNextOutlineL()
    {
    switch ( iCurrentOutline )
        {
        case EAknExFormCmdEmptyOutline:
            HandleCommandL( EAknExFormCmdOutline02 );
            break;
        case EAknExFormCmdOutline02:
            HandleCommandL( EAknExFormCmdOutline14 );
            break;
        case EAknExFormCmdOutline14:
            HandleCommandL( EAknExFormCmdOutline16 );
            break;
        case EAknExFormCmdOutline16:
            HandleCommandL( EAknExFormCmdOutline22 );
            break;
        case EAknExFormCmdOutline22:
            HandleCommandL( EAknExFormCmdOutline25 );
            break;
        case EAknExFormCmdOutline25:
            HandleCommandL( EAknExFormCmdOutline29 );
            break;
        case EAknExFormCmdOutline29:
            HandleCommandL( EAknExFormCmdOutline31 );
            break;
        case EAknExFormCmdOutline31:
            HandleCommandL( EAknExFormCmdOutline52 );
            break;
        case EAknExFormCmdOutline52:
            HandleCommandL( EAknExFormCmdOutline54 );
            break;
        case EAknExFormCmdOutline54:
            HandleCommandL( EAknExFormCmdOutline55 );
            break;
        case EAknExFormCmdOutline55:
            HandleCommandL( EAknExFormCmdOutline57 );
            break;
        case EAknExFormCmdOutline57:
            HandleCommandL( EAknExFormCmdOutline68 );
            break;
        case EAknExFormCmdOutline68:
            HandleCommandL( EAknExFormCmdOutline70 );
            break;
        case EAknExFormCmdOutline70:
            HandleCommandL( EAknExFormCmdOutline83 );
            break;
        case EAknExFormCmdOutline83:
            HandleCommandL( EAknExFormCmdOutline102 );
            break;
        case EAknExFormCmdOutline102:
            HandleCommandL( EAknExFormCmdEmptyOutline );
            break;
        default:
            HandleCommandL( EAknExFormCmdEmptyOutline );
            break;
        }
    }

// ----------------------------------------------------------------------------
// TUid CAknExFormView::Id()
// Returns ID of view.
// ----------------------------------------------------------------------------
//
TUid CAknExFormView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// void CAknExFormView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExFormView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        /* case EAknSoftkeyBack and EAknCmdExit
          are handled by the AppUi class.*/
        case EAknExFormCmdEmptyOutline:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_TITLE );
            break;
        case EAknExFormCmdOutline02:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_TEXT_NUMBER_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline14:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_MANY_ROW_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline16:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_NAVIPANE_DIALOG );
            break;
        case EAknExFormCmdOutline22:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL(
                R_AKNEXFORM_TEXT_NUMBER_WITH_ICON_DIALOG );
            break;
        case EAknExFormCmdOutline25:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_TEXT_NUMBER_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline29:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_ALL_EDITOR_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline31:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_TEXT_NUMBER_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline52:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_SEPARATOR_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline54:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_NONE_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline55:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            ///iContainer->DisplayFormL( R_AKNEXFORM_TEXT_FIELD_DIALOG );
            {
            CAknExFormAdd* form = new( ELeave ) CAknExFormAdd;
            CleanupStack::PushL(form);
            form->ConstructL();
            CleanupStack::Pop();
            form->ExecuteLD(R_AKNEXFORM_TEXT_FIELD_DIALOG);
            }
            break;
        case EAknExFormCmdOutline57:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_TEXT_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline68:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_THREE_SLIDER_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline70:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_NAVIGATE_SIX_PAGES_DIALOG );
            break;
        case EAknExFormCmdOutline83:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_TEXT_NUMBER_FIELD_DIALOG );
            break;
        case EAknExFormCmdOutline102:
            iCurrentOutline = aCommand;
            IndicateTitlePaneTextL( aCommand );
            iContainer->SetTextToLabelL( R_AKNEXFORM_TEXT_LABEL_OPERATION );
            iContainer->DisplayFormL( R_AKNEXFORM_DOUBLE_AND_SINGLE_LINE_FORM );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExFormView::IndicateTitlePaneTextL( TInt )
// Set title text to status-pane
// ----------------------------------------------------------------------------
//
void CAknExFormView::IndicateTitlePaneTextL( TInt aCommand )
    {
    TBool useDefaultText( EFalse );
    TInt resourceId( KAknExFormResourceIdInitialize );
    switch ( aCommand )
        {
        case EAknExFormCmdEmptyOutline:
            useDefaultText = ETrue;
            break;
        case EAknExFormCmdOutline02:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE02;
            break;
        case EAknExFormCmdOutline14:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE14;
            break;
        case EAknExFormCmdOutline16:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE16;
            break;
        case EAknExFormCmdOutline22:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE22;
            break;
        case EAknExFormCmdOutline25:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE25;
            break;
        case EAknExFormCmdOutline29:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE29;
            break;
        case EAknExFormCmdOutline31:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE31;
            break;
        case EAknExFormCmdOutline52:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE52;
            break;
        case EAknExFormCmdOutline54:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE54;
            break;
        case EAknExFormCmdOutline55:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE55;
            break;
        case EAknExFormCmdOutline57:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE57;
            break;
        case EAknExFormCmdOutline68:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE68;
            break;
        case EAknExFormCmdOutline70:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE70;
            break;
        case EAknExFormCmdOutline83:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE83;
            break;
        case EAknExFormCmdOutline102:
            resourceId = R_AKNEXFORM_TEXT_STATUS_PANE_TITLE102;
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
        TBuf<KAknExFormTitleBufLength> titleText( NULL );
        iEikonEnv->ReadResource( titleText, resourceId );
        titlePane->SetTextL( titleText );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExFormView::DoActivateL( const TVwsViewId&, TUid, const TDesC8& )
// Creates container class object.
// ----------------------------------------------------------------------------
//
void CAknExFormView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    // Creates container object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExFormContainer( this );
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );
        // Adds container to view control stack.
        AppUi()->AddToStackL( *this, iContainer );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExFormView::DoDeactivate()
// Deletes container class object.
// ----------------------------------------------------------------------------
//
void CAknExFormView::DoDeactivate()
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

// ----------------------------------------------------------------------------
// CAknExFormAdd::CAknExFormAdd()
// C++ default constructor can NOT contain any code, that
// might leave.
// ----------------------------------------------------------------------------
//
CAknExFormAdd::CAknExFormAdd()
    {
    iNewItemId = EAknExFormDlgCtrlIdEdwin02 + 1;
    }
        
// ----------------------------------------------------------------------------
// CAknExFormAdd::~CAknExFormAdd()
// Destructor
// ----------------------------------------------------------------------------
//
CAknExFormAdd::~CAknExFormAdd()
    {
    }

// ----------------------------------------------------------------------------
// void CAknExFormAdd::AddItemL()
// Add item for testing uses customised dialog.
// ----------------------------------------------------------------------------
//
void CAknExFormAdd::AddItemL()
    {
    // Add Edwin control
    TBuf<KAknExFormLabelBufLength> caption( NULL );
    iCoeEnv->ReadResource( caption, R_AKNEXFORM_LABEL_ADD_EDWIN );
    //TInt myId = EAknExFormDlgCtrlIdEdwin02 + 1;
    
    CCoeControl* myEdControl = CreateLineByTypeL(caption, ActivePageId(),
        iNewItemId /*myId*/ , EEikCtEdwin, NULL) ;

    CEikEdwin* myEdwin = STATIC_CAST(CEikEdwin*, myEdControl) ;
    myEdwin->ConstructL(EEikEdwinNoHorizScrolling | EEikEdwinResizable, 10,
        64, 10);
    myEdwin->CreateTextViewL();
    Line(iNewItemId /*myId*/)->ActivateL();

    SetEditableL(IsEditable()) ;
    DrawNow() ;
    // In order to prevent adding controls which ID is the same,
    // Id of next adding control is different from the others.
    iNewItemId++;
    }


// End of File

