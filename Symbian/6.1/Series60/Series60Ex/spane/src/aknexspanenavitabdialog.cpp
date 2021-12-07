/*
* ============================================================================
*  Name     : AknExSpaneNaviDialog from Control, MCoeControlObserver
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <aknconsts.h>
#include <Avkon.rsg>
#include <akncontext.h>
#include <aknform.h>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpaneNaviViewContainer.h"
#include "AknExSpaneNaviTabDialog.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpaneNaviTabDialog::CAknExSpaneNaviTabDialog(CAknExSpaneNaviViewContainer* aContainer, TInt aCommand)
    :iContainer(aContainer),
    iCommand(aCommand)
    {
    }

// ---------------------------------------------------------
// CAknExSpaneNaviTabDialog::PreLayoutDynInitL(void)
// set params before showing dialog
// ---------------------------------------------------------
//
void CAknExSpaneNaviTabDialog::PreLayoutDynInitL(void)
    {
    TInt startIndex;
    TInt endIndex;
    TInt curIndex;
    iContainer->GetTabIndexRange(&startIndex, &endIndex, &curIndex);

    if ((iCommand == EAknExSpaneNaviTabAdd) || (iCommand == EAknExSpaneNaviTabReplace))
        {
        SetNumberEditorValue(EAknExSpaneNaviDialogTabImage,EAknExSpaneNaviTabNoImage);
        }

    if ((iCommand == EAknExSpaneNaviTabSelect) || (iCommand == EAknExSpaneNaviTabReplace))
        {
        SetNumberEditorMinAndMax(EAknExSpaneNaviDialogTabIndex,startIndex,endIndex);
        SetNumberEditorValue(EAknExSpaneNaviDialogTabIndex,curIndex);
        }
    SetEditableL(ETrue);
    }

// ---------------------------------------------------------
// CAknExSpaneNaviTabDialog::PreLayoutDynInitL(void)
// set params before showing dialog
// ---------------------------------------------------------
//
TBool CAknExSpaneNaviTabDialog::OkToExitL(TInt /*aKeycode*/)
    {
    TInt tabIndex, tabImageNumber;
    TBuf<KLengthOfNaviTempString> tabText= _L("");

    tabIndex = 0;
    tabImageNumber = EAknExSpaneNaviTabNoImage;

    switch (iCommand)
        {
        case EAknExSpaneNaviTabAdd:
            tabImageNumber = NumberEditorValue(EAknExSpaneNaviDialogTabImage);
                //HorOptionButListCurrentSet(EAknExSpaneNaviDialogTabImage);
            GetEdwinText(tabText, EAknExSpaneNaviDialogTabText);
            break;

        case EAknExSpaneNaviTabReplace:
            tabIndex = NumberEditorValue(EAknExSpaneNaviDialogTabIndex);
            tabImageNumber = NumberEditorValue(EAknExSpaneNaviDialogTabImage);
            GetEdwinText(tabText, EAknExSpaneNaviDialogTabText);
            break;

        case EAknExSpaneNaviTabSelect:
            tabIndex = NumberEditorValue(EAknExSpaneNaviDialogTabIndex);
            break;

        default:
            break;
        }

    iContainer->SetTabOperate(iCommand, tabIndex, tabText, tabImageNumber);

    return ETrue;
    }

// End of File