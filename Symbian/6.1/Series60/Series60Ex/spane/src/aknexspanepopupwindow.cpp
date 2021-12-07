/*
* ============================================================================
*  Name     : CAknExSpanePopUpWindow from CCoeControl
*  Part of  : AknExSpane
*  Copyright (c) 2003 Nokia. All rights reserved.
* ============================================================================
*/

// INCLUDE FILES
#include <eiklabel.h>
#include <aknconsts.h>
#include <akncontext.h>

#include <AknExSpane.rsg>
#include "AknExSpane.hrh"
#include "AknExSpaneApp.h"
#include "AknExSpaneAppUi.h"
#include "AknExSpanePopupWindow.h"

// ================= MEMBER FUNCTIONS =======================

// C++ default constructor can NOT contain any code, that
// might leave.
//
CAknExSpanePopUpWindow::CAknExSpanePopUpWindow() : iColor(AKNEXSPANE_KRGB_BLUE)
    {
    }

// EPOC default constructor can leave.
void CAknExSpanePopUpWindow::ConstructL(const TRect& aRect)
    {
    iMyWindowGroup=RWindowGroup(iCoeEnv->WsSession());
    
    User::LeaveIfError(iMyWindowGroup.Construct((TUint32)&iMyWindowGroup));
    
    iMyWindowGroup.SetOrdinalPosition(0, ECoeWinPriorityAlwaysAtFront);
    iMyWindowGroup.EnableReceiptOfFocus(EFalse);
    
    CreateWindowL(&iMyWindowGroup);
    SetRect(aRect);
    EnableDragEvents();
    ActivateL();
    }

// Destructor
CAknExSpanePopUpWindow::~CAknExSpanePopUpWindow()
    {
    iMyWindowGroup.Close();
    }

// ---------------------------------------------------------
// CAknExSpanePopUpWindow
// ---------------------------------------------------------
//
void CAknExSpanePopUpWindow::SetColor(TRgb aColor)
    {
    iColor = aColor;
    }

// ---------------------------------------------------------
// CAknExSpanePopUpWindow::Draw(const TRect& aRect) const
// Draw function.
// ---------------------------------------------------------
//
void CAknExSpanePopUpWindow::Draw(const TRect& aRect) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetPenStyle(CGraphicsContext::ENullPen);
    gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
    gc.SetBrushColor(AKNEXSPANE_KRGB_BLUE);
    gc.DrawRect(aRect);
    }

// End of File
