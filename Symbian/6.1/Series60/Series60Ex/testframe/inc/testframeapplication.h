/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __TESTFRAME_APPLICATION_H__
#define __TESTFRAME_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CTestframeApplication
  
  @discussion An instance of CTestframeApplication is the application part of the AVKON
  application framework for the TEST FRAMEWORK example application
  */
class CTestframeApplication : public CAknApplication
	{
private:

/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();

/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;
	};

#endif // __TESTFRAME_APPLICATION_H__
