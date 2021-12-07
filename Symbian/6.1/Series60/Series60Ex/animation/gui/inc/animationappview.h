/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __ANIMATIONAPPVIEW_H__
#define __ANIMATIONAPPVIEW_H__


#include <coecntrl.h>


/*! 
  @class CAnimationAppView
  
  @discussion An instance of the Application View object for the Animation 
  example application
  */
class CAnimationAppView : public CCoeControl
    {
public:  // New methods

/*!
  @function NewL
   
  @discussion Create a CAnimationAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CAnimationAppView
  */
    static CAnimationAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CAnimationAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CAnimationAppView
  */
    static CAnimationAppView* NewLC(const TRect& aRect);

/*!
  @function ~CAnimationAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CAnimationAppView();

public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CAnimationAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& /*aRect*/) const;
  

private: // New methods

/*!
  @function CAnimationAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CAnimationAppView();

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CAnimationAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);
    };


#endif //__ANIMATIONAPPVIEW_H__
