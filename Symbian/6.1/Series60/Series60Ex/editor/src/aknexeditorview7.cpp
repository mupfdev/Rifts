/*
* ============================================================================
*  Name     : CAknExEditorView7 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView7.h"
#include "AknExEditorcontainer7.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView7::CAknExEditorView7()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView7::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW7);
    }

// Destructor
CAknExEditorView7::~CAknExEditorView7()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView7::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView7::Id() const
    {
    return KViewId7;
    }

// ---------------------------------------------------------
// CAknExEditorView7::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView7::HandleCommandL(TInt aCommand)
    {
    AppUi()->HandleCommandL(aCommand);
    }

// ---------------------------------------------------------
// CAknExEditorView7::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView7::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView7::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView7::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer7;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView7::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView7::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

