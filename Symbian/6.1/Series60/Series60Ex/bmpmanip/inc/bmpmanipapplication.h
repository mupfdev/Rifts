/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __BMPMANIP_APPLICATION_H__
#define __BMPMANIP_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CBmpmanipApplication
  
  @discussion An instance of CBmpmanipApplication is the application part of the AVKON
  application framework for the BMPMANIP example application
  */
class CBmpmanipApplication : public CAknApplication
    {
public: // from CEikApplication
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

#endif // __BMPMANIP_APPLICATION_H__
