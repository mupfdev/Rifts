/*
* ============================================================================
*  Name     : CAknExEditorView1 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView1.h"
#include "AknExEditorContainer1.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView1::CAknExEditorView1()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView1::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW1);
    }

// Destructor
CAknExEditorView1::~CAknExEditorView1()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView1::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView1::Id() const
    {
    return KViewId1;
    }

// ---------------------------------------------------------
// CAknExEditorView1::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView1::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdSelectEdwin1:
        case EAknExEditorCmdSelectGTextEd1:
            iContainer->FocusTo(aCommand);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorView1::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView1::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView1::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView1::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer1;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView1::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView1::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

