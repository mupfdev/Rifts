/*
* ============================================================================
*  Name     : CAknExEditorView5 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView5.h"
#include "AknExEditorContainer5.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView5::CAknExEditorView5()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView5::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW5);
    }

// Destructor
CAknExEditorView5::~CAknExEditorView5()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView5::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView5::Id() const
    {
    return KViewId5;
    }

// ---------------------------------------------------------
// CAknExEditorView5::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView5::HandleCommandL(TInt aCommand)
    {
    AppUi()->HandleCommandL(aCommand);
    }

// ---------------------------------------------------------
// CAknExEditorView5::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView5::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView5::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView5::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer5;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView5::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView5::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

