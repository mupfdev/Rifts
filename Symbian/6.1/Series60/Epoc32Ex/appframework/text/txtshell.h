// TXTSHELL.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __TXTSHELL_H
#define __TXTSHELL_H

#include <coecntrl.h>
#include <coeccntx.h>

#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>

#include "txtexamp.h"

// UID of app
const TUid KUidExampleShellApp= {0x01000e00} ;

//
// TExampleShellModel
//

class TExampleShellModel
	// A place-holder class for the model class that would be used 
	// in a fully-developed application.
	{
public:
	TExampleShellModel();
	TBool Differs(const TExampleShellModel* aCompare) const;
public:
	TFileName iLibrary; // active control
	};

//
// class CExampleShellContainer
//

class CExampleShellContainer : public CCoeControl,
		public MCoeControlBrushContext,
		public MGraphicsExampleObserver
    {
public:
    void ConstructL(const TRect& aRect, TExampleShellModel* aModel);
    ~CExampleShellContainer();
	// changing view
	void ResetExampleL(CGraphicExampleControl* aExample);
private: // from CCoeControl
	void Draw(const TRect& /*aRect*/) const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl(TInt aIndex) const;
private: // from MGraphicsExampleObserver
	void NotifyGraphicExampleFinished();
public: // also from MGraphicsExampleObserver
	void NotifyStatus(const TDesC& aMessage);
private: // new function
	void CreateLabelL();
private: // member data
	CGraphicExampleControl* iExampleControl; // example control
	CEikLabel* iLabel; // label for status messages
	// irrelevant
	TExampleShellModel* iModel;
    };

//
// CExampleShellDocument
//

class CExampleShellDocument : public CEikDocument
	{
public:
	CExampleShellDocument(CEikApplication& aApp): CEikDocument(aApp) { }
	TExampleShellModel* Model() { return(&iModel); }
private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
private:
	TExampleShellModel iModel;
	};

//
// CExampleShellAppUi
//

class CExampleShellAppUi : public CEikAppUi
    {
public:
    void ConstructL();
	~CExampleShellAppUi();
private: // from CEikAppUi
	void HandleCommandL(TInt aCommand);
private:
    CExampleShellContainer* iContainer;
	TExampleShellModel* iModel;
    };

//
// CExampleShellApplication
//

class CExampleShellApplication : public CEikApplication
	{
private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};

#endif
