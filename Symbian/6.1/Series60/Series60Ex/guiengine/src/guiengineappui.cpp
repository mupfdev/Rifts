/* Copyright (c) 2001, Nokia. All rights reserved */
#include <eiktbar.h>
#include <eikenv.h>
#include <w32adll.h>
#include <avkon.hrh>

#include "GuiEngine.pan"
#include "GuiEngineDocument.h"
#include "GuiEngineAppUi.h"
#include "GuiEngineAppView.h"
#include "GuiEngine.hrh"


CGuiEngineAppUi::CGuiEngineAppUi(CGuiEngineDocument* aDocument) 
:	iDocument(aDocument)                                
	{
	//	No implementation required
	}


void CGuiEngineAppUi::ConstructL()
	{
    BaseConstructL();

    iAppView = CGuiEngineAppView::NewL(ClientRect(), iDocument);    

    // Enable the virtual cursor
    iEikonEnv->VirtualCursor().SetCursorStateL(TEikVirtualCursor::EOn,*iEikonEnv);

    AddToStackL(iAppView);

	}


CGuiEngineAppUi::~CGuiEngineAppUi()
	{
	if (iAppView)
		{
		RemoveFromStack(iAppView);

		delete iAppView;
	    iAppView = NULL;
		}

	}

void CGuiEngineAppUi::HandleCommandL(TInt aCommand)
	{

    switch(aCommand)
		{
        case EAknSoftkeyExit:
            SaveL();
            Exit();
            break;
        case KClear:
            iAppView->Clear();
            break;
        case KSelectBrushCircle:
            iAppView->SetBrushShapeType(CGuiEngineAppView::ECircle);
            break;
        case KSelectBrushRectangle:
            iAppView->SetBrushShapeType(CGuiEngineAppView::ERectangle);
            break;
        default:
			User::Panic(KGuiEnginePanicName, EGuiEngineUnknownCommand);
            break;
		}
    
	}

void CGuiEngineAppUi::HandleModelChangeL()
    {
    // Redraw the application view based on the new model.
	iAppView->DrawNow();

    // Update the file name in the task list to show the current file.
	iEikonEnv->UpdateTaskNameL();
    }

TStreamId CGuiEngineAppUi::StoreL(CStreamStore& aStore) const
    {
    RStoreWriteStream stream;
    TStreamId id = stream.CreateLC(aStore); 

	// Write the data to the stream
    iAppView->ExternalizeL(stream);
    stream.CommitL(); 

    CleanupStack::PopAndDestroy(); 
    return id; // return the stream ID          
    }

void CGuiEngineAppUi::RestoreL(const CStreamStore& aStore, TStreamId aStreamId)
    {
    RStoreReadStream stream; 
    stream.OpenLC(aStore,aStreamId); 

	//	Read in the data
    iAppView->InternalizeL(stream); 

    CleanupStack::PopAndDestroy();
    }


