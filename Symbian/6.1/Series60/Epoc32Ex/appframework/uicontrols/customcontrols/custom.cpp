// CUSTOM.CPP
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//


//
// UI Control Framework example program
//
// This example demonstrates how to write new control classes.
//
// The example creates three new control classes:
//      1. CSmiley              - a simple control which displays a 
//                              smiley face that can have two moods,
//                              happy and sad. The user can change
//                              the smiley's mood by pressing the
//                              space bar.
//      2. CSmileyContainer     - a compound control which contains
//                              two CSmiley controls, side by side.
//                              The user can move the keyboard focus
//                              from one CSmiley to the other using
//                              the arrow keys, or the pointer.
//      3. CMainWinControl      - a compound control which does nothing
//                              except act as a background window and a 
//                              container for other controls in the 
//                              application.
//
//
// When the application starts up, it creates a CMainWinControl to cover
// the entire screen, and a CSmileyContainer inside this main window.
// The application's menu contains just two options. One of them closes 
// the application; the other creates a dialog which contains a 
// CSmileyContainer. CSmileyContainer therefore illustrates how to write 
// a control that can be created both in a dialog and within the
// application's main view.
//

#include "custom.h"


//////////////////////////////////////////////////////////////////////////////
//
// -----> CMainWinControl(implementation)
//
//////////////////////////////////////////////////////////////////////////////
CMainWinControl::CMainWinControl()
	{
	}

CMainWinControl::~CMainWinControl()
	{
	delete iContainer;
	}

// CMainWinControl needs a ConstructL(), because it is a compound control
// (and a window-owning control).
void CMainWinControl::ConstructL(const TRect& rect)
	{
	// Make this a window-owning control.
	CreateWindowL();
	SetRect(rect);

	// Create its only component, a CSmileyContainer
	iContainer = new(ELeave) CSmileyContainer;
	iContainer->SetContainerWindowL(*this);
	TRect containerRect=Rect();
	iContainer->ConstructL(containerRect);
	// Activate the main window control - this will also activate the 
	// CSmileyContainer and its components.
	ActivateL();
	DrawNow();
	}

// The following two functions have to be implemented for all compound controls.
TInt CMainWinControl::CountComponentControls() const
	{
	return 1;
	}

CCoeControl* CMainWinControl::ComponentControl(TInt /*aIndex*/) const
	{
	return iContainer;
	}

// Draw the main window.
void CMainWinControl::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc=SystemGc();
	gc.SetBrushColor(KRgbWhite);
	gc.Clear(Rect());
	}

// CSmileyContainer can't be put on the control stack, because it's a component of this 
// control. The main window control goes on the stack and passes on any key events it gets
// to the CSmileyContainer.
TKeyResponse CMainWinControl::OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType)
	{
	return (iContainer->OfferKeyEventL(aKeyEvent, aType));
	}

//////////////////////////////////////////////////////////////////////////////
//
// -----> CSmileyContainer (implementation)
//
//////////////////////////////////////////////////////////////////////////////
CSmileyContainer::CSmileyContainer()
	{}

	
CSmileyContainer::~CSmileyContainer()
	{
	  // Delete all the contained controls 
	delete iSmiley1;
	delete iSmiley2;
	}


// Because CSmileyContainer is a compound control, it needs a
// ConstructL() for when it's created outside a dialog, and a
// ConstructFromResourceL() for when it's created inside a dialog.
void CSmileyContainer::ConstructL(const TRect& aRect)
	{
	TBool isSmiling=ETrue;

	// Create the two CSmileys. Their size and position is 
	// set in CSmileyContainer::SizeChangedL().
	iSmiley1 = new(ELeave) CSmiley(isSmiling);
	iSmiley1->SetContainerWindowL(*this);

	isSmiling=EFalse;

	iSmiley2 = new(ELeave) CSmiley(isSmiling);
	iSmiley2->SetContainerWindowL(*this);

	iSmiley1->SetFocus(ETrue);

	// Set the container as the observer of the two CSmileys. This 
	// is for handling keyboard focus. When an arrow key is pressed 
	// or the pointer is clicked on one of the CSmileys, an 
	// EEventRequestFocus event is sent to the container, and the
	// container changes the focus if applicable.
	iSmiley1->SetObserver(this);
	iSmiley2->SetObserver(this);

	// Set the bounding rectangle of this control (this will result in 
	// a call to SizeChangedL(). The component controls must be 
	// created before calling this, because SizeChangedL() sets their
	// sizes.
	SetRect(aRect);
	}


