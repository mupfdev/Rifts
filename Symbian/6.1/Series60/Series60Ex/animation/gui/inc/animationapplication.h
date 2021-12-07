/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __ANIMATIONAPPLICATION_H__
#define __ANIMATIONAPPLICATION_H__

#include <aknapp.h>


/*! 
  @class CCSSyncApplication
  
  @discussion An instance of CAnimationApplication is the application part of the AVKON
  application framework for the Animation example application
  */
class CAnimationApplication : public CAknApplication
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


#endif // __ANIMATIONAPPLICATION_H__
