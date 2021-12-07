/*
* =============================================================================
*  Name     : CAknExListBaseView
*  Part of  : AknExList
*  Copyright (c) 2003 Nokia. All rights reserved.
* =============================================================================
*/

// INCLUDE FILES
#include <barsread.h>
#include <akntitle.h>
#include <aknnavide.h>
#include <akntabgrp.h>
#include <aknexlist.rsg>
#include "AknExList.hrh"
#include "AknExListAppUi.h"
#include "AknExListBaseView.h"
#include "AknExListColumnView.h"
#include "AknExListFormView.h"
#include "AknExListSettingView.h"
#include "AknExListMarkView.h"
#include "AknExListFlagTestView.h"

// CONSTANTS
const TInt KAknExListTitleBufLength(256); // for lenght.

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// CAknExListBaseView::CAknExListBaseView()
// Default constructor.
// ----------------------------------------------------------------------------
//
CAknExListBaseView::CAknExListBaseView()
    {
    }

// ----------------------------------------------------------------------------
// CAknExListBaseView::~CAknExListBaseView()
// Destructor.
// ----------------------------------------------------------------------------
//
CAknExListBaseView::~CAknExListBaseView()
    {
    if ( iNaviPane )
        {
        if ( iNaviPane->Top() == iDecoratedTabGroup )
            {
            iNaviPane->Pop( iDecoratedTabGroup );
            delete iDecoratedTabGroup;
            }
        }
    }

