/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __FOCUSEVENTAPPVIEW_H__
#define __FOCUSEVENTAPPVIEW_H__


#include <coecntrl.h>

static const TInt KTestFrameworkMaxScreenMessageLength = 100;
typedef TBuf<KTestFrameworkMaxScreenMessageLength> TTextLine;

/*! 
  @class CFocusEventAppView
  
  @discussion An instance of the Application View object for the FocusEvent 
  example application
  */
class CFocusEventAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CFocusEventAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CFocusEventAppView
  */
    static CFocusEventAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CFocusEventAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CFocusEventAppView
  */
    static CFocusEventAppView* NewLC(const TRect& aRect);


/*!
  @function ~CFocusEventAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CFocusEventAppView();


public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CFocusEventAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  
/*!
  @function ShowTextOnScreen
  
  @discussion Display text on the screen
  @param aText the text to display
  */
    void CFocusEventAppView::ShowTextOnScreen(const TDesC& aText);

/*!
  @function Print
  
  @discussion Display/Write text via the selected methods
  @param aText the text to display
  */
    void CFocusEventAppView::Print(const TDesC& aText);

/*!
  @function PrintNewLineL
  
  @discussion Display/Write a new line via the selected methods
  */
    void CFocusEventAppView::PrintNewLineL();

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CFocusEventAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CFocusEventAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CFocusEventAppView();

    /*! @var iTextLines The lines of text being displayed on the screen*/
	RArray <TTextLine> iTextLines;
    };


#endif // __FOCUSEVENTAPPVIEW_H__
