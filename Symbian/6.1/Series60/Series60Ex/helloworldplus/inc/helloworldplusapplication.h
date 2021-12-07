/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __HELLOWORLDPLUS_APPLICATION_H__
#define __HELLOWORLDPLUS_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CHelloWorldPlusApplication
  
  @discussion An instance of CHelloWorldPlusApplication is the application part of the AVKON
  application framework for the HelloWorldPlus example application
  */
class CHelloWorldPlusApplication : public CAknApplication
    {
public:  // from CApaApplication

/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CEikApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __HELLOWORLDPLUS_APPLICATION_H__
