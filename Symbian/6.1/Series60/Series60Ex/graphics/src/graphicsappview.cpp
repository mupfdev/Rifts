/* Copyright (c) 2001, Nokia. All rights reserved */

#include <images.mbg>
#include "GraphicsAppView.h"
#include "bitmapmethods.h"
#include "sprite.h"

_LIT (KMultiBitmapFilename,"c:\\System\\Apps\\Graphics\\images.mbm");

static const TInt KInitialXSpeed = 4;
static const TInt KInitialYSpeed = 4;


// Standard Epoc construction sequence
CGraphicsAppView* CGraphicsAppView::NewL(const TRect& aRect)
    {
    CGraphicsAppView* self = CGraphicsAppView::NewLC(aRect);
    CleanupStack::Pop();
    return self;
    }

CGraphicsAppView* CGraphicsAppView::NewLC(const TRect& aRect)
    {
    CGraphicsAppView* self = new (ELeave) CGraphicsAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CGraphicsAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the window's size and position
    SetRect(aRect);

	// Load in the bitmap images from the multi bitmap file
	iBackgroundImage = NBitmapMethods::CreateBitmapL(KMultiBitmapFilename,EMbmImagesImage1);
	iSpriteImage = NBitmapMethods::CreateBitmapL(KMultiBitmapFilename,EMbmImagesImage2);
	iSpriteMask = NBitmapMethods::CreateBitmapL(KMultiBitmapFilename,EMbmImagesImage2_mask);

	// Create the off screen bitmap and device / gc
	iOffScreenBitmap = NBitmapMethods::CreateBitmapL(Rect().Size(),KColourDepth);
	iOffScreenBitmapDevice = NBitmapMethods::CreateBitmapDeviceL(*iOffScreenBitmap);
	iOffScreenBitmapGc = NBitmapMethods::CreateGraphicsContextL(*iOffScreenBitmapDevice);

	// Create a periodic timer but don't start it yet
	iPeriodicTimer = CPeriodic::NewL(CActive::EPriorityStandard);

    //Create the array of sprite pointers
	iSprites = new (ELeave) CArrayPtrFlat<CSprite> (1);

	SetUpSpritesL();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }


CGraphicsAppView::CGraphicsAppView()
    {
    }


CGraphicsAppView::~CGraphicsAppView()
    {
	if (iPeriodicTimer)
		{
		// Stop the periodic timer
		iPeriodicTimer->Cancel();
		}
	delete iPeriodicTimer;
	iPeriodicTimer = NULL;

	delete iOffScreenBitmapGc;
	iOffScreenBitmapGc = NULL;

	delete iOffScreenBitmapDevice;
	iOffScreenBitmapDevice = NULL;

	delete iOffScreenBitmap;
	iOffScreenBitmap = NULL;

	delete iBackgroundImage;
	iBackgroundImage = NULL;

	if (iSprites)
		{
		iSprites->ResetAndDestroy();
		delete iSprites;
		iSprites = NULL;
		}

	delete iSpriteImage;
	iSpriteImage = NULL;

	delete iSpriteMask;
	iSpriteMask = NULL;
    }


void CGraphicsAppView::SetUpSpritesL()
	{
    ASSERT(iSpriteImage);
	ASSERT(iSprites);

	//Create the sprites
	CSprite* sprite = NULL;

	sprite = CSprite::NewLC(KInitialXSpeed,KInitialYSpeed,Rect().iTl);
	iSprites->AppendL(sprite);
	CleanupStack::Pop(sprite);

	sprite = CSprite::NewLC(-KInitialXSpeed,-KInitialYSpeed,Rect().iBr - iSpriteImage->SizeInPixels());
	iSprites->AppendL(sprite);
	CleanupStack::Pop(sprite);

	sprite = CSprite::NewLC(-KInitialXSpeed,KInitialYSpeed,Rect().iTl + iSpriteImage->SizeInPixels());
	iSprites->AppendL(sprite);
	CleanupStack::Pop(sprite);
	}


// Draw this application's view to the screen
void CGraphicsAppView::Draw(const TRect& /*aRect*/) const
    {
	// The system GC will already be activated when this function is called by the framework
	UpdateDisplay();
    }


void CGraphicsAppView::UpdateDisplay() const
    {
    CWindowGc& gc = SystemGc();

    if (!iUsingOffScreenBitmap)
        {
        // Blit the background image onto the screen at the top left position
        gc.BitBlt(Rect().iTl,iBackgroundImage);

        // Blit the sprites on top of it using their mask to retain the background where necessary
        TRect sourceRect(TPoint(0,0),iSpriteImage->SizeInPixels());
        for (TInt count = 0;count<iSprites->Count();count++)
            {
            gc.BitBltMasked(iSprites->At(count)->Position(),iSpriteImage,sourceRect,iSpriteMask,ETrue);
            }
        }
    else
        {
        // Blit the background image onto the off screen bitmap at the top left position
        iOffScreenBitmapGc->BitBlt(TPoint(0,0),iBackgroundImage);

        // Blit the sprites on top of it using its mask to retain the background where necessary
        for (TInt count = 0;count<iSprites->Count();count++)
            {
            NBitmapMethods::BitBltMaskedEntireBitmap(*iOffScreenBitmapGc,iSprites->At(count)->Position(),*iSpriteImage,*iSpriteMask);
            }

        // Blit the offscreen image onto the screen at the top left position
        gc.BitBlt(Rect().iTl,iOffScreenBitmap);
        }
    }


void CGraphicsAppView::StopDemo()
	{
	//Stop the timer if it is active
	if (iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Cancel();
		}
	}


void CGraphicsAppView::StartOffScreenDemo()
	{
	iUsingOffScreenBitmap = ETrue;
	StartTimer();
	}
	

void CGraphicsAppView::StartNoOffScreenDemo()
	{
	iUsingOffScreenBitmap = EFalse;
	StartTimer();
	}


void CGraphicsAppView::StartTimer()
	{
	//If the timer is not already running, start it
	if (!iPeriodicTimer->IsActive())
		{
		iPeriodicTimer->Start(1,1,TCallBack(CGraphicsAppView::Period,this));
		}

	}


void CGraphicsAppView::DoPeriodTask()
	{
	//Move the sprites
	for (TInt count = 0;count<iSprites->Count();count++)
		{
		iSprites->At(count)->Move(iSpriteImage->SizeInPixels(),Rect());
		}

	// Update the screen
	CWindowGc& gc = SystemGc();
	gc.Activate(*DrawableWindow());
	UpdateDisplay();
	gc.Deactivate();
	}


// This function is called by the periodic timer
TInt CGraphicsAppView::Period(TAny * aPtr)
	{
    ((CGraphicsAppView*)aPtr)->DoPeriodTask();
    //returning a value of TRUE indicates the callback should be done again
	return TRUE;
	}
