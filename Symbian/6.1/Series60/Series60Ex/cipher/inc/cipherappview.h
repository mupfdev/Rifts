/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CIPHER_APPVIEW_H__
#define __CIPHER_APPVIEW_H__


#include <coecntrl.h>

/*! 
  @class CCipherAppView
  
  @discussion An instance of the Application View object for the Cipher 
  example application
  */
class CCipherAppView : public CCoeControl
    {
public:

/*!
  @function NewL
   
  @discussion Create a CCipherAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CCipherAppView
  */
    static CCipherAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CCipherAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CCipherAppView
  */
    static CCipherAppView* NewLC(const TRect& aRect);


/*!
  @function ~CCipherAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCipherAppView();

/*!
  @function PrintLineL

  @discussion Report text and appends new line.
  @param aText the log text
  */
    void PrintLineL(const TDesC& aText);

public: // from CoeControl

/*!
  @function OfferKeyEventL
  
  @discussion Handle key events.
  @param aKeyEvent The key event.
  @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown.
  @result Indicate whether or not the key event was used by this control.
  */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

/*!
  @function CountComponentControls
  
  @discussion Get the number of controls contained in a compound control.
  @result The number of component controls contained by this control.
  */
    TInt CountComponentControls() const;

/*!
  @function ComponentControl
 
  @discussion Get the specified component of a compound control.
  @result The component control with an index of aIndex.
  */
    CCoeControl* ComponentControl(TInt aIndex) const;

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CCipherAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CCipherAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CCipherAppView();

private:

    /*! @var iListBox the control used to display the results */
    CAknSingleStyleListBox* iListBox;

    /*! @var iMessageList the list of messages to display */
    CDesCArrayFlat* iMessageList;

    /*! @var iMsgIndex the id for the next message in the list */
    TInt iMsgIndex;

    /*! @var iOutputText the next string to be added on invoking PrintLineL */
    HBufC*  iOutputText;
    };


#endif // __CIPHER_APPVIEW_H__
