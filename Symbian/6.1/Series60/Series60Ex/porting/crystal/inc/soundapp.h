// Copyright c 2000, Nokia. All rights reserved.

#ifndef __SOUNDAPP_H__
#define __SOUNDAPP_H__

#include <eikapp.h>

/*! 
  @class CSoundApplication
  
  @discussion An instance of CSoundApplication is the application part of the AVKON
  application framework for the Sound example application
  */
class CSoundApplication : public CEikApplication
    {
public:
/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

private: // from CApaApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();

    };

#endif // __SOUNDAPP_H__

