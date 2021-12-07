/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __GRAPHICSAPPUI_H__
#define __GRAPHICSAPPUI_H__

#include <aknappui.h>

class CGraphicsAppView;

/*! 
  @class CGraphicsAppUi
  
  @discussion An instance of class CGraphicsAppUi is the UserInterface part of the AVKON
  application framework for the Graphics example application
  */
class CGraphicsAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CGraphicsAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CGraphicsAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CGraphicsAppUi();


/*!
  @function ~CGraphicsAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CGraphicsAppUi();


public: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /** The application view */
    CGraphicsAppView* iAppView;
    };


#endif // __GRAPHICSAPPUI_H__

