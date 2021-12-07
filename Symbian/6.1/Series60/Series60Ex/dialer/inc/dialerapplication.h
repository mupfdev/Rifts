/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __DIALER_APPLICATION_H__
#define __DIALER_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CDialerApplication
  
  @discussion An instance of CDialerApplication is the application part of the AVKON
  application framework for the DIALER example application
  */
class CDialerApplication : public CAknApplication
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

#endif // __DIALER_APPLICATION_H__
