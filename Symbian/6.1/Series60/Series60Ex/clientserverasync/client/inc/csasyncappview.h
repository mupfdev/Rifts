/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CSASYNCAPPVIEW_H__
#define __CSASYNCAPPVIEW_H__


#include <coecntrl.h>

class CCSAsyncDocument;

/*! 
  @class CCSAsyncAppView
  
  @discussion An instance of the Application View object for the CSAsync 
  example application
  */
class CCSAsyncAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CCSAsyncAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aDocument the document to read time data from
  @result a pointer to the created instance of CCSAsyncAppView
  */
    static CCSAsyncAppView* NewL(const TRect& aRect, CCSAsyncDocument& aDocument);

/*!
  @function NewLC
   
  @discussion Create a CCSAsyncAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aDocument the document to read time data from
  @result a pointer to the created instance of CCSAsyncAppView
  */
    static CCSAsyncAppView* NewLC(const TRect& aRect, CCSAsyncDocument& aDocument);


/*!
  @function ~CCSAsyncAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CCSAsyncAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CCSAsyncAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function CCSAsyncAppView
  
  @discussion Perform the first phase of two phase construction 
  @param aDocument the document to read time data from
  */
    CCSAsyncAppView(CCSAsyncDocument& aDocument);

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CCSAsyncAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

private: // data
    CCSAsyncDocument& iDocument;

    };


#endif // __CSASYNCAPPVIEW_H__
