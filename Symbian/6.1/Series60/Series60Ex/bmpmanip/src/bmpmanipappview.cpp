/* Copyright (c) 2001, Nokia. All rights reserved */
#include <eikenv.h>
#include <gdi.h>

#include "BmpmanipAppView.h"
#include "EikonEnvironment.h"

//file to load in
_LIT(KGifFileName,"c:\\System\\Apps\\Bmpmanip\\image1.gif");
//file to save
_LIT(KBmpFileName,"c:\\System\\Apps\\Bmpmanip\\newimage.bmp");

static const TDisplayMode KDeviceColourDepth = EColor4K;
//gif file frame index (in this case there is only one frame)
static const TInt KGifFrameIndex = 0;

//new size to scale image
static const TInt KNewImageWidth = 150;
static const TInt KNewImageHeight = 150;


// Standard Epoc construction sequence
CBmpmanipAppView* CBmpmanipAppView::NewL(const TRect& aRect)
    {
    CBmpmanipAppView* self = CBmpmanipAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CBmpmanipAppView* CBmpmanipAppView::NewLC(const TRect& aRect)
    {
    CBmpmanipAppView* self = new (ELeave) CBmpmanipAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

void CBmpmanipAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);

    // Activate the window, which makes it ready to be drawn
    ActivateL();

	iBitmap = new (ELeave) CFbsBitmap();

	iRotator = CMdaBitmapRotator::NewL();
	iFileSaver = CMdaImageBitmapToFileUtility::NewL(*this);
	iScaler = CMdaBitmapScaler::NewL();

	iConverter = CMdaImageFileToBitmapUtility::NewL(*this);
	//Start an asynchronous process to open the gif file
	iConverter->OpenL(KGifFileName);
    }

CBmpmanipAppView::CBmpmanipAppView()
:	iConvertState(EConvertStateNull)
    {
    }


CBmpmanipAppView::~CBmpmanipAppView()
    {
	delete iFileSaver;
	iFileSaver = NULL;

	delete iRotator;
	iRotator = NULL;

    delete iScaler;
	iScaler = NULL;
	
	delete iConverter;
	iConverter = NULL;

	delete iBitmap;
	iBitmap = NULL;
    }


//Draw this applications view to the screen
void CBmpmanipAppView::Draw(const TRect& /*aRect*/) const
    {
    // clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear(Rect());

	//if the bitmap is not currently being processed in any way
	if (iConvertState == EConvertStateReady || iConvertState == EConvertStateSaving)
		{
		gc.BitBlt(Rect().iTl,iBitmap);
		}
    }


void CBmpmanipAppView::RotateImageClockwiseL(TImageRotateAngle aAngle)
	{
	if (iConvertState != EConvertStateReady)
		{
		//Inform the UI that the gif file is still being loaded
		User::Leave(KErrInUse);
		}

	switch (aAngle)
		{
	case E90Degrees:
		//Start an asynchronous process to rotate the bitmap
		iRotator->RotateL(*this,*iBitmap,CMdaBitmapRotator::ERotation90DegreesClockwise);
		iConvertState = EConvertStateRotating;
		break;
	case E180Degrees:
		//Start an asynchronous process to rotate the bitmap
		iRotator->RotateL(*this,*iBitmap,CMdaBitmapRotator::ERotation180DegreesClockwise);
		iConvertState = EConvertStateRotating;
		break;
	case E270Degrees:
		//Start an asynchronous process to rotate the bitmap
		iRotator->RotateL(*this,*iBitmap,CMdaBitmapRotator::ERotation270DegreesClockwise);
		iConvertState = EConvertStateRotating;
		break;
	default:
		ASSERT(FALSE);
		}
	}


void CBmpmanipAppView::SaveL()
	{
	if (iConvertState != EConvertStateReady)
		{
		return;
		}

	//Start an asyncronous process to create a file for the bitmap
	//Note this does not save the actual bitmap - this is done once the file has been created
	iFileSaver->CreateL(KBmpFileName,&iClipFormat,&iCodec,&iCodec);
	iConvertState = EConvertStateSaving;
	}


