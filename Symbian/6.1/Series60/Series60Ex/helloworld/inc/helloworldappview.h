/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLD_APPVIEW_H__
#define __HELLOWORLD_APPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CHelloWorldAppView
  
  @discussion An instance of the Application View object for the HelloWorld 
  example application
  */
class CHelloWorldAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CHelloWorldAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CHelloWorldAppView
  */
    static CHelloWorldAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CHelloWorldAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CHelloWorldAppView
  */
    static CHelloWorldAppView* NewLC(const TRect& aRect);


/*!
  @function ~CHelloWorldAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CHelloWorldAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CHelloWorldAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CHelloWorldAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CHelloWorldAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CHelloWorldAppView();
    };


#endif // __HELLOWORLD_APPVIEW_H__
