/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTHCIAPPUI_H__
#define __BTHCIAPPUI_H__

#include <aknappui.h>

class CBTHCIAppView;
class CBTHCIUtility;

/*! 
  @class CBTHCIAppUi
  
  @discussion An instance of class CBTHCIAppUi is the UserInterface part of the AVKON
  application framework for the BTHCI example application
  */
class CBTHCIAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBTHCIAppUi object.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CBTHCIAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CBTHCIAppUi();


/*!
  @function ~CBTHCIAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBTHCIAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /*! @var iAppView the application view */
    CBTHCIAppView* iAppView;

    /*! @var iBTHCIUtility bluetooth HCI utility object */
    CBTHCIUtility* iBTHCIUtility;
    };


#endif // __BTHCIAPPUI_H__

