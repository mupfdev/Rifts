/*
* ============================================================================
*  Name     : CAknExEditorView23 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView23.h"
#include "AknExEditorContainer23.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView23::CAknExEditorView23()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView23::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW23);
    }

// Destructor
CAknExEditorView23::~CAknExEditorView23()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView23::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView23::Id() const
    {
    return KViewId23;
    }

// ---------------------------------------------------------
// CAknExEditorView23::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView23::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdSelectNumSecretEditor:
        case EAknExEditorCmdSelectSecretEditor:

            iContainer->FocusTo(aCommand);
            break;

        case EAknExEditorCmdShowForm:
            iContainer->ShowFormL();
            break;

        case EAknExEditorCmdShowEditorText:
            iContainer->ShowEditorText();
            break;

        case EAknExEditorCmdView23InitializeDisplay5:
        case EAknExEditorCmdView23InitializeDisplay10:
        case EAknExEditorCmdView23Reset:
        case EAknExEditorCmdView23SetMaxLength5:
        case EAknExEditorCmdView23SetMaxLength10:
        case EAknExEditorCmdView23SetText:
            iContainer->TestSelectedAPIL(aCommand);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorView23::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView23::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView23::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView23::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                     TUid /*aCustomMessageId*/,
                                     const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer23;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView23::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView23::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