// ----------------------------------------------------------------------------
// CAknExListBaseView::TabGroup()
// Returns pointer to tab group object.
// ----------------------------------------------------------------------------
//
CAknTabGroup* CAknExListBaseView::TabGroup()
    {
    return iTabGroup;
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseView::SwitchDisplayOutlineL( const TInt )
// Switches screen by outline.
// ----------------------------------------------------------------------------
//
void CAknExListBaseView::SwitchDisplayOutlineL( const TInt aOutlineId )
    {
    TUid viewId( KAknExListColumnViewId );

    // Sets view id used next.
    switch ( aOutlineId )
        {
        // Column List
        case EAknExListCmdEmptyOutline:
        case EAknExListCmdOutline01:
        case EAknExListCmdOutline02:
        case EAknExListCmdOutline03:
        case EAknExListCmdOutline04:
        case EAknExListCmdOutline05:
        case EAknExListCmdOutline07:
        case EAknExListCmdOutline08:
        case EAknExListCmdOutline09:
        case EAknExListCmdOutline10:
        case EAknExListCmdOutline11:
        case EAknExListCmdOutline12:
        case EAknExListCmdOutline13:
        case EAknExListCmdOutline14:
        case EAknExListCmdOutline15:
        case EAknExListCmdOutline26:
        case EAknExListCmdOutline27:
        case EAknExListCmdOutline30:
        case EAknExListCmdOutline30T1:
        case EAknExListCmdOutline30T2:
        case EAknExListCmdOutline31:
        case EAknExListCmdOutline33:
        case EAknExListCmdOutline41:
        case EAknExListCmdOutline41T1:
        case EAknExListCmdOutline41T2:
        case EAknExListCmdOutline43:
        case EAknExListCmdOutline44:
        case EAknExListCmdOutline45:
        case EAknExListCmdOutline46:
        case EAknExListCmdOutline47:
        case EAknExListCmdOutline48:
        case EAknExListCmdOutline49:
        case EAknExListCmdOutline50:
        case EAknExListCmdOutline51:
        case EAknExListCmdOutline52:
        case EAknExListCmdOutline60:
        case EAknExListCmdOutline61:
        case EAknExListCmdOutline62:
        case EAknExListCmdOutline63:
        case EAknExListCmdOutline64:
        //case EAknExListCmdOutline65:
        case EAknExListCmdOutline66:
        case EAknExListCmdOutline69:
        case EAknExListCmdOutline70:
        case EAknExListCmdOutline77:
        case EAknExListCmdOutline78:
        case EAknExListCmdOutline80:
        case EAknExListCmdOutline80Sub:
            viewId = KAknExListColumnViewId;
            break;
        // Formatted List
        case EAknExListCmdOutline16:
        case EAknExListCmdOutline17:
        case EAknExListCmdOutline18:
        case EAknExListCmdOutline19:
        case EAknExListCmdOutline20:
        case EAknExListCmdOutline21:
        case EAknExListCmdOutline41T3:
        case EAknExListCmdOutline53:
        case EAknExListCmdOutline54:
        case EAknExListCmdOutline55:
        case EAknExListCmdOutline57:
        case EAknExListCmdOutline58:
        case EAknExListCmdOutline67:
        case EAknExListCmdOutline68:
        case EAknExListCmdOutline71:
            viewId = KAknExListFormViewId;
            break;
        // Setting List
        case EAknExListCmdOutline22:
        case EAknExListCmdOutline23:
        case EAknExListCmdOutline59:
        case EAknExListCmdOutline74:
        case EAknExListCmdOutline75:
        case EAknExListCmdOutline76:
        case EAknExListCmdOutline79:
            viewId = KAknExListSettingViewId;
            break;
        case EAknExListCmdOutline32:
        case EAknExListCmdOutline81:
        case EAknExListCmdOutline82:
        case EAknExListCmdOutline83:
        case EAknExListCmdOutline87:
            viewId = KAknExListMarkViewId;
            break;
        case EAknExListCmdOutline06:
        case EAknExListCmdOutline88:
        case EAknExListCmdOutline90:
        case EAknExListCmdOutline91:
        case EAknExListCmdOutline93:
        case EAknExListCmdOutline95:
        case EAknExListCmdOutline97:
        case EAknExListCmdOutline99:
        case EAknExListCmdOutline102:
            viewId = KAknExListFlagTestViewId;
            break;
        case EAknExListCmdOutline85:
            viewId = KAknExListSetPageViewId;
            break;    
        default:
            break;
        }

    SetNavigationPaneL(); // Sets navigation pane.

    if ( viewId != Id() ) // Should view be switched?
        {
        AppUi()->ActivateLocalViewL( viewId );
        }
    else
        {
        if ( iDecoratedTabGroup )
            {
            DisplayListBoxL( iTabGroup->TabIdFromIndex( iTabGroup->
                                                        ActiveTabIndex() ) );
            }
        else
            {
            SetTitlePaneL( aOutlineId );
            DisplayListBoxL( aOutlineId );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseView::DisplayNextOutlineL()
// Sets ID of feature to displayed next.
// ----------------------------------------------------------------------------
//
void CAknExListBaseView::DisplayNextOutlineL()
    {
    TInt outlineId( STATIC_CAST( CAknExListAppUi*, AppUi() )->OutlineId() );

    DeleteTabGroup(); // Deletes tab group.

    switch ( outlineId ) // Current outline is...
        {
        case EAknExListCmdEmptyOutline: // Start screen.
            // Next : OUTLINE1 screen.
            outlineId = EAknExListCmdOutline01;
            break;
        case EAknExListCmdOutline01: // OUTLINE1 screen.
            // Next : OUTLINE2 screen.
            outlineId = EAknExListCmdOutline02;
            break;
        case EAknExListCmdOutline02: // OUTLINE2 screen.
            // Next : OUTLINE3 screen.
            outlineId = EAknExListCmdOutline03;
            break;
        case EAknExListCmdOutline03: // OUTLINE3 screen.
            // Next : OUTLINE4 screen.
            outlineId = EAknExListCmdOutline04;
            break;
        case EAknExListCmdOutline04: // OUTLINE4 screen.
            // Next : OUTLINE5 screen.
            outlineId = EAknExListCmdOutline05;
            break;
        case EAknExListCmdOutline05: // OUTLINE5 screen.
            // Next : OUTLINE6 screen.
            outlineId = EAknExListCmdOutline06;
            break;
        case EAknExListCmdOutline06: // OUTLINE6 screen.
            // Next : OUTLINE7 screen.
            outlineId = EAknExListCmdOutline07;
            break;
        case EAknExListCmdOutline07: // OUTLINE7 screen.
            // Next : OUTLINE8 screen.
            outlineId = EAknExListCmdOutline08;
            break;
        case EAknExListCmdOutline08: // OUTLINE8 screen.
            // Next : OUTLINE9 screen.
            outlineId = EAknExListCmdOutline09;
            break;
        case EAknExListCmdOutline09: // OUTLINE9 screen.
            // Next : OUTLINE10 screen.
            outlineId = EAknExListCmdOutline10;
            break;
        case EAknExListCmdOutline10: // OUTLINE10 screen.
            // Next : OUTLINE11 screen.
            outlineId = EAknExListCmdOutline11;
            break;
        case EAknExListCmdOutline11: // OUTLINE11 screen.
            // Next : OUTLINE12 screen.
            outlineId = EAknExListCmdOutline12;
            break;
        case EAknExListCmdOutline12: // OUTLINE12 screen.
            // Next : OUTLINE13 screen.
            outlineId = EAknExListCmdOutline13;
            break;
        case EAknExListCmdOutline13: // OUTLINE13 screen.
            // Next : OUTLINE14 screen.
            outlineId = EAknExListCmdOutline14;
            break;
        case EAknExListCmdOutline14: // OUTLINE14 screen.
            // Next : OUTLINE15 screen.
            outlineId = EAknExListCmdOutline15;
            break;
        case EAknExListCmdOutline15: // OUTLINE15 screen.
            // Next : OUTLINE16 screen.
            outlineId = EAknExListCmdOutline16;
            break;
        case EAknExListCmdOutline16: // OUTLINE16 screen.
            // Next : OUTLINE17 screen.
            outlineId = EAknExListCmdOutline17;
            break;
        case EAknExListCmdOutline17: // OUTLINE17 screen.
            // Next : OUTLINE18 screen.
            outlineId = EAknExListCmdOutline18;
            break;
        case EAknExListCmdOutline18: // OUTLINE18 screen.
            // Next : OUTLINE19 screen.
            outlineId = EAknExListCmdOutline19;
            break;
        case EAknExListCmdOutline19: // OUTLINE19 screen.
            // Next : OUTLINE20 screen.
            outlineId = EAknExListCmdOutline20;
            break;
        case EAknExListCmdOutline20: // OUTLINE20 screen.
            // Next : OUTLINE21 screen.
            outlineId = EAknExListCmdOutline21;
            break;
        case EAknExListCmdOutline21: // OUTLINE21 screen.
            // Next : OUTLINE22 screen.
            outlineId = EAknExListCmdOutline22;
            break;
        case EAknExListCmdOutline22: // OUTLINE22 screen.
            // Next : OUTLINE23 screen.
            outlineId = EAknExListCmdOutline23;
            break;
        case EAknExListCmdOutline23: // OUTLINE23 screen.
            // Next : OUTLINE26 screen.
            outlineId = EAknExListCmdOutline26; // tentative
            break;
        case EAknExListCmdOutline26: // OUTLINE26 screen.
            // Next : OUTLINE27 screen.
            outlineId = EAknExListCmdOutline27;
            break;
        case EAknExListCmdOutline27: // OUTLINE27 screen.
            // Next : OUTLINE30 screen.
            outlineId = EAknExListCmdOutline30;
            break;
        case EAknExListCmdOutline30: // OUTLINE30 screen.
            // Next : OUTLINE31 screen.
            outlineId = EAknExListCmdOutline31;
            //outlineId = EAknExListCmdOutline32; // tentative
            break;
        case EAknExListCmdOutline31: // OUTLINE31 screen.
            // Next : OUTLINE32 screen.
            outlineId = EAknExListCmdOutline32;
            break;
        case EAknExListCmdOutline32: // OUTLINE32 screen.
            // Next : OUTLINE33 screen.
            outlineId = EAknExListCmdOutline33;
            break;
        case EAknExListCmdOutline33: // OUTLINE33 screen.
            // Next : OUTLINE41 screen.
            outlineId = EAknExListCmdOutline41;
            break;
        case EAknExListCmdOutline41: // OUTLINE41 screen.
            // Next : OUTLINE43 screen.
            outlineId = EAknExListCmdOutline43;
            break;
        case EAknExListCmdOutline43: // OUTLINE43 screen.
            // Next : OUTLINE44 screen.
            outlineId = EAknExListCmdOutline44;
            break;
        case EAknExListCmdOutline44: // OUTLINE44 screen.
            // Next : OUTLINE45 screen.
            outlineId = EAknExListCmdOutline45;
            break;
        case EAknExListCmdOutline45: // OUTLINE45 screen.
            // Next : OUTLINE46 screen.
            outlineId = EAknExListCmdOutline46;
            break;
        case EAknExListCmdOutline46: // OUTLINE46 screen.
            // Next : OUTLINE47 screen.
            outlineId = EAknExListCmdOutline47;
            break;
        case EAknExListCmdOutline47: // OUTLINE47 screen.
            // Next : OUTLINE48 screen.
            outlineId = EAknExListCmdOutline48;
            break;
        case EAknExListCmdOutline48: // OUTLINE48 screen.
            // Next : OUTLINE49 screen.
            outlineId = EAknExListCmdOutline49;
            break;
        case EAknExListCmdOutline49: // OUTLINE49 screen.
            // Next : OUTLINE50 screen.
            outlineId = EAknExListCmdOutline50;
            break;
        case EAknExListCmdOutline50: // OUTLINE50 screen.
            // Next : OUTLINE51 screen.
            outlineId = EAknExListCmdOutline51;
            break;
        case EAknExListCmdOutline51: // OUTLINE51 screen.
            // Next : OUTLINE52 screen.
            outlineId = EAknExListCmdOutline52;
            break;
        case EAknExListCmdOutline52: // OUTLINE52 screen.
            // Next : OUTLINE53 screen.
            outlineId = EAknExListCmdOutline53;
            break;
        case EAknExListCmdOutline53: // OUTLINE53 screen.
            // Next : OUTLINE54 screen.
            outlineId = EAknExListCmdOutline54;
            break;
        case EAknExListCmdOutline54: // OUTLINE54 screen.
            // Next : OUTLINE55 screen.
            outlineId = EAknExListCmdOutline55;
            break;
        case EAknExListCmdOutline55: // OUTLINE55 screen.
            // Next : OUTLINE57 screen.
            outlineId = EAknExListCmdOutline57;
            break;
        case EAknExListCmdOutline57: // OUTLINE57 screen.
            // Next : OUTLINE58 screen.
            outlineId = EAknExListCmdOutline58;
            break;
        case EAknExListCmdOutline58: // OUTLINE58 screen.
            // Next : OUTLINE59 screen.
            outlineId = EAknExListCmdOutline59;
            break;
        case EAknExListCmdOutline59: // OUTLINE59 screen.
            // Next : OUTLINE60 screen.
            outlineId = EAknExListCmdOutline60;
            break;
        case EAknExListCmdOutline60: // OUTLINE60 screen.
            // Next : OUTLINE61 screen.
            outlineId = EAknExListCmdOutline61;
            break;
        case EAknExListCmdOutline61: // OUTLINE61 screen.
            // Next : OUTLINE62 screen.
            outlineId = EAknExListCmdOutline62;
            break;
        case EAknExListCmdOutline62: // OUTLINE62 screen.
            // Next : OUTLINE63 screen.
            outlineId = EAknExListCmdOutline63;
            break;
        case EAknExListCmdOutline63: // OUTLINE63 screen.
            // Next : OUTLINE64 screen.
            outlineId = EAknExListCmdOutline64;
            break;
        case EAknExListCmdOutline64: // OUTLINE64 screen.
            // Next : OUTLINE66 screen.
            outlineId = EAknExListCmdOutline66;
            break;
        case EAknExListCmdOutline66: // OUTLINE66 screen.
            // Next : OUTLINE67 screen.
            outlineId = EAknExListCmdOutline67;
            break;
        case EAknExListCmdOutline67: // OUTLINE67 screen.
            // Next : OUTLINE68 screen.
            outlineId = EAknExListCmdOutline68;
            break;
        case EAknExListCmdOutline68: // OUTLINE68 screen.
            // Next : OUTLINE69 screen.
            outlineId = EAknExListCmdOutline69;
            break;
        case EAknExListCmdOutline69: // OUTLINE69 screen.
            // Next : OUTLINE70 screen.
            outlineId = EAknExListCmdOutline70;
            break;
        case EAknExListCmdOutline70: // OUTLINE70 screen.
            // Next : OUTLINE71 screen.
            outlineId = EAknExListCmdOutline71;
            break;
        case EAknExListCmdOutline71: // OUTLINE71 screen.
            // Next : OUTLINE74 screen.
            outlineId = EAknExListCmdOutline74;
            break;
        case EAknExListCmdOutline74: // OUTLINE74 screen.
            // Next : OUTLINE75 screen.
            outlineId = EAknExListCmdOutline75;
            break;
        case EAknExListCmdOutline75: // OUTLINE75 screen.
            // Next : OUTLINE76 screen.
            outlineId = EAknExListCmdOutline76;
            break;
        case EAknExListCmdOutline76: // OUTLINE76 screen.
            // Next : OUTLINE77.
            outlineId = EAknExListCmdOutline77;
            break;
        case EAknExListCmdOutline77: // OUTLINE77 screen.
            // Next : OUTLINE78 screen.
            outlineId = EAknExListCmdOutline78;
            break;
        case EAknExListCmdOutline78: // OUTLINE78 screen.
            // Next : OUTLINE79 screen.
            outlineId = EAknExListCmdOutline79;
            break;
        case EAknExListCmdOutline79: // OUTLINE79 screen.
            // Next : OUTLINE80 screen.
            outlineId = EAknExListCmdOutline80;
            break;
        case EAknExListCmdOutline80: // OUTLINE80 screen.
            // Next : OUTLINE81 screen.
            outlineId = EAknExListCmdOutline81;
            break;
        case EAknExListCmdOutline81: // OUTLINE81 screen.
            // Next : OUTLINE82 screen.
            outlineId = EAknExListCmdOutline82;
            break;
        case EAknExListCmdOutline82: // OUTLINE82 screen.
            // Next : OUTLINE83 screen.
            outlineId = EAknExListCmdOutline83;
            break;
        case EAknExListCmdOutline83: // OUTLINE83 screen.
            // Next : OUTLINE83 screen.
            outlineId = EAknExListCmdOutline85;
            break;
        case EAknExListCmdOutline85: // OUTLINE85 screen.
            // Next : OUTLINE83 screen.
            outlineId = EAknExListCmdOutline87;
            break;
        case EAknExListCmdOutline87: // OUTLINE87 screen.
            // Next : OUTLINE88 screen.
            outlineId = EAknExListCmdOutline88;
            break;
        case EAknExListCmdOutline88: // OUTLINE88 screen.
            // Next : OUTLINE90 screen.
            outlineId = EAknExListCmdOutline90;
            break;
        case EAknExListCmdOutline89: // OUTLINE89 screen.
            // Next : OUTLINE90 screen.
            outlineId = EAknExListCmdOutline90;
            break;
        case EAknExListCmdOutline90: // OUTLINE90 screen.
            // Next : OUTLINE91 screen.
            outlineId = EAknExListCmdOutline91;
            break;
        case EAknExListCmdOutline91: // OUTLINE91 screen.
            // Next : OUTLINE93 screen.
            outlineId = EAknExListCmdOutline93;
            break;
        case EAknExListCmdOutline92: // OUTLINE92 screen.
            // Next : OUTLINE93 screen.
            outlineId = EAknExListCmdOutline93;
            break;
        case EAknExListCmdOutline93: // OUTLINE93 screen.
            // Next : OUTLINE95 screen.
            outlineId = EAknExListCmdOutline95;
            break;
        case EAknExListCmdOutline94: // OUTLINE94 screen.
            // Next : OUTLINE95 screen.
            outlineId = EAknExListCmdOutline95;
            break;
        case EAknExListCmdOutline95: // OUTLINE95 screen.
            // Next : OUTLINE97 screen.
            outlineId = EAknExListCmdOutline97;
            break;
        case EAknExListCmdOutline96: // OUTLINE96 screen.
            // Next : OUTLINE97 screen.
            outlineId = EAknExListCmdOutline97;
            break;
        case EAknExListCmdOutline97: // OUTLINE97 screen.
            // Next : OUTLINE99 screen.
            outlineId = EAknExListCmdOutline99;
            break;
        case EAknExListCmdOutline98: // OUTLINE98 screen.
            // Next : OUTLINE99 screen.
            outlineId = EAknExListCmdOutline99;
            break;
        case EAknExListCmdOutline99: // OUTLINE99 screen.
            // Next : OUTLINE102 screen.
            outlineId = EAknExListCmdOutline102;
            break;
        case EAknExListCmdOutline102: // OUTLINE102 screen.
            outlineId = EAknExListCmdEmptyOutline;
            break;
        default:
            // Ecepstion : OUTLINE1 screen.
            outlineId = EAknExListCmdOutline01;
            break;
        }

    HandleCommandL( outlineId );
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseView::IndicateTitlePaneTextL
// Sets text to titie pane.
// This is for outline 100, 101, 103, 104.
// ----------------------------------------------------------------------------
void CAknExListBaseView::IndicateTitlePaneTextL( const TDesC& aTitle )
    {
    // Fetches pointer to the default title pane control.
    CAknTitlePane* titlePane = STATIC_CAST(
        CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

    titlePane->SetTextL( aTitle );
    }


// ----------------------------------------------------------------------------
// void CAknExListBaseView::HandleCommandL( TInt )
// Handles the commands. If the command is command which is require to display
// outline-screen, the command display outline-screen corresponded to required.
// ----------------------------------------------------------------------------
void CAknExListBaseView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand ) // Command is...
        {
        case EAknSoftkeyBack:
            AppUi()->ProcessCommandL( EEikCmdExit /*EAknCmdExit*/);
            break;
        //case EEikCmdExit:
        case EAknCmdExit:
            AppUi()->ProcessCommandL( EEikCmdExit /*EAknCmdExit*/ );
            break;
        case EAknExListSoftkeyNextOutline:
            DisplayNextOutlineL();
            break;
        default:
            DeleteTabGroup(); // Deletes tab group.
            STATIC_CAST( CAknExListAppUi*, AppUi() )->SetOutlineId( aCommand );
            SwitchDisplayOutlineL( aCommand );
            break;
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseView::IndicateTitlePaneTextL( const TInt )
// Sets text by resource ID in title pane.
// ----------------------------------------------------------------------------
//
void CAknExListBaseView::IndicateTitlePaneTextL( const TInt aResourceId )
    {
    // Fetches pointer to the default title pane control.
    CAknTitlePane* titlePane = STATIC_CAST(
        CAknTitlePane*,
        StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );

    // Makes and sets text which is used title pane.
    if ( aResourceId == KAknExListInitTitleId )
        {
        titlePane->SetTextToDefaultL();
        }
    else
        {
        TBuf<KAknExListTitleBufLength> titleText( 0 );
        iCoeEnv->ReadResource( titleText, aResourceId );
        titlePane->SetTextL( titleText );
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseView::DisplayInitOutlineL()
// Displays initial outline when view changed.
// ----------------------------------------------------------------------------
//
void CAknExListBaseView::DisplayInitOutlineL()
    {
    TInt outlineId( STATIC_CAST( CAknExListAppUi*, AppUi() )->OutlineId() );

    if ( !iNaviPane )
        {
        iNaviPane = STATIC_CAST(
            CAknNavigationControlContainer*,
            StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
        }

    iDecoratedTabGroup = iNaviPane->Top();

    if ( iDecoratedTabGroup )
        {
        iTabGroup = STATIC_CAST(
            CAknTabGroup*, iDecoratedTabGroup->DecoratedControl() );
        if ( !iTabGroup->ActiveTabIndex() ) // Is active tab first tab?
            {
            SetTitlePaneL( outlineId );
            }
        DisplayListBoxL( iTabGroup->TabIdFromIndex( iTabGroup->
                                                    ActiveTabIndex() ) );
        }
    else
        {
        if ( iTabGroup )
            {
            iTabGroup = NULL;
            }
        SetTitlePaneL( outlineId );
        DisplayListBoxL( outlineId );
        }
    }

// ------------------------------------------------------------------------------
// CAknExListBaseView::SetNavigationPaneL()
// Sets Navigation pane.
// ------------------------------------------------------------------------------
//
void CAknExListBaseView::SetNavigationPaneL()
    {
    if ( !iNaviPane )
        {
        iNaviPane = STATIC_CAST(
            CAknNavigationControlContainer*,
            StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
        }

    TInt outlineId( STATIC_CAST( CAknExListAppUi*, AppUi() )->OutlineId() );

    TInt resourceId(0);

    switch ( outlineId )
        {
        case EAknExListCmdOutline26:
            resourceId = R_AKNEXLIST_SELECTION_TAB;
            break;
        case EAknExListCmdOutline30:
            resourceId = R_AKNEXLIST_MULTISELECTION_TAB;
            break;
        case EAknExListCmdOutline41:
            resourceId = R_AKNEXLIST_STYLE_OF_FINDBOX_TAB;
            break;
        case EAknExListCmdOutline06:
        case EAknExListCmdOutline88:
        case EAknExListCmdOutline90:
        case EAknExListCmdOutline91:
        case EAknExListCmdOutline93:
        case EAknExListCmdOutline95:
        case EAknExListCmdOutline97:
        case EAknExListCmdOutline99:
        case EAknExListCmdOutline102:
            resourceId = R_AKNEXLIST_FLAGTEST_TAB;
            break;
        case EAknExListCmdOutline89:
        case EAknExListCmdOutline92:
        case EAknExListCmdOutline94:
        case EAknExListCmdOutline96:
        case EAknExListCmdOutline98:
            resourceId = R_AKNEXLIST_FLAGTEST_WITHS_TAB;
            break;
        default:
            break;
        }

    if ( resourceId )
        {
        if ( !iDecoratedTabGroup ) // Isn't tab group created?
            {
            SetTitlePaneL( outlineId );

            TResourceReader reader;
            iCoeEnv->CreateResourceReaderLC( reader, resourceId );
            iDecoratedTabGroup = iNaviPane->CreateTabGroupL( reader );
            CleanupStack::PopAndDestroy();  // resource reader

            iTabGroup = STATIC_CAST( CAknTabGroup*,
                                     iDecoratedTabGroup->DecoratedControl() );

            iNaviPane->PushL( *iDecoratedTabGroup );
            }
        }
    }

// ----------------------------------------------------------------------------
// void CAknExListBaseView::SetTitlePaneL( TInt )
// Sets text of title pane by outline ID.
// ----------------------------------------------------------------------------
void CAknExListBaseView::SetTitlePaneL( TInt /*aOutlineId*/ )
    {
    IndicateTitlePaneTextL( KAknExListInitTitleId );
    }

// ----------------------------------------------------------------------------
// CAknExListBaseView::DeleteTabGroup()
// Deletes tab group.
// ----------------------------------------------------------------------------
//
void CAknExListBaseView::DeleteTabGroup()
    {
    if ( iNaviPane )
        {
        if ( iDecoratedTabGroup )
            {
            iNaviPane->Pop( iDecoratedTabGroup );
            delete iDecoratedTabGroup;
            iDecoratedTabGroup = NULL;
            iTabGroup = NULL;
            }
        }
    }

// End of File
