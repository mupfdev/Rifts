/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __CIPHER_APPLICATION_H__
#define __CIPHER_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CCipherApplication
  
  @discussion An instance of CCipherApplication is the application part of the AVKON
  application framework for the Cipher example application
  */
class CCipherApplication : public CAknApplication
    {
public:  // from CAknApplication

/*! 
  @function AppDllUid
  
  @discussion Return the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CAknApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __CIPHER_APPLICATION_H__
