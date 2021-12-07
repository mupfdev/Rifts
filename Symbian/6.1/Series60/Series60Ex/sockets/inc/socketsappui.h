/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SOCKETSAPPUI_H__
#define __SOCKETSAPPUI_H__

#include <aknappui.h>

class CSocketsAppView;
class CSocketsEngine;

/*! 
  @class CSocketsAppUi
  
  @discussion An instance of class CSocketsAppUi is the UserInterface part of the AVKON
  application framework for the Sockets example application
  */
class CSocketsAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CSocketsAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CSocketsAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CSocketsAppUi();


/*!
  @function ~CSocketsAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CSocketsAppUi();

public: // from MEikMenuPaneObserver
/*!
  @function DynInitMenuPaneL

  @discussion Initialise a menu pane before it is displayed
  @param aMenuId id of menu
  @param aMenuPane handle for menu pane
  */
    void DynInitMenuPaneL(TInt aMenuId, CEikMenuPane* aMenuPane);


private: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

/*!
  @function HandleKeyEventL
  
  @discussion Handle user key input
  @param aKeyEvent event information
  @param aType event type
  @result EKeyWasConsumed
  */
    TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

private: // Member data
    /*! @var The application view */
    CSocketsAppView*    iAppView;

    /*! @var An RSocket wrapper to do the work for this example */
    CSocketsEngine*     iSocketsEngine;
    };


#endif // __SOCKETSAPPUI_H__

