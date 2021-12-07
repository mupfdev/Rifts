/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __ERRORUI_APPVIEW_H__
#define __ERRORUI_APPVIEW_H__


#include <coecntrl.h>

class CErrorUI;		// Forward reference

/*! 
  @class CErrorUiAppView
  
  @discussion An instance of the Application View object for the ErrorUi 
  example application
  */
class CErrorUiAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CErrorUiAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CErrorUiAppView
  */
    static CErrorUiAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CErrorUiAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CErrorUiAppView
  */
    static CErrorUiAppView* NewLC(const TRect& aRect);


/*!
  @function ThrowLeaveErrorL

  @discussion Leave with given error code
  @param aError  leave with this error code
  */

    void CErrorUiAppView::ThrowLeaveErrorL( TInt aError );

/*!
  @function ~CErrorUiAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CErrorUiAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CErrorUiAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CErrorUiAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CErrorUiAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CErrorUiAppView();

    };


#endif // __ERRORUI_APPVIEW_H__
