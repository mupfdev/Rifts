/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CSSYNC_APPLICATION_H__
#define __CSSYNC_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CCSSyncApplication
  
  @discussion An instance of CCSSyncApplication is the application part of the AVKON
  application framework for the CSSYNC example application
  */
class CCSSyncApplication : public CAknApplication
    {
public: // from CAknApplication
/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
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

#endif // __CSSYNC_APPLICATION_H__
