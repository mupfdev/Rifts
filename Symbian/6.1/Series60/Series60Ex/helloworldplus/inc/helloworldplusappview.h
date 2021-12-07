/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLDPLUSAPPVIEW_H__
#define __HELLOWORLDPLUSAPPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CHelloWorldPlusAppView
  
  @discussion An instance of the Application View object for the HelloWorldPlus 
  example application
  */
class CHelloWorldPlusAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CHelloWorldPlusAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CHelloWorldPlusAppView
  */
    static CHelloWorldPlusAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CHelloWorldPlusAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CHelloWorldPlusAppView
  */
    static CHelloWorldPlusAppView* NewLC(const TRect& aRect);


/*!
  @function ~CHelloWorldPlusAppView
  
  @discussion Destroy the object and release all memory
  */
     ~CHelloWorldPlusAppView();

/*!
  @function UserDraw
  
  @discussion Draw this CHelloWorldAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void UserDraw() const;


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CHelloWorldPlusAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

/*!
  @function OfferKeyEventL
  
  @discussion Handle any user keypresses
  @param aKeyEvent holds the data for the event that occurred
  @param aType holds the type of key event that occured
  @result a TKeyResponse indicating if the key was consumed or not
  */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

/*!
  @function InputCapabilities
  
  @discussion Return the capabilities of the OfferKeyEventL 
              method for this class
  @result a TCoeInputCapabilities indicating the capabilities 
          for this class
  */
	TCoeInputCapabilities InputCapabilities() const;

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CHelloWorldPlusAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CHelloWorldPlusAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CHelloWorldPlusAppView();
    };


#endif // __HELLOWORLDPLUSAPPVIEW_H__
