/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CIPHER_APPUI_H__
#define __CIPHER_APPUI_H__

#include <aknappui.h>

// Forward reference
class CCipherAppView;

/*! 
  @class CCipherAppUi
  
  @discussion An instance of class CCipherAppUi is the UserInterface part of the AVKON
  application framework for the Cipher example application
  */
class CCipherAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCipherAppUi object.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CCipherAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CCipherAppUi();

/*!
  @function ~CCipherAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCipherAppUi();

/*!
  @function Encrypt
  
  @discussion Encrypt string to file \\system\\apps\\cipher\\cipher.enc
  */
    void EncryptL();

/*!
  @function Decrypt
  
  @discussion Decrypt file \\system\\apps\\cipher\\cipher.enc
  and print out the contents to the screen
  */
    void DecryptL();

public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView The application view */
    CCipherAppView* iAppView;
    };


#endif // __CIPHER_APPUI_H__