// This function is used when the CSmileyContainer is created inside a dialog.
void CSmileyContainer::ConstructFromResourceL(TResourceReader& aReader)
	{
	// Read the smiley mood from the resource file
	TBool isSmiling=(TBool)aReader.ReadInt8();
	// Read the width of the smiley container from the resource file.
	TInt width=aReader.ReadInt16();
	// Set the height of the container to be half its width
	TSize containerSize (width, width/2);

	iSmiley1 = new(ELeave) CSmiley(isSmiling);
	iSmiley1->SetContainerWindowL(*this);

	iSmiley2 = new(ELeave) CSmiley(isSmiling);
	iSmiley2->SetContainerWindowL(*this);

	iSmiley1->SetFocus(ETrue);

	iSmiley1->SetObserver(this);
	iSmiley2->SetObserver(this);

	SetSize(containerSize);

	ActivateL();	
	}

// The following two functions have to be implemented for all compound controls.
TInt CSmileyContainer::CountComponentControls() const
	{
	return 2;
	}

CCoeControl* CSmileyContainer::ComponentControl(TInt aIndex) const
	{
	if (aIndex==0)
		return iSmiley1;
	else
		return iSmiley2;
	}

// This function gets called whenever one of the size-setting functions is called.
// As this is a compound control, this function calculates and sets the size and  
// position for its components, based on its own size.
void CSmileyContainer::SizeChanged()
    {
	TInt containerWidth=Size().iWidth;
	TInt containerHeight=Size().iHeight;
	// Find half of the greater - width or height
	TInt length=containerHeight>containerWidth ? containerWidth/4 : containerHeight/4; 
	TSize smileySize(length,length);

	// Do some preliminary calculations so that Draw() is as short
	// as possible.
	TInt xOffset=smileySize.iWidth/4; // x offset from the center
	TInt yOffset=(containerHeight - smileySize.iHeight) / 2;
	iSmiley1->SetPosition(Position() +
		TPoint(containerWidth/2 - smileySize.iWidth - xOffset, yOffset));
	iSmiley2->SetPosition(Position() + 
		TPoint(containerWidth/2 + xOffset, yOffset));
	// Calling SetSizeL() causes the components' SizeChanged() to be called.
	iSmiley1->SetSize(smileySize);
	iSmiley2->SetSize(smileySize);
	}
	
void CSmileyContainer::Draw(const TRect& aRect) const
	{
	// Just draw a rectangle round the edge of the control.
	CWindowGc& gc=SystemGc();
	gc.Clear(aRect);
	gc.SetClippingRect(aRect);
	gc.DrawRect(Rect());
	}

// This function is defined by MCoeControlObserver. It gets called whenever
// a control that this control is observing calls ReportEventL().
// In this example, the CSmileyContainer is the observer for both of the 
// CSmileys.  CCoeControl::ProcessPointerEventL() calls ReportEvent(), 
// sending an event of type EEventRequestFocus, whenever an EButton1Down event
// occurs in the CSmiley that doesn't currently have focus.
void CSmileyContainer::HandleControlEventL(CCoeControl* aControl,
										TCoeEvent aEventType)
	{
	switch (aEventType)
		{
		case EEventRequestFocus:
			{
			if (aControl->IsFocused())
				return;
			SwapFocus(aControl);
			}
			break;
		default:
			break;
		}
	}

// This function is called by the framework whenever a component in a dialog is 
// about to lose focus. It checks that the data in ithe component is valid. In
// this example, there's a "rule" that both the CSmileys in the container can't
// be miserable! If they are, the function leaves. The framework issues the message 
// we give it, and doesn't move focus away from the CSmileyContainer.
void CSmileyContainer::PrepareForFocusLossL()	
	{
	if (!iSmiley1->IsSmiling() && !iSmiley2->IsSmiling())
		{
		CEikonEnv::Static()->LeaveWithInfoMsg(R_EXAMPLE_TEXT_VALIDATE);
		}
	}

// This function gets called whenever the application calls SetFocus().
// It redraws the CSmileyContainer, so that they are updated to show 
// which one now has focus.
void CSmileyContainer::FocusChanged(TDrawNow aDrawNow)
	{
	if (IsFocused())
		{
		iSmiley1->SetFocus(ETrue, EDrawNow);
		}
	else
		{
			if (iSmiley1->IsFocused())
			iSmiley1->SetFocus(EFalse, EDrawNow);
			else
			iSmiley2->SetFocus(EFalse, EDrawNow);
		}
	if (aDrawNow)
		DrawNow();
	}


void CSmileyContainer::SwapFocus(CCoeControl* aControl)
	{
	if (aControl==iSmiley1)
		{
		iSmiley2->SetFocus(EFalse, EDrawNow);
		iSmiley1->SetFocus(ETrue, EDrawNow);
		}
	else
		{
		iSmiley1->SetFocus(EFalse, EDrawNow);
		iSmiley2->SetFocus(ETrue, EDrawNow);
		}
	}

