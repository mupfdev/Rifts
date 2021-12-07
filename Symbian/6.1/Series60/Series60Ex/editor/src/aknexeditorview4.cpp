/*
* ============================================================================
*  Name     : CAknExEditorView4 from CAknView
*  Part of  : AknExEditor
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <aknviewappui.h>
#include <avkon.hrh>

#include <AknExEditor.rsg>
#include "AknExEditor.hrh"
#include "AknExEditorView4.h"
#include "AknExEditorContainer4.h" 

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExEditorView4::CAknExEditorView4()
    {
    }

// EPOC default constructor can leave.
void CAknExEditorView4::ConstructL()
    {
    BaseConstructL(R_AKNEXEDITOR_VIEW4);
    }

// Destructor
CAknExEditorView4::~CAknExEditorView4()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }

    delete iContainer;
    }

// ---------------------------------------------------------
// TUid CAknExEditorView4::Id()
// Returns Id of the view.
// ---------------------------------------------------------
TUid CAknExEditorView4::Id() const
    {
    return KViewId4;
    }

// ---------------------------------------------------------
// CAknExEditorView4::HandleCommandL(TInt aCommand)
// Handles commands
// ---------------------------------------------------------
void CAknExEditorView4::HandleCommandL(TInt aCommand)
    {   
    switch (aCommand)
        {
        case EAknExEditorCmdFont1:
            iContainer->SetFontL(R_AKNEXEDITOR_FONT1);
            break;
        case EAknExEditorCmdFont2:
            iContainer->SetFontL(R_AKNEXEDITOR_FONT2);
            break;
        case EAknExEditorCmdFont3:
            iContainer->SetFontL(R_AKNEXEDITOR_FONT3);
            break;
        case EAknExEditorCmdFont4:
            iContainer->SetFontL(R_AKNEXEDITOR_FONT4);
            break;
        case EAknExEditorCmdFont5:
            iContainer->SetFontL(R_AKNEXEDITOR_FONT5);
            break;
        case EAknExEditorCmdFont6:
            iContainer->SetFontL(R_AKNEXEDITOR_FONT6);
            break;

        case EAknExEditorCmdLatinPlain12:
            iContainer->SetSystemFontL(ELatinPlain12);
            break;
        case EAknExEditorCmdLatinBold12:
            iContainer->SetSystemFontL(ELatinBold12);
            break;
        case EAknExEditorCmdLatinBold13:
            iContainer->SetSystemFontL(ELatinBold13);
            break;
        case EAknExEditorCmdLatinBold17:
            iContainer->SetSystemFontL(ELatinBold17);
            break;
        case EAknExEditorCmdLatinBold19:
            iContainer->SetSystemFontL(ELatinBold19);
            break;
        case EAknExEditorCmdNumberPlain5:
            iContainer->SetSystemFontL(ENumberPlain5);
            break;
        case EAknExEditorCmdClockBold30:
            iContainer->SetSystemFontL(EClockBold30);
            break;
        case EAknExEditorCmdLatinClock14:
            iContainer->SetSystemFontL(ELatinClock14);
            break;

        default:
            AppUi()->HandleCommandL(aCommand);
            break;
        }
    }

// ---------------------------------------------------------
// CAknExEditorView4::HandleClientRectChange()
// Handles client rect change.
// ---------------------------------------------------------
void CAknExEditorView4::HandleClientRectChange()
    {
    if (iContainer)
        {
        iContainer->SetRect(ClientRect());
        }
    }

// ---------------------------------------------------------
// CAknExEditorView4::DoActivateL(...)
// Creates the Container class object.
// ---------------------------------------------------------
void CAknExEditorView4::DoActivateL(const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    iContainer = new (ELeave) CAknExEditorContainer4;
    iContainer->SetMopParent(this);
    iContainer->ConstructL(ClientRect());
    AppUi()->AddToStackL(*this, iContainer);
    }

// ---------------------------------------------------------
// CAknExEditorView4::DoDeactivate()
// Deletes the Container class object.
// ---------------------------------------------------------
void CAknExEditorView4::DoDeactivate()
    {
    if (iContainer)
        {
        AppUi()->RemoveFromStack(iContainer);
        }
    
    delete iContainer;
    iContainer = NULL;
    }

// End of File

