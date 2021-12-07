// Picture.cpp
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#include "EmbeddingGraphicsControl.h"
#include <coemain.h>

// for the store
#include <s32std.h>

static const TUid KUidExampleSmileyPicture = { 0x100000E6 } ;

/*
	CExamplePictureFactory

	Give picture header, checks UID and only if it's KUidExampleSmileyPicture will this restore
	a picture - changing the swizzle in aHeader from a stream id into a pointer.
	[incidentally, what errors should result if either the picture is already restored, or the UID
	isn't recognized?]
*/

class TExamplePictureFactory : public MPictureFactory
	{
public:
	void NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore) const;
	};

void TExamplePictureFactory::NewPictureL(TPictureHeader& aHeader,const CStreamStore& aDeferredPictureStore) const
	{
	if (aHeader.iPictureType == KUidExampleSmileyPicture)
		{
		// restore new picture from store into the TSwizzle
		// (which changes from stream id to pointer)
		// Construct a CSmileyPicture object and restore from the stream
	    if (aHeader.iPicture.IsId())
			aHeader.iPicture = CSmileyPicture::NewL(aDeferredPictureStore,aHeader.iPicture.AsId());
			
		}
	else
		{
			// output error and panic
			User::Leave(KErrNoMemory);
		}
	}

// implementation of the CSmileyPicture class

CSmileyPicture::CSmileyPicture()
	{
	// do nothing
	}

CSmileyPicture* CSmileyPicture::NewL(TMood aMood, TSizeSpec aSizeSpec)
	{
	CSmileyPicture* self = new (ELeave) CSmileyPicture();
	self->iMood = aMood;
	self->iSizeSpec = aSizeSpec;
	return self;
	}

CSmileyPicture* CSmileyPicture::NewL(const CStreamStore& aStore, TStreamId aStreamId) 
// create from store
	{
	RStoreReadStream inStream;
	inStream.OpenLC(aStore,aStreamId);
	CSmileyPicture* self = new (ELeave) CSmileyPicture();
	self->InternalizeL(inStream);
	CleanupStack::PopAndDestroy();
	return self;
	}

TStreamId CSmileyPicture::StoreL(CStreamStore& aStore) const
// stores the CSmileyPicture in a new stream of the specified store (using ExternalizeL())
	{
	RStoreWriteStream stream;
	TStreamId id=stream.CreateLC(aStore);
	ExternalizeL(stream);  
	stream.CommitL();
	CleanupStack::PopAndDestroy();
	return id;
	}

void CSmileyPicture::ExternalizeL(RWriteStream& aStream) const
	{
	aStream.WriteInt8L(iMood);
	aStream.WriteInt8L(iSizeSpec);
	}

void CSmileyPicture::InternalizeL(RReadStream& aStream)
	{
	iMood = TMood(aStream.ReadInt8L());
	iSizeSpec = TSizeSpec(aStream.ReadInt8L());
	}

TInt CSmileyPicture::SpecToFactor() const
	{
	switch (iSizeSpec)
		{
		case ESmall:
			return 1;
			break;
		case EMedium:
			return 2;
			break;
		case ELarge:
			return 3;
			break;
		default:
			return 0;
		}
	}

void CSmileyPicture::Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
						MGraphicsDeviceMap* /*aMap*/) const
	{
	aGc.SetClippingRect(aClipRect);  

	TInt scaleFactor = SpecToFactor();

	TSize penSizeBold(3*scaleFactor,3*scaleFactor);
	TSize penSizeFat(5*scaleFactor,5*scaleFactor);
	aGc.SetPenSize(penSizeFat);

	TInt leftOffset = 13*scaleFactor;
	TInt rightOffset = 27*scaleFactor;
	TInt circleSize = 40*scaleFactor;
	TInt shrinkSize = 10*scaleFactor;
	TInt halfCircle = 20*scaleFactor;
	TInt neutralSize = 13*scaleFactor;

	TPoint leftEye(aTopLeft.iX+leftOffset,aTopLeft.iY+leftOffset);
	TPoint rightEye(aTopLeft.iX+rightOffset,aTopLeft.iY+leftOffset);
	aGc.Plot(leftEye);
	aGc.Plot(rightEye);
	aGc.SetPenSize(penSizeBold);
	TRect circle(aTopLeft,TPoint(aTopLeft.iX+circleSize,aTopLeft.iY+circleSize));
	aGc.DrawEllipse(circle);

	// draw the smile
	TRect smile = circle;
	switch (iMood)
		{
		case EHappy:
			{
			smile.Shrink(shrinkSize,shrinkSize);
			aGc.DrawArc(smile,TPoint(aTopLeft.iX,aTopLeft.iY+circleSize-shrinkSize),TPoint(aTopLeft.iX+circleSize,aTopLeft.iY+circleSize-shrinkSize));
			}
			break;
		case ENeutral:
			{
			aGc.DrawLine(TPoint(leftEye.iX,leftEye.iY+neutralSize),TPoint(rightEye.iX,rightEye.iY+neutralSize));
			}
			break;
		case ESad:
			{
			smile.Shrink(shrinkSize,shrinkSize);
			smile.Move(0,15*scaleFactor);
			aGc.DrawArc(smile,TPoint(aTopLeft.iX+circleSize,aTopLeft.iY+halfCircle),TPoint(aTopLeft.iX,aTopLeft.iY+halfCircle));
			}
			break;
		}
	}

