/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLD_APPUI_H__
#define __HELLOWORLD_APPUI_H__

#include <aknappui.h>

// Forward reference
class CHelloWorldAppView;

/*! 
  @class CHelloWorldAppUi
  
  @discussion An instance of class CHelloWorldAppUi is the UserInterface part of the AVKON
  application framework for the HelloWorld example application
  */
class CHelloWorldAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CHelloWorldAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CHelloWorldAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CHelloWorldAppUi();


/*!
  @function ~CHelloWorldAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CHelloWorldAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView The application view */
    CHelloWorldAppView* iAppView;
    };


#endif // __HELLOWORLD_APPUI_H__

