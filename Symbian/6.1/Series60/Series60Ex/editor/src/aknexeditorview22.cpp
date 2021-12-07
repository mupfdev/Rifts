/*
* ============================================================================
*  Name     : CAknExEditorView22 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView22.h"
#include "AknExEditorContainer22.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView22::CAknExEditorView22()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView22::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW22);
    }

// Destructor
CAknExEditorView22::~CAknExEditorView22()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView22::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView22::Id() const
    {
    return KViewId22;
    }

// ---------------------------------------------------------
// CAknExEditorView22::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView22::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdSelectDateEditor:
        case EAknExEditorCmdSelectTimeEditor:
        case EAknExEditorCmdSelectDurationEditor:
        case EAknExEditorCmdSelectTimeAndDateEditor:

            iContainer->FocusTo(aCommand);
            break;

        case EAknExEditorCmdShowForm:
            iContainer->ShowFormL();
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorView22::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView22::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView22::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView22::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                     TUid /*aCustomMessageId*/,
                                     const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer22;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView22::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView22::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// ---------------------------------------------------------
// CAknExEditorView22::ProcessCommandL(TInt aCommand)
// 
// ---------------------------------------------------------
void CAknExEditorView22::ProcessCommandL(TInt aCommand)
    {
    if (iContainer && aCommand == EAknSoftkeyOptions)
        iContainer->PrepareForFocusLossL();
    CAknView::ProcessCommandL(aCommand);
    }


// End of File

