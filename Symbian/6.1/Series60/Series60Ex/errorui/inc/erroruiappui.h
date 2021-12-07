/* Copyright (c) 2002, Nokia. All rights reserved */

#ifndef __ERRORUI_APPUI_H__
#define __ERRORUI_APPUI_H__

#include <aknappui.h>

// Forward reference
class CErrorUiAppView;
class CErrorUI;

/*! 
  @class CErrorUiAppUi
  
  @discussion An instance of class CErrorUiAppUi is the UserInterface part of the AVKON
  application framework for the ErrorUi example application
  */
class CErrorUiAppUi : public CAknAppUi
    {
public:

/*!
  @enum TErrorDialogType

  @discussion Type of dialog to display for errors
  @value EShowNote show a Global Error Note dialog (timed note)
  @value EShowQuery show a Global Error Query dialog (query note)
  */
   
    enum TErrorDialogType
        {
        EShowNote,
        EShowQuery
        };

public:
/*!
  @function HandleErrorL

  @discussion Handle leave errors for OOM or Cancel errors, 
  otherwise Leave and pass error to framework
  upto framework
  @param aError   error code 
  @param aType    select dialog type, note or query
  */

    void HandleLeaveErrorL(TInt aError, TErrorDialogType aType = EShowNote);

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CErrorUiAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CErrorUiAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CErrorUiAppUi();


/*!
  @function ~CErrorUiAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CErrorUiAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*! @var iAppView The application view */
    CErrorUiAppView* iAppView;

/*! @var iErrorUI The error dialog instance */
	CErrorUI*		 iErrorUI;

    };


#endif // __ERRORUI_APPUI_H__

