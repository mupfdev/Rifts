/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __FOCUSEVENTAPPUI_H__
#define __FOCUSEVENTAPPUI_H__

#include <aknappui.h>

class CFocusEventAppView;

/*! 
  @class CFocusEventAppUi
  
  @discussion An instance of class CFocusEventAppUi is the UserInterface part of the AVKON
  application framework for the FocusEvent example application
  */
class CFocusEventAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CFocusEventAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CFocusEventAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CFocusEventAppUi();


/*!
  @function ~CFocusEventAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CFocusEventAppUi();

public:  // from CEikAppUi
/*!
  @function HandleForegroundEventL
  
  @discussion Handle a change of focus
  @param aForeground is ETrue is this application has focus
  */
    void HandleForegroundEventL	(TBool aForeground);

/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
    /** The application view */
    CFocusEventAppView* iAppView;
    };


#endif // __FOCUSEVENTAPPUI_H__

