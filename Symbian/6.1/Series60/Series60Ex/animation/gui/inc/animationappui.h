/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __ANIMATIONAPPUI_H__
#define __ANIMATIONAPPUI_H__

#include <aknappui.h>

#include "clientdll.h"
#include "clientimagecommander.h"

// Forward declarations
class CAnimationAppView;


/*! 
  @class CAnimationAppUi
  
  @discussion An instance of class CAnimationAppUi is the UserInterface part of the AVKON
  application framework for the Animation example application
  */
class CAnimationAppUi : public CAknAppUi
    {
public: // New methods

/*!
  @function CAnimationAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  @param aSession the window server session to use
  */
    CAnimationAppUi(RWsSession& aSession);

/*!
  @function ~CAnimationAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CAnimationAppUi();

public: // From CAknAppUi

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CAnimationAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

public: // From CAknAppUi

/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private: // New methods

/*!
  @function SetupClientDllL
  
  @discussion Setup the animation client Dll
  */
    void SetupClientDllL();

/*!
  @function SetupImageCommanderL
  
  @discussion Setup the animation image commander
  */
    void SetupImageCommanderL();

private:
    /** The application view */
    CAnimationAppView* iAppView;

    // Do not change the order of these variables, as they are called
    // in the AppUi constructor list in the order listed here

    /** Animation client dll, controls an animation server dll */
    RClientDll iClientDll;

    /** Animation image commander object, controls an animation image object */
    RImageCommander iClientCommander;
    };


#endif // __ANIMATIONAPPUI_H__
