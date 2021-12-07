/*
* ============================================================================
*  Name     : CAknExEditorView25 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView25.h"
#include "AknExEditorContainer25.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView25::CAknExEditorView25()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView25::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW25);
    }

// Destructor
CAknExEditorView25::~CAknExEditorView25()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView25::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView25::Id() const
    {
    return KViewId25;
    }

// ---------------------------------------------------------
// CAknExEditorView25::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView25::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdSelect12HoursEditor:
        case EAknExEditorCmdSelect24HoursEditor:

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
// CAknExEditorView25::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView25::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView25::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView25::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                     TUid /*aCustomMessageId*/,
                                     const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer25;
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView25::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView25::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

