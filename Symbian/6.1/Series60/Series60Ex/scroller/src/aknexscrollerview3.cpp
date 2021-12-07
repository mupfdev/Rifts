/*
* ============================================================================
*  Name     : CAknExScrollerView3 from CAknView
*  Part of  : AknExScroller
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include  <AknViewAppUi.h>
#include  <EikMenub.h>
#include  <Avkon.hrh>
#include  <Avkon.rsg>
#include  <AknExScroller.rsg>
#include  "AknExScroller.hrh"
#include  "AknExScrollerView3.h"
#include  "AknExScrollerContainer3.h"


// ================= MEMBER FUNCTIONS =======================
// C++ default constructor can NOT contain any code, that
// might leave.
//

// ---------------------------------------------------------
// CAknExScrollerView3Form::NewL
// 
// ---------------------------------------------------------
//
CAknExScrollerView3Form* CAknExScrollerView3Form::NewL()
    {
    CAknExScrollerView3Form* self = 
        new (ELeave) CAknExScrollerView3Form();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::~CAknExScrollerView3Form
// 
// ---------------------------------------------------------
//
CAknExScrollerView3Form::~CAknExScrollerView3Form()
    {
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::CAknExScrollerView3Form
// 
// ---------------------------------------------------------
//
CAknExScrollerView3Form::CAknExScrollerView3Form()
    {
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::ConstructL
// 
// ---------------------------------------------------------
//
void CAknExScrollerView3Form::ConstructL()
    {
    CAknForm::ConstructL();
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::SetFormData
// 
// ---------------------------------------------------------
//
void CAknExScrollerView3Form::SetFormData()
    {
    if (ControlOrNull(EAknExScrollerDlgLineEdwin0))
        GetEdwinText(iEdwinData1, EAknExScrollerDlgLineEdwin0);
    if (ControlOrNull(EAknExScrollerDlgLineNumberEd))
        iNumberData = NumberEditorValue(EAknExScrollerDlgLineNumberEd);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin2))
        GetEdwinText(iEdwinData2, EAknExScrollerDlgLineEdwin2);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin3))
        GetEdwinText(iEdwinData3, EAknExScrollerDlgLineEdwin3);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin4))
        GetEdwinText(iEdwinData4, EAknExScrollerDlgLineEdwin4);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin5))
        GetEdwinText(iEdwinData5, EAknExScrollerDlgLineEdwin5);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin6))
        GetEdwinText(iEdwinData6, EAknExScrollerDlgLineEdwin6);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin7))
        GetEdwinText(iEdwinData7, EAknExScrollerDlgLineEdwin7);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin8))
        GetEdwinText(iEdwinData8, EAknExScrollerDlgLineEdwin8);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin9))
        GetEdwinText(iEdwinData9, EAknExScrollerDlgLineEdwin9);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin10))
        GetEdwinText(iEdwinData10, EAknExScrollerDlgLineEdwin10);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin11))
        GetEdwinText(iEdwinData11, EAknExScrollerDlgLineEdwin11);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin12))
        GetEdwinText(iEdwinData12, EAknExScrollerDlgLineEdwin12);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin13))
        GetEdwinText(iEdwinData13, EAknExScrollerDlgLineEdwin13);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin14))
        GetEdwinText(iEdwinData14, EAknExScrollerDlgLineEdwin14);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin15))
        GetEdwinText(iEdwinData15, EAknExScrollerDlgLineEdwin15);
    if (ControlOrNull(EAknExScrollerDlgLineEdwin16))
        GetEdwinText(iEdwinData16, EAknExScrollerDlgLineEdwin16);
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::PostLayoutDynInitL
// 
// ---------------------------------------------------------
//
void CAknExScrollerView3Form::PostLayoutDynInitL()
    {
    CAknForm::PostLayoutDynInitL();
    SetFormData();
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::QuerySaveChangesL
// 
// ---------------------------------------------------------
//
TBool CAknExScrollerView3Form::QuerySaveChangesL()
    {
    TBool isAnsYes(CAknForm::QuerySaveChangesL());

    if (isAnsYes)
        {
        SetFormData();
        }
    else 
        {
        // Case that answer "No" to query.
        if (ControlOrNull(EAknExScrollerDlgLineEdwin0))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin0, &iEdwinData1);
        if (ControlOrNull(EAknExScrollerDlgLineNumberEd))
            SetNumberEditorValue(EAknExScrollerDlgLineNumberEd, iNumberData);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin2))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin2, &iEdwinData2);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin3))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin3, &iEdwinData3);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin4))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin4, &iEdwinData4);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin5))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin5, &iEdwinData5);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin6))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin6, &iEdwinData6);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin7))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin7, &iEdwinData7);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin8))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin8, &iEdwinData8);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin9))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin9, &iEdwinData9);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin10))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin10, &iEdwinData10);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin11))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin11, &iEdwinData11);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin12))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin12, &iEdwinData12);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin13))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin13, &iEdwinData13);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin14))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin14, &iEdwinData14);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin15))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin15, &iEdwinData15);
        if (ControlOrNull(EAknExScrollerDlgLineEdwin16))
            SetEdwinTextL(EAknExScrollerDlgLineEdwin16, &iEdwinData16);
        }

    return isAnsYes;
    }

// ---------------------------------------------------------
// CAknExScrollerView3Form::DynInitMenuPaneL
// 
// ---------------------------------------------------------
//
void CAknExScrollerView3Form::DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane )
    {
    CAknForm::DynInitMenuPaneL(aResourceId, aMenuPane);

    if (aResourceId == R_AVKON_FORM_MENUPANE)
        {
        aMenuPane->SetItemDimmed(EAknFormCmdAdd,ETrue);
        aMenuPane->SetItemDimmed(EAknFormCmdLabel,ETrue);
        }
    }

// ---------------------------------------------------------
// CAknExScrollerView3
// 
// ---------------------------------------------------------
CAknExScrollerView3::CAknExScrollerView3()
    {
    }

// ---------------------------------------------------------
// CAknExScrollerView3::ConstructL()
// EPOC two-phased constructor
// ---------------------------------------------------------
//
void CAknExScrollerView3::ConstructL()
    {
    BaseConstructL( R_AKNEXSCROLLER_VIEW3 );
    }


// Destructor
CAknExScrollerView3::~CAknExScrollerView3()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }

    delete iContainer;
    iContainer = NULL;
    }

// ---------------------------------------------------------
// TUid CAknExScrollerView3::Id()
// returns View id
// ---------------------------------------------------------
//
TUid CAknExScrollerView3::Id() const
    {
    return KViewId3;
    }

// ---------------------------------------------------------
// CAknExScrollerView3::HandleCommandL( TInt aCommand )
// handles the commands
// ---------------------------------------------------------
//
void CAknExScrollerView3::HandleCommandL( TInt aCommand )
    {   
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->HandleCommandL( EAknCmdExit );
            break;

        // Chosen Form in Menu Pane
        case EAknExScrollerForm:
            iForm = CAknExScrollerView3Form::NewL();
            iForm->ExecuteLD( R_AKNEXSCROLLER_DIALOG );
            break;

        case EAknExScrollerCBACommnadNext:
            AppUi()->HandleCommandL( EAknExScrollerView4 );
            break;

       default:
            AppUi()->HandleCommandL( aCommand );
            break;
        }
    }


// ---------------------------------------------------------
// CAknExScrollerView3::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
//
void CAknExScrollerView3::DoActivateL(
                         const TVwsViewId& /*aPrevViewId*/,
                         TUid /*aCustomMessageId*/,
                         const TDesC8& /*aCustomMessage*/ )
    {
    iContainer = new ( ELeave ) CAknExScrollerContainer3();
    iContainer->SetMopParent(this);
    iContainer->ConstructL( ClientRect() );
    AppUi()->AddToStackL( *this, iContainer );
    }

// ---------------------------------------------------------
// CAknExScrollerView3::DoDeactivate()
// Deletes the Container class object
// ---------------------------------------------------------
//
void CAknExScrollerView3::DoDeactivate()
    {
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File
