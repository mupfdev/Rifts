/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __BMPMANIPAPPUI_H__
#define __BMPMANIPAPPUI_H__

#include <aknappui.h>

class CBmpmanipAppView;

/*! 
  @class CBmpmanipAppUi
  
  @discussion An instance of class CBmpmanipAppUi is the UserInterface part of the AVKON
  application framework for the Bmpmanip example application
  */
class CBmpmanipAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBmpmanipAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CBmpmanipAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CBmpmanipAppUi();


/*!
  @function ~CBmpmanipAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBmpmanipAppUi();


public: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*!
  @function CommandHandlerL

  @discussion Helper function for HandleCommandL.  
  Encapsulates the switch statement that is the core of HandleCommandL.
  This is done so that the TRAPD macro in HandleCommandL is not forced to enclose the
  entire switch statement.  Solely a matter of clear programming style.
  @param aCommand the enumerated code for the option selected
  */
	void CommandHandlerL(TInt aCommand);

private:
    /** The application view */
    CBmpmanipAppView* iAppView;
    };


#endif // __BMPMANIPAPPUI_H__

