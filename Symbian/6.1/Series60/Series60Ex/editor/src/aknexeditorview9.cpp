/*
* ============================================================================
*  Name     : CAknExEditorView9 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView9.h"
#include "AknExEditorContainer9.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView9::CAknExEditorView9()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView9::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW9);
    }

// Destructor
CAknExEditorView9::~CAknExEditorView9()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView9::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView9::Id() const
    {
    return KViewId9;
    }

// ---------------------------------------------------------
// CAknExEditorView9::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView9::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdSelectEdwin1:
        case EAknExEditorCmdSelectGTextEd1:
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
// CAknExEditorView9::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView9::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView9::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView9::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer9;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView9::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView9::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

