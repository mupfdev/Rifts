/* Copyright (c) 2001, Nokia. All rights reserved */
#ifndef __CSSYNCAPPUI_H__
#define __CSSYNCAPPUI_H__

#include <aknappui.h>

class CCSSyncAppView;
class CCSSyncDocument;

/*! 
  @class CCSSyncAppUi
  
  @discussion An instance of class CCSSyncAppUi is the UserInterface part of the AVKON
  application framework for the CSSync example application
  */
class CCSSyncAppUi : public CAknAppUi
    {
public: 

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CCSSyncAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CCSSyncAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CCSSyncAppUi();

/*!
  @function ~CCSSyncAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CCSSyncAppUi();

public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

private:
/*!
  @function SyncDocument
  
  @discussion cast iDocument member from CAknAppUi to CCSSyncDocument
  */
    CCSSyncDocument* SyncDocument() const;

private:
    /** The application view */
    CCSSyncAppView* iAppView;

    };


#endif // __CSSYNCAPPUI_H__

