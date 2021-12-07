/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTPOINTTOPOINT_APPLICATION_H__
#define __BTPOINTTOPOINT_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CBTPointToPointApplication
  
  @discussion An instance of CBTPointToPointApplication is the application part of the AVKON
  application framework for the BTPointToPoint example application
  */
class CBTPointToPointApplication : public CAknApplication
    {
public:  // from CEikApplication

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

#endif // __BTPOINTTOPOINT_APPLICATION_H__
