/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTPOINTTOPOINT_APPUI_H__
#define __BTPOINTTOPOINT_APPUI_H__

#include <aknappui.h>

class CBTPointToPointAppView;
class CMessageClient;
class CMessageServer;

/*! 
  @class CBTPointToPointAppUi
  
  @discussion An instance of class CBTPointToPointAppUi is the UserInterface part of the AVKON
  application framework for the BTPointToPoint example application
  */
class CBTPointToPointAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTPointToPointAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CBTPointToPointAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CBTPointToPointAppUi();

/*!
  @function ~CBTPointToPointAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTPointToPointAppUi();

public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

/*!
  @function DynInitMenuPaneL
  
  @discussion Which of the receiver operations are available and set menu 
  accordingly
  @param aResourceId resource ID of the menu pane to be initialised
  @param aMenuPane the in-memory representation of the menu pane
  */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

private:
    /*! @var iAppView The application view */
    CBTPointToPointAppView* iAppView;

    /*! @var iServer the message receiving engine */
    CMessageServer* iServer;

    /*! @var iClient the message sending engine */
    CMessageClient* iClient;

    };


#endif // __BTPOINTTOPOINT_APPUI_H__

