/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __DIALERAPPVIEW_H__
#define __DIALERAPPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CDialerAppView
  
  @discussion An instance of the Application View object for the Dialer 
  example application
  */
class CDialerAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CDialerAppView object
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CDialerAppView
  */
    static CDialerAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CDialerAppView object
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CDialerAppView
  */
    static CDialerAppView* NewLC(const TRect& aRect);


/*!
  @function ~CDialerAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CDialerAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CDialerAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CDialerAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CDialerAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CDialerAppView();
    };


#endif // __DIALERAPPVIEW_H__
