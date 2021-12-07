/* Copyright (c) 2001, Nokia. All rights reserved */
#include "GuiEngineDocument.h"
#include "GuiEngineApplication.h"

// local constants
const TUid KUidGuiEngineApp = {0x10005B7D};
const TUid KUidGuiEngineUi = {0x10005B83};

CApaDocument* CGuiEngineApplication::CreateDocumentL()
	{  
    // Create an GuiEngine document, and return a pointer to it
    CApaDocument* document = CGuiEngineDocument::NewL(*this);
    return document;
	}

TUid CGuiEngineApplication::AppDllUid() const
	{
    // Return the UID for the GuiEngine application
    return KUidGuiEngineApp;
	}

TUid CGuiEngineApplication::AppUiUid() const
	{
    // Return the UID for the Ui
    return KUidGuiEngineUi;
	}

