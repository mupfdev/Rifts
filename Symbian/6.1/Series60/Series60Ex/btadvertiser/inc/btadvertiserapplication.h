/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTADVERTISER_APPLICATION_H__
#define __BTADVERTISER_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CBTAdvertiserApplication
  
  @discussion An instance of CBTAdvertiserApplication is the application part of the AVKON
  application framework for the BTAdvertiser example application
  */
class CBTAdvertiserApplication : public CAknApplication
    {
public:  // from CAknApplication

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

#endif // __BTADVERTISER_APPLICATION_H__
