/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTDISCOVERY_APPLICATION_H__
#define __BTDISCOVERY_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CBTDiscoveryApplication
  
  @discussion An instance of CBTDiscoveryApplication is the application part of the AVKON
  application framework for the BTDISCOVERY example application
  */
class CBTDiscoveryApplication : public CAknApplication
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

#endif // __BTDISCOVERY_APPLICATION_H__
