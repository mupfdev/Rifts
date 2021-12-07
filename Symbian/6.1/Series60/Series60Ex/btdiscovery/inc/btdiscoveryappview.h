/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTDISCOVERYAPPVIEW_H__
#define __BTDISCOVERYAPPVIEW_H__

#include <coecntrl.h>
#include <btmanclient.h>
#include <btextnotifiers.h>
#include <aknlists.h>
#include "Reporter.h"
#include "BTDiscoverer.h"

/*! 
  @class CBTDiscoveyAppView
  
  @discussion container control class. Display the selected device and its service
              records.
  */

class CBTDiscoveryAppView : public CCoeControl, public MReporter
    {
public: 
/*!
  @function NewL

  @discussion Create a CBTDiscoveryAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTDiscoveryAppView
  */
    static CBTDiscoveryAppView* NewL(const TRect& aRect);

/*!
  @function NewLC

  @discussion Create a CBTDiscoveryAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTDiscoveryAppView
  */
    static CBTDiscoveryAppView* NewLC(const TRect& aRect);  

/*!
  @function ~CBTDiscoveryAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTDiscoveryAppView();

/*! 
  @function SelectDeviceAndListServicesL
  
  @discussion the services on the specified device are displayed
  */
    void SelectDeviceAndListServicesL();

/*! 
  @function ClearL
  
  @discussion clears the screen
  */
    void ClearL();

public: // from CoeControl

/*!
  @function OfferKeyEventL
  
  @discussion Handles key events.
  @param aKeyEvent The key event.
  @param aType The type of key event: EEventKey, EEventKeyUp or EEventKeyDown.
  @result Indicates whether or not the key event was used by this control.
  */
    TKeyResponse    OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

/*!
  @function CountComponentControls
  
  @discussion Gets the number of controls contained in a compound control.
  @result The number of component controls contained by this control.
  */
    TInt CountComponentControls() const;

/*!
  @function ComponentControl
 
  @discussion Gets the specified component of a compound control.
  @result The component control with an index of aIndex.
  */
    CCoeControl* ComponentControl(TInt aIndex) const;

public: // from MReporter

/*!
  @function Error

  @discussion reports an error and appends a new line.
  @param text the log text
  */
    void Error(const TDesC& text);

/*!
  @function Print
  
  @discussion reports text, does not print to the screen until PrintNewLine or
              PrintLine is invoked.
  @param text the log text
  */
    void Print(const TDesC& text);

/*!
  @function PrintLine

  @discussion reports text and appends new line.
  @param text the log text
  */
    void PrintLine(const TDesC& text);

/*!
  @function PrintNewLine
  
  @discussion prints a new line.
  */
    void PrintNewLine();


private:

/*!
  @function ConstructL

  @discussion  Perform the second phase construction of a CBTDiscoveryAppView object
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

    /*! @var iServiceDiscovery  bt service discovery and service listing */
    CBTDiscoverer* iDiscoverer;

    /*! @var iNextStr the next string to be added on invoking PrintNewLine or PrintLine */
    HBufC*  iOutputText;
    };

#endif //__BTDISCOVERYAPPVIEW_H__