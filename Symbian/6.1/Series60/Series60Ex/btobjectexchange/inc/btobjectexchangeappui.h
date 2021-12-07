/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTOBJECTEXCHANGE_APPUI_H__
#define __BTOBJECTEXCHANGE_APPUI_H__

#include <aknappui.h>

class CBTObjectExchangeAppView;
class CObjectExchangeClient;
class CObjectExchangeServer;

/*! 
  @class CBTObjectExchangeAppUi
  
  @discussion An instance of class CBTObjectExchangeAppUi is the UserInterface part of the AVKON
  application framework for the BTObjectExchange example application
  */
class CBTObjectExchangeAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTObjectExchangeAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CBTObjectExchangeAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CBTObjectExchangeAppUi();


/*!
  @function ~CBTObjectExchangeAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTObjectExchangeAppUi();


public: // from CEikAppUi
/*!
  @function DynInitMenuPaneL
  
  @discussion Determine which operations are available and set menu 
  accordingly
  @param aResourceId resource ID of the menu pane to be initialised
  @param aMenuPane the in-memory representation of the menu pane
  */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /*! @var iAppView the application view */
    CBTObjectExchangeAppView* iAppView;

    /*! @var iClient the client owned by this user interface */
    CObjectExchangeClient* iClient;

    /*! @var iServer the server owned by this user interface */
    CObjectExchangeServer* iServer;

    };


#endif // __BTOBJECTEXCHANGE_APPUI_H__

