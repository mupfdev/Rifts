/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __GRAPHICSAPPVIEW_H__
#define __GRAPHICSAPPVIEW_H__

#include <coecntrl.h>


class CSprite;


/*! 
  @class CGraphicsAppView
  
  @discussion An instance of the Application View object for the Graphics 
  example application
  */
class CGraphicsAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CGraphicsAppView object
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CGraphicsAppView
  */
    static CGraphicsAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CGraphicsAppView object
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CGraphicsAppView
  */
    static CGraphicsAppView* NewLC(const TRect& aRect);

/*!
  @function ~CGraphicsAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CGraphicsAppView();


public: //new functions

/*!
  @function StartOffScreenDemo
  
  @discussion Begin the demo using an off screen bitmap
  */
	void StartOffScreenDemo();


/*!
  @function StartNoOffScreenDemo
  
  @discussion Begin the demo without using an off screen bitmap
  */
	void StartNoOffScreenDemo();


/*!
  @function StopDemo
  
  @discussion Stop animation
  */
	void StopDemo();


private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CGraphicsAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CGraphicsAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CGraphicsAppView();


private: // from CCoeControl

/*!
  @function Draw
  
  @discussion Draw this CGraphicsAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;



private: //new functions

/*!
  @function DoPeriodTask
  
  @discussion Called by period task static function
  */
	void DoPeriodTask();

/*!
  @function Period
  
  @discussion Call back function for a periodic timer
  @param aPtr a parameter passed to the timer when the timer is started
  */
	static TInt Period(TAny* aPtr);

/*!
  @function UpdateDisplay
  
  @discussion Perfom the drawing, does not activate the GC
  */
	void UpdateDisplay() const;

/*!
  @function SetUpSpritesL
  
  @discussion Initialise the objects being drawn
  */
	void SetUpSpritesL();


/*!
  @function StartTimer
  
  @discussion Starts the timer
  */
	void StartTimer();


private:

	/** background bitmap */
	CFbsBitmap* iBackgroundImage;
	/** "sprite" image */
	CFbsBitmap* iSpriteImage;
	/** "sprite" mask */
	CFbsBitmap* iSpriteMask;
	
	/** off screen bitmap */
	CFbsBitmap* iOffScreenBitmap;
	/** off screen bitmap device */
	CFbsBitmapDevice* iOffScreenBitmapDevice;
	/** off screen bitmap gc */
	CFbsBitGc* iOffScreenBitmapGc;

	/** periodic timer used to control the animation */
	CPeriodic* iPeriodicTimer;

	/** flag to keep track of whether or not the demo is using an off screen bitmap */
	TBool iUsingOffScreenBitmap;

	/** sprites */
	CArrayPtrFlat<CSprite>* iSprites;

    };


#endif // __GRAPHICSAPPVIEW_H__