TKeyResponse CSmileyContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	// Use the arrow keys to move focus between the two CSmileys.
	switch (aKeyEvent.iScanCode)
		{
		case EStdKeySpace:
			if (iSmiley1->IsFocused())
				return iSmiley1->OfferKeyEventL(aKeyEvent, aType);
			else if (iSmiley2->IsFocused())
				return iSmiley2->OfferKeyEventL(aKeyEvent, aType);
			break;
		case EStdKeyRightArrow:
			if (iSmiley1->IsFocused())
				SwapFocus(iSmiley2);
			return EKeyWasConsumed;
			break;
		case EStdKeyLeftArrow:
			if (iSmiley2->IsFocused())
				SwapFocus(iSmiley1);
			return EKeyWasConsumed;
			break;
		default:
			break;
		}
	// If the CSmileyContainer didn't use the key event, it must return EKeyWasNotConsumed,
	// so that the key event is passed to other controls on the stack.
	return EKeyWasNotConsumed;
	}




//////////////////////////////////////////////////////////////////////////////
//
// -----> CSmiley (implementation)
//
//////////////////////////////////////////////////////////////////////////////

// CSmiley doesn't need a ConstructL() because it's a simple control.

CSmiley::CSmiley(TBool aSmiling) : iSmiling(aSmiling)
	{
	}

CSmiley::~CSmiley()
	{
	}

TBool CSmiley::IsSmiling()
	{
	return iSmiling;
	}

void CSmiley::Draw(const TRect& aRect) const
	{
	CWindowGc& gc=SystemGc();
	if (IsFocused())
		{
		gc.SetPenColor(KRgbBlack);
		}
	else
		{
		gc.SetPenColor(KRgbWhite);
		}
	gc.SetBrushColor(KRgbWhite);
	gc.Clear(Rect());
	gc.DrawRect(Rect());

	gc.SetClippingRect(aRect);

	// Draw the smiley face, smiling or looking sad
	gc.SetPenColor(KRgbBlack);
	// Draw a circle for the face
	gc.DrawEllipse(iSmileyRect);
	// Draw the eyes
	TPoint leftEye(iSmileyWidth/3, iSmileyHeight/3);
	TPoint rightEye(iSmileyWidth*2/3, iSmileyHeight/3);
	gc.SetPenSize(TSize(5,5));
	gc.Plot(iSmileyRect.iTl+leftEye);
	gc.Plot(iSmileyRect.iTl+rightEye);
	//Draw the mouth, smiling or looking sad.
	gc.SetPenSize(TSize(1,1));
	gc.SetPenColor(KRgbWhite);
	if (iSmiling)
		gc.DrawArc(iFrownRect, iFrownRect.iTl+TPoint(iSmileyWidth/2,iFrownRect.Height()/2), 
							  iFrownRect.iTl+TPoint(0,iFrownRect.Height()/2));
	else
		gc.DrawArc(iSmileRect, iSmileRect.iTl+TPoint(0,iSmileRect.Height()/2), 
							  iSmileRect.iTl+TPoint(iSmileyWidth/2,iSmileRect.Height()/2));
	gc.SetPenColor(KRgbBlack);
	if (iSmiling)
		gc.DrawArc(iSmileRect, iSmileRect.iTl+TPoint(0,iSmileRect.Height()/2), 
							  iSmileRect.iTl+TPoint(iSmileyWidth/2,iSmileRect.Height()/2));
	else
		gc.DrawArc(iFrownRect, iFrownRect.iTl+TPoint(iSmileyWidth/2,iFrownRect.Height()/2), 
							  iFrownRect.iTl+TPoint(0,iFrownRect.Height()/2));
	}

void CSmiley::SizeChanged()
	{
	// Calculate sizes of rectangles for drawing face and mouth
	iSmileyRect=Rect();
	// Allow room for the focus rectangle round the outside
	iSmileyRect.Shrink(3,3);
	iSmileyWidth=iSmileyRect.Width();
	iSmileyHeight=iSmileyRect.Height();
	iSmileRect.SetRect(iSmileyRect.iTl+TPoint(iSmileyWidth/4, iSmileyHeight/2),
					TSize(iSmileyWidth/2, iSmileyHeight/3));
	iFrownRect.SetRect(iSmileyRect.iTl+TPoint(iSmileyWidth/4, iSmileyHeight*2/3),
					TSize(iSmileyWidth/2, iSmileyHeight/3));
	}

void CSmiley::FocusChanged(TDrawNow aDrawNow)
	{
	if (aDrawNow)
		DrawNow();
	}

