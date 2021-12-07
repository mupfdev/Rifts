/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __TESTFRAMEAPPUI_H__
#define __TESTFRAMEAPPUI_H__

#include <aknappui.h>

class CTestframeAppView;

/*! 
  @class CTestframeAppUi
  
  @discussion An instance of class CTestframeAppUi is the UserInterface part of the AVKON
  application framework for the test framework example application
  */
class CTestframeAppUi : public CAknAppUi
{
public: 

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CTestframeAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CTestframeAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CTestframeAppUi();

/*!
  @function ~CTestframeAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CTestframeAppUi();

public: //from CAknAppUi

/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /*! @var iAppView The application view*/
    CTestframeAppView* iAppView;

};


#endif // __TESTFRAMEAPPUI_H__

