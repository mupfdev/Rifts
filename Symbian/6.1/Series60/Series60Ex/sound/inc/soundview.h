// Copyright (c) 2001, Nokia. All rights reserved.

#ifndef __SOUNDVIEW_H__
#define __SOUNDVIEW_H__

#include <coecntrl.h>
#include <coeccntx.h>

class CEikLabel;
class CSoundDocument;

/*! 
  @class CSoundView
  
  @discussion An instance of the Application View object for the Sound 
  example application
  */
class CSoundView : public CCoeControl, public MCoeControlBrushContext
    {
public:
/*!
  @function NewL
   
  @discussion Create a CSoundView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aMessage the text to use for the label
  @result a pointer to the created instance of CSoundView
  */
    static CSoundView* NewL(const TRect& aRect, const TDesC& aMessage);

/*!
  @function NewLC
   
  @discussion Create a CSoundView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @param aMessage the text to use for the label
  @result a pointer to the created instance of CSoundView
  */
    static CSoundView* NewLC(const TRect& aRect, const TDesC& aMessage);

/*!
  @function ~CSoundView
  
  @discussion Destroy the object and release all memory objects
  */
    ~CSoundView();

/*!
  @function NotifyStatusL
  
  @discussion Display a string identifying the current audio utility
  @param aMessage the string to be displayed
  */
    void NotifyStatusL(const TDesC& aMessage);

public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CSoundView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;

protected: // From CCoeControl
/*!
  @function CountComponentControls
  
  @discussion Count the number of component controls that the application view owns
  @result the number of controls
  */
    TInt CountComponentControls() const;

/*!
  @function ComponentControl
  
  @discussion Return a pointer to the 'aIndex'th component control.
  @result a pointer to the 'aIndex'th component control
  */
    CCoeControl* ComponentControl(TInt aIndex) const;

/*!
  @function SizeChanged
  
  @discussion Respond to size changed.
  */
    void SizeChanged(); 

private:

/*!
  @function CSoundView
  
  @discussion Perform the first phase of two phase construction 
  */
    CSoundView();

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CSoundView object
  @param aRect the rectangle this view will be drawn to
  @param aMessage the text to use for the label
  */
    void ConstructL(const TRect& aRect, const TDesC& aMessage);

private:

    /** The label for displaying the current sound utility identifier. */
    CEikLabel* iLabel;
    };

#endif // __SOUNDVIEW_H__

