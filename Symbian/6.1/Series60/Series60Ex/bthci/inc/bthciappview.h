/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTHCIAPPVIEW_H__
#define __BTHCIAPPVIEW_H__

#include <coecntrl.h>
#include <btmanclient.h>
#include <btextnotifiers.h>
#include <aknlists.h>
#include "Reporter.h"

/*! 
  @class CBTHCIAppView
  
  @discussion Container control class. Display information associated with HCI command requests.
  */

class CBTHCIAppView : public CCoeControl, public MReporter
    {
public: 
/*!
  @function NewL

  @discussion Create a CBTHCIAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTHCIAppView
  */
    static CBTHCIAppView* NewL(const TRect& aRect);

/*!
  @function NewLC

  @discussion Create a CBTHCIAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTHCIAppView
  */
    static CBTHCIAppView* NewLC(const TRect& aRect);  

/*!
  @function ~CBTHCIAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTHCIAppView();

/*! 
  @function ClearL
  
  @discussion Clear the screen
  */
    void ClearL();

public: // from CoeControl

/*!
  @function OfferKeyEventL
  
  @discussion Handle key events
  @param aKeyEvent the key event
  @param aType the type of key event: EEventKey, EEventKeyUp or EEventKeyDown
  @result indicates whether or not the key event was used by this control
  */
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

/*!
  @function CountComponentControls
  
  @discussion Get the number of controls contained in a compound control
  @result the number of component controls contained by this control
  */
    TInt CountComponentControls() const;

/*!
  @function ComponentControl
 
  @discussion Get the specified component of a compound control
  @param aIndex the component control index
  @result the component control with an index of aIndex
  */
    CCoeControl* ComponentControl(TInt aIndex) const;

public: // from MReporter

/*!
  @function Print
  
  @discussion Report text, does not print to the screen until PrintNewLine or
              PrintLine is invoked
  @param text the log text
  */
    void Print(const TDesC& text);

/*!
  @function PrintLine

  @discussion Report text and appends new line
  @param text the log text
  */
    void PrintLine(const TDesC& text);

/*!
  @function PrintNewLine
  
  @discussion Print a new line
  */
    void PrintNewLine();

private:

/*!
  @function ConstructL

  @discussion  Perform the second phase construction of a CBTHCIAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

private:

    /*! @var iListBox the control used to display the results */
    CAknSingleStyleListBox* iListBox;

    /*! @var iMessageList the list of messages to display */
    CDesCArrayFlat* iMessageList;

    /*! @var iMsgIndex the id for the next message in the list */
    TInt iMsgIndex;

    /*! @var iOutputText the next string to be added on invoking PrintNewLine or PrintLine */
    HBufC*  iOutputText;
    };

#endif //__BTHCIAPPVIEW_H__
