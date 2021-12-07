/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __FOCUSEVENT_APPLICATION_H__
#define __FOCUSEVENT_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CFocusEventApplication
  
  @discussion An instance of CFocusEventApplication is the application part of the AVKON
  application framework for the FOCUSEVENT example application
  */
class CFocusEventApplication : public CAknApplication
    {
public:

/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected:

/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __FOCUSEVENT_APPLICATION_H__
