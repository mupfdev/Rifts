/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __LANGUAGE_APPUI_H__
#define __LANGUAGE_APPUI_H__

#include <aknappui.h>

class CLanguageAppView;

/*! 
  @class CLanguageAppUi
  
  @discussion An instance of class CLanguageAppUi is the UserInterface part of the AVKON
  application framework for the Language example application
  */
class CLanguageAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CLanguageAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CLanguageAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CLanguageAppUi();


/*!
  @function ~CLanguageAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CLanguageAppUi();


public: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /*! @var iAppView the application view */
    CLanguageAppView* iAppView;
    };


#endif // __LANGUAGE_APPUI_H__