void CSmileyPicture::SetMood(TMood aMood)
	{
	iMood = aMood;	
	}

CSmileyPicture::TMood CSmileyPicture::Mood()
	{
	return iMood;
	}

void CSmileyPicture::SetSize(TSizeSpec aSizeSpec)
	{
	iSizeSpec = aSizeSpec;	
	}

CSmileyPicture::TSizeSpec CSmileyPicture::Size()
	{
	return iSizeSpec;
	}

void CSmileyPicture::GetOriginalSizeInTwips(TSize& aSize)const
	{
	// do nothing
	}


void CSmileyPicture::SetScaleFactor(TInt /*aScaleFactorWidth*/,TInt /*aScaleFactorHeight*/)
	{
	// do nothing
	}


TInt CSmileyPicture::ScaleFactorWidth()const
	{
	return 1;
	}


TInt CSmileyPicture::ScaleFactorHeight()const
	{
	return 1;
	}


void CSmileyPicture::SetCropInTwips(const TMargins& /*aMargins*/)
	{
	// do nothing
	}


void CSmileyPicture::GetCropInTwips(TMargins& aMargins)const
	{
	CPicture::GetCropInTwips(aMargins); // no crop
	}

TPictureCapability CSmileyPicture::Capability()const
	{
	return CPicture::Capability(); // no scale, no crop
	}

// example really starts here
CPictureControl::CPictureControl()
	{ 
	SetMaxPhases(7);
	iValidDocument = CPictureControl::EPicture;
	iOffset = TPoint(50,50);
	}

// The file name
_LIT(KFileName,"C:\\grpict.dat");

// Literal text
_LIT(KTxtUpdateModelCase0,"draw happy face at (50,50)");
_LIT(KTxtUpdateModelCase1,"draw sad face at (50,50)");
_LIT(KTxtUpdateModelCase2,"draw neutral face at (50,50)");
_LIT(KTxtUpdateModelCase3,"store picture in file");
_LIT(KTxtUpdateModelCase4,"delete picture from memory");
_LIT(KTxtUpdateModelCase5,"restore picture header from file");
_LIT(KTxtUpdateModelCase6,"restore picture from file");

