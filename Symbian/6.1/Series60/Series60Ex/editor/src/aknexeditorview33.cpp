/*
* ============================================================================
*  Name     : CAknExEditorView33 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView33.h"
#include "AknExEditorContainer33.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView33::CAknExEditorView33()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView33::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW33);
    }

// Destructor

CAknExEditorView33::~CAknExEditorView33()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView33::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView33::Id() const
    {
    return KViewId33;
    }

// ---------------------------------------------------------
// CAknExEditorView33::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView33::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorSetWordWrapTrue:
        case EAknExEditorSetWordWrapFalse:

            iContainer->TestSelectedCase(aCommand);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }


// ---------------------------------------------------------
// CAknExEditorView33::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView33::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView33::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView33::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                     TUid /*aCustomMessageId*/,
                                     const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer33;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView33::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView33::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    iContainer = NULL;
    }

// End of File

