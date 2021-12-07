/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTPOINTTOPOINTAPPVIEW_H__
#define __BTPOINTTOPOINTAPPVIEW_H__


#include <coecntrl.h>
#include <aknlists.h>
#include "Log.h"

/*! 
  @class CBTPointToPointAppView
  
  @discussion An instance of the CBTPointToPointAppView View object for the BTPointToPoint 
  example application
  */
class CBTPointToPointAppView 
:   public CCoeControl, 
    public MLog
    {
public:

/*!
  @function NewL
   
  @discussion Create a CBTPointToPointAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTPointToPointAppView
  */
    static CBTPointToPointAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CBTPointToPointAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CBTPointToPointAppView
  */
    static CBTPointToPointAppView* NewLC(const TRect& aRect);

/*!
  @function ~CBTPointToPointAppView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTPointToPointAppView();

/*!
  @function ContainsEntries

  @result ETrue if the list view contains entries
  */
    TBool ContainsEntries();

/*!
  @function ClearMessageListL
  
  @discussion Clear the list of messages.
  */
    void ClearMessageListL();

public: // from MLog
/*!
  @function LogL
  
  @discussion Add an entry to the log.
  @param aText the text of the entry
  */
    void LogL(const TDesC& aText);

/*!
  @function LogL
  
  @discussion Add an entry to the log.
  @param aText the text of the entry
  @param aExtraText extra text to append onto the entry
  */
    void LogL(const TDesC& aText, const TDesC& aExtraText);

/*!
  @function LogL
  
  @discussion Add an entry to the log.
  @param aText the text of the entry
  @param aNumber a number to append onto the entry
  */
    void LogL(const TDesC& aText, TInt aNumber);

public:  // from CCoeControl
/*!
  @function OfferKeyEventL
  
  @discussion Offer the key event to the list box
  @param aKeyEvent the key that caused the event
  @param aType the type of event that occured
  */  
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode aType);

/*!
  @function CountComponentControls
  
  @discussion Return the number of component controls
  @result the number of component controls
  */
   TInt CountComponentControls() const;

/*!
  @function ComponentControl
  
  @discussion Return a component control
  @param aIndex the index of the control to return
  @result the specified component control
  */
   CCoeControl* ComponentControl(TInt aIndex) const;

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CBTPointToPointAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CBTPointToPointAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CBTPointToPointAppView();

private:
    /*! @var iListBox the control used to display the results */
    CEikTextListBox* iListBox;

    /*! @var iMessageList the list of messages to display */
    CDesCArrayFlat* iMessageList;

    /*! @var iMsgIndex the id for the next message in the list */
    TInt iMsgIndex;

    };


#endif // __BTPOINTTOPOINTAPPVIEW_H__
