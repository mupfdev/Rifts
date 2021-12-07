/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_CONTAINER2_H__
#define __MULTIVIEWS_CONTAINER2_H__

#include <aknview.h>

class CMultiViewsContainer2 : public CCoeControl
    {
public: 

/*!
  @function NewL
   
  @discussion Create a CMultiViewsContainer2 object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CMultiViewsContainer2
  */
    static CMultiViewsContainer2* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CMultiViewsContainer2 object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CMultiViewsContainer2
  */
    static CMultiViewsContainer2* NewLC(const TRect& aRect);

/*!
  @fuction ConstructL
  
  @discussion Perform the second phase construction of a CMultiViewsContainer2 object
  @param aRect Frame rectangle for container.
  */
    void ConstructL(const TRect& aRect);

public: // from CoeControl
/*!
  @function CountComponentControls
  
  @discussion Gets the number of controls contained in this compound control
  @return Number of component controls 
  */
    TInt CountComponentControls() const;

/*!
  @function ComponentControl.

  @discussion Gets the specified component
  @param aIndex specification for component pointer
  @return Pointer to component control
  */
    CCoeControl* ComponentControl(TInt aIndex) const;

/*!
  @function Draw
  
  @discussion Draw this CMultiViewsContainer2 to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
    };

#endif // __MULTIVIEWS_CONTAINER2_H__