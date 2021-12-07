/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __CSASYNCAPPUI_H__
#define __CSASYNCAPPUI_H__

#include <aknappui.h>
#include "AsyncTimeObserver.h"

class CCSAsyncAppView;
class CCSAsyncDocument;

/*! 
  @class CCSAsyncAppUi
  
  @discussion An instance of class CCSAsyncAppUi is the UserInterface part of the AVKON
  application framework for the CSAsync example application
  */
class CCSAsyncAppUi : public CAknAppUi, public MAsyncTimeObserver
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCSAsyncAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CCSAsyncAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CCSAsyncAppUi();


/*!
  @function ~CCSAsyncAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCSAsyncAppUi();

public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

/*!
  @function DynInitMenuPaneL
  
  @discussion Prepare the menu prior to display
  @param aResourceId the resource for the menu to be displayed
  @param aMenuPane the handle to the menu
  */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

public: // from MAsyncTimeObserver
/*!
  @function HandleTimeUpdate
  
  @discussion Handle updates to the time
  */
    void HandleTimeUpdate();

private:
/*!
  @function AsyncDocument
  
  @discussion cast iDocument member from CAknAppUi to CCSAsyncDocument
  */
    CCSAsyncDocument* AsyncDocument() const;

private:
    /** The application view */
    CCSAsyncAppView* iAppView;
    };


#endif // __CSASYNCAPPUI_H__

