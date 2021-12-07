/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTADVERTISER_APPUI_H__
#define __BTADVERTISER_APPUI_H__

#include <aknappui.h>

class CBTAdvertiserAppView;

/*! 
  @class CBTAdvertiserAppUi
  
  @discussion An instance of class CBTAdvertiserAppUi is the UserInterface part of the AVKON
  application framework for the BTAdvertiser example application
  */
class CBTAdvertiserAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTAdvertiserAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CBTAdvertiserAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CBTAdvertiserAppUi();


/*!
  @function ~CBTAdvertiserAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTAdvertiserAppUi();


public: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

/*!
  @function DynInitMenuPaneL
  
  @discussion Set up which of the menu operations are available
  @param aResourceId resource ID of the menu pane to be initialised
  @param aMenuPane the in-memory representation of the menu pane
  */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

private:
    /*! @var iAppView The application view */
    CBTAdvertiserAppView* iAppView;
    };


#endif // __BTADVERTISER_APPUI_H__
