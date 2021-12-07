/*
* =============================================================================
*  Name     : CAknExSettingListView
*  Part of  : AknExSettingList
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/
// INCLUDE FILES
#include <avkon.hrh>
#include <avkon.rsg>
#include <akntitle.h>
#include <aknviewappui.h>
#include <aknexsettinglist.rsg>
#include "aknexsettinglist.hrh"
#include "aknexsettinglistview.h"
#include "aknexsettinglistcontainer.h"
#include "aknexsettinglistlistbox.h"
#include "aknexsettinglistitemdata.h"

// CONSTANTS
const TUid KViewId = { 1 }; // UID of View.
const TInt KAknExSettingListTitleBufLength = 256;
const TInt KAknExSettingListInitial = 0;

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExSettingListView::CAknExSettingListView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListView::CAknExSettingListView()
//:   iContainer( NULL )
:   iCurrentOutlineId( EAknExSettingListCmdEmptyOutline )
    {
    }

// ----------------------------------------------------------------------------
// CAknExSettingListView::~CAknExSettingListView()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExSettingListView::~CAknExSettingListView()
    {
    // Deletes the Container class object.
    if ( iContainer )
        {
        // Removes Container from View control stack.
        AppUi()->RemoveFromStack( iContainer );
        }

    if (iListBox)
        {
        AppUi()->RemoveFromStack(iListBox);
        }

    //delete iContainer;
    delete iListBox;
    delete iData;
    }

// ----------------------------------------------------------------------------
// void CAknExSettingList::DisplayNextOutlineL()
// Displays the next outline.
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::DisplayNextOutlineL()
    {
    switch ( iCurrentOutlineId ) // Current outline is...
        {
        case EAknExSettingListCmdEmptyOutline:
            HandleCommandL( EAknExSettingListCmdOutline01 );
            break;
        case EAknExSettingListCmdOutline01:
            HandleCommandL( EAknExSettingListCmdOutline02 );
            break;
        case EAknExSettingListCmdOutline02:
            HandleCommandL( EAknExSettingListCmdOutline03 );
            break;
        case EAknExSettingListCmdOutline03:
            HandleCommandL( EAknExSettingListCmdOutline04 );
            break;
        case EAknExSettingListCmdOutline04:
            HandleCommandL( EAknExSettingListCmdOutline05 );
            break;
        case EAknExSettingListCmdOutline05:
            HandleCommandL( EAknExSettingListCmdOutline06 );
            break;
        case EAknExSettingListCmdOutline06:
            HandleCommandL( EAknExSettingListCmdOutline07 );
            break;
        case EAknExSettingListCmdOutline07:
            HandleCommandL( EAknExSettingListCmdOutline08 );
            break;
        case EAknExSettingListCmdOutline08:
            HandleCommandL( EAknExSettingListCmdOutline09 );
            break;
        case EAknExSettingListCmdOutline09:
            HandleCommandL( EAknExSettingListCmdOutline10 );
            break;
        case EAknExSettingListCmdOutline10:
            HandleCommandL( EAknExSettingListCmdOutline01 );
            break;
        default:
            HandleCommandL( EAknExSettingListCmdEmptyOutline );
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExSettingList::DisplayPreviousOutlineL()
// Displays the previous outline.
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::DisplayPreviousOutlineL()
    {
    switch ( iCurrentOutlineId ) // Current outline is...
        {
        case EAknExSettingListCmdEmptyOutline:
            HandleCommandL( EAknExSettingListCmdOutline10 );
            break;
        case EAknExSettingListCmdOutline01:
            HandleCommandL( EAknExSettingListCmdOutline10 );
            break;
        case EAknExSettingListCmdOutline02:
            HandleCommandL( EAknExSettingListCmdOutline01 );
            break;
        case EAknExSettingListCmdOutline03:
            HandleCommandL( EAknExSettingListCmdOutline02 );
            break;
        case EAknExSettingListCmdOutline04:
            HandleCommandL( EAknExSettingListCmdOutline03 );
            break;
        case EAknExSettingListCmdOutline05:
            HandleCommandL( EAknExSettingListCmdOutline04 );
            break;
        case EAknExSettingListCmdOutline06:
            HandleCommandL( EAknExSettingListCmdOutline05 );
            break;
        case EAknExSettingListCmdOutline07:
            HandleCommandL( EAknExSettingListCmdOutline06 );
            break;
        case EAknExSettingListCmdOutline08:
            HandleCommandL( EAknExSettingListCmdOutline07 );
            break;
        case EAknExSettingListCmdOutline09:
            HandleCommandL( EAknExSettingListCmdOutline08 );
            break;
        case EAknExSettingListCmdOutline10:
            HandleCommandL( EAknExSettingListCmdOutline09 );
            break;
        default:
            HandleCommandL( EAknExSettingListCmdEmptyOutline );
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAknExSettingListView::SetCurrentOutlineId( const TInt )
// Set iCurrentOutlineId
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::SetCurrentOutlineId( const TInt aOutlineId )
    {
    iCurrentOutlineId = aOutlineId;
    }

// ----------------------------------------------------------------------------
// TUid CAknExSettingListView::Id() const
// Returns ID of View.
// ----------------------------------------------------------------------------
//
TUid CAknExSettingListView::Id() const
    {
    return KViewId;
    }

// ----------------------------------------------------------------------------
// CAknExSettingListView::HandleCommandL( TInt )
// Handles the commands.
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand ) // Command is...
        {
        case EAknSoftkeyBack:
            {
            AppUi()->ProcessCommandL( EAknCmdExit );
            break;
            }
        case EAknExSettingListCmdEmptyOutline:
            iCurrentOutlineId = aCommand;
            SwapContainerL(ETrue);
            iContainer->SetCurrentOutlineId( aCommand );
            IndicateTitlePaneTextL( aCommand );
            iContainer->DisplayLabelL( R_AKNEXSETTINGLIST_TEXT_LABEL_TITLE );
            break;
        case EAknExSettingListCmdOutline01:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_TEXT);
            break;
        case EAknExSettingListCmdOutline02:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_SLIDER);
            break;
        case EAknExSettingListCmdOutline03:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_VOLUME);
            break;
        case EAknExSettingListCmdOutline04:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_ENUMTEXT);
            break;
        case EAknExSettingListCmdOutline05:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_DATE);
            break;
        case EAknExSettingListCmdOutline06:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_TIME);
            break;
        case EAknExSettingListCmdOutline07:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_BINARY);
            break;
        case EAknExSettingListCmdOutline08:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_PW);
            break;
        case EAknExSettingListCmdOutline09:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_PIN);
            break;
        case EAknExSettingListCmdOutline10:
            iCurrentOutlineId = aCommand;
            SwapContainerL(EFalse);
            CreateListBoxL(R_AKNEXSETTINGLIST_SETTING_LIST_SETTING_IP);
            break;
        case EAknExSetListCbaCmdNext:
            DisplayNextOutlineL();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CAknExSettingListView::CurrentOutlineId
//  Returns current outline id
// ----------------------------------------------------------------------------
//
TInt CAknExSettingListView::CurrentOutlineId()
    {
    return iCurrentOutlineId;
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListView::IndicateTitlePaneTextL( const TInt )
// Sets text on title pane by ID of resource.
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::IndicateTitlePaneTextL( const TInt aCommand )
    {
    TInt resourceId( KAknExSettingListInitial );

    // Sets ID of resource.
    switch ( aCommand ) // Command is...
        {
        case EAknExSettingListCmdOutline01:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE01;
            break;
        case EAknExSettingListCmdOutline02:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE02;
            break;
        case EAknExSettingListCmdOutline03:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE03;
            break;
        case EAknExSettingListCmdOutline04:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE04;
            break;
        case EAknExSettingListCmdOutline05:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE05;
            break;
        case EAknExSettingListCmdOutline06:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE06;
            break;
        case EAknExSettingListCmdOutline07:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE07;
            break;
        case EAknExSettingListCmdOutline08:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE08;
            break;
        case EAknExSettingListCmdOutline09:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE09;
            break;
        case EAknExSettingListCmdOutline10:
            resourceId = R_AKNEXSETTINGLIST_TEXT_STATUS_PANE_TITLE10;
            break;
        default:
            break;
        }

    CAknTitlePane* titlePane = STATIC_CAST(
        CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

    if ( resourceId )
        {
        TBuf<KAknExSettingListTitleBufLength> titleText( NULL );
        iEikonEnv->ReadResource( titleText, resourceId );
        titlePane->SetTextL( titleText ); // Sets text on title pane.
        }
    else
        {
        titlePane->SetTextToDefaultL();
        }
    }

// ----------------------------------------------------------------------------
// CAknExSettingListView::SwapContainerL
// 
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::SwapContainerL
        (TBool aActiveContainer)
    {
    if (iActiveContainer == aActiveContainer)
        {
        return;
        }

    if (aActiveContainer)
        {
        if (iListBox)
            {
            AppUi()->RemoveFromStack(iListBox);
            }
        delete iListBox;
        iListBox = NULL;

        iContainer->MakeVisible(ETrue);
        AppUi()->AddToStackL( *this, iContainer );
        }
    else
        {
        iContainer->MakeVisible(EFalse);
        AppUi()->RemoveFromStack( iContainer );
        }

    iActiveContainer = aActiveContainer;
    }

// ----------------------------------------------------------------------------
// CAknExSettingListView::CreateListBoxL
// 
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::CreateListBoxL(TInt aResourceId)
    {
    if (iListBox)
        {
        AppUi()->RemoveFromStack(iListBox);
        }
    delete iListBox;
    iListBox = NULL;

    delete iData;
    iData = CAknExSettingListItemData::NewL();

    iListBox = new (ELeave) CAknExSettingListListbox;
    iListBox->SetData(iData);
    iListBox->SetView(this);
    iListBox->SetMopParent(this);
    iListBox->ConstructFromResourceL(aResourceId);
    AppUi()->AddToStackL( *this, iListBox );
    iListBox->MakeVisible(ETrue);
    iListBox->SetRect(ClientRect());
    iListBox->ActivateL();
    iListBox->DrawNow();
    IndicateTitlePaneTextL(iCurrentOutlineId);
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListView::DoActivateL( const TVwsViewId&, TUid,
//  const TDesC8& )
// Creates the Container class object.
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::DoActivateL(
    const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/,
    const TDesC8& /*aCustomMessage*/ )
    {
    // Creates the Container class object.
    if ( !iContainer )
        {
        iContainer = new( ELeave ) CAknExSettingListContainer( this );
        iContainer->SetMopParent(this);
        iContainer->ConstructL( ClientRect() );
        iActiveContainer = ETrue;

        // Adds Container to View control stack.
        AppUi()->AddToStackL( *this, iContainer );

        // Requires to display the default screen.
        iContainer->DisplayLabelL( R_AKNEXSETTINGLIST_TEXT_LABEL_TITLE );
        iContainer->MakeVisible( ETrue );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExSettingListView::DoDeactivate()
// Deletes the Container class object.
// ----------------------------------------------------------------------------
//
void CAknExSettingListView::DoDeactivate()
    {
    // Deletes the container class object.
    if ( iContainer )
        {
        // Removes Container from View control stack.
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// End of File
