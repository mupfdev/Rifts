/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __SERVERIMAGE_H__
#define __SERVERIMAGE_H__

#if !defined __W32ADLL_H__
#include <w32adll.h>
#endif

#if !defined __SERVERTIMEOUTNOTIFY_H__
#include "servertimeoutnotify.h"
#endif


// Forward reference of the timer class
class CTimeOutTimer;

/*! 
  @class CImage
  
  @discussion An instance of class CImage encapsulates the functionality 
              of the bouncing square on the screen
  */
class CImage : public CWindowAnim, public MTimeoutNotify
    {

public:  // From CWindowAnim

/*!
  @function ConstructL
  
  @discussion Complete animation server object construction (called by windows server)
  @param aArgs any arguments required during construction (passed from client through window
               server)
  @param aHasFocus true if the animation has window server focus
  */
    void ConstructL(TAny* aArgs, TBool aHasFocus);

/*!
  @function CommandReplyL
  
  @discussion Perform aCommand with optional additional arguments aArgs and return a reply
  @param aCommand the command to perform
  @param aArgs any additional arguments required 
  @note This method can return an error, so any actions that can leave should
        use this method and not Command ().   
        This command is not buffered and so requests from the client side are
        performed immediately.  For these reason these functions should not take
        a long time
  */
    TInt CommandReplyL(TInt aCommand, TAny* aArgs);

/*!
  @function Command
  
  @discussion Perform aCommand with optional additional arguments aArgs
  @param aCommand the command to perform
  @param aArgs any additional arguments required 
  @note Because there is no way to return an error from this method, it 
        is important that these commands should    not be able to fail or leave
        This command is buffered and so may have been requested by the client
        side an unknown period ago
  */
    void Command(TInt aCommand, TAny* aArgs);

/*!
  @function Redraw
  
  @discussion Redraw the animation object, called by the Windows Server
  */
    void Redraw();

/*!
  @function Animate
  
  @discussion Animate the object, normally called by the Windows Server
              at a fixed period
  */
    void Animate (TDateTime* aDateTime);

/*!
  @function FocusChanged
  
  @discussion Handle the event when the focus changes,
  @param aState TRUE if the Animation Server has focus
  */    
    void FocusChanged (TBool aState);

/*!
  @function OfferRawEvent
  
  @discussion For handling raw events. Not used in this example so return false.
  */
    TBool OfferRawEvent(const TRawEvent &aRawEvent);

public: // From MTimeoutNotify
/*!
  @function TimedOut
  
  @discussion Handle timer time out 
  */
    void TimedOut();


public:  // New functions
/*!
  @function CImage
  
  @discussion Construct the object, forced to be public
  */
    CImage();

/*!
  @function ~CImage
  
  @discussion Destroy the object
  */
    ~CImage();

private: // Data and constants

/** An animation timer object */
    CTimeOutTimer* iServerTimer;

/** The square's current position */
    TPoint iNewPoint;

/** The square's last position */
    TPoint iLastPoint;

/** The square's size */
    TSize iSize;

/** The screen size */
    TRect iScreenSize;

/** Should the animation be reset back to the beginning */
    TBool iAnimationReset;

/** Has the animation been drawn ? */
    TBool iDrawn;

/** x coordinate step */
    TBool iDeltaX;

/** y coordinate step */
    TBool iDeltaY;
    };

#endif // __SERVERIMAGE_H__
