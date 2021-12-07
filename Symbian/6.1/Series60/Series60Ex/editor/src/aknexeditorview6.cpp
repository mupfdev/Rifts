/*
* ============================================================================
*  Name     : CAknExEditorView6 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView6.h"
#include "AknExEditorContainer6.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView6::CAknExEditorView6()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView6::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW6);
    }

// Destructor
CAknExEditorView6::~CAknExEditorView6()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView6::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView6::Id() const
    {
    return KViewId6;
    }

// ---------------------------------------------------------
// CAknExEditorView6::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView6::HandleCommandL(TInt aCommand)
    {
    AppUi()->HandleCommandL(aCommand);
    }

// ---------------------------------------------------------
// CAknExEditorView6::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView6::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView6::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView6::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer6;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView6::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView6::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

