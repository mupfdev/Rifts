/* Copyright (c) 2001, Nokia. All rights reserved */
/*!
	@header GuiEngineApplication
	
*/

#ifndef __GUIENGINE_APPLICATION_H__
#define __GUIENGINE_APPLICATION_H__

#include <aknapp.h>


/*!
  @class CGuiEngineApplication
  @discussion An instance of CGuiEngineApplication is the application part of the CKON
  application framework for the GuiEngine example application
  */
class CGuiEngineApplication : public CAknApplication
	{
public: // New methods
/*!
  @function AppUiUid
  @abstract Return the application UI UID value (for externalising/internalising UI state)
  */
    TUid AppUiUid() const;

public:  // from CEikApplication
/*!
  @function	AppDllUid
  @abstract Return the application DLL UID value
  */
    TUid AppDllUid() const;

protected:  // from CEikApplication
/*!
  @function	CreateDocumentL
  @abstract Create a CApaDocument object and return a pointer to it
  */
    CApaDocument* CreateDocumentL();
	};

#endif // __GUIENGINE_APPLICATION_H__
