/*
* ============================================================================
*  Name     : CAknExEditorView21 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView21.h"
#include "AknExEditorContainer21.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView21::CAknExEditorView21()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView21::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW21);
    }

// Destructor
CAknExEditorView21::~CAknExEditorView21()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView21::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView21::Id() const
    {
    return KViewId21;
    }

// ---------------------------------------------------------
// CAknExEditorView21::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView21::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdShowForm:
            iContainer->ShowFormL();
            break;
        case EAknExEditorCmdReadIPAddress:
            iContainer->ReadIPAddress();
            break;
        case EAknExEditorCmdDisplayIPAddress:
            iContainer->DisplayIPAddress();
            break;
        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorView21::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView21::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView21::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView21::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                     TUid /*aCustomMessageId*/,
                                     const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer21;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView21::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView21::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    iContainer = NULL;
    }

// End of File

