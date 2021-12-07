/*
* ============================================================================
*  Name     : AknBitmapAnimation.h
*  Part of  : Avkon
*
*  Description:
*  Copyright (c) 2002 Nokia. All rights reserved.
* ============================================================================
*/
// AKNBITMAPANIMATION.H
//
// Copyright (c) 1997-2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNBITMAPANIMATION_H__)
#define __AKNBITMAPANIMATION_H__

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#include <bmpancli.h>

class RAknBitmapAnim : public RBitmapAnim
	{
public:
	/**
	 * Constructor
	 */
	RAknBitmapAnim(RAnimDll& aAnimDll);

	/**
	 * Starts the animation, and displays the last frame when finished.
	 */
	void StartAndKeepLastFrameL();

	/**
	 * Stops the animation.
	 */
	TInt Stop();
	};

//forward declarations
class TResourceReader;

class CAknBitmapAnimation : public CCoeControl
	{
public:
	/**
	 * 2 phase construction.
	 */
	IMPORT_C static CAknBitmapAnimation* NewL();

	/**
	 * Destructor.
	 */
	IMPORT_C virtual ~CAknBitmapAnimation();
public:
	/**
	 * gives access to RBitmapAnimation.
	 */
	IMPORT_C RBitmapAnim& Animation();

	/**
	 * gives access to CBitmapAnimClientData.
	 */
	IMPORT_C CBitmapAnimClientData* BitmapAnimData() const;

	/**
	 * Cancels the animation.
	 */
	IMPORT_C TInt CancelAnimation();

	/**
	 * Sets the frame index.
	 */
	IMPORT_C void SetFrameIndexL(TInt aIndex);

	/**
	 * Sets the frame interval in milliSeconds.
	 */
	IMPORT_C void SetFrameIntervalL(TInt aFrameIntervalInMilliSeconds);

	/**
	 * Starts the animation.
	 */
	IMPORT_C void StartAnimationL();
public: 
	/**
	 * Set if the animation has started
	 */
	TInt AnimationHasStarted(TBool aHasStarted);
public: // from CCoeControl
	/**
	 * Construct animation from resource.
	 */
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aResourceReader);

	/**
	 * Minimum size.
	 */
	IMPORT_C virtual TSize MinimumSize();
private: // from CCoeControl
	virtual void SizeChanged();
	virtual void PositionChanged();
	virtual void Draw(const TRect& aRect) const;

private:
	CAknBitmapAnimation();
	void ConstructL();
	void CompleteAnimationInitialisationL();
	TBool IsInitialisationCompleted();
	CBitmapFrameData* CreateFrameDataFromResourceL(TResourceReader& aFramesReader, const TDesC& aFileName);
	void SetAnimationWindowL();
private: // timer
	static TInt AnimationStartedCallback(TAny* aPtr);

private:
	CBitmapAnimClientData* iBitmapAnimData;
	RAnimDll iAnimDll;
	RAknBitmapAnim iAnimation;
	TInt iFlags;
	TPtrC iFileName;
	CPeriodic* iTimer;
	TInt iSpare;
	};

#endif
