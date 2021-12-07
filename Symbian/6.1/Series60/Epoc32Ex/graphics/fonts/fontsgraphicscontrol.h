// FontsGraphicsControl.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.

#ifndef __FontsGraphicsControl_H
#define __FontsGraphicsControl_H

#include <coecntrl.h>
#include <s32file.h>
#include "CommonGraphicsControlFramework.h"


class CSmileyPicture : public CPicture
	{
public:
	enum TMood { EHappy, ENeutral, ESad }; // various moods
	enum TSizeSpec { ELarge, EMedium, ESmall }; // sizes

	// creating
	CSmileyPicture();
	static CSmileyPicture* NewL(TMood aMood, TSizeSpec aSizeSpec); // from scratch
	static CSmileyPicture* NewL(const CStreamStore& aStore, TStreamId aStreamId); // from stream
	TStreamId StoreL(CStreamStore& aStore) const;
	void Draw(CGraphicsContext& aGc,const TPoint& aTopLeft,const TRect& aClipRect,
						MGraphicsDeviceMap* aMap)const; 

	void SetMood(TMood aMood); // set mood
	TMood Mood(); // get mood
	void SetSize(TSizeSpec aSizeSpec);	// set size
	TSizeSpec Size(); // get size
	TInt SpecToFactor() const;

	void GetOriginalSizeInTwips(TSize& aSize) const;

	// only needed for cropping and scaling
	void SetScaleFactor(TInt aScaleFactorWidth,TInt aScaleFactorHeight);
	void SetCropInTwips(const TMargins& aMargins);
	TPictureCapability Capability() const;
	void GetCropInTwips(TMargins& aMargins) const;
	TInt ScaleFactorWidth() const;
	TInt ScaleFactorHeight() const;
private:
	// streaming
	void ExternalizeL(RWriteStream& aStream) const;		// externalize state
	void InternalizeL(RReadStream& aStream);			// internalize state
private:
	// member data - size and details of whether happy or sad
	TMood iMood;
	TSizeSpec iSizeSpec;
	};

// sundry derived classes

class CHelloControl : public CGraphicExampleControl
	{
public:
	CHelloControl() { SetMaxPhases(7); };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
	};

class CPictureControl : public CGraphicExampleControl
	{
public:
	CPictureControl();
	~CPictureControl() { delete(iPicture); };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	enum TDocStatus { EFalse, EHeader, EPicture };
	TStreamId StoreHeaderL(CStreamStore& aStore) const;
	void StoreHeaderComponentsL(CStoreMap& aMap,CStreamStore& aStore) const;
	void RestoreHeaderL(CStreamStore& aStore, TStreamId aId);

	TZoomFactor testZf;
	MGraphicsDeviceMap* testMap;

	TDocStatus iValidDocument; // if false, then Draw() draws gray screen
	CSmileyPicture* iPicture; // if there, then draw
	TPictureHeader iHeader; // if no iPicture, draw outline to specified size
	TPoint iOffset; // offset of picture from top-left
	CFileStore* iStore; // stream store for persistence
	TStreamId iHeaderId;  // root stream of store
	};

class CFontControl : public CGraphicExampleControl
	{
public:
	CFontControl();
	~CFontControl() { };
	void UpdateModelL();
	void Draw(const TRect& aRect) const;
private:
	MGraphicsDeviceMap* iDeviceMap;
	TZoomFactor iZoomFactor;
	TInt iNumTypefaces;
	TBuf<19> iCurrentFont;
	};

#endif
