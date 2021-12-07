/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __BTOBJECTEXCHANGE_APPLICATION_H__
#define __BTOBJECTEXCHANGE_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CBTObjectExchangeApplication
  
  @discussion An instance of CBTObjectExchangeApplication is the application part of the AVKON
  application framework for the BTObjectExchange example application
  */
class CBTObjectExchangeApplication : public CAknApplication
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

#endif // __BTOBJECTEXCHANGE_APPLICATION_H__