void CSmiley::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	if (aPointerEvent.iType==TPointerEvent::EButton1Down)
		{
		iSmiling = !iSmiling;
		DrawNow();
		}
	}

TKeyResponse CSmiley::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
	{
	// The space bar changes the "mood" of the CSmiley.
	if (aType==EEventKey && aKeyEvent.iScanCode==EStdKeySpace)
		{
		iSmiling = !iSmiling;
		DrawNow();
		return EKeyWasConsumed;
		}
	else
		{
		return EKeyWasNotConsumed;
		}
	}

//////////////////////////////////////////////////////////////////////////////
//
// -----> CSmileyDialog(implementation)
//
//////////////////////////////////////////////////////////////////////////////
TBool CSmileyDialog::RunDlgLD()
	{
	CEikDialog* dialog = new (ELeave) CSmileyDialog();
	return (dialog->ExecuteLD(R_SMILEY_DIALOG));
	}

// This function is used by CEikForm::ConstructByTypeL() to create the custom 
// control within the dialog.
SEikControlInfo CSmileyDialog::CreateCustomControlL(TInt aControlType)
	{
	SEikControlInfo controlInfo;
	controlInfo.iControl = NULL;
	controlInfo.iTrailerTextId = 0;
	controlInfo.iFlags = 0;

    switch (aControlType)
        {
    case ESmileyControl:
		controlInfo.iControl = new(ELeave) CSmileyContainer;
		break;
	default:
		break;
		}
    return controlInfo;
	}

//////////////////////////////////////////////////////////////////////////////
//
// -----> CExampleAppUi (implementation)
//
//////////////////////////////////////////////////////////////////////////////
void CExampleAppUi::ConstructL()
	{
	  // Allow base class (CEikAppUi) to perform necessary construction
	BaseConstructL();
	// Construct the CMainWinControl which forms the main view
	// for this application.
	iMainWinControl=new(ELeave) CMainWinControl;
	iMainWinControl->ConstructL(ClientRect());
	// The main window is added to the control stack (for key event
	// handling).	
	AddToStackL(iMainWinControl);
	}
	

CExampleAppUi::~CExampleAppUi()
	{
	RemoveFromStack(iMainWinControl);
	  // Delete the main window
	delete iMainWinControl;
	}

void CExampleAppUi::HandleCommandL(TInt aCommand)
	{
	  // Handle the command generated by:
	  //   1. menu item selection
	  //   2. short-cut key press
	switch (aCommand)
		{
	// EXIT comand
	case EEikCmdExit:
		OnCmdExit();
		break;
	case ECreateSmileyDialog:
		CSmileyDialog::RunDlgLD();
		break;
	default :
		break;
		}
	}

void CExampleAppUi::OnCmdExit()
	{
	CBaActiveScheduler::Exit();
	}

void CExampleAppUi::HandleModelChangeL()
	{
	}

/////////////////////////////////////////////////////////////////////////////
//
// -----> CExampleDocument (implementation)
//
/////////////////////////////////////////////////////////////////////////////

CExampleDocument::CExampleDocument(CEikApplication& aApp)
	 : CEikDocument(aApp)
	{}

CExampleDocument::~CExampleDocument()
	{
	}

CExampleDocument* CExampleDocument::NewL(CEikApplication& aApp)
	{
	CExampleDocument* self=new(ELeave) CExampleDocument(aApp);
	CleanupStack::PushL(self);
	self->CreateModelL();
	CleanupStack::Pop();
	return self;
	}

void CExampleDocument::ResetModelL()
	{
	CreateModelL();
	}

void CExampleDocument::CreateModelL()
	{
	}

CEikAppUi* CExampleDocument::CreateAppUiL()
	{
    return(new(ELeave) CExampleAppUi);
	}

void CExampleDocument::NewDocumentL()
	{
	ResetModelL();
	}

void CExampleDocument::StoreL(CStreamStore& /*aStore*/,CStreamDictionary& /*aStreamDic*/) const
	{
	}

void CExampleDocument::RestoreL(const CStreamStore& /*aStore*/,const CStreamDictionary& /*aStreamDic*/)
	{
	}


//////////////////////////////////////////////////////////////////////////////
//
// -----> CExampleApplication (implementation)
//
//////////////////////////////////////////////////////////////////////////////
TUid CExampleApplication::AppDllUid() const
	{
	return(KUidExampleApp);
	}


CApaDocument* CExampleApplication::CreateDocumentL()
	{
	return CExampleDocument::NewL(*this);
	}


//
// EXPORTed functions
//

EXPORT_C CApaApplication* NewApplication()
	{
	return(new CExampleApplication);
	}


GLDEF_C TInt E32Dll(TDllReason)
	{
	return(KErrNone);
	}





