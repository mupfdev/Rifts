/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SOCKETSAPPVIEW_H__
#define __SOCKETSAPPVIEW_H__


#include <coecntrl.h>
#include "UINotifier.h"

// forward declarations
class CEikRichTextEditor;
class CEikLabel;

/*! 
  @class CSocketsAppView
  
  @discussion An instance of the Application View object for the Sockets 
  example application
  */
class CSocketsAppView : public CCoeControl, public MUINotifier
    {
public:

/*!
  @function NewL
   
  @discussion Create a CSocketsAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CSocketsAppView
  */
    static CSocketsAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CSocketsAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CSocketsAppView
  */
    static CSocketsAppView* NewLC(const TRect& aRect);

/*!
  @function ~CSocketsAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CSocketsAppView();

/*!
  @function ClearText
  
  @discussion Clear contents of editor window
  */
     void ClearTextL();

public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CSocketsAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;

/*!
  @function CountComponentControls

  @discussion Determine number of component controls
  @result number of component controls
  */    
    TInt CountComponentControls() const;

/*!
  @function ComponentControl

  @discussion Get handle to a component control
  @param aIndex index number of the control
  @result handle of the control
  */
    CCoeControl* ComponentControl(TInt aIndex) const;

/*!
  @function KeyEventL

  @discussion Handle a 'key event'
  @param aCode keycode
  */
    void KeyEventL(TInt aCode);

public: // From MUINotifier
/*!
  @function PrintNotify

  @discussion Display text on console
  @param aDes text to display
  @param aFontStyle style (italic/bold/etc) for this text
  */
    void PrintNotify(const TDesC& aDes, TUint aFontStyle = 0);

/*!
  @function PrintNotify

  @discussion Display text on console
  @param aDes text to display
  @param aFontStyle style (italic/bold/etc) for this text
  */
    void PrintNotify(const TDesC8& aDes, TUint aFontStyle = 0);

/*!
  @function ErrorNotify

  @discussion Notify user of an error
  @param aErrMessage message associated with error
  @param aErrCode error code
  */
    void ErrorNotify(const TDesC& aErrMessage, TInt aErrCode);

/*!
  @function SetStatus

  @discussion Change 'status' display.
  @param aStatus new status text to display
  */
    void SetStatus(const TDesC& aStatus);


private: // New methods

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CSocketsAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CSocketsAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CSocketsAppView();

/*!
  @function SetFontStyle

  @discussion Change font style for subsequent text
  @param aFontStyle new font style
  */
    void SetFontStyle(TUint aFontStyle);

/*!
  @function UpdateFontAttribute

  @discussion Set or clear an individual font attribute if necessary,
  so that it matches the required style
  @param aFontStyle required font style
  @param aAttribute the individual attribute to correct
  */
    void UpdateFontAttribute(TUint aFontStyle, TInt aAttribute);

private: // Member data

    /*! @var object for use as our output window */
    CEikRichTextEditor*   iOutputWindow;

    /*! @var Single line of text to display connection status */
    CEikLabel*            iStatusWindow;

    /*! @var Current style in use by output window */
    TUint                 iFontStyle;
    };


#endif // __SOCKETSAPPVIEW_H__
