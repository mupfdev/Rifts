// Copyright c 2000, Nokia. All rights reserved.

#ifndef __MAUDIOADAPTER__
#define __MAUDIOADAPTER__

#include <e32std.h>

class CEikMenuPane;

/*! 
  @class MAudioAdapter
  
  @discussion An instance of class MAudioAdapter is an adapter for an audio utility object
  */

class MAudioAdapter
    {
public:

/*! 
  @function PlayL
  
  @discussion Play the audio utility.
  */
    virtual void PlayL() = 0;

/*! 
  @function StopL
  
  @discussion Stop the audio utility.
  */
    virtual void StopL() = 0;

/*! 
  @function RecordL
  
  @discussion Record using the audio utility (if supported).
  */
    virtual void RecordL() = 0;

/*! 
  @function UpdateMenuL
  
  @discussion Update the menu aMenuPane to reflect the current state of the audio utility.
  @param aMenuPane the menu pane to update
  */
    virtual void UpdateMenuL(CEikMenuPane* aMenuPane) = 0;

/*! 
  @function UpdateCBA
  
  @discussion Update the application's command button area to reflect the current state of the audio utility.
  */
    virtual void UpdateCBA() = 0;

/*! 
  @function Identify
  
  @discussion Return an identifying string 
  @result an identifier
  */    
    virtual const TDesC& Identify() = 0;

    };

#endif // __MAUDIOADAPTER__
