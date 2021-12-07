/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CSSYNCAPPVIEW_H__
#define __CSSYNCAPPVIEW_H__


#include <coecntrl.h>

class CCSSyncDocument;

/*! 
  @class CCSSyncAppView
  
  @discussion An instance of the Application View object for the CSSync 
  example application
  */
class CCSSyncAppView : public CCoeControl
    {
public:  // New methods

/*!
  @function NewL
   
  @discussion Create a CCSSyncAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aDocument the document to read time data from
  @result a pointer to the created instance of CCSSyncAppView
  */
    static CCSSyncAppView* NewL(const TRect& aRect, CCSSyncDocument& aDocument);

/*!
  @function NewLC
   
  @discussion Create a CCSSyncAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aDocument the document to read time data from
  @result a pointer to the created instance of CCSSyncAppView
  */
    static CCSSyncAppView* NewLC(const TRect& aRect, CCSSyncDocument& aDocument);

/*!
  @function ~CCSSyncAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCSSyncAppView();

public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CCSSyncAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& /*aRect*/) const;
  

private: // New methods

/*!
  @function CCSSyncAppView
  
  @discussion Perform the first phase of two phase construction 
  @param aDocument the document to read time data from
  */
    CCSSyncAppView(CCSSyncDocument& aDocument);

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CCSSyncAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

private: // Data
    CCSSyncDocument& iDocument;

    };


#endif // __CSSYNCAPPVIEW_H__
