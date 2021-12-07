/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __RIMAGE_COMMANDER_H__
#define __RIMAGE_COMMANDER_H__


#if !defined __W32ADLL_H__
#include <w32adll.h>
#endif


/*! 
  @class RImageCommander
  
  @discussion An instance of RImageCommander is an Animation Client Commander which 
   sends commands to the Animation Server
  */
class RImageCommander : public RAnim
    {

public:  // New methods

/*!
  @function ImageCommand
  
  @discussion Send aCommand to the Animation Server object;
              aCommand == KAnimationReset implies "reset the animation"
  @param aCommand the enumerated code for the option selected
  @note Because there is no way to return an error from the server side using this
        method, it is important that any server side code for these commands should
        not be able to fail or leave
        This command is also buffered and may not be performed immediately
  */
    IMPORT_C void ImageCommand(TInt aCommand);

/*!
  @function RImageCommander
  
  @discussion Construct an Animation Client object for Animation Client DLL aAnimDll
  @param aAnimDll the Animation Client DLL to use
  */
    IMPORT_C RImageCommander(RAnimDll& aAnimDll);

/*!
  @function ImageConstruct
  
  @discussion Complete Animation Client construction
  @param aDevice the window device
  @param aType KAnimationSquare implies "Construct a bouncing square"
  @param aParams parameters to pass to the server side to tell it how to construct
                 or initialise itself
  */
    IMPORT_C void ImageConstruct(const RWindowBase& aDevice, TInt aType, const TDesC8& aParams);

public: // Constants

/** Constant used to indicate the animation of a bouncing square should 
  * be created, enumeration can be expanded
  */
    enum KAnimationTypes 
        {
        KAnimationSquare = 1
        };

/** Constant used to request a reset of the bouncing square, 
  *enumeration can be expanded */
    enum KAnimationCommands
        {
        KAnimationReset  = 1
        };
    };

#endif // __RIMAGE_COMMANDER_H__
