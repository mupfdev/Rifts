/*
* ============================================================================
*  Name     : CAknExEditorView30 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView30.h"
#include "AknExEditorContainer30.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView30::CAknExEditorView30()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView30::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW30);
    }

// Destructor

CAknExEditorView30::~CAknExEditorView30()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView30::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView30::Id() const
    {
    return KViewId30;
    }

// ---------------------------------------------------------
// CAknExEditorView30::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView30::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {

        case EAknExEditorSelectText:
        case EAknExEditorClearSelection:
        case EAknExEditorCut:
        case EAknExEditorCopy:
        case EAknExEditorPaste:
        case EAknExEditorUndo:
            iContainer->TestSelectedCase(aCommand);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorView30::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView30::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView30::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView30::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                     TUid /*aCustomMessageId*/,
                                     const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer30;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView30::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView30::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    iContainer = NULL;
    }

// End of File

