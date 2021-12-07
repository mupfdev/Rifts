/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __LANGUAGE_APPVIEW_H__
#define __LANGUAGE_APPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CLanguageAppView
  
  @discussion An instance of the Application View object for the Language 
  example application
  */
class CLanguageAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CLanguageAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CLanguageAppView
  */
    static CLanguageAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CLanguageAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CLanguageAppView
  */
    static CLanguageAppView* NewLC(const TRect& aRect);


/*!
  @function ~CLanguageAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CLanguageAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CLanguageAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CLanguageAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CLanguageAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CLanguageAppView();
    };


#endif // __LANGUAGE_APPVIEW_H__
