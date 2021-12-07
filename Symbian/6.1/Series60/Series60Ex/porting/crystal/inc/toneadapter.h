// Copyright c 2000, Nokia. All rights reserved.

#ifndef __CTONEADAPTER__
#define __CTONEADAPTER__

#include <e32std.h>

#include <MdaAudioTonePlayer.h>

#include "audioadapter.h"

class CSoundAppUi;

/*! 
  @class CToneAdapter
  
  @discussion An instance of class CToneAdapter is an adapter for the CMdaAudioToneUtility class.
  */
class CToneAdapter : public CBase, public MAudioAdapter, public MMdaAudioToneObserver
    {
public:
/*!
  @function NewL
  
  @discussion Create a CToneAdapter object using two phase construction,
  and return a pointer to the created object
  @param aAppUi the User Interface
  @result pointer to new object
  */
    static CToneAdapter* NewL(CSoundAppUi& aAppUi);
    
/*!
  @function NewLC
  
  @discussion Create a CToneAdapter object using two phase construction,
  and return a pointer to the created object
  @param aAppUi the User Interface
  @result pointer to new object
  */
    static CToneAdapter* NewLC(CSoundAppUi& aAppUi);

/*!
  @function ~CToneAdapter
  
  @discussion Destroy the object and release all memory objects
  */
    ~CToneAdapter();

public: // from MAudioAdapter
/*!
  @function PlayL
  
  @discussion Begin playback of the tone.
  */
    void PlayL();

/*!
  @function RecordL
  
  @discussion Do nothing. Recording is not supported.
  */
    void RecordL();

/*!
  @function StopL
  
  @discussion Stop playback or recording of the tone.
              Note that this implementation of the virtual function does not leave. 
  */
    void StopL();

/*!
  @function UpdateMenuL
  
  @discussion Update the menu aMenuPane to reflect the 
              current state of the audio tone utility.
              Note that this implementation of the virtual function does not leave. 
  @param aMenuPane the menu pane to update
  */
    void UpdateMenuL(CEikMenuPane* aMenuPane);

    void UpdateCBA();

/*!
  @function Identify
  
  @discussion Return an identifying string 
  @result An identification string 
  */  
    const TDesC& Identify();

public: // from MMdaAudioToneObserver

/*!
  @function MatoPrepareComplete
  
  @discussion Handle the event when a tone utility initialisation operation has completed. 
  @param aError indicates whether an error occurred.
  */
    void MatoPrepareComplete(TInt aError);

/*!
  @function MatoPlayComplete
  
  @discussion Handle the event when a tone playing operation has completed. 
  @param aError indicates whether an error occurred.
  */
    void MatoPlayComplete(TInt aError);
    
protected:
    __DECLARE_TEST; 

private:
/*!
  @function CToneAdapter
  
  @discussion Perform the first phase of two phase construction 
  @param aAppUi the Ui to use
  */
    CToneAdapter(CSoundAppUi& aAppUi);

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CToneAdapter object
  */
    void ConstructL();

private:

/** The audio tone utility object. */
    CMdaAudioToneUtility* iMdaAudioToneUtility;

/** Reference to the application's UI object. */
    CSoundAppUi& iAppUi;

    };

#endif // __CTONEADAPTER__


