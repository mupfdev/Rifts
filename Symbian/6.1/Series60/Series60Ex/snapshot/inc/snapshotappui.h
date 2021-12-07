/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __SNAPSHOTAPPUI_H__
#define __SNAPSHOTAPPUI_H__

#include <aknappui.h>

class CSnapShotAppView;

/*! 
  @class CSnapShotAppUi
  
  @discussion An instance of class CSnapShotAppUi is the User Interface part of the AVKON
  application framework for the SnapShot example application
  */
class CSnapShotAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CSnapShotAppUi object.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CSnapShotAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CSnapShotAppUi();


/*!
  @function ~CSnapShotAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CSnapShotAppUi();


private: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

/*!
  @function DynInitMenuPaneL
  
  @discussion Determine if the 'Take Picture' operation is available and set menu 
  accordingly
  @param aResourceId resource ID of the menu pane to be initialised
  @param aMenuPane the in-memory representation of the menu pane
  */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

private:
    /** The application view */
    CSnapShotAppView* iAppView;
    };


#endif // __SNAPSHOTAPPUI_H__

