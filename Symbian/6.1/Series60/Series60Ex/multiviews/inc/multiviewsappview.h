/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_APPVIEW_H__
#define __MULTIVIEWS_APPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CMultiViewsAppView
  
  @discussion An instance of the Application View object for the MultiViews 
  example application
*/
class CMultiViewsAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CMultiViewsAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CMultiViewsAppView
*/
    static CMultiViewsAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CMultiViewsAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CMultiViewsAppView
*/
    static CMultiViewsAppView* NewLC(const TRect& aRect);


/*!
  @function ~CMultiViewsAppView
  
  @discussion Destroy the object and release all memory objects
*/
    ~CMultiViewsAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CMultiViewsAppView to the screen
  @param aRect the rectangle of this view that needs updating
*/
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CMultiViewsAppView object
  @param aRect the rectangle this view will be drawn to
*/
    void ConstructL(const TRect& aRect);

/*!
  @function CMultiViewsAppView
  
  @discussion Perform the first phase of two phase construction 
*/
    CMultiViewsAppView();
    };


#endif // __MULTIVIEWS_APPVIEW_H__
