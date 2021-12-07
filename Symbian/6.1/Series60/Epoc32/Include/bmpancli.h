// BMPANCLI.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


#if !defined(__BMPANCLI_H__)
#define __BMPANCLI_H__


//
// CFrameData
//

/*
 * The CFrameData class encapsulates the animation data for one frame. It has a bitmap and
 * its relative mask, a time expressed in milliseconds which specifies for how long the frame
 * should be displayed and a position relative to the animation window.
 *
 * @internal
 * Internal to Symbian
 *
 */
class CBitmapFrameData : public CBase
	{
public:
	IMPORT_C ~CBitmapFrameData();
	IMPORT_C static CBitmapFrameData* NewL();
	IMPORT_C static CBitmapFrameData* NewL(CFbsBitmap* aBitmap, CFbsBitmap* aMask=NULL);
	IMPORT_C static CBitmapFrameData* NewL(CFbsBitmap* aBitmap, CFbsBitmap* aMask, TInt aIntervalInMilliSeconds, TPoint aPosition);
//
	IMPORT_C void SetBitmap(CFbsBitmap* aBitmap);
	IMPORT_C void SetMask(CFbsBitmap* aMask);
	IMPORT_C void SetPosition(TPoint aPosition);
	IMPORT_C void SetInterval(TInt aIntervalInMilliSeconds);
	IMPORT_C void SetBitmapsOwnedExternally(TBool aOwnedExternally);
//
	IMPORT_C CFbsBitmap* Bitmap() const;
	IMPORT_C CFbsBitmap* Mask() const;
	IMPORT_C TInt IntervalInMilliSeconds() const;
	IMPORT_C TPoint Position() const;
	IMPORT_C TBool BitmapsOwnedExternally() const;
private:
	CBitmapFrameData();
private:
	CFbsBitmap* iBitmap;
	CFbsBitmap* iMaskBitmap;
	TBool iBitmapsOwnedExternally;
	TInt iIntervalInMilliSeconds;
	TPoint iPosition;
	};




//
// CBitmapAnimClientData
//

/*
 * The CBitmapAnimClientData  class encapsulates the animation data, which includes general
 * attributes, a list of frames used for the animation and a background frame. The general
 * attributes consist of a frame interval, a flash mode and a play-mode. The first one is used
 * as constant interval between each frame and it is expressed in milliseconds. The second one
 * determines whether the animation should flash or not. The third one determines the play mode.
 *
 * @internal
 * Internal to Symbian
 *
 */
class CBitmapAnimClientData : public CBase
	{
public:
	enum TPlayMode
		{
		EPlay		= 0x00,
		ECycle		= 0x01,
		EBounce		= 0x02
		};
public:
	IMPORT_C static CBitmapAnimClientData* NewL();
	IMPORT_C ~CBitmapAnimClientData();
//
	IMPORT_C void AppendFrameL(CBitmapFrameData* aFrame);
	IMPORT_C void ResetFrameArray();
	IMPORT_C void SetBackgroundFrame(CBitmapFrameData* aBackgroundFrame);
	IMPORT_C void SetFlash(TBool aFlash);
	IMPORT_C void SetFrameInterval(TInt aFrameIntervalInMilliSeconds);
	IMPORT_C void SetPlayMode(TPlayMode aPlayMode);
//
	IMPORT_C CBitmapFrameData* BackgroundFrame() const;
	IMPORT_C TBool Flash() const;
	IMPORT_C const CArrayPtrFlat<CBitmapFrameData>& FrameArray() const;
	IMPORT_C TInt FrameIntervalInMilliSeconds() const;
	IMPORT_C TPlayMode PlayMode() const;
//
	IMPORT_C TInt DurationInMilliSeconds() const;
	IMPORT_C TSize Size() const;
private:
	CBitmapAnimClientData();
private:
	TBool iFlash;
	TPlayMode iPlayMode;
	TInt iFrameIntervalInMilliSeconds;
	CArrayPtrFlat<CBitmapFrameData> iFrameArray;
	CBitmapFrameData* iBackgroundFrame;
	};



/*
 * The RBitmapAnim class is used to allow the communication between the client and the server.
 * This communication is performed by packaging the data and then sending it to the player.
 *
 * @internal
 * Internal to Symbian
 *
 */
class RBitmapAnim : public RAnim
	{
public:
	IMPORT_C RBitmapAnim(RAnimDll& aAnimDll);
	IMPORT_C void ConstructL(const RWindowBase& aWindow);
	IMPORT_C void DisplayFrameL(TInt aIndex);
	IMPORT_C void SetBitmapAnimDataL(const CBitmapAnimClientData& aBitmapAnimData);
	IMPORT_C void SetFlashL(TBool aFlash);
	IMPORT_C void SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds);
	IMPORT_C void SetPlayModeL(CBitmapAnimClientData::TPlayMode aPlayMode);
	IMPORT_C void StartL();
	IMPORT_C void StopL();
	IMPORT_C void SetNumberOfCyclesL(TInt aNumberOfCycles);
	IMPORT_C void SetPositionL(TPoint aPosition);
private:
	void SetAttributesL(const CBitmapAnimClientData& aBitmapAnimData);
	void SetBackgroundFrameL(const CBitmapFrameData& aFrame);
	void SetFrameArrayL(const CArrayPtrFlat<CBitmapFrameData>& aFrameArray);
	void SetFrameL(const CBitmapFrameData& aFrame, TInt aOpCode);
	};

#endif

