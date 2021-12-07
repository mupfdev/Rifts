/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __MULTIVIEWS_APPLICATION_H__
#define __MULTIVIEWS_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CMultiViewsApplication
  
  @discussion An instance of CMultiViewsApplication is the application part of the AVKON
  application framework for the MultiViews example application
  */
class CMultiViewsApplication : public CAknApplication
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

#endif // __MULTIVIEWS_APPLICATION_H__
