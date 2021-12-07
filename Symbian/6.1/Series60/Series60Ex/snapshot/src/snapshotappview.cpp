/* Copyright (c) 2001, Nokia. All rights reserved */

#include "EikonEnvironment.h"
#include "SnapShotAppView.h"

// Standard Epoc construction sequence
CSnapShotAppView* CSnapShotAppView::NewL(const TRect& aRect)
    {
    CSnapShotAppView* self = CSnapShotAppView::NewLC(aRect);
    CleanupStack::Pop();
    return self;
    }

CSnapShotAppView* CSnapShotAppView::NewLC(const TRect& aRect)
    {
    CSnapShotAppView* self = new (ELeave) CSnapShotAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CSnapShotAppView::ConstructL(const TRect& aRect)
    {
    iCameraManager = CCameraManager::NewL(*this);

    iBitmap = new (ELeave) CFbsBitmap();

    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

CSnapShotAppView::CSnapShotAppView()
    {
    // Add any construction code that can not leave here
    }


CSnapShotAppView::~CSnapShotAppView()
    {
    delete iCameraManager;
    iCameraManager = NULL;

    delete iBitmap;
    iBitmap = NULL;
    }

TBool CSnapShotAppView::IsCameraReady()
    {
    ASSERT(iCameraManager != NULL);
    return  iCameraManager->IsReady();
    }

void CSnapShotAppView::Snap()
    {
    ASSERT(iCameraManager != NULL);
    iCameraManager->Snap(*iBitmap);
    }

void CSnapShotAppView::Draw(const TRect& /*aRect*/) const
    {
    ASSERT(iCameraManager != NULL);

    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());

	//if the bitmap is not currently being processed in any way
	// AND a valid bitmap exists, then draw it
	if ( (iCameraManager->IsReady()) && (iBitmap->Handle()) )
		{
		gc.DrawBitmap(Rect(), iBitmap, iBitmap->SizeInPixels());
		}
    }


void CSnapShotAppView::PictureTaken()
    {
    DrawDeferred();
    }


_LIT (KEmulatorError, "Snapshot is not currently supported by this emulator.");
_LIT (KErrorMessage,  "Camera server error : %d");

void CSnapShotAppView::Error(TInt aError)
    {
#ifdef __WINS__
    if (aError == KErrNotFound)
		{
		NEikonEnvironment::MessageBox (KEmulatorError);
		return;
		}
#endif
	TBuf<32> cameraError;
	cameraError.Format (KErrorMessage, aError);
	NEikonEnvironment::MessageBox (cameraError);
    }

