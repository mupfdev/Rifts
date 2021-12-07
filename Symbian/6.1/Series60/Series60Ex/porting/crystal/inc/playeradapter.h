// Copyright c 2000, Nokia. All rights reserved.

#ifndef __CPLAYERADAPTER__
#define __CPLAYERADAPTER__

#include <MdaAudioSamplePlayer.h>

#include "audioadapter.h"

class CSoundAppUi;

/*! 
  @class CPlayerAdapter
  
  @discussion An instance of class CPlayerAdapter is an adapter object for 
              the CMdaAudioPlayerUtility class.
  */
class CPlayerAdapter : public CBase, public MAudioAdapter, public MMdaAudioPlayerCallback
    {
public:
/*!
  @function NewL
  
  @discussion Create a CPlayerAdapter object using two phase construction,
  and return a pointer to the created object
  @param aFileName the audio file
  @param aAppUi the User Interface
  @result pointer to new object
  */
    static CPlayerAdapter* NewL(const TDesC& aFileName, CSoundAppUi& aAppUi);
    
/*!
  @function NewLC
  
  @discussion Create a CPlayerAdapter object using two phase construction,
  and return a pointer to the created object
  @param aFileName the audio file
  @param aAppUi the User Interface
  @result pointer to new object
  */
    static CPlayerAdapter* NewLC(const TDesC& aFileName, CSoundAppUi& aAppUi);

/*!
  @function ~CPlayerAdapter
  
  @discussion Destroy the object and release all memory objects
  */
    ~CPlayerAdapter();

public: // from MAudioAdapter
/*!
  @function PlayL
  
  @discussion Begin playback of the audio sample. 
  */
    void PlayL();

/*!
  @function RecordL
  
  @discussion Do nothing. Recording is not supported.
  */
    void RecordL();

/*!
  @function StopL
  
  @discussion Stop playback of the audio sample.
              Note that this implementation of the virtual function does not leave. 
  */
    void StopL();

/*!
  @function UpdateMenuL
  
  @discussion Update the menu aMenuPane to reflect the 
              current state of the audio player utility.
              Note that this implementation of the virtual function does not leave. 
  @param aMenuPane the menu pane to update
  */
    void UpdateMenuL(CEikMenuPane* aMenuPane);

/** @semantics Update the application's command button area to reflect the current state of the audio utility. */
    void UpdateCBA();

/*!
  @function Identify
  
  @discussion Return an identifying string 
  @result An identification string 
  */    const TDesC& Identify();
    
public: // from MMdaAudioPlayerCallback
/*!
  @function MapcInitComplete
  
  @discussion Handle the event when initialisation of the audio player utility is complete.
  @param aError The status of the audio sample after initialisation
  @param aDuration The duration of the sample
  */   

    void MapcInitComplete(TInt aError, const TTimeIntervalMicroSeconds& aDuration);

/*!
  @function MapcInitComplete
  
  @discussion Handle the event when when the audio player utility completes asynchronous playing.
  @param aError The status of playback
  */
    void MapcPlayComplete(TInt aError);

protected:
    __DECLARE_TEST; 

private:

/*!
  @function CPlayerAdapter
  
  @discussion Perform the first phase of two phase construction 
  @param aAppUi the Ui to use
  */
    CPlayerAdapter(CSoundAppUi& aAppUi);
    
    
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CPlayerAdapter object
  */
    void ConstructL(const TDesC& aFileName);

private:
/** The current state of the audio player utility. */
    enum TState
        {
        ENotReady,
        EReadyToPlay,
        EPlaying
        };
    
    TState iState;

/** The audio player utility object. */
    CMdaAudioPlayerUtility* iMdaAudioPlayerUtility;

/** Reference to the application's UI object. */
    CSoundAppUi& iAppUi;
    };

#endif // __CPLAYERADAPTER__



