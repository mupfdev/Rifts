/* Copyright (c) 2001, Nokia. All rights reserved */
#include "GuiEngineAppUi.h"
#include "GuiEngineDocument.h"
#include "GuiEngineApplication.h"


CGuiEngineDocument* CGuiEngineDocument::NewLC(CEikApplication& aApp)
	{
    CGuiEngineDocument* self = new (ELeave) CGuiEngineDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
	}

CGuiEngineDocument* CGuiEngineDocument::NewL(CEikApplication& aApp)
	{
    CGuiEngineDocument* self = NewLC(aApp);
    CleanupStack::Pop(self); 
    return self;
	}

void CGuiEngineDocument::ConstructL()
	{
	iModel = CShapeListManager::NewL();
	}    

CGuiEngineDocument::~CGuiEngineDocument()
	{
	delete iModel;
	iModel = NULL;
	}

CGuiEngineDocument::CGuiEngineDocument(CEikApplication& aApp)
:	CEikDocument(aApp)     
	{    
	//	No implementation required
	}

CEikAppUi* CGuiEngineDocument::CreateAppUiL()
	{
    // Create the application user interface, and return a pointer to it
    CEikAppUi* appUi = new (ELeave) CGuiEngineAppUi(this);
    return appUi;
	}

void CGuiEngineDocument::StoreL(CStreamStore& aStore, CStreamDictionary& aStreamDic) const
    {
    // Store model information first

	//	Get the model to save itself to the store
    TStreamId modelStreamId = iModel->StoreL(aStore);
	//	Add an entry into the dictionary for the model data
    aStreamDic.AssignL(Application()->AppDllUid(), modelStreamId); 

    // Now get the Ui to store itself to the store
    TStreamId uiStreamId = static_cast<CGuiEngineAppUi*>(iAppUi)->StoreL(aStore);
	//	Add an entry for it to the dictionary
    aStreamDic.AssignL(static_cast<CGuiEngineApplication*>(Application())->AppUiUid(), uiStreamId);
    }

void CGuiEngineDocument::RestoreL(const CStreamStore& aStore, const CStreamDictionary& aStreamDic)
    {

    // Restore the model from the appropriate store stream.

    // Do not set this as the document's model yet.
    // That way, if the restore fails, we have still
    // got the old model.

    CShapeListManager* newModel = CShapeListManager::NewL();
    CleanupStack::PushL(newModel);

	//	Find the stream id for the model's data
    TStreamId modelStreamId = aStreamDic.At(Application()->AppDllUid());
	//	restore the model from that stream 
    newModel->RestoreL(aStore, modelStreamId);

	//	Now get rid of the old model and set the new one as current
    delete iModel;
    iModel = newModel;
    CleanupStack::Pop(newModel);

	//	Just restored so can't have changed
    SetChanged(EFalse); 

    // Now restore UI data
	TStreamId uiStreamId;
    uiStreamId = aStreamDic.At(static_cast<CGuiEngineApplication*>(Application())->AppUiUid());
    ((CGuiEngineAppUi*)iAppUi)->RestoreL(aStore, uiStreamId);
    }

CShapeListManager* CGuiEngineDocument::Model() 
    {
    return iModel;
    }
