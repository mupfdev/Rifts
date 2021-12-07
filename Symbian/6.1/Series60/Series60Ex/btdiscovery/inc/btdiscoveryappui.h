/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTDISCOVERYAPPUI_H__
#define __BTDISCOVERYAPPUI_H__

#include <aknappui.h>

class CBTDiscoveryAppView;

/*! 
  @class CBTDiscoveryAppUi
  
  @discussion An instance of class CBTDiscoveryAppUi is the UserInterface part of the AVKON
  application framework for the BTDiscovery example application
  */
class CBTDiscoveryAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTDiscoveryAppUi object.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CBTDiscoveryAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CBTDiscoveryAppUi();


/*!
  @function ~CBTDiscoveryAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTDiscoveryAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /*! @var iAppView The application view */
    CBTDiscoveryAppView* iAppView;
    };


#endif // __BTDISCOVERYAPPUI_H__

