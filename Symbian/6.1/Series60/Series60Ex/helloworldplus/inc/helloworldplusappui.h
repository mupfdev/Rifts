/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLDPLUS_APPUI_H__
#define __HELLOWORLDPLUS_APPUI_H__

#include <aknappui.h>

class CHelloWorldPlusAppView;

/*! 
  @class CHelloWorldPlusAppUi
  
  @discussion An instance of class CHelloWorldPlusAppUi is the UserInterface part of the AVKON
  application framework for the HelloWorldPlus example application
  */
class CHelloWorldPlusAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CHelloWorldPlusAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CHelloWorldPlusAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CHelloWorldPlusAppUi();


/*!
  @function ~CHelloWorldPlusAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CHelloWorldPlusAppUi();


public: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView The application view */
    CHelloWorldPlusAppView* iAppView;
    };


#endif // __HELLOWORLDPLUS_APPUI_H__

