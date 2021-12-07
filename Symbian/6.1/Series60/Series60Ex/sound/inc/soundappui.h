// Copyright (c) 2001, Nokia. All rights reserved.

#ifndef __SOUNDAPPUI_H__
#define __SOUNDAPPUI_H__

#include <eikappui.h>
#include <aknappui.h>
#include <eikmenub.h> 
#include <e32base.h>

class MAudioAdapter;
class CToneAdapter;
class CPlayerAdapter;
class CRecorderAdapter;
class CSoundDocument;
class CSoundView;

/*! 
  @class CSoundAppUi
  
  @discussion An instance of class CSoundAppUi is the UserInterface part of the AVKON
  application framework for the Sound example application
  */
class CSoundAppUi : public CAknAppUi 
    {
public:
/*!
  @function ~CSoundAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CSoundAppUi();

/*!
  @function CSoundAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CSoundAppUi();

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CSoundAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function UpdateViewL
  
  @discussion Update the view
  */
    void UpdateViewL();
    
public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);

/*!
  @function DynInitMenuPaneL
  
  @discussion Prepare the menu prior to display
  @param aResourceId the resource for the menu to be displayed
  @param aMenuPane the handle to the menu
  */
    void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

private:
/*!
  @function SetAdapterL
  
  @discussion Set the current audio adapter to aAudioAdapter.
  @param aAudiaAdapter The adapter to use
  */
    void SetAdapterL(MAudioAdapter* aAudioAdapter);

private:

/** The audio tone adapter. */
    CToneAdapter*     iToneAdapter;

/** The audio player adapter. */
    CPlayerAdapter*   iPlayerAdapter;

/** The audio recorder adapter. */
    CRecorderAdapter* iRecorderAdapter;

/** The current audio adapter. */
    MAudioAdapter* iAudioAdapter;
    
/** The view. */
    CSoundView* iAppView;
    };

#endif // __SOUNDAPPUI_H__