void CPictureControl::UpdateModelL()
	{
	// set up zoom factor object
	testZf.SetGraphicsDeviceMap(iCoeEnv->ScreenDevice());
	// set the zoom factor of the object
	testZf.SetZoomFactor(TZoomFactor::EZoomOneToOne);
	// use graphics device maps for drawing and getting fonts
	testMap=&testZf;

	// the file session used in the example
	RFs fsSession;
	TParse filestorename;
	
	switch (Phase())
		{
		case 0:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase0);
			iPicture = CSmileyPicture::NewL(CSmileyPicture::EHappy,CSmileyPicture::ESmall);
			break;
		case 1:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase1);
			iPicture->SetMood(CSmileyPicture::ESad);
			iPicture->SetSize(CSmileyPicture::EMedium);
			break;
		case 2:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase2);
			iPicture->SetMood(CSmileyPicture::ENeutral);
			iPicture->SetSize(CSmileyPicture::ELarge);
			break;
		case 3:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase3);
			// set up the permament direct file store for the picture
			fsSession.Connect();
			
			// Create (replace, if it exists) the direct file store
			fsSession.Parse(KFileName,filestorename);
			iStore = CDirectFileStore::ReplaceLC(fsSession,filestorename.FullName(),EFileWrite);
			// Must say what kind of file store.
			iStore->SetTypeL(KDirectFileStoreLayoutUid);

			// create picture header
			iHeader.iPicture = iPicture;
			iHeader.iSize = TSize(iPicture->SpecToFactor()*40,iPicture->SpecToFactor()*40);
			iHeader.iPictureType = KUidExampleSmileyPicture;

			// store picture header and picture
			iHeaderId = StoreHeaderL(*iStore);
			// make header stream the root stream
			iStore->SetRootL(iHeaderId);

			// close store
			CleanupStack::PopAndDestroy();
			fsSession.Close();
			break;
		case 4:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase4);
			delete iPicture;
			iPicture = NULL;
			iValidDocument = CPictureControl::EFalse;
			break;
		case 5:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase5);
			// set up the permament direct file store for the picture
			fsSession.Connect();
			
			// Open the direct file store and read the header
			fsSession.Parse(KFileName,filestorename);
			iStore = CDirectFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);

			RestoreHeaderL(*iStore,iStore->Root());
			// close store
			CleanupStack::PopAndDestroy();
			fsSession.Close();
			iValidDocument = CPictureControl::EHeader;
			break;
		case 6:
			iGraphObserver->NotifyStatus(KTxtUpdateModelCase6);

			fsSession.Connect();
			
			// Open the direct file store and read the header
			fsSession.Parse(KFileName,filestorename);
			iStore = CDirectFileStore::OpenLC(fsSession,filestorename.FullName(),EFileRead);
			
			TExamplePictureFactory factory;
			factory.NewPictureL(iHeader,*iStore);
						
			iPicture = (CSmileyPicture *) iHeader.iPicture.AsPtr();

			// close store
			CleanupStack::PopAndDestroy();
			fsSession.Close();
			iValidDocument = CPictureControl::EPicture;
			break;
		}
	}

void CPictureControl::RestoreHeaderL(CStreamStore& aStore, TStreamId aId)
	{
	RStoreReadStream stream;
	stream.OpenLC(aStore,aId);
	iHeader.InternalizeL(stream);
	CleanupStack::PopAndDestroy();		// close and delete the stream
	}

TStreamId CPictureControl::StoreHeaderL(CStreamStore& aStore) const
	{
	CStoreMap* map=CStoreMap::NewLC(aStore);
	StoreHeaderComponentsL(*map,aStore);

	RStoreWriteStream stream(*map);
	TStreamId id = stream.CreateLC(aStore);
	iHeader.ExternalizeL(stream);
	stream.CommitL();
	map->Reset();
	CleanupStack::PopAndDestroy(2);
	return id;
	}

void CPictureControl::StoreHeaderComponentsL(CStoreMap& aMap,CStreamStore& aStore) const
	{
	TStreamId id;

	id = iPicture->StoreL(aStore);
	aMap.BindL(iPicture,id);
	}

void CPictureControl::Draw(const TRect& /* aRect */) const
	{
	// draw surrounding rectangle
	CWindowGc& gc=SystemGc(); // graphics context we draw to
	gc.UseFont(iMessageFont); // use the system message font
	gc.Clear(); // clear the area to be drawn to
	SystemGc().DrawRect(Rect()); // surrounding rectangle to draw into
	TRect rect=Rect(); // a centered rectangle of the default size
	TRgb darkGray(85,85,85);

	// decide what to do, and do it
	switch (iValidDocument)
		{
	case CPictureControl::EFalse:
		// if document is not valid then Draw() draws gray screen
		gc.SetBrushColor(darkGray);
		gc.Clear(rect);
		break;
	case CPictureControl::EPicture:
		// if picture in is memory then draw it
		iPicture->Draw(gc,iOffset,rect,testMap);
		break;
	case CPictureControl::EHeader: 
		// if no iPicture, draw picture outline to specified size at iOffset
		TInt bottomRightX = iOffset.iX + iHeader.iSize.iWidth;
		TInt bottomRightY = iOffset.iY + iHeader.iSize.iHeight;
		TRect outlineBox(iOffset,TPoint(bottomRightX,bottomRightY));
	
		gc.SetPenStyle(CGraphicsContext::EDottedPen);
		gc.DrawRect(outlineBox);
		break;
		}

	//iConEnv->ScreenDevice()->ReleaseFont(iMessageFont);
	//gc.ReleaseFont(iMessageFont);
	//gc.DiscardFont(); // discard font
   	}
