// W32ADLL.H
//
// Copyright (c) 1995-2000 Symbian Ltd.  All rights reserved.
//

// Started by 1, August 1995, last code change March 2000
//
// Header for writing animated DLL add ons
//

#if !defined(__W32ADLL_H__)
#define __W32ADLL_H__

#if !defined(__W32STD_H__)
#include <w32std.h>
#endif

#if !defined(__BITSTD_H__)
#include <bitstd.h>
#endif


const TUint KWservAnimDllUidValue8=268435858;
const TUid KWservAnimDllUid8={KWservAnimDllUidValue8};
const TUint KWservAnimDllUidValue16=268450594;
const TUid KWservAnimDllUid16={KWservAnimDllUidValue16};
#if defined(_UNICODE)
const TUint KWservAnimDllUidValue=KWservAnimDllUidValue16;
#else
const TUint KWservAnimDllUidValue=KWservAnimDllUidValue8;
#endif
const TUid KWservAnimDllUid={KWservAnimDllUidValue};

//
// Contains functions callable from animated DLL's
//

class TWindowInfo
	{
public:
	TRect iScreenPos;
	TDisplayMode iMode;
private:
	TAny *iFree1;
	TAny *iFree2;
	};

class MEventHandler
	{
public:
	virtual TBool OfferRawEvent(const TRawEvent &aRawEvent)=0;
	};

class MAnimGeneralFunctions
	{
public:
	enum TAnimSync	// The animator can be synchronised to any of the below, the Animate() call will take place
		{			// at the start of the new unit (day, hour, etc..)
		ESyncNone,			// Not synchronised
		ESyncFlash,			// Animate() called twice a second, on the second and on seven o'clock
		ESyncSecond,		// Animate() called every second
		ESyncMinute,		// Animate() called every minute
		ESyncDay,			// Animate() called every day
		};
	//Timing functions
	virtual void Animate(TDateTime *aDateTime)=0; // Trigger a call to the DLL's Animate function
	virtual void SetSync(TAnimSync aSyncMode)=0;
	virtual void SetInterval(TInt aInterval)=0;		// Set the regular repeat interval, does not affect the current countdown
	virtual void SetNextInterval(TInt aInterval)=0;	// Sets the interval to the next Animate, after that it will fall back to the usual rate
	virtual TDateTime SystemTime() const=0;			// Return the system time as it was when Animate last called
	virtual TBool FlashStateOn() const=0;			// Return ETrue if in the on part of the flash cycle
	virtual TAnimSync Sync() const=0;							// Return the current sync mode
	//Other functions generally useful
	virtual const CFbsScreenDevice *ScreenDevice()=0;		// Pointer to screen device
	virtual CFbsBitmap *DuplicateBitmapL(TInt aHandle)=0;	// Create and duplicate a bitmap from a handle
	virtual CFbsFont *DuplicateFontL(TInt aHandle)=0;	// Create and duplicate a font from a handle
	virtual void CloseFont(CFbsFont *)=0;				// Close a font duplicated by DuplicateFontL
	virtual const RThread &Client()=0;					// Return a reference to the calling clients thread
	virtual void ReplyBuf(const TDesC8 &aDes)=0;				// Reply a buffer to the client
#if defined(_UNICODE)
	virtual void ReplyBuf(const TDesC16 &aDes)=0;				// Reply a buffer to the client
#endif
	virtual void Panic() const=0;							// Trigger a client panic
	//Event functions
	virtual void GetRawEvents(TBool aGetEvents) const=0;	// Switch On/Off raw event are passing to CAnim::OfferRawEventL
	virtual void PostRawEvent(const TRawEvent &aRawEvent) const=0;	// Create an event just as if it had come from the kernal
	virtual void PostKeyEvent(const TKeyEvent &aRawEvent) const=0;	// Send a key event
private:
	virtual void Reserved1() const;
	virtual void Reserved2() const;
	};

class MAnimWindowFunctions
	{
public:
	virtual void ActivateGc()=0;					// Activate the GC to enable drawing in a command or animate function
	virtual void SetRect(const TRect &aRect)=0;		// Sets the rect that this instance wants to draw to.
	virtual TSize WindowSize() const=0;				// Return the window size
	virtual TBool IsHidden()=0;
	virtual void SetVisible(TBool aState)=0;
	virtual void Invalidate(const TRect &aRect)=0;
	virtual void Parameters(TWindowInfo &aData)=0;
	virtual void VisibleRegion(TRegion& aRegion)=0;
	//virtual void CopyScreen(CFbsBitGc *aBitmapGc,TRect aRect)=0;
private:
	virtual void Reserved() const;
	};

class MAnimFreeTimerWindowFunctions : public MAnimWindowFunctions
	{
public:
	virtual void DeactivateGc()=0;					// Deactivate the GC after drawing from our own RunL
	virtual void Update()=0;
private:
	virtual void Reserved3() const;
	};

class MAnimSpriteFunctions
	{
public:
	virtual TSpriteMember *GetSpriteMember(TInt aMember) const=0;		//Returns sprite member data
	virtual void UpdateMember(TInt aMember,const TRect& aRect,TBool aFullUpdate)=0;		//Redraw of part of a sprite
	virtual void Activate(TBool aActive)=0;		// Turn sprite on or off
	virtual void SizeChangedL()=0;			//Finish constructing sprite (must be called after members are sized or change size)
	virtual void SetPosition(const TPoint &aPos)=0;			//Change the positon of the sprite
private:
	virtual void Reserved() const;
	};

class CAnimGc : public CBitmapContext
	{
public:
	virtual void SetClippingRegion(const TRegion &aRegion)=0;
	virtual void CancelClippingRegion()=0;
	};

class CWsAnim; // Forward ref for friend declaration
//
//	Base class to derive server side Animated DLL instances from.
//
class CAnim : public CBase , public MEventHandler
	{
public:
	virtual TInt CommandReplyL(TInt aOpcode, TAny *aArgs)=0;
	virtual void Command(TInt aOpcode, TAny *aArgs)=0;
	virtual void Animate(TDateTime *aDateTime)=0;
private:
	inline CAnim() {}
protected:
	MAnimGeneralFunctions *iFunctions;
	friend class CWsAnim;
	friend class CWindowAnim;
	friend class CSpriteAnim;
	};

class CWindowAnim : public CAnim
	{
public:
	virtual void ConstructL(TAny *aArgs, TBool aHasFocus)=0;
	virtual void Redraw()=0;
	virtual void FocusChanged(TBool aState)=0;
protected:
	inline CWindowAnim() {}
	MAnimWindowFunctions *iWindowFunctions;
	CAnimGc *iGc;
	friend class CWsAnim;
	};

class CFreeTimerWindowAnim : public CWindowAnim
	{
protected:
	inline MAnimFreeTimerWindowFunctions* WindowFunctions()
		{return STATIC_CAST(MAnimFreeTimerWindowFunctions*,iWindowFunctions);}
	};

class CSpriteAnim : public CAnim
	{
public:
	virtual void ConstructL(TAny *aArgs)=0;
protected:
	inline CSpriteAnim() {}
	MAnimSpriteFunctions *iSpriteFunctions;
	friend class CWsAnim;
	};

//
// Base class to derive server side Animated DLL classes from
//
class CAnimDll : public CBase
	{
public:
	virtual CAnim *CreateInstanceL(TInt aType)=0;
	};

#endif
