// EmbeddingShell.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.


#include <e32keys.h>

#include <coemain.h>

#include <eikenv.h>
#include <eikdef.h>
#include <eikon.hrh>
#include <eiklabel.h>

#include <EmbeddingShell.rsg>
#include "EmbeddingShell.hrh"
#include "EmbeddingShell.h"


//
// TExampleShellModel
//

TExampleShellModel::TExampleShellModel()
	{
	iLibrary=KNullDesC;
	}

TBool TExampleShellModel::Differs(const TExampleShellModel* aCompare) const
	{
	return((*(TInt32*)this)!=(*(TInt32*)aCompare));
	}

//
// class CExampleShellContainer
//

void CExampleShellContainer::ConstructL(const TRect& aRect, TExampleShellModel* aModel)
    {
	iModel=aModel;
    CreateWindowL();
    Window().SetShadowDisabled(ETrue);
    iContext=this;
   	iBrushStyle=CGraphicsContext::ESolidBrush;
    iBrushColor=KRgbWhite;
    SetRect(aRect);
	CreateLabelL();
    ActivateL();
    }

CExampleShellContainer::~CExampleShellContainer()
    {
	delete iExampleControl;
	delete iLabel;
    }
    
TInt CExampleShellContainer::CountComponentControls() const
	{
	return 1 + (iExampleControl ? 1 : 0);
	}

CCoeControl* CExampleShellContainer::ComponentControl(TInt aIndex) const
	{
	switch (aIndex)
		{
	case 0: return iLabel;
	case 1: return iExampleControl;
	default: return 0;
		};
	}

const TInt KLabelHeight=20;

void CExampleShellContainer::CreateLabelL()
	{
	iLabel=new (ELeave) CEikLabel;
	TRect rect=Rect();
	rect.iTl.iY=rect.iBr.iY-KLabelHeight; // make it bottom 20 pixels
	iLabel->SetContainerWindowL(*this);
	iLabel->SetRect(rect);
	iLabel->SetAlignment(EHCenterVCenter); // center text
	iLabel->SetBufferReserveLengthL(200); // nice long buffer
	iLabel->SetFont(iEikonEnv->AnnotationFont());
	iLabel->ActivateL(); // now ready
	}

void CExampleShellContainer::ResetExampleL(CGraphicExampleControl* aExample)
	{
	// get rid of old control
	delete iExampleControl;
	// set up new one
	iExampleControl=aExample;
	// if non-zero, then carry on
	if (!iExampleControl) return;
	TRect rect=Rect(); // get our rect
	rect.iBr.iY-=KLabelHeight; // make way for label
	rect.Shrink(2,2); // shrink it a bit
	iExampleControl->ConstructL(rect,this,*this); // construct, giving rect and observer
	}

_LIT(KTxtFinished,"example finished");
void CExampleShellContainer::NotifyGraphicExampleFinished()
	{
	NotifyStatus(KTxtFinished);
	}

void CExampleShellContainer::NotifyStatus(const TDesC& aMessage)
	{
	iLabel->SetTextL(aMessage);
	if (IsActivated()) iLabel->DrawNow();
	}

TKeyResponse CExampleShellContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
	if	(iExampleControl)
   		return iExampleControl->OfferKeyEventL(aKeyEvent,aType);
	else
		return EKeyWasNotConsumed;
    }

void CExampleShellContainer::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetPenStyle(CGraphicsContext::ENullPen);
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.DrawRect(Rect());
	}

//
// CExampleShellAppUi
//

_LIT(KTxtInitialized,"initialized");
void CExampleShellAppUi::ConstructL()
    {
    BaseConstructL();
	iModel=((CExampleShellDocument*)iDocument)->Model();
    iContainer=new(ELeave) CExampleShellContainer;
    iContainer->ConstructL(ClientRect(),iModel);
	iContainer->NotifyStatus(KTxtInitialized);
	// add container to stack; enables key event handling.
	AddToStackL(iContainer);
    }

void CExampleShellAppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case EExampleShellSelectPicture:
		iContainer->ResetExampleL(new (ELeave) CPictureControl);
		return;
	case EEikCmdExit:
		Exit();
		return;
		}
	}

CExampleShellAppUi::~CExampleShellAppUi()
	{
	RemoveFromStack(iContainer);
    delete iContainer;
	}

//
// CExampleShellDocument
//

CEikAppUi* CExampleShellDocument::CreateAppUiL()
	{
    return(new(ELeave) CExampleShellAppUi);
	}

//
// CExampleShellApplication
//

TUid CExampleShellApplication::AppDllUid() const
	{
	return KUidExampleShellApp;
	}

CApaDocument* CExampleShellApplication::CreateDocumentL()
	{
	return new(ELeave) CExampleShellDocument(*this);
	}

//
// EXPORTed functions
//

EXPORT_C CApaApplication* NewApplication()
	{
	return new CExampleShellApplication;
	}

GLDEF_C TInt E32Dll(TDllReason)
	{
	return KErrNone;
	}
