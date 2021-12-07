/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __GRAPHICS_APPLICATION_H__
#define __GRAPHICS_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CGraphicsApplication
  
  @discussion An instance of CGraphicsApplication is the application part of the AVKON
  application framework for the GRAPHICS example application
  */
class CGraphicsApplication : public CAknApplication
    {
public: // from CeikApplication
/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CeikApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __GRAPHICS_APPLICATION_H__
