/* Copyright (c) 2001, Nokia. All rights reserved */

#ifndef __DIALERAPPUI_H__
#define __DIALERAPPUI_H__

#include <aknappui.h>
#include <etel.h>

class CDialerAppView;

/*! 
  @class CDialerAppUi
  
  @discussion An instance of class CDialerAppUi is the UserInterface part of the AVKON
  application framework for the Dialer example application
  */
class CDialerAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CDialerAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CDialerAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CDialerAppUi();


/*!
  @function ~CDialerAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CDialerAppUi();

/*!
  @function DialNumberL
  
  @discussion Dial a number
  @param aPhoneNumber the number to dial
  */
	void DialNumberL(const TDesC& aPhoneNumber);

public: // from CEikAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);


private:
    /** The application view */
    CDialerAppView* iAppView;
    };


#endif // __DIALERAPPUI_H__