//This function is called when the gif file has been opened or an error has occured in the process
void CBmpmanipAppView::MiuoOpenComplete(TInt aError)
	{
	if (aError == KErrNone)
		{
		iConvertState = EConvertStateConvertingFromGif;
		
		TFrameInfo frameInfo;
		//Get the frame info
		iConverter->FrameInfo(KGifFrameIndex,frameInfo);
		
		//Create a bitmap based on the size of the gif
		TInt err = iBitmap->Create(frameInfo.iOverallSizeInPixels,KDeviceColourDepth);
		if (err == KErrCouldNotConnect)
			{
			NEikonEnvironment::MessageBox(_L("Could not connect to font and bitmap server"));
			return;
			}
		if (err == KErrArgument)
			{
			NEikonEnvironment::MessageBox(_L("Illegal Gif file size"));
			return;
			}

		//Convert the gif into a bitmap
		TRAPD(convertErr,iConverter->ConvertL(*iBitmap,KGifFrameIndex));
		
		//Trap error as this function cannot leave
		if (convertErr != KErrNone)
			{
			NEikonEnvironment::MessageBox(_L("Cannot initiate converter"));
			}

		}

	else if (aError == KErrUnderflow)
		{
		//This error occurs if the gif file contains insufficient information
		//This is usually because the file is being opened in a cache so a futher attempt to open
		//should be performed
		TRAPD(err,iConverter->OpenL(KGifFileName));
		if (err !=KErrNone)
			{
			NEikonEnvironment::MessageBox(_L("Gif file contains insufficient information, cannot retry"));
			}
		}

	else
		{
		NEikonEnvironment::MessageBox(_L("Error opening file"));
		}

	}

//This function is called whenever a conversion process has finished
void CBmpmanipAppView::MiuoConvertComplete(TInt aError)
	{
	switch (iConvertState)
		{
		//Finished converting gif file to bitmap
		case EConvertStateConvertingFromGif:
			ConvertingFromGifFinished(aError);
			break;
		//Finished saving file
		case EConvertStateSaving:
			SavingFinished(aError);
			break;
		//Finished Scaling file
		case EConvertStateScaling:
			ScalingFinished(aError);
			break;
		//Finished Rotating file
		case EConvertStateRotating:
			RotatingFinished(aError);
			break;
		case EConvertStateNull:
		default:
			ASSERT(FALSE);
		}

	}

//This function is called when the bitmap (output) file has been created
void CBmpmanipAppView::MiuoCreateComplete(TInt aError)
	{
	if (aError == KErrNone)
		{
		//Now the bitmap file has been created, write the bitmap to it
		TRAPD(err,iFileSaver->ConvertL(*iBitmap));

		if (err != KErrNone)
			{
			NEikonEnvironment::MessageBox(_L("Conversion could not be started"));
			}
		}
	else
		{
		//Reset state so that other operations can still be performed
		iConvertState = EConvertStateReady;
		NEikonEnvironment::MessageBox(_L("File Could not be created"));
		}
	}

//This function is called when conversion has finished
void CBmpmanipAppView::ConvertingFromGifFinished(TInt aError)
	{
	if (aError == KErrNone)
		{	
		TRAPD(err,iScaler->ScaleL(*this,*iBitmap,TSize(KNewImageWidth,KNewImageHeight)));
		if (err == KErrNone)
			{
			iConvertState = EConvertStateScaling;
			}
		else
			{
			NEikonEnvironment::MessageBox(_L("Cannnot re scale image"));
			}
		}
	else
		{
			NEikonEnvironment::MessageBox(_L("Error converting file"));
		}
	}


//This function is called when saving has finished
void CBmpmanipAppView::SavingFinished(TInt aError)
	{
	if (aError == KErrNone)
		{
		iConvertState = EConvertStateReady;
		NEikonEnvironment::MessageBox(_L("File Saved"));
		}
	else
		{
		NEikonEnvironment::MessageBox(_L("Error saving image"));
		}
	}

//This function is called when scaling has finished
void CBmpmanipAppView::ScalingFinished(TInt aError)
	{
	if (aError == KErrNone)
		{
		iConvertState = EConvertStateReady;
		DrawNow();
		}
	else
		{
		NEikonEnvironment::MessageBox(_L("Error resizing image"));
		}
	}

//This function is called when rotation has finished
void CBmpmanipAppView::RotatingFinished(TInt aError)
	{
	if (aError == KErrNone)
		{
		iConvertState = EConvertStateReady;
		DrawNow();
		}
	else
		{
		NEikonEnvironment::MessageBox(_L("Error rotating image"));
		}
	}

