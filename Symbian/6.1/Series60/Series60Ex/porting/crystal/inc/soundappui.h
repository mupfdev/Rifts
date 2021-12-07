// Copyright c 2000, Nokia. All rights reserved.

#ifndef __SOUNDAPPUI_H__
#define __SOUNDAPPUI_H__

#include <eikappui.h>

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
class CSoundAppUi : public CEikAppUi
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
  @function UpdateViewL
  
  @discussion Update the view
  */
    void UpdateViewL();

/*!
  @function DisableCBACommand
  
  @discussion Disable a specific cba/toolbar command.
  */    
    void DisableCBACommand(TInt aCommandId);

/*!
  @function EnableCBACommand
  
  @discussion Enable a specific cba/toolbar command.
  */
    void EnableCBACommand(TInt aCommandId);

/*!
  @function DrawCBA
  
  @discussion Draw the cba/toolbar.
  */
    void DrawCBA();

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CSoundAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

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
    void DynInitMenuPaneL(TInt aMenuId,CEikMenuPane* aMenuPane);

private:
/** @semantics Check if a command aCommandId is enabled on the menu/toolbar */
    TBool IsCommandEnabled(TInt aCommandId) const;

/** @semantics Cycle the current audio adapter, and its associated utility. */
    void ChangeAdapterL();

/*!
  @function SetAdapterL
  
  @discussion Set the current audio adapter to aAudioAdapter.
  @param aAudiaAdapter The adapter to use
  */
    void SetAdapterL(MAudioAdapter* aAudioAdapter);

protected:
/** @semantics Check the class invariants. */
    __DECLARE_TEST; 

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
